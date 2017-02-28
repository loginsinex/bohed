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

const COLORREF g_crNesColor[] =
{
		XCHGCOLORREF( 0x00747474),
		XCHGCOLORREF( 0x008C1824),
		XCHGCOLORREF( 0x00A80000),
		XCHGCOLORREF( 0x009C0044),
		XCHGCOLORREF( 0x0074008C),
		XCHGCOLORREF( 0x001000A8),
		XCHGCOLORREF( 0x000000A4),
		XCHGCOLORREF( 0x0000087C),
		XCHGCOLORREF( 0x00002C40),
		XCHGCOLORREF( 0x00004400),
		XCHGCOLORREF( 0x00005000),
		XCHGCOLORREF( 0x00143C00),
		XCHGCOLORREF( 0x005C3C18),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00BCBCBC),
		XCHGCOLORREF( 0x00EC7000),
		XCHGCOLORREF( 0x00EC3820),
		XCHGCOLORREF( 0x00F00080),
		XCHGCOLORREF( 0x00BC00BC),
		XCHGCOLORREF( 0x005800E4),
		XCHGCOLORREF( 0x000028D8),
		XCHGCOLORREF( 0x000C4CC8),
		XCHGCOLORREF( 0x00007088),
		XCHGCOLORREF( 0x00009400),
		XCHGCOLORREF( 0x0000A800),
		XCHGCOLORREF( 0x00389000),
		XCHGCOLORREF( 0x00888000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00FCFCFC),
		XCHGCOLORREF( 0x00FCBC3C),
		XCHGCOLORREF( 0x00FC945C),
		XCHGCOLORREF( 0x00FC8840),
		XCHGCOLORREF( 0x00FC78F4),
		XCHGCOLORREF( 0x00B474FC),
		XCHGCOLORREF( 0x006074FC),
		XCHGCOLORREF( 0x003898FC),
		XCHGCOLORREF( 0x003CBCF0),
		XCHGCOLORREF( 0x0010D080),
		XCHGCOLORREF( 0x0048DC4C),
		XCHGCOLORREF( 0x0098F858),
		XCHGCOLORREF( 0x00D8E800),
		XCHGCOLORREF( 0x00787878),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00FCFCFC),
		XCHGCOLORREF( 0x00FCE4A8),
		XCHGCOLORREF( 0x00FCD4C4),
		XCHGCOLORREF( 0x00FCC8D4),
		XCHGCOLORREF( 0x00FCC4FC),
		XCHGCOLORREF( 0x00D8C4FC),
		XCHGCOLORREF( 0x00B0BCFC),
		XCHGCOLORREF( 0x00A8D8FC),
		XCHGCOLORREF( 0x00A0E4FC),
		XCHGCOLORREF( 0x00A0FCE0),
		XCHGCOLORREF( 0x00BCF0A8),
		XCHGCOLORREF( 0x00CCFCB0),
		XCHGCOLORREF( 0x00F0FC9C),
		XCHGCOLORREF( 0x00C4C4C4),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00747474),
		XCHGCOLORREF( 0x008C1824),
		XCHGCOLORREF( 0x00A80000),
		XCHGCOLORREF( 0x009C0044),
		XCHGCOLORREF( 0x0074008C),
		XCHGCOLORREF( 0x001000A8),
		XCHGCOLORREF( 0x000000A4),
		XCHGCOLORREF( 0x0000087C),
		XCHGCOLORREF( 0x00002C40),
		XCHGCOLORREF( 0x00004400),
		XCHGCOLORREF( 0x00005000),
		XCHGCOLORREF( 0x00143C00),
		XCHGCOLORREF( 0x005C3C18),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00BCBCBC),
		XCHGCOLORREF( 0x00EC7000),
		XCHGCOLORREF( 0x00EC3820),
		XCHGCOLORREF( 0x00F00080),
		XCHGCOLORREF( 0x00BC00BC),
		XCHGCOLORREF( 0x005800E4),
		XCHGCOLORREF( 0x000028D8),
		XCHGCOLORREF( 0x000C4CC8),
		XCHGCOLORREF( 0x00007088),
		XCHGCOLORREF( 0x00009400),
		XCHGCOLORREF( 0x0000A800),
		XCHGCOLORREF( 0x00389000),
		XCHGCOLORREF( 0x00888000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00FCFCFC),
		XCHGCOLORREF( 0x00FCBC3C),
		XCHGCOLORREF( 0x00FC945C),
		XCHGCOLORREF( 0x00FC8840),
		XCHGCOLORREF( 0x00FC78F4),
		XCHGCOLORREF( 0x00B474FC),
		XCHGCOLORREF( 0x006074FC),
		XCHGCOLORREF( 0x003898FC),
		XCHGCOLORREF( 0x003CBCF0),
		XCHGCOLORREF( 0x0010D080),
		XCHGCOLORREF( 0x0048DC4C),
		XCHGCOLORREF( 0x0098F858),
		XCHGCOLORREF( 0x00D8E800),
		XCHGCOLORREF( 0x00787878),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00FCFCFC),
		XCHGCOLORREF( 0x00FCE4A8),
		XCHGCOLORREF( 0x00FCD4C4),
		XCHGCOLORREF( 0x00FCC8D4),
		XCHGCOLORREF( 0x00FCC4FC),
		XCHGCOLORREF( 0x00D8C4FC),
		XCHGCOLORREF( 0x00B0BCFC),
		XCHGCOLORREF( 0x00A8D8FC),
		XCHGCOLORREF( 0x00A0E4FC),
		XCHGCOLORREF( 0x00A0FCE0),
		XCHGCOLORREF( 0x00BCF0A8),
		XCHGCOLORREF( 0x00CCFCB0),
		XCHGCOLORREF( 0x00F0FC9C),
		XCHGCOLORREF( 0x00C4C4C4),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00747474),
		XCHGCOLORREF( 0x008C1824),
		XCHGCOLORREF( 0x00A80000),
		XCHGCOLORREF( 0x009C0044),
		XCHGCOLORREF( 0x0074008C),
		XCHGCOLORREF( 0x001000A8),
		XCHGCOLORREF( 0x000000A4),
		XCHGCOLORREF( 0x0000087C),
		XCHGCOLORREF( 0x00002C40),
		XCHGCOLORREF( 0x00004400),
		XCHGCOLORREF( 0x00005000),
		XCHGCOLORREF( 0x00143C00),
		XCHGCOLORREF( 0x005C3C18),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00BCBCBC),
		XCHGCOLORREF( 0x00EC7000),
		XCHGCOLORREF( 0x00EC3820),
		XCHGCOLORREF( 0x00F00080),
		XCHGCOLORREF( 0x00BC00BC),
		XCHGCOLORREF( 0x005800E4),
		XCHGCOLORREF( 0x000028D8),
		XCHGCOLORREF( 0x000C4CC8),
		XCHGCOLORREF( 0x00007088),
		XCHGCOLORREF( 0x00009400),
		XCHGCOLORREF( 0x0000A800),
		XCHGCOLORREF( 0x00389000),
		XCHGCOLORREF( 0x00888000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00FCFCFC),
		XCHGCOLORREF( 0x00FCBC3C),
		XCHGCOLORREF( 0x00FC945C),
		XCHGCOLORREF( 0x00FC8840),
		XCHGCOLORREF( 0x00FC78F4),
		XCHGCOLORREF( 0x00B474FC),
		XCHGCOLORREF( 0x006074FC),
		XCHGCOLORREF( 0x003898FC),
		XCHGCOLORREF( 0x003CBCF0),
		XCHGCOLORREF( 0x0010D080),
		XCHGCOLORREF( 0x0048DC4C),
		XCHGCOLORREF( 0x0098F858),
		XCHGCOLORREF( 0x00D8E800),
		XCHGCOLORREF( 0x00787878),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00FCFCFC),
		XCHGCOLORREF( 0x00FCE4A8),
		XCHGCOLORREF( 0x00FCD4C4),
		XCHGCOLORREF( 0x00FCC8D4),
		XCHGCOLORREF( 0x00FCC4FC),
		XCHGCOLORREF( 0x00D8C4FC),
		XCHGCOLORREF( 0x00B0BCFC),
		XCHGCOLORREF( 0x00A8D8FC),
		XCHGCOLORREF( 0x00A0E4FC),
		XCHGCOLORREF( 0x00A0FCE0),
		XCHGCOLORREF( 0x00BCF0A8),
		XCHGCOLORREF( 0x00CCFCB0),
		XCHGCOLORREF( 0x00F0FC9C),
		XCHGCOLORREF( 0x00C4C4C4),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00747474),
		XCHGCOLORREF( 0x008C1824),
		XCHGCOLORREF( 0x00A80000),
		XCHGCOLORREF( 0x009C0044),
		XCHGCOLORREF( 0x0074008C),
		XCHGCOLORREF( 0x001000A8),
		XCHGCOLORREF( 0x000000A4),
		XCHGCOLORREF( 0x0000087C),
		XCHGCOLORREF( 0x00002C40),
		XCHGCOLORREF( 0x00004400),
		XCHGCOLORREF( 0x00005000),
		XCHGCOLORREF( 0x00143C00),
		XCHGCOLORREF( 0x005C3C18),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00BCBCBC),
		XCHGCOLORREF( 0x00EC7000),
		XCHGCOLORREF( 0x00EC3820),
		XCHGCOLORREF( 0x00F00080),
		XCHGCOLORREF( 0x00BC00BC),
		XCHGCOLORREF( 0x005800E4),
		XCHGCOLORREF( 0x000028D8),
		XCHGCOLORREF( 0x000C4CC8),
		XCHGCOLORREF( 0x00007088),
		XCHGCOLORREF( 0x00009400),
		XCHGCOLORREF( 0x0000A800),
		XCHGCOLORREF( 0x00389000),
		XCHGCOLORREF( 0x00888000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00FCFCFC),
		XCHGCOLORREF( 0x00FCBC3C),
		XCHGCOLORREF( 0x00FC945C),
		XCHGCOLORREF( 0x00FC8840),
		XCHGCOLORREF( 0x00FC78F4),
		XCHGCOLORREF( 0x00B474FC),
		XCHGCOLORREF( 0x006074FC),
		XCHGCOLORREF( 0x003898FC),
		XCHGCOLORREF( 0x003CBCF0),
		XCHGCOLORREF( 0x0010D080),
		XCHGCOLORREF( 0x0048DC4C),
		XCHGCOLORREF( 0x0098F858),
		XCHGCOLORREF( 0x00D8E800),
		XCHGCOLORREF( 0x00787878),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00FCFCFC),
		XCHGCOLORREF( 0x00FCE4A8),
		XCHGCOLORREF( 0x00FCD4C4),
		XCHGCOLORREF( 0x00FCC8D4),
		XCHGCOLORREF( 0x00FCC4FC),
		XCHGCOLORREF( 0x00D8C4FC),
		XCHGCOLORREF( 0x00B0BCFC),
		XCHGCOLORREF( 0x00A8D8FC),
		XCHGCOLORREF( 0x00A0E4FC),
		XCHGCOLORREF( 0x00A0FCE0),
		XCHGCOLORREF( 0x00BCF0A8),
		XCHGCOLORREF( 0x00CCFCB0),
		XCHGCOLORREF( 0x00F0FC9C),
		XCHGCOLORREF( 0x00C4C4C4),
		XCHGCOLORREF( 0x00000000),
		XCHGCOLORREF( 0x00000000)
};


