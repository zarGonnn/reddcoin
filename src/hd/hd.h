/*
 * Copyright (c) 2014 Reddcoin developers
 */

#ifndef HD_WALLET_H
#define HD_WALLET_H

#include "serialize.h"
#include "key.h"
#include "hd/mnemonic.h"


// hardened derivation
#define BIP32_PRIME 0x80000000;


class CHDSeed
{
private:
    unsigned int nVersion;
    unsigned int nSize; 
    std::string strPrefix;
    std::vector<unsigned char> vch;
    CElectrumMnemonic mnemonic;

    std::string ElectrumHash(const unsigned char *seed, unsigned int nSeedLen) const;

public:
    CHDSeed()
    {
        nVersion = 9;
        nSize = 17; // 128 bits + 8 bits of prefix
        strPrefix = "01";
    }

    CHDSeed(const std::vector<unsigned char>& seed)
    {
        nVersion = 9;
        nSize = 17; // 128 bits + 8 bits of prefix
        strPrefix = "01";

        if (seed.size() == nSize)
            vch = seed;
    }

    bool IsValid() const
    {
        return vch.size() == nSize;
    }

    void New();

    bool GetEntropy(std::vector<unsigned char>& entropy) const
    {
        if (!IsValid()) return false;

        entropy = vch;
        return true;
    }

    bool GetMnemonic(std::string& words) const;

    IMPLEMENT_SERIALIZE
    (
        READWRITE(nVersion);
        READWRITE(nSize);
        READWRITE(vch);
    )    
};

class CHDWalletInterface
{
protected:
     // Create the main account based on BIP-44.
    virtual bool HDCreateMainAccount() =0;

    virtual bool HDNewSeed() =0;
    virtual bool HDNewSeed(const std::vector<unsigned char>& entropy) =0;
    virtual bool HDGetSeed() =0;
    virtual bool HDGetMnemonic(std::string& mnemonic) =0;

    virtual bool HDSetMasterPubKey(const CExtPubKey& mpk) =0;
    virtual bool HDGetMasterPubKey(CExtPubKey& mpk) const =0;

    virtual bool HDGenerateSecret(CExtKey &out, unsigned int n, bool fChange) =0;
    virtual bool HDGeneratePubKey(CExtPubKey &out, unsigned int n, bool fChange) =0;
};

#endif
