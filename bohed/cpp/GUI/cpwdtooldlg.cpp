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

const TCHAR m_pwdMap[] = { 
	_T('\0'), _T('A'), _T('B'), _T('C'), _T('D'), _T('E'),
	_T('F'), _T('G'), _T('H'), _T('I'), _T('J'), _T('K'),
	_T('L'), _T('M'), _T('N'), _T('O'), _T('P'), _T('Q'),
	_T('R'), _T('S'), _T('T'), _T('U'), _T('V'), _T('W'),
	_T('X'), _T('Y'), _T('Z'), _T('0'), _T('1'), _T('2'),
	_T('3'), _T('4'), _T('5'), _T('6'), _T('7'), _T('8'),
	_T('9'), _T('!'), _T('?'), _T('\x263c'), _T('\x263a'), _T('\x25bc'),
	_T('\x2206')
};


CPwdToolDlg::CPwdToolDlg(HINSTANCE hInstance)
	: CDialog(hInstance, MAKEINTRESOURCE(IDD_PASSWORD_TOOL)),
	m_fntPwd(16, 8, 0, 0, 0xf0, 0, 0, 0, 0, 0, 0 ,0, 0, TEXT("Arial"))
{
	ZeroMemory(m_bPassword, sizeof(m_bPassword));
}

BOOL CPwdToolDlg::OnInit(LPARAM lParam)
{
	m_cEdit.Assign(Ctl(IDC_EDIT1));

	m_pCanvas = (CNesCanvas*) dSendMessage(IDC_IMAGE, WM_GETCUSTOMINSTANCE);
	if ( !m_pCanvas )
	{
		Close(1);
		return TRUE;
	}

	m_bPassword[0] = m_bPassword[1] = m_bPassword[2] = m_bPassword[3] = m_bPassword[4] = 1;

	m_pCanvas->SetCursorSet(0, RGB(255, 255, 255), 32, 32, 32, 32);
	m_pCanvas->SetArea(32 * sizeof(m_bPassword), 32);
	m_pCanvas->GetActiveCursor().Visible(TRUE);
	DecodePwd();
	UpdatePwdCanvas();

	return TRUE;
}

VOID CPwdToolDlg::Let_PwdDecryptData(NES_PWD_DECRYPT_DATA pwd)
{
	m_pwdata = pwd;
}

VOID CPwdToolDlg::UpdatePwdCanvas()
{
	CBitmap bm(16 * sizeof(m_bPassword), 16);

	TCHAR chr[2] = { 0 };
	for(int i = 0; i < sizeof(m_bPassword); ++i)
	{
		chr[0] = m_pwdMap[m_bPassword[i]];
		bm.RenderText(16 * i, 0, 16, 16, chr, m_fntPwd, TRUE, RGB(255, 255, 255), 0, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}

	StretchBlt(*m_pCanvas, 0, 0, 2 * bm.Width(), 2 * bm.Height(), bm, 0, 0, bm.Width(), bm.Height(), SRCCOPY);
}

INT_PTR CPwdToolDlg::OnNotify(LPNMHDR lpnm)
{
	if ( CVN_REQMODIFY == lpnm->code && IDC_IMAGE == lpnm->idFrom )
	{
		PCVNREQMODIFY pcvn = (PCVNREQMODIFY) lpnm;
		POINT & pt = pcvn->cvnh.pt;
		if ( pt.x < 0 || pt.x >= sizeof(m_bPassword) )
			return 0;

		if ( pcvn->delta )
		{
			int chr = m_bPassword[pt.x];
			chr += pcvn->delta;
			if ( chr < 1 )
				chr = sizeof(m_pwdMap) / sizeof(m_pwdMap[0]) - 1;
			else if ( chr >= sizeof(m_pwdMap) / sizeof(m_pwdMap[0]) )
				chr = 1;

			m_bPassword[pt.x] = LOBYTE(chr);
			DecodePwd();
			UpdatePwdCanvas();			
			InvalidateRect(*m_pCanvas, NULL, TRUE);
		}
	}

	return 0;
}

VOID CPwdToolDlg::EncodePwd()
{

}

VOID CPwdToolDlg::DecodePwd()
{
	m_cEdit.Text(TEXT("Password incorrect"));

	BYTE energys[5] = { 0x8c, 0x0c, 0x0c, 0x0c, 0x0c };
	BYTE mapmask = 0;
	BYTE bits[5] = { 0 };

	// validate password
	for(int i = 0; i < sizeof(m_bPassword); ++i)
	{
		bits[i] = m_pwdata.decoder[m_bPassword[i]];
		BYTE bt = bits[i];

		if ( bt & 0x80 )
		{
			// fail
			// MessageBeep(0);
			return;
		}

		if ( i < sizeof(m_bPassword) - 1 && ( (bt & m_pwdata.mask[i]) != m_pwdata.bits[i] ) )
		{
			// fail
			// MessageBeep(0);
			return;
		}
	}

	energys[0] = m_pwdata.chars_energy[ bits[0] & 3 ] | 0x80;
	energys[1] = m_pwdata.chars_energy[ bits[1] & 3 ];
	energys[2] = m_pwdata.chars_energy[ bits[2] & 3 ];
	energys[3] = m_pwdata.chars_energy[ bits[3] & 3 ];
	energys[4] = m_pwdata.chars_energy[ bits[4] & 3 ];

	BYTE lomap = 0, himap = m_pwdata.pmaphi[ ( ( bits[3] & 4 ) | ( bits[4] & 8 ) ) >> 2 ];
	for(int i = 1; i < sizeof(bits) / sizeof(bits[0]); ++i)
	{
		BYTE bt = bits[i] & 3;
		if ( !bt )
			continue;

		lomap |= m_pwdata.pmaplo[ i ];
	}

	mapmask = ( lomap | himap );

	tstring str(255, 0);
	_stprintf_s(&str[0], str.length(), 
		TEXT("Energy1: %d\r\n")
		TEXT("Energy2: %d\r\n")
		TEXT("Energy3: %d\r\n")
		TEXT("Energy4: %d\r\n")
		TEXT("Energy5: %d\r\n")
		TEXT("Planets: %d, %d, %d, %d\r\n")
		TEXT("Tanker: %d"),
		energys[0] - 0x80,
		( energys[1] & 0x80 ? energys[1] - 0x80 : 0 ),
		( energys[2] & 0x80 ? energys[2] - 0x80 : 0 ),
		( energys[3] & 0x80 ? energys[3] - 0x80 : 0 ),
		( energys[4] & 0x80 ? energys[4] - 0x80 : 0 ),
		( mapmask >> 0 ) & 1,
		( mapmask >> 1 ) & 1,
		( mapmask >> 2 ) & 1,
		( mapmask >> 3 ) & 1,
		( mapmask >> 4 )
		);

	m_cEdit.Text(str);
}
