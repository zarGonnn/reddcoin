// Copyright (c) 2014-2015 Reddcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <openssl/rand.h>
#include "util.h"
#include "bignum.h"
#include "hd/seed.h"


std::string CHdSeed::SeedHash(const unsigned char *seed, unsigned int nSeedLen) const
{
    static const char hashkey[] = {'S','e','e','d',' ','v','e','r','s','i','o','n'};
    HMAC_SHA512_CTX ctx;
    HMAC_SHA512_Init(&ctx, hashkey, sizeof(hashkey));
    HMAC_SHA512_Update(&ctx, seed, nSeedLen);
    unsigned char out[64];
    LockObject(out);
    HMAC_SHA512_Final(out, &ctx);
    std::string key = HexStr(BEGIN(out), END(out));
    UnlockObject(out);
    return key;
}

void CHdSeed::Generate()
{
    std::vector<unsigned char> vch2(nSize, 0);
    RandAddSeedPerfmon();
    while(!RAND_bytes(&vch2[0], vch2.size()));

    CBigNum entropy = CBigNum(vch2);
    std::string key;
    do {
        key = SeedHash((const unsigned char *)&vch2[0], vch2.size());
        if (key.substr(0, 2) == strPrefix)
            break;
        entropy++;
        vch2 = entropy.getvch();
    } while (true);

    vch = vch2;
}

bool CHdSeed::GetMnemonic(std::string& words) const
{
    return IsValid() && CHdMnemonic::Encode(CBigNum(vch), words);
}

bool CHdSeed::SetMnemonic(const std::string& words)
{
    CBigNum entropy;
    if (!CHdMnemonic::Decode(entropy, words))
        return false;

    std::vector<unsigned char> vch2 = entropy.getvch();
    std::string key = SeedHash((const unsigned char *)&vch2[0], vch2.size());
    if (key.substr(0, 2) != strPrefix)
        return false;

    vch = vch2;
    return true;
}

