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

CNesCanvasCursor::CNesCanvasCursor(COLORREF clr, INT width, INT height, INT x_delta, INT y_delta, BYTE bAlpha)
	: m_fVisible( FALSE ), m_bAlpha( 200 )
{
	Create(clr, width, height, x_delta, y_delta, bAlpha);
}

CNesCanvasCursor::CNesCanvasCursor(CNesCanvasCursor & curs)
{
	if ( &curs == this )
		return;

	this->m_bAlpha = curs.m_bAlpha;
	this->m_bmImage = curs.m_bmImage;
	this->m_delta = curs.m_delta;
	this->m_fVisible = curs.m_fVisible;
	this->m_pt = curs.m_pt;
}

CNesCanvasCursor::CNesCanvasCursor()
	: m_fVisible( FALSE ), m_bAlpha( 200 )
{
	Create(RGB(255, 255, 255), 10, 10, 10, 10);
}

VOID CNesCanvasCursor::Create(COLORREF clr, INT width, INT height, INT x_delta, INT y_delta, BYTE bAlpha)
{
	m_pt.x = m_pt.y = 0;
	if ( x_delta <= 0 || y_delta <= 0 )
		throw std::exception("invalid cursor data");

	m_bmImage.Create(width, height);
	m_delta.cx = x_delta; m_delta.cy = y_delta;
	m_bAlpha = bAlpha;
	m_bmImage.FillRect(0, 0, width, height, clr);
}

VOID CNesCanvasCursor::Modify(COLORREF clr, INT width, INT height, INT x_delta, INT y_delta, BYTE bAlpha)
{
	if ( width < 0 )
		width = m_bmImage.Width();
	
	if ( height < 0 )
		height = m_bmImage.Height();
	
	m_bmImage.Create(width, height);
	
	if ( x_delta > 0 )
		m_delta.cx = x_delta; 

	if ( y_delta > 0 )
		m_delta.cy = y_delta;

	m_bAlpha = bAlpha;	
	m_bmImage.FillRect(0, 0, width, height, clr);
}

POINT CNesCanvasCursor::Pos()
{
	return m_pt;
}

POINT CNesCanvasCursor::ScreenToCursor(INT x, INT y)
{
	POINT pt = { x / m_delta.cx, y / m_delta.cy };
	return pt;
}

POINT CNesCanvasCursor::CursorToScreen()
{
	POINT pt = { m_pt.x * m_delta.cx, m_pt.y * m_delta.cy };
	return pt;
}

VOID CNesCanvasCursor::Pos(POINT pt)
{
	m_pt = pt;
}

VOID CNesCanvasCursor::DrawCursor(HDC hDC)
{
	if ( !m_fVisible )
		return;

	POINT pt = CursorToScreen();
	BLENDFUNCTION bf = { 0 };
	bf.AlphaFormat = AC_SRC_OVER;
	bf.SourceConstantAlpha = m_bAlpha;
	AlphaBlend(hDC, pt.x, pt.y, m_bmImage.Width(), m_bmImage.Height(),
		m_bmImage, 0, 0, m_bmImage.Width(), m_bmImage.Height(), bf);
}

SIZE CNesCanvasCursor::Size()
{
	SIZE sz = { m_bmImage.Width(), m_bmImage.Height() };
	return sz;
}


BOOL CNesCanvasCursor::Visible()
{
	return m_fVisible;
}

VOID CNesCanvasCursor::Visible(BOOL fVisible)
{
	m_fVisible = fVisible;
}

POINT CNesCanvasCursor::CursorToScreen(INT x, INT y)
{
	POINT pt = { x * m_delta.cx, y * m_delta.cy };
	return pt;
}

POINT CNesCanvasCursor::GetNextPoint(INT x, INT y)
{
	POINT pt = { m_pt.x + x, m_pt.y + y };
	return pt;
}

// --

CNesCanvas::CNesCanvas(CREATESTRUCT & cs, HWND hWnd)
	: CCustomControl(cs, hWnd), m_bmCanvas(GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN))
{
	FlushDefault();
	m_curs.active = -1;
	SetCursorSet(0, 0, 1, 1, 1, 1);
	SetActiveCursor(0);
	GetActiveCursor().Visible(FALSE);
}

VOID CNesCanvas::Register(HINSTANCE hInstance)
{
	CCustomControl::Register(TEXT("SysImage32"), hInstance, CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW, NULL, LoadCursor(NULL, IDC_ARROW), NULL);
}

CNesCanvas::~CNesCanvas()
{
	
}

BOOL CNesCanvas::OnCreate(LPCREATESTRUCT lpcs)
{
	m_hwndParent = lpcs->hwndParent;
	m_scroll.Assign(*this);
	m_scroll.ScrollTo(0, 0);
	SetTimer(*this, 1, 300, NULL);
	return FALSE;
}

VOID CNesCanvas::OnDestroy()
{
	KillTimer(*this, 1);
}

