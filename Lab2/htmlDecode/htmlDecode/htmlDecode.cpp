#include "stdafx.h"
#include "htmlDecode.h"

using namespace std;

string HtmlDecode(string const& html)
{
	string newHtmlStr = html;
	map <string, string> decodeMap = { 
		{ "&quot;", "\"" },
		{ "&apos;", "'" },
		{ "&lt;", "<" },
		{ "&gt;", ">" },
		{ "&amp;", "&" }
	};

	for (auto i = decodeMap.begin(); i != decodeMap.end(); i++)
	{
		Replace(newHtmlStr, i->first, i->second);
	}

	return newHtmlStr;
}

void Replace(string& currentStr, string const& searchStr, string const& replaceStr)
{
	size_t copiedPos = 0;
	size_t searchStrPos = currentStr.find(searchStr, 0);

	string newStr;

	while (copiedPos != currentStr.length() || searchStrPos != string::npos)
	{
		if (copiedPos != searchStrPos)
		{
			newStr += currentStr[copiedPos];
			++copiedPos;
		}
		else
		{
			newStr += replaceStr;
			copiedPos += searchStr.length();
			searchStrPos = currentStr.find(searchStr, copiedPos);
		}
	}
	currentStr.swap(newStr);
}