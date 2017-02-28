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
#include <Uxtheme.h>

CSprInfoDlg::CSprInfoDlg(HINSTANCE hInstance, CNesEditor & nEditor)
	: CDialog(hInstance, MAKEINTRESOURCE(IDD_SPRITEINFO)), m_nEditor( nEditor )
{

}

BOOL CSprInfoDlg::OnInit(LPARAM lParam)
{
	m_pCanvas = (CNesCanvas*) dSendMessage(IDC_IMAGE, WM_GETCUSTOMINSTANCE);
	m_pCanvas->SetArea(256 * 3 + 10, 256);

	m_cCheck.Assign(Ctl(IDC_CHECK1));
	m_cCheckByObject.Assign(Ctl(IDC_CHECK2));

	m_lv.Assign(Ctl(IDC_LIST1));
	SetWindowTheme(m_lv, TEXT("EXPLORER"), NULL);

	m_lv.AddColumn(TEXT("Position"), 75);
	m_lv.AddColumn(TEXT("Tile"), 75);
	m_lv.AddColumn(TEXT("Attributes"), 75);
	m_lv.AddColumn(TEXT("Flipping"));
	m_lv.ExtendedStyle(LVS_EX_FULLROWSELECT);

	SPINRANGE(IDC_SPIN1, 255, 0);
	SPINSET(IDC_SPIN1, 0);

	UpdateList();

	return TRUE;
}

VOID CSprInfoDlg::Let_Objects(std::vector<CNesObject> & vList)
{
	m_nObjList = vList;
}

VOID CSprInfoDlg::OnButton(USHORT uId)
{
	BOOL fChecked = (BOOL) m_cCheck.cSendMessage(BM_GETCHECK);

	m_pCanvas->Visible(fChecked);
	m_lv.Visible(!fChecked);

	if ( fChecked )
		SetTimer(*this, 0x100, 100, NULL);
	else
		KillTimer(*this, 0x100);

	UpdateList();
}

VOID CSprInfoDlg::OnDestroy()
{
	KillTimer(*this, 0x100);
}

VOID CSprInfoDlg::OnTimer(DWORD_PTR idTimer, FARPROC pTimerProc)
{
	m_nFrameCounter++;
	m_nFrameCounter %= 1000000;
	UpdateList();
}

VOID CSprInfoDlg::OnCommand(USHORT uCmd, USHORT uId, HWND hCtl)
{
	if ( EN_CHANGE == uCmd && IDC_EDIT1 == uId )
		UpdateList();
}

VOID CSprInfoDlg::UpdateList()
{
	if ( SPINERR(IDC_SPIN1) )
		return;

	BOOL fByObject = (BOOL) m_cCheckByObject.cSendMessage(BM_GETCHECK);

	INT id = int(SPINVAL(IDC_SPIN1));
	if ( fByObject )
	{
		if ( id >= NES_COUNT_OBJECTS )
			return;

		id = m_nEditor.Get_IndexByObject(LOBYTE(id));
	}

	if ( id < 0 || id >= int(m_nObjList.size()) )
		return;

	BOOL fShowImage = (BOOL) m_cCheck.cSendMessage(BM_GETCHECK);
	if ( !fShowImage )
	{
		m_lv.ResetContent();
		std::vector<std::vector<NES_SPRITE>> vSpr;
		m_nObjList[id].Get_SpriteInfo(vSpr);

		size_t count = vSpr.size();

		std::map<BYTE, tstring> mFlip;
		mFlip[0] = TEXT("Unknown 0x01");
		mFlip[1] = TEXT("Unknown 0x02");
		mFlip[2] = TEXT("Unknown 0x04");
		mFlip[3] = TEXT("Behind bg");
		mFlip[4] = TEXT("Flip horizontally");
		mFlip[5] = TEXT("Flip vertically");

		for(size_t n = 0; n < count; ++n)
		{
			size_t scount = vSpr[n].size();

			TCHAR pszFrame[32] = { 0 };
			_stprintf_s(pszFrame, TEXT("Frame: #%d"), n + 1);
			m_lv.AddItem(pszFrame, 0);

			for(size_t sn = 0; sn < scount; ++sn)
			{
				TCHAR psz[32] = { 0 };
				_stprintf_s(psz, 32, TEXT("%02d:%02d"), vSpr[n][sn].X, vSpr[n][sn].Y);

				int item = m_lv.AddItem(psz, n);

				_stprintf_s(psz, TEXT("%02X"), vSpr[n][sn].tile); m_lv.SetItem(item, 1, psz);
				m_lv.SetItem(item, 2, vSpr[n][sn].attr);

				tstring sflip;
				for(int i = 0; i < 6; ++i)
				{
					if ( vSpr[n][sn].data & ( 1 << i ) )
					{
						sflip = sflip + TEXT(" ");
						sflip = sflip + mFlip[i];
					}

				}								
				m_lv.SetItem(item, 3, sflip.c_str());
			}
		}
	}
	else
	{
		RECT rc = { 0, 0, 256, 256 };
		SIZE sz = { 0 };
		FillRect(*m_pCanvas, &rc, GetStockBrush(GRAY_BRUSH));

		std::vector<std::vector<NES_SPRITE>> vSpr;
		m_nObjList[id].Get_SpriteInfo(vSpr);
		size_t count_frame = vSpr.size(), frame = m_nFrameCounter % ( count_frame > 0 ? count_frame : 1 );

		if ( count_frame )
		{
			m_nEditor.DrawSpriteByIndex(*m_pCanvas, 128, 128, LOBYTE(id), LOBYTE(frame), sz);
			m_nEditor.DrawPPU(*m_pCanvas, 256, 0);
		}

		InvalidateRect(*m_pCanvas, NULL, TRUE);
	}
}