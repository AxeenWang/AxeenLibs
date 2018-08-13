﻿/**************************************************************************//**
 * @file	mrstream_define.hh
 * @brief	MRStream Dynamic Library 前置設定
 * @date	2018-08-01
 * @date	2018-08-01
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_MRSTREAM_DEFINE_HH__
#define __AXEEN_MRSTREAM_DEFINE_HH__

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
#include "mrstream/mrstream_struct.hh"

#endif // !__AXEEN_MRSTREAM_DEFINE_HH__
