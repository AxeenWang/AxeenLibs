/**************************************************************************//**
 * @file	dmc_object.cc
 * @brief	DMC Frame 基底類別, 成員函數
 * @date	2000-10-10
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#include "dmcframe/dmc_object.hh"

//! DmObject construct
DmObject::DmObject() : m_dmError(DMCERR::ERR_OK), m_szErrorTextPtr(NULL)
{
	m_szErrorTextPtr = new (std::nothrow) TCHAR[BUFF_SIZE_256];
	assert(m_szErrorTextPtr);

	if (m_szErrorTextPtr == NULL) {
		this->SetLastError(DMCERR::ERR_INVALID_POINTER);
	}
}

//! DmObject deconstruct
DmObject::~DmObject() { this->ClassInTheEnd(); }

/**
 * @brief	設定最後錯誤資訊
 * @param	[in] dmErr		錯誤碼
 * @param	[in] szTextPtr	錯誤資訊文字敘述位址 (預設為 NULL)
 */
void DmObject::SetLastError(DMCERR dmErr, const TCHAR* szTextPtr)
{
	auto szPtr = m_szErrorTextPtr;
	
	assert(szPtr);

	m_dmError = dmErr;
	if (szPtr != NULL) {
		_tcscpy(m_szErrorTextPtr, szTextPtr);
	}
}

/**
 * @brief	設定最後錯誤資訊
 * @param	[in] dwErr		錯誤碼
 * @param	[in] szTextPtr	錯誤資訊文字敘述位址 (預設為 NULL)
 */
void DmObject::SetLastError(DWORD dwErr, const TCHAR* szTextPtr)
{
	this->SetLastError(static_cast<DMCERR>(dwErr), szTextPtr);
}

/**
 * @brief	取得最後錯誤碼
 * @return	@c 型別: DMCERR \n
 *			傳回最後發生錯誤的錯誤碼
 */
DMCERR DmObject::GetLastError()
{
	return m_dmError;
}

//! 類別結束處理
void DmObject::ClassInTheEnd()
{
	SAFE_DELETE_ARRAY(m_szErrorTextPtr);
}

