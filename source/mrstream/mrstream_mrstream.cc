/**************************************************************************//**
 * @file	mrstream_mrstream.cc
 * @brief	MRStream Dynamic Library - export function
 * @date	2018-08-01
 * @date	2018-08-01
 * @author	Swang
 *****************************************************************************/
#include "mrstream/mrstream.hh"
#include "include/mrstream_carlist.hh"

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
#if 0
	TCHAR*	verPtr = NULL;
	TCHAR	szName[MAX_PATH + 1] = { 0 };
	DWORD	dwSize;
	DWORD	dummy;
	MRSRESULT err = static_cast<MRSRESULT>(MRS_ERROR_SUCCESS);

	for (;;) {
		if ((dwSize = ::GetModuleFileName(NULL, szName, MAX_PATH)) == 0) {
			err = static_cast<MRSRESULT>(::GetLastError()) + static_cast<MRSRESULT>(MRS_ERROR_THEEND);
			break;
		}

		if ((dwSize = ::GetFileVersionInfoSize(szName, &dummy)) == 0) {
			err = static_cast<MRSRESULT>(::GetLastError()) + static_cast<MRSRESULT>(MRS_ERROR_THEEND);
			break;
		}

		if ((verPtr = new (std::nothrow) TCHAR[dwSize + 1]) == NULL) {
			err = static_cast<MRSRESULT>(MRS_ERROR_NEW_ARRAY);
			break;
		}

		if (!::GetFileVersionInfo(szName, NULL, dwSize, verPtr)) {
			err = static_cast<MRSRESULT>(::GetLastError()) + static_cast<MRSRESULT>(MRS_ERROR_THEEND);
			break;
		}

		// get the name and version strings
		LPVOID		vProductNamePtr = NULL;
		UINT		uProductNameLen = 0;
		LPVOID		vProductVersionPtr = NULL;
		UINT		uProductVersionLen = 0;

		// replace "040404b0" with the language ID of your resources
		if (!VerQueryValue(verPtr, TEXT("\\StringFileInfo\\040404b0\\ProductName"), &vProductNamePtr, &uProductNameLen) ||
			!VerQueryValue(verPtr, TEXT("\\StringFileInfo\\040404b0\\ProductVersion"), &vProductVersionPtr, &uProductVersionLen)) {
			err = static_cast<MRSRESULT>(MRS_ERROR_FAIL);
			break;
		}

		::wsprintf(szTextPtr, TEXT("%s : %s"), vProductNamePtr, vProductVersionPtr);
		break;
	}

	SAFE_DELETE_ARRAY(verPtr);
	return static_cast<MRSRESULT>(err);
#else
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
	return static_cast<MRSRESULT>(err);
#endif
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
	CxCarlist* clist = NULL;

	for (;;) {
		if (szHostPtr == NULL || szHostPtr[0] == 0) {
			break;
		}

		if (nHostPort <= 0) {
			break;
		}

		clist = new (std::nothrow) CxCarlist();
		if (clist == NULL) {
			break;
		}

		if (clist->SetHost(szHostPtr, nHostPort) != MRS_ERROR_SUCCESS) {
			SAFE_DELETE(clist);
			break;
		}
		break;
	}

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
