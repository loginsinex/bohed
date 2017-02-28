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

#define		SPINVAL(x)				( dSendMessage((x), UDM_GETPOS) )
#define		SPINSET(x, a)			( dSendMessage((x), UDM_SETPOS, 0, MAKELONG((a), 0)) )
#define		SPINRANGE(x, a, b)		( dSendMessage((x), UDM_SETRANGE, 0, MAKELONG((a), (b))) )
#define		SPINERR(x)				( 0 != ( HIWORD(SPINVAL(x) ) ) )

#define			ANCHOR_LEFT_TOP		0
#define			ANCHOR_LEFT_BOTTOM	1
#define			ANCHOR_RIGHT_TOP	2
#define			ANCHOR_RIGHT_BOTTOM	3
#define			ANCHOR_FULL			4
#define			ANCHOR_LEFT			5
#define			ANCHOR_TOP			6
#define			ANCHOR_RIGHT		7
#define			ANCHOR_BOTTOM		8
#define			WM_GETCUSTOMINSTANCE	( WM_USER + 0x100 )

typedef enum _tagMOUSEBUTTON
{
	mbLeft,
	mbRight,
	mbMiddle,
	mbX
} MOUSEBUTTON, *PMOUSEBUTTON;

typedef enum _tagMOUSEACTION
{
	maDown,
	maUp,
	maDblClick
} MOUSEACTION, *PMOUSEACTION;

class CWindow;

class CControl
{
	HWND				m_hWnd;
	HWND				m_hParent;
	HINSTANCE			m_hInstance;

	struct
	{
		USHORT			uId;
		tstring			sClass;
		tstring			sTitle;
		POINT			pt;
		SIZE			sz;
		RECT			rc;
		DWORD			dwStyle;
		DWORD			dwStyleEx;
		WORD			wAnchor;
		RECT			rcAnchor;
	} m_pre;

public:
	CControl(HINSTANCE hInstance);
	CControl();
	CControl(HINSTANCE hInstance, USHORT uId, 
		LPCTSTR pszClass, LPCTSTR pszTitle, 
		INT x, INT y, INT cx, INT cy,
		DWORD dwStyle, DWORD dwStyleEx = 0, WORD wAnchor = 0);

	VOID				Assign(HWND hCtl);
	HWND				Create(HWND hParent, USHORT uId, 
							int x, int y, int cx, int cy,
							LPCTSTR pszClass, LPCTSTR pszTitle,
							DWORD dwStyle, DWORD dwStyleEx = 0);

	HWND				Create(CWindow * pWnd);

	INT_PTR				cSendMessage(UINT uMsg, WPARAM wParam = NULL, LPARAM lParam = NULL);
	operator			HWND();
	
	VOID				Defer(HDWP hdwp, INT cx, INT cy);
	VOID				UpdateSize(INT cx, INT cy);

	VOID				Enable(BOOL fEnable);
	BOOL				Enable();
	VOID				Visible(BOOL fVisible);
	BOOL				Visible();

	tstring				Text();
	VOID				Text(tstring sText);
};

class CDialog;

class CWindow
{
	friend					CDialog;
	CWindow					*m_pParent;
	BOOL					m_fDialogMode;
	BOOL					m_fModal;
	BOOL					m_fExternal;
	BOOL					m_fInFocus;
	HINSTANCE				m_hInstance;
	HWND					m_hWnd;
	tstring					m_sClass;
	LONG_PTR				m_idRes;
	LPARAM					m_lDlgParam;

	HBRUSH					m_hbgBrush;
	std::vector<CControl*>	m_vCtl;
	CFont					m_fntDefault;
	CControl				m_cDefaultOk;
	CControl				m_cDefaultCancel;

	static INT_PTR CALLBACK SysDialogProc(HWND, UINT, WPARAM, LPARAM);
	LRESULT				WindowProc(UINT, WPARAM, LPARAM);

