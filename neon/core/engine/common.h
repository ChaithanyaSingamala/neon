#pragma once

#include <string>
#include <assert.h>

class Common
{
public:
	Common();
	virtual ~Common();
};

#if 0
void ASSERT(char *str);
#else
#define ASSERT(str)		assert(0 && str)
#endif
std::string GetFromCommandOption(std::string _for_value);
std::string ReadFromFile(std::string _filename);