CNesEditor::CNesEditor(CNesSimpleMMC3 & file)
	: m_nCurrentLevel( -1 ), m_nActId( -1 ), m_fLoaded( FALSE ), m_file( file )
{

}

BOOL CNesEditor::SelectLevel(INT nCurrentLevel, INT nActId)
{
	if ( m_fLoaded && nCurrentLevel >= 0 && nCurrentLevel < NES_COUNT_LEVELS || ( nCurrentLevel == ( NES_COUNT_LEVELS - 1 ) && nActId < 8 ) )
	{
		m_nCurrentLevel = nCurrentLevel;
		m_nActId = nActId;
		CacheBlocks();
		return TRUE;
	}
	return FALSE;
}

INT CNesEditor::SelectedLevel()
{
	if ( !m_fLoaded )
		return -1;

	return m_nCurrentLevel;
}

INT CNesEditor::SelectedAct()
{
	if ( !m_fLoaded )
		return -1;

	return m_nActId;
}

BOOL CNesEditor::LoadGame()
{
	CNesSimpleMMC3 & file = m_file;

	if ( !file.IsFileLoaded() )
		return FALSE;

	try
	{
		file.SelectPRG(0x30);
		WORD ptrLevels = file.Data<WORD>(0x8162);
		WORD ptrBanksList = file.Data<WORD>(0xC0C5);
		WORD ptrPalIndexes = file.Data<WORD>(0xC4DA);

		BYTE bBanksList[NES_COUNT_LEVELS] = { 0 };
		CopyMemory(bBanksList, file.Data<BYTE[NES_COUNT_LEVELS]>(ptrBanksList), sizeof(bBanksList));

		for(int i = 0; i < NES_COUNT_LEVELS; ++i)
		{
			WORD ptrAct = file.Data<WORD>(ptrLevels + i * sizeof(ptrLevels));
			m_nLevel[i].nLevelHeaders.clear();
			m_nLevel[i].nLevelRooms.clear();
			m_nBanks[i].nAttrs.clear();
			m_nBanks[i].nBlocks.clear();
			m_nBanks[i].nHeaders.clear();
			m_nBanks[i].nRooms.clear();

			while(file.Data<BYTE>(ptrAct))
			{
				NES_ACT nAct = file.Data<NES_ACT>(ptrAct);
				m_nLevel[i].nLevelHeaders.push_back(LOWORD(m_nBanks[i].nHeaders.size()));
				m_nBanks[i].nHeaders.push_back(nAct);
				ptrAct += sizeof(nAct);
			}

			CopyMemory(m_nBanks[i].bActPalIndex, file.Data<BYTE[0x10]>(0x10 * i + ptrPalIndexes), sizeof(m_nBanks[i].bActPalIndex));
		}

		WORD ptrChrOffsets = file.Data<WORD>(0x8200);
		CopyMemory(m_nGame.nChrOffsets, file.Data<BYTE[NES_COUNT_CHR_OFFSETS]>(ptrChrOffsets), sizeof(m_nGame.nChrOffsets));

		WORD ptrLevelsData = file.Data<WORD>(0xC0DB);
		WORD ptrBlocks = file.Data<WORD>(0xC0E5), ptrAttrs = file.Data<WORD>(0xC0D1);

		for(int i = 0; i < NES_COUNT_LEVELS; ++i)
		{
			file.SelectPRG(bBanksList[i]);

			// load blocks, attributes, rooms
			WORD ptrLevelBlocks = file.Data<WORD>(ptrBlocks + i * sizeof(ptrLevelBlocks)),
				ptrLevelAttrs = file.Data<WORD>(ptrAttrs + i * sizeof(ptrLevelAttrs)),
				ptrRooms = file.Data<WORD>(ptrLevelsData + i * sizeof(ptrLevelsData));

			file.Data<WORD>(ptrBlocks + i * sizeof(ptrLevelBlocks)) = 0;
			file.Data<WORD>(ptrAttrs + i * sizeof(ptrLevelAttrs)) = 0;
			file.Data<WORD>(ptrLevelsData + i * sizeof(ptrLevelsData)) = 0;

			size_t count_blocks = (ptrLevelAttrs - ptrLevelBlocks) / sizeof(NES_BLOCK);
			size_t count_attr = ( ptrRooms - ptrLevelAttrs );

			if ( count_blocks > count_attr )
				throw std::exception( "blocks greater than attrs" );

			NES_BLOCK empty_block = { 0 };
			for(size_t n = 0; n < count_blocks; ++n)
			{
				m_nBanks[i].nBlocks.push_back(file.Data<NES_BLOCK>(ptrLevelBlocks + DWORD(n) * sizeof(NES_BLOCK)));
				file.Data<NES_BLOCK>(ptrLevelBlocks + DWORD(n) * sizeof(NES_BLOCK)) = empty_block;
			}

			for(size_t n = 0; n < count_attr; ++n)
			{
				m_nBanks[i].nAttrs.push_back(file.Data<BYTE>(ptrLevelAttrs + DWORD(n) * sizeof(BYTE)));
				file.Data<BYTE>(ptrLevelAttrs + DWORD(n) * sizeof(BYTE)) = 0;
			}
			
			// load rooms
			std::map<WORD, WORD> mRooms;
						
			WORD ptrMin = 0xFFFF;
			do
			{
				WORD ptrRoom = file.Data<WORD>(ptrRooms);
				if ( ptrRoom < 0x8000 || ptrRoom > 0xBFFF || ptrRooms >= ptrMin )
					break;
				
				file.Data<WORD>(ptrRooms) = 0;

				ptrMin = min(ptrRoom, ptrMin);

				if ( mRooms.find(ptrRoom) == mRooms.end() )
				{
					mRooms[ptrRoom] = LOWORD(m_nBanks[i].nRooms.size());
					m_nBanks[i].nRooms.push_back(file.Data<NES_ROOM>(ptrRoom));
				}
				
				m_nLevel[i].nLevelRooms.push_back( mRooms[ptrRoom] );
				ptrRooms += sizeof(ptrRoom);
			} while(1);
		}


		file.SelectPRG(0x38);

		WORD ptrPals = file.Data<WORD>(0xC534);
		for(int i = 0; i < NES_COUNT_TXTPAL; ++i)
		{
			WORD ptrPal = file.Data<WORD>(ptrPals + i * sizeof(ptrPal));
			m_nGame.nPal[i] = file.Data<NES_CUT_PALETTE>(ptrPal);
		}

		WORD ptrChrLoaders = file.Data<WORD>(0xFDAF);
		for(int i = 0; i < NES_COUNT_CHR_LOADERS; ++i)
		{
			WORD ptrChrLoader = file.Data<WORD>(ptrChrLoaders + i * sizeof(ptrChrLoader));
			m_nGame.nChr[i] = file.Data<NES_CHR_LOADER>(ptrChrLoader);
		}



		// load objects
		const BYTE bObjectsBank = file.Data<BYTE>(0xDB8E);

		file.SelectPRG(bObjectsBank);
		m_nGame.nSprites.clear();
		CopyMemory(m_nGame.nObjectsHPs, 
			file.Data<BYTE[NES_COUNT_OBJECTS]>( file.Data<WORD>(0xDB4C) ),
			sizeof(m_nGame.nObjectsHPs));
		
		CopyMemory(m_nGame.nObjectsIds, 
			file.Data<BYTE[NES_COUNT_OBJECTS]>( file.Data<WORD>(0xDB52) ),
			sizeof(m_nGame.nObjectsIds));

		// load sprites
		for(int i = 0; i < 0x100; ++i)
		{
			CNesObject obj;
			obj.LoadObjectByIndex(file, LOBYTE(i));
			m_nGame.nSprites.push_back(obj);			
		}

		file.SelectPRG(bObjectsBank);
		ZeroMemory(file.Data<BYTE[NES_COUNT_OBJECTS]>( file.Data<WORD>(0xDB4C) ),
			sizeof(m_nGame.nObjectsHPs));
		
		ZeroMemory(file.Data<BYTE[NES_COUNT_OBJECTS]>( file.Data<WORD>(0xDB52) ),
			sizeof(m_nGame.nObjectsIds));

		file.SelectPRG(bObjectsBank);
		WORD ptrObjects = file.Data<WORD>(0xD9E5);
		std::map<WORD, size_t> mObjRooms;

		for(int i = 0; i < NES_COUNT_LEVELS; ++i)
		{
			WORD ptrLevelObjects = file.Data<WORD>(ptrObjects + i * sizeof(ptrLevelObjects));
			file.Data<WORD>(ptrObjects + i * sizeof(ptrLevelObjects)) = 0;
			size_t count_rooms = m_nLevel[i].nLevelRooms.size();
			for(size_t n = 0; n < count_rooms; ++n)
			{				
				WORD ptrRoomsObjects = file.Data<WORD>(ptrLevelObjects + int(n) * sizeof(ptrRoomsObjects));
				if ( ptrRoomsObjects < 0x8000 || ptrRoomsObjects > 0xBFFF )
					continue;

				file.Data<WORD>(ptrLevelObjects + int(n) * sizeof(ptrRoomsObjects)) = 0;

				if ( mObjRooms.find(ptrRoomsObjects) == mObjRooms.end() )
				{
					mObjRooms[ptrRoomsObjects] = m_nBanks[i].nRoomsObjects.size();

					std::vector<NES_OBJECT> nRoomsObjects;
					WORD ptr = ptrRoomsObjects;
					while( file.Data<BYTE>(ptr) )
					{
						nRoomsObjects.push_back( file.Data<NES_OBJECT>( ptr ) );
						ptr += sizeof(NES_OBJECT);
					}
					m_nBanks[i].nRoomsObjects.push_back(nRoomsObjects);
				}

				m_nLevel[i].nRoomsObjects.push_back( LOWORD(mObjRooms[ptrRoomsObjects]) );
			}
		}

		file.SelectPRG(0x34);
		CopyMemory(m_nGame.pwd_data.decoder,		file.Data<BYTE[43]>(file.Data<WORD>(0xBEDA)),	sizeof(m_nGame.pwd_data.decoder));
		CopyMemory(m_nGame.pwd_data.mask,			file.Data<BYTE[5]>(file.Data<WORD>(0xBEED)),	sizeof(m_nGame.pwd_data.mask));
		CopyMemory(m_nGame.pwd_data.bits,			file.Data<BYTE[4]>(file.Data<WORD>(0xBEF0)),	sizeof(m_nGame.pwd_data.bits));
		CopyMemory(m_nGame.pwd_data.pmaplo,			file.Data<BYTE[5]>(file.Data<WORD>(0xBF21)),	sizeof(m_nGame.pwd_data.pmaplo));
		CopyMemory(m_nGame.pwd_data.chars_energy,	file.Data<BYTE[4]>(file.Data<WORD>(0xBF05)),	sizeof(m_nGame.pwd_data.chars_energy));
		CopyMemory(m_nGame.pwd_data.pmaphi,			file.Data<BYTE[4]>(file.Data<WORD>(0xBF3C)),	sizeof(m_nGame.pwd_data.pmaphi));
	}
	catch(std::exception & e)
	{
		UNREFERENCED_PARAMETER( e );
		m_fLoaded = FALSE;
		m_nCurrentLevel = -1;
		m_nActId = -1;
		return FALSE;
	}

	/*
	for(INT i = 0; i < NES_COUNT_LEVELS; ++i)
	{
		_tprintf(TEXT("Level: %d\n"), i + 1);

		size_t count = m_nLevel[i].nLevelHeaders.size();
		for(size_t n = 0; n < count; ++n)
		{
			_tprintf(TEXT("\t*** Act %d\n"), n+1);
			NES_ACT & act = m_nBanks[i].nHeaders[ m_nLevel[i].nLevelHeaders[n] ];
			_tprintf(TEXT("\tDirection: 0x%02X, "), act.bDirection & 0xBF);
			_tprintf(TEXT("Start screen: %d, "), act.bRoomId);
			_tprintf(TEXT("Player point: %d:%d\n"), act.npPlayer.X, act.npPlayer.Y);
			_tprintf(TEXT("\tScroll byte: 0x%02X, "), act.bScroll);
			_tprintf(TEXT("Screens count: %d, "), max(act.bRoomId, act.bRoomIdExit) - min(act.bRoomId, act.bRoomIdExit) + 1);
			_tprintf(TEXT("Exit point: %d:%d\n"), act.npExit.X, act.npExit.Y);
			_tprintf(TEXT("\n"));
		}
		_tprintf(TEXT("*****\n\n"));
	}
	*/

	m_fLoaded = TRUE;
	m_nCurrentLevel = -1;
	return SelectLevel(0, 0);
}

