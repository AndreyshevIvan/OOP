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

	if (!CheckRadix(sourceRadix) && !CheckRadix(destenationRadix))
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

	cout << "---main---" << "\n";
	cout << "valueInDec : " << valueInDec << "\n";
	string valueInRadix = IntToString(valueInDec, destenationRadix, wasError);
	cout << "---main---" << "\n";
	cout << "finalValue : " << valueInRadix << "\n";

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
	if (radix < MIN_RADIX && radix > MAX_RADIX)
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
			return 1;
		}

		const size_t digitOrder = str.length() - digitPos - 1;
		const int addedValue = calculateAddedValue(digit, radix, digitOrder, wasError);

		if (wasError)
			return 1;

		cout << "addedValue : " << addedValue << "\n";

		if (!CheckAdding(result, addedValue, isNumberNegative))
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

string IntToString(int& value, int& radix, bool& wasError)
{
	cout << "---IntToString---" << "\n";
	string result = "";
	string tempStr = "";
	const bool isNumberNegative = (value < 0);
	int mod = 0;
	int div = value;
	if (isNumberNegative)
	{
		div = abs(div) - 1;
	}
	cout << "mod : " << mod << "\n";
	cout << "div : " << div << "\n";

	while (div >= radix)
	{
		mod = div % radix;
		div = (div - mod) / radix;
		tempStr = result;
		result = DigitToChar(mod);
		result += tempStr;
		cout << "mod : " << mod << "\n";
		cout << "div : " << div << "\n";
		cout << "result : " << result << "\n";
	}
	tempStr = result;
	if (isNumberNegative)
	{
		result = "-";
		result += DigitToChar(div);
		result += tempStr;
		result[result.length() - 1] = char(result[result.length() - 1] + 1);
		cout << "tempStr[tempStr.length()] + 1 : " << result[result.length() - 1] << "\n";
	}
	else
	{
		result = DigitToChar(div);
		result += tempStr;
	}
	cout << "result : " << result << "\n";
	

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

	cout << "---DigitToChar---" "\n";
	cout << "digit : " << digit << "\n";
	cout << "result : " << result << "\n";
	cout << "testStr : " << testStr << "\n";

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

	cout << "Overflow" "\n";
	return false;
}

bool CheckDigit(int& digit, int& radix)
{
	cout << "---CheckDigit---" "\n";
	cout << "radix : " << radix << "\n";
	cout << "digit : " << digit << "\n";
	if (digit >= 0 && digit < radix)
		return true;

	cout << "Invalid character for this notation" "\n";
	return false;
}

const int calculateAddedValue(int& digit, int& radix, const size_t& digitOrder, bool& wasError)
{
	cout << "---calculateAddedValue---" "\n";
	if ((log(INT_MAX) / log(radix) >= digitOrder) && (INT_MAX / pow(radix, digitOrder <= digit)))
	{
		cout << "pow : " << pow(radix, digitOrder) << "\n";
		cout << "digit : " << digit << "\n";
		return digit * pow(radix, digitOrder);
	}

	//cout << "Overflow" << "\n";
	//cout << "radix : " << radix << "\n";
	//cout << "digitOrder : " << digitOrder << "\n";
	//cout << "log(INT_MAX) / log(radix) : " << log(INT_MAX) / log(radix) << "\n";
	//cout << "INT_MAX / digit : " << INT_MAX / digit << "\n";
	wasError = true;
	return 1;
}