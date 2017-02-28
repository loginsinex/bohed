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

class CMainDlg: public CDialog
{
	VOID			OnOK();

public:
	CMainDlg(HINSTANCE hInstance);
};

class CMainWindow: public CWindow
{
	CNesCanvas *	m_pCanvas;
	CNesSimpleMMC3	m_File;
	CNesEditor		m_nEditor;
	BYTE			m_bCatchedItem;
	BOOL			m_fShowSprites;

	struct
	{
		BOOL		fObjectCatched;
		NES_OBJECT	vObject;
	} m_catchedObject;

	BOOL			OnCreate(LPCREATESTRUCT lpcs);
	VOID			OnNCDestroy();
	VOID			OnOK();

	VOID			OnButton(USHORT uId);
	VOID			OnCommand(USHORT uCmd, USHORT uId, HWND hCtl);

	// commands
	VOID			Ctl_OnOpen();
	VOID			Ctl_OnSave();
	VOID			Ctl_OnPwdTool();
	VOID			Ctl_OnSprInfo();
	VOID			Ctl_OnShowSprites();
	VOID			Ctl_OnChangeLayer(USHORT uCmd);

	INT_PTR			ReqPos(PCVNHEADER pcvn);
	VOID			ReqMdf(PCVNREQMODIFY pcvn);

	INT_PTR			ReqPosBlocks(PCVNHEADER pcvn);
	VOID			ReqMdfBlocks(PCVNREQMODIFY pcvn);

	INT_PTR			ReqPosObjects(PCVNHEADER pcvn);
	VOID			ReqMdfObjects(PCVNREQMODIFY pcvn);

	INT_PTR			OnNotify(LPNMHDR lpnm);
	VOID			ShowStat();

	VOID			DrawCurrentLevel();

	CTreeView		m_ctv;
	CControl		m_cCanvas;
	CControl		m_cStatus;

public:
	CMainWindow(HINSTANCE hInstance);
};