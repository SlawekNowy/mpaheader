#include "mpafilestream.hpp"
#include "mpaexception.hpp"
#include "mpaendoffileexception.hpp"

// 1KB is inital buffersize
const std::uint32_t CMPAFileStream::INIT_BUFFERSIZE = 1024;	

CMPAFileStream::CMPAFileStream(std::unique_ptr<CMPAIFile> file) :
	CMPAStream(""), m_dwOffset(0), m_file{std::move(file)}
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
		m_file = nullptr;
}

// set file position
void CMPAFileStream::SetPosition(std::uint32_t dwOffset) const
{
	// convert from unsigned std::uint32_t to signed 64bit long
	m_file->Seek(dwOffset);
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
	return m_file->GetSize();
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
std::uint32_t CMPAFileStream::Read(void *pData, std::uint32_t dwOffset, std::uint32_t dwSize) const
{
	std::uint32_t dwBytesRead = 0;
	
	// set position first
	SetPosition(dwOffset);

	dwBytesRead = m_file->Read(pData, dwSize);
	if (dwBytesRead != dwSize)
		throw CMPAException(CMPAException::ErrReadFile, m_szFile, "ReadFile", true);
	
	return dwBytesRead;
}