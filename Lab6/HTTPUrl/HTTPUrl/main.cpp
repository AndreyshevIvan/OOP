#include "stdafx.h"
#include "CHttpUrl.h"
#include <sstream>
#include <fstream>
#include <iostream>

int main()
{
	std::string url;
	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "Enter URL: ";
		std::cin >> url;
		if (std::cin.eof() || std::cin.fail())
		{
			break;
		}
		try
		{
			std::cout << Info(CHttpUrl(url));
		}
		catch(CUrlParsingError const& e)
		{
			std::cout << e.what();
		}
	}

	return 0;
}