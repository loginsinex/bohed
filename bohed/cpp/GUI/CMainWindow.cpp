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
#include <shlwapi.h>
#include <Uxtheme.h>

CMainDlg::CMainDlg(HINSTANCE hInstance)
	: CDialog(hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX))
{

}

VOID CMainDlg::OnOK()
{
	if ( Confirm(TEXT("Close this dialog?")) )
		Close(1);
}

CMainWindow::CMainWindow(HINSTANCE hInstance)
	: CWindow(hInstance, TEXT("Bucky O'Hare Level Editor")),
	m_ctv(hInstance, 0x10, 14, 14, 200, -(14 + 25 + 14), WS_VISIBLE | WS_TABSTOP | WS_BORDER | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS, 0, ANCHOR_LEFT),
	m_cCanvas(hInstance, 0x1010, TEXT("SysImage32"), NULL, 220, 14, -14, -(14 + 25 + 14), WS_VISIBLE | WS_TABSTOP | WS_BORDER, 0, ANCHOR_FULL),
	m_cStatus(hInstance, 0x1011, STATUSCLASSNAME, NULL, 0, 0, 0, 0, WS_VISIBLE, 0, ANCHOR_BOTTOM),
	m_nEditor( m_File ),
	m_fShowSprites( TRUE )
{
	m_catchedObject.fObjectCatched = FALSE;
	Register(CS_DBLCLKS, NULL, LoadCursor(NULL, IDC_ARROW), (HBRUSH) (COLOR_BTNFACE + 1));
	pushctl(m_cCanvas);
	pushctl(m_ctv);
	pushctl(m_cStatus);
}

BOOL CMainWindow::OnCreate(LPCREATESTRUCT lpcs)
{
	m_pCanvas = (CNesCanvas*) m_cCanvas.cSendMessage(WM_GETCUSTOMINSTANCE);
	
	SetMenu(*this, LoadMenu(GetInstance(), MAKEINTRESOURCE(IDC_BOHED)));

	SetWindowTheme(m_ctv, TEXT("EXPLORER"), NULL);
	m_ctv.SetCurSel( m_ctv.AddItem(NULL, TEXT("Game not loaded"), 0, TRUE) );

	return FALSE;
}

VOID CMainWindow::OnNCDestroy()
{
	PostQuitMessage(0);
}

VOID CMainWindow::OnOK()
{

}

VOID CMainWindow::OnCommand(USHORT uCmd, USHORT uId, HWND hCtl)
{
	if ( 1 == uCmd )
		OnButton(uId);
}

VOID CMainWindow::OnButton(USHORT uId)
{
	switch(uId)
	{
	case ID_FILE_OPEN: Ctl_OnOpen(); break;
	case ID_FILE_SAVE: Ctl_OnSave(); break;
	case ID_TOOLS_PASSWORDTOOL: Ctl_OnPwdTool(); break;
	case ID_TOOLS_SPRITESINFO: Ctl_OnSprInfo(); break;
	case ID_VIEW_SHOWSPRITES: Ctl_OnShowSprites(); break;
	case ID_LAYER_BLOCKSLAYER: 
	case ID_LAYER_OBJECTSLAYER: Ctl_OnChangeLayer(uId); break;
	case IDM_EXIT: Close(0); break;
	}
}

