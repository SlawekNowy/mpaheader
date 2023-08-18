#ifndef MUSICMATCHTAG_A8BF2AE6_A3A9_46D5_B3F0_5119A971132A
#define MUSICMATCHTAG_A8BF2AE6_A3A9_46D5_B3F0_5119A971132A
#include "tag.hpp"

#include <cstdint>
class CMusicMatchTag : public CTag
{
public:
	static CMusicMatchTag *FindTag(CMPAStream *pStream, bool bAppended, std::uint32_t dwBegin, std::uint32_t dwEnd);
	~CMusicMatchTag(void);

private:
	CMusicMatchTag(CMPAStream *pStream, std::uint32_t dwOffset);
};

#endif /* MUSICMATCHTAG_A8BF2AE6_A3A9_46D5_B3F0_5119A971132A */