VOID CNesCanvas::OnPaint(HDC hDC, BOOL fErase, PRECT prc)
{
	OnEraseBg(hDC);
}

VOID CNesCanvas::OnGotFocus(HWND hWnd)
{
	InvalidateRect(*this, NULL, TRUE);
}

VOID CNesCanvas::OnLostFocus(HWND hWnd)
{
	InvalidateRect(*this, NULL, TRUE);
}

VOID CNesCanvas::OnSize(INT dwState, USHORT cx, USHORT cy)
{
	m_scroll.UpdateScroll();
}

VOID CNesCanvas::OnSizing(INT dwState, USHORT cx, USHORT cy)
{
	OnSize(dwState, cx, cy);
}


VOID CNesCanvas::OnEraseBg(HDC hDC)
{
	RECT rc = { 0 };
	GetClientRect(*this, &rc);

	RECT rcArea = m_scroll.GetClientArea();

	BitBlt(m_bmCanvas, 0, 0, m_bmWorkArea.Width(), m_bmWorkArea.Height(), m_bmWorkArea, 0, 0, SRCCOPY);

	if ( m_curs.fVisible && m_curs.cursors.find( m_curs.active ) != m_curs.cursors.end() && InFocus() )
	{
		POINT pt = GetActiveCursor().CursorToScreen();
		if ( pt.x < m_szArea.cx && pt.y < m_szArea.cy )
			m_curs.cursors[m_curs.active].DrawCursor(m_bmCanvas);
	}

	BitBlt(hDC, 0, 0, m_bmCanvas.Width(), m_bmCanvas.Height(), m_bmCanvas,
		( m_szArea.cx < rc.right ? 0 : rcArea.left ),
		( m_szArea.cy < rc.bottom ? 0 : rcArea.top ),
		SRCCOPY);

	m_bmCanvas.FreeDC();
	m_bmWorkArea.FreeDC();
}

LRESULT CNesCanvas::OnDlgCode(DWORD vKey, LPMSG lpmsg)
{
	return DLGC_WANTARROWS | DLGC_WANTCHARS;
}

CNesCanvas::operator HDC()
{
	return m_bmWorkArea;
}

VOID CNesCanvas::OnTimer(DWORD_PTR idTimer, FARPROC pTimerProc)
{
	m_curs.fVisible = !m_curs.fVisible;
	InvalidateRect(*this, NULL, TRUE);
}

VOID CNesCanvas::FlushDefault()
{
	m_bmCanvas.GradientFill(0, 0, m_bmCanvas.Width(), m_bmCanvas.Height(), 0x00E6A17A, 0x00D67563, GRADIENT_FILL_RECT_V);
}

VOID CNesCanvas::OnScroll(UINT vScrollType, USHORT uPos, USHORT uRequest, HWND hCtl)
{
	RECT rc = { 0 };
	GetClientRect(*this, &rc);

	if ( vScrollType == WM_VSCROLL && rc.bottom < m_szArea.cy ||
		 vScrollType == WM_HSCROLL && rc.right < m_szArea.cx )
	{
		m_scroll.ScrollEvent(vScrollType, MAKELONG(uRequest, uPos));
		InvalidateRect(*this, NULL, TRUE);
	}
}

VOID CNesCanvas::SetArea(UINT cx, UINT cy)
{
	m_szArea.cx = cx; m_szArea.cy = cy;
	SIZE szScreen = { GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN) };

	m_bmWorkArea.Create(m_szArea.cx, m_szArea.cy);
	m_bmCanvas.Create(max(m_szArea.cx, szScreen.cx), max(m_szArea.cy, szScreen.cy));
	FlushDefault();
	m_scroll.SetScrollArea(cx, cy);
	m_scroll.ScrollTo(0, 0);
	InvalidateRect(*this, NULL, TRUE);
}

CNesCanvasCursor & CNesCanvas::GetActiveCursor()
{
	if ( m_curs.cursors.find(m_curs.active) == m_curs.cursors.end() )
		throw std::exception("no such cursor");

	return m_curs.cursors[ m_curs.active ];
}

INT CNesCanvas::GetActiveCursorId()
{
	return m_curs.active;
}

VOID CNesCanvas::SetActiveCursor(INT id)
{
	if ( m_curs.cursors.find(id) == m_curs.cursors.end() )
		return;

	m_curs.active = id;
	RequestPos( GetActiveCursor().Pos() );
}

VOID CNesCanvas::SetCursorSet(INT id, COLORREF clr, INT width, INT height, INT x_delta, INT y_delta)
{
	if ( m_curs.cursors.find(id) != m_curs.cursors.end() )
		m_curs.cursors.erase( m_curs.cursors.find(id ) );

	CNesCanvasCursor curs(clr, width, height, x_delta, y_delta);
	m_curs.cursors[id] = curs;
}

