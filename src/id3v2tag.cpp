#include "pch.hpp"
#include <id3v2tag.hpp>
#include <cstring>
CID3V2Tag *CID3V2Tag::FindTag(CMPAStream *pStream, bool bAppended, std::uint32_t dwBegin, std::uint32_t dwEnd)
{
	char *szID;
	std::uint32_t dwOffset;

	if (!bAppended)
	{
		// stands at the beginning of file (complete header is 10 bytes)
		dwOffset = dwBegin;
		szID = "ID3";
	}
	else
	{
		// stands at the end of the file (complete footer is 10 bytes)
		dwOffset = dwEnd - 10;
		szID = "3DI";
	}
	CMPAByte *pBuffer = pStream->ReadBytes(10, dwOffset, false);

	if (std::memcmp(szID, pBuffer, 3) == 0)
		return new CID3V2Tag(pStream, bAppended, dwOffset);
	return nullptr;
}

CID3V2Tag::CID3V2Tag(CMPAStream *pStream, bool bAppended, std::uint32_t dwOffset) : CTag(pStream, "ID3", false, dwOffset)
{
	dwOffset += 3;

	// read out version info
	CMPAByte *pBuffer = m_pStream->ReadBytes(3, dwOffset);
	SetVersion(2, pBuffer[0], pBuffer[1]);
	CMPAByte bFlags = pBuffer[3];
	/*m_bUnsynchronization = (bFlags & 0x80)?true:false;	// bit 7
	m_bExtHeader = (bFlags & 0x40)?true:false;			// bit 6
	m_bExperimental = (bFlags & 0x20)?true:false;		// bit 5*/
	bool bFooter = (bFlags & 0x10) ? true : false; // bit 4

	// convert synchsafe integer
	m_dwSize = GetSynchsafeInteger(m_pStream->ReadBEValue(4, dwOffset)) + (bFooter ? 20 : 10);

	// for appended tag: calculate new offset
	if (bAppended)
		m_dwOffset -= m_dwSize - 10;
}

// return for each byte only lowest 7 bits (highest bit always zero)
std::uint32_t CID3V2Tag::GetSynchsafeInteger(std::uint32_t dwValue)
{
	// masks first 7 bits
	const std::uint32_t dwMask = 0x7F000000;
	std::uint32_t dwReturn = 0;
	for (int n = 0; n < sizeof(std::uint32_t); n++)
	{
		dwReturn = (dwReturn << 7) | ((dwValue & dwMask) >> 24);
		dwValue <<= 8;
	}
	return dwReturn;
}

CID3V2Tag::~CID3V2Tag(void)
{
}
