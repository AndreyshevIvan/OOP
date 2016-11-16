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
bool CheckAdding(int& result, const int& addedValue, const bool& isNumberNegative);
bool CheckDigit(int& digit, int& radix);

int StringToInt(const string& str, int radix, bool& wasError);
string IntToString(int& value, int& radix, bool& wasError);
int CharToDigit(const char& ch);
char DigitToChar(const int& digit);
const int calculateAddedValue(int& digit, int& radix, const size_t& digitOrder, bool& wasError);

int main(int argc, char * argv[])
{
	bool wasError = false;

	if (!CheckArgumentsCount(argc))
		return 1;

	int sourceRadix = stoi(argv[1]);
	int destenationRadix = stoi(argv[2]);

	if (!CheckRadix(sourceRadix) || !CheckRadix(destenationRadix))
		return 1;

	const string value = argv[3];

	if (sourceRadix == destenationRadix)
	{
		cout << value << "\n";
		return 1;
	}

	int valueInDec = StringToInt(value, sourceRadix, wasError);
	if (wasError)
		return 1;

	bool isValueNegative = (valueInDec < 0);

	string valueInRadix = IntToString(valueInDec, destenationRadix, wasError);
	if (isValueNegative)
	{
		string tempStr = valueInRadix;
		valueInRadix = "-";
		valueInRadix += tempStr;
	}

	cout << valueInRadix << "\n";

    return 0;
}

bool CheckArgumentsCount(int& argc)
{
	if (argc != ARGUMENTS_COUNT)
	{
		cout << "Invalid arguments count" "\n"
			<< "Usage: replace.exe <source notation> <destenation notation> <value>" "\n";
		return false;
	}

	return true;
}

bool CheckRadix(int& radix)
{
	if (radix < MIN_RADIX || radix > MAX_RADIX)
	{
		cout << "Invalid notation value" "\n"
			<< "Radix should be in the range [2; 36]" "\n";
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
			return 1;
		}

		const size_t digitOrder = str.length() - digitPos - 1;
		const int addedValue = calculateAddedValue(digit, radix, digitOrder, wasError);

		if (wasError)
			return 1;

		if (!CheckAdding(result, addedValue, isNumberNegative))
		{
			wasError = true;
			return 1;
		}

		if (isNumberNegative)
		{
			result -= addedValue;
		}
		else
		{
			result += addedValue;
		}
	}

	return result;
}

string IntToString(int& value, int& radix, bool& wasError)
{
	string result = "";
	string tempStr = "";
	const bool isNumberNegative = (value < 0);
	int mod = 0;
	unsigned int div = abs(value);

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

int CharToDigit(const char& ch)
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

char DigitToChar(const int& digit)
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

bool CheckAdding(int& result, const int& addedValue, const bool& isNumberNegative)
{
	if (isNumberNegative)
	{
		if (result >= (INT_MIN + addedValue))
			return true;
	}
	else if (result <= (INT_MAX - addedValue))
			return true;

	cout << "Error: overflow" "\n";
	return false;
}

bool CheckDigit(int& digit, int& radix)
{
	if (digit >= 0 && digit < radix)
		return true;

	cout << "Invalid character for this notation" "\n";
	return false;
}

const int calculateAddedValue(int& digit, int& radix, const size_t& digitOrder, bool& wasError)
{
	if ((log(INT_MAX) / log(radix) >= digitOrder) && (INT_MAX / pow(radix, digitOrder <= digit)))
		return int(digit * pow(radix, digitOrder));

	cout << "Error: overflow" "\n";
	wasError = true;
	return 1;
}