#include "StdAfx.h"
#include "MPAFileStream.h"
#include "mpaexception.h"
#include "mpaendoffileexception.h"

// 1KB is inital buffersize
const std::uint32_t CMPAFileStream::INIT_BUFFERSIZE = 1024;	

CMPAFileStream::CMPAFileStream(const char* szFilename) :
	CMPAStream(szFilename), m_dwOffset(0)
{
	// open with CreateFile (no limitation of 128byte filename length, like in mmioOpen)
	m_hFile = ::CreateFile(szFilename, GENERIC_READ, FILE_SHARE_READ, NULL, 
										    OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (m_hFile == INVALID_FILE*_VALUE)
	{
		// throw error
		throw CMPAException(CMPAException::ErrOpenFile, szFilename, _T("CreateFile"), true);
	}
	Init();
}

CMPAFileStream::CMPAFileStream(const char* szFilename, FILE* hFile) :
	CMPAStream(szFilename), m_hFile(hFile)
{
	Init();
}


void CMPAFileStream::Init() 
{
	m_dwBufferSize = INIT_BUFFERSIZE;
	// fill buffer for first time
	m_pBuffer = new char[m_dwBufferSize];
	FillBuffer(m_dwOffset, m_dwBufferSize, false);
}

CMPAFileStream::~CMPAFileStream(void)
{
	if (m_pBuffer)
		delete[] m_pBuffer;
	
	// close file
	if (m_bMustReleaseFile)
		::CloseHandle(m_hFile);	
}

// VC++6 doesn't contain this definition
#ifndef INVALID_SET_FILE_POINTER
#define INVALID_SET_FILE_POINTER ((std::uint32_t)-1)
#endif

// set file position
void CMPAFileStream::SetPosition(std::uint32_t dwOffset) const
{
	// convert from unsigned std::uint32_t to signed 64bit long
	std::uint32_t result = ::SetFilePointer(m_hFile, dwOffset, NULL, FILE_BEGIN); 
	if (result == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
	{ 
		// != NO_ERROR
		// throw error
		throw CMPAException(CMPAException::ErrSetPosition, m_szFile, _T("SetFilePointer"), true);
	}
}


char* CMPAFileStream::ReadBytes(std::uint32_t dwSize, std::uint32_t& dwOffset, bool bMoveOffset, bool bReverse) const
{
	// enough bytes in buffer, otherwise read from file
	if (m_dwOffset > dwOffset || ( ((int)((m_dwOffset + m_dwBufferSize) - dwOffset)) < (int)dwSize))
	{
		if (!FillBuffer(dwOffset, dwSize, bReverse)) 
		{
			throw CMPAEndOfFileException(m_szFile);
		}
	}

	char* pBuffer = m_pBuffer + (dwOffset-m_dwOffset);
	if (bMoveOffset)
		dwOffset += dwSize;
	
	return pBuffer;
}

std::uint32_t CMPAFileStream::GetSize() const
{
	std::uint32_t dwSize = ::GetFileSize(m_hFile, NULL);
	if (dwSize == INVALID_FILE_SIZE)
		throw CMPAException(CMPAException::ErrReadFile, m_szFile, _T("GetFileSize"), true);
	return dwSize;
}

// fills internal buffer, returns false if EOF is reached, otherwise true. Throws exceptions
bool CMPAFileStream::FillBuffer(std::uint32_t dwOffset, std::uint32_t dwSize, bool bReverse) const
{
	// calc new buffer size
	if (dwSize > m_dwBufferSize)
	{
        m_dwBufferSize = dwSize;
		
		// release old buffer 
		delete[] m_pBuffer;

		// reserve new buffer
		m_pBuffer = new char[m_dwBufferSize];
	}	

	if (bReverse)
	{
		if (dwOffset + dwSize < m_dwBufferSize)
			dwOffset = 0;
		else
			dwOffset = dwOffset + dwSize - m_dwBufferSize;
	}

	// read <m_dwBufferSize> bytes from offset <dwOffset>
	m_dwBufferSize = Read(m_pBuffer, dwOffset, m_dwBufferSize);

	// set new offset
	m_dwOffset = dwOffset;

	if (m_dwBufferSize < dwSize)
		return false;

	return true;
}

// read from file, return number of bytes read
std::uint32_t CMPAFileStream::Read(void* pData, std::uint32_t dwOffset, std::uint32_t dwSize) const
{
	std::uint32_t dwBytesRead = 0;
	
	// set position first
	SetPosition(dwOffset);

	if (!::ReadFile(m_hFile, pData, dwSize, &dwBytesRead, NULL))
		throw CMPAException(CMPAException::ErrReadFile, m_szFile, _T("ReadFile"), true);
	
	return dwBytesRead;
}