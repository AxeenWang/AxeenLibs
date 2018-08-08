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

	DLLAPI MRSRESULT STDCALL GetMRStreamVersionText(LPTSTR szTextPtr);

#if defined(__cplusplus)
}
#endif






#endif // !__AXEEN_MRSTREAM_MRSTREAM_HH__
