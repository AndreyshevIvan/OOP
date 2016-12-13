#include "stdafx.h"
#include "CHttpUrl.h"
#include <sstream>

int main()
{
	std::string strToParse;
	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cin >> strToParse;
		try
		{
			CHttpUrl parsedUrl(strToParse);
			std::cout << parsedUrl.ToString();
		}
		catch (CUrlParsingError const& e)
		{
			std::cout << e.what();
		}
	}

	return 0;
}