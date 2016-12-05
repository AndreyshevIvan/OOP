#include <iostream>
#include <string>
#include <cmath>

const int ARGUMENTS_COUNT = 4;
const int MIN_RADIX = 2;
const int MAX_RADIX = 36;

using namespace std;

bool IsRadixValid(int radix);

int StringToInt(string const& str, int radix, bool& wasError);
string IntToString(int value, int radix);
int CharToDigit(char ch);
char DigitToChar(int digit);
void AddOrderToNumber(int& number, int radix, int digit, bool& wasError, bool isNumberNegative);

int main(int argc, char * argv[])
{
	if (argc != ARGUMENTS_COUNT)
	{
		cout << "Invalid arguments count" "\n"
			"Usage: replace.exe <source notation> <destination notation> <value>" "\n";
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
		string valueInRadix = IntToString(valueInDec, destenationRadix);
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

		if (digit < 0 || digit >= radix)
		{
			cout << "Invalid character for this notation" "\n";
			wasError = true;
			return 1;
		}

		if (digitPos < str.length() - 1)
		{
			AddOrderToNumber(result, radix, digit, wasError, isNumberNegative);
		}
		else if (isNumberNegative && (INT_MIN + digit <= result))
		{
			result -= digit;
		}
		else if (!isNumberNegative && (INT_MAX - digit >= result))
		{
			result += digit;
		}
		else
		{
			wasError = true;
			cout << "Overflow when adding unit to nuber";
		}
	}

	return result;
}

string IntToString(int value, int radix)
{
	string result = "";
	const bool isNumberNegative = (value < 0);
	int mod = 0;
	unsigned div = abs(value);

	while (div >= static_cast<unsigned>(radix))
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
	else if (ch >= 'A' && ch <= 'Z')
	{
		result = (int)ch - 'A' + 10;
	}
	else if (ch >= 'a' && ch <= 'z')
	{
		result = (int)ch - 'a' + 10;
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
	else
	{
		result = char(digit + 'A' - 10);
	}

	return result;
}

void AddOrderToNumber(int& number, int radix, int digit, bool& wasError, bool isNumberNegative)
{
	if (isNumberNegative)
	{
		if ((std::numeric_limits<int>::min() + digit > number) || (std::numeric_limits<int>::min() / radix) > (number - digit))
		{
			wasError = true;
			cout << "Overflow when adding order" << "\n";
		}
		else
		{
			number = (number - digit) * radix;
		}
	}
	else
	{
		if (std::numeric_limits<int>::max() - digit < number || (std::numeric_limits<int>::max() / radix) < (number + digit))
		{
			wasError = true;
			cout << "Overflow when adding order" << "\n";
		}
		else
		{
			number = (number + digit) * radix;
		}
	}
}