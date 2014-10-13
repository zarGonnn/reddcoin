/*
 * Copyright (c) 2014 Reddcoin developers
 */

#ifndef HD_MNEMONIC_H
#define HD_MNEMONIC_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "bignum.h"
#include "hd/wordlist/english.h"


class CElectrumMnemonic
{
private:
	std::vector<std::string> wordlist_;

public:
	CElectrumMnemonic()
	{
		wordlist_ = std::vector<std::string>(wordlist_en, std::end(wordlist_en));
	}

	bool Encode(CBigNum entropy, std::string& words) const;
	bool Decode(CBigNum& entropy, const std::string& words) const;
};

#endif
