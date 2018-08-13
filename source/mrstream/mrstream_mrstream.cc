/**************************************************************************//**
 * @file	mrstream_mrstream.cc
 * @brief	MRStream Dynamic Library - export function
 * @date	2018-08-01
 * @date	2018-08-01
 * @author	Swang
 *****************************************************************************/
#include "mrstream/mrstream.hh"
#include "include/mrstream_carlist.hh"

EEMRS STDCALL InOutLastError(EEMRS eErrCode = MRS_ERROR_THEEND);

/**
 * @brief 取得最後錯誤碼
 * @param [in] eErrCode	錯誤碼
 * @return 最後錯誤碼
 */
EEMRS STDCALL InOutLastError(EEMRS eErrCode)
{
	static EEMRS eeLastErrorCode;

	if (eErrCode != MRS_ERROR_THEEND)
		eeLastErrorCode = eErrCode;
	return eeLastErrorCode;
}


MRSRESULT STDCALL MRStream_GetLastError()
{
	return static_cast<MRSRESULT>(InOutLastError());
}

/**
 * @brief	取得 MRStream 版本資訊
 * @param	[out]	szTextPtr	字串緩衝區位址
 * @param	[in]	cchMax		取得最大文字數 (in TCHAR) 不含結尾 NULL
 * @return	@c 型別: MRSRESULT \n
 *			函數操作成功返回零值 (zero) ERR_MRS_SUCCESS \n
 *			若操作失敗則返回非零值(non-zero), 該值為錯誤碼
 * @rmark	基於複製字串安全考量，已做基礎的防止溢位處理
 */
MRSRESULT STDCALL MRStream_GetVersionText(LPTSTR szTextPtr, size_t cchMax)
{
	const UINT uMajor = 3;
	const UINT uMinor = 2;
	const UINT uRelease = 1;

	static BOOL		bFirst = FALSE;
	static TCHAR	szVersion[BUFF_SIZE_32];

	if (!bFirst) {
		::wsprintf(szVersion, TEXT("%u.%u build %04u"), uMajor, uMinor, uRelease);
		bFirst = TRUE;
	}

	EEMRS err = MRS_ERROR_SUCCESS;
	size_t len = _tcslen(szVersion);

	for (;;) {
		if (szTextPtr == NULL) {
			err = MRS_ERROR_INVALID_POINTER;
			break;
		}

		if (cchMax <= 0) {
			err = MRS_ERROR_INVALID_INDEX;
			break;
		}

		if (cchMax < len) {
			// 只複製指定的字串長度
			_tcsncpy(szTextPtr, szVersion, cchMax);
			szTextPtr[cchMax] = '\0';
		}
		else ::wsprintf(szTextPtr, TEXT("%s"), szVersion);

		break;
	}
	return err;
}


/**
 * @brief	建立車輛資訊操作物件
 * @param	[in] szHostPtr	主機IP位址字串存放位址
 * @param	[in] nHostPort	主機通訊埠
 * @return	@c 型別: HMRSTREAM \n
 *			若函數操作成功將返回 HMRSTREAM (Handle of MRStream) \n
 *			若函數操作失敗返回值為 NULL
 * @remark	成功建立車輛資訊物件後，即可進行相關函數調用 \n
 *			當不再使用時，必須呼叫(調用) ReleaseCarlist 進行釋放物件，否則 memory leek。
 */
HMRSTREAM STDCALL MRStream_Carlist_Create(LPCTSTR szHostPtr, int nHostPort)
{
	auto clist = new (std::nothrow) CxCarlist();

	// TBD ...

	return static_cast<HMRSTREAM>(clist);
}


/**
 * @brief	釋放車輛資訊操作物件
 * @param	[in,out] hMrsCarlistPtr	存放 HMRSTREAM 位址
 * @return	@c 型別: MRSRESULT \n
 *			函數操作成功返回零值 (zero) ERR_MRS_SUCCESS
 *			若操作失敗則返回非零值(non-zero), 該值為錯誤碼
 */
MRSRESULT STDCALL MRStream_Carlist_Release(HMRSTREAM* hMrsCarlistPtr)
{
	EEMRS err = MRS_ERROR_SUCCESS;

	for (;;) {
		if (hMrsCarlistPtr == NULL) {
			err = MRS_ERROR_INVALID_POINTER;
			break;
		}

		if (*hMrsCarlistPtr == NULL) {
			err = MRS_ERROR_INVALID_HANDLE;
			break;
		}

		SAFE_DELETE(*hMrsCarlistPtr);
		break;
	}
	return err;
}
