#pragma once

class CMPAStream
{
public:

	virtual ~CMPAStream(void);

	virtual std::uint32_t GetSize() const = 0;
	virtual BYTE* ReadBytes(std::uint32_t dwSize, std::uint32_t& dwOffset, bool bMoveOffset = true, bool bReverse = false) const = 0;
	
	std::uint32_t ReadBEValue(std::uint32_t dwNumBytes, std::uint32_t& dwOffset, bool bMoveOffset = true) const;
	std::uint32_t ReadLEValue(std::uint32_t dwNumBytes, std::uint32_t& dwOffset, bool bMoveOffset = true) const;
	LPCTSTR GetFilename() const { return m_szFile; };

protected:
	LPTSTR m_szFile;

	CMPAStream(LPCTSTR szFilename);
};
