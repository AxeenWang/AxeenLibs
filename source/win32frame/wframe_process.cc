/**************************************************************************//**
 * @file	wframe_process.cc
 * @brief	程序操作基底類別，成員函式
 * @date	2002-01-15
 * @date	2018-04-02
 * @author	Swang
 *****************************************************************************/
#include "win32frame/wframe_process.hh"


//! CxFrameProcess 建構式
CxFrameProcess::CxFrameProcess()
	: m_hProcess(NULL),
	m_idProcess(0) {
}

//! CxFrameProcess 解構式
CxFrameProcess::~CxFrameProcess() { this->ClassInTheEnd(); }

/**
 * @brief	搜尋指定目標程序
 * @param	[in] szModulePtr 指定程序名稱，如： foo.exe, foo.dll
 * @return	@c 型別: DWORD \n
 *			函數操作成功返回值非零值(non-zero)為目標模組的程序運作 ID \n 
 *			函數操作失敗則返回零(zero)
 * @remark	@c 使用方式 \n
 *			程序模組名稱即為可執行程式的檔案名稱，如 Foo.exe, Foo.dll \n
 *			程序模組名稱不必刻意注意大小寫，會自動進行辨認。 \n
 *			若搜尋到指定程序於系統中運行，則傳回該程序運作之 ID
 */
DWORD CxFrameProcess::SearchProcess(LPCTSTR szModulePtr)
{
	const DWORD errProcessID = 0;
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;

	// 採用快照方式，取得系統正在運作的全部程序。
	hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
		return errProcessID;

	// 在使用 結構前，必須先指定其長度 !!重要步驟
	::memset(&pe32, 0, sizeof(PROCESSENTRY32));
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// 取得第一個執行中程序，若失敗就退出
	if (!::Process32First(hProcessSnap, &pe32))
		return errProcessID;

	// 開始依序取得系統中所有執行的程式
	do {
		// 比對指定搜尋程式名稱
		if (this->StrCompare(szModulePtr, pe32.szExeFile, FALSE)) {
			// 找到目標程序, 回傳運行程序ID
			return pe32.th32ProcessID;
		}
	} while (::Process32Next(hProcessSnap, &pe32));

	return errProcessID;
}

/**
 * @brief	開啟目標程序
 * @param	[in] dwProcessID	運行中程序 ID
 * @return	@c 型別: HANDLE \n
 *			函數操作成功返回非零值(non-zero)為模組程序運作 HANDLE
 *			函數操作失敗返回零(zero)
 * @remark	使用系統運行ID 開啟指定之程序，即可針對開程序進行各項操作，如... \n
 *			對該程序記憶體讀寫 (遊戲作弊常用) \n
 *			對該程序模組進行操作，如取得運作式窗，並可針對該視窗傳送命令。
 */
HANDLE CxFrameProcess::OpenProcess(DWORD dwProcessID)
{
	HANDLE hProcess = NULL;

	// 使用程序運作ID 進行取得程序運作 HANDLE
	if (dwProcessID != 0) {
		hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessID);
		if (hProcess != NULL) {
			m_hProcess = hProcess;
			m_idProcess = dwProcessID;
		}
	}
	return hProcess;
}

/**
 * @brief	讀取指定記憶體區資料
 * @param	[in]  aBasePtr	欲讀取目標位址
 * @param	[out] aBuffPtr	欲讀取資料存放位址
 * @param	[in]  uSize		欲讀取資料長度 (in Byte)
 * @return	@c 型別: SIZE_T \n
 *			讀取成功返回非零值(non-zero)為實際讀取資料長度 (單位 byte) \n
 *			讀取失敗返回零(zero) \n
 *			實際資料讀取長度與指定長度不同，使用 GetLastError() 去了解狀況
 */
SIZE_T CxFrameProcess::ReadMemory(LPCVOID aBasePtr, LPVOID aBuffPtr, SIZE_T uSize)
{
	HANDLE hProcess = m_hProcess;
	SIZE_T cbReads = 0;
	::ReadProcessMemory(hProcess, aBasePtr, aBuffPtr, uSize, &cbReads);
	return cbReads;
}

