
#include "pch.hpp"
#include "mpafilestream_posix.hpp"
#include <mpaexception.hpp>
#include <mpaendoffileexception.hpp>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// 1KB is inital buffersize
const std::uint32_t CMPAFileStreamPOSIX::INIT_BUFFERSIZE = 1024;

CMPAFileStreamPOSIX::CMPAFileStreamPOSIX(const char *szFilename) : CMPAStream(szFilename), m_dwOffset(0)
{
	// open with CreateFile (no limitation of 128byte filename length, like in mmioOpen)
	// m_hFile = ::CreateFile(szFilename, GENERIC_READ, FILE_SHARE_READ, NULL,
	//					   OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	// if (m_hFile == INVALID_FILE_VALUE)
	//{
	// throw error
	//	throw CMPAException(CMPAException::ErrOpenFile, szFilename, "CreateFile", true);
	//}
	m_fdFile = open(szFilename, O_RDONLY);
	if (m_fdFile == -1)
	{
		throw CMPAException(CMPAException::ErrOpenFile, szFilename, "open", true);
	}

	Init();
}

CMPAFileStreamPOSIX::CMPAFileStreamPOSIX(const char *szFilename, FD_INT hFile) : CMPAStream(szFilename), m_fdFile(hFile)
{
	Init();
}

void CMPAFileStreamPOSIX::Init()
{
	m_dwBufferSize = INIT_BUFFERSIZE;
	// fill buffer for first time
	m_pBuffer = new char[m_dwBufferSize];
	FillBuffer(m_dwOffset, m_dwBufferSize, false);
}

CMPAFileStreamPOSIX::~CMPAFileStreamPOSIX(void)
{
	if (m_pBuffer)
		delete[] m_pBuffer;

	// close file
	if (m_bMustReleaseFile)
		//::CloseHandle(m_hFile);
		close(m_fdFile);
}

// set file position
void CMPAFileStreamPOSIX::SetPosition(std::uint32_t dwOffset) const
{
	// convert from unsigned std::uint32_t to signed 64bit long
	// std::uint32_t result = ::SetFilePointer(m_fdFile, dwOffset, NULL, FILE_BEGIN);
	// if (result == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
	std::uint32_t result = lseek(m_fdFile, dwOffset, SEEK_SET);
	if (result == -1) // errno is never set to zero
	{
		// != NO_ERROR
		// throw error
		throw CMPAException(CMPAException::ErrSetPosition, m_szFile, "lseek", true);
	}
}

char *CMPAFileStreamPOSIX::ReadBytes(std::uint32_t dwSize, std::uint32_t &dwOffset, bool bMoveOffset, bool bReverse) const
{
	// enough bytes in buffer, otherwise read from file
	if (m_dwOffset > dwOffset || (((int)((m_dwOffset + m_dwBufferSize) - dwOffset)) < (int)dwSize))
	{
		if (!FillBuffer(dwOffset, dwSize, bReverse))
		{
			throw CMPAEndOfFileException(m_szFile);
		}
	}

	char *pBuffer = m_pBuffer + (dwOffset - m_dwOffset);
	if (bMoveOffset)
		dwOffset += dwSize;

	return pBuffer;
}

std::uint32_t CMPAFileStreamPOSIX::GetSize() const
{
	// std::uint32_t dwSize = ::GetFileSize(m_fdFile, NULL);
	// if (dwSize == INVALID_FILE_SIZE)
	struct stat *fdStat{0};
	std::uint32_t result = fstat(m_fdFile, fdStat);
	if (result == -1)
		throw CMPAException(CMPAException::ErrReadFile, m_szFile, "fstat", true);
	std::size_t dwSize = fdStat->st_size;
	return dwSize;
}

// fills internal buffer, returns false if EOF is reached, otherwise true. Throws exceptions
bool CMPAFileStreamPOSIX::FillBuffer(std::uint32_t dwOffset, std::uint32_t dwSize, bool bReverse) const
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
std::uint32_t CMPAFileStreamPOSIX::Read(void *pData, std::uint32_t dwOffset, std::uint32_t dwSize) const
{
	std::uint32_t dwBytesRead = 0;

	// set position first
	SetPosition(dwOffset);

	// if (!::ReadFile(m_fdFile, pData, dwSize, &dwBytesRead, NULL))
	dwBytesRead = read(m_fdFile, pData, dwSize);
	if (dwBytesRead == -1)
		throw CMPAException(CMPAException::ErrReadFile, m_szFile, "read", true);

	return dwBytesRead;
}