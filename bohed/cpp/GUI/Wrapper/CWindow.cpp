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
#include <atlstr.h>

CControl::CControl(HINSTANCE hInstance)
	: m_hInstance( hInstance ), m_hWnd( NULL ), m_hParent( NULL )
{
	m_pre.uId = 0; 
	ZeroMemory(&m_pre.pt, sizeof(m_pre.pt));
	ZeroMemory(&m_pre.sz, sizeof(m_pre.sz));
	ZeroMemory(&m_pre.rcAnchor, sizeof(m_pre.rcAnchor));
	m_pre.dwStyle = m_pre.dwStyleEx = 0;
	m_pre.wAnchor = 0;
}

CControl::CControl()
	: m_hInstance( NULL ), m_hWnd( NULL ), m_hParent( NULL )
{
	m_pre.uId = 0; 
	ZeroMemory(&m_pre.pt, sizeof(m_pre.pt));
	ZeroMemory(&m_pre.sz, sizeof(m_pre.sz));
	ZeroMemory(&m_pre.rcAnchor, sizeof(m_pre.rcAnchor));
	m_pre.dwStyle = m_pre.dwStyleEx = 0;
	m_pre.wAnchor = 0;
}

CControl::CControl(HINSTANCE hInstance, USHORT uId, 
		LPCTSTR pszClass, LPCTSTR pszTitle, 
		INT x, INT y, INT cx, INT cy,
		DWORD dwStyle, DWORD dwStyleEx, WORD wAnchor)
		: m_hInstance( hInstance ), m_hWnd( NULL ), m_hParent( NULL )
{
	m_pre.uId = uId;
	m_pre.sClass = ( pszClass ? pszClass : TEXT("") );
	m_pre.sTitle = ( pszTitle ? pszTitle : TEXT("") );
	m_pre.pt.x = x; m_pre.pt.y = y;
	m_pre.sz.cx = cx; m_pre.sz.cy = cy;
	m_pre.dwStyle = dwStyle; m_pre.dwStyleEx = dwStyleEx;
	m_pre.wAnchor = wAnchor;
}


VOID CControl::Assign(HWND hCtl)
{
	if ( !IsWindow(hCtl) || !( GetWindowLongPtr(hCtl, GWL_STYLE) & WS_CHILD ) )
		return;

	m_hWnd = hCtl;
	m_hInstance = (HINSTANCE) GetWindowLongPtr(m_hWnd, GWL_HINSTANCE);
}

HWND CControl::Create(HWND hParent, USHORT uId, 
							int x, int y, int cx, int cy,
							LPCTSTR pszClass, LPCTSTR pszTitle,
							DWORD dwStyle, DWORD dwStyleEx)
{
	if ( !IsWindow(hParent) )
		return NULL;

	m_hParent = hParent;
	m_hWnd = CreateWindowEx(dwStyleEx, pszClass, pszTitle, dwStyle | WS_CHILD, x, y, cx, cy, hParent, (HMENU) uId, m_hInstance, NULL); 
	return m_hWnd;
}

