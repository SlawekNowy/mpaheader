#pragma once
#include "mpaexception.hpp"

class CMPAEndOfFileException : public CMPAException
{
public:
	CMPAEndOfFileException(LPCTSTR szFile);
	virtual ~CMPAEndOfFileException(void);
};
