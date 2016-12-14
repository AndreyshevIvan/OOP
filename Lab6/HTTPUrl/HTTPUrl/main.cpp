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
		std::cin >> url;
		if (std::cin.eof() || std::cin.fail())
		{
			break;
		}
		std::cout << Info(CHttpUrl(url));
	}

	return 0;
}