VOID CNesEditor::LocalLevelPatch(CNesSimpleMMC3 & file, BYTE bBank, INT level)
{
	switch(level)
	{
	case 0x05:		// salvage chute lighters
		{
			file.Data<BYTE>(0xC129) = bBank;	// bank for tiles has been moved
			break;
		}
	}
}

BOOL CNesEditor::StorGame()
{
	CNesSimpleMMC3 & file = m_file;

	try
	{
		if ( !m_file.IsROMExtended() )
		{
			m_file.SetExROM();
		}

		file.SelectPRG(0x30);
		WORD ptrLevels = file.Data<WORD>(0x8162);
		WORD ptrBanksList = file.Data<WORD>(0xC0C5);
		WORD ptrPalIndexes = file.Data<WORD>(0xC4DA);

		BYTE bBanksList[NES_COUNT_LEVELS] = { 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e };
		CopyMemory(file.Data<BYTE[NES_COUNT_LEVELS]>(ptrBanksList), bBanksList, sizeof(bBanksList));

		WORD ptrAct = file.Data<WORD>(ptrLevels);
		for(int i = 0; i < NES_COUNT_LEVELS; ++i)
		{
			file.Data<WORD>(ptrLevels + i * sizeof(ptrLevels)) = ptrAct;

			size_t count = m_nBanks[i].nHeaders.size();
			for(size_t n = 0; n < count; ++n)
			{
				file.Data<NES_ACT>(ptrAct) = m_nBanks[i].nHeaders[n];
				ptrAct += sizeof(NES_ACT);
			}
			file.Data<BYTE>(ptrAct++) = 0;

			CopyMemory(file.Data<BYTE[0x10]>(0x10 * i + ptrPalIndexes), m_nBanks[i].bActPalIndex, sizeof(m_nBanks[i].bActPalIndex));
		}

		WORD ptrChrOffsets = file.Data<WORD>(0x8200);
		CopyMemory(m_nGame.nChrOffsets, file.Data<BYTE[NES_COUNT_CHR_OFFSETS]>(ptrChrOffsets), sizeof(m_nGame.nChrOffsets));

		WORD ptrLevelsData = file.Data<WORD>(0xC0DB);
		WORD ptrBlocks = file.Data<WORD>(0xC0E5), ptrAttrs = file.Data<WORD>(0xC0D1);

		for(int i = 0; i < NES_COUNT_LEVELS; ++i)
		{
			file.SelectPRG(bBanksList[i]);

			// store blocks, attributes, rooms
			WORD ptrLevelBlocks = 0x8001;
				

			size_t count_blocks = m_nBanks[i].nBlocks.size();
			size_t count_attr = m_nBanks[i].nAttrs.size();

			if ( count_blocks > count_attr )
				throw std::exception( "blocks greater than attrs" );

			for(size_t n = 0; n < count_blocks; ++n)
				file.Data<NES_BLOCK>(ptrLevelBlocks + DWORD(n) * sizeof(NES_BLOCK)) = m_nBanks[i].nBlocks[n];

			WORD ptrLevelAttrs = ptrLevelBlocks + LOWORD(count_blocks) * sizeof(NES_BLOCK);
			
			for(size_t n = 0; n < count_attr; ++n)
				file.Data<BYTE>(ptrLevelAttrs + LOWORD(n) * sizeof(BYTE)) = m_nBanks[i].nAttrs[n];


			WORD ptrRooms = ptrLevelAttrs + LOWORD(count_attr) * sizeof(BYTE);
			
			// store rooms
			std::map<WORD, WORD> mRooms;
			size_t count_rooms_links = m_nLevel[i].nLevelRooms.size(),
				count_rooms = m_nBanks[i].nRooms.size();
			WORD ptrRoom = ptrRooms + sizeof(ptrRoom) * LOWORD(count_rooms_links); 
			for(size_t n = 0; n < count_rooms; ++n)
			{
				mRooms[LOWORD(n)] = ptrRoom;
				file.Data<NES_ROOM>(ptrRoom) = m_nBanks[i].nRooms[n];
				ptrRoom += sizeof(NES_ROOM);
			}

			// store ptrs
			WORD ptrRoomsPtrs = ptrRooms;
			size_t count_links_rooms = m_nLevel[i].nLevelRooms.size();
			for(size_t n = 0; n < count_links_rooms; ++n)
			{
				file.Data<WORD>(ptrRoomsPtrs) = mRooms[ m_nLevel[i].nLevelRooms[n] ];
				ptrRoomsPtrs += sizeof(ptrRoomsPtrs);
			}

			file.Data<WORD>(ptrBlocks + i * sizeof(ptrLevelBlocks)) = ptrLevelBlocks;
			file.Data<WORD>(ptrAttrs + i * sizeof(ptrLevelAttrs)) = ptrLevelAttrs;
			file.Data<WORD>(ptrLevelsData + i * sizeof(ptrLevelsData)) = ptrRooms;

			LocalLevelPatch(file, bBanksList[i], i);
		}


		file.SelectPRG(0x38);

		WORD ptrPals = file.Data<WORD>(0xC534);
		for(int i = 0; i < NES_COUNT_TXTPAL; ++i)
		{
			WORD ptrPal = file.Data<WORD>(ptrPals + i * sizeof(ptrPal));
			file.Data<NES_CUT_PALETTE>(ptrPal) = m_nGame.nPal[i];
		}

		WORD ptrChrLoaders = file.Data<WORD>(0xFDAF);
		for(int i = 0; i < NES_COUNT_CHR_LOADERS; ++i)
		{
			WORD ptrChrLoader = file.Data<WORD>(ptrChrLoaders + i * sizeof(ptrChrLoader));
			file.Data<NES_CHR_LOADER>(ptrChrLoader) = m_nGame.nChr[i];
		}

		// store enemies
		const BYTE bObjectsBank = 0x34;
		const WORD ptrObjectsInfo = 0x8001;
		const WORD ptrObjects = ptrObjectsInfo + sizeof(m_nGame.nObjectsHPs) + sizeof(m_nGame.nObjectsIds);

		file.SelectPRG(bObjectsBank);
		file.Data<WORD>(0xDB4C) = ptrObjectsInfo;
		file.Data<WORD>(0xDB52) = ptrObjectsInfo + sizeof(m_nGame.nObjectsHPs);
		file.Data<BYTE>(0xDB8E) = bObjectsBank;
		file.Data<BYTE>(0xD9D5) = bObjectsBank;
		file.Data<WORD>(0xD9E5) = ptrObjects;
		file.Data<WORD>(0xD9EA) = ptrObjects + 1;
		
		CopyMemory(file.Data<BYTE[NES_COUNT_OBJECTS]>(ptrObjectsInfo), m_nGame.nObjectsHPs, NES_COUNT_OBJECTS);
		CopyMemory(file.Data<BYTE[NES_COUNT_OBJECTS]>(ptrObjectsInfo + NES_COUNT_OBJECTS), m_nGame.nObjectsIds, NES_COUNT_OBJECTS);

		WORD ptrObjArray = ptrObjects + sizeof(ptrObjects) * NES_COUNT_LEVELS;

		for(int i = 0; i < NES_COUNT_LEVELS; ++i)
		{
			file.Data<WORD>(ptrObjects + sizeof(ptrObjects) * i) = ptrObjArray;
			
			size_t count_links_rooms = m_nLevel[i].nLevelRooms.size();

			WORD ptrObjData = ptrObjArray + sizeof(ptrObjData) * LOWORD(count_links_rooms);
			std::vector<WORD> vObj;
			size_t count_rooms = m_nBanks[i].nRoomsObjects.size();

			WORD ptr = ptrObjData;
			for(size_t n = 0; n < count_rooms; ++n)
			{
				vObj.push_back(ptr);

				size_t count_objects = m_nBanks[i].nRoomsObjects[n].size();
				for(size_t on = 0; on < count_objects; ++on)
				{
					file.Data<NES_OBJECT>(ptr) = m_nBanks[i].nRoomsObjects[n][on];
					ptr += sizeof(NES_OBJECT);
				}
				file.Data<BYTE>(ptr++) = 0;
			}

			// save pointers
			size_t count_rooms_links = m_nLevel[i].nRoomsObjects.size();
			for(size_t n = 0; n < count_rooms_links; ++n)
				file.Data<WORD>(ptrObjArray + LOWORD(n) * sizeof(ptrObjArray)) = vObj[m_nLevel[i].nRoomsObjects[n]];

			ptrObjArray = ptr;
		}
	}
	catch(std::exception & e)
	{
		UNREFERENCED_PARAMETER( e );
		return FALSE;
	}

	return TRUE;
}

