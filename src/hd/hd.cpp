/**
 * Copyright (c) 2014 Reddcoin developers
 */

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <openssl/rand.h>
#include "util.h"
#include "bignum.h"
#include "wallet.h"


std::string CHDSeed::ElectrumHash(const unsigned char *seed, unsigned int nSeedLen) const
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

void CHDSeed::New()
{
    std::vector<unsigned char> vch2(nSize, 0);
    while(!RAND_bytes(&vch2[0], vch2.size()));

    CBigNum entropy = CBigNum(vch2);
    std::string key;
    do {
        vch2 = entropy.getvch();
        key = ElectrumHash((const unsigned char *)&vch2[0], vch2.size());
        if (key.substr(0, 2) == strPrefix)
            break;
        entropy++;
    } while (true);

    vch = vch2;
    std::string words;
    GetMnemonic(words);
    LogPrintf("CHSeed::New: %s\n", words.c_str());
}

bool CHDSeed::GetMnemonic(std::string& words) const
{
    if (!IsValid()) return false;

    mnemonic.Encode(CBigNum(vch), words);
    LogPrintf("CHDSeed::GetMnemonic: %s\n", words);
    return true;
}

bool CWallet::HDCreateMainAccount()
{
    if (!hdSeed.IsValid()) return false;

    account_xprv_.erase(strRootName);
    account_xpub_.erase(strRootName);

    std::vector<std::string> vNodes;
    boost::split(vNodes, strRootDerivation, boost::is_any_of("/"));
    CExtKey parent, out;

    std::vector<unsigned char> entropy;
    hdSeed.GetEntropy(entropy);
    parent.SetMaster(&entropy[0], entropy.size());

    for (std::vector<std::string>::const_iterator it = vNodes.begin(); it != vNodes.end(); ++it)
    {
        std::string node = *it;
        if (node == "" || (node == "m" && it == vNodes.begin()))
            continue;
        bool hardened = node[node.size() - 1] == '\'';
        if (hardened)
            node = node.substr(0, node.size()-1);

        try
        {
            unsigned int child = boost::lexical_cast<unsigned int>(node);
            if (hardened)
                child += BIP32_PRIME;
            if (!parent.Derive(out, child))
                return false;
            else
                parent = out;
        }
        catch(const boost::bad_lexical_cast &)
        {
            return false;
        }
    }

    account_xprv_[strRootName] = out;
    account_xpub_[strRootName] = out.Neuter();
    return true;
}

bool CWallet::HDNewSeed()
{
    hdSeed.New();
    {
        LOCK(cs_wallet);
        if (pwalletdbEncryption)
            return pwalletdbEncryption->WriteHDSeed(hdSeed);
        else
            return CWalletDB(strWalletFile).WriteHDSeed(hdSeed);
    }
}

bool CWallet::HDNewSeed(const std::vector<unsigned char>& entropy)
{
    LogPrintf("CWallet::HDSetSeed: nSize=%d\n", entropy.size());
    hdSeed = CHDSeed(entropy);
    if (!hdSeed.IsValid()) return false;

    // if (!fFileBacked)
    //     return false;
    // TODO
    // if (IsCrypted())
    //     return false;

    {
        LOCK(cs_wallet);
        if (pwalletdbEncryption)
            return pwalletdbEncryption->WriteHDSeed(hdSeed);
        else
            return CWalletDB(strWalletFile).WriteHDSeed(hdSeed);
    }
}

bool CWallet::HDGetSeed(CHDSeed& seed)
{
    if (hdSeed.IsValid())
    {
        seed = hdSeed;
        return true;
    }
    else
    {
        LOCK(cs_wallet);
        bool ret;
        if (pwalletdbEncryption)
            ret = pwalletdbEncryption->ReadHDSeed(hdSeed);
        else
            ret = CWalletDB(strWalletFile).ReadHDSeed(hdSeed);

        if (ret && hdSeed.IsValid()) {
            seed = hdSeed;
            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool CWallet::HDGetMnemonic(std::string& words)
{
    CHDSeed seed;
    HDGetSeed(seed);
    return seed.GetMnemonic(words);
}

bool CWallet::HDSetMasterPubKey(const CExtPubKey& mpk)
{
    // Don't set master public key if a seed already exists.
    if (hdSeed.IsValid()) return false;

    xpub_ = mpk;
    return true;
}

bool CWallet::HDGetMasterPubKey(CExtPubKey& mpk) const
{
    if (hdSeed.IsValid())
    {
        std::vector<unsigned char> entropy;
        hdSeed.GetEntropy(entropy);
        CExtKey mk;
        mk.SetMaster(&entropy[0], entropy.size());
        mpk = mk.Neuter();
    }
    else
    {
        mpk = xpub_;
    }
    return true;
}

bool CWallet::HDGenerateSecret(CExtKey &out, unsigned int n, bool fChange)
{
    CExtKey parent;

    if (account_xprv_.find(strRootName) == account_xprv_.end())
        HDCreateMainAccount();

    if (!account_xprv_[strRootName].Derive(parent, int(fChange)))
        return false;

    return parent.Derive(out, n);
}

bool CWallet::HDGeneratePubKey(CExtPubKey &out, unsigned int n, bool fChange)
{
    CExtPubKey parent;

    if (account_xpub_.find(strRootName) == account_xpub_.end())
        HDCreateMainAccount();

    if (!account_xpub_[strRootName].Derive(parent, int(fChange)))
        return false;

    return parent.Derive(out, n);
}
