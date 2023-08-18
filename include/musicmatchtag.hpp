#pragma once
#include "tag.hpp"

class CMusicMatchTag : public CTag
{
public:
	static CMusicMatchTag *FindTag(CMPAStream *pStream, bool bAppended, std::uint32_t dwBegin, std::uint32_t dwEnd);
	~CMusicMatchTag(void);

private:
	CMusicMatchTag(CMPAStream *pStream, std::uint32_t dwOffset);
};
