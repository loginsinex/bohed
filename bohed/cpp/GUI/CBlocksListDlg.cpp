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

CBlocksListDlg::CBlocksListDlg(HINSTANCE hInstance)
	: CDialog(hInstance, MAKEINTRESOURCE(IDD_BLOCKSLIST)), m_bBlock( 0 )
{

}

BOOL CBlocksListDlg::OnInit(LPARAM lParam)
{
	m_cbOk.Assign(Ctl(IDOK));
	m_cbCancel.Assign(Ctl(IDCANCEL));
	m_cStatic.Assign(Ctl(IDC_BLOCKID));
	m_pCanvas = (CNesCanvas*) dSendMessage(IDC_IMAGE, WM_GETCUSTOMINSTANCE);
	
	m_cbOk.Text(MB_GetString(IDOK - 1).c_str());
	m_cbCancel.Text(MB_GetString(IDCANCEL - 1).c_str());

	m_pCanvas->SetArea(16 * 32, ( DWORD(m_vpBlocks.size()) / 16 + 1 ) * 32);

	size_t count = m_vpBlocks.size();
	for(size_t n = 0; n < count; ++n)
	{
		CBitmap & bm = *m_vpBlocks[n];
		BitBlt(*m_pCanvas, 32 * (int(n) % 16), 32 * (int(n) / 16), bm.Width(), bm.Height(), bm, 0, 0, SRCCOPY);
	}

	m_pCanvas->SetCursorSet(0, RGB(255, 255, 255), 32, 32, 32, 32);
	m_pCanvas->SetActiveCursor(0);
	m_pCanvas->GetActiveCursor().Visible(TRUE);
	
	POINT pt = { m_bBlock % 16, m_bBlock / 16 };
	m_pCanvas->GetActiveCursor().Pos( pt );
	SetFocus(*m_pCanvas);
	return FALSE;
}

VOID CBlocksListDlg::OnOK()
{
	POINT pt = m_pCanvas->GetActiveCursor().Pos();
	m_bBlock = LOBYTE(pt.x + 16 * pt.y);
	Close(1);
}

VOID CBlocksListDlg::Let_Blocks(std::vector<CBitmap*> vpbmBlocks, BYTE bBlock)
{
	m_vpBlocks = vpbmBlocks;
	m_bBlock = bBlock;
}

VOID CBlocksListDlg::Get_Block(BYTE & bBlock)
{
	bBlock = m_bBlock;
}

INT_PTR CBlocksListDlg::OnNotify(LPNMHDR lpnm)
{
	if ( IDC_IMAGE == lpnm->idFrom )
	{
		if ( CVN_REQPOS == lpnm->code )
		{
			PCVNHEADER pcvn = (PCVNHEADER) lpnm;
			POINT & pt = pcvn->pt;

			if ( LOBYTE(pt.x + 16 * pt.y) >= m_vpBlocks.size() )
				return 1;
			
			m_bBlock = LOBYTE(pt.x + 16 * pt.y);

			tstring strblock(255, 0);
			_stprintf_s(&strblock[0], strblock.length(), TEXT("Block 0x%02X"), m_bBlock);
			m_cStatic.Text(strblock);
		}
	}

	return 0;
}