VOID CMainWindow::Ctl_OnOpen()
{
	tstring sFile = OpenFile(TEXT("Bucky O'Hare.nes"), TEXT("NES files (*.nes)"), TEXT("*.nes"), 
		TEXT("All files (*.*)"), TEXT("*.*"), 0);

	if ( sFile.length() > 0 )
	{
		m_File.FreeFile();
		if ( !m_File.LoadFile(sFile.c_str()) )
		{
			ShowErrorF(TEXT("Unable to open file '%s'.\nFile access error or not valid iNES file"),
			PathFindFileName( sFile.c_str() ));
			m_File.FreeFile();
		}
		else
		{
			if ( !m_nEditor.LoadGame() )
				ShowError(TEXT("Unable to load game"));
			else
			{
				/*
				m_nEditor.SelectLevel(0, 0);
				std::vector<NES_OBJECT> vObjects;
				m_nEditor.Get_RoomObjects(0, vObjects);
				vObjects.clear();

				NES_OBJECT no = { 0 };
				no.slot = 1;
				no.timer = 9;
				no.id = 0x09;
				no.X = no.Y = 128;
				vObjects.push_back(no);
				no.X = 148;
				no.slot = 2;
				no.timer = 1;
				vObjects.push_back(no);
				no.X = 168;
				no.slot = 3;
				no.timer = 9;
				vObjects.push_back(no);
				m_nEditor.Let_RoomObjects(0, vObjects);
				*/

				HTREEITEM hSelItem = NULL;
				m_ctv.ResetContent();
				for(int i = 0; i < NES_COUNT_LEVELS; ++i)
				{
					if ( m_nEditor.SelectLevel(i, 0) )
					{
						tstring str(255, 0);
						_stprintf_s(&str[0], str.length(), TEXT("Level %d"), i + 1);

						size_t acts = m_nEditor.GetActsCount();
						HTREEITEM hItem = m_ctv.AddItem(NULL, str.c_str(), MAKELONG(-1, i), TRUE);

						for(size_t n = 0; n < acts; ++n)
						{
							_stprintf_s(&str[0], str.length(), TEXT("Act %d"), DWORD(n & 0xFFFFFFFF) + 1);
							HTREEITEM h = m_ctv.AddItem(hItem, str.c_str(), MAKELONG(LOWORD(n), i));
							if ( !hSelItem )
								hSelItem = h;

						}
					}
				}

				m_ctv.SetCurSel(hSelItem);
				m_ctv.cSendMessage(TVM_EXPAND, TVE_EXPAND, (LPARAM) hSelItem);

				SetFocus(m_ctv);
			}

			// InvalidateRect(*m_pCanvas, NULL, TRUE);
			m_pCanvas->SetCursorSet(0, RGB(255, 255, 255), 32, 32, 32, 32);
			m_pCanvas->SetActiveCursor(0);
			m_pCanvas->GetActiveCursor().Visible(TRUE);

			m_pCanvas->SetCursorSet(1, RGB(120, 250, 200), 16, 16, 1, 1);						
		}
	}
}

VOID CMainWindow::Ctl_OnSave()
{
	if ( !m_File.IsFileLoaded() )
		return;

	//ShowError(TEXT("No implemented yet"));
	//return;

	if ( !m_nEditor.StorGame() )
	{
		ShowError(TEXT("Game saving failed"));
		return;
	}

	if ( !m_File.SaveFile() )
		ShowErrorF(TEXT("Unable to save file '%s'.\nPossible access error"), 
		PathFindFileName( ((tstring) m_File).c_str()));
	else
		ShowMessageF(TEXT("File '%s' saved."), 
		PathFindFileName( ((tstring) m_File).c_str()));

}

VOID CMainWindow::Ctl_OnChangeLayer(USHORT uCmd)
{
	switch(uCmd)
	{
	case ID_LAYER_BLOCKSLAYER: m_pCanvas->SetActiveCursor(0); break;
	case ID_LAYER_OBJECTSLAYER: m_pCanvas->SetActiveCursor(1); break;
	}
	m_pCanvas->GetActiveCursor().Visible(TRUE);

	HMENU hMenu = GetSubMenu(GetSubMenu(GetMenu(*this), 1), 1);

	int count = GetMenuItemCount(hMenu);
	for(int i = 0; i < count; ++i)
	{
		if ( GetMenuItemID(hMenu, i) != uCmd )
			CheckMenuItem(hMenu, i, MF_BYPOSITION | MF_UNCHECKED);
		else
			CheckMenuItem(hMenu, i, MF_BYPOSITION | MF_CHECKED);
	}
}

VOID CMainWindow::Ctl_OnPwdTool()
{
	if ( !m_File.IsFileLoaded() )
		return;

	NES_PWD_DECRYPT_DATA pwd = { 0 };
	CPwdToolDlg dlg(GetInstance());
	
	m_nEditor.Get_PwdDecryptData(pwd);
	dlg.Let_PwdDecryptData(pwd);
	dlg.Show(this);
}

VOID CMainWindow::Ctl_OnSprInfo()
{
	if ( !m_File.IsFileLoaded() )
		return;

	std::vector<CNesObject> vList;
	m_nEditor.Get_SprList(vList);

	CSprInfoDlg dlg(GetInstance(), m_nEditor);

	dlg.Let_Objects(vList);

	dlg.Show(this);
}


