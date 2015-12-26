// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

#include <stdint.h>

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double SIGCHECK_VERIFICATION_FACTOR = 5.0;

    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64_t nTimeLastCheckpoint;
        int64_t nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    bool fEnabled = true;

    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (    10, uint256("0xa198c38a77555a9fbff0b147bf7ce0660416d6abdaa86adaa3a9be97092592ed"))
        (  1000, uint256("0x9d849e078deac30d58372db898318186cf5073a7f0b109b4776393b21b7b4e5a"))
        (  2000, uint256("0x4674c50137c1d9bf47d96dee5e8c38c41895d494a0bb71e243d1c8a6c805e1f7"))
        (  3000, uint256("0x0deff246b8dfc102ccdbc3a306649be82c441e1da0fba8ca1075cf6b5d7f3c01"))
        (  4000, uint256("0xad880a4c23d511f04311e98ee77f5163e54cd92f80433e9f3bd6bc2261d50592"))
        (  5000, uint256("0x3f673ef045f4a7d71fb841ce96ed190b20569182bd3dfe628527ec3a7934d08f"))
        (  6000, uint256("0x1222056e58dce70c0a6638e07415bd6190fa5ccdd6d5e7f6af68abb30ebd4eb8"))
        (  6150, uint256("0xe221b12cf8b0c264697e9bb3c9c9f0f7ada5f2736e054cbd53b94852908cdbd3"))
        ( 10000, uint256("0x35d5f9cbd94c15771d5ebebf55ea4bfc649c473c0a868fe4d1832f5b45bd5d0c"))
        ( 15000, uint256("0x87a8c4289e661720095f2ab6a077151bc84b9615a53c5e7207ba1c20418bd178"))
        ( 20000, uint256("0x6a86a4cbbcea694027591ba416ae3831b4f3f9aa3cc6a0a1b5627f920dd765bb"))
        ( 44878, uint256("0xd81a3724a81b78e762821d16bfe23565576905685b2c072ea9a3fa7d36dbad8b"))
        ( 45189, uint256("0xd10b5da162b922d3cf09c44ea3d533a203c9ab1c442015d7e72f21062d20aeb4"))
        ( 45239, uint256("0xe14dba7c7d1ed1a7566e23b0ca0989e3e26099b7beaa673d324001d1291223f7"))
        (114834, uint256("0xdc5c776ca006c6d40e48c90aeeb43bf6493de589e28f779b486e64aa3403344a"))
        (184000, uint256("0xe22e6b027cd49cd9aa2ba6df0e0c264c2eed5656b1fa39052c8235d52f2b04d6"))
        (244999, uint256("0x0b7bb56edfae2f2f1e71ac39daab16614fccf1a1e02c58d4169521d76d880b42"))
        ;
    static const CCheckpointData data = {
        &mapCheckpoints,
        1406060223, // * UNIX timestamp of last checkpoint block
        934860,     // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        8000.0      // * estimated number of transactions per day after checkpoint
    };

    static MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 0, uint256("0xa12ac9bd4cd26262c53a6277aafc61fe9dfe1e2b05eaa1ca148a5be8b394e35a"))
        ;
    static const CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1399544585,
        1,
        2000
    };

    static MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of
        ( 0, uint256("0x0472dc040de80ded8bd385a2b6bc6e4e05cb6432047efa07692724c6ccef40ac"))
        ;
    static const CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        1401051600,
        1,
        10
    };

    const CCheckpointData &Checkpoints() {
        if (Params().NetworkID() == CChainParams::TESTNET)
            return dataTestnet;
        else if (Params().NetworkID() == CChainParams::MAIN)
            return data;
        else
            return dataRegtest;
    }

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (!fEnabled)
            return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex, bool fSigchecks) {
        if (pindex==NULL)
            return 0.0;

        int64_t nNow = time(NULL);

        double fSigcheckVerificationFactor = fSigchecks ? SIGCHECK_VERIFICATION_FACTOR : 1.0;
        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkpoint, and
        // fSigcheckVerificationFactor per transaction after.

        const CCheckpointData &data = Checkpoints();

        if (pindex->nChainTx <= data.nTransactionsLastCheckpoint) {
            double nCheapBefore = pindex->nChainTx;
            double nCheapAfter = data.nTransactionsLastCheckpoint - pindex->nChainTx;
            double nExpensiveAfter = (nNow - data.nTimeLastCheckpoint)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore;
            fWorkAfter = nCheapAfter + nExpensiveAfter*fSigcheckVerificationFactor;
        } else {
            double nCheapBefore = data.nTransactionsLastCheckpoint;
            double nExpensiveBefore = pindex->nChainTx - data.nTransactionsLastCheckpoint;
            double nExpensiveAfter = (nNow - pindex->nTime)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore + nExpensiveBefore*fSigcheckVerificationFactor;
            fWorkAfter = nExpensiveAfter*fSigcheckVerificationFactor;
        }

        return fWorkBefore / (fWorkBefore + fWorkAfter);
    }

    int GetTotalBlocksEstimate()
    {
        if (!fEnabled)
            return 0;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (!fEnabled)
            return NULL;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
