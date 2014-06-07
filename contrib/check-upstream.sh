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
	c6cb40f04bdad2bb9f60aa1c177a9b12122a0d0e

check litecoin \
	master-0.8 \
	ccd9a1f5f72235244886d108f014d40d2d6c7bd5

echo ""
echo "In the output files, commits prefixed with a + are not yet merged from upstream for some reason"
echo "or they are merged but the diffs don't match."
echo ""
echo "After checking them update the pointer to were you checked in this script."
echo ""
echo "If you don't include a commit for some reason, explain why at the bottom of this script."


<<NOTMERGED

# Not merged from Litecoin

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
  Gitian will be done separatel
a6635f6e95d3e5fbc9de3f8d13a9de669995a4b5 Add wtogami to gitian download scripts.
  Gitian will be done separatel
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
