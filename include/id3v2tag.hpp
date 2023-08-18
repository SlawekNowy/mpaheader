#pragma once
#include "tag.hpp"

#include <cstdint>
class CID3V2Tag : public CTag
{
public:
	static CID3V2Tag *FindTag(CMPAStream *pStream, bool bAppended, std::uint32_t dwBegin, std::uint32_t dwEnd);
	~CID3V2Tag(void);

private:
	CID3V2Tag(CMPAStream *pStream, bool bAppended, std::uint32_t dwOffset);
	static std::uint32_t GetSynchsafeInteger(std::uint32_t dwValue);
};
