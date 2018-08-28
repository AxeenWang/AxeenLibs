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
		this->SetError(DMCERR::ERR_INVALID_POINTER);
	}
}

//! DmObject deconstruct
DmObject::~DmObject() { this->ClassInTheEnd(); }

/**
 * @brief	設定最後錯誤資訊
 * @param	[in] dmErr		錯誤碼
 * @param	[in] szTextPtr	錯誤資訊文字敘述位址 (預設為 NULL)
 */
void DmObject::SetError(DMCERR dmErr, const TCHAR* szTextPtr)
{
	auto szPtr = m_szErrorTextPtr;
	
	assert(szPtr);

	m_dmError = dmErr;
	if (szPtr != NULL) {
		_tcscpy(szPtr, szTextPtr);
	}
}

/**
 * @brief	取得最後錯誤的錯誤碼碼
 * @return	@c 型別: DMCERR \n
 *			傳回最後發生錯誤的錯誤碼
 */
DMCERR DmObject::GetError() { return m_dmError; }

/**
 * @brief	取得最後錯誤文字訊息
 * @return	@c 型別: int \n
 *			返回值為實際取得文字(in TCHAR)數, 不含 NULL 結尾.
 */
int DmObject::GetErrorText(TCHAR * szTextPtr, size_t cchMax)
{
	auto szPtr = m_szErrorTextPtr;
	assert(szPtr);
	assert(szTextPtr);
	assert(cchMax);

	int res = 0;
	for (;;) {
		if (szPtr == NULL) {
			this->SetError(DMCERR::ERR_NOTEXIST_TARGET);
			break;
		}

		if (szTextPtr == NULL) {
			this->SetError(DMCERR::ERR_INVALID_POINTER);
			break;
		}

		size_t srcLen = _tcslen(szPtr);
		if (srcLen > cchMax) {
			_tcsncpy(szTextPtr, szPtr, cchMax);
			szTextPtr[cchMax] = '\0';
		}
		else {
			_tcscpy(szTextPtr, szPtr);
		}

		res = static_cast<int>(_tcslen(szTextPtr));
		break;
	}
	return res;
}

/**
 * @brief	取得最後錯誤文字訊息
 * @return	@c 型別: const TCHAR* \n
 *			若以存在錯誤文字訊息，將返回非零值(non-zero)為文字存放位址(指標) \n
 *			若不存在錯誤訊息，則返回 NULL 或 空字串(Empty c-string)
 */
const TCHAR * DmObject::GetErrorText() { return m_szErrorTextPtr; }

//! 類別結束處理
void DmObject::ClassInTheEnd()
{
	SAFE_DELETE_ARRAY(m_szErrorTextPtr);
}
