#pragma once

#include <string>

class Common
{
public:
	Common();
	virtual ~Common();
};


void ASSERT(char *str);
std::string GetFromCommandOption(std::string _for_value);
std::string ReadFromFile(std::string _filename);