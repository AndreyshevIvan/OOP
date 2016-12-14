#include "stdafx.h"
#include "CHttpUrl.h"
#include <sstream>

int main()
{
	try
	{
		std::string strToParse = "http://vk.com/document";
		CHttpUrl parsedUrl(strToParse);
	}
	catch (CUrlParsingError const& e)
	{
		std::cout << e.what();
	}

	return 0;
}