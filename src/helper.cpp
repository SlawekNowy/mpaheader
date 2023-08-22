#include "helper.hpp"
#include <cstring>

char *MPAHelper::cloneCString(const char *origStr)
{
	if (origStr == nullptr)
		return nullptr;

	size_t len = std::strlen(origStr) + 1;
	char* newStr = static_cast<char*>(std::malloc(len));

	if (newStr != nullptr)
		std::memcpy(newStr, origStr, len);

	return newStr;
}
