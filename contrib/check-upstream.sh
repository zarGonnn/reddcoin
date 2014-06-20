#!/bin/sh

# Usage: check <repo> <branch> <last commit checked>

function check(){
	output="merge-$1-$2.txt"

	echo "Checking $1..."

	git fetch $1
	git cherry -v master $1/$2 $3 > $output

	echo "Done, check $output"
}

check bitcoin \
	master \
	26702e6930519c7d063796f2572a5b4ef5f29b06

check litecoin \
	master-0.8 \
	fab1907372397423e2debb44416385dc53ffd079

echo ""
echo "In the output files, commits prefixed with a + are not yet merged from upstream for some reason"
echo "or they are merged but the diffs don't match."
echo ""
echo "After checking them update the pointer to were you checked in this script."
echo ""
echo "If you don't include a commit for some reason, explain why at the bottom of this script."


<<NOTMERGED

# Not merged from Litecoin

fab1907372397423e2debb44416385dc53ffd079 Litecoin v0.8.7.2
  Obvious
cc924b775c04326e3695d897739d6f791fd76b26 Litecoin: Checkpoint at block 585010
  Obvious
73f892b5907a41af0800158ac676ede61eaf98ce upgrade to openssl-1.0.1h for CVE-2014-0224
  Gitian done separately
c2cf47946aefa4b799343be39bb740ff0b38c75e Changed old bitcoin links
  Reddcoin has own documentation
dc4cd268f521ab7ae503692eb2c56f581087ef9f Update Qt 4.8.3 download link
  Reddcoin has own release documentation
a8f8323fa9b369f8473511f1c2864ddcac997572 Change release-process.md to sign release tags
  Reddcoin has own release documentation
5a79068b5aeca439fc7ef08846b7b36175c0c600 Update build-osx.md
  Reddcoin has own release documentation
70313dd1e7518d410dac30db4906aac4846520a7 Litecoin: settxfee label in LTC
  Committed with RDD labeling
06e78495d588c5f7d8cc56b6eb379fc9c46880c5 Litecoin: Checkpoint at block 541794
  Litecoin specific
41fa6245259bb1edc226c9b49b548d23a6627fc1 Litecoin: Upgrade openssl, qt, miniupnpc, zlib, libpng, qrencode
  Reddcoin has own gitian
6ce2f0b2fb4d8a58e86919b25d86a917a6f8808f Litecoin v0.8.6.9
  Litecoin specific
aa77ae3a8c31b7bada91e53d451172f01405ce51 Litecoin v0.8.7.1
  Litecoin specific
ccd9a1f5f72235244886d108f014d40d2d6c7bd5 Update testnet DNS seeds
  Litecoin specific
f389e65c8dcb1544a023caff33da41c71fe61a80 Add testnet DNS seed from xurious.com
  Litecoin specific
570f4b03eba23abb3c09045a673105d956103847 Litecoin: Add checkpoints to testnet
  Litecoin specific, we don't have checkpoints in our testnet (yet)

# Not merged from Bitcoin (since the original fork of Litecoin upto the commit specified above)

62568f9a1e98065bd51069649f23a337eab89f94 doc: build with qt5 is currently not possible
  It works again
b2ba55c42b563418e7be4adb38cdbf1852e6c78d Avoid core dump if rpc port is in use.
  Already merged
c00237de9d4a4bce9f9e536e9e71fa2b5b0ffef5 Update michagogo's gitian pgp key, adding UIDs
  Gitian will be done separate
5ea66c54fb210a53a6d0f639b8bbd240670bf128 style-police: fixed badly readable code in ProcessMessage()
  Already merged
fbed9c9d6356f86e5507b3fc032f263a17137d57 special case DoS value == 0 in ProcessMessage()
  Already merged
61823c47dbdb371ecbffa3eb371e0a4fc8d3fee2 HTTPS-ify the downloads for the deps
  Gitian will be done separate
d18f5bf12c077c945507170276b71367fc5be9ad Switch the order of win32 deps and win32 qt in release-process.md
  Gitian will be done separate
7048443e8b5b5ca85b7440be973609bd61b31402 Fix and improve release-process.md
  Gitian will be done separate
b0730874d95e42953736f49d8041221d698ed95a Support absence of wallet (pwalletMain==NULL) in several locations, notably RPC.
  Already merged
738b8598aea6aa42d253d1520234809cd7c90471 Hardcode string in miniupnpcstring.h and remove wine requirement from deps-win32.yml
  Gitian will be done separate
f65dddc7b28e3cc8d660b3a7cf336b27c18b1ce7 misc small spelling/indentation fixes
  Already merged
b5ab7f34f8c6d2319dec3c565721bc9431c64abc Fix gitian qt-win32.yml build
  Gitian will be done separate
cd4d495ed483fad22cac765d42196481b8d19553 Update Qt 4.8.3 download link
  Gitian will be done separate
