#pragma once
#include "mpastream.hpp"

#include <cstdint>
class CMPAFileStream : public CMPAStream
{
public:
	CMPAFileStream(const char *szFilename);
	CMPAFileStream(const char *szFilename, FILE *hFile);
	virtual ~CMPAFileStream(void);

private:
	static const std::uint32_t INIT_BUFFERSIZE;
	FILE *m_hFile;
	bool m_bMustReleaseFile;

	// concerning read-buffer
	mutable char *m_pBuffer;
	mutable std::uint32_t m_dwOffset; // offset (beginning if m_pBuffer)
	mutable std::uint32_t m_dwBufferSize;

	void Init();
	std::uint32_t Read(void *pData, std::uint32_t dwOffset, std::uint32_t dwSize) const;
	bool FillBuffer(std::uint32_t dwOffset, std::uint32_t dwSize, bool bReverse) const;
	void SetPosition(std::uint32_t dwOffset) const;

protected:
	// methods for file access (must be implemented by all derived classes)

	virtual char *ReadBytes(std::uint32_t dwSize, std::uint32_t &dwOffset, bool bMoveOffset = true, bool bReverse = false) const;
	virtual std::uint32_t GetSize() const;
};
