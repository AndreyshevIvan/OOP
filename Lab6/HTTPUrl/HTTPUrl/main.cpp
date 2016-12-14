#include "stdafx.h"
#include "CHttpUrl.h"
#include <sstream>
#include <fstream>

int main()
{
	std::string url = "https://site.com:0/documentation";
	std::cout << CHttpUrl(url).GetStringURL();
	return 0;
}