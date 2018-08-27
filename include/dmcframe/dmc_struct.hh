/**************************************************************************//**
 * @file	dmc_struct.hh
 * @brief	DmcFrame library structure declaration
 * @date	2000-10-10
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_DMCFRAME_STRUCT_HH__
#define __AXEEN_DMCFRAME_STRUCT_HH__

enum class DMCERR : DWORD
{
	ERR_OK = 0
	, ERR_INVALID_HANDLE
	, ERR_INVALID_HWND
	, ERR_INVALID_POINTER
	, ERR_INVALID_FUNCTION
	, ERR_EXIST_HANDLE
	, ERR_EXIST_HWND
	, ERR_THEEND
};

#endif // !__AXEEN_DMCFRAME_STRUCT_HH__