HWND CControl::Create(CWindow * pWnd)
{
	if ( !pWnd )
		return NULL;

	HWND hParent = *pWnd;
	if ( !IsWindow(hParent) )
		return NULL;

	RECT rcw = { 0 };
	RECT rcc = m_pre.rc;

	RECT & rc = m_pre.rcAnchor;
	GetClientRect(hParent, &rcw);

	switch(m_pre.wAnchor)
	{
	case ANCHOR_LEFT_TOP: rc.left = rc.top = rc.right = rc.bottom = -1; break;
	case ANCHOR_LEFT_BOTTOM: rc.left = rc.right = -1; rc.top = rcw.bottom - rcc.top; rc.bottom = rcw.bottom - rcc.bottom; break;
	case ANCHOR_RIGHT_TOP: rc.left = rcw.right - rcc.left; rc.right = rcw.right - rcc.right; rc.top = rc.bottom = -1; break;
	case ANCHOR_RIGHT_BOTTOM: 
		{
			rc.top = rcw.bottom - rcc.top; rc.bottom = rcw.bottom - rcc.bottom;
			rc.left = rcw.right - rcc.left; rc.right = rcw.right - rcc.right; 
			break;
		}
	case ANCHOR_FULL:
		{
			rc.left = rc.top = -1;
			rc.bottom = rcw.bottom - rcc.bottom;
			rc.right = rcw.right - rcc.right; 
			break;
		}
	case ANCHOR_LEFT:
		{
			rc.left = rc.top = rc.right = -1;
			rc.bottom = rcw.bottom - rcc.bottom;
			break;
		}
	case ANCHOR_TOP:
		{
			rc.left = rc.top = rc.bottom = -1;
			rc.right = rcw.right - rcc.right; 
			break;
		}
	case ANCHOR_RIGHT:
		{
			rc.top = rc.right = rc.bottom = -1;
			rc.left = rcw.right - rcc.left;
			break;
		}
	case ANCHOR_BOTTOM:
		{
			rc.left = rc.bottom = -1;
			rc.top = rcw.bottom - rcc.top; 
			rc.right = rcw.right - rcc.right; 
			break;
		}
	}

	return Create(hParent, 
		m_pre.uId, m_pre.rc.left, m_pre.rc.top, m_pre.rc.right - m_pre.rc.left, m_pre.rc.bottom - m_pre.rc.top, 
		m_pre.sClass.c_str(), m_pre.sTitle.c_str(), m_pre.dwStyle, m_pre.dwStyleEx);
}

VOID CControl::UpdateSize(INT cx, INT cy)
{
	if ( m_pre.pt.x < 0 )
		m_pre.rc.left = m_pre.pt.x + cx;
	else
		m_pre.rc.left = m_pre.pt.x;

	if ( m_pre.pt.y < 0 )
		m_pre.rc.top = m_pre.pt.y + cy;
	else
		m_pre.rc.top = m_pre.pt.y;

	if ( m_pre.sz.cx < 0 )
		m_pre.rc.right = ( cx + m_pre.sz.cx );
	else
		m_pre.rc.right = m_pre.rc.left + m_pre.sz.cx;

	if ( m_pre.sz.cy < 0 )
		m_pre.rc.bottom = ( cy + m_pre.sz.cy );
	else
		m_pre.rc.bottom = m_pre.rc.top + m_pre.sz.cy;
}

VOID CControl::Defer(HDWP hdwp, INT cx, INT cy)
{
	RECT & rc = m_pre.rcAnchor;
	RECT rcw = { 0, 0, cx, cy };
	RECT rcc = { 0 };
	GetClientRect(m_hParent, &rcw);

	if ( rc.left != -1 )
		rcc.left = rcw.right - rc.left;
	else
		rcc.left = m_pre.rc.left;

	if ( rc.top != -1 )
		rcc.top = rcw.bottom - rc.top;
	else
		rcc.top = m_pre.rc.top;

	if ( rc.right != -1 )
		rcc.right = rcw.right - rc.right;
	else
		rcc.right = m_pre.rc.right;

	if ( rc.bottom != -1 )
		rcc.bottom = rcw.bottom - rc.bottom;
	else
		rcc.bottom = m_pre.rc.bottom;

	DeferWindowPos(hdwp, *this, NULL, rcc.left, rcc.top, rcc.right - rcc.left, rcc.bottom - rcc.top, 0);
}

INT_PTR CControl::cSendMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return SendMessage(m_hWnd, uMsg, wParam, lParam);
}

CControl::operator HWND()
{
	return m_hWnd;
}

VOID CControl::Enable(BOOL fEnable)
{
	EnableWindow(*this, fEnable);
}

BOOL CControl::Enable()
{
	return IsWindowEnabled(*this);
}

VOID CControl::Visible(BOOL fVisible)
{
	ShowWindow(*this, ( fVisible ? SW_SHOW : SW_HIDE ));
}

BOOL CControl::Visible()
{
	return IsWindowVisible(*this);
}

tstring CControl::Text()
{
	INT_PTR len = cSendMessage(WM_GETTEXTLENGTH) + 1;
	tstring str;
	str.append(len, 0);
	cSendMessage(WM_GETTEXT, len + 1, (LPARAM) &str[0]);
	return str;
}

VOID CControl::Text(tstring sText)
{
	cSendMessage(WM_SETTEXT, 0, (LPARAM) sText.c_str());
}


// window