INT_PTR CMainWindow::OnNotify(LPNMHDR lpnm)
{
	switch(lpnm->idFrom)
	{
	case 0x10:
		{
			if ( TVN_SELCHANGED == lpnm->code && m_File.IsFileLoaded() )
			{
				LPARAM l = m_ctv.Param(m_ctv.GetCurSel());
				INT level = HIWORD(l), act = LOWORD(l);
				if ( act != 0xFFFF )
				{
					
					m_nEditor.SelectLevel(level, act);
					
					BOOL fDirection = m_nEditor.GetActDirection(), fBoss = m_nEditor.IsActBoss();
					size_t count = m_nEditor.GetRoomsCount();
					const int room_height = ( fDirection || fBoss ? NES_ROOM_HEIGHT + 2 : NES_ROOM_HEIGHT );
					m_pCanvas->SetArea(
						32 * NES_ROOM_WIDTH * ( fDirection ? 1 : UINT(count) ),
						32 * ( room_height * ( !fDirection ? 1 : UINT(count) ) - 
						( fDirection ? 2 : 0 ) )
						);

					m_bCatchedItem = 0;
					m_catchedObject.fObjectCatched = FALSE;

					DrawCurrentLevel();
					m_pCanvas->SetActiveCursor(m_pCanvas->GetActiveCursorId());
				}
			}
			break;
		}
	case 0x1010:
		{
			switch(lpnm->code)
			{
			case CVN_REQMODIFY: ReqMdf((PCVNREQMODIFY) lpnm);
			case CVN_REQPOS: return ReqPos((PCVNHEADER) lpnm);
			case CVN_POSCHANGED: ShowStat(); break;
			}
			break;
		}
	}
	return 0;
}

VOID CMainWindow::Ctl_OnShowSprites()
{
	m_fShowSprites = !m_fShowSprites;

	UINT uCheck = ( MF_BYCOMMAND | ( m_fShowSprites ? MF_CHECKED : MF_UNCHECKED ) );
	HMENU hMenu = GetSubMenu(GetMenu(*this), 1);
	CheckMenuItem(hMenu, ID_VIEW_SHOWSPRITES, uCheck);
	if ( m_File.IsFileLoaded() )
		DrawCurrentLevel();
}

VOID CMainWindow::DrawCurrentLevel()
{
	m_nEditor.DrawLevel(*m_pCanvas, m_fShowSprites);
	InvalidateRect(*m_pCanvas, NULL, TRUE);
}

VOID CMainWindow::ShowStat()
{
	tstring status;
	INT id = m_pCanvas->GetActiveCursorId();
	if ( -1 == id )
		return;

	POINT pt = m_pCanvas->GetActiveCursor().Pos();
	switch(id)
	{
	case 0:
		{
			status.append(255, 0);
			_stprintf_s(&status[0], status.length(), TEXT("%d:%d - 0x%02X"), pt.x, pt.y, m_nEditor.Get_Block(pt.x, pt.y));
			break;
		}
	case 1:
		{
			std::vector<NES_OBJECT> vObjects;
			BYTE bRoomId = 0, bSelected = 0;
			POINT ptInRoom = { 0 };

			if ( m_nEditor.Get_RoomObjectsByPos(pt.x, pt.y, bRoomId, vObjects, ptInRoom, bSelected) )
			{
				status.append(255, 0);
				if ( bSelected != 0xff )
				{
					POINT ptObj = { vObjects[bSelected].X, vObjects[bSelected].Y };
					if ( m_nEditor.GetActDirection() )
					{
						ptObj.y = vObjects[bSelected].X;
						ptObj.x = vObjects[bSelected].Y;
					}

					_stprintf_s(&status[0], status.length(), TEXT("Object: %02X%01X, Slot: %02X [%d:%d]"), 
						vObjects[bSelected].id, vObjects[bSelected].timer, vObjects[bSelected].slot, ptObj.x, ptObj.y);
				}
				else
				{
					_stprintf_s(&status[0], status.length(), TEXT("No object [%d:%d]"), pt.x % 256, pt.y % 256);
				}

				status = status.c_str();

				tstring slots = TEXT("Used slots: ");
				size_t count = vObjects.size();
				BYTE bSlots[16] = { 0 };

				for(size_t n = 0; n < count; ++n)
					bSlots[vObjects[n].slot] = 1;

				for(int n = 0; n < sizeof(bSlots); ++n)
				{
					if ( bSlots[n] )
					{
						TCHAR pszNum[8] = { 0 };
						_stprintf_s(pszNum, TEXT("%01X"), n);
						slots += pszNum;
						slots += TEXT(" ");
					}
				}

				status += TEXT(". ") + slots;
			}

			break;
		}
	}

	m_cStatus.cSendMessage(SB_SETTEXT, 0, (LPARAM) status.c_str());
}


