#ifndef TAG_AA44F1A4_E34F_411D_B471_A42EF1210830
#define TAG_AA44F1A4_E34F_411D_B471_A42EF1210830
#include "mpastream.hpp"

#include <cstdint>
class DLLMPAH CTag
{
public:
	std::uint32_t GetOffset() const { return m_dwOffset; };
	std::uint32_t GetEnd() const { return m_dwOffset + m_dwSize; };
	const char *GetName() const { return m_szName; };
	std::uint32_t GetSize() const { return m_dwSize; };
	float GetVersion() const { return m_fVersion; };

	virtual ~CTag(void);

protected:
	CMPAStream *m_pStream;

	CTag(CMPAStream *pStream, const char *szName, bool bAppended, std::uint32_t dwOffset = 0, std::uint32_t dwSize = 0);

	std::uint32_t m_dwOffset; // beginning of tag
	std::uint32_t m_dwSize;	  // size of tag
	bool m_bAppended;		  // true if at the end of file
	float m_fVersion;		  // format x.yz
	char *m_szName;			  // name of tag

	void SetVersion(char bVersion1, char bVersion2 = 0, char bVersion3 = 0);
};

#endif /* TAG_AA44F1A4_E34F_411D_B471_A42EF1210830 */
