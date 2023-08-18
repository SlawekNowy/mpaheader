#include "StdAfx.h"
#include "MPAEndOfFileException.h"

CMPAEndOfFileException::CMPAEndOfFileException(const char* szFile) :
	CMPAException(CMPAException::EndOfFile, szFile)
{
}

CMPAEndOfFileException::~CMPAEndOfFileException(void)
{
}
