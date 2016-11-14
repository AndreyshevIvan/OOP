#include "stdafx.h"
#include <iostream>
#include <string>
#include <cmath>

const int ARGUMENTS_COUNT = 4;
const int MIN_RADIX = 2;
const int MAX_RADIX = 36;

using namespace std;

bool CheckArgumentsCount(int& argc);
bool CheckRadix(int& radix);
int StringToInt(const string& str, int radix, bool& wasError);
int CharToDigit(const char& ch);
bool CheckOverflow(int& result, const int& addedValue, const bool& isNumberNegative);
bool CheckDigit(int& digit, int& radix);

int main(int argc, char * argv[])
{
	bool wasError = false;

	if (!CheckArgumentsCount(argc))
		return EXIT_FAILURE;

	int sourceRadix = stoi(argv[1]);
	int destenationRadix = stoi(argv[2]);

	if (!CheckRadix(sourceRadix) || !CheckRadix(destenationRadix))
		return EXIT_FAILURE;

	const string value = argv[3];

	if (sourceRadix == destenationRadix)
	{
		cout << value << "\n";
		return 1;
	}

	int valueInDec = StringToInt(value, sourceRadix, wasError);
	if (wasError)
		return EXIT_FAILURE;

	cout << valueInDec << "\n";

    return 0;
}

bool CheckArgumentsCount(int& argc)
{
	if (argc != ARGUMENTS_COUNT)
	{
		cout << "Invalid arguments count" "\n"; 
		cout << "Usage: replace.exe <source notation> <destenation notation> <value>" "\n";
		return false;
	}

	return true;
}

bool CheckRadix(int& radix)
{
	if (radix < MIN_RADIX || radix > MAX_RADIX)
	{
		cout << "Invalid notation value" "\n";
		cout << "Radix should be in the range [2; 36]" "\n";
		return false;
	}
	
	return true;
}

int StringToInt(const string& str, int radix, bool& wasError)
{
	int result = 0;
	int digit = 0;
	size_t digitPos = 0;
	const bool isNumberNegative = (str[0] == '-');

	if (isNumberNegative)
		digitPos = 1;

	for (digitPos; digitPos < str.length(); digitPos++)
	{
		digit = CharToDigit(str[digitPos]);
		if (!CheckDigit(digit, radix))
		{
			wasError = true;
			return -1;
		}

		const int addedValue = digit * (int)pow(radix, str.length() - digitPos - 1);
		if (!CheckOverflow(result, addedValue, isNumberNegative))
		{
			wasError = true;
			return -1;
		}

		if (isNumberNegative)
			result -= addedValue;
		else
			result += addedValue;
	}

	return result;
}

int CharToDigit(const char& ch)
{
	int result;

	if (ch >= '0' && ch <= '9')
	{
		result = (int)ch - '0';
	}
	else if (ch > '9' && ch <= 'Z')
	{
		result = (int)ch - 'A' + 10;
	}

	return result;
}

bool CheckOverflow(int& result, const int& addedValue, const bool& isNumberNegative)
{
	if (isNumberNegative)
	{
		if (result >= (INT_MIN + addedValue))
			return true;
	}
	else if (result <= (INT_MAX - addedValue))
			return true;

	cout << "Overflow" "\n";
	return false;
}

bool CheckDigit(int& digit, int& radix)
{
	if (digit >= 0 || digit < radix)
		return true;

	cout << "Invalid character for this notation" "\n";
	return false;
}