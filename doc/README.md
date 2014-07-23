Reddcoin
================

Copyright (c) 2009-2014 Bitcoin Developers
Copyright (c) 2011-2014 Litecoin Developers
Copyright (c) 2014 Reddcoin Developers


Setup
---------------------
[Reddcoin-Qt](http://www.reddcoin.com) is the original Reddcoin client and it builds the backbone of the network. However, it downloads and stores the entire history of Reddcoin transactions; depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more.

Running
---------------------
The following are some helpful notes on how to run Reddcoin on your native platform. 

### Unix

You need the Qt4 run-time libraries to run Reddcoin-Qt. On Debian or Ubuntu:

	sudo apt-get install libqtgui4

Unpack the files into a directory and run:

- bin/32/reddcoin-qt (GUI, 32-bit) or bin/32/reddcoind (headless, 32-bit)
- bin/64/reddcoin-qt (GUI, 64-bit) or bin/64/reddcoind (headless, 64-bit)



### Windows

Unpack the files into a directory, and then run reddcoin-qt.exe.

### OSX

Drag Reddcoin-Qt to your applications folder, and then run Reddcoin-Qt.

### Need Help?

* See the documentation at the [Reddcoin Website](http://www.reddcoin.com) for help and more information.
* Ask for help on [#reddcoin](http://webchat.freenode.net?channels=reddcoin) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net?channels=reddcoin).
* Ask for help on [Reddit](http://www.reddit.com/r/reddCoin/).

Building
---------------------
The following are developer notes on how to build Reddcoin on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [OSX Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-msw.md)

Development
---------------------
The Reddcoin repo's [root README](https://github.com/reddcoin-project/reddcoin/blob/master/README.md) contains relevant information on the development process and automated testing.

- [Coding Guidelines](coding.md)
- [Multiwallet Qt Development](multiwallet-qt.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Translation Process](translation_process.md)
- [Unit Tests](unit-tests.md)

### Resources
* Discuss on [#reddcoin](http://webchat.freenode.net?channels=reddcoin) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net?channels=reddcoin).
* Discuss on [Reddit](http://www.reddit.com/r/reddCoin/).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Tor Support](tor.md)
- [Systemd](systemd.md)

License
---------------------
Distributed under the [MIT/X11 software license](http://www.opensource.org/licenses/mit-license.php).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
