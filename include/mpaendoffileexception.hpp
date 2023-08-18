#ifndef MPAENDOFFILEEXCEPTION_A3F76427_D5AD_4274_A26D_5ACCBF6DB173
#define MPAENDOFFILEEXCEPTION_A3F76427_D5AD_4274_A26D_5ACCBF6DB173
#include "mpaexception.hpp"

class CMPAEndOfFileException : public CMPAException
{
public:
	CMPAEndOfFileException(const char *szFile);
	virtual ~CMPAEndOfFileException(void);
};

#endif /* MPAENDOFFILEEXCEPTION_A3F76427_D5AD_4274_A26D_5ACCBF6DB173 */
