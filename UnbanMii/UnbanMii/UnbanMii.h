#include <cstdint>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#pragma pack(push, 1)
struct nwc24_config_t
{
	enum
	{
		NWC24_IDCS_INITIAL    = 0,
		NWC24_IDCS_GENERATED  = 1,
		NWC24_IDCS_REGISTERED = 2
	};

	enum
	{
		URL_COUNT           = 0x05,
		MAX_URL_LENGTH      = 0x80,
		MAX_EMAIL_LENGTH    = 0x40,
		MAX_PASSWORD_LENGTH = 0x20,
	};

	u32 magic;      /* 'WcCf' 0x57634366 */
	u32 _unk_04;    /* must be 8 */
	u64 nwc24_id;
	u32 id_generation;
	u32 creation_stage; /* 0==not_generated;1==generated;2==registered; */
	char email[MAX_EMAIL_LENGTH];
	char paswd[MAX_PASSWORD_LENGTH];
	char mlchkid[0x24];
	char http_urls[URL_COUNT][MAX_URL_LENGTH];
	u8 reserved[0xDC];
	u32 enable_booting;
	u32 checksum;
};
#pragma pack(pop)
