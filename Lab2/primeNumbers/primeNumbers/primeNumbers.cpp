#include "stdafx.h"
#include "primeNumbers.h"

using namespace std;

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