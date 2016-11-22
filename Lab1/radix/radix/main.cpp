#include "stdafx.h"
#include <iostream>
#include <string>
#include <cmath>

const int ARGUMENTS_COUNT = 4;
const int MIN_RADIX = 2;
const int MAX_RADIX = 35;

using namespace std;

bool IsRadixValid(int radix);
bool IsAddingAllowed(int result, int addedValue, bool isNumberNegative);

int StringToInt(string const& str, int radix, bool& wasError);
string IntToString(int value, int radix, bool& wasError);
int CharToDigit(char ch);
char DigitToChar(int digit);
const int CalculateAddedValue(int digit, int radix, size_t const& digitOrder, bool& wasError);

int main(int argc, char * argv[])
{
	if (argc != ARGUMENTS_COUNT)
	{
		cout << "Invalid arguments count" "\n"
			"Usage: replace.exe <source notation> <destenation notation> <value>" "\n";
		return 1;
	};

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

	if (!wasError)
	{
		const bool isValueNegative = (valueInDec < 0);
		string valueInRadix = IntToString(valueInDec, destenationRadix, wasError);
		if (isValueNegative)
			valueInRadix = "-" + valueInRadix;

		cout << valueInRadix << "\n";
		return 0;
	}
	
	return 1;
}

bool IsRadixValid(int radix)
{
	return (radix >= MIN_RADIX && radix <= MAX_RADIX);
}

int StringToInt(string const& str, int radix, bool& wasError)
{
	int result = 0;
	int digit = 0;
	size_t digitPos = 0;
	const bool isNumberNegative = (str[0] == '-');
	
	if (isNumberNegative)
		digitPos++;

	for (digitPos; digitPos < str.length(); digitPos++)
	{
		digit = CharToDigit(str[digitPos]);

		if (digit < 0 && digit >= radix)
		{
			cout << "Invalid digit for this notation" "\n";
			wasError = true;
			return 1;
		}

		const size_t digitOrder = str.length() - digitPos - 1;
		const int addedValue = CalculateAddedValue(digit, radix, digitOrder, wasError);

		if (!wasError)
		{
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
		else
		{
			cout << "Overflow: Forbidden to calculate added value" "\n";
			return 1;
		}
	}

	return result;
}

string IntToString(int value, int radix, bool& wasError)
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

int CharToDigit(char ch)
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

char DigitToChar(int digit)
{
	char result;

	if (digit >= 0 && digit <= 9)
	{
		result = char(digit + '0');
	}
	else if (digit > 9 && digit <= MAX_RADIX)
	{
		result = char(digit + 'A' - 10);
	}

	return result;
}

bool IsAddingAllowed(int result, int addedValue, bool isNumberNegative)
{
	if (isNumberNegative)
	{
		return (result >= (INT_MIN + addedValue));
	}
	else
	{
		return (result <= (INT_MAX - addedValue));
	}

	return false;
}

const int CalculateAddedValue(int digit, int radix, size_t const& digitOrder, bool& wasError)
{
	const bool isExponentValid = (log(INT_MAX) / log(radix) >= digitOrder);
	const bool isDigitValid = (INT_MAX / pow(radix, digitOrder <= digit));

	if (isExponentValid && isDigitValid)
	{
		return (digit * pow(radix, digitOrder));
	}

	wasError = true;
	return 1;
}