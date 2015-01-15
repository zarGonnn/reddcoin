// Copyright (c) 2014-2015 Reddcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HD_WALLET_H
#define HD_WALLET_H

#include "hd/seed.h"


class CHdWalletInterface
{
protected:
     // Create the main account based on BIP-44.
    virtual bool CreateHdMainAccount() = 0;

    virtual bool GenerateNewHdSeed() = 0;
    virtual bool GetHdSeed() = 0;
    virtual bool GetHdMnemonic(std::string& mnemonic) = 0;
    virtual bool SetHdSeed(const std::string &mnemonic) = 0;

    virtual bool GetHdMasterPubKey(CExtPubKey& mpk, bool fChange) const = 0;
    virtual bool DeriveHdSecret(CExtKey &out, unsigned int n, bool fChange) = 0;
    virtual bool DeriveHdPubKey(CExtPubKey &out, unsigned int n, bool fChange) = 0;
};

#endif
