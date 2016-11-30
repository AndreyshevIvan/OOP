#pragma once
#include "stdafx.h"

const int MIN_PRIME_NUMBER = 2;
const int MAX_UPPER_BOUND = 100000000;

int StrToInt(std::string const& str, bool& wasError);
int CharToDigit(char ch, bool& wasError);
std::set<int> GeneratePrimeNumbersSet(int upperBound);