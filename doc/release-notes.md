BWS Core version 10020 is now available from:

  <https://github.com/bws/bws/releases>

This is a new minor version release, including various bug fixes and
performance improvements, as well as updated translations.

Please report bugs using the issue tracker at github:

  <https://github.com/bws/bws/issues>

Compatibility
==============

BWS Core is extensively tested on multiple operating systems using
the Linux kernel, macOS 10.8+, and Windows Vista and later.

Microsoft ended support for Windows XP on [April 8th, 2014](https://www.microsoft.com/en-us/WindowsForBusiness/end-of-xp-support),
No attempt is made to prevent installing or running the software on Windows XP, you
can still do so at your own risk but be aware that there are known instabilities and issues.
Please do not report issues about Windows XP to the issue tracker.

BWS Core should also work on most other Unix-like systems but is not
frequently tested on them.

Notable Changes
===============

Block Data Corruption
---------------------

Additional startup procedures have been added to fix corrupted blockchain databases.
The majority of users that are experiencing #106 (ConnectBlock() assertion on startup)
that have tested the new wallet have reported that their corrupt blockchain has
successfully been repaired. The new code will automatically detect and repair the
blockchain if it is able to.

If users still experience corruptions with the new wallet and it is not fixed
with the new startup procedures, it is suggested that they try using the
`-forcestart` startup flag which will bypass the new procedures altogether, and
in rare cases allow the wallet to run. If the database is not fixed by either
the automatic procedures or the `-forcestart` flag, the user should resync the
blockchain.

Additional progress has been made to prevent the wallet crashes that are causing
the corrupted databases, for example removing the Trading Window (explained below)
and fixing several other minor memory leaks that were inherited from the version
of Bitcoin that BWS was forked from.

RPC Changes
-----------

- Exporting or dumping an addresses' private key while the wallet is unlocked for
  anonymization and Staking only is no longer possible.

- A new command (`getstakingstatus`) has been added that returns the internal conditions
  for staking to be activated and their status.

- KeePass integration has been removed for the time being due to various inefficiencies
  with it's code.

Trading Window Removed
----------------------

The Bittrex trading window in the GUI wallet was problematic with it's memory
handling, often leaking, and was overall an inefficient use of resources in it's
current implementation. A revised multi-exchange trading window may be implemented
at a later date.
