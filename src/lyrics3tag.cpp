#include "pch.hpp"
#include "lyrics3tag.hpp"
#include "mpaexception.hpp"

#include <cstring>
#include <cstdlib>

CLyrics3Tag *CLyrics3Tag::FindTag(CMPAStream *pStream, bool bAppended, std::uint32_t dwBegin, std::uint32_t dwEnd)
{
	// stands at the end of file
	std::uint32_t dwOffset = dwEnd - 9;
	CMPAByte *pBuffer = pStream->ReadBytes(9, dwOffset, false, true);

	// is it Lyrics 2 Tag
	if (std::memcmp("LYRICS200", pBuffer, 9) == 0)
		return new CLyrics3Tag(pStream, dwOffset, true);
	else if (std::memcmp("LYRICSEND", pBuffer, 9) == 0)
		return new CLyrics3Tag(pStream, dwOffset, false);

	return nullptr;
}

CLyrics3Tag::CLyrics3Tag(CMPAStream *pStream, std::uint32_t dwOffset, bool bVersion2) : CTag(pStream, "Lyrics3", true, dwOffset)
{
	CMPAByte *pBuffer;
	if (bVersion2)
	{
		SetVersion(2);

		// look for size of tag (stands before dwOffset)
		dwOffset -= 6;
		pBuffer = pStream->ReadBytes(6, dwOffset, false);

		// add null termination
		char szSize[7];
		memcpy(szSize, pBuffer, 6);
		szSize[6] = '\0';

		// convert string to integer
		m_dwSize = std::atoi(szSize);
		m_dwOffset = dwOffset - m_dwSize;
		m_dwSize += 6 + 9; // size must include size info and end string
	}
	else
	{
		SetVersion(1);

		// seek back 5100 bytes and look for LYRICSBEGIN
		m_dwOffset -= 5100;
		pBuffer = pStream->ReadBytes(11, m_dwOffset, false);

		while (std::memcmp("LYRICSBEGIN", pBuffer, 11) != 0)
		{
			if (dwOffset >= m_dwOffset)
				throw CMPAException(CMPAException::CorruptLyricsTag);
		}
		m_dwSize = (dwOffset - m_dwOffset) + 9;
	}
}

CLyrics3Tag::~CLyrics3Tag(void)
{
}
