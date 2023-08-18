#ifndef ID3V1TAG_F66ACE33_8231_4ADE_B5D1_3F95E823D428
#define ID3V1TAG_F66ACE33_8231_4ADE_B5D1_3F95E823D428
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

#endif /* ID3V1TAG_F66ACE33_8231_4ADE_B5D1_3F95E823D428 */
