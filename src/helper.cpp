#include "helper.hpp"
#include <cstring>
namespace MPAHeader
{
    char *strdup(const char *origStr)
    {
        int strLength = std::strlen(origStr);
        char *destStr = new char[strLength + 1];
        std::strcpy(destStr, origStr);
        return destStr;
    }
}