CDialog::CDialog(HINSTANCE hInstance, LPCTSTR pszResource)
	: CWindow(hInstance, (LONG_PTR) pszResource)
{

}


CWindow::CWindow(HINSTANCE hInstance, tstring sClass, BOOL fAddDefaultButtons)
	: m_hInstance(hInstance), m_sClass(sClass), m_hWnd(NULL), m_fDialogMode( FALSE ), m_fModal( FALSE ), m_idRes( 0 ), m_fExternal( FALSE ), m_pParent(NULL),
	m_fInFocus( FALSE ),
	m_cDefaultOk(hInstance, IDOK, WC_BUTTON, MB_GetString(IDOK - 1).c_str(), 
			-(10 + 75 + 10 + 75), -(10 + 25), 75, 25, WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 0, ANCHOR_RIGHT_BOTTOM),
	m_cDefaultCancel(hInstance, IDCANCEL, WC_BUTTON, MB_GetString(IDCANCEL - 1).c_str(), 
			-(10 + 75), -(10 + 25), 75, 25, WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON, 0, ANCHOR_RIGHT_BOTTOM)
{
	if ( fAddDefaultButtons )
	{
		pushctl(m_cDefaultCancel);
		pushctl(m_cDefaultOk);
	}
}

CWindow::CWindow(HINSTANCE hInstance, LONG_PTR idRes)
	: m_hInstance(hInstance), m_hWnd(NULL), m_fDialogMode( TRUE ), m_idRes( idRes ), m_fModal( FALSE ), m_fExternal( FALSE ), m_pParent(NULL),
	m_fInFocus( FALSE )
{

}

CWindow::CWindow(CREATESTRUCT cs, HWND hWnd)
	: m_hInstance(cs.hInstance), m_hWnd(hWnd), m_fDialogMode( FALSE ), m_idRes( 0 ), m_fModal( FALSE ), m_fExternal( TRUE ),
	m_fInFocus( FALSE )
{
	if ( cs.hwndParent )
	{
		m_pParent = (CWindow*) GetWindowLongPtr(cs.hwndParent, 4);
		m_sClass = ( cs.lpszClass ? cs.lpszClass : TEXT("") );
	}
}

CWindow::~CWindow()
{
	if ( m_hWnd )		// warning: window still not destroyed, but we cant call OnDestroy and OnNCDestroy at this point
	{
		DestroyWindow(m_hWnd);
	}
}

LRESULT CWindow::CreateExternal(HWND hWnd, LPCREATESTRUCT lpcs, CWindow * This)
{
	if ( This )
	{
		CREATESTRUCT cs = *lpcs;
		cs.lpCreateParams = This;
		if ( CWindow::SysWindowProc(hWnd, WM_NCCREATE, 0, (LPARAM) &cs) )
			return TRUE;

		delete This;
		This = NULL;
	}
	return FALSE;
}

LRESULT CALLBACK CWindow::SysWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if ( WM_NCCREATE == uMsg )
	{
		CWindow * This = (CWindow*) ((LPCREATESTRUCT) lParam)->lpCreateParams;
		if ( This )
		{
			This->m_hWnd = hWnd;
			if ( This->WindowProc(uMsg, wParam, lParam) )
			{
				SetWindowLongPtr(hWnd, 8, (LONG_PTR) This);
				return TRUE;
			}
			This->m_hWnd = NULL;
		}
		return FALSE;
	}
	else
	{
		CWindow * This = (CWindow*) GetWindowLongPtr(hWnd, 8);
		if ( This )
			return This->WindowProc(uMsg, wParam, lParam);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

INT_PTR CALLBACK CWindow::SysDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if ( WM_INITDIALOG == uMsg )
	{
		CWindow * This = (CWindow*) lParam;
		if ( This )
		{
			This->m_hWnd = hWnd;
			LRESULT lResult = This->WindowProc(uMsg, wParam, lParam);
			SetWindowLongPtr(hWnd, DWL_USER, (LONG_PTR) This);
			return lResult;
		}
		return FALSE;
	}
	else
	{
		CWindow * This = (CWindow*) GetWindowLongPtr(hWnd, DWL_USER);
		if ( This )
			return This->WindowProc(uMsg, wParam, lParam);
	}

	return 0;
}


