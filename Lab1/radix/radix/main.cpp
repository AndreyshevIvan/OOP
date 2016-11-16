#include "stdafx.h"
#include <iostream>
#include <string>
#include <cmath>

const int ARGUMENTS_COUNT = 4;
const int MIN_RADIX = 2;
const int MAX_RADIX = 35;

using namespace std;

bool IsArgumentsCountValid(int argc);
bool IsRadixValid(int const& radix);
bool IsAddingAllowed(int result, int const& addedValue, bool const& isNumberNegative);
bool IsDigitValid(int const& digit, int const& radix);

int StringToInt(string const& str, int const& radix, bool& wasError);
string IntToString(int const& value, int const& radix, bool& wasError);
int CharToDigit(char const& ch);
char DigitToChar(int const& digit);
const int CalculateAddedValue(int const& digit, int const& radix, size_t const& digitOrder, bool& wasError);

int main(int argc, char * argv[])
{
	if (!IsArgumentsCountValid(argc))
	{
		cout << "Invalid arguments count" "\n"
			"Usage: replace.exe <source notation> <destenation notation> <value>" "\n";
		return 1;
	}

	const int sourceRadix = stoi(argv[1]);
	const int destenationRadix = stoi(argv[2]);

	if (!IsRadixValid(sourceRadix) || !IsRadixValid(destenationRadix))
	{
		cout << "Invalid notation value" "\n"
			"Radix should be in the range [2; 36]" "\n";
		return 1;
	}

	const string value = argv[3];
	bool wasError = false;
	const int valueInDec = StringToInt(value, sourceRadix, wasError);

	if (wasError)
		return 1;

	const bool isValueNegative = (valueInDec < 0);
	string valueInRadix = IntToString(valueInDec, destenationRadix, wasError);
	if (isValueNegative)
		valueInRadix = "-" + valueInRadix;

	cout << valueInRadix << "\n";

    return 0;
}

bool IsArgumentsCountValid(int argc)
{
	return (argc == ARGUMENTS_COUNT);
}

bool IsRadixValid(int const& radix)
{
	return (radix >= MIN_RADIX && radix <= MAX_RADIX);
}

int StringToInt(string const& str, int const& radix, bool& wasError)
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

		if (!IsDigitValid(digit, radix))
		{
			cout << "Invalid digit for this notation" "\n";
			wasError = true;
			return 1;
		}

		const size_t digitOrder = str.length() - digitPos - 1;
		const int addedValue = CalculateAddedValue(digit, radix, digitOrder, wasError);

		if (wasError)
		{
			cout << "Overflow: Invalid calculate added value" "\n";
			return 1;
		}

		if (!IsAddingAllowed(result, addedValue, isNumberNegative))
		{
			cout << "Overflow: Invalid adding added value" "\n";
			wasError = true;
			return 1;
		}

		if (isNumberNegative)
			result -= addedValue;
		else
			result += addedValue;
	}

	return result;
}

string IntToString(int const& value, int const& radix, bool& wasError)
{
	string result = "";
	const bool isNumberNegative = (value < 0);
	int mod = 0;
	unsigned int div = abs(value);

	while (div >= radix)
	{
		mod = div % radix;
		div = (div - mod) / radix;
		result = DigitToChar(mod) + result;
	}
	result = DigitToChar(div) + result;

	return result;
}

int CharToDigit(char const& ch)
{
	int result = -1;

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

char DigitToChar(int const& digit)
{
	char result;
	string testStr;

	if (digit >= 0 && digit <= 9)
	{
		result = char(digit + '0');
	}
	else if (digit > 9 && digit <= MAX_RADIX)
	{
		result = char(digit + 'A' - 10);
	}

	testStr = result;

	return result;
}

bool IsAddingAllowed(int result, int const& addedValue, bool const& isNumberNegative)
{
	if (isNumberNegative)
		return (result >= (INT_MIN + addedValue));
	else
		return (result <= (INT_MAX - addedValue));

	return false;
}

bool IsDigitValid(int const& digit, int const& radix)
{
	return (digit >= 0 && digit < radix);
}

const int CalculateAddedValue(int const& digit, int const& radix, size_t const& digitOrder, bool& wasError)
{
	const bool isExponentValid = (log(INT_MAX) / log(radix) >= digitOrder);
	const bool IsDigitValid = (INT_MAX / pow(radix, digitOrder <= digit));

	if (isExponentValid && IsDigitValid)
	{
		return digit * pow(radix, digitOrder);
	}

	wasError = true;
	return 1;
}