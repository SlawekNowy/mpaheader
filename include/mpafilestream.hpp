#pragma once
#include "mpastream.hpp"
#include <memory>

struct DLLMPAH CMPAIFile {
	enum class Whence : uint8_t { Set = 0, Cur, End };
	virtual ~CMPAIFile() = default;
	virtual size_t Read(void* data, size_t size) = 0;
	virtual void Seek(size_t offset, Whence whence = Whence::Set) = 0;
	virtual size_t GetSize() = 0;
};

class DLLMPAH CMPAFileStream :
	public CMPAStream
{
public:
	// Use CMPAIFile
	CMPAFileStream(std::unique_ptr<CMPAIFile> file);
	virtual ~CMPAFileStream(void);

private:
	static const std::uint32_t INIT_BUFFERSIZE;
	std::unique_ptr<CMPAIFile> m_file;
	bool m_bMustReleaseFile;

	// concerning read-buffer
	mutable CMPAByte* m_pBuffer;
	mutable std::uint32_t m_dwOffset;	// offset (beginning if m_pBuffer)
	mutable std::uint32_t m_dwBufferSize;

	void Init();
	std::uint32_t Read(void *pData, std::uint32_t dwOffset, std::uint32_t dwSize) const;
	bool FillBuffer(std::uint32_t dwOffset, std::uint32_t dwSize, bool bReverse) const;
	void SetPosition(std::uint32_t dwOffset) const;

protected:
	// methods for file access (must be implemented by all derived classes)

	virtual std::uint32_t GetSize() const override;
	virtual CMPAByte* ReadBytes(std::uint32_t dwSize, std::uint32_t& dwOffset, bool bMoveOffset = true, bool bReverse = false) const override;
};
