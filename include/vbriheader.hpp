#ifndef VBRIHEADER_EE1B19A6_BFD4_4317_BA8B_906606EF4301
#define VBRIHEADER_EE1B19A6_BFD4_4317_BA8B_906606EF4301
#include "mpaframe.hpp"
#include "vbrheader.hpp"

class DLLMPAH CVBRIHeader : public CVBRHeader
{
public:
	static CVBRIHeader *FindHeader(const CMPAFrame *pFrame);

	CVBRIHeader(const CMPAFrame *pFrame, std::uint32_t dwOffset);
	virtual ~CVBRIHeader(void);

	virtual std::uint32_t SeekPosition(float &fPercent) const;
	std::uint32_t SeekPositionByTime(float fEntryTimeMS) const;

	// these values exist only in VBRI headers
	float m_fDelay;
	std::uint32_t m_dwTableScale; // for seeking
	std::uint32_t m_dwBytesPerEntry;
	std::uint32_t m_dwFramesPerEntry;
	std::uint32_t m_dwVersion;

private:
	std::uint32_t m_dwLengthSec;
};

#endif /* VBRIHEADER_EE1B19A6_BFD4_4317_BA8B_906606EF4301 */
