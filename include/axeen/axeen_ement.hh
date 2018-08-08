/**************************************************************************//**
 * @file	axeen_ement.hh
 * @brief	編譯環境定義
 * @date	2000-10-10
 * @date	2018-03-25
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_AXEENEMENT_HH__
#define __AXEEN_AXEENEMENT_HH__

// ---------------------------------------
// set platform symbol
// ---------------------------------------
#if defined(_WIN32) || defined(_WIN64)
#	ifndef __WINDOWS__
#	define __WINDOWS__
#	endif

#	ifndef __WIN32__
#	define __WIN32__
#	endif
#endif

// ---------------------------------------
// set compiler symbol
// ---------------------------------------
// MS VC++ 15.0 _MSC_VER = 1910 (Visual Studio 2017)
// MS VC++ 14.0 _MSC_VER = 1900 (Visual Studio 2015)
// MS VC++ 12.0 _MSC_VER = 1800 (VisualStudio 2013)
// MS VC++ 11.0 _MSC_VER = 1700 (VisualStudio 2012)
// MS VC++ 10.0 _MSC_VER = 1600 (VisualStudio 2010)
// MS VC++  9.0 _MSC_VER = 1500 (VisualStudio 2008)
// MS VC++  8.0 _MSC_VER = 1400 (VisualStudio 2005)
// MS VC++  7.1 _MSC_VER = 1310 (VisualStudio 2003)
// MS VC++  7.0 _MSC_VER = 1300 (VisualStudio.NET)
// MS VC++  6.0 _MSC_VER = 1200 (VisualStudio 98)
// MS VC++  5.0 _MSC_VER = 1100 (VisualStudio 97)
#if defined(_MSC_VER)
#	if _MSC_VER < 1600
#		error "This Visual C++ version is not supported any longer (at least MSVC 2010 required)."
#	elif _MSC_VER < 1700
#		define __VISUALC__	10	// vs2010	
#	elif _MSC_VER < 1800
#		define __VISUALC__	11	// vs2012
#	elif _MSC_VER < 1900
#		define __VISUALC__	12	// vs2013
#	elif _MSC_VER < 1910
#		define __VISUALC__	14	// vs2015
#	elif _MSC_VER < 2000
#		define __VISUALC__	15	// vs2017
#	else
#		pragma message("Please update axeen_ement.hh to recognize this VC++ version")
#	endif
#endif

// ---------------------------------------
// set x64 symbol
// ---------------------------------------
#if defined(_WIN64) || (__x86_64__) || (__ppc64__) || (_M_X64) || (_M_AMD64)
#	ifndef __WIN64__
#	define __WIN64__
#	endif
#endif

// ---------------------------------------
// unicode symbol
// ---------------------------------------
#if defined(_UNICODE) || (UNICODE)
#	ifndef __UINCODE__
#	define __UNICODE__
#	endif
#endif

// ---------------------------------------
// Set using windows platform sdk
// ---------------------------------------
// _WIN32_WINNT version constants (see windows sdk sdkddkver.h)
#define M_WIN32_SYMBOL_WINNT4		0x0400  //!< Windows NT 4.0
#define M_WIN32_SYMBOL_WIN2K		0x0500  //!< Windows 2000
#define M_WIN32_SYMBOL_WINXP		0x0501  //!< Windows XP
#define M_WIN32_SYMBOL_WIN2K3		0x0502  //!< Windows Server 2003
#define M_WIN32_SYMBOL_WINVISTA		0x0600  //!< Windows Vista
#define M_WIN32_SYMBOL_WIN2K8		0x0600  //!< Windows Server 2008
#define M_WIN32_SYMBOL_WIN7			0x0601  //!< Windows 7
#define M_WIN32_SYMBOL_WIN8			0x0602  //!< Windows 8
#define M_WIN32_SYMBOL_WIN8BLUE		0x0603  //!< Windows 8.1
#define M_WIN32_WINNT_WINTHRESHOLD	0x0A00	//!< ABRACADABRA_THRESHOLD
#define M_WIN32_WINNT_WIN10			0x0A00	//!< Windows 10	ABRACADABRA_THRESHOLD

// _WIN32_IE_ version constants (see windows sdk sdkddkver.h)
#define M_WIN32_IE_IE20				0x0200	//!< IE 2.0
#define M_WIN32_IE_IE30				0x0300	//!< IE 3.0
#define M_WIN32_IE_IE302			0x0302	//!< IE 3.2
#define M_WIN32_IE_IE40				0x0400	//!< IE 4.0
#define M_WIN32_IE_IE401			0x0401	//!< IE 4.1
#define M_WIN32_IE_IE50				0x0500	//!< IE 5.0
#define M_WIN32_IE_IE501			0x0501	//!< IE 5.1
#define M_WIN32_IE_IE55				0x0550	//!< IE 5.5
#define M_WIN32_IE_IE60				0x0600	//!< IE 6.0
#define M_WIN32_IE_IE60SP1			0x0601	//!< IE 6.0 SP1
#define M_WIN32_IE_IE60SP2			0x0603	//!< IE 6.0 SP2
#define M_WIN32_IE_IE70				0x0700	//!< IE 7.0
#define M_WIN32_IE_IE80				0x0800	//!< IE 8.0
#define M_WIN32_IE_IE90				0x0900	//!< IE 9.0
#define M_WIN32_IE_IE100			0x0A00	//!< IE 10.0
#define M_WIN32_IE_IE110			0x0A00	//!< IE 11.0 ABRACADABRA_THRESHOLD

// ---------------------------------------
// Set _WIN32_WINNT minimum requirements
// ---------------------------------------
#ifdef __WINVER__
#	ifndef _WIN32_WINNT
#	define _WIN32_WINNT	__WINVER__
#	endif
#endif

#ifndef _WIN32_WINNT
	#define _WIN32_WINNT M_WIN32_SYMBOL_WIN7
#else
#	if (_WIN32_WINNT < M_WIN32_SYMBOL_WIN7)
#		undef  _WIN32_WINNT
#		define _WIN32_WINNT M_WIN32_SYMBOL_WIN7
#	endif
#endif

// ---------------------------------------
// Set WINVER based on _WIN32_WINNT
// ---------------------------------------
#ifndef WINVER
#define WINVER _WIN32_WINNT
#else
#undef  WINVER
#define WINVER _WIN32_WINNT
#endif

// ---------------------------------------
// Set _WINN32_IE minimum requirements
// ---------------------------------------
#ifdef __IEEVER__
#	ifndef _WIN32_IE
#	define _WIN32_IE	__IEEVER__
#	endif
#endif

#ifndef _WIN32_IE
#define _WIN32_IE	M_WIN32_IE_IE90
#else
#	if (_WIN32_IE < M_WIN32_IE_IE90)
#		undef  _WIN32_IE
#		define _WIN32_IE M_WIN32_IE_IE90
#	endif
#endif

// ---------------------------------------
// To do speed up compilations, before include windows.h
// ---------------------------------------
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

// ---------------------------------------
// Enable features that require more care in declaring and using types.
// ---------------------------------------
#ifndef STRICT
#define STRICT
#endif

// ---------------------------------------
// Disable Compiler Warning(level 3) C4996 -- disable unsafe deprecation.
// ---------------------------------------
#ifndef _CRT_SECURE_NO_WARNINGS
#define	_CRT_SECURE_NO_WARNINGS
#endif

#ifndef _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_NON_CONFORMING_SWPRINTFS
#endif

#ifndef _SCL_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#endif

/*! 使用 DLLAPI 前綴字巨集 */
#if		(__DLL_EXPORT__ == 1)
#	define DLLAPI __declspec(dllexport)	//!< 動態程式庫 Export 類別或函數給外界使用宣告
#elif	(__DLL_EXPORT__ == 2)
#	define DLLAPI __declspec(dllimport)	//!< 動態程式庫 Export 類別或函數給外界使用宣告
#else
#	define DLLAPI
#endif

