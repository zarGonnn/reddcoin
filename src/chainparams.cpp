// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "assert.h"
#include "random.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0xc0;
        pchMessageStart[2] = 0xb6;
        pchMessageStart[3] = 0xdb;
        vAlertPubKey = ParseHex("0437b4b0f5d356f205c17ffff6c46dc9ec4680ffb7f8a9a4e6eebcebd5f340d01df00ef304faea7779d97d8f1addbe1e87308ea237aae3ead96e0a736c7e9477a1");
        nDefaultPort = 45444;
        bnProofOfWorkLimit = ~uint256(0) >> 32;
        nSubsidyHalvingInterval = 50000;
        nMinerThreads = 0;

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        const char* pszTimestamp = "January 21st 2014 was such a nice day...";
        CMutableTransaction txNew(1390280400); // nTime
        txNew.nVersion = 1;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 10000 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("040184710fa689ad5023690c80f3a49c8f13f8d45b8c857fbcbc8bc4a8e4d3eb4b10f4d4604fa08dce601aaf0f470216fe1b51850b4acf21b179c45070ac7b03a9") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1390280400;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 222583475;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xb868e0d95a3c3c0e0dadc67ee587aaf9dc8acbf99e3b4b3110fad4eb74c1decc"));
        assert(genesis.hashMerkleRoot == uint256("0xb502bc1dc42b07092b9187e92f70e32f9a53247feae16d821bebffa916af79ff"));

        vSeeds.push_back(CDNSSeedData("seed.reddcoin.com", "seed.reddcoin.com"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(61);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(5);
        base58Prefixes[SECRET_KEY] =     list_of(189);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
        
        // PoSV
        bnProofOfStakeLimit = ~uint256(0) >> 20;
        bnProofOfStakeReset = ~uint256(0) >> 32; // 1
        nLastPoWBlock = 260800 - 1; // 2nd August 2014
        nStakeMinAge = 8 * 60 * 60; // 8 hours
        nStakeMaxAge = 45 * 24 *  60 * 60; // 45 days

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fDefaultCheckMemPool = false;
        fAllowMinDifficultyBlocks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
    }
};
static CMainParams mainParams;

//
// Testnet (v3)
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfe;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0xb9;
        pchMessageStart[3] = 0xde;
        vAlertPubKey = ParseHex("048b75ab041ee9965f6f57ee299395c02daf5105f208fc49e908804aad3ace5a77c7f87b3aae74d6698124f20c3d1bea31c9fcdd350c9c61c0113fd988ecfb5c09");
        nDefaultPort = 55444;
        nLastPoWBlock = 150;

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        CMutableTransaction txGenesis = genesis.vtx[0];
        genesis.nTime = txGenesis.nTime = 1399544585;
        genesis.vtx[0] = txGenesis;
        genesis.nNonce = 1403777;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x46db8d519c64586e3f0bf16153f61fdcf1d30b71ab159bf4a5b46dbcbc79d814"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("testnet-seed.reddcoin.com", "testnet-seed.reddcoin.com"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(111);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(239);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fDefaultCheckMemPool = false;
        fAllowMinDifficultyBlocks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
    }
};
static CTestNetParams testNetParams;

//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xff;
        pchMessageStart[1] = 0xc4;
        pchMessageStart[2] = 0xba;
        pchMessageStart[3] = 0xdf;
        nSubsidyHalvingInterval = 150;
        nMinerThreads = 1;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1401051600;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 3;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 56444;
        assert(hashGenesisBlock == uint256("0472dc040de80ded8bd385a2b6bc6e4e05cb6432047efa07692724c6ccef40ac"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultCheckMemPool = true;
        fAllowMinDifficultyBlocks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    switch (network) {
        case CBaseChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CBaseChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CBaseChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    if (!SelectBaseParamsFromCommandLine())
        return false;

    SelectParams(BaseParams().NetworkID());
    return true;
}
