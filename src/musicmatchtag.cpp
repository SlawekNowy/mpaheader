#include "pch.hpp"
#include <musicmatchtag.hpp>

#include <math.h> // for floor

// information from documentation "musicmatch.txt" in id3lib's doc folder

CMusicMatchTag *CMusicMatchTag::FindTag(CMPAStream *pStream, bool bAppended, std::uint32_t dwBegin, std::uint32_t dwEnd)
{
	// check for footer at the end of file
	std::uint32_t dwOffset = dwEnd - 48;
	CMPAByte *pBuffer = pStream->ReadBytes(32, dwOffset, true);
	if (memcmp("Brava Software Inc.             ", pBuffer, 32) == 0)
		return new CMusicMatchTag(pStream, dwOffset);
	return nullptr;
}

CMusicMatchTag::CMusicMatchTag(CMPAStream *pStream, std::uint32_t dwOffset) : CTag(pStream, "MM", true, dwOffset)
{
	// get version info (from footer)
	char szVersion[5];
	memcpy(szVersion, (char *)pStream->ReadBytes(4, dwOffset, false, true), 4);
	szVersion[4] = '\0';

	m_fVersion = (float)atof(szVersion);

	// data offsets in the 20 bytes before footer
	dwOffset -= 52;
	std::uint32_t dwImgExtOffset = pStream->ReadLEValue(4, dwOffset);
	dwOffset += 4;
	// std::uint32_t dwImgOffset = pStream->ReadLEValue(4, dwOffset);

	// next 4 bytes unused
	dwOffset += 4;
	std::uint32_t dwVersionOffset = pStream->ReadLEValue(4, dwOffset);

	dwOffset += 4;
	//	std::uint32_t dwMetadataOffset = pStream->ReadLEValue(4, dwOffset);

	std::uint32_t dwMetadataSize = 0;
	CMPAByte *pBuffer;

	if (m_fVersion > 3.00)
	{
		// three possible lengths for metadata section: 7936, 8004, and 8132 bytes
		std::uint32_t dwPossSizes[3] = {7936, 8004, 8132};
		std::uint32_t dwSyncOffset;

		for (int nIndex = 0; nIndex < 3; nIndex++)
		{
			// check for sync in version section
			dwSyncOffset = dwOffset - 20 - dwPossSizes[nIndex] - 256;
			pBuffer = pStream->ReadBytes(8, dwSyncOffset, false, true);

			if (memcmp("18273645", pBuffer, 8) == 0)
			{
				dwMetadataSize = dwPossSizes[nIndex];
				break;
			}
		}
	}
	else
		dwMetadataSize = 7868; // fixed size up to version 3

	if (dwMetadataSize == 0) // could not find correct metadata size
		throw nullptr;

	// total size = footer + data offsets + metadata + version + img (incl. unused)
	m_dwSize = 48 + 20 + dwMetadataSize + 256 + (dwVersionOffset - dwImgExtOffset);

	// is header there?
	dwOffset -= (m_dwSize - 48) + 256;
	pBuffer = pStream->ReadBytes(8, dwOffset, false);
	if (memcmp("18273645", pBuffer, 8) == 0)
	{
		m_dwSize += 256; // header exists
		m_dwOffset = dwOffset;
	}
	else
		m_dwOffset = dwOffset + 256;
}

CMusicMatchTag::~CMusicMatchTag(void)
{
}
