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

CObjectEditorDlg::CObjectEditorDlg(HINSTANCE hInstance, CNesEditor & nEditor)
	: CDialog(hInstance, MAKEINTRESOURCE(IDD_OBJECT)), m_nEditor( nEditor )
{
	m_nEditor.Get_SprList(m_nObjList);
	ZeroMemory(&m_nObject, sizeof(m_nObject));
}

BOOL CObjectEditorDlg::OnInit(LPARAM lParam)
{
	m_cOk.Assign(Ctl(IDOK));
	m_cCancel.Assign(Ctl(IDCANCEL));

	m_cOk.Text(MB_GetString(IDOK - 1));
	m_cCancel.Text(MB_GetString(IDCANCEL - 1));

	m_cbObj.Assign(Ctl(IDC_COMBO1));
	m_cbObjParam.Assign(Ctl(IDC_COMBO3));
	m_pObjCanvas = (CNesCanvas*) dSendMessage(IDC_IMAGE, WM_GETCUSTOMINSTANCE);
	m_cbObjSlot.Assign(Ctl(IDC_COMBO2));

	m_pObjCanvas->SetArea(256, 256);

	for(int i = 0; i < NES_COUNT_OBJECTS; ++i)
	{
		TCHAR pszNum[16] = { 0 };
		_stprintf_s(pszNum, TEXT("0x%02X"), i);

		m_cbObj.cSendMessage(CB_ADDSTRING, 0, (LPARAM) pszNum);

		if ( i >= 1 && i <= 0x0f )
			m_cbObjSlot.cSendMessage(CB_ADDSTRING, 0, (LPARAM) pszNum);

		if ( i >= 0 && i <= 0x0f )
			m_cbObjParam.cSendMessage(CB_ADDSTRING, 0, (LPARAM) pszNum);
	}

	m_cbObj.cSendMessage(CB_SETCURSEL);
	m_cbObjSlot.cSendMessage(CB_SETCURSEL);
	m_cbObjParam.cSendMessage(CB_SETCURSEL);

	SetTimer(*this, 1, 100, NULL);

	return TRUE;
}

VOID CObjectEditorDlg::OnCommand(USHORT uCmd, USHORT uId, HWND hCtl)
{
	if ( uCmd == CBN_SELENDOK && uId == IDC_COMBO1 )
		UpdateCanvas();
}

VOID CObjectEditorDlg::OnOK()
{
	int obj_id = int(m_cbObj.cSendMessage(CB_GETCURSEL));
	int param = int(m_cbObjParam.cSendMessage(CB_GETCURSEL));
	int slot = int(m_cbObjSlot.cSendMessage(CB_GETCURSEL)) + 1;

	if ( obj_id < 0 || obj_id >= NES_COUNT_OBJECTS ||
		param < 0 || param >= 0x10 ||
		slot < 1 || slot >= 0x10 )
	{
		ShowError(TEXT("Incorrect objects parameters"));
		return;
	}

	m_nObject.id = LOBYTE(obj_id);
	m_nObject.slot = LOBYTE(slot);
	m_nObject.timer = LOBYTE(param);
	Close(1);
}

VOID CObjectEditorDlg::OnDestroy(LPARAM lParam)
{
	KillTimer(*this, 1);
}

VOID CObjectEditorDlg::OnTimer(DWORD_PTR idTimer, FARPROC pTimerProc)
{
	m_nFrameCounter++;
	m_nFrameCounter %= 0x1000;
	UpdateCanvas();
}

VOID CObjectEditorDlg::UpdateCanvas()
{
	int obj_id = int(m_cbObj.cSendMessage(CB_GETCURSEL));
	if ( obj_id < 0 || obj_id >= NES_COUNT_OBJECTS )
		return;

	int id = m_nEditor.Get_IndexByObject(LOBYTE(obj_id));

	RECT rc = { 0, 0, 256, 256 };
	SIZE sz = { 0 };
	FillRect(*m_pObjCanvas, &rc, GetStockBrush(GRAY_BRUSH));

	std::vector<std::vector<NES_SPRITE>> vSpr;
	m_nObjList[id].Get_SpriteInfo(vSpr);
	size_t count_frame = vSpr.size(), frame = m_nFrameCounter % ( count_frame > 0 ? count_frame : 1 );

	if ( count_frame )
	{
		m_nEditor.DrawSpriteByIndex(*m_pObjCanvas, 128, 128, LOBYTE(id), LOBYTE(frame), sz);
		m_nEditor.DrawPPU(*m_pObjCanvas, 256, 0);
	}

	InvalidateRect(*m_pObjCanvas, NULL, TRUE);
}

VOID CObjectEditorDlg::Get_Object(NES_OBJECT & nObj)
{
	nObj = m_nObject;
}