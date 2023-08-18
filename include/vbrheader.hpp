#ifndef VBRHEADER_AC48F8C4_4682_4F74_B67F_E6752D7F8A9B
#define VBRHEADER_AC48F8C4_4682_4F74_B67F_E6752D7F8A9B

#include <cstdint>
// class CMPAFrame must be included first and must be known here
class CMPAFrame;

class CVBRHeader
{
public:
	static CVBRHeader *FindHeader(const CMPAFrame *pFrame);
	virtual ~CVBRHeader(void);
	bool SeekPosition(float &fPercent, std::uint32_t &dwSeekPoint) const;

	std::uint32_t m_dwBytes;  // total number of bytes
	std::uint32_t m_dwFrames; // total number of frames

protected:
	CVBRHeader(CMPAStream *pStream, std::uint32_t dwOffset);

	static bool CheckID(CMPAStream *pStream, std::uint32_t dwOffset, char ch0, char ch1, char ch2, char ch3);
	virtual std::uint32_t SeekPosition(float &fPercent) const = 0;
	CMPAStream *m_pStream;

public:
	std::uint32_t m_dwOffset;
	std::uint32_t m_dwQuality;	 // quality (0..100)
	int *m_pnToc;				 // TOC points for seeking (must be freed)
	std::uint32_t m_dwTableSize; // size of table (number of entries)
};

#endif /* VBRHEADER_AC48F8C4_4682_4F74_B67F_E6752D7F8A9B */
