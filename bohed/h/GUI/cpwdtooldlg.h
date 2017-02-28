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

class CPwdToolDlg: public CDialog
{
	NES_PWD_DECRYPT_DATA	m_pwdata;

	CControl		m_cEdit;
	CFont			m_fntPwd;
	CNesCanvas		*m_pCanvas;
	CBitmap			m_bmPwd;
	BYTE			m_bPassword[5];
	
	BOOL			OnInit(LPARAM lParam);
	INT_PTR			OnNotify(LPNMHDR lpnm);

	VOID			UpdatePwdCanvas();

	VOID			EncodePwd();
	VOID			DecodePwd();

public:
	CPwdToolDlg(HINSTANCE hInstance);

	VOID			Let_PwdDecryptData(NES_PWD_DECRYPT_DATA pwd);
};