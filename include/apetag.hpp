#ifndef APETAG_B6E0395E_A637_47A9_9C53_29718CA0F58B
#define APETAG_B6E0395E_A637_47A9_9C53_29718CA0F58B
#include "mpadefinitions.hpp"
#include "tag.hpp"
#include <cstdint>

class DLLMPAH CAPETag : public CTag
{
public:
	static CAPETag *FindTag(CMPAStream *pStream, bool bAppended, std::uint32_t dwBegin, std::uint32_t dwEnd);
	~CAPETag(void);

private:
	CAPETag(CMPAStream *pStream, bool bAppended, std::uint32_t dwOffset);
};

#endif /* APETAG_B6E0395E_A637_47A9_9C53_29718CA0F58B */