LRESULT CWindow::WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_NCCREATE: return InternalOnNCCreate((LPCREATESTRUCT) lParam);
	case WM_CREATE: return InternalOnCreate((LPCREATESTRUCT) lParam);
	case WM_INITDIALOG: return InternalOnInit();
	case WM_DESTROY: OnDestroy(); break;
	case WM_PAINT: InternalOnPaint(wParam, lParam); break;
	case WM_CLOSE: InternalOnClose(); break;
	case WM_ERASEBKGND: OnEraseBg((HDC) wParam); break;
	case WM_SIZE: InternalOnSize(wParam, lParam); break;
	case WM_SIZING: InternalOnSizing(wParam, lParam); break;
	case WM_NOTIFY: return InternalOnNotify((LPNMHDR) lParam);
	case WM_COMMAND: InternalOnCommand(HIWORD(wParam), LOWORD(wParam), (HWND) lParam); break;
	case WM_GETCUSTOMINSTANCE: return (LRESULT) this;
	case WM_TIMER: OnTimer(wParam, (FARPROC) lParam); break;
	case WM_VSCROLL:
	case WM_HSCROLL: InternalOnScroll(uMsg, wParam, lParam); break;
	case WM_GETDLGCODE: return OnDlgCode((DWORD) wParam, (LPMSG) lParam);
	case WM_MOUSEWHEEL: OnMouseWheel(HIWORD(wParam), LOWORD(wParam), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); break;
	case WM_KEYDOWN:
	case WM_KEYUP: OnKeyEvent(uMsg, (DWORD) wParam, (DWORD) lParam); break;

	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MBUTTONDBLCLK:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_XBUTTONDBLCLK:
		{
			InternalOnMouseAction(uMsg, wParam, lParam);
			break;
		}
	case WM_SETFOCUS: 
	case WM_KILLFOCUS: InternalOnFocus(uMsg, (HWND) wParam); break;
	case WM_NCDESTROY:
		{
			OnNCDestroy();
			m_hWnd = NULL;
			m_pParent = NULL;
			if ( m_fExternal )
				delete this;

			return 0;
		}
	default:
		{
			BOOL fHandle = FALSE;
			LRESULT lRet = OnMessage(uMsg, wParam, lParam, fHandle);
			if ( fHandle )
				return lRet;
			
			return ( m_fDialogMode ? 0 : DefWindowProc(*this, uMsg, wParam, lParam) );
		}
	}

	return 0;
}

VOID CWindow::pushctl(CControl & ctl)
{
	m_vCtl.push_back(&ctl);	// store a pointer to control instead of control, because vector creates a new instance of control
}

BOOL CWindow::InternalOnNCCreate(LPCREATESTRUCT lpcs)
{
	WNDCLASS wc = { 0 };
	if ( GetClassInfo(m_hInstance, m_sClass.c_str(), &wc) )
		m_hbgBrush = wc.hbrBackground;
	else
		m_hbgBrush = GetStockBrush(BLACK_BRUSH);

	return OnNCCreate(lpcs);
}

BOOL CWindow::InternalOnCreate(LPCREATESTRUCT lpcs)
{
	size_t count = m_vCtl.size();
	RECT wrc = { 0 };
	GetClientRect(*this, &wrc);

	for(size_t n = 0; n < count; ++n)
	{
		m_vCtl[n]->UpdateSize(wrc.right - wrc.left, wrc.bottom - wrc.top);
		m_vCtl[n]->Create(this);
		SetWindowFont(*m_vCtl[n], m_fntDefault, TRUE);
	}

	return OnCreate(lpcs);
}

BOOL CWindow::InternalOnInit()
{
	return OnInit(m_lDlgParam);
}

VOID CWindow::InternalOnPaint(WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps = { 0 };
	HDC hDC = BeginPaint(*this, &ps);
	if ( hDC )
	{
		OnPaint(hDC, ps.fErase, &ps.rcPaint);
		EndPaint(*this, &ps);
	}
}

VOID CWindow::InternalOnClose()
{
	if ( OnClose() )
		Close();
}

VOID CWindow::InternalOnSize(WPARAM wParam, LPARAM lParam)
{
	USHORT cx = GET_X_LPARAM(lParam), cy = GET_Y_LPARAM(lParam);
	InternalSizeChanged(cx, cy);
	OnSize((INT) wParam, cx, cy);
}

