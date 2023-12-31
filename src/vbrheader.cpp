#include "pch.hpp"
#include <mpaframe.hpp> // also includes vbrheader.h

#include <xingheader.hpp>
#include <vbriheader.hpp>
#include <cassert>

// first test with this static method, if it does exist
CVBRHeader *CVBRHeader::FindHeader(const CMPAFrame *pFrame)
{
	assert(pFrame);
	CVBRHeader *pVBRHeader = NULL;

	pVBRHeader = CXINGHeader::FindHeader(pFrame);
	if (!pVBRHeader)
		pVBRHeader = CVBRIHeader::FindHeader(pFrame);

	return pVBRHeader;
}

CVBRHeader::CVBRHeader(CMPAStream *pStream, std::uint32_t dwOffset) : m_pStream(pStream), m_pnToc(NULL), m_dwOffset(dwOffset), m_dwFrames(0), m_dwBytes(0), m_dwQuality(0), m_dwTableSize(0)
{
}

bool CVBRHeader::CheckID(CMPAStream *pStream, std::uint32_t dwOffset, char ch0, char ch1, char ch2, char ch3)
{
	auto *pBuffer = pStream->ReadBytes(4, dwOffset, false);
	if (pBuffer[0] == ch0 && pBuffer[1] == ch1 && pBuffer[2] == ch2 && pBuffer[3] == ch3)
		return true;
	return false;
}

/*
// currently not used
bool CVBRHeader::ExtractLAMETag( std::uint32_t dwOffset )
{
	// LAME ID found?
	if( !CheckID( m_pMPAFile, dwOffset, 'L', 'A', 'M', 'E' ) && !CheckID( m_pMPAFile, dwOffset, 'G', 'O', 'G', 'O' ) )
		return false;

	return true;
}*/

CVBRHeader::~CVBRHeader(void)
{
	if (m_pnToc)
		delete[] m_pnToc;
}

// get byte position for percentage value (fPercent) of file
bool CVBRHeader::SeekPosition(float &fPercent, std::uint32_t &dwSeekPoint) const
{
	if (!m_pnToc || m_dwBytes == 0)
		return false;

	// check range of fPercent
	if (fPercent < 0.0f)
		fPercent = 0.0f;
	if (fPercent > 99.0f)
		fPercent = 99.0f;

	dwSeekPoint = SeekPosition(fPercent);
	return true;
}