// ---------------------------------------
// Include C CRT header
// ---------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <time.h>

// ---------------------------------------
// Include C++ CRT header
// ---------------------------------------
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

// ---------------------------------------
// Windows Win32API header
// ---------------------------------------
#include <windows.h>
#include <tchar.h>
#include <commctrl.h>
#include "axeen_undef.hh"
#include "axeen_inline.hh"

// ---------------------------------------
// User type define
// ---------------------------------------
#if !defined(__WINDOWS__)
typedef __int8				INT8,	*PINT8;		//!< 8	位元, 整數型別 (帶正負號)
typedef __int16				INT16,	*PINT16;	//!< 16	位元, 整數型別 (帶正負號)
typedef __int32				INT32,	*PINT32;	//!< 32 位元, 整數型別 (帶正負號)
typedef __int64				INT64,	*PINT64;	//!< 64 位元, 整數型別 (帶正負號)
typedef unsigned __int8		UINT8,	*PUINT8;	//!< 8	位元, 整數型別
typedef unsigned __int16	UINT16,	*PUINT16;	//!< 16	位元, 整數型別
typedef unsigned __int32	UINT32,	*PUINT32;	//!< 32	位元, 整數型別
typedef unsigned __int64	UINT64,	*PUINT64;	//!< 64	位元, 整數型別

