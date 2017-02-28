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

CBitmap::CBitmap()
{
	m_buffer.hDC = m_buffer.hDCDesktop = NULL;
	m_buffer.hBitmap = m_buffer.hDefaultBitmap = NULL;
	m_buffer.pvBuffer = NULL;
	m_buffer.sz.cx = m_buffer.sz.cy = 0;
	m_buffer.uSize = 0;
	m_buffer.fLocked = FALSE;
}

CBitmap::CBitmap(INT cx, INT cy)
{
	m_buffer.fLocked = FALSE;
	if ( cx <= 0 || cy <= 0 )
		throw tstring(TEXT("Invalid size"));

	Create(cx, cy);
}

CBitmap::CBitmap(CBitmap & bm)
{
	this->operator=(bm);
}

CBitmap::CBitmap(HINSTANCE hInstance, LPCTSTR pszResource)
{
	m_buffer.fLocked = FALSE;
	if ( !CreateFromResource(hInstance, pszResource) )
		throw tstring(TEXT("Invalid bitmap resource"));
}

CBitmap & CBitmap::operator=(CBitmap & bm)
{
	if ( &bm == this )
		return bm;

	Create(bm.m_buffer.sz.cx, bm.m_buffer.sz.cy);
	CopyMemory(Bits(), bm.Bits(), m_buffer.uSize);
	return *this;
}

BOOL CBitmap::CreateFromResource(HINSTANCE hInstance, LPCTSTR lpBitmapName)
{
	HRSRC hRes = FindResource( hInstance, lpBitmapName, (LPCTSTR) RT_BITMAP);
	if ( hRes )
	{
		DWORD uSize = SizeofResource( hInstance, hRes );
		HGLOBAL hData = LoadResource( hInstance, hRes );
		if ( hData )
		{
			PVOID pvBits = LockResource( hData );
			PVOID pvBmpBits = PBYTE( pvBits ) + 40;
			INT x = 0, y = 0, bppxl = 0;
			x			= ((LPDWORD) pvBits)[1];
			y			= ((LPDWORD) pvBits)[2];
			bppxl		= ((USHORT*) pvBits)[7];


			if ( 32 == bppxl )
			{
				Create( x, y );

				if ( m_buffer.uSize > 0 )
				{
					RGBQUAD * pvBuffer = Bits();
					for(int i = 0; i < y; ++i)
						CopyMemory(&pvBuffer[i*x], &((RGBQUAD*) pvBmpBits)[(y - i - 1)*x], x * sizeof(RGBQUAD));
					return TRUE;
				}
			}
		}
	}

	return FALSE;
}


CBitmap::~CBitmap()
{
	Destroy();
}

VOID CBitmap::Create(INT cx, INT cy)
{
	Destroy();
	m_buffer.hDCDesktop = GetDC(GetDesktopWindow());
	m_buffer.hDC = CreateCompatibleDC(m_buffer.hDC);
	
	UINT uSize = m_buffer.uSize = sizeof(RGBQUAD)*cx*cy;

	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(bmi);
	bmi.bmiHeader.biWidth = cx;
	bmi.bmiHeader.biHeight = -cy;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = uSize;

	m_buffer.hBitmap = CreateDIBSection( m_buffer.hDC, &bmi, DIB_RGB_COLORS, (PVOID*) &m_buffer.pvBuffer, NULL, 0 );

	if ( !m_buffer.hBitmap )
		throw tstring(TEXT("Bitmap creation failed"));

	m_buffer.sz.cx = cx;
	m_buffer.sz.cy = cy;

	m_buffer.vLines.clear();
	for(int i = 0; i < m_buffer.sz.cy; ++i)
		m_buffer.vLines.push_back(&m_buffer.pvBuffer[ m_buffer.sz.cx * i ]);
}

VOID CBitmap::Destroy()
{
	if ( m_buffer.uSize )
	{
		FreeDC();
		DeleteObject(m_buffer.hBitmap);
		DeleteDC(m_buffer.hDC);
		ReleaseDC(GetDesktopWindow(), m_buffer.hDCDesktop);

		m_buffer.hDC = m_buffer.hDCDesktop = NULL;
		m_buffer.hBitmap = m_buffer.hDefaultBitmap = NULL;
		m_buffer.pvBuffer = NULL;
		m_buffer.sz.cx = m_buffer.sz.cy = 0;
		m_buffer.uSize = 0;
		m_buffer.vLines.clear();
	}
}

VOID CBitmap::FreeDC()
{
	if ( m_buffer.fLocked )
	{
		SelectObject(m_buffer.hDC, m_buffer.hDefaultBitmap);
		m_buffer.fLocked = FALSE;
	}
}

HDC CBitmap::LockDC()
{
	if ( !m_buffer.fLocked )
	{
		m_buffer.hDefaultBitmap = (HBITMAP) SelectObject(m_buffer.hDC, m_buffer.hBitmap);
		m_buffer.fLocked = TRUE;
	}

	return m_buffer.hDC;
}

RGBQUAD * CBitmap::Bits()
{
	FreeDC();
	return m_buffer.pvBuffer;
}

RGBQUAD * CBitmap::operator[](int cy)
{
	return m_buffer.vLines[cy];
}

CBitmap::operator HDC()
{
	GdiFlush();
	return LockDC();
}

HBITMAP CBitmap::Bitmap()
{
	INT cx = m_buffer.sz.cx, cy = m_buffer.sz.cy, uSize = sizeof(RGBQUAD) * cx * cy;
	PVOID pvBuffer = NULL;

	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(bmi);
	bmi.bmiHeader.biWidth = cx;
	bmi.bmiHeader.biHeight = -cy;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = uSize;

	HBITMAP hBitmap = CreateDIBSection( m_buffer.hDC, &bmi, DIB_RGB_COLORS, (PVOID*) &pvBuffer, NULL, 0 );
	if ( hBitmap )
	{
		CopyMemory(pvBuffer, Bits(), uSize);
		return hBitmap;
	}

	return NULL;
}