VOID CWindow::InternalOnSizing(WPARAM wParam, LPARAM lParam)
{
	RECT & rc = *((PRECT) lParam);
	USHORT cx = LOWORD(rc.right - rc.left), cy = LOWORD(rc.bottom - rc.top);
	InternalSizeChanged(cx, cy);
	OnSizing((INT) wParam, cx, cy);
}

VOID CWindow::InternalSizeChanged(USHORT cx, USHORT cy)
{
	size_t count = m_vCtl.size();

	HDWP hdwp = BeginDeferWindowPos((int) count);
	for(size_t n = 0; n < count; ++n)
		m_vCtl[n]->Defer(hdwp, cx, cy);

	EndDeferWindowPos(hdwp);
}

INT_PTR CWindow::InternalOnNotify(LPNMHDR lpnm)
{
	INT_PTR ret = OnNotify(lpnm);
	SetWindowLongPtr(*this, DWL_MSGRESULT, ret);
	return ret;
}

VOID CWindow::InternalOnCommand(USHORT uCmd, USHORT uId, HWND hCtl)
{
	switch(uCmd)
	{
	case BN_CLICKED:
		{
			switch(uId)
			{
			case IDOK: OnOK(); break;
			case IDCANCEL: OnCancel(); break;
			default: OnButton(uId); break;
			}
			break;
		}
	default: OnCommand(uCmd, uId, hCtl);
	}
}

VOID CWindow::InternalOnMouseAction(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	MOUSEACTION ma;
	MOUSEBUTTON mb;
	switch(uMsg)
	{
	case WM_LBUTTONDOWN:		ma = maDown; mb = mbLeft; break;
	case WM_LBUTTONUP:			ma = maUp; mb = mbLeft; break;
	case WM_LBUTTONDBLCLK:		ma = maDblClick; mb = mbLeft; break;
	case WM_RBUTTONDOWN:		ma = maDown; mb = mbRight; break;
	case WM_RBUTTONUP:			ma = maUp; mb = mbRight; break;
	case WM_RBUTTONDBLCLK:		ma = maDblClick; mb = mbRight; break;
	case WM_MBUTTONDOWN:		ma = maDown; mb = mbMiddle; break;
	case WM_MBUTTONUP:			ma = maUp; mb = mbMiddle; break;
	case WM_MBUTTONDBLCLK:		ma = maDblClick; mb = mbMiddle; break;
	case WM_XBUTTONDOWN:		ma = maDown; mb = mbX; break;
	case WM_XBUTTONUP:			ma = maUp; mb = mbX; break;
	case WM_XBUTTONDBLCLK:		ma = maDblClick; mb = mbX; break;
	}

	OnMouseButton(ma, mb, (UINT) wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
}

VOID CWindow::InternalOnFocus(UINT uMsg, HWND hWnd)
{
	m_fInFocus = ( WM_SETFOCUS == uMsg );

	switch(uMsg)
	{
	case WM_SETFOCUS: OnGotFocus(hWnd); break;
	case WM_KILLFOCUS: OnLostFocus(hWnd); break;
	}
}

VOID CWindow::InternalOnScroll(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	OnScroll(uMsg, HIWORD(wParam), LOWORD(wParam), (HWND) lParam);
}

tstring CWindow::MB_GetString(INT wButton)
{
	LPCWSTR (WINAPI* mbgs)(UINT);

	*((PVOID*) &mbgs) = GetProcAddress(GetModuleHandle(TEXT("user32")), "MB_GetString");

	if ( mbgs )
		return mbgs(wButton);
	else
		return TEXT("");
}

BOOL CWindow::OnClose()
{
	return TRUE;
}

INT_PTR CWindow::dSendMessage(USHORT uId, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return SendDlgItemMessage(*this, uId, uMsg, wParam, lParam);
}

INT_PTR CWindow::wSendMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return SendMessage(*this, uMsg, wParam, lParam);
}

BOOL CWindow::OnNCCreate(LPCREATESTRUCT lpcs)
{
	return TRUE;
}

BOOL CWindow::OnCreate(LPCREATESTRUCT lpcs)
{
	return FALSE;
}

