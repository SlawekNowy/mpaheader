#include "pch.hpp"
#include <apetag.hpp>
#include <cstring>
CAPETag *CAPETag::FindTag(CMPAStream *pStream, bool bAppended, std::uint32_t dwBegin, std::uint32_t dwEnd)
{
	std::uint32_t dwOffset;

	if (!bAppended)
	{
		// stands at the beginning of file (complete header is 32 bytes)
		dwOffset = dwBegin;
	}
	else
	{
		// stands at the end of the file (complete footer is 32 bytes)
		dwOffset = dwEnd - 32;
	}
	CMPAByte *pBuffer = pStream->ReadBytes(8, dwOffset, false);

	if (std::memcmp("APETAGEX", pBuffer, 8) == 0)
		return new CAPETag(pStream, bAppended, dwOffset);
	return nullptr;
}

CAPETag::CAPETag(CMPAStream *pStream, bool bAppended, std::uint32_t dwOffset) : CTag(pStream, "APE", bAppended, dwOffset)
{
	dwOffset += 8;
	std::uint32_t dwVersion = pStream->ReadLEValue(4, dwOffset);

	// first byte is version number
	m_fVersion = dwVersion / 1000.0f;

	// get size
	m_dwSize = pStream->ReadLEValue(4, dwOffset);

	/*std::uint32_t dwNumItems = */ pStream->ReadLEValue(4, dwOffset);

	// only valid for version 2
	std::uint32_t dwFlags = pStream->ReadLEValue(4, dwOffset);
	bool bHeader, bFooter;
	if (m_fVersion > 1.0f)
	{
		bHeader = dwFlags >> 31 & 0x1;
		bFooter = dwFlags >> 30 & 0x1;
	}
	else
	{
		bHeader = false;
		bFooter = true;
	}

	if (bHeader)
		m_dwSize += 32; // add header

	if (bAppended)
		m_dwOffset -= (m_dwSize - 32);
}

CAPETag::~CAPETag(void)
{
}
