/**************************************************************************//**
 * @file	edialog_define.hh
 * @brief	Example3 - main frame class
 * @date	2010-12-05
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_EXAMPLE3_EDIALOG_DEFINE_HH__
#define	__AXEEN_EXAMPLE3_EDIALOG_DEFINE_HH__

#ifndef __WINVER__
#define	__WINVER__			0x0601	//!< 預設 Windows 7
#endif

#ifndef __IEEVER__
#define __IEEVER__			0x0900	//!< 預設 IE 9.0
#endif

#ifndef __DLL_EXPORT__
#define	__DLL_EXPORT__		1		//!< 是否使用 EXPORTS 宣告
#endif

#ifndef __XPP_STYLE__
#define __XPP_STYLE__		1		//<! // 編譯 GUI 類型的的程式，是否編譯成具備 XP 的風格
#endif

#include "win32frame/wframe.hh"
#include "resource/resource.h"

#endif // !__AXEEN_EXAMPLE3_EDIALOG_DEFINE_HH__