BOOL CWindow::OnInit(LPARAM lParam)
{
	return TRUE;
}

VOID CWindow::OnPaint(HDC hDC, BOOL fErase, PRECT prc)
{
	// do nothing
	return;
}

VOID CWindow::OnSize(INT dwState, USHORT cx, USHORT cy)
{
	return;
}

VOID CWindow::OnSizing(INT dwState, USHORT cx, USHORT cy)
{
	return;
}

VOID CWindow::OnEraseBg(HDC hDC)
{
	DefWindowProc(*this, WM_ERASEBKGND, (WPARAM) hDC, 0);
	return;
}

INT_PTR CWindow::OnNotify(LPNMHDR lpnm)
{
	return 0;
}

VOID CWindow::OnButton(USHORT uId)
{
	return;
}

VOID CWindow::OnMouseButton(MOUSEACTION ma, MOUSEBUTTON mb, UINT vKey, SHORT x, SHORT y)
{
	if ( mbLeft == mb && maDown == ma )
		SetFocus(*this);
}

VOID CWindow::OnOK()
{
	return;
}

VOID CWindow::OnCancel()
{
	Close(0);
}

VOID CWindow::OnCommand(USHORT uCmd, USHORT uId, HWND hCtl)
{
	return;
}

LRESULT CWindow::OnMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & fHandle)
{
	fHandle = FALSE;
	return 0;
}

VOID CWindow::OnDestroy()
{
	return;
}

VOID CWindow::OnGotFocus(HWND hLostFocus)
{

}

VOID CWindow::OnLostFocus(HWND hGotFocus)
{

}

VOID CWindow::OnScroll(UINT vScrollType, USHORT uPos, USHORT uRequest, HWND hCtl)
{
	return;
}

VOID CWindow::OnTimer(DWORD_PTR idTimer, FARPROC pTimerProc)
{
	return;
}

VOID CWindow::OnMouseWheel(SHORT uDelta, USHORT vKey, SHORT x, SHORT y)
{
	OnScroll(WM_VSCROLL, 0, ( uDelta < 0 ? SB_LINEDOWN : SB_LINEUP ), NULL);
}

VOID CWindow::OnNCDestroy()
{
	return;
}

LRESULT CWindow::OnDlgCode(DWORD vKey, LPMSG lpmsg)
{
	return 0;
}

VOID CWindow::OnKeyEvent(DWORD vEvent, DWORD vKey, DWORD vScanCode)
{
	return;
}


ATOM CWindow::Register(DWORD style, HICON hIcon, HCURSOR hCursor, HBRUSH hBg)
{
	return Register(m_hInstance, style, CWindow::SysWindowProc, m_sClass, hIcon, hCursor, hBg);
}

ATOM CWindow::Register(HINSTANCE hInstance, DWORD style, WNDPROC lpfnCustomProcm, tstring sClass, HICON hIcon, HCURSOR hCursor, HBRUSH hBg)
{
	WNDCLASS wc = { 0 };
	wc.style = style;
	wc.cbClsExtra = 16;
	wc.cbWndExtra = 16;
	wc.hbrBackground = hBg;
	wc.hCursor = hCursor;
	wc.hIcon = hIcon;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = lpfnCustomProcm;
	wc.lpszClassName = sClass.c_str();
	wc.lpszMenuName = NULL;
	return RegisterClass(&wc);
}

HWND CWindow::InternalCreate(DWORD dwStyle, DWORD dwStyleEx, LPCTSTR pszCaption, HWND hParent, USHORT uId)
{
	return InternalCreate(dwStyle, dwStyleEx, pszCaption, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hParent, uId);
}

HWND CWindow::InternalCreate(DWORD dwStyle, DWORD dwStyleEx, LPCTSTR pszCaption, int x, int y, int cx, int cy, HWND hParent, USHORT uId)
{
	m_fModal = FALSE;
	HWND hwnd = CreateWindowEx(dwStyleEx, m_sClass.c_str(), pszCaption, dwStyle, x, y, cx, cy, hParent, (HMENU) uId, m_hInstance, this);
	if ( hwnd )
	{
		SetWindowText(hwnd, pszCaption);
		return hwnd;
	}
	return NULL;
}