size_t CNesEditor::GetActsCount()
{
	if ( !m_fLoaded || -1 == m_nCurrentLevel )
		return 0;

	return m_nLevel[m_nCurrentLevel].nLevelHeaders.size();
}

VOID CNesEditor::CacheBlocks()
{
	INT actid = m_nActId;
	BYTE bChrLoader = ( m_nGame.nChrOffsets[ m_nCurrentLevel * 0x10 + actid ] & 0xfe ) / 2;
	
	BYTE bChr[6] = { 
		m_nGame.nChr[bChrLoader].bank[0], m_nGame.nChr[bChrLoader].bank[1],
		0x50, 0x56,
		m_nGame.nChr[bChrLoader].bank[2], m_nGame.nChr[bChrLoader].bank[3]
		};

	BYTE bPalIndex = ( m_nBanks[m_nCurrentLevel].bActPalIndex[actid] & 0x7f );
	NES_CUT_PALETTE bPal = m_nGame.nPal[bPalIndex];

	BYTE bPalette[0x20] =
	{
		0x0F, bPal.clr[ 0], bPal.clr[ 1], bPal.clr[ 2],
		0x0F, bPal.clr[ 3], bPal.clr[ 4], bPal.clr[ 5],
		0x0F, bPal.clr[ 6], bPal.clr[ 7], bPal.clr[ 8],
		0x0F, bPal.clr[ 9], bPal.clr[10], bPal.clr[11],

		0x0F, bPal.clr[12], bPal.clr[13], bPal.clr[14],
		0x0F, bPal.clr[15], bPal.clr[16], bPal.clr[17],
		0x0F, bPal.clr[18], bPal.clr[19], bPal.clr[20],
		0x0F, bPal.clr[21], bPal.clr[22], bPal.clr[23]
	};


	m_file.SelectCHR(bChr);

	COLORREF clr[4] = { 0, 0x808080, 0xA0A0A0, 0xFFFFFF };
	size_t count = m_nBanks[m_nCurrentLevel].nBlocks.size();

	for(size_t n = 0; n < count; ++n)
	{
		NES_BLOCK & block = m_nBanks[m_nCurrentLevel].nBlocks[n];
		CBitmap & bm = m_bmBlocks[n];
		bm.Create(32, 32);

		COLORREF * pclr = ((COLORREF*) bm.Bits());
		BYTE attr_val = m_nBanks[m_nCurrentLevel].nAttrs[n];
		for(int tiley = 0; tiley < 4; ++tiley)
		{
			for(int tilex = 0; tilex < 4; ++tilex)
			{
				NES_TILE & tile = m_file.Tile(block.tile[tiley][tilex]);
				BYTE attr_index = (tiley & 2) + ((tilex & 2) >> 1),
					attr = ( attr_val >> ( 2 * attr_index )) & 3;

				for(int ty = 0; ty < 8; ++ty)
				{
					for(int tx = 0; tx < 8; ++tx)
					{
						pclr[32 * (8 * tiley + ty) + (8 * tilex + tx)] = g_crNesColor[ bPalette[ 4 * attr + tile.pix[ty][tx] ] ];
					}
				}
			}
		}
	}
}

