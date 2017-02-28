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

class CObjectEditorDlg: public CDialog
{
	CControl					m_cbObj;
	CControl					m_cbObjParam;
	CControl					m_cOk;
	CControl					m_cCancel;
	CNesCanvas					*m_pObjCanvas;
	CControl					m_cbObjSlot;
	CNesEditor					& m_nEditor;
	size_t						m_nFrameCounter;
	std::vector<CNesObject>		m_nObjList;
	NES_OBJECT					m_nObject;


	VOID						OnTimer(DWORD_PTR idTimer, FARPROC pTimerProc);
	BOOL						OnInit(LPARAM lParam);
	VOID						OnDestroy(LPARAM lParam);
	VOID						UpdateCanvas();
	VOID						OnCommand(USHORT uCmd, USHORT uId, HWND hCtl);
	VOID						OnOK();

public:
	CObjectEditorDlg(HINSTANCE hInstance, CNesEditor & nEditor);

	VOID						Get_Object(NES_OBJECT & nObj);
};