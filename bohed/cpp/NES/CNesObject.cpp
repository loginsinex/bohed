/*
    A NES Bucky O'Hare Level Editor
    Copyright (C) 2015 ALXR aka loginsin

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "stdafx.h"

CNesObject::CNesObject()
	: m_nObjId( -1 )
{
	ZeroMemory(&m_nObj, sizeof(m_nObj));
}

VOID CNesObject::LoadObject(CNesSimpleMMC3 & file, BYTE id)
{
	m_nObjId = id;

	BYTE bObjValsBank = file.Data<BYTE>(0xDB8E);

	file.SelectPRG(bObjValsBank);
	WORD ptrHP = file.Data<WORD>(0xDB4C);
	WORD ptrVal = file.Data<WORD>(0xDB52);

	m_nObj.hp = file.Data<BYTE>(ptrHP + id);
	BYTE val = file.Data<BYTE>(ptrVal + id);
	LoadObjectByIndex(file, val);
}

VOID CNesObject::LoadObjectByIndex(CNesSimpleMMC3 & file, BYTE val)
{
	BYTE nObjDataBank = file.Data<BYTE>(0xC6B5);

	file.SelectPRG(nObjDataBank);

	WORD ptrSet1 = file.Data<WORD>(0xC6CB) + val;
	WORD ptrSet2 = file.Data<WORD>(0xC6D5) + val;

	if ( val % 2 )
	{
		ptrSet1 = file.Data<WORD>(0xC6E5) + val;
		ptrSet2 = file.Data<WORD>(0xC6EF) + val;
	}

	ptrSet1 = file.Data<WORD>(ptrSet1);
	ptrSet2 = file.Data<WORD>(ptrSet2);

	BYTE bSet1[3] = { 0 }, bSet2[2] = { 0 };
	CopyMemory(bSet1, file.Data<BYTE[3]>(ptrSet1), sizeof(bSet1));
	CopyMemory(bSet2, file.Data<BYTE[2]>(ptrSet2), sizeof(bSet2));

	m_nObj.flags = bSet1[0];
	m_nObj.hitboxX = bSet1[1];
	m_nObj.hitboxY = (bSet1[2] & 0x3f);

	m_nObj.set1Lo = bSet2[1];				// offset in spr_set array
	m_nObj.set1Hi = ( bSet1[2] >> 6 ) & 3;	// id of array
	m_nObj.set2Lo = ( bSet2[0] & 0x7f );	// count of frames
	m_nObj.set2Hi = val;					// data offset

	WORD ptrFrames = GetFramePtr(file, m_nObj.set1Hi);
	WORD ptrSet = ptrFrames + m_nObj.set1Lo;

	AddFrame(file, ptrSet);
		
	// load other frames
	WORD ptrSetFrame = ptrSet2 + sizeof(bSet2);
	while( !(0x80 & file.Data<BYTE>(ptrSetFrame)) )
	{
		CopyMemory(bSet2, file.Data<BYTE[2]>(ptrSetFrame), sizeof(bSet2));
		AddFrame(file, ptrFrames + bSet2[1]);
		ptrSetFrame += sizeof(bSet2);
	}
}

WORD CNesObject::GetFramePtr(CNesSimpleMMC3 & file, BYTE id)
{
	switch(id)
	{
	case 0: return file.Data<WORD>(0xD253);
	case 1: return file.Data<WORD>(0xD244);
	case 2: return file.Data<WORD>(0xD235);
	default: return file.Data<WORD>(0xD226);
	}
}


VOID CNesObject::AddFrame(CNesSimpleMMC3 & file, WORD ptr)
{
	ptr = file.Data<WORD>(ptr);

	std::vector<NES_SPRITE> sprlist;
	BYTE nSprites = file.Data<BYTE>(ptr++);
	for(int i = 0; i < nSprites; ++i)
	{
		NES_SPRITE spr = file.Data<NES_SPRITE>(ptr);
		BOOL fReduced = !( spr.tile & 0x80 );

		spr.tile <<= 1;
		spr.tile |= 1;
				
		if ( fReduced )
		{
			spr.X = spr.attrdata;
			spr.attrdata = ( i > 0 ? sprlist[i - 1].attrdata : 0 );
			ptr--;
		}
				
		sprlist.push_back(spr);
		ptr += sizeof(NES_SPRITE);
	}
			
	m_vSprite.push_back(sprlist);
}

VOID CNesObject::Get_SpriteInfo(std::vector<std::vector<NES_SPRITE>> & vList)
{
	vList = m_vSprite;
}

SIZE CNesObject::Size()
{
	SIZE sz = { m_nObj.hitboxX, m_nObj.hitboxY };
	return sz;
}