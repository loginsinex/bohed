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

#pragma once

#pragma comment(linker, \
    "\"/manifestdependency:type='Win32' "\
    "name='Microsoft.Windows.Common-Controls' "\
    "version='6.0.0.0' "\
    "processorArchitecture='*' "\
    "publicKeyToken='6595b64144ccf1df' "\
    "language='*'\"")


#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <WindowsX.h>
#include <CommCtrl.h>
#include <CommDlg.h>

inline void * __cdecl operator new(size_t size) 
{ 
	PVOID pParam = GlobalAlloc(GMEM_ZEROINIT | GMEM_FIXED, size);
	
	if ( !pParam )
		FatalAppExit(0, TEXT("Can't allocate memory\n\nProgram will abnormal closed"));
	return (void *) pParam;
}

inline void __cdecl operator delete(void *ptr) 
{ 
	GlobalFree(ptr);
}

inline void __cdecl operator delete[](void *ptr) 
{ 
	GlobalFree(ptr);
}

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <map>
#include <string>
#include <Resource.h>

#ifdef UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

// TODO: reference additional headers your program requires here
#ifdef _WIN64
#ifndef GWL_HINSTANCE
#define GWL_HINSTANCE GWLP_HINSTANCE
#endif

#ifndef GWL_WNDPROC
#define GWL_WNDPROC GWLP_WNDPROC
#endif

#ifndef GWL_HWNDPARENT
#define GWL_HWNDPARENT GWLP_HWNDPARENT
#endif

#ifndef GWL_USERDATA
#define GWL_USERDATA GWLP_USERDATA
#endif

#ifndef GWL_ID
#define GWL_ID GWLP_ID
#endif

#ifndef DWL_MSGRESULT
#define DWL_MSGRESULT DWLP_MSGRESULT
#endif

#ifndef DWL_USER
#define DWL_USER DWLP_USER
#endif

#endif

#ifndef _DEBUG
#undef _tprintf
#define _tprintf(...)
#endif

#include "GUI\Wrapper\CBitmap.h"
#include "GUI\Wrapper\CFont.h"
#include "GUI\Wrapper\CWindow.h"
#include "GUI\Wrapper\Controls\CScroll.h"
#include "GUI\Wrapper\Controls\ctreeview.h"
#include "GUI\Wrapper\Controls\CListView.h"

#include "NES\CNesFile.h"
#include "NES\CNesObject.h"
#include "NES\CNesEditor.h"
#include "GUI\Canvas\CNesCanvas.h"

#include "GUI\CObjectEditorDlg.h"
#include "GUI\csprinfodlg.h"
#include "GUI\cpwdtooldlg.h"
#include "GUI\CBlocksListDlg.h"
#include "GUI\CMainWindow.h"
