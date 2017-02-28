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

CNesFile::CNesFile()
	: m_uMapper( 0 ), m_fFileLoaded( FALSE )
{
	ZeroMemory(&m_iNesHeader, sizeof(m_iNesHeader));
}

BOOL CNesFile::ParseFile()
{
	if ( m_vFile.size() < 0x10 )
		return FALSE;

	PNES_HEADER pNes = (PNES_HEADER) &m_vFile[0];

	if ( pNes->uSignature != NES_FILE_SIGNATURE )
		return FALSE;

	m_uMapper = pNes->fMapperLo | ( pNes->fMapperHi << 4 );

	size_t uMinimumSize = 
		size_t(pNes->bPrgCount) * NES_PRG_SIZE +
		size_t(pNes->bChrCount) * NES_CHR_SIZE +
		size_t( pNes->fTrainerPresent ? 0x200 : 0 ) +
		sizeof(NES_HEADER);

	if ( m_vFile.size() < uMinimumSize )
		return FALSE;

	std::vector<BYTE>::iterator ptr = m_vFile.begin() + sizeof(NES_HEADER);
	if ( pNes->fTrainerPresent )
	{
		m_vTrainer.insert(m_vTrainer.begin(), 
			ptr,
			ptr + 0x200
			);
		ptr += 0x200;
	}

	for(int i = 0; i < pNes->bPrgCount; ++i)
	{
		std::vector<BYTE> vPRG;
		vPRG.insert(vPRG.begin(), ptr, ptr + NES_PRG_SIZE);
		m_vPRG.push_back(vPRG);
		ptr += NES_PRG_SIZE;
	}

	for(int i = 0; i < pNes->bChrCount; ++i)
	{
		m_vCHR.insert(m_vCHR.end(), ptr, ptr + NES_CHR_SIZE);
		ptr += NES_CHR_SIZE;
	}

	CopyMemory(&m_iNesHeader, pNes, sizeof(m_iNesHeader));
	m_fFileLoaded = TRUE;

	return TRUE;
}

