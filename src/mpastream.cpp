#include "stdafx.h"

#include "mpastream.h"
#include "mpaexception.h"

#include <windows.h>	// for CreateFile, CloseHandle, ...

// constructor
CMPAStream::CMPAStream(LPCTSTR szFilename)
{
	// save filename
	m_szFile = _tcsdup(szFilename);
}

CMPAStream::~CMPAStream(void)
{
	free(m_szFile);
}

std::uint32_t CMPAStream::ReadLEValue(std::uint32_t dwNumBytes, std::uint32_t& dwOffset, bool bMoveOffset) const
{
	_ASSERTE(dwNumBytes > 0);
	_ASSERTE(dwNumBytes <= 4);	// max 4 byte

	BYTE* pBuffer = ReadBytes(dwNumBytes, dwOffset, bMoveOffset);

	std::uint32_t dwResult = 0;

	// little endian extract (least significant byte first) (will work on little and big-endian computers)
	std::uint32_t dwNumByteShifts = 0;

	for (std::uint32_t n=0; n < dwNumBytes; n++)
	{
		dwResult |= pBuffer[n] << 8 * dwNumByteShifts++;                                                          
	}
	
	return dwResult;
}

// convert from big endian to native format (Intel=little endian) and return as std::uint32_t (32bit)
std::uint32_t CMPAStream::ReadBEValue(std::uint32_t dwNumBytes, std::uint32_t& dwOffset,  bool bMoveOffset) const
{	
	_ASSERTE(dwNumBytes > 0);
	_ASSERTE(dwNumBytes <= 4);	// max 4 byte

	BYTE* pBuffer = ReadBytes(dwNumBytes, dwOffset, bMoveOffset);

	std::uint32_t dwResult = 0;

	// big endian extract (most significant byte first) (will work on little and big-endian computers)
	std::uint32_t dwNumByteShifts = dwNumBytes - 1;

	for (std::uint32_t n=0; n < dwNumBytes; n++)
	{
		dwResult |= pBuffer[n] << 8*dwNumByteShifts--; // the bit shift will do the correct byte order for you                                                           
	}
	
	return dwResult;
}