BOOL CNesEditor::DrawSprite(HDC hDC, INT hx, INT hy, BYTE spr_id, BYTE frame_id, SIZE & sz)
{
	INT actid = m_nActId;
	if ( !m_fLoaded || -1 == m_nCurrentLevel || ( m_nCurrentLevel == ( NES_COUNT_LEVELS - 1 ) && actid >= 8 ) || actid < 0 )
		return FALSE;

	if ( actid < 0 || actid >= (int) GetActsCount() )
		return FALSE;

	if ( spr_id >= NES_COUNT_OBJECTS )
		return FALSE;

	return DrawSpriteByIndex(hDC, hx, hy, m_nGame.nObjectsIds[spr_id], frame_id, sz);
}

BOOL CNesEditor::DrawPPU(HDC hDC, INT hx, INT hy)
{
	INT actid = m_nActId;
	if ( !m_fLoaded || -1 == m_nCurrentLevel || ( m_nCurrentLevel == ( NES_COUNT_LEVELS - 1 ) && actid >= 8 ) || actid < 0 )
		return FALSE;

	if ( actid < 0 || actid >= (int) GetActsCount() )
		return FALSE;

	m_file.DrawTiles(hDC, hx, hy);

	return TRUE;
}

BOOL CNesEditor::DrawSpriteByIndex(HDC hDC, INT hx, INT hy, BYTE spr_id, BYTE frame_id, SIZE & sz)
{
	INT actid = m_nActId;
	if ( !m_fLoaded || -1 == m_nCurrentLevel || ( m_nCurrentLevel == ( NES_COUNT_LEVELS - 1 ) && actid >= 8 ) || actid < 0 )
		return FALSE;

	if ( actid < 0 || actid >= (int) GetActsCount() )
		return FALSE;

	std::vector<std::vector<NES_SPRITE>> vSpr;
	m_nGame.nSprites[ spr_id ].Get_SpriteInfo(vSpr);
	sz = m_nGame.nSprites[ spr_id ].Size();

	if ( !vSpr.size() || frame_id >= LOBYTE(vSpr.size()) )
		return FALSE;

	if ( !vSpr[frame_id].size() )
		return FALSE;

	BYTE bPalIndex = ( m_nBanks[m_nCurrentLevel].bActPalIndex[m_nActId] & 0x7f );
	NES_CUT_PALETTE bPal = m_nGame.nPal[bPalIndex];

	BYTE bPalette[0x20] =
	{
		0x0F, bPal.clr[ 0], bPal.clr[ 1], bPal.clr[ 2],
		0x0F, bPal.clr[ 3], bPal.clr[ 4], bPal.clr[ 5],
		0x0F, bPal.clr[ 6], bPal.clr[ 7], bPal.clr[ 8],
		0x0F, bPal.clr[ 9], bPal.clr[10], bPal.clr[11],

		0x0F, bPal.clr[12], bPal.clr[13], bPal.clr[14],
		0x0F, bPal.clr[15], bPal.clr[16], bPal.clr[17],
		0x0F, bPal.clr[18], bPal.clr[19], bPal.clr[20],
		0x0F, bPal.clr[21], bPal.clr[22], bPal.clr[23]
	};

	const int ydelta = 1;

	size_t count = vSpr[frame_id].size();
	for(size_t n = 0; n < count; ++n)
	{
		NES_SPRITE & nspr = vSpr[frame_id][n];
		BOOL fMirrorX = ( nspr.data & 0x10 ), fMirrorY = ( nspr.data & 0x20 );

		if ( !fMirrorY )
		{
			m_file.DrawTile(hDC, hx + nspr.X, hy + nspr.Y + 8 + ydelta, nspr.tile + 0x100, &bPalette[0x10 + 4 * nspr.attr], fMirrorX, fMirrorY);
			m_file.DrawTile(hDC, hx + nspr.X, hy + nspr.Y + 0 + ydelta, nspr.tile + 0x100 - 1, &bPalette[0x10 + 4 * nspr.attr], fMirrorX, fMirrorY);
		}
		else
		{
			m_file.DrawTile(hDC, hx + nspr.X, hy + nspr.Y + 0 + ydelta, nspr.tile + 0x100, &bPalette[0x10 + 4 * nspr.attr], fMirrorX, fMirrorY);
			m_file.DrawTile(hDC, hx + nspr.X, hy + nspr.Y + 8 + ydelta, nspr.tile + 0x100 - 1, &bPalette[0x10 + 4 * nspr.attr], fMirrorX, fMirrorY);
		}
	}

	GdiFlush();
	return TRUE;
}

