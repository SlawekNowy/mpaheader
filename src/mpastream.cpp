#include "pch.hpp"

#include "mpastream.hpp"
#include "mpaexception.hpp"

#include <cstdio>
#include <cstring>
#include <cassert>

// #include <windows.h>	// for CreateFile, CloseHandle, ...

// constructor
CMPAStream::CMPAStream(const char *szFilename)
{
	// save filename
	// m_szFile = std::strdup(szFilename);
	int strLength = std::strlen(szFilename);
	m_szFile = new char[strLength + 1];
	std::strcpy(m_szFile, szFilename);
}

CMPAStream::~CMPAStream(void)
{
	delete[] m_szFile;
}

std::uint32_t CMPAStream::ReadLEValue(std::uint32_t dwNumBytes, std::uint32_t &dwOffset, bool bMoveOffset) const
{
	assert(dwNumBytes > 0);
	assert(dwNumBytes <= 4); // max 4 byte

	CMPAByte *pBuffer = ReadBytes(dwNumBytes, dwOffset, bMoveOffset);

	std::uint32_t dwResult = 0;

	// little endian extract (least significant byte first) (will work on little and big-endian computers)
	std::uint32_t dwNumByteShifts = 0;

	for (std::uint32_t n = 0; n < dwNumBytes; n++)
	{
		dwResult |= pBuffer[n] << 8 * dwNumByteShifts++;
	}

	return dwResult;
}

// convert from big endian to native format (Intel=little endian) and return as std::uint32_t (32bit)
std::uint32_t CMPAStream::ReadBEValue(std::uint32_t dwNumBytes, std::uint32_t &dwOffset, bool bMoveOffset) const
{
	assert(dwNumBytes > 0);
	assert(dwNumBytes <= 4); // max 4 byte

	CMPAByte *pBuffer = ReadBytes(dwNumBytes, dwOffset, bMoveOffset);

	std::uint32_t dwResult = 0;

	// big endian extract (most significant byte first) (will work on little and big-endian computers)
	std::uint32_t dwNumByteShifts = dwNumBytes - 1;

	for (std::uint32_t n = 0; n < dwNumBytes; n++)
	{
		dwResult |= pBuffer[n] << 8 * dwNumByteShifts--; // the bit shift will do the correct byte order for you
	}

	return dwResult;
}