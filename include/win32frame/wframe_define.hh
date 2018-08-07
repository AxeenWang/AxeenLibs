/**************************************************************************//**
 * @file	wframe_define.hh
 * @brief	Win32 Frame library 先行編譯檔
 * @date	2018-03-31
 * @date	2018-07-24
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_WIN32FRAME_DEFINE_HH__
#define __AXEEN_WIN32FRAME_DEFINE_HH__
#include "axeen/axeen_ement.hh"
#include "wframe_struct.hh"

#ifndef __WINVER__
#define	__WINVER__	0x0601	//!< 預設 Windows 7
#endif

#ifndef __IEEVER__
#define __IEEVER__	0x0900	//!< 預設 IE 9.0
#endif

// 導入 Windows Library
#if defined(__WINDOWS__) && !defined(_LIB) || defined(_CONSOLE)
	// 作業系統 library
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
