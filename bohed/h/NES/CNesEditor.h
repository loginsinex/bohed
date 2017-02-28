
#define			NES_COUNT_LEVELS			8
#define			NES_COUNT_CHR_LOADERS		50
#define			NES_COUNT_CHR_OFFSETS		( NES_COUNT_LEVELS * 0x10 - 8 )
#define			NES_COUNT_TXTPAL			0x71
#define			NES_COUNT_OBJECTS			0x87

#define			NES_ROOM_WIDTH				8
#define			NES_ROOM_HEIGHT				6
#define			NES_BLOCK_WIDTH				4
#define			NES_BLOCK_HEIGHT			NES_BLOCK_WIDTH

extern const COLORREF g_crNesColor[];


#pragma pack(push,1)

typedef struct _tagNES_BLOCK
{
	BYTE		tile[NES_BLOCK_HEIGHT][NES_BLOCK_WIDTH];
} NES_BLOCK, *PNES_BLOCK;

typedef struct _tagNES_ROOM
{
	BYTE		block[NES_ROOM_HEIGHT][NES_ROOM_WIDTH];
	BYTE		blockv[2][NES_ROOM_WIDTH];
} NES_ROOM, *PNES_ROOM;

typedef struct _tagNES_POINT
{
	BYTE		Y;
	BYTE		X;
} NES_POINT, *PNES_POINT;

typedef struct _tagNES_ACT
{
	BYTE			bDirection;
	BYTE			bRoomId;
	NES_POINT		npPlayer;
	BYTE			bScroll;
	BYTE			bRoomIdExit;
	NES_POINT		npExit;
} NES_ACT, *PNES_ACT;

typedef struct _tagNES_CHR_LOADER
{
	BYTE			bank[4];
} NES_CHR_LOADER, *PNES_CHR_LOADER;

typedef struct _tagNES_CUT_PALETTE
{
	BYTE			clr[24];
} NES_CUT_PALETTE, *PNES_CUT_PALETTE;

typedef struct _tagNES_PWD_DECRYPT_DATA
{
	BYTE					decoder[43];
	BYTE					mask[5];
	BYTE					bits[4];
	BYTE					pmaplo[5];
	BYTE					chars_energy[4];
	BYTE					pmaphi[4];
} NES_PWD_DECRYPT_DATA, *PNES_PWD_DECRYPT_DATA;

typedef struct _tagNES_OBJECT
{
	BYTE					X;
	union
	{
		BYTE					data;
		struct
		{
			BYTE					slot:4;
			BYTE					timer:4;
		};
	};
	BYTE					Y;
	BYTE					id;
} NES_OBJECT, *PNES_OBJECT;

#pragma pack(pop)

class CNesEditor
{
	CNesSimpleMMC3 &				m_file;
	INT								m_nCurrentLevel;
	INT								m_nActId;
	BOOL							m_fLoaded;

	struct
	{
		NES_CHR_LOADER				nChr[NES_COUNT_CHR_LOADERS];
		BYTE						nChrOffsets[NES_COUNT_CHR_OFFSETS];
		NES_CUT_PALETTE				nPal[NES_COUNT_TXTPAL];
		NES_PWD_DECRYPT_DATA		pwd_data;
		std::vector<CNesObject>		nSprites;
		BYTE						nObjectsIds[NES_COUNT_OBJECTS];
		BYTE						nObjectsHPs[NES_COUNT_OBJECTS];
	} m_nGame;

	struct
	{
		std::vector<NES_ACT>					nHeaders;
		std::vector<NES_ROOM>					nRooms;
		std::vector<NES_BLOCK>					nBlocks;
		std::vector<BYTE>						nAttrs;
		BYTE									bActPalIndex[0x10];
		std::vector<std::vector<NES_OBJECT>>	nRoomsObjects;
	} m_nBanks[NES_COUNT_LEVELS];

	struct
	{
		std::vector<WORD>					nLevelHeaders;
		std::vector<WORD>					nLevelRooms;
		std::vector<WORD>					nRoomsObjects;
	} m_nLevel[NES_COUNT_LEVELS];

	CBitmap							m_bmBlocks[0x100];

	VOID							LocalLevelPatch(CNesSimpleMMC3 & file, BYTE bBank, INT level);

	VOID							CacheBlocks();

public:
	CNesEditor(CNesSimpleMMC3 & file);

	BOOL							LoadGame();
	BOOL							StorGame();
	BOOL							SelectLevel(INT nCurrentLevel, INT nActId);
	INT								SelectedLevel();
	INT								SelectedAct();
	size_t							GetActsCount();
	BOOL							GetActDirection();
	BOOL							IsActBoss();
	size_t							GetRoomsCount();
	
	VOID							Get_BlocksImages(std::vector<CBitmap*> & bmBlocks);
	VOID							Let_Blocks(std::vector<NES_BLOCK> & vBlocks);
	VOID							Get_Blocks(std::vector<NES_BLOCK> & vBlocks);

	VOID							Get_RoomObjects(BYTE bRoomId, std::vector<NES_OBJECT> & vObjects);
	VOID							Let_RoomObjects(BYTE bRoomId, std::vector<NES_OBJECT> & vObjects);

	BOOL							Get_RoomObjectsByPos(INT x, INT y, BYTE & bRoomId, std::vector<NES_OBJECT> & vObjects, POINT & ptInRoom, BYTE & bSelected);

	BYTE							Get_Block(INT x, INT y);
	VOID							Let_Block(INT x, INT y, BYTE block);
	VOID							Get_PwdDecryptData(NES_PWD_DECRYPT_DATA & pwd);
	VOID							Get_SprList(std::vector<CNesObject> & vList);
	BYTE							Get_IndexByObject(BYTE id);

	BOOL							DrawLevel(HDC hDC, BOOL fShowObjectsSprites = TRUE);
	BOOL							DrawSprite(HDC hDC, INT hx, INT hy, BYTE spr_id, BYTE frame_id, SIZE & sz);
	BOOL							DrawSpriteByIndex(HDC hDC, INT hx, INT hy, BYTE spr_id, BYTE frame_id, SIZE & sz);
	BOOL							DrawPPU(HDC hDC, INT hx, INT hy);

};