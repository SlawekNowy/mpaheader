#pragma once
#include "mpaexception.hpp"

class CMPAEndOfFileException : public CMPAException
{
public:
	CMPAEndOfFileException(const char *szFile);
	virtual ~CMPAEndOfFileException(void);
};
