#include "stdafx.h"
#include "CHttpUrl.h"
#include <sstream>

int main()
{
	std::string strToParse;

	while (!std::cin.eof() && !std::cin.fail())
	{
		try
		{
			std::cin >> strToParse;
			CHttpUrl parsedUrl(strToParse);
		}
		catch (CUrlParsingError const& e)
		{
			std::cout << e.what();
		}
	}

	return 0;
}