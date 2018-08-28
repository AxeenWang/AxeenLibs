/**************************************************************************//**
 * @file	dmc_struct.hh
 * @brief	DmcFrame library structure declaration
 * @date	2000-10-10
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_DMCFRAME_STRUCT_HH__
#define __AXEEN_DMCFRAME_STRUCT_HH__

/**
 * @enum	DMCERR
 * @brief	DmcFrame Library error code
 * @remark	系統錯誤可透過 Win32api 的 GetLastError() 取得錯誤資訊 \n
 *			DMCERR dmError = ERR_ENDVALUE + static_cast<DMCERR>(::GetLastError());
 */
enum class DMCERR : DWORD
{
	ERR_OK = 0					//!< 沒有錯誤
	, ERR_INVALID_HANDLE		//!< 無效的操作碼
	, ERR_INVALID_HWND			//!< 無效的視窗(控制項)操作碼
	, ERR_INVALID_POINTER		//!< 無效的指標
	, ERR_INVALID_FUNCTION		//!< 無效的函數指標
	, ERR_INVALID_STRINGLENGTH	//!< 無效的字串長度
	, ERR_EXIST_HANDLE			//!< 操作碼已存在
	, ERR_EXIST_HWND			//!< 視窗(控制項)操作碼已存在
	, ERR_NOTEXIST_TARGET		//!< 指定目標不存在
	, ERR_ENDVALUE				//!< 不是錯誤!!! 錯誤碼結尾識別碼
};




#endif // !__AXEEN_DMCFRAME_STRUCT_HH__
