/**************************************************************************//**
 * @file	wframe_control.cc
 * @brief	Win32 視窗操作 : 控制項操作項基底類別 - 成員函式
 * @date	2000-10-10
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#include "win32frame/wframe_control.hh"

//! CxFrameControl 建構式
CxFrameControl::CxFrameControl() : CxFrameObject() {  }

/**
 * @brief	CxFrameControl 建構式
 * @param	eType 控制項種類
 * @see		EECTRLTYPE
 */
CxFrameControl::CxFrameControl(EECTRLTYPE eType) : CxFrameObject(eType) {  }

//! CxFrameControl 解構式
CxFrameControl::~CxFrameControl() { }


/**
 * @brief	建立控制項, 使用 Win32API - CreateWindowEx
 * @param	[in] ctrlPtr SSCTRL 結構資料位址
 * @return	@c BOOL \n
 *			若函數操作成功返回非零值(non-zero)，失敗將返回零值(zero) \n
 *			若返回失敗可調用 CxWindow::GetError 取得錯誤碼
 * @remark	定義 SSCTRL 結構內容建立控制項，控制項種類參照 EECTRLTYPE
 * @see		SSCTRL
 * @see		EECTRLTYPE
 */
BOOL CxFrameControl::CreateController(LPSSCTRL ctrlPtr)
{
	const BOOL err = FALSE;
	HINSTANCE hInst = NULL;
	HWND	hCtrl = NULL;
	HMENU	hMenu = NULL;
	DWORD	dwStyle = 0;
	DWORD	dwExStyle = 0;
	LPCTSTR	szClassPtr;

	/*
	if (hInst == NULL							// 無效的模組 handle
		|| ctrlPtr == NULL						// 無效的 SuCTRLS 指標
		|| this->IsExist()						// 此類別物件已經存在視窗定義
		|| ctrlPtr->hParent == NULL				// 無效的父視窗操作 handle
		|| ctrlPtr->idItem < 0					// 無效的子控制項 id
		|| ctrlPtr->eType <= ECtrlPassStart		// 子控制項型態指定錯誤
		|| ctrlPtr->eType >= ECtrlPassEnd)		// 子控制項型態指定錯誤
		return err;
	*/

	for (;;) {
		if (ctrlPtr == NULL) {
			this->SetError(ERROR_INVALID_DATA);
			break;
		}

		if (ctrlPtr->hInstance == NULL) {
			if ((hInst = ::GetModuleHandle(NULL)) == NULL) {
				this->SetError(::GetLastError());
				break;
			}
		}

		if (ctrlPtr->hParent == NULL) {
			this->SetError(ERROR_INVALID_WINDOW_HANDLE);
			break;
		}

		if (ctrlPtr->idItem <= SSCTRL_ITEMID_NIL || ctrlPtr->idItem > SSCTRL_ITEMID_MAX) {
			this->SetError(ERROR_INVALID_INDEX);
			break;
		}

		/* --- Updata to safety check 2018.08.05
		if (ctrlPtr->eType <= ECtrlPassStart || ctrlPtr->eType >= ECtrlPassEnd) {
			this->SetError(ERROR_INVALID_INDEX);
			break;
		}
		*/

		if (ctrlPtr->eType != m_eCtrlType) {
			this->SetError(ERROR_INVALID_INDEX);
			break;
		}

		// 取得 Controller 於系統註冊 class 名稱
		if ((szClassPtr = this->GetControlClassName(ctrlPtr->eType)) == NULL) {
			this->SetError(ERROR_INVALID_NAME);
			break;
		}

		// 設定視窗 style
		if (ctrlPtr->eType == ECtrlDialogBox)
			dwStyle = ctrlPtr->dwStyle | WS_CLIPSIBLINGS | WS_VISIBLE;
		else
			dwStyle = ctrlPtr->dwStyle | WS_CLIPSIBLINGS | WS_VISIBLE | WS_CHILD;

		dwExStyle = ctrlPtr->dwExStyle;

		// hMenu = reinterpret_cast<HMENU>(ctrlPtr->idItem);	// 64-bits 檢測會有，警告 C4312
		QINT uTemp = ctrlPtr->idItem;
		hMenu = reinterpret_cast<HMENU>(uTemp);

		// 建立控制項
		hCtrl = CreateWindowEx(
			dwExStyle,
			szClassPtr,
			ctrlPtr->szNamePtr,
			dwStyle,
			ctrlPtr->iPosx,
			ctrlPtr->iPosy,
			ctrlPtr->iWidth,
			ctrlPtr->iHeight,
			ctrlPtr->hParent,
			hMenu, hInst,
			(LPVOID)ctrlPtr->vUnknowPtr);
		if (hCtrl == NULL) {
			this->SetError(::GetLastError());
			break;
		}

		// 保存各項數據
		m_hModule = hInst;
		m_hWndParent = ctrlPtr->hParent;
		m_hWnd = hCtrl;
		m_idItem = ctrlPtr->idItem;
		m_eCtrlType = ctrlPtr->eType;

		// Is using WndProc Callback ?
		if (ctrlPtr->fnWndProc != NULL) {
			this->SysSetWindowProcess(ctrlPtr->fnWndProc);
		}
		break;
	}

	return hCtrl != NULL;
}


/**************************************************//**
 * @brief	建立控制項 (資源檔建立或其他已建立之控制項)
 * @param	[in] hInst		Handle of module. 若為 NULL 將視為使用現行程序模組
 * @param	[in] hCtrl		控制項 handle
 * @param	[in] idItem		控制項 ID
 * @param	[in] fnWndProc	使用者自訂 Callback function 位址
 * @return	@c BOOL \n
 *			函數操作成功返回非零值(non-zero), 若操作失敗則返回零 (zero) \n
 *			操作失敗可由 CxFrameObject::GetError 或衍生類別取得失敗錯誤碼
 ******************************************************/
