/*
 * Copyright (c) 2014 Reddcoin developers
 */

#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include "util.h"
#include "hd/mnemonic.h"


bool CElectrumMnemonic::Encode(CBigNum entropy, std::string& words) const
{
    const CBigNum n = CBigNum((unsigned int)wordlist_.size());
    CBigNum x;
    std::vector<std::string> result;

    while (entropy.getuint256() > 0)
    {
        x = entropy % n;
        entropy /= n;
        result.push_back(wordlist_[(size_t)x.getuint()]);
    }

    words = boost::algorithm::join(result, " ");
    return true;
}

bool CElectrumMnemonic::Decode(CBigNum& entropy, const std::string& words) const
{
    const CBigNum n = CBigNum((unsigned int)wordlist_.size());
    CBigNum i = CBigNum(0);
    std::vector<std::string> result;
    boost::split(result, words, boost::is_any_of(" "));

    for (std::vector<std::string>::const_reverse_iterator rit = result.rbegin(); rit != result.rend(); ++rit)
    {
        size_t k = std::find(wordlist_.begin(), wordlist_.end(), *rit) - wordlist_.begin();
        if (k == wordlist_.size())
            return false;

        i = i * n + (unsigned int)k;
    }

    entropy = i;
    return true;
}
