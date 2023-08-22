#ifndef MPAHEADER_D81F250B_BC1E_4921_97B5_E6DDED55D9E2
#define MPAHEADER_D81F250B_BC1E_4921_97B5_E6DDED55D9E2
#include "mpastream.hpp"

#include <cstdint>
#define MPA_HEADER_SIZE 4 // MPEG-Audio Header Size 32bit
#define MAXTIMESREAD 5

class DLLMPAH CMPAHeader
{
public:
	CMPAHeader(CMPAStream *pStream, std::uint32_t &dwOffset, bool bExactOffset, bool bReverse, CMPAHeader *pCompareHeader);
	~CMPAHeader();

	bool operator==(CMPAHeader &DestHeader) const;

	std::uint32_t CalcFrameSize() const { return int(((m_dwCoefficients[m_bLSF][m_Layer] * m_dwBitrate / m_dwSamplesPerSec) + m_dwPaddingSize)) * m_dwSlotSizes[m_Layer]; };

	// bitrate is in bit per second, to calculate in bytes => (/ 8)
	std::uint32_t GetBytesPerSecond() const { return m_dwBitrate / 8; };
	// calc number of seconds from number of frames
	std::uint32_t GetLengthSecond(std::uint32_t dwNumFrames) const { return dwNumFrames * m_dwSamplesPerFrame / m_dwSamplesPerSec; };
	std::uint32_t GetBytesPerSecond(std::uint32_t dwNumFrames, std::uint32_t dwNumBytes) const { return dwNumBytes / GetLengthSecond(dwNumFrames); };
	bool IsMono() const { return (m_ChannelMode == SingleChannel) ? true : false; };
	// true if MPEG2/2.5 otherwise false
	bool IsLSF() const { return m_bLSF; };
	std::uint32_t GetSideInfoSize() const { return m_dwSideInfoSizes[IsLSF()][IsMono()]; };
	std::uint32_t GetNumChannels() const { return IsMono() ? 1 : 2; };

private:
	static const std::uint32_t m_dwMaxRange;
	static const std::uint32_t m_dwTolerance;

	static const std::uint32_t m_dwSamplingRates[4][3];
	static const std::uint32_t m_dwPaddingSizes[3];
	static const std::uint32_t m_dwBitrates[2][3][15];
	static const bool m_bAllowedModes[15][2];
	static const std::uint32_t m_dwSamplesPerFrames[2][3];
	static const std::uint32_t m_dwCoefficients[2][3];
	static const std::uint32_t m_dwSlotSizes[3];
	static const std::uint32_t m_dwSideInfoSizes[2][2];

	bool m_bLSF; // true means lower sampling frequencies (=MPEG2/MPEG2.5)

	void Init(char *pHeader, const char *szFilename);

public:
	static const char *m_szLayers[];
	static const char *m_szMPEGVersions[];
	static const char *m_szChannelModes[];
	static const char *m_szEmphasis[];

	enum MPAVersion
	{
		MPEG25 = 0,
		MPEGReserved,
		MPEG2,
		MPEG1
	} m_Version;

	enum MPALayer
	{
		Layer1,
		Layer2,
		Layer3,
		LayerReserved
	} m_Layer;

	enum Emphasis
	{
		EmphNone = 0,
		Emph5015,
		EmphReserved,
		EmphCCITJ17
	} m_Emphasis;

	enum ChannelMode
	{
		Stereo,
		JointStereo,
		DualChannel,
		SingleChannel
	} m_ChannelMode;

	std::uint32_t m_dwSamplesPerSec;
	std::uint32_t m_dwSamplesPerFrame;
	std::uint32_t m_dwBitrate; // in bit per second (1 kb = 1000 bit, not 1024)
	std::uint32_t m_dwPaddingSize;
	std::uint16_t m_wBound;				   // only valid for intensity stereo
	std::uint16_t m_wAllocationTableIndex; // only valid for MPEG 1 Layer II (0=table a, 1=table b,...)

	// flags
	bool m_bCopyright, m_bPrivate, m_bOriginal;
	bool m_bCRC;
	char m_ModeExt;
};

#endif /* MPAHEADER_D81F250B_BC1E_4921_97B5_E6DDED55D9E2 */
