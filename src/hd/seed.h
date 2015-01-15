// Copyright (c) 2014-2015 Reddcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HD_SEED_H
#define HD_SEED_H

#include "serialize.h"
#include "key.h"
#include "hd/mnemonic.h"


// hardened derivation
#define BIP32_PRIME 0x80000000;


class CHdSeed
{
private:
    std::vector<unsigned char> vch;
    std::string SeedHash(const unsigned char *seed, unsigned int nSeedLen) const;

public:
    static const unsigned int nVersion = 9;
    static const unsigned int nSize = 17; // 128 bits + 8 bits of prefix
    static const std::string strPrefix;

    CHdSeed() {}

    bool IsValid() const
    {
        std::string key = SeedHash((const unsigned char *)&vch[0], vch.size());
        return key.substr(0, 2) == strPrefix;
    }

    void Generate();

    bool GetEntropy(std::vector<unsigned char>& entropy) const
    {
        if (!IsValid()) return false;

        entropy = vch;
        return true;
    }

    bool GetMnemonic(std::string& words) const;
    bool SetMnemonic(const std::string& words);

    IMPLEMENT_SERIALIZE
    (
        READWRITE(vch);
    )
};

const std::string CHdSeed::strPrefix = "01";

#endif
