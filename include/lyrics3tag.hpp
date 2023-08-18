#pragma once
#include "tag.hpp"

class CLyrics3Tag : public CTag
{
public:
	static CLyrics3Tag *FindTag(CMPAStream *pStream, bool bAppended, std::uint32_t dwBegin, std::uint32_t dwEnd);
	~CLyrics3Tag(void);

private:
	CLyrics3Tag(CMPAStream *pStream, std::uint32_t dwOffset, bool bVersion2);
};