LRESULT CWindow::Show(CWindow * pParent, LPARAM lParam)
{
	if ( m_fDialogMode )	// can't modal for usual window
	{
		HWND hParent = ( pParent ? pParent->m_hWnd : NULL );
		m_pParent = pParent;
		m_fModal = TRUE;
		return DialogBoxParam(m_hInstance, (LPCTSTR) m_idRes, hParent, CWindow::SysDialogProc, (LPARAM) this);

	}
	return 0;
}

HWND CWindow::Create(CWindow * pParent, LPARAM lParam)
{
	HWND hParent = ( pParent ? pParent->m_hWnd : NULL );
	m_pParent = pParent;
	m_fModal = FALSE;

	if ( m_fDialogMode )
		return CreateDialogParam(m_hInstance, MAKEINTRESOURCE(m_idRes), hParent, CWindow::SysDialogProc, (LPARAM) this);
	else
	{
		if ( InternalCreate(WS_OVERLAPPEDWINDOW | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CAPTION | WS_DLGFRAME | WS_SYSMENU, 
		0, NULL, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hParent, 0) )
		{
			SetWindowLongPtr(*this, GWL_HWNDPARENT, (LONG) hParent);
			return *this;
		}
	}

	return NULL;
}

HWND CWindow::Create(DWORD dwStyle, DWORD dwStyleEx, LPCTSTR pszCaption, CWindow * pParent, USHORT uId)
{
	HWND hParent = ( pParent ? pParent->m_hWnd : NULL );
	m_pParent = pParent;
	return InternalCreate(dwStyle, dwStyleEx, pszCaption, hParent, 0);	
}

HWND CWindow::Create(DWORD dwStyle, DWORD dwStyleEx, LPCTSTR pszCaption, int x, int y, int cx, int cy, CWindow * pParent, USHORT uId)
{
	HWND hParent = ( pParent ? pParent->m_hWnd : NULL );
	m_pParent = pParent;
	return InternalCreate(dwStyle, dwStyleEx, pszCaption, x, y, cx, cy, hParent, 0);	
}

VOID CWindow::Close(INT_PTR uExitCode)
{
	if ( m_fModal )
		EndDialog(m_hWnd, uExitCode);
	else
		DestroyWindow(m_hWnd);
}

CWindow * CWindow::Parent()
{
	return m_pParent;
}

CWindow::operator HWND()
{
	return m_hWnd;
}

HFONT CWindow::SetWndFont(HFONT hFont)
{
	HFONT hPrev = (HFONT) wSendMessage(WM_GETFONT);
	SetWindowFont(*this, hFont, TRUE);
	return hPrev;
}

HINSTANCE CWindow::GetInstance()
{
	return m_hInstance;
}

INT CWindow::MsgBox(LPCTSTR pszText, LPCTSTR pszCaption, UINT uType)
{
	tstring sCaption;

	if ( !pszCaption )
	{
		int len = (int) wSendMessage(WM_GETTEXTLENGTH) + 1;
		if ( len > 0 )
		{
			sCaption.append(len + 1, 0);
			GetWindowText(*this, &sCaption[0], len);
		}
	}
	else
		sCaption = pszCaption;

	return MessageBox(*this, pszText, sCaption.c_str(), uType);
}

VOID CWindow::ShowMessage(LPCTSTR pszText)
{
	MsgBox(pszText, NULL, MB_ICONINFORMATION);
}

VOID CWindow::ShowMessageF(LPCTSTR pszText, ...)
{
	va_list argptr;
	CString msg;

	va_start(argptr, pszText);
	msg.FormatV(pszText, argptr);
	ShowMessage(msg);
	va_end(argptr);
}

VOID CWindow::ShowAlert(LPCTSTR pszText)
{
	MsgBox(pszText, NULL, MB_ICONWARNING);
}

VOID CWindow::ShowAlertF(LPCTSTR pszText, ...)
{
	va_list argptr;
	CString msg;

	va_start(argptr, pszText);
	msg.FormatV(pszText, argptr);
	ShowAlert(msg);
	va_end(argptr);
}

VOID CWindow::ShowError(LPCTSTR pszText)
{
	MsgBox(pszText, NULL, MB_ICONERROR);	
}