BOOL CxFrameControl::CreateController(HINSTANCE hInst, HWND hCtrl, int idItem, WNDPROC fnWndProc)
{
	BOOL err = FALSE;

	for (;;) {
		if (hInst == NULL) {
			if ((hInst = ::GetModuleHandle(NULL)) == NULL) {
				this->SetError(::GetLastError());
				break;
			}
		}

		if (hCtrl == NULL) {
			this->SetError(ERROR_INVALID_WINDOW_HANDLE);
			break;
		}

		m_hModule = hInst;
		m_hWnd = hCtrl;
		m_hWndParent = ::GetParent(hCtrl);

		// Is using user WndProc Callback ?
		if (fnWndProc != NULL) {
			this->SysSetWindowProcess(fnWndProc);
		}

		err += hCtrl != NULL;
		break;
	}
	return err;
}


/**
 * @brief	建立控制項 (資源檔建立或其他已建立之控制項)
 * @param	[in] hInst		Handle of module. 若為 NULL 將視為使用現行程序模組
 * @param	[in] hWndParent	父視窗 HANDLE
 * @param	[in] idItem		控制項 ID
 * @param	[in] fnWndProc	使用者自訂 callback function 位址
 * @return	@c BOOL \n
 *			若函數操作成功返回非零值(non-zero), 失敗將返回零值(zero) \n
 */
BOOL CxFrameControl::CreateControllerEx(HINSTANCE hInst, HWND hWndParent, int idItem, WNDPROC fnWndProc)
{
	HWND	hCtrl = NULL;
	BOOL	err = FALSE;

	for (;;) {
		if (hInst == NULL) {
			if ((hInst = ::GetModuleHandle(NULL)) == NULL) {
				this->SetError(::GetLastError());
				break;
			}
		}

		if ((hCtrl = ::GetDlgItem(hWndParent, idItem)) == NULL) {
			this->SetError(::GetLastError());
			break;
		}

		if (this->IsExist()) {
			this->SetError(ERROR_FILE_EXISTS);
			break;
		}

		// 控制項 ID 不能小於或等於 0
		if (idItem <= SSCTRL_ITEMID_NIL || idItem > SSCTRL_ITEMID_MAX) {
			this->SetError(ERROR_INVALID_INDEX);
			break;
		}

		m_hModule = hInst;
		m_hWndParent = hWndParent;
		m_hWnd = hCtrl;
		m_idItem = idItem;

		// Is using user WndProc Callback ?
		if (fnWndProc != NULL) {
			this->SysSetWindowProcess(fnWndProc);
		}
		err += TRUE;
		break;
	}

	return err;
}


/**
 * 視窗結束處理 (釋放配置記憶體與成員物件)
 *
 * 此為虛擬函數, 由衍生類別繼承 \n
 * 視窗進入關閉階段時進行運作此一函數, 確保類別內所配置的物件與記憶體都被釋放.
 * 壁面物件或記憶體未釋放造成 memory leek.
 */
void CxFrameControl::WindowInTheEnd()
{
	// TODO: 結束視窗處理
	CxFrameObject::WindowInTheEnd();
}


/**
 * @brief	取得控制項名稱
 * @param	[in] index	取得控制項 calss name 索引，參照 EECTRLTYPE
 * @return	@c LPCTSTR \n
 *			若操作成功返回控制項系統註冊 class 名稱字串位址. \n
 *			若操作失敗將返回 NULL
 * @see		EECTRLTYPE
 */
LPCTSTR CxFrameControl::GetControlClassName(EECTRLTYPE index)
{
	static const TCHAR* szClass[] = {
		TEXT("Pass Start"),			// 起始識別符
		TEXT("Button"),				// Button
		TEXT("ComboBox"),			// Combo Box
		TEXT("Edit"),				// Edit control.
		TEXT("ListBox"),			// List box.
		TEXT("MDIClient"),			// MDI client window.
		TEXT("ScrollBar"),			// Scroll bar.
		TEXT("Static"),				// Static control.

		TEXT("ComboLBox"),			// List box contained in a combo box.
		TEXT("DDEMLEvent"),			// Dynamic Data Exchange Management Library (DDEML) events.
		TEXT("Message"),			// Message-only window.
		TEXT("#32768"),				// Menu.
		TEXT("#32769"),				// Desktop window.
		TEXT("#32770"),				// Dialog box. (32770)
		TEXT("#32771"),				// Task switch window.
		TEXT("#32772"),				// Icon titles.

		TEXT("ToolbarWindow32"),	// Toolbar
		TEXT("tooltips_class32"),	// Tooltip
		TEXT("msctls_statusbar32"), // Status bar
		TEXT("SysTreeView32"),		// Tree view
		TEXT("SysListView32"),		// List view
		TEXT("SysAnimate32"),		// Animation
		TEXT("SysHeader32"),		// Header
		TEXT("msctls_hotkey32"),	// Hot-key
		TEXT("msctls_progress32"),	// Progress bar
		TEXT("RICHEDIT"),			// Rich edit
		TEXT("msctls_updown32"),	// Up-down
		TEXT("SysTabControl32"),	// Tab
		TEXT("Pass Error")			// 錯誤識別符
	};
	const int len = sizeof(szClass) / sizeof(szClass[0]);
	int idx = (int)index;

	if (idx >= len)
		return NULL;
	return szClass[idx];
}