#if !defined(__UNICODE__)
typedef char				TCHAR;				//!< 字元 - 單位元組
#else
typedef wchar_t				TCHAR;				//!< 字元 - 雙位元組
#endif
#endif

// ---
#if defined(__WIN64__)
typedef INT64	QINT;		//!< 有號數，對應CPU編譯架構最大型別 64bit / 32bit
typedef UINT64	QUINT;		//!< 無號數，對應CPU編譯架構最大型別 64bit / 32bit
#else
typedef INT32	QINT;		//!< 有號數，對應CPU編譯架構最大型別 64bit / 32bit
typedef UINT32	QUINT;		//!< 有號數，對應CPU編譯架構最大型別 64bit / 32bit
#endif

// ---------------------------------------
// define the calling convention symbol
// ---------------------------------------
#ifndef STDCALL
#define STDCALL		__stdcall		//<! 由最後參數先開始推入堆疊 (x64 會利用暫存器加速，原理不變)
#endif

#ifndef PASCALL
#define	PASCALL		__stdcall		//<! 由最後參數先開始推入堆疊 (x64 會利用暫存器加速，原理不變)
#endif

#ifndef CDECALL
#define CDECALL		__cdecl			//!< 由最後參數先開始推入堆疊 (x64 會利用暫存器加速，原理不變)
#endif

#ifndef FASTCALL
#define FASTCALL	__fastcall		//!< 藉由暫存器 (eax, ecx) 加速 (x64 會做例外處理)
#endif

// ---------------------------------------
// constant macro
// ---------------------------------------
#ifndef NULL
#ifdef __cplusplus
#define NULL  0				//!< 空值，無值 null C++11 wnaana update to nullptr? (#define NULL nullptr)
#else
#define NULL  ((void*)0)	//!< 空值，無值 null
#endif
#endif

#ifndef TRUE
#define TRUE	1			//!< 布林式判別，值 = 1 (非零值)
#endif

#ifndef FALSE
#define FALSE	0			//!< 布林式判別，值 = 0
#endif

// ---------------------------------------
// string macro
// ---------------------------------------
#ifndef __WINDOWS__
#	ifdef  __UNICODE__
#		ifndef __TEXT
#		define __TEXT(quote) L ## quote		//!< 字串定義巨集
#		endif
#	else
#		ifndef __TEXT
#		define __TEXT(quote) quote			//!< 字串定義巨集
#		endif
#	endif

#	ifndef TEXT
#		define TEXT(quote) __TEXT(quote)	//!< 字串定義巨集
#	endif
#endif

// ---------------------------------------
// memory, object control macro
// ---------------------------------------
#define SAFE_FREE(p)            { if (NULL!=(p))  { ::free((void*)(p); (p)=NULL; } }	//!< 釋放記憶體
#define SAFE_DELETE(p)          { if (NULL!=(p))  { delete (p); (p)=NULL; } }			//!< 釋放記憶體配置 (物件型)
#define SAFE_DELETE_ARRAY(p)    { if (NULL!=(p))  { delete [] (p); (p)=NULL; } }		//!< 釋放記憶體配置 (陣列型)
#define SAFE_CLOSE_FILE(p)      { if (NULL!=(p))  { ::fclose(p); (p)=NULL; } }			//!< 關閉檔案
#define SAFE_CLOSE_HANDLE(p)    { if (NULL!=(p) && INVALID_HANDLE_VALUE!=(p))  { ::CloseHandle(p); (p)=NULL; } }	//!< 關閉 Window Handle

// ---------------------------------------
// buffer size macro
// ---------------------------------------
#define BUFF_SIZE_16	16		//!< 緩衝區容量巨集 16		個單位
#define BUFF_SIZE_32	32		//!< 緩衝區容量巨集 32		個單位
#define BUFF_SIZE_64	64		//!< 緩衝區容量巨集 64		個單位
#define BUFF_SIZE_128	128		//!< 緩衝區容量巨集 128	個單位
#define BUFF_SIZE_256	256		//!< 緩衝區容量巨集 256	個單位
#define BUFF_SIZE_512	512		//!< 緩衝區容量巨集 512	個單位
#define BUFF_SIZE_1024	1024	//!< 緩衝區容量巨集 1024	個單位

// ---------------------------------------
// used xp-style GUI
// ---------------------------------------
/*! 使用 XP-STYLE 編譯 */
#if (__XPP_STYLE__)
#	if defined(__WINDOWS__) && !defined(_LIB) || defined(_CONSOLE)
#		if defined _M_IX86
#			pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#		elif defined _M_IA64
#			pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#		elif defined _M_X64
#			pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#		else
#			pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#		endif
#	endif
#endif


#endif	// !__AXEEN_AXEENEMENT_HH__
