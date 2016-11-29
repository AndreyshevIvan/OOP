#include "stdafx.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;

const int ARGUMENTS_COUNT = 2;
const int MIN_PRIME_NUMBER = 2;
const int MAX_UPPER_BOUND = 100000000;
const int MAX_PRIME_NUMBERS_COUNT = 5761456;

int StrToInt(string const& str, bool& wasError);
int CharToDigit(char ch, bool& wasError);
set<int> GeneratePrimeNumbersSet(int upperBound);

int main(int argc, char * argv[])
{
	if (argc != ARGUMENTS_COUNT)
	{
		cout << "Invalid arguments count" << "\n"
			<< "Usage: primeNumbers.exe <upperBound>" "\n";
		return 1;
	}

	bool wasError = false;
	int upperBound = StrToInt(argv[1], wasError);

	if (wasError)
	{
		return 1;
	}
	if (upperBound > MAX_UPPER_BOUND)
	{
		cout << "Invalid upperBound. UpperBound can be in range [0, 1000000000]" << "\n";
		return 1;
	}
	set<int> primeNumbers = GeneratePrimeNumbersSet(upperBound);
	
	cout << primeNumbers.size() << "\n";

	return 0;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	vector<bool> isNumberPrime(upperBound + 1, true);
	set<int> primeNumbers;

	for (int i = MIN_PRIME_NUMBER; i * i <= upperBound + 1; i++)
	{
		if (isNumberPrime[i])
		{
			for (int j = i * i; j < upperBound; j += i)
			{
				isNumberPrime[j] = false;
			}
		}
	}

	for (int i = MIN_PRIME_NUMBER; i <= upperBound; i++)
	{
		if (isNumberPrime[i])
		{
			primeNumbers.emplace(i);
		}
	}

	return primeNumbers;
}

int StrToInt(string const& str, bool& wasError)
{
	int digit;
	int result = 0;

	for (size_t i = 0; i < str.length(); i++)
	{
		digit = CharToDigit(str[i], wasError);

		if (INT_MAX / 10 >= result && INT_MAX - digit >= result * 10 && !wasError)
		{
			result *= 10;
			result = (result + digit);
		}
		else
		{
			cout << "Overflow when convert upperBound from string to int." "\n";
			wasError = true;
			return -1;
		}
	}

	return result;
}

int CharToDigit(char ch, bool& wasError)
{
	if (ch >= '0' && ch <= '9')
	{
		return (int)ch - '0';
	}
	
	wasError = true;
	cout << "Invalid symbol in input string." "\n";
	return 0;
}