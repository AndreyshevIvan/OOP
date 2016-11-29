#include "stdafx.h"
#include "htmlDecode.h"

using namespace std;

int main()
{
	string htmlString;
	cout << "Enter html strings to decode. Enter EOF for exit." << "\n";
	while (getline(cin, htmlString))
	{
		htmlString = HtmlDecode(htmlString);
		cout << htmlString << "\n";
	}

	return 0;
}