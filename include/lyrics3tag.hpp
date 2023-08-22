#ifndef LYRICS3TAG_E2CD8E1D_634D_4982_BED5_E184A76A238D
#define LYRICS3TAG_E2CD8E1D_634D_4982_BED5_E184A76A238D
#include "mpadefinitions.hpp"
#include "tag.hpp"

#include <cstdint>
class DLLMPAH CLyrics3Tag : public CTag
{
public:
	static CLyrics3Tag *FindTag(CMPAStream *pStream, bool bAppended, std::uint32_t dwBegin, std::uint32_t dwEnd);
	~CLyrics3Tag(void);

private:
	CLyrics3Tag(CMPAStream *pStream, std::uint32_t dwOffset, bool bVersion2);
};

#endif /* LYRICS3TAG_E2CD8E1D_634D_4982_BED5_E184A76A238D */
