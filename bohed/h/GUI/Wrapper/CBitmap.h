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

#define XCHGCOLORREF(_x)              ((((_x)&0xFF00FF00L)|(((_x)&0x00FF0000L)>>16)|(((_x)&0x000000FFL)<<16)))

class CBitmap
{
	struct
	{
		HDC						hDCDesktop;
		HDC						hDC;
		RGBQUAD *				pvBuffer;
		HBITMAP					hBitmap;
		HBITMAP					hDefaultBitmap;
		SIZE					sz;
		UINT					uSize;
		std::vector<RGBQUAD*>	vLines;
		BOOL					fLocked;
	} m_buffer;


	BOOL					CreateFromResource(HINSTANCE hInstance, LPCTSTR pszResource);
	VOID					Destroy();

public:
	CBitmap();
	CBitmap(CBitmap & bm);
	CBitmap(INT cx, INT cy);
	CBitmap(HINSTANCE hInstance, LPCTSTR pszResource);
	~CBitmap();

	VOID						Create(INT cx, INT cy);
	RGBQUAD *					Bits();
	RGBQUAD *					operator[](int cy);
	CBitmap &					operator=(CBitmap & bm);
	operator HDC();
	VOID						FreeDC();
	HDC							LockDC();
	HBITMAP						Bitmap();
	INT							Width();
	INT							Height();

	HBRUSH						CreateBrush();

	VOID						FillRect(int x, int y, int cx, int cy, COLORREF clr, BYTE bAlpha = 0);
	VOID						PremultiplyAlpha();
	VOID						RenderBitmap(CBitmap & bmSrc, int x, int y, int cx, int cy, int dest_x, int dest_y, BYTE bAlpha = 255, BOOL fUseSourceAlpha = FALSE);
	VOID						RenderBitmap(HDC hDC, int x, int y, int cx, int cy, int dest_x, int dest_y, BYTE bAlpha = 255, BOOL fUseSourceAlpha = FALSE);
	VOID						GradientFill(INT x, INT y, INT cx, INT cy, COLORREF crColor1, COLORREF crColor2, DWORD dwFlags);
	VOID						GradientFillEx(INT x, INT y, INT cx, INT cy, COLORREF crColor1, COLORREF crColor2, BYTE bAlpha1, BYTE bAlpha2, DWORD dwFlags);
	VOID						RenderText(INT x, INT y, INT cx, INT cy, LPTSTR pszText, HFONT hFont, BOOL bTransparent, COLORREF crTextColor, COLORREF crBackColor, DWORD dwFlags);

};