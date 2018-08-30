/**************************************************************************//**
 * @file	dmc_object.cc
 * @brief	DMC Frame 基底類別, 成員函數
 * @date	2000-10-10
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#include "dmcframe/dmc_object.hh"

//! DmObject construct
DmObject::DmObject() { }

//! DmObject deconstruct
DmObject::~DmObject() { }

/**
 * @brief	取得本程序模組代碼(Handle)
 * @return	@c 型別: HINSTANCE \n
 *			If the function succeeds, the return value is a handle to the specified module. \n
 *			If the function fails, the return value is NULL. To get extended error information, call GetLastError.
 */
HINSTANCE DmObject::GetSaeModule() const { return ::GetModuleHandle(NULL); }
