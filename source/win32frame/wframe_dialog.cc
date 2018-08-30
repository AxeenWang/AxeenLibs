/**************************************************************************//**
 * @file	wframe_dialog.cc
 * @brief	Win32 視窗操作 : 控制項 Dialog 類別 - 成員函數
 * @date	2000-10-10
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#include "win32frame/wframe_dialog.hh"


//! CxFrameDialog 建構式
CxFrameDialog::CxFrameDialog() : CxFrameObject(ECtrlDialogBox) { }

//! CxFrameDialog 解構式
CxFrameDialog::~CxFrameDialog() { }

/**
* @brief	Dialog 訊息處理 Callback fuction
* @param	[in] hWnd		視窗 Handle
* @param	[in] uMessage	視窗訊息
* @param	[in] wParam		訊息參數
* @param	[in] lParam		訊息參數
* @return	@c INT_PTR		運作結果返回資訊
* @remark	DialogProc 函示為靜態函示，作為建立 Dialog callback function
*/
INT_PTR CxFrameDialog::DialogProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	CxFrameDialog*	ddObj = NULL;	// dialog object

	if (uMessage == WM_INITDIALOG) {
		// save user data using "GWLP_USERDATA" mode
		ddObj = (CxFrameDialog*)lParam;
		if (ddObj != NULL) {
			ddObj->m_hWnd = hWnd;
			::SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)ddObj);
		}
	}

	// get user saved data form "GWLP_USERDATA" mode
	if ((ddObj = (CxFrameDialog*)::GetWindowLongPtr(hWnd, GWLP_USERDATA)) == NULL) {
		return 0;
	}

	// transfer window message
	return ddObj->MessageDispose(uMessage, wParam, lParam);
}


/**
 * @brief	Dialog 訊息處理 Callback fuction
 * @details 虛擬函數，訊息處理函數
 * @param	[in] uMessage	視窗訊息
 * @param	[in] wParam		訊息參數
 * @param	[in] lParam		訊息參數
 * @return	@c INT_PTR		訊息處理結果
 * @remark	MessageDisopse 為虛擬函示，由衍生者重載重新定義動作內容
 */
INT_PTR CxFrameDialog::MessageDispose(UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	switch (uMessage)
	{
	case WM_INITDIALOG:
		break;
	case WM_DESTROY:
		this->SysDestroyWindow();
		break;
	case WM_CLOSE:
		this->SysCloseWindow();
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

/**
 * @brief	建立 Dialog 控制項
 * @param	[in] hParent	父視窗 Handle
 * @param	[in] idItem		控制項 ID
 * @param	[in] bModule	是否建立 Module Dialog
 *			- 預設為 FALSE 建立 Child Dialog
 *			- 設定為 TRUE 建立 Module Dialog
 * @return	@c BOOL \n
 *			若 Dialog 被建立返回非零值(non-zero), 建立失敗返回零值(zero) 
 * @remark	使用資源檔(Resource)定義的 Dialog
 */
BOOL CxFrameDialog::CreateDialog(HWND hParent, int idItem, BOOL bModule)
{
	HINSTANCE hInst	= ::GetModuleHandle(NULL);	// 取得程序模組 Handle
	LPTSTR szTemplatePtr;
	BOOL err = FALSE;

	for (;;) {
		if (hInst == NULL) {
			this->SetError(GetLastError());
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

		// 使用 MAKEINTRESOURCE 巨集轉換控制項 ID
		// 造出 DialogBoxParam、CreateDialogParam 函數所需資源ID 字串
		szTemplatePtr = MAKEINTRESOURCE(idItem);

		// 保存相關資料
		m_hModule = hInst;
		m_hWndParent = hParent;

		if (bModule) {
			// DialogBoxParam 若運作失敗將傳回 0 or -1
			auto result = ::DialogBoxParam(
				hInst,
				szTemplatePtr,
				hParent,
				CxFrameDialog::DialogProc,
				reinterpret_cast<LPARAM>(this));

			if (result == -1) {
				this->SetError(::GetLastError());
				break;
			}

			err += result >= 0;
			break;
		}
		else {
			// 若運作失敗將傳回 NULL，若運作成功返回 Dialog Handle
			auto result = ::CreateDialogParam(
				hInst,
				szTemplatePtr,
				hParent,
				CxFrameDialog::DialogProc,
				reinterpret_cast<LPARAM>(this));

			if (result == NULL) {
				this->SetError(::GetLastError());
				break;
			}
			err += result != NULL;
		}
		break;
	}

	return err;
}


/**
 * 結束類別物件處理 (釋放配置記憶體與成員物件)
 *
 * 此為虛擬函數, 由衍生類別繼承 \n
 * 視窗進入關閉階段時進行運作此一函數, 確保類別內所配置的物件與記憶體都被釋放.
 * 壁面物件或記憶體未釋放造成 memory leek.
 */
void CxFrameDialog::WindowInTheEnd()
{
	// TODO 視窗結束前處理

	// 呼叫父類別繼續處理
	CxFrameObject::WindowInTheEnd();
}
