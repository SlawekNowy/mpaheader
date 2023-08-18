#pragma once
#include "tag.hpp"

#include <cstdint>

class CID3V1Tag : public CTag
{
public:
	static CID3V1Tag *FindTag(CMPAStream *pStream, bool bAppended, std::uint32_t dwBegin, std::uint32_t dwEnd);
	~CID3V1Tag(void);

private:
	CID3V1Tag(CMPAStream *pStream, std::uint32_t dwOffset);
};
