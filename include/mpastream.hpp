#ifndef MPASTREAM_C235D32D_77DC_423D_9F80_002478D39C47
#define MPASTREAM_C235D32D_77DC_423D_9F80_002478D39C47

#include <cstdint>
class CMPAStream
{
public:
	virtual ~CMPAStream(void);

	virtual std::uint32_t GetSize() const = 0;
	virtual char *ReadBytes(std::uint32_t dwSize, std::uint32_t &dwOffset, bool bMoveOffset = true, bool bReverse = false) const = 0;

	std::uint32_t ReadBEValue(std::uint32_t dwNumBytes, std::uint32_t &dwOffset, bool bMoveOffset = true) const;
	std::uint32_t ReadLEValue(std::uint32_t dwNumBytes, std::uint32_t &dwOffset, bool bMoveOffset = true) const;
	const char *GetFilename() const { return m_szFile; };

protected:
	char *m_szFile;

	CMPAStream(const char *szFilename);
};

#endif /* MPASTREAM_C235D32D_77DC_423D_9F80_002478D39C47 */