BOOL CNesFile::InternalLoadFile(LPCTSTR pszFile)
{
	if ( m_fFileLoaded )
		return FALSE;

	BOOL fResult = FALSE;

	HANDLE hFile = CreateFile(pszFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if ( INVALID_HANDLE_VALUE != hFile )
	{
		LARGE_INTEGER li = { 0 };
		if ( GetFileSizeEx(hFile, &li) && li.QuadPart <= 10 * ( 1 << 20 ) )	// maximum 10 MB
		{
			DWORD w = 0;
			m_vFile.clear();
			m_vFile.insert(m_vFile.begin(), li.LowPart, 0);

			if ( ::ReadFile(hFile, &m_vFile[0], li.LowPart, &w, NULL) && w == li.LowPart )
				fResult = TRUE;
		}
		CloseHandle(hFile);
	}

	if ( fResult )
		fResult = ParseFile();

	if ( !fResult )
		InternalFreeFile();
	else
		m_sFilename = pszFile;

	return fResult;
}

BOOL CNesFile::InternalSaveFile(LPCTSTR pszFile)
{
	if ( !m_fFileLoaded )
		return FALSE;

	size_t ptr = 0;

	m_iNesHeader.bChrCount = LOBYTE(m_vPRG.size());
	m_iNesHeader.bPrgCount = LOBYTE(m_vCHR.size() / NES_CHR_SIZE);
	m_iNesHeader.fTrainerPresent = ( m_vTrainer.size() > 0 );

	m_vFile.clear();
	m_vFile.insert(m_vFile.begin(), sizeof(NES_HEADER), 0);

	CopyMemory(&m_vFile[ptr], &m_iNesHeader, sizeof(m_iNesHeader));
	ptr += sizeof(m_iNesHeader);
	if ( m_vTrainer.size() > 0 )
	{
		m_vFile.insert(m_vFile.end(), m_vTrainer.begin(), m_vTrainer.end());
		ptr += m_vTrainer.size();
	}

	for(int i = 0; i < m_iNesHeader.bPrgCount; ++i)
	{
		m_vFile.insert(m_vFile.end(), m_vPRG[i].begin(), m_vPRG[i].end());
		ptr += NES_PRG_SIZE;
	}

	m_vFile.insert(m_vFile.end(), m_vCHR.begin(), m_vCHR.end());

	if ( !pszFile )
		pszFile = m_sFilename.c_str();

	HANDLE hFile = CreateFile(pszFile, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, 0, NULL);

	BOOL fResult = FALSE;
	if ( hFile != INVALID_HANDLE_VALUE )
	{
		DWORD w = 0;
		if ( ::WriteFile(hFile, &m_vFile[0], (DWORD) (m_vFile.size()), &w, NULL) && w == m_vFile.size() )
			fResult = TRUE;

		CloseHandle(hFile);
	}

	if ( fResult )
		m_sFilename = pszFile;

	return fResult;
}

BOOL CNesFile::InternalFreeFile()
{
	m_sFilename = TEXT("");
	m_uMapper = 0;
	m_fFileLoaded = FALSE;

	m_vFile.clear();
	m_vPRG.clear();
	m_vTrainer.clear();
	m_vCHR.clear();
	ZeroMemory(&m_iNesHeader, sizeof(m_iNesHeader));
	return TRUE;
}

BOOL CNesFile::IsFileLoaded()
{
	return m_fFileLoaded;
}

BYTE CNesFile::Mapper()
{
	return m_uMapper;
}

CNesFile::operator LPCTSTR()
{
	return m_sFilename.c_str();
}

CNesFile::operator tstring()
{
	return m_sFilename;
}

NES_HEADER CNesFile::GetHeader()
{
	return m_iNesHeader;
}

std::vector<BYTE> &	CNesFile::AddPrg()
{
	if ( !IsFileLoaded() )
		throw std::exception("tried to extend file while its not being loaded");

	std::vector<BYTE> prg(NES_PRG_SIZE, 0);
	m_vPRG.insert(m_vPRG.begin(), prg);
	m_iNesHeader.bPrgCount = LOBYTE( m_vPRG.size() );

	return m_vPRG[0];
}


// mmc3

CNesSimpleMMC3::CNesSimpleMMC3()
{
	ZeroMemory(m_uSelectedBank, sizeof(m_uSelectedBank));
	m_uSelectedBank[0] = 0x00;
	m_uSelectedBank[1] = 0x07;
	ZeroMemory(m_uSelectedCHR, sizeof(m_uSelectedCHR));
}

BOOL CNesSimpleMMC3::IsROMExtended()
{
	return ( GetHeader().bPrgCount == 0x10 );
}

BOOL CNesSimpleMMC3::SetExROM()
{
	if ( !IsFileLoaded() )
		return FALSE;

	if ( IsROMExtended() )
		return TRUE;

	if ( GetHeader().bPrgCount != 0x08 )
		return FALSE;

	RevertPRG();
	BYTE bBank1 = Data<BYTE>(0x8000), bBank2 = Data<BYTE>(0xC000);

	for(BYTE i = 0x2e; i >= 0x20; i-=2)
		AddPrg()[0] = i;

	m_uSelectedBank[0] = FindBank(bBank1);
	m_uSelectedBank[1] = FindBank(bBank2);
	ApplyPRG();

	return TRUE;
}

BOOL CNesSimpleMMC3::LoadFile(LPCTSTR pszFile)
{
	if ( InternalLoadFile(pszFile) )
	{
		if ( Mapper() != 0x04 || ( m_vPRG.size() != 0x08 && m_vPRG.size() != 0x10 ) || m_vCHR.size() != 0x20000 )
		{
			InternalFreeFile();
			return FALSE;
		}

		m_uSelectedBank[0] = FindBank(0x30);
		m_uSelectedBank[1] = FindBank(0x3e);

		if ( m_uSelectedBank[0] == 0xff || m_uSelectedBank[1] == 0xff )
		{
			InternalFreeFile();
			return FALSE;

		}

		m_vRAM.clear();
		m_vPPU.clear();
		m_vRAM.insert(m_vRAM.begin(), 0x8000, 0);
		m_vPPU.insert(m_vPPU.begin(), 0x2000, 0);
		LoadTiles();
		ApplyPRG();
		ApplyCHR();
		return TRUE;
	}
	return FALSE;
}

VOID CNesSimpleMMC3::ApplyPRG()
{	
	CopyMemory(&m_vRAM[0x0000], &m_vPRG[m_uSelectedBank[0]][0], NES_PRG_SIZE);
	CopyMemory(&m_vRAM[0x4000], &m_vPRG[m_uSelectedBank[1]][0], NES_PRG_SIZE);
}

VOID CNesSimpleMMC3::RevertPRG()
{
	CopyMemory(&m_vPRG[m_uSelectedBank[0]][0], &m_vRAM[0x0000], NES_PRG_SIZE);
	CopyMemory(&m_vPRG[m_uSelectedBank[1]][0], &m_vRAM[0x4000], NES_PRG_SIZE);
}

VOID CNesSimpleMMC3::ApplyCHR()
{
	POINT c[6] =
	{
		{ m_uSelectedCHR[0] * NES_CHR_BANK, 2 * NES_CHR_BANK },
		{ m_uSelectedCHR[2] * NES_CHR_BANK, 2 * NES_CHR_BANK },
		{ m_uSelectedCHR[4] * NES_CHR_BANK, NES_CHR_BANK },
		{ m_uSelectedCHR[5] * NES_CHR_BANK, NES_CHR_BANK },
		{ m_uSelectedCHR[6] * NES_CHR_BANK, NES_CHR_BANK },
		{ m_uSelectedCHR[7] * NES_CHR_BANK, NES_CHR_BANK }
	};

	INT ptr = 0;
	for(int i = 0; i < sizeof(c) / sizeof(c[0]); ++i)
	{
		for(int n = 0; n < c[i].y; n += 0x10)
			m_vTiles[(ptr + n) / 0x10 ] = LOWORD(( c[i].x + n ) / 0x10);

		ptr += c[i].y;
	}
}

VOID CNesSimpleMMC3::LoadTiles()
{
	size_t count = m_vCHR.size();
	m_vTileset.clear();
	for(size_t n = 0; n < count; n += 0x10)
	{
		NES_TILE tile = { 0 };
		for(int y = 0; y < 8; ++y)
		{
			for(int x = 0; x < 8; ++x)
			{
				tile.pix[y][x] = 
					( 1 & ( m_vCHR[n + y] >> ( 7 - x ) ) | 
					( 1 & ( m_vCHR[8 + n + y] >> ( 7 - x ) ) ) << 1 );
			}
		}

		m_vTileset.push_back(tile);
	}
}

VOID CNesSimpleMMC3::StorTiles()
{
	size_t count = m_vCHR.size();
	for(size_t n = 0; n < count; n += 0x10)
	{
		NES_TILE & tile = m_vTileset[ n / 0x10 ];
		
		for(int y = 0; y < 8; ++y)
		{
			m_vCHR[n + y] = 0;
			m_vCHR[8 + n + y] = 0;
			for(int x = 0; x < 8; ++x)
			{
				m_vCHR[n + y] |= (tile.pix[y][x] & 1) << (7 - x);
				m_vCHR[8 + n + y] |= ((tile.pix[y][x] >> 1) & 1 ) << (7 - x);
			}
		}
	}
}

BOOL CNesSimpleMMC3::SaveFile(LPCTSTR pszFile)
{
	if ( !IsFileLoaded() )
		return FALSE;

	RevertPRG();
	StorTiles();
	return InternalSaveFile(pszFile);
}

BOOL CNesSimpleMMC3::FreeFile()
{
	m_vRAM.clear();
	m_vPPU.clear();
	m_vTileset.clear();
	return InternalFreeFile();
}

BYTE CNesSimpleMMC3::FindBank(BYTE bBank)
{
	size_t count = m_vPRG.size(), bank = -1;
	for(size_t n = 0; n < count; ++n)
		if ( m_vPRG[n][0] == bBank ) bank = n;

	return LOBYTE(bank);
}

BOOL CNesSimpleMMC3::SelectPRG(BYTE bBank)
{
	size_t count = m_vPRG.size(), bank = FindBank(bBank);

	if ( bank != -1 )
	{
		RevertPRG();
		m_uSelectedBank[0] = LOBYTE(bank);
		ApplyPRG();
		return TRUE;
	}
	return FALSE;
}

BOOL CNesSimpleMMC3::SelectCHR(BYTE bRegister, BYTE bBank)
{
	if ( bRegister >= 6 )
		return FALSE;

	BYTE b[6] = { 
		m_uSelectedCHR[0], m_uSelectedCHR[2],
		m_uSelectedCHR[4], m_uSelectedCHR[5],
		m_uSelectedCHR[6], m_uSelectedCHR[7]
		};

	b[bRegister] = bBank;
	return SelectCHR(b);
}

BOOL CNesSimpleMMC3::SelectCHR(BYTE bBank[6])
{
	for(int i = 0; i < 6; ++i)
		if ( bBank[i] >= 0x80 )
			return FALSE;

	if ( bBank[0] >= 0x7f || bBank[1] >= 0x7f )
		return FALSE;

	m_uSelectedCHR[0] = bBank[0] & 0xFE;
	m_uSelectedCHR[1] = bBank[0] | 0x1;
	m_uSelectedCHR[2] = bBank[1] & 0xFE;
	m_uSelectedCHR[3] = bBank[1] | 0x1;
	m_uSelectedCHR[4] = bBank[2];
	m_uSelectedCHR[5] = bBank[3];
	m_uSelectedCHR[6] = bBank[4];
	m_uSelectedCHR[7] = bBank[5];

	ApplyCHR();
	return TRUE;
}


VOID CNesSimpleMMC3::DrawTile(HDC hDC, INT cx, INT cy, WORD ntile, PBYTE pbPal, BOOL fMirrorX, BOOL fMirrorY)
{
	COLORREF clr[4] = { 0, 0x808080, 0xA0A0A0, 0xFFFFFF };

	if ( pbPal )
	{
		clr[1] = g_crNesColor[ pbPal[1] ];
		clr[2] = g_crNesColor[ pbPal[2] ];
		clr[3] = g_crNesColor[ pbPal[3] ];
	}

	CBitmap tbm(8, 8);
	BitBlt(tbm, 0, 0, tbm.Width(), tbm.Height(), hDC, cx, cy, SRCCOPY);

	NES_TILE & tile = Tile(ntile);
	for(int y = 0; y < 8; ++y)
	{
		for(int x = 0; x < 8; ++x)
		{
			INT tx = ( fMirrorX ? 7 - x : x ), ty = ( fMirrorY ? 7 - y : y );

			if ( tile.pix[ty][tx] )
				*((COLORREF*) &tbm[y][x]) = clr[ tile.pix[ty][tx] ];
		}
	}

	BitBlt(hDC, cx, cy, tbm.Width(), tbm.Height(), tbm, 0, 0, SRCCOPY); 
}

VOID CNesSimpleMMC3::DrawTiles(HDC hDC, INT tx, INT ty)
{
	COLORREF clr[4] = { 0, 0x808080, 0xA0A0A0, 0xFFFFFF };

	CBitmap tbm[2];
	tbm[0].Create(128, 128); tbm[1].Create(128, 128);

	for(int i = 0; i < 0x200; ++i)
	{
		CBitmap & bm = tbm[i / 0x100];
		INT ntile = (i % 0x100), tx = ntile % 16, ty = ntile / 16;
		NES_TILE & tile = Tile(i);
		for(int y = 0; y < 8; ++y)
		{
			for(int x = 0; x < 8; ++x)
			{
				*((COLORREF*) &bm[8 * ty + y][8 * tx + x]) = clr[ tile.pix[y][x] ]; // clr[ m_vTileset[ m_vTiles[i] ].pix[y][x]];
			}
		}
	}

	StretchBlt(hDC, tx, ty, 2 * tbm[0].Width(), 2 * tbm[0].Height(), tbm[0], 0, 0, 
		tbm[0].Width(), tbm[0].Height(),
		SRCCOPY);

	StretchBlt(hDC, tx + 260, ty, 2 * tbm[1].Width(), 2 * tbm[1].Height(), tbm[1], 0, 0, 
		tbm[1].Width(), tbm[1].Height(),
		SRCCOPY);
}