VOID CNesCanvas::OnKeyEvent(DWORD vEvent, DWORD vKey, DWORD vScanCode)
{
	if ( m_curs.active == -1 )
		return;

	if ( !GetActiveCursor().Visible() )
		return;

	CNesCanvasCursor & curs = GetActiveCursor();

	if ( vEvent == WM_KEYDOWN )
	{
		POINT pt = { 0 };

		switch(vKey)
		{
		case VK_DOWN: pt = curs.GetNextPoint(0, 1); break;
		case VK_UP: pt = curs.GetNextPoint(0, -1); break;
		case VK_LEFT: pt = curs.GetNextPoint(-1, 0); break;
		case VK_RIGHT: pt = curs.GetNextPoint(1, 0); break;
		default: RequestModify(vKey); return;
		}

		RequestPos( curs.CursorToScreen( pt.x, pt.y ) );
	}
}

VOID CNesCanvas::OnMouseButton(MOUSEACTION ma, MOUSEBUTTON mb, UINT vKey, SHORT x, SHORT y)
{
	if ( m_curs.active == -1 )
		return;

	if ( !GetActiveCursor().Visible() )
		return;

	SetFocus(*this);

	if ( ma == maDown && mb == mbLeft )
	{
		RECT rc = { 0 };
		GetClientRect(*this, &rc);

		RECT rcArea = m_scroll.GetClientArea();

		POINT pt = { ( m_szArea.cx < rc.right ? 0 : rcArea.left ), ( m_szArea.cy < rc.bottom ? 0 : rcArea.top ) };
		pt.x += x; pt.y += y;
		RequestPos(pt);
	}
	else if ( ma == maDblClick && mb == mbLeft )
		OnKeyEvent(WM_KEYDOWN, VK_INSERT, 0);
}

VOID CNesCanvas::RequestPos(POINT pt)
{
	if ( pt.x < 0 || pt.y < 0 || pt.x >= m_szArea.cx || pt.y >= m_szArea.cy )
		return;

	CNesCanvasCursor & curs = GetActiveCursor();

	CVNHEADER cvnh = { 0 };
	cvnh.nm.code = CVN_REQPOS;
	cvnh.nm.hwndFrom = *this;
	cvnh.nm.idFrom = GetWindowLongPtr(*this, GWL_ID);
	cvnh.id = m_curs.active;
	cvnh.pt = curs.ScreenToCursor( pt.x, pt.y );

	if ( SendMessage(m_hwndParent, WM_NOTIFY, 0, (LPARAM) &cvnh) )
	{
		MessageBeep(MB_ICONERROR);
		return;
	}

	pt = curs.CursorToScreen(cvnh.pt.x, cvnh.pt.y);

	curs.Pos( curs.ScreenToCursor( pt.x, pt.y ) );

	cvnh.nm.code = CVN_POSCHANGED;
	SendMessage(m_hwndParent, WM_NOTIFY, 0, (LPARAM) &cvnh);

	RECT rc = { 0 };
	GetClientRect(*this, &rc);
	
	RECT rcArea = m_scroll.GetClientArea();
	POINT ptScroll = { ( m_szArea.cx < rc.right ? 0 : rcArea.left ), ( m_szArea.cy < rc.bottom ? 0 : rcArea.top ) };

	SIZE csz = GetActiveCursor().Size();

	if ( ptScroll.x > pt.x )
		m_scroll.ScrollTo(pt.x, ptScroll.y);
	else if ( ptScroll.y > pt.y )
		m_scroll.ScrollTo(ptScroll.x, pt.y);
	else if ( pt.x > ptScroll.x + rc.right - csz.cx )
		m_scroll.ScrollTo(ptScroll.x + csz.cx, ptScroll.y);
	else if ( pt.y > ptScroll.y + rc.bottom - csz.cy )
		m_scroll.ScrollTo(ptScroll.x, ptScroll.y + csz.cy);

	m_curs.fVisible = TRUE;
	InvalidateRect(*this, NULL, TRUE);
}

VOID CNesCanvas::RequestModify(DWORD vKey)
{
	CVNREQMODIFY cvnh = { 0 };
	cvnh.cvnh.nm.code = CVN_REQMODIFY;
	cvnh.cvnh.nm.hwndFrom = *this;
	cvnh.cvnh.nm.idFrom = GetWindowLongPtr(*this, GWL_ID);
	cvnh.cvnh.id = m_curs.active;
	cvnh.cvnh.pt = GetActiveCursor().Pos();
	cvnh.vKey = vKey;

	switch(vKey)
	{
	case VK_ADD:
	case VK_OEM_PLUS: cvnh.delta = 1; break;
		
	case VK_SUBTRACT:
	case VK_OEM_MINUS: cvnh.delta = -1; break;

	case VK_PRIOR: cvnh.delta = -32; break;
	case VK_NEXT: cvnh.delta = 32; break;
	}

	SendMessage(m_hwndParent, WM_NOTIFY, 0, (LPARAM) &cvnh);
}