INT_PTR CMainWindow::ReqPos(PCVNHEADER pcvn)
{
	switch(pcvn->id)
	{
	case 0: return ReqPosBlocks(pcvn);
	case 1: return ReqPosObjects(pcvn);
	}

	return 0;
}

VOID CMainWindow::ReqMdf(PCVNREQMODIFY pcvn)
{
	switch(pcvn->cvnh.id)
	{
	case 0: ReqMdfBlocks(pcvn); break;
	case 1: ReqMdfObjects(pcvn); break;
	}
}

INT_PTR CMainWindow::ReqPosBlocks(PCVNHEADER pcvn)
{
	return 0;
}

VOID CMainWindow::ReqMdfBlocks(PCVNREQMODIFY pcvn)
{
	if ( pcvn->delta )
	{
		std::vector<NES_BLOCK> vblocks;
		m_nEditor.Get_Blocks(vblocks);
				
		int block = m_nEditor.Get_Block(pcvn->cvnh.pt.x, pcvn->cvnh.pt.y) + pcvn->delta;
		if ( block >= int(vblocks.size()) )
			block = 0;
		else if ( block < 0 )
			block = int(vblocks.size()) - 1;

		m_nEditor.Let_Block(pcvn->cvnh.pt.x, pcvn->cvnh.pt.y, LOBYTE(block));
		DrawCurrentLevel();
		ShowStat();
	}
	else if ( pcvn->vKey == VK_INSERT )
	{
		std::vector<CBitmap*> vpbmImages;

		m_nEditor.Get_BlocksImages(vpbmImages);
		BYTE block = m_nEditor.Get_Block(pcvn->cvnh.pt.x, pcvn->cvnh.pt.y);
		CBlocksListDlg dlg(GetInstance());
		dlg.Let_Blocks(vpbmImages, block);
		
		if ( dlg.Show(this) )
		{
			dlg.Get_Block(block);
			m_nEditor.Let_Block(pcvn->cvnh.pt.x, pcvn->cvnh.pt.y, block);
			DrawCurrentLevel();
			ShowStat();
		}
	}
	else if ( pcvn->vKey == VK_SPACE )
	{
		if ( HIWORD(GetKeyState(VK_CONTROL)) )
		{
			m_bCatchedItem = m_nEditor.Get_Block(pcvn->cvnh.pt.x, pcvn->cvnh.pt.y);
		}
		else
		{
			m_nEditor.Let_Block(pcvn->cvnh.pt.x, pcvn->cvnh.pt.y, m_bCatchedItem);
			DrawCurrentLevel();
			ShowStat();
		}
	}
}

INT_PTR CMainWindow::ReqPosObjects(PCVNHEADER pcvn)
{
	std::vector<NES_OBJECT> vObjects;
	BYTE bRoomId = 0, bSelected = 0;
	POINT ptInRoom = { 0 };

	if ( m_nEditor.Get_RoomObjectsByPos(pcvn->pt.x, pcvn->pt.y, bRoomId, vObjects, ptInRoom, bSelected) )
	{
		if ( bSelected != 0xff )
			m_pCanvas->GetActiveCursor().Modify(RGB(250, 200, 120));
		else
			m_pCanvas->GetActiveCursor().Modify(RGB(120, 250, 200));
	}
	else
		return 1;

	return 0;
}

