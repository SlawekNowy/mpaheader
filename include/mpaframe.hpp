#pragma once
#include "mpastream.hpp"
#include "mpaheader.hpp"
#include "vbrheader.hpp"
#include "vbriheader.hpp"
#include "xingheader.hpp"

class CMPAFrame
{
public:
	CMPAFrame(CMPAStream *pStream, std::uint32_t &dwOffset, bool bFindSubsequentFrame, bool bExactOffset, bool bReverse, CMPAHeader *pCompareHeader);
	~CMPAFrame(void);

	CVBRHeader *FindVBRHeader() const;

	std::uint32_t GetSubsequentHeaderOffset() const { return m_dwOffset + m_dwFrameSize; };
	bool CheckCRC() const;
	bool IsLast() const { return m_bIsLast; };

public:
	CMPAHeader *m_pHeader;
	CMPAStream *m_pStream;

	std::uint32_t m_dwOffset;	 // offset in bytes where frame begins
	std::uint32_t m_dwFrameSize; // calculated frame size

private:
	static const std::uint32_t m_dwProtectedBitsLayer2[5][2];
	static WORD CalcCRC16(BYTE *pBuffer, std::uint32_t dwSize);
	bool m_bIsLast; // true, if it is last frame
};
