
#define			NES_FILE_SIGNATURE		0x1A53454E
#define			NES_PRG_SIZE			0x4000
#define			NES_CHR_SIZE			0x2000
#define			NES_CHR_BANK			0x400

#pragma pack(push, 1)
typedef struct _tagNES_TILE
{
	BYTE pix[8][8];
} NES_TILE, *PNES_TILE;

typedef struct _tagNES_HEADER
{
	union
	{
		BYTE		bSignature[4];
		DWORD		uSignature;
	};

	BYTE		bPrgCount;
	BYTE		bChrCount;
	union
	{
		BYTE	bFlag6;
		struct
		{
			BYTE fMirroring:1;
			BYTE fPrgRAMPresent:1;
			BYTE fTrainerPresent:1;
			BYTE fSquareVRAM:1;
			BYTE fMapperLo:4;
		};
	};
	union
	{
		BYTE	bFlag7;
		struct
		{
			BYTE fVSUnisystem:1;
			BYTE fPlayChoice10:1;	// ROM growed up in 8 kB after chr
			BYTE fHeaderFormat:2;	// 0x02 - this is iNES2.0
			BYTE fMapperHi:4;
		};
	};
	BYTE	bPrgRamSize;

	union
	{
		BYTE	bFlag9;
		struct
		{
			BYTE fTVSystem:1;	// 0 - NTSC, 1 - PAL
			BYTE fReserved:7;
		}; 
	};

	union
	{
		BYTE	bFlag10;
		struct
		{
			BYTE fTVSystemUO:2;
			BYTE fReserved2:2;
			BYTE fPrgRamPresentUO:1;
			BYTE fBusConflicts:1;
			BYTE fReserved3:2;
		};
	};

	BYTE	bReserved[5];
} NES_HEADER, *PNES_HEADER;

#pragma pack(pop)

class CNesFile
{
	NES_HEADER			m_iNesHeader;
	tstring				m_sFilename;
	BYTE				m_uMapper;
	BOOL				m_fFileLoaded;

	std::vector<BYTE>				m_vFile;
	std::vector<BYTE>				m_vTrainer;

	BOOL				ParseFile();

protected:
	std::vector<std::vector<BYTE>>	m_vPRG;
	std::vector<BYTE>				m_vCHR;
	BOOL				InternalLoadFile(LPCTSTR pszFile);
	BOOL				InternalSaveFile(LPCTSTR pszFile = NULL);
	BOOL				InternalFreeFile();
	std::vector<BYTE> &	AddPrg();

public:
	CNesFile();

	NES_HEADER			GetHeader();
	BOOL				IsFileLoaded();
	BYTE				Mapper();
	operator LPCTSTR();
	operator tstring();
};

class CNesSimpleMMC3: public CNesFile
{
	std::vector<BYTE>		m_vRAM;
	std::vector<BYTE>		m_vPPU;
	std::vector<NES_TILE>	m_vTileset;
	WORD					m_vTiles[0x200];

	BYTE				m_uSelectedBank[2];
	BYTE				m_uSelectedCHR[8];
	VOID				ApplyPRG();
	VOID				RevertPRG();
	VOID				ApplyCHR();
	VOID				LoadTiles();
	VOID				StorTiles();
	BYTE				FindBank(BYTE bankId);

public:
	CNesSimpleMMC3();
	BOOL				SetExROM();
	BOOL				IsROMExtended();
	BOOL				LoadFile(LPCTSTR pszFile);
	BOOL				SaveFile(LPCTSTR pszFile = NULL);
	BOOL				FreeFile();

	BOOL				SelectPRG(BYTE bBank);
	BOOL				SelectCHR(BYTE bBank[6]);
	BOOL				SelectCHR(BYTE bRegister, BYTE bBank);

	VOID				DrawTiles(HDC hDC, INT tx, INT ty);
	VOID				DrawTile(HDC hDC, INT x, INT y, WORD tile, PBYTE pbPal, BOOL fMirrorX, BOOL fMirrorY);

	template<typename T> T & Data(UINT ref)
	{
		if ( ref + sizeof(T) > 0xFFFF || ref < 0x8000 )
			throw std::exception("Invalid pointer operation");

		return *((T*) &m_vRAM[ref - 0x8000]);
	}

	NES_TILE &				Tile(UINT id)
	{
		if ( id >= 0x200 )
			throw std::exception("Invalid tile requested");

		return m_vTileset[ m_vTiles[id] ];
	}
};