/******************************************************//**
 * @brief	寫入指定記憶體區資料
 * @param	[out] aBasePtr	欲寫入目標位址
 * @param	[in]  aBuffPtr	欲寫入資料存放位址
 * @param	[in]  uSize	欲寫入資料長度 (單位 byte)
 * @return	@c 型別: SIZE_T \n
 *			讀取成功返回非零值(non-zero)為實際寫入資料長度 (in byte) \n
 *			讀取失敗返回零(zero) \n
 *			實際資料寫入長度與指定長度不同，使用 GetLastError() 去了解狀況
 *********************************************************/
inline SIZE_T CxFrameProcess::WriteMemory(LPVOID aBasePtr, LPCVOID aBuffPtr, SIZE_T uSize)
{
	HANDLE hProcess = m_hProcess;
	SIZE_T cbWrite = 0;
	::WriteProcessMemory(hProcess, aBasePtr, aBuffPtr, uSize, &cbWrite);
	return cbWrite;
}

/**
 * @brief	取得已連接的 Process Handle
 * @return	@c 型別: HANDLE \n
 *			傳回目標模組的程序運作 handle
 */
HANDLE CxFrameProcess::GetProcessHandle() { return m_hProcess; }

/**
 * @brief	取得已連接的 Process ID
 * @return	@c 型別: DWORD \n
 *			傳回目標模組的程序運作 ID
 */
DWORD CxFrameProcess::GetProcessID() { return m_idProcess; }


//! 類別物件結束處理
void CxFrameProcess::ClassInTheEnd()
{
	SAFE_CLOSE_HANDLE(m_hProcess);
	m_idProcess = 0;
}


/**
 * @brief	比對字串
 * @param	[in] szDstPtr	第一個字串位址
 * @param	[in] szSrcPtr	第二個字串位址
 * @param	[in] bCase		比對時是否區分字元大小寫 (TRUE = 區分大小寫)
 * @return	@c 型別: BOOL \n
 *			比對結果相符返回值為 TRUE \n
 *			比對結果不符返回值為 FALSE
 */
BOOL CxFrameProcess::StrCompare(LPCTSTR szDstPtr, LPCTSTR szSrcPtr, BOOL bCase)
{
	TCHAR szDst[MAX_PATH];
	TCHAR szSrc[MAX_PATH];

	// 防呆，防例外處理
	if (szDstPtr == NULL || szSrcPtr == NULL)
		return FALSE;

	// 比對時區分大小寫
	if (bCase) return _tcscmp(szDstPtr, szSrcPtr) == 0;

	// 進行字串大小寫轉換後再比對
	_tcscpy(szDst, szDstPtr);
	_tcscpy(szSrc, szSrcPtr);
	this->StrUpper(szDst);
	this->StrUpper(szSrc);
	return _tcscmp(szDst, szSrc) == 0;
}

/**
 * @brief	轉換成大寫，將字串內容轉為大寫
 * @param	[in,out] szPtr 字串位址(指標)
 */
void CxFrameProcess::StrUpper(LPTSTR szPtr)
{
	size_t i, len;

	if (szPtr == NULL) return;
	len = _tcslen(szPtr);
	for (i = 0; i < len; i++) {
		szPtr[i] = static_cast<TCHAR>(_totupper(szPtr[i]));
	}
}

/**
 * @brief	轉換成小寫，將字串內容轉為小寫
 * @param	[in,out] szPtr 字串位址(指標)
 */
void CxFrameProcess::StrLower(LPTSTR szPtr)
{
	size_t i, len;
	
	if (szPtr == NULL) return;
	len = _tcslen(szPtr);
	for (i = 0; i < len; i++) {
		szPtr[i] = static_cast<TCHAR>(_totlower(szPtr[i]));
	}
}
