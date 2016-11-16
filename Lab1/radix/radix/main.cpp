#include "stdafx.h"
#include <iostream>
#include <string>
#include <cmath>

const int ARGUMENTS_COUNT = 4;
const int MIN_RADIX = 2;
const int MAX_RADIX = 36;

using namespace std;

bool IsArgumentsCountValid(int argc);
bool IsRadixValueValid(int radix);
bool IsAddedValueValid(int result, const int addedValue, const bool isNumberNegative);
bool IsDigitValid(int digit, int radix);

int StringToInt(const string str, int radix, bool& wasError);
string IntToString(int value, int radix, bool& wasError);
int CharToDigit(const char ch);
char DigitToChar(const int digit);
const int CalculateAddedValue(int digit, int radix, const size_t digitOrder, bool& wasError);

int main(int argc, char * argv[])
{
	bool wasError = false;

	if (!IsArgumentsCountValid(argc))
		return 1;

	int sourceRadix = stoi(argv[1]);
	int destenationRadix = stoi(argv[2]);

	if (!IsRadixValueValid(sourceRadix) || !IsRadixValueValid(destenationRadix))
		return 1;

	const string value = argv[3];

	if (sourceRadix == destenationRadix)
	{
		cout << value << "\n";
		return 1;
	}

	int valueInDec = StringToInt(value, sourceRadix, wasError);
	bool isValueNegative = (valueInDec < 0);
	if (wasError)
		return 1;

	string valueInRadix = IntToString(valueInDec, destenationRadix, wasError);
	if (isValueNegative)
		valueInRadix = "-" + valueInRadix;
	cout << valueInRadix << "\n";

    return 0;
}

bool IsArgumentsCountValid(int argc)
{
	if (argc != ARGUMENTS_COUNT)
	{
		cout << "Invalid arguments count" "\n"
			"Usage: replace.exe <source notation> <destenation notation> <value>" "\n";
		return false;
	}

	return true;
}

bool IsRadixValueValid(int radix)
{
	if (radix > MIN_RADIX && radix < MAX_RADIX)
	{
		return true;
	}
	
	cout << "Invalid notation value" "\n"
		"Radix should be in the range [2; 36]" "\n";
	return false;
}

int StringToInt(const string str, int radix, bool& wasError)
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
			wasError = true;
			return 1;
		}

		const size_t digitOrder = str.length() - digitPos - 1;
		const int addedValue = CalculateAddedValue(digit, radix, digitOrder, wasError);

		if (wasError)
			return 1;

		if (!IsAddedValueValid(result, addedValue, isNumberNegative))
		{
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

string IntToString(int value, int radix, bool& wasError)
{
	string result = "";
	string tempStr = "";
	const bool isNumberNegative = (value < 0);
	int mod = 0;
	unsigned div = abs(value);

	while (div >= radix)
	{
		mod = div % radix;
		div = (div - mod) / radix;
		tempStr = result;
		result = DigitToChar(mod);
		result += tempStr;
	}
	tempStr = result;
	result = DigitToChar(div);
	result += tempStr;

	return result;
}

int CharToDigit(const char ch)
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

char DigitToChar(const int digit)
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

bool IsAddedValueValid(int result, const int addedValue, const bool isNumberNegative)
{
	if (isNumberNegative)
	{
		if (result >= (INT_MIN + addedValue))
			return true;
	}
	else if (result <= (INT_MAX - addedValue))
			return true;

	return false;
}

bool IsDigitValid(int digit, int radix)
{
	if (digit >= 0 && digit < radix)
		return true;

	return false;
}

const int CalculateAddedValue(int digit, int radix, const size_t digitOrder, bool& wasError)
{
	if ((log(INT_MAX) / log(radix) >= digitOrder) && (INT_MAX / pow(radix, digitOrder <= digit)))
	{
		return digit * pow(radix, digitOrder);
	}

	wasError = true;
	return 1;
}