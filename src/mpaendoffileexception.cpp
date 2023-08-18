#include "pch.hpp"
#include <mpaendoffileexception.hpp>

CMPAEndOfFileException::CMPAEndOfFileException(const char *szFile) : CMPAException(CMPAException::EndOfFile, szFile)
{
}

CMPAEndOfFileException::~CMPAEndOfFileException(void)
{
}
