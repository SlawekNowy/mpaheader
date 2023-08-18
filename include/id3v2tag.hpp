#ifndef ID3V2TAG_D153286B_E881_43A3_BD5E_3D66AECBFFDA
#define ID3V2TAG_D153286B_E881_43A3_BD5E_3D66AECBFFDA
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

#endif /* ID3V2TAG_D153286B_E881_43A3_BD5E_3D66AECBFFDA */
