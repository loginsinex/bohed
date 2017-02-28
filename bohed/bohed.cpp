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
#include "bohed.h"


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	CNesCanvas::Register(hInstance);

	INT_PTR retval = 0;
	CMainWindow wnd(hInstance);

	wnd.Create(WS_CAPTION | WS_SIZEBOX | WS_BORDER | WS_DLGFRAME | WS_OVERLAPPEDWINDOW | WS_SYSMENU | WS_CLIPCHILDREN,
		0, TEXT("Bucky O'Hare level editor"), NULL, 0);

	if ( wnd )
	{
		ShowWindow(wnd, nCmdShow);
		UpdateWindow(wnd);

		HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BOHED));
		MSG msg = { 0 };

		do
		{
			int ret = GetMessage(&msg, NULL, 0, 0);
			if ( !ret || -1 == ret || !IsWindow(wnd))
				break;

			if ( !TranslateAccelerator(wnd, hAccel, &msg) )
			{
				if ( !IsDialogMessage(wnd, &msg) )
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		} while(TRUE);

		retval = msg.wParam;
	}

	return (INT) retval;
}

int main(int argc, char ** argv)
{
	return _tWinMain(GetModuleHandle(NULL), NULL, GetCommandLine(), SW_SHOW);
}