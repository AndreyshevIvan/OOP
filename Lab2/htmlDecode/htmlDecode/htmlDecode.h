#pragma once

#include <string>
#include <iostream>
#include <map>

std::string HtmlDecode(std::string const& html);
void Replace(std::string& currentStr, std::string const& searchStr, std::string const& replaceStr);