f2bc1d35d6900e044209e76533dc514d31f768fe Upgrade gitian win32 to boost-1.54.0
  Gitian will be done separate
af6c2c71ed7282791f0f09fd9e5aadb948e5bbbf Upgrade gitian win32 to Precise 12.04.
  Gitian will be done separate
c589f5f2bdc18c76d16107e557757e0d9698e6b6 build: add libcrypt32 dep for new mingw. Also ensure that libgcc/libstdc++ are static-linked regardless of the toolchain config
  Gitian will be done separate
7010e505f5c87104afecb847ecf5bf9892ddc493 Adjust weight for michagogo in gitian download scripts
  Gitian will be done separate
0766e6ced5f1b914518837c2af7a2d77c0ed276d Add michagogo to gitian download scripts
  Gitian will be done separate
9a4a7d3c6a6413b952dde12c899cf74a3fab8452 qt: english translation update
  Translations done separately
d64eef48a45d1bbbbab5adf39d6ba1fe4537cea1 Add getnetworkhashps to get the calculated network hashrate
  Already merged
08081e393b6d3249c19395f91537a7d824ec7333 included-tests: update gitian descriptors for hexdump dependency
  Gitian will be done separate
9d14e689c86a395c11a530767db4ddf895446ba8 [raw] reject insanely high fees by default in sendrawtransaction
  Already merged
f1dbed9233fb138026c646db0ac34e83ae2114f1 miner: constify CreateNewBlock() arg scriptPubKeyIn
  Already merged
24e5d7d5ae735b41beaaa7ef5feed845607c8280 Fix out-of-bounds check
  Already merged
7e1701899534151972ddff3c08cc964a9db64bc5 CreateNewBlock() now takes scriptPubKey argument, rather than a key.
  Already merged
1bb86d6f154da45464eb8b009c298dccd1cb3dab Squashed 'src/leveldb/' changes from a02ddf9..be1b0ff
  Already at 1.15
bb237705d08bcf0a5963219c9ac4866e2f60b485 Checkpoint at block 250,000
  Obvious
84d6d69fc69662b2709fffbeaf3c3b4f53c535b1 Squashed 'src/leveldb/' changes from ae6c262..a02ddf9
  Already at 1.15
f0784ac470a5541343e7985ceb0cb3c28d9a964e Fix non-standard disconnected transactions causing mempool orphans
  Already merged
2b6a8993fbcb94e318d32e4e157795e5b654bfb8 Add missing 0x prefix in chainparams.cpp
  Bitcoin specific, was already correct
8f6f92c72bc560ecf8d12fc7235a3e2222d7c033 Revert "Truncate oversize 'tx' messages before relaying/storing."
  Was not committed in the first place (see below)
d4e2b040ed5dc4f068c89039bc1a8610b68df5c7 Bugfix: Move boost/version include from db.cpp to walletdb.cpp where BOOST_VERSION is used
  Already merged
e5c4dfdfc02b91027ba58816546d28499b0581cc Make the rand tests determinstic. (fixes #2714)
  Already merged
e9bfe6572900451e79fea7686625fd1a13eb9929 Made the build/release process completable verbatim as listed in release-process.md
  Gitian will be done separate
a6635f6e95d3e5fbc9de3f8d13a9de669995a4b5 Add wtogami to gitian download scripts.
  Gitian will be done separate
091aa8dae9b7345a1cd81e2733766463dfbf4b82 RPC: add getbestblockhash, to return tip of best chain
  Already merged
adae78ea9940f4d44382967d1296e7db0b54a4de Squashed 'src/leveldb/' changes from aca1ffc..ae6c262
  Already at 1.15
c40a5aaaf484855a4350fd702e8e72fd21a68155 Truncate oversize 'tx' messages before relaying/storing.
  Reverted in future commit so no need to merge
1d626952f9fac57b8febec6bfad14b059b4184d8 Added GNU/kFreeBSD kernel name (TARGET_OS)
  Already merged
f679b2900a3a9f863f888cfb0b1a5e593628e37b MaxOSX: settings fixes (#2371)
  Already merged
25c0cce7fb494fcb871d134e28b26504d30e34d3 Qt5 compatibility
  Already merged
d98bf10f23e0e633ff2ff33075a353d30bf862b4 Move pMiningKey init out of StartRPCThreads
  Already merged
bb70bbfc5d561af230c2efcf08e660e2add1b0f1 Made more generic by removing specific version references
  Gitian scripts will be updated after merge
8c8132be73b680d04b9f6dff9dee0ae277c1bebb Prepare for 0.9 merge window
  Release specific stuff
c25e98186d0f716451ef000e55646d25e014f573 Squashed 'src/leveldb/' content from commit aca1ffc
  Not possible to merge


NOTMERGED
