// Copyright (c) 2014-2015 Reddcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HD_MNEMONIC_H
#define HD_MNEMONIC_H

#include <algorithm>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>

#include "bignum.h"
#include "hd/wordlist/english.h"


class CHdMnemonic
{
private:
	static const std::vector<std::string> wordlist;

public:
	static bool Encode(CBigNum entropy, std::string& words)
	{
		const CBigNum n = CBigNum((unsigned int)wordlist.size());
		CBigNum x;
		std::vector<std::string> result;

		while (entropy.getuint256() > 0)
		{
		    x = entropy % n;
		    entropy /= n;
		    result.push_back(wordlist[(size_t)x.getuint()]);
		}

		words = boost::algorithm::join(result, " ");
		return true;
	}

	static bool Decode(CBigNum& entropy, const std::string& words)
	{
	    const CBigNum n = CBigNum((unsigned int)wordlist.size());
	    CBigNum i = CBigNum(0);
	    std::vector<std::string> result;
	    boost::split(result, words, boost::is_any_of(" "));

	    for (std::vector<std::string>::const_reverse_iterator rit = result.rbegin(); rit != result.rend(); ++rit)
	    {
	        size_t k = std::find(wordlist.begin(), wordlist.end(), *rit) - wordlist.begin();
	        if (k == wordlist.size())
	            return false;

	        i = i * n + (unsigned int)k;
	    }

	    entropy = i;
	    return true;
	}
};

const std::vector<std::string> CHdMnemonic::wordlist = std::vector<std::string>(wordlist_en, wordlist_en+2048);

#endif
