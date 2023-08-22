#ifndef LAMETAG_CB3CDFFB_984C_4641_90AC_B62F8CE52D70
#define LAMETAG_CB3CDFFB_984C_4641_90AC_B62F8CE52D70
#include "mpadefinitions.hpp"
#include "tag.hpp"

#include <cstdint>
#include <string>
class DLLMPAH CLAMETag : public CTag
{
public:
	static CLAMETag *FindTag(CMPAStream *pStream, bool bAppended, std::uint32_t dwBegin, std::uint32_t dwEnd);
	~CLAMETag(void);

	std::string m_strEncoder;
	std::uint32_t m_dwLowpassFilterHz;
	char m_bBitrate; // in kbps
	char m_bRevision;

	bool IsVBR() const;
	bool IsABR() const;
	bool IsCBR() const;
	const char *GetVBRInfo() const;
	bool IsSimpleTag() const { return m_bSimpleTag; };

private:
	CLAMETag(CMPAStream *pStream, bool bAppended, std::uint32_t dwOffset);

	char m_bVBRInfo;
	bool m_bSimpleTag;
	static const char *m_szVBRInfo[10];
};

#endif /* LAMETAG_CB3CDFFB_984C_4641_90AC_B62F8CE52D70 */