BOOL CNesEditor::DrawLevel(HDC hDC, BOOL fShowObjectsSprites)
{
	INT actid = m_nActId;
	if ( !m_fLoaded || -1 == m_nCurrentLevel || ( m_nCurrentLevel == ( NES_COUNT_LEVELS - 1 ) && actid >= 8 ) || actid < 0 )
		return FALSE;

	if ( actid < 0 || actid >= (int) GetActsCount() )
		return FALSE;

	NES_ACT & act = m_nBanks[m_nCurrentLevel].nHeaders[ m_nLevel[m_nCurrentLevel].nLevelHeaders[actid] ];

	BYTE bBeginRoom = min(act.bRoomId, act.bRoomIdExit);
	BYTE bEndRoom = max(act.bRoomId, act.bRoomIdExit);
	BYTE fDirection = GetActDirection(); // (act.bDirection & 1);
	BOOL fBoss = IsActBoss();
	size_t count_blocks = m_nBanks[m_nCurrentLevel].nBlocks.size();
	const int room_height = ( fDirection ? NES_ROOM_HEIGHT + 2 : NES_ROOM_HEIGHT );

	CFont fntExit(10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("FixedSys"));
	CFont fntObj(12, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Tahoma"));

	if ( IsActBoss() && bBeginRoom > 0 )
		bBeginRoom--;

	for(int i = bEndRoom; i >= bBeginRoom; --i)
	{
		int rx = ( fDirection ? 0 : 32 * NES_ROOM_WIDTH * (i-bBeginRoom) );
		int ry = ( fDirection ? 32 * room_height * (i-bBeginRoom) : 0 );
		WORD nRoomId = m_nLevel[m_nCurrentLevel].nLevelRooms[i];
		NES_ROOM & room = m_nBanks[m_nCurrentLevel].nRooms[ nRoomId ];

		for(int y = 0; y < NES_ROOM_HEIGHT; ++y)
		{
			for(int x = 0; x < NES_ROOM_WIDTH; ++x)
			{
				if ( room.block[y][x] >= count_blocks )
					continue;

				CBitmap & bm = m_bmBlocks[ room.block[y][x] ];
				BitBlt(hDC, bm.Width() * x + rx, bm.Height() * y + ry, 
					bm.Width(), bm.Height(), bm, 0, 0, SRCCOPY);
				bm.FreeDC();
			}
		}

		if ( fDirection && i != bEndRoom || fBoss )
		{			
			for(int y = 0; y < 2; ++y)
			{
				for(int x = 0; x < NES_ROOM_WIDTH; ++x)
				{
					if ( room.block[y][x] >= count_blocks )
						continue;

					CBitmap & bm = m_bmBlocks[ room.blockv[y][x] ];
					BitBlt(hDC, bm.Width() * x + rx, bm.Height() * y + ry + 32 * NES_ROOM_HEIGHT,
						bm.Width(), bm.Height(), bm, 0, 0, SRCCOPY);
					bm.FreeDC();
				}
			}		
		}


		if ( act.bRoomIdExit == i )
		{
			INT bkMode = GetBkMode(hDC);
			INT clrText = GetTextColor(hDC);
			INT clrBk = GetBkColor(hDC);
			SetBkMode(hDC, OPAQUE);
			SetTextColor(hDC, RGB(0, 0xff, 0));
			SetBkColor(hDC, RGB(0x00, 0, 0));
			HGDIOBJ hOldFn = SelectObject(hDC, fntExit);
			RECT rcExit = { rx + int(act.npExit.X), ry + int(act.npExit.Y) - 16, 0, 0 };
			rcExit.right = rcExit.left + 40; rcExit.bottom = rcExit.top + 100;
			DrawText(hDC, TEXT("E\r\nx\r\ni\r\nt"), -1, &rcExit, 0);
			SelectObject(hDC, hOldFn);
			SetTextColor(hDC, clrText);
			SetBkColor(hDC, clrBk);
			SetBkMode(hDC, bkMode);

		}
	}

	HPEN hpn = CreatePen(PS_INSIDEFRAME, 1, RGB(0, 255, 0));
	HGDIOBJ holdbr = SelectObject(hDC, GetStockBrush(NULL_BRUSH));
	HGDIOBJ holdpn = SelectObject(hDC, hpn);

	for(int i = bEndRoom; i >= bBeginRoom; --i)
	{
		int rx = ( fDirection ? 0 : 32 * NES_ROOM_WIDTH * (i-bBeginRoom) );
		int ry = ( fDirection ? 32 * room_height * (i-bBeginRoom) : 0 );
		WORD nRoomId = m_nLevel[m_nCurrentLevel].nLevelRooms[i];
		NES_ROOM & room = m_nBanks[m_nCurrentLevel].nRooms[ nRoomId ];


		// draw objects
		if ( i < int(m_nLevel[m_nCurrentLevel].nRoomsObjects.size()) )
		{
			std::vector<NES_OBJECT> & nRoomObjects = m_nBanks[m_nCurrentLevel].nRoomsObjects[ m_nLevel[m_nCurrentLevel].nRoomsObjects[ i ] ];

			TCHAR psz[8] = { 0 };
			_stprintf_s(psz, 8, TEXT("%02X"), i, nRoomId);
			CBitmap bm;
			bm.Create(16, 16);
			bm.RenderText(0, 0, bm.Width(), bm.Height(), psz, fntExit, FALSE, RGB(0xFF, 0x80, 0x80), 0, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
			BitBlt(hDC, rx, ry, bm.Width(), bm.Height(), bm, 0, 0, SRCCOPY);

			size_t count = nRoomObjects.size();
			for(size_t n = 0; n < count; ++n)
			{
				NES_OBJECT & no = nRoomObjects[n];
				SIZE szHitbox = { 0 };
				bm.FillRect(0, 0, bm.Width(), bm.Height(), 0);
				_stprintf_s(psz, 8, TEXT("%02X%01X"), no.id, no.timer);
				bm.RenderText(0, 0, bm.Width(), bm.Height(), psz, fntObj, FALSE, RGB(0, 0xFF, 0), 0, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
				
				if ( !fDirection )
				{
					if ( !fShowObjectsSprites || !DrawSprite(hDC, rx + int(no.X), ry + int(no.Y), no.id, 0, szHitbox))
					{
						BitBlt(hDC, rx + int(no.X), ry + int(no.Y), bm.Width(), bm.Height(), bm, 0, 0, SRCCOPY);					
					}
					
					RECT rc = { rx + int(no.X) - szHitbox.cx / 2, ry + int(no.Y) - szHitbox.cy / 2,
						rx + int(no.X) + szHitbox.cx / 2, ry + int(no.Y) + szHitbox.cy / 2 };
					Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom);
					
				}
				else
				{
					if ( !fShowObjectsSprites || !DrawSprite(hDC, rx + int(no.Y), ry + int(no.X), no.id, 0, szHitbox) )
					{
						BitBlt(hDC, rx + int(no.Y), ry + int(no.X), bm.Width(), bm.Height(), bm, 0, 0, SRCCOPY);					
					}

					RECT rc = { rx + int(no.Y) - szHitbox.cx / 2, ry + int(no.X) - szHitbox.cy / 2,
						rx + int(no.Y) + szHitbox.cx / 2, ry + int(no.X) + szHitbox.cy / 2 };
					Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom);
					
				}				
			}
		}
	}

	SelectObject(hDC, holdbr);
	SelectObject(hDC, holdpn);
	DeletePen(hpn);

	return TRUE;

}

BOOL CNesEditor::IsActBoss()
{
	INT actid = m_nActId;
	if ( !m_fLoaded || -1 == m_nCurrentLevel || ( m_nCurrentLevel == ( NES_COUNT_LEVELS - 1 ) && actid >= 8 ) || actid < 0 )
		return FALSE;

	NES_ACT & act = m_nBanks[m_nCurrentLevel].nHeaders[ m_nLevel[m_nCurrentLevel].nLevelHeaders[actid] ];

	return (act.bDirection & 0x04);
}

BOOL CNesEditor::GetActDirection()
{
	INT actid = m_nActId;
	if ( !m_fLoaded || -1 == m_nCurrentLevel || ( m_nCurrentLevel == ( NES_COUNT_LEVELS - 1 ) && actid >= 8 ) || actid < 0 )
		return FALSE;

	NES_ACT & act = m_nBanks[m_nCurrentLevel].nHeaders[ m_nLevel[m_nCurrentLevel].nLevelHeaders[actid] ];

	return (act.bDirection & 1);
}

size_t CNesEditor::GetRoomsCount()
{
	INT actid = m_nActId;
	if ( !m_fLoaded || -1 == m_nCurrentLevel || ( m_nCurrentLevel == ( NES_COUNT_LEVELS - 1 ) && actid >= 8 ) || actid < 0 )
		return 0;

	NES_ACT & act = m_nBanks[m_nCurrentLevel].nHeaders[ m_nLevel[m_nCurrentLevel].nLevelHeaders[actid] ];

	BYTE bBeginRoom = min(act.bRoomId, act.bRoomIdExit);
	BYTE bEndRoom = max(act.bRoomId, act.bRoomIdExit);

	if ( IsActBoss() && bBeginRoom > 0 )
		bBeginRoom--;

	return ( bEndRoom - bBeginRoom + 1 );
}

VOID CNesEditor::Let_Blocks(std::vector<NES_BLOCK> & vBlocks)
{
	if ( !m_fLoaded || -1 == m_nCurrentLevel )
		return;

	m_nBanks[m_nCurrentLevel].nBlocks = vBlocks;
	CacheBlocks();
}

VOID CNesEditor::Get_Blocks(std::vector<NES_BLOCK> & vBlocks)
{
	if ( !m_fLoaded || -1 == m_nCurrentLevel )
		return;

	vBlocks = m_nBanks[m_nCurrentLevel].nBlocks;
}

BYTE CNesEditor::Get_Block(INT x, INT y)
{
	INT actid = m_nActId;
	if ( !m_fLoaded || -1 == m_nCurrentLevel || ( m_nCurrentLevel == ( NES_COUNT_LEVELS - 1 ) && actid >= 8 ) || actid < 0 )
		return FALSE;

	NES_ACT & act = m_nBanks[m_nCurrentLevel].nHeaders[ m_nLevel[m_nCurrentLevel].nLevelHeaders[actid] ];
	BOOL fDirection = GetActDirection();

	BYTE bBeginRoom = min(act.bRoomId, act.bRoomIdExit);
	BYTE bEndRoom = max(act.bRoomId, act.bRoomIdExit);

	if ( IsActBoss() && bBeginRoom > 0 )
		bBeginRoom--;

	INT room = ( fDirection ? y / NES_ROOM_HEIGHT : x / NES_ROOM_WIDTH ) + min(bBeginRoom, bEndRoom);
	INT rx = ( x % NES_ROOM_WIDTH ), ry = ( y % NES_ROOM_HEIGHT );

	if ( fDirection )
	{
		room = y / ( NES_ROOM_HEIGHT + 2 ) + min(bBeginRoom, bEndRoom);
		ry = y % ( NES_ROOM_HEIGHT + 2 );
	}
	else if ( IsActBoss() )
		ry = y % ( NES_ROOM_HEIGHT + 2 );

	NES_ROOM & droom = m_nBanks[m_nCurrentLevel].nRooms[ m_nLevel[m_nCurrentLevel].nLevelRooms[room] ];
	
	if ( ry >= NES_ROOM_HEIGHT )
		return droom.blockv[ry - NES_ROOM_HEIGHT][rx];
	else
		return droom.block[ry][rx];
}

VOID CNesEditor::Let_Block(INT x, INT y, BYTE block)
{
	INT actid = m_nActId;
	if ( !m_fLoaded || -1 == m_nCurrentLevel || ( m_nCurrentLevel == ( NES_COUNT_LEVELS - 1 ) && actid >= 8 ) || actid < 0 )
		return;

	if ( block >= LOBYTE( m_nBanks[m_nCurrentLevel].nBlocks.size() ) )
		return;

	NES_ACT & act = m_nBanks[m_nCurrentLevel].nHeaders[ m_nLevel[m_nCurrentLevel].nLevelHeaders[actid] ];
	BOOL fDirection = GetActDirection();

	BYTE bBeginRoom = min(act.bRoomId, act.bRoomIdExit);
	BYTE bEndRoom = max(act.bRoomId, act.bRoomIdExit);

	if ( IsActBoss() && bBeginRoom > 0 )
		bBeginRoom--;

	INT room = ( fDirection ? y / NES_ROOM_HEIGHT : x / NES_ROOM_WIDTH ) + min(bBeginRoom, bEndRoom);
	INT rx = ( x % NES_ROOM_WIDTH ), ry = ( y % NES_ROOM_HEIGHT );
	if ( fDirection )
	{
		room = y / ( NES_ROOM_HEIGHT + 2 ) + min(bBeginRoom, bEndRoom);
		ry = y % ( NES_ROOM_HEIGHT + 2 );
	}
	else if ( IsActBoss() )
		ry = y % ( NES_ROOM_HEIGHT + 2 );

	NES_ROOM & droom = m_nBanks[m_nCurrentLevel].nRooms[ m_nLevel[m_nCurrentLevel].nLevelRooms[room] ];
	
	if ( ry >= NES_ROOM_HEIGHT )
		droom.blockv[ry - NES_ROOM_HEIGHT][rx] = block;
	else
		droom.block[ry][rx] = block;
}

VOID CNesEditor::Get_BlocksImages(std::vector<CBitmap*> & bmBlocks)
{
	if ( !m_fLoaded || -1 == m_nCurrentLevel )
		return;

	bmBlocks.clear();
	size_t count = m_nBanks[m_nCurrentLevel].nBlocks.size();
	for(size_t n = 0; n < count; ++n)
		bmBlocks.push_back(&m_bmBlocks[n]);
}

VOID CNesEditor::Get_PwdDecryptData(NES_PWD_DECRYPT_DATA & pwd)
{
	if ( !m_fLoaded )
		return;

	pwd = m_nGame.pwd_data;
}

VOID CNesEditor::Get_SprList(std::vector<CNesObject> & vList)
{
	vList = m_nGame.nSprites;
}

BYTE CNesEditor::Get_IndexByObject(BYTE id)
{
	if ( id < NES_COUNT_OBJECTS )
		return m_nGame.nObjectsIds[id];

	return 0;
}

VOID CNesEditor::Get_RoomObjects(BYTE bRoomId, std::vector<NES_OBJECT> & vObjects)
{
	if ( !m_fLoaded || -1 == m_nCurrentLevel )
		return;

	if ( bRoomId >= m_nLevel[m_nCurrentLevel].nRoomsObjects.size() )
		return;

	vObjects = m_nBanks[m_nCurrentLevel].nRoomsObjects[ m_nLevel[m_nCurrentLevel].nRoomsObjects[bRoomId] ];
}

VOID CNesEditor::Let_RoomObjects(BYTE bRoomId, std::vector<NES_OBJECT> & vObjects)
{
	if ( !m_fLoaded || -1 == m_nCurrentLevel )
		return;

	if ( bRoomId >= m_nLevel[m_nCurrentLevel].nRoomsObjects.size() )
		return;

	m_nBanks[m_nCurrentLevel].nRoomsObjects[ m_nLevel[m_nCurrentLevel].nRoomsObjects[bRoomId] ] = vObjects;
}

BOOL CNesEditor::Get_RoomObjectsByPos(INT x, INT y, BYTE & bRoomId, std::vector<NES_OBJECT> & vObjects, POINT & ptInRoom, BYTE & bSelected)
{
	if ( !m_fLoaded || -1 == m_nCurrentLevel )
		return FALSE;

	BOOL fDirection = GetActDirection(), fBoss = IsActBoss();

	NES_ACT & act = m_nBanks[m_nCurrentLevel].nHeaders[ m_nLevel[m_nCurrentLevel].nLevelHeaders[m_nActId] ];

	BYTE bBeginRoom = min(act.bRoomId, act.bRoomIdExit);
	BYTE bEndRoom = max(act.bRoomId, act.bRoomIdExit);

	if ( IsActBoss() && bBeginRoom > 0 )
		bBeginRoom--;

	INT room = ( fDirection ? y / 256 : x / 256 ) + min(bBeginRoom, bEndRoom);
	INT rx = ( x % 256 ), ry = ( y % 256 );

	ptInRoom.x = rx; ptInRoom.y = ry;

	Get_RoomObjects(LOBYTE(room), vObjects);

	// check for hitbox
	size_t count = vObjects.size();
	bSelected = 0xff;
	for(size_t n = 0; n < count; ++n)
	{
		NES_OBJECT & no = vObjects[n];
		CNesObject & spr = m_nGame.nSprites[ Get_IndexByObject( no.id ) ];
		
		POINT pt = { fDirection ? no.Y : no.X , fDirection ? no.X : no.Y };

		SIZE sz = spr.Size();
		if ( sz.cx < 2 )
			sz.cx = 8;
		if ( sz.cy < 2 )
			sz.cy = 8;

		RECT rc = { pt.x - sz.cx / 2, pt.y - sz.cy / 2, pt.x + sz.cx / 2, pt.y + sz.cy / 2 };
		if ( PtInRect(&rc, ptInRoom) )
		{
			bSelected = LOBYTE(n);
			break;
		}
	}

	bRoomId = LOBYTE(room);
	return TRUE;
}

