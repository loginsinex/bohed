
#pragma pack(push, 1)

typedef struct _tagNES_SPRITE
{
	char				Y;
	BYTE				tile;
	union
	{
		BYTE				attrdata;
		struct
		{
			BYTE			attr:2;
			BYTE			data:6;
		};
	};
	char				X;
} NES_SPRITE, *PNES_SPRITE;

#pragma pack(pop)

class CNesObject
{
	BYTE			m_nObjId;

	struct
	{
		BYTE		hp;
		BYTE		flags;
		BYTE		hitboxX;
		BYTE		hitboxY;

		BYTE		set1Lo;
		BYTE		set1Hi;
		BYTE		set2Lo;
		BYTE		set2Hi;
	} m_nObj;

	std::vector<std::vector<NES_SPRITE>>		m_vSprite;

	VOID			AddFrame(CNesSimpleMMC3 & file, WORD ptr);
	WORD			GetFramePtr(CNesSimpleMMC3 & file, BYTE id);

public:
	CNesObject();

	VOID			LoadObject(CNesSimpleMMC3 & file, BYTE id);
	VOID			LoadObjectByIndex(CNesSimpleMMC3 & file, BYTE id);
	VOID			Get_SpriteInfo(std::vector<std::vector<NES_SPRITE>> & vSprite);
	SIZE			Size();
};