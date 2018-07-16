// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018 The BWS developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"
#include <assert.h>
#include <boost/assign/list_of.hpp>
using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};
#include "chainparamsseeds.h"

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}
//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x000003d0cfd60da5030fab898517367c2265e4b4a037aa8d93d4d8df2cc5dfe4"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1527211317, // * UNIX timestamp of last checkpoint block
    1,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
   5600        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256("0x000005ec1afbcbfbb965c80110f0d06dbda347b51756fa4e7e223d08663d9b7c"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1527211319,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
    (0, uint256("0x000000a97c8950f7d057ecde7c62b7a8d49d041cb313107a101af9e3f2fbf99e"));

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1527211322,
    1,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);
    return &ZCParams;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
		pchMessageStart[0] = 0xd1;
		pchMessageStart[1] = 0x5a;
		pchMessageStart[2] = 0xc4;
		pchMessageStart[3] = 0x54;
        vAlertPubKey = ParseHex("0");
        nDefaultPort = 41967;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // BWS starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 910000000; //aka never
        nMaxReorganizationDepth = 100;
        nMinerThreads = 0;
        nLastPOWBlock = 23000;
        nTargetTimespan = 1 * 60; // BWS: 1 minute
        nTargetSpacing = 1 * 60;  // BWS: 1 minute
        nMaturity = 10;
		nMaxMoneyOut = 910000000 * COIN;
		nMinStakeInput = 15 * COIN;

		const char* pszTimestamp = "The Washington Post Senate approves bipartisan resolution to restore FCC net neutrality rules";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("041e2be616cdaadb196b3d15c9587dbf0f5803c04c1df97cc01699cbb7462b90d9efee0d4c4b45b63419d83013c33fa3710cd71f0e0b8f4232ba76877ecb08c847") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1527211317;
        genesis.nNonce = 22513459;
		    genesis.nBits = 0x1e0ffff0;
        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x000003d0cfd60da5030fab898517367c2265e4b4a037aa8d93d4d8df2cc5dfe4"));
        assert(genesis.hashMerkleRoot == uint256("0x613b20717cb85496bc9027ff414a578ab9ad0315430e5cfa9064e3b9f32acdc0"));

		/** Height or Time Based Activations **/
        nModifierUpdateBlock = 1;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
		nBlockEnforceInvalidUTXO = nLastPOWBlock + 1;
		// THIS MUST BE SOMETIME IN THE FUTURE AFTER BLOCK 1
        //nZerocoinStartTime = genesis.nTime + 2678400; // 31 days after genesis
        nZerocoinStartTime = genesis.nTime + 600; // 10min after genesis
		nZerocoinStartHeight = nLastPOWBlock + 1;

        vSeeds.push_back(CDNSSeedData("144.202.24.153", "144.202.24.153"));
	vSeeds.push_back(CDNSSeedData("45.76.248.116", "45.76.248.116"));
	vSeeds.push_back(CDNSSeedData("217.163.23.222", "217.163.23.222"));
	vSeeds.push_back(CDNSSeedData("80.240.20.121", "80.240.20.121"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 29); //
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 66); //
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0xe1).convert_to_container<std::vector<unsigned char> >();
        //convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;
        nPoolMaxTransactions = 3;
        strSporkKey = "0";
        strObfuscationPoolDummyAddress = "CimQVbCGNoFt1JHhoNQ1v8rMLFn6v9sqRw";
        nStartMasternodePayments = 1521792000; //Fri, 23 Mar 2018 8:00 UTC

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 2;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;
/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
		pchMessageStart[0] = 0x73;
		pchMessageStart[1] = 0x7c;
		pchMessageStart[2] = 0xd1;
		pchMessageStart[3] = 0x86;
		vAlertPubKey = ParseHex("04bcef7296a547c2c84c3e7b564ae6b3c1e4455982a2ca736d4570fd37443840873578e4ec7485027256956d4804bc5db25ed80d5546b30264b423b69fa009843d");
        nDefaultPort = 27192;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // BWS starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000000; //aka never
        nMaxReorganizationDepth = 100;
        nMinerThreads = 0;
        nLastPOWBlock = 500; // 43200 ~1 month
        nTargetTimespan = 1 * 60; // BWS: 1 minute
        nTargetSpacing = 1 * 60;  // BWS: 1 minute
        nMaturity = 10;
		nMaxMoneyOut = 21000000 * COIN;
		nMinStakeInput = 200 * COIN;
        nMasternodeCountDrift = 4;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nVersion = 1;
        genesis.nTime = 1527211319;
        genesis.nNonce = 22168579;
		    genesis.nBits = 0x1e0ffff0;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000005ec1afbcbfbb965c80110f0d06dbda347b51756fa4e7e223d08663d9b7c"));

		/** Height or Time Based Activations **/
        nModifierUpdateBlock = 1;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
		nBlockEnforceInvalidUTXO = nLastPOWBlock + 1;
		// THIS MUST BE SOMETIME IN THE FUTURE AFTER BLOCK 1
        nZerocoinStartTime = genesis.nTime + 2678400; // 31 days after genesis
		nZerocoinStartHeight = nLastPOWBlock + 1;

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("192.166.1.15", "192.166.1.15"));
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet bws addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet bws script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet bws BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet bws BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet bws BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x01)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();
        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));
        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;
        nPoolMaxTransactions = 2;
        strSporkKey = "0";
        strObfuscationPoolDummyAddress = "y57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;
/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
		pchMessageStart[0] = 0xa3;
		pchMessageStart[1] = 0xe8;
		pchMessageStart[2] = 0x00;
		pchMessageStart[3] = 0xbd;
		nDefaultPort = 51476;
        nSubsidyHalvingInterval = 210000000; //aka never
        nLastPOWBlock = 100;
        nMinerThreads = 0;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nVersion = 1;
        genesis.nTime = 1527211322;
        genesis.nNonce = 22679347;
		    genesis.nBits = 0x1e0ffff0;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000000a97c8950f7d057ecde7c62b7a8d49d041cb313107a101af9e3f2fbf99e"));

		/** Height or Time Based Activations **/
        nModifierUpdateBlock = 1;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
		nBlockEnforceInvalidUTXO = nLastPOWBlock + 1;
		// THIS MUST BE SOMETIME IN THE FUTURE AFTER BLOCK 1
        nZerocoinStartTime = genesis.nTime + 2678400; // 31 days after genesis
		nZerocoinStartHeight = nLastPOWBlock + 1;

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.
        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
        nTargetTimespan = 1 * 60;
        nTargetSpacing = 1 * 60;
        nMaturity = 10;
		nMinStakeInput = 5 * COIN;
		nMaxReorganizationDepth = 100;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;
/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.
        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }
    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}
CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}
void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;
    SelectParams(network);
    return true;
}
