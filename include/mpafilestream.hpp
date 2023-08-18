#pragma once
#include "mpastream.hpp"

class CMPAFileStream : public CMPAStream
{
public:
	CMPAFileStream(LPCTSTR szFilename);
	CMPAFileStream(LPCTSTR szFilename, HANDLE hFile);
	virtual ~CMPAFileStream(void);

private:
	static const std::uint32_t INIT_BUFFERSIZE;
	HANDLE m_hFile;
	bool m_bMustReleaseFile;

	// concerning read-buffer
	mutable BYTE *m_pBuffer;
	mutable std::uint32_t m_dwOffset; // offset (beginning if m_pBuffer)
	mutable std::uint32_t m_dwBufferSize;

	void Init();
	std::uint32_t Read(LPVOID pData, std::uint32_t dwOffset, std::uint32_t dwSize) const;
	bool FillBuffer(std::uint32_t dwOffset, std::uint32_t dwSize, bool bReverse) const;
	void SetPosition(std::uint32_t dwOffset) const;

protected:
	// methods for file access (must be implemented by all derived classes)

	virtual BYTE *ReadBytes(std::uint32_t dwSize, std::uint32_t &dwOffset, bool bMoveOffset = true, bool bReverse = false) const;
	virtual std::uint32_t GetSize() const;
};