VOID CWindow::ShowErrorF(LPCTSTR pszText, ...)
{
	va_list argptr;
	CString msg;

	va_start(argptr, pszText);
	msg.FormatV(pszText, argptr);
	ShowError(msg);
	va_end(argptr);
}

BOOL CWindow::Confirm(LPCTSTR pszText, BOOL fDefaultNo)
{
	return ( IDYES == MsgBox(pszText, NULL, MB_ICONQUESTION | MB_YESNO | ( fDefaultNo ? MB_DEFBUTTON2 : 0 )) );
}

BOOL CWindow::ConfirmF(LPCTSTR pszText, BOOL fDefaultNo, ...)
{
	va_list argptr;
	CString msg;

	va_start(argptr, fDefaultNo);
	msg.FormatV(pszText, argptr);
	BOOL fResult = Confirm(msg, fDefaultNo);
	va_end(argptr);
	return fResult;
}

VOID CWindow::Enable(BOOL fEnable)
{
	EnableWindow(*this, fEnable);
}

BOOL CWindow::Enable()
{
	return IsWindowEnabled(*this);
}

VOID CWindow::Visible(BOOL fVisible)
{
	ShowWindow(*this, ( fVisible ? SW_SHOW : SW_HIDE ));
}

BOOL CWindow::Visible()
{
	return IsWindowVisible(*this);
}

VOID CWindow::EnableAll(BOOL fEnable, ...)
{
	va_list argptr;
	va_start(argptr, fEnable);

	for(int id = 0; argptr[id]; ++id)
		EnableWindow(GetDlgItem(*this, argptr[id]), fEnable);

	va_end(argptr);
}

VOID CWindow::ShowAll(BOOL fVisible, ...)
{
	va_list argptr;
	va_start(argptr, fVisible);

	int nCmd = ( fVisible ? SW_SHOW : SW_HIDE );

	for(int id = 0; argptr[id]; ++id)
		ShowWindow(Ctl(argptr[id]), nCmd);

	va_end(argptr);
}

HWND CWindow::Ctl(INT id)
{
	return GetDlgItem(*this, id);
}

BOOL CWindow::InFocus()
{
	return m_fInFocus;
}

tstring CWindow::ShellFileDialog(BOOL fOpenFile, LPCTSTR pszDefaultFilename, std::vector<tstring> & vExtensions)
{
	tstring pszFile = pszDefaultFilename;
	pszFile.append(MAX_PATH, 0);

	tstring szList;
	size_t count = vExtensions.size();
	for(size_t n = 0; n < count; ++n)
	{
		szList.append(vExtensions[n].begin(), vExtensions[n].end());
		szList.push_back(0);
	}
	szList.push_back(0);

	OPENFILENAME ofn = { 0 };

	ofn.lStructSize = sizeof(ofn);
	ofn.Flags = 
		( fOpenFile ?
			OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR | OFN_PATHMUSTEXIST :
			OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_NOCHANGEDIR | OFN_PATHMUSTEXIST
		);

	ofn.hInstance = GetInstance();
	ofn.hwndOwner = *this;
	ofn.lpstrFile = &pszFile[0];
	ofn.lpstrFilter = &szList[0];
	ofn.nMaxFile = (DWORD) pszFile.length();
	
	BOOL fResult = ( fOpenFile ? GetOpenFileName(&ofn) : GetSaveFileName(&ofn) );

	if ( fResult )
		return pszFile;
	
	return TEXT("");
}

tstring CWindow::OpenFile(LPCTSTR pszDefaultFilename, ...)
{
	va_list argptr;
	va_start(argptr, pszDefaultFilename);

	std::vector<tstring> vExt;

	for(int i = 0; argptr[0] != NULL; ++i)
		vExt.push_back(va_arg(argptr, LPCTSTR));

	return ShellFileDialog(TRUE, pszDefaultFilename, vExt);
}

tstring CWindow::SaveFile(LPCTSTR pszDefaultFilename, ...)
{
	va_list argptr;
	va_start(argptr, pszDefaultFilename);

	std::vector<tstring> vExt;

	for(int i = 0; argptr[i] != NULL; ++i)
		vExt.push_back(va_arg(argptr, LPCTSTR));

	return ShellFileDialog(FALSE, pszDefaultFilename, vExt);
}