VOID CMainWindow::ReqMdfObjects(PCVNREQMODIFY pcvn)
{
	std::vector<NES_OBJECT> vObjects;
	BYTE bRoomId = 0, bSelected = 0;
	POINT ptInRoom = { 0 };
	BOOL fShift = HIWORD(GetKeyState(VK_SHIFT)), fCtrl = HIWORD(GetKeyState(VK_CONTROL));

	if ( m_nEditor.Get_RoomObjectsByPos(pcvn->cvnh.pt.x, pcvn->cvnh.pt.y, bRoomId, vObjects, ptInRoom, bSelected) )
	{
		if ( bSelected != 0xFF )
		{
			NES_OBJECT & vObject = vObjects[bSelected];

			if ( pcvn->delta )
			{
				if ( fShift )
				{
					int slot = int(vObject.slot) + pcvn->delta;
					
					while(slot < 0 )
						slot += 0x10;
				
					while(slot >= 0x10 )
						slot -= 0x10;

					if ( !slot && pcvn->delta < 0 )
						slot = 0x0f;
					else if ( !slot && pcvn->delta > 0 )
						slot = 1;					

					vObject.slot = LOBYTE(slot);
					m_nEditor.Let_RoomObjects(bRoomId, vObjects);					 
				}
				else
				{
					int param = vObject.timer, id = vObject.id;

					param += pcvn->delta;
					while(param < 0)
					{
						param += 0x10;
						id--;
					}

					while(param >= 0x10 )
					{
						param -= 0x10;
						id++;
					}

					while(id < 0)
						id += NES_COUNT_OBJECTS;

					while(id >= NES_COUNT_OBJECTS)
						id -= NES_COUNT_OBJECTS;

					vObject.timer = LOBYTE(param);
					vObject.id = LOBYTE(id);
					m_nEditor.Let_RoomObjects(bRoomId, vObjects);
					DrawCurrentLevel();
				}
			}
			else if ( pcvn->vKey == VK_DELETE )
			{
				if ( Confirm(TEXT("Are you sure that you want to delete selected object?")) )
				{
					vObjects.erase(vObjects.begin() + bSelected);
					m_nEditor.Let_RoomObjects(bRoomId, vObjects);
					DrawCurrentLevel();
				}
			}
			else if ( pcvn->vKey == VK_SPACE )
			{
				if ( fCtrl && !m_catchedObject.fObjectCatched )
				{
					m_catchedObject.fObjectCatched = TRUE;
					m_catchedObject.vObject = vObjects[bSelected];
					vObjects.erase(vObjects.begin() + bSelected);
					m_nEditor.Let_RoomObjects(bRoomId, vObjects);
					DrawCurrentLevel();
				}
			}			
		}

		if ( pcvn->vKey == VK_SPACE && !fCtrl && m_catchedObject.fObjectCatched )
		{
			m_catchedObject.fObjectCatched = FALSE;
			if ( !m_nEditor.GetActDirection() )
			{
				m_catchedObject.vObject.X = (pcvn->cvnh.pt.x % 0x100);
				m_catchedObject.vObject.Y = (pcvn->cvnh.pt.y % 0x100);
			}
			else
			{
				m_catchedObject.vObject.Y = (pcvn->cvnh.pt.x % 0x100);
				m_catchedObject.vObject.X = (pcvn->cvnh.pt.y % 0x100);
			}

			vObjects.push_back(m_catchedObject.vObject);
			m_nEditor.Let_RoomObjects(bRoomId, vObjects);
			DrawCurrentLevel();
		}
		else if ( pcvn->vKey == VK_INSERT )
		{
			CObjectEditorDlg dlg(GetInstance(), m_nEditor);
			if ( dlg.Show(this) )
			{
				NES_OBJECT nObject;
				dlg.Get_Object(nObject);
				
				if ( !m_nEditor.GetActDirection() )
				{
					nObject.X = (pcvn->cvnh.pt.x % 0x100);
					nObject.Y = (pcvn->cvnh.pt.y % 0x100);
				}
				else
				{
					nObject.Y = (pcvn->cvnh.pt.x % 0x100);
					nObject.X = (pcvn->cvnh.pt.y % 0x100);
				}
				vObjects.push_back(nObject);
				m_nEditor.Let_RoomObjects(bRoomId, vObjects);
				DrawCurrentLevel();
			}
		}
		ShowStat();
	}
}