	BOOL				InternalOnNCCreate(LPCREATESTRUCT lpcs);
	BOOL				InternalOnCreate(LPCREATESTRUCT lpcs);
	BOOL				InternalOnInit();
	VOID				InternalOnPaint(WPARAM, LPARAM);
	VOID				InternalOnClose();
	VOID				InternalOnSize(WPARAM wParam, LPARAM lParam);
	VOID				InternalOnSizing(WPARAM wParam, LPARAM lParam);
	VOID				InternalSizeChanged(USHORT cx, USHORT cy);
	INT_PTR				InternalOnNotify(LPNMHDR lpnm);
	VOID				InternalOnCommand(USHORT uCmd, USHORT uId, HWND hCtl);
	VOID				InternalOnMouseAction(UINT uMsg, WPARAM wParam, LPARAM lParam);
	VOID				InternalOnFocus(UINT uMsg, HWND hWnd);	
	VOID				InternalOnScroll(UINT uMsg, WPARAM wParam, LPARAM lParam);
	tstring				ShellFileDialog(BOOL fOpenFile, LPCTSTR pszDefaultFilename, std::vector<tstring> & vExtensions);
	CWindow(HINSTANCE, LONG_PTR pszResource);

protected:
	CWindow(CREATESTRUCT lpcs, HWND hWnd);
	static LRESULT CALLBACK SysWindowProc(HWND, UINT, WPARAM, LPARAM);
	static LRESULT		CreateExternal(HWND hWnd, LPCREATESTRUCT lpcs, CWindow * This);
	tstring				MB_GetString(INT id);
	ATOM				Register(DWORD style, HICON hIcon = NULL, HCURSOR hCursor = NULL, HBRUSH hBg = NULL);
	static ATOM			Register(HINSTANCE hInstance, DWORD style, WNDPROC lpfnCustomProc, tstring sClass, HICON hIcon = NULL, HCURSOR hCursor = NULL, HBRUSH hBg = NULL);
	virtual	BOOL		OnInit(LPARAM lParam);
	virtual BOOL		OnNCCreate(LPCREATESTRUCT lpcs);
	virtual BOOL		OnCreate(LPCREATESTRUCT lpcs);
	virtual LRESULT		OnMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & fHandle);
	virtual VOID		OnDestroy();
	virtual VOID		OnNCDestroy();
	virtual VOID		OnPaint(HDC hDC, BOOL fErase, PRECT prc);
	virtual VOID		OnEraseBg(HDC hDC);
	virtual BOOL		OnClose();
	virtual VOID		OnSize(INT dwState, USHORT cx, USHORT cy);
	virtual VOID		OnSizing(INT dwState, USHORT cx, USHORT cy);
	virtual INT_PTR		OnNotify(LPNMHDR lpnm);
	virtual VOID		OnButton(USHORT uId);
	virtual VOID		OnOK();
	virtual VOID		OnCancel();
	virtual VOID		OnCommand(USHORT uCmd, USHORT uId, HWND hCtl);
	virtual VOID		OnMouseButton(MOUSEACTION ma, MOUSEBUTTON mb, UINT vKey, SHORT x, SHORT y);
	virtual VOID		OnGotFocus(HWND hLostFocus);
	virtual VOID		OnLostFocus(HWND hGotFocus);
	virtual VOID		OnScroll(UINT vScrollType, USHORT uPos, USHORT uRequest, HWND hCtl);
	virtual VOID		OnTimer(DWORD_PTR idTimer, FARPROC pTimerProc);
	virtual VOID		OnMouseWheel(SHORT uDelta, USHORT vKey, SHORT x, SHORT y);
	virtual LRESULT		OnDlgCode(DWORD vKey, LPMSG lpmsg);
	virtual VOID		OnKeyEvent(DWORD vEvent, DWORD vKey, DWORD vScanCode);
	INT_PTR				dSendMessage(USHORT uId, UINT uMsg, WPARAM wParam = NULL, LPARAM lParam = NULL);
	INT_PTR				wSendMessage(UINT uMsg, WPARAM wParam = NULL, LPARAM lParam = NULL);

	HFONT				SetWndFont(HFONT hFont);

	VOID				pushctl(CControl & ctl);

	HWND				InternalCreate(DWORD dwStyle, DWORD dwStyleEx, LPCTSTR pszCaption, HWND hParent, USHORT uId);
	HWND				InternalCreate(DWORD dwStyle, DWORD dwStyleEx, LPCTSTR pszCaption, int x, int y, int cx, int cy, HWND hParent, USHORT uId);

	VOID				Close(INT_PTR uExitCode = 0);
	HINSTANCE			GetInstance();

	INT					MsgBox(LPCTSTR pszText, LPCTSTR pszCaption, UINT uType);
	VOID				ShowMessage(LPCTSTR pszText);
	VOID				ShowMessageF(LPCTSTR pszText, ...);
	VOID				ShowAlert(LPCTSTR pszText);
	VOID				ShowAlertF(LPCTSTR pszText, ...);
	VOID				ShowError(LPCTSTR pszText);
	VOID				ShowErrorF(LPCTSTR pszText, ...);
	BOOL				Confirm(LPCTSTR pszText, BOOL fDefaultNo = FALSE);
	BOOL				ConfirmF(LPCTSTR pszText, BOOL fDefaultNo, ...);

	tstring				OpenFile(LPCTSTR pszDefaultFilename, ...);
	tstring				SaveFile(LPCTSTR pszDefailtFilename, ...);

public:
	CWindow(HINSTANCE, tstring sClass, BOOL fAddDefaultButtons = FALSE);
	virtual				~CWindow();

	BOOL				InFocus();
	LRESULT				Show(CWindow * pParent = NULL, LPARAM lParam = 0);
	HWND				Create(CWindow * pParent = NULL, LPARAM lParam = 0);
	HWND				Create(DWORD dwStyle, DWORD dwStyleEx, LPCTSTR pszCaption, CWindow * pParent, USHORT uId);
	HWND				Create(DWORD dwStyle, DWORD dwStyleEx, LPCTSTR pszCaption, int x, int y, int cx, int cy, CWindow * pParent, USHORT uId);

	CWindow *			Parent();
	operator			HWND();
	VOID				Visible(BOOL fVisible);
	BOOL				Visible();
	VOID				Enable(BOOL fEnable);
	BOOL				Enable();

	VOID				EnableAll(BOOL fEnable, ...);
	VOID				ShowAll(BOOL fVisible, ...);
	HWND				Ctl(INT id);
};

class CDialog: public CWindow
{

public:
	CDialog(HINSTANCE hInstance, LPCTSTR pszResource);

};

template<class T> class CCustomControl: public CWindow
{
	static LRESULT CALLBACK SysWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch(uMsg)
		{
		case WM_NCCREATE:
				return CWindow::CreateExternal(hWnd, (LPCREATESTRUCT) lParam, new T(*((LPCREATESTRUCT) lParam), hWnd));
		default:
				return CWindow::SysWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}

	virtual VOID	OnCancel() { return; }	// do nothing

protected:
	CCustomControl(CREATESTRUCT & cs, HWND hWnd)
		: CWindow(cs, hWnd) { }

	static VOID Register(tstring sClassName, HINSTANCE hInstance, DWORD style, HICON hIcon = NULL, HCURSOR hCursor = NULL, HBRUSH hBg = NULL)
	{
		CWindow::Register(hInstance, style, CCustomControl<T>::SysWindowProc, sClassName, hIcon, hCursor, hBg);
	}
};