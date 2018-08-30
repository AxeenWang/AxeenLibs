/**************************************************************************//**
 * @file	wframe_define.hh
 * @brief	Win32 Frame library 先行編譯檔
 * @date	2018-03-31
 * @date	2018-07-24
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_WIN32FRAME_DEFINE_HH__
#define __AXEEN_WIN32FRAME_DEFINE_HH__
#include "axeen/axeen_setup.hh"
#include "axeen/axeen_ement.hh"
#include "wframe_struct.hh"

// 導入 Windows Library
// #if defined(__WINDOWS__) && !defined(_LIB) || defined(_CONSOLE)
#if defined(__WINDOWS__) && !defined(__LIB__)
	// Windows 作業系統 引用 library
	#pragma comment(lib, "kernel32.lib")
	#pragma comment(lib, "user32.lib")
	#pragma comment(lib, "gdi32.lib")
	#pragma comment(lib, "winspool.lib")
	#pragma comment(lib, "comdlg32.lib")
	#pragma comment(lib, "advapi32.lib")
	#pragma comment(lib, "shell32.lib")
	#pragma comment(lib, "ole32.lib")
	#pragma comment(lib, "oleaut32.lib")
	#pragma comment(lib, "uuid.lib")
	#pragma comment(lib, "odbc32.lib")
	#pragma comment(lib, "odbccp32.lib")

	#pragma comment(lib, "comctl32.lib")
	#pragma comment(lib, "winmm.lib")
	#pragma comment(lib, "shlwapi.lib")

	// win32frame library
	#ifdef __WIN64__
	#	if defined(_DEBUG)
	#		pragma comment(lib, "win32frame64d.lib")
	#	else
	#		pragma comment(lib, "win32frame64.lib")
	#	endif
	#else
	#	if defined(_DEBUG)
	#		pragma comment(lib, "win32frame32d.lib")
	#	else
	#		pragma comment(lib, "win32frame32.lib")
	#	endif
	#endif
#endif

#endif // !__AXEEN_WIN32FRAME_DEFINE_HH__
