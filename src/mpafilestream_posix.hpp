#ifndef MPAFILESTREAM_POSIX_C66170D4_7C80_47A6_BDD6_68CC4E90D77F
#define MPAFILESTREAM_POSIX_C66170D4_7C80_47A6_BDD6_68CC4E90D77F
#include <mpastream.hpp>

#include <cstdint>

typedef int FD_INT;

class CMPAFileStreamPOSIX : public CMPAStream
{
public:
	CMPAFileStreamPOSIX(const char *szFilename);
	CMPAFileStreamPOSIX(const char *szFilename, FD_INT hFile);
	virtual ~CMPAFileStreamPOSIX(void);

private:
	static const std::uint32_t INIT_BUFFERSIZE;
	FD_INT m_fdFile;
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

#endif /* MPAFILESTREAM_POSIX_C66170D4_7C80_47A6_BDD6_68CC4E90D77F */
