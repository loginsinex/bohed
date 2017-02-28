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

#define		CVN_FIRST				( -900 )
#define		CVN_REQPOS				( CVN_FIRST - 1 )
#define		CVN_REQMODIFY			( CVN_FIRST - 2 )
#define		CVN_POSCHANGED			( CVN_FIRST - 3 )

typedef struct _tagCVNHEADER
{
	NMHDR		nm;
	POINT		pt;
	INT			id;
} CVNHEADER, *PCVNHEADER;

typedef struct _tagCVNREQMODIFY
{
	CVNHEADER		cvnh;
	DWORD			vKey;
	INT				delta;
} CVNREQMODIFY, *PCVNREQMODIFY; 

class CNesCanvasCursor
{
	CBitmap				m_bmImage;
	POINT				m_pt;
	SIZE				m_delta;
	BYTE				m_bAlpha;
	BOOL				m_fVisible;

public:
	CNesCanvasCursor(CNesCanvasCursor & curs);
	CNesCanvasCursor();
	CNesCanvasCursor(COLORREF clr, INT width, INT height, INT x_delta, INT y_delta, BYTE bAplha = 200);

	VOID				Create(COLORREF clr, INT width, INT height, INT x_delta, INT y_delta, BYTE bAplha = 200);
	VOID				Modify(COLORREF clr, INT width = -1, INT height = -1, INT x_delta = -1, INT y_delta = -1, BYTE bAplha = 200);

	POINT				Pos();
	POINT				ScreenToCursor(INT x, INT y);
	POINT				CursorToScreen();
	POINT				CursorToScreen(INT x, INT y);
	VOID				Pos(POINT pt);
	POINT				GetNextPoint(INT x, INT y);
	SIZE				Size();
	
	VOID				DrawCursor(HDC hDC);
	BOOL				Visible();
	VOID				Visible(BOOL fVisible);
};

class CNesCanvas: public CCustomControl<CNesCanvas>
{
	CBitmap							m_bmCanvas;
	CBitmap							m_bmWorkArea;
	CScroll							m_scroll;
	HWND							m_hwndParent;

	struct
	{
		std::map<INT, CNesCanvasCursor>	cursors;
		INT								active;
		BOOL							fVisible;
	} m_curs;
	
	SIZE			m_szArea;

	VOID			OnPaint(HDC hDC, BOOL fErase, PRECT prc);
	VOID			OnEraseBg(HDC hDC);
	VOID			OnTimer(DWORD_PTR idTimer, FARPROC pTimerProc);

	VOID			OnGotFocus(HWND hWnd);
	VOID			OnLostFocus(HWND hWnd);
	VOID			OnScroll(UINT vScrollType, USHORT uPos, USHORT uRequest, HWND hCtl);
	BOOL			OnCreate(LPCREATESTRUCT lpcs);
	VOID			OnDestroy();
	VOID			OnSize(INT dwState, USHORT cx, USHORT cy);
	VOID			OnSizing(INT dwState, USHORT cx, USHORT cy);
	LRESULT			OnDlgCode(DWORD vKey, LPMSG lpmsg);
	VOID			OnKeyEvent(DWORD vEvent, DWORD vKey, DWORD vScanCode);
	VOID			OnMouseButton(MOUSEACTION ma, MOUSEBUTTON mb, UINT vKey, SHORT x, SHORT y);

	VOID			RequestPos(POINT pt);
	VOID			RequestModify(DWORD vKey);

	CNesCanvas(CREATESTRUCT & cs, HWND hWnd);
	~CNesCanvas();

public:
	static VOID		Register(HINSTANCE hInstance);

	operator HDC();
	VOID			FlushDefault();

	VOID			SetArea(UINT cx, UINT cy);

	CNesCanvasCursor &	GetActiveCursor();
	INT				GetActiveCursorId();
	VOID			SetActiveCursor(INT id);
	VOID			SetCursorSet(INT id, COLORREF clr, INT width, INT height, INT x_delta, INT y_delta);

	friend CCustomControl<CNesCanvas>;
};