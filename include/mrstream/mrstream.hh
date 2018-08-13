/**************************************************************************//**
 * @file	mrstream_mrstream.hh
 * @brief	MRStream Dynamic Library - header of export function
 * @date	2018-08-01
 * @date	2018-08-01
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_MRSTREAM_MRSTREAM_HH__
#define __AXEEN_MRSTREAM_MRSTREAM_HH__

#ifndef __WINVER__
#define	__WINVER__			0x0601	//!< 使用 Windows 7 (含) 以後版本的特定功能。
#endif

#ifndef __IEEVER__
#define __IEEVER__			0x0900	//!< 使用 IE 9.0 (含) 以後版本的特定功能。
#endif

#ifndef __DLL_EXPORT__
#define	__DLL_EXPORT__		1		//!< 使用 EXPORTS, DLLAPI 前綴
#endif

#ifndef __XPP_STYLE__
#define __XPP_STYLE__		1		//<! 使用 XP-STYLE 編譯 具備 GUI 類型的的程式。
#endif

#include "axeen/axeen_ement.hh"
#include "mrstream_struct.hh"

#if defined(__cplusplus)
extern "C" {
#endif

	DLLEXPORT MRSRESULT	STDCALL MRStream_GetLastError();
	DLLEXPORT MRSRESULT	STDCALL MRStream_GetVersionText(LPTSTR szTextPtr, size_t cchMax);
	DLLEXPORT HMRSTREAM STDCALL MRStream_Carlist_Create (LPCTSTR szHostPtr, int nHostPort);
	DLLEXPORT MRSRESULT	STDCALL MRStream_Carlist_Release(HMRSTREAM* hMrsCarlistPtr);

#if defined(__cplusplus)
}
#endif

// 導入 MRStream Library
// #if defined(__WINDOWS__) && !defined(_LIB) || defined(_CONSOLE)
#if defined(__WINDOWS__) && !defined(_LIB) && !defined(__WINDLL__)
// win32frame library
#ifdef __WIN64__
#	if defined(_DEBUG)
#		pragma comment(lib, "mrstream64d.lib")
#	else
#		pragma comment(lib, "mrstream64.lib")
#	endif
#else
#	if defined(_DEBUG)
#		pragma comment(lib, "mrstream32d.lib")
#	else
#		pragma comment(lib, "mrstream32.lib")
#	endif
#endif
#endif

#endif // !__AXEEN_MRSTREAM_MRSTREAM_HH__