INT CBitmap::Width()
{
	return m_buffer.sz.cx;
}

INT CBitmap::Height()
{
	return m_buffer.sz.cy;
}

VOID CBitmap::FillRect(int x, int y, int cx, int cy, COLORREF clr, BYTE bAlpha)
{
	RECT rc = { x, y, x + cx, y + cy };
	HBRUSH hBrush = CreateSolidBrush(clr);
	::FillRect(*this, &rc, hBrush);
	DeleteBrush(hBrush);

	RGBQUAD * pvBuffer = Bits();

	if ( bAlpha > 0 )
		for(UINT i = 0; i < m_buffer.uSize; ++i)
			pvBuffer[i].rgbReserved = bAlpha;
}

VOID CBitmap::PremultiplyAlpha()
{
	BOOL fLocked = m_buffer.fLocked;
	FreeDC();
	for(UINT i = 0; i < m_buffer.uSize; ++i)
	{
		RGBQUAD & w = m_buffer.pvBuffer[i];
		w.rgbBlue = (BYTE) ( int(w.rgbReserved) * int(w.rgbBlue) / 255 );
		w.rgbGreen = (BYTE) ( int(w.rgbReserved) * int(w.rgbGreen) / 255 );
		w.rgbRed = (BYTE) ( int(w.rgbReserved) * int(w.rgbRed) / 255 );
	}

	if ( fLocked )
		LockDC();
}


VOID CBitmap::RenderBitmap(CBitmap & bmSrc, int x, int y, int cx, int cy, int dest_x, int dest_y, BYTE bAlpha, BOOL fUseSourceAlpha)
{
	BLENDFUNCTION bf = { 0 };
	bf.AlphaFormat = ( fUseSourceAlpha ? AC_SRC_ALPHA : 0 );
	bf.BlendOp = AC_SRC_OVER;
	bf.SourceConstantAlpha = bAlpha;

	AlphaBlend(*this, dest_x, dest_y, cx, cy, bmSrc, x, y, cx, cy, bf);
}


VOID CBitmap::RenderBitmap(HDC hDC, int x, int y, int cx, int cy, int dest_x, int dest_y, BYTE bAlpha, BOOL fUseSourceAlpha)
{
	BLENDFUNCTION bf = { 0 };
	bf.AlphaFormat = ( fUseSourceAlpha ? AC_SRC_ALPHA : 0 );
	bf.BlendOp = AC_SRC_OVER;
	bf.SourceConstantAlpha = bAlpha;

	AlphaBlend(hDC, dest_x, dest_y, cx, cy, *this, x, y, cx, cy, bf);
}

VOID CBitmap::GradientFill(INT x, INT y, INT cx, INT cy, COLORREF crColor1, COLORREF crColor2, DWORD dwFlags)
{
	if (!m_buffer.uSize) return;		// return if bitmap was not created
	GradientFillEx(x, y, cx, cy, crColor1, crColor2, 255, 255, dwFlags);
}

VOID CBitmap::GradientFillEx(INT x, INT y, INT cx, INT cy, COLORREF crColor1, COLORREF crColor2, BYTE bAlpha1, BYTE bAlpha2, DWORD dwFlags)
{
	if (!m_buffer.uSize) return;		// return if bitmap was not created

	TRIVERTEX tvi[2] = { 0 };
	GRADIENT_RECT grc = { 0 };
	tvi[0].Alpha = WORD(bAlpha1) << 8;
	tvi[0].Red = GetRValue(crColor1) << 8;
	tvi[0].Green = GetGValue(crColor1) << 8;
	tvi[0].Blue = GetBValue(crColor1) << 8;
	tvi[0].x = x;
	tvi[0].y = y;
	
	tvi[1].Alpha = WORD(bAlpha1) << 8;
	tvi[1].Red = GetRValue(crColor2) << 8;
	tvi[1].Green = GetGValue(crColor2) << 8;
	tvi[1].Blue = GetBValue(crColor2) << 8;
	tvi[1].x = x + cx;
	tvi[1].y = y + cy;

	grc.UpperLeft = 0; grc.LowerRight = 1;
	::GdiGradientFill(*this, tvi, 2, &grc, 1, dwFlags);
}

HBRUSH CBitmap::CreateBrush()
{
	return CreatePatternBrush(m_buffer.hBitmap);
}

VOID CBitmap::RenderText(INT x, INT y, INT cx, INT cy, LPTSTR pszText, HFONT hFont, BOOL bTransparent, COLORREF crTextColor, COLORREF crBackColor, DWORD dwFlags)
{
	if (!m_buffer.uSize) return;		// return if bitmap was not created

	INT iright = x+cx,ibottom = y+cy;

	int bkMode = GetBkMode( *this );
	COLORREF clrText = GetTextColor( *this );
	COLORREF clrBg = GetBkColor( *this );
	HGDIOBJ hfntOld = SelectObject( *this, hFont );

	SetBkMode( *this,  bTransparent ? TRANSPARENT : OPAQUE );
	SetTextColor( *this, crTextColor );
	SetBkColor( *this, crBackColor );
	RECT rc = { x, y, x + cx, y + cy };

	DrawText( *this, pszText, lstrlen(pszText), &rc, dwFlags);

	SetBkMode( *this,  bkMode );
	SetTextColor( *this, clrText );
	SetBkColor( *this, clrBg );
	SelectObject( *this, hfntOld );

	GdiFlush();
}
