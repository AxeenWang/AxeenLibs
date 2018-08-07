/**************************************************************************//**
 * @file	wframe_editbox.cc
 * @brief	Win32 視窗操作 : 控制項 Edit Box 類別 - 成員函數
 * @date	2000-10-10
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#include "win32frame/wframe_editbox.hh"


//! CxFrameEditbox 建構式
CxFrameEditbox::CxFrameEditbox() : CxFrameControl(ECtrlEditBox) { }

//! CxFrameEditbox 解構式
CxFrameEditbox::~CxFrameEditbox() { }


/**
 * @brief	於撤回的編輯的列隊中(undo queue)是否有可撤回的內容存在
 * @return	@c BOOL 型別 \n
 *			如果輸入框的撤回列隊中有內容存在，返回值為非零值(non-zero)。\n
 *			如果撤回列隊中無任何內容，則返回值為零(zero)。
 */
BOOL CxFrameEditbox::CanUndo()
{
	// EM_CANUNDO
	// wParam = 未使用，必須為零
	// lParam = 未使用，必須為零
	return this->SendMessage(EM_CANUNDO, 0, 0) != 0;
}


/**
 * @brief	取得輸入框字數限制
 * @return	@c int 型別 \n
 *			返回字數限制數，單位 TCHAR
 */
int CxFrameEditbox::GetLimitText()
{
	// EM_GETLIMITTEXT
	// wParam = 未使用，必須為零
	// lParam = 未使用，必須為零
	return static_cast<int>(this->SendMessage(EM_GETLIMITTEXT, 0, 0));
}

/**
 * @brief	取得輸入框矩形邊界尺寸
 * @param	[out] rcPtr RECT 結構資料保存位址
 * @return	無，沒有返回值。(這個訊息的返回值沒有意義)
 */
void CxFrameEditbox::GetRect(LPRECT rcPtr)
{
	// EM_GETRECT
	// wParam = 未使用
	// lParam = 要輸出的 RECT 結構資料位址
	this->SendMessage(EM_GETRECT, 0, reinterpret_cast<LPARAM>(rcPtr));
}

/**
 * @brief	取得文字被選取的範圍資訊
 * @param	[out] dwPtr	DWORD 型別資料保存位址 (可以傳入 NULL, 不擷取)
 * @param	[out] ddPtr DWORD 型別資料保存位址 (可以傳入 NULL, 不擷取)
 * @return	@c DWORD 型別 \n
 *			返回值的 HIWORD 部分為被選取的第一個字元位置 \n
 *			LOWORD 部分為被選取範圍後的第一個字元位置
 * @remark
 *			dwPtr 保存被選取的第一個字元位置 \n
 *			ddPtr 保存被選取範圍外的第一個字元位置
 */
DWORD CxFrameEditbox::GetSelect(DWORD * dwPtr, DWORD * ddPtr)
{
	// EM_GETSEL
	// wParam = 存放被選取的第一個字元位置
	// lParam = 存放被選後的第一個自原位置
	return static_cast<DWORD>(this->SendMessage(EM_GETSEL, reinterpret_cast<WPARAM>(dwPtr), reinterpret_cast<LPARAM>(ddPtr)));
}


/**
 * @brief	設定輸入框字數限制, 單位 TCHAR
 * @param	ccMax 字數限制 單位 TCHAR
 * @return	@c 無，此函數沒有返回值
 * @remark	在使用 EM_SETLIMITTEXT 之前，使用者可以在編輯控件中輸入的文本量的默認限制為32,767個字符(TCHAR)。
 */
void CxFrameEditbox::SetLimitText(int ccMax)
{
	// EM_SETLIMITTEXT
	// wParam = 字數限制
	// lParam = 未使用
	this->SendMessage(EM_SETLIMITTEXT, static_cast<WPARAM>(ccMax), 0);
}


/**
 * @brief	設定輸入框僅供讀取，不接受輸入 (不影響 WM_SETTEXT)
 * @param	[in] bEnable 啟用 or 停用僅供讀取 (TRUE or FALSE)
 * @return	@c BOOL 型別 \n
 *			若函數操作成功將返回非零值(non-zero), 若操作失敗將返回零(zero)
 */
BOOL CxFrameEditbox::SetReadonly(BOOL bEnable)
{
	// EM_SETREADONLY 
	// wParam = 啟用 or 停用
	// lParam = 未使用
	return this->SendMessage(EM_SETREADONLY, bEnable, 0) != 0;
}


/**
 * @brief	設定輸入框矩形邊界尺寸
 * @param	[in] rcPtr RECT 結構資料位址
 * @return	@c 無，此函數沒有返回值。
 */
void CxFrameEditbox::SetRect(LPRECT rcPtr)
{
}


/**
 * @brief	設定文字選取範圍
 * @param	[in] starting	開始位置
 * @param	[in] ending		結束位置
 * @return	@c 無，此函數沒有返回值
 */
void CxFrameEditbox::SetSelect(DWORD starting, DWORD ending)
{
	// EM_SETSEL 
	// wParam = 開始位置
	// lParam = 結束位置
	this->SendMessage(EM_SETSEL, static_cast<DWORD>(starting), static_cast<DWORD>(ending));
}


/**
 * @brief	撤回輸入框最後一個編輯操作
 * @return	@c BOOL 型別 \n
 *			對於單行編輯輸入框，返回值始終為 TRUE。\n
 *			對於多行編輯輸入框，如果撤回操作成功，則返回值為 TRUE, 如果取消操作失敗，則返回值為 FALSE。
 */
BOOL CxFrameEditbox::Undo()
{
	// EM_UNDO
	// wParam = 未使用，必須為零
	// lParam = 未使用，必須為零
	return this->SendMessage(EM_UNDO, 0, 0) != 0;
}

/**
 * @brief	建立 EditBox 控制項
 * @param	[in] szCaptionPtr	必定為 NULL
 * @param	[in] x				EditBox 起始位置 (對應父視窗左上座標 X)
 * @param	[in] y				EditBox 起始位置 (對應父視窗左上座標 Y)
 * @param	[in] wd				EditBox 寬度
 * @param	[in] ht				EditBox 高度
 * @param	[in] hParent		父視窗 Handle
 * @param	[in] idItem			控制項 ID
 * @param	[in] hInst			handle of module, 若此值為 NULL, 表示使用現行的程序模組
 * @param	[in] fnWndProc		使用者自訂 callback function 位址
 * @return	@c BOOL 型別 \n
 *			函數操作成功返回非零值(non-zero), 若操作失敗砸返回零(zero)\n
 *			操作失敗可由 CxFrameObject::GetError 或衍生類別取得失敗錯誤碼
 */
BOOL CxFrameEditbox::CreateEditBox(LPCTSTR szCaptionPtr, int x, int y, int wd, int ht, HWND hParent, int idItem, HINSTANCE hInst, WNDPROC fnWndProc)
{
	BOOL err = FALSE;
	SSCTRL ctrl;

	for (;;) {
		if (hInst == NULL) {
			if ((hInst = ::GetModuleHandle(NULL)) == NULL) {
				this->SetError(::GetLastError());
				break;
			}
		}

		if (hParent == NULL) {
			this->SetError(ERROR_INVALID_WINDOW_HANDLE);
			break;
		}

		if (idItem <= SSCTRL_ITEMID_NIL || idItem > SSCTRL_ITEMID_MAX) {
			this->SetError(ERROR_INVALID_INDEX);
			break;
		}

		::memset((void*)&ctrl, 0, sizeof(SSCTRL));
		ctrl.hInstance	= hInst;
		ctrl.hParent	= hParent;
		ctrl.eType		= ECtrlEditBox;
		ctrl.szNamePtr	= NULL;						// 不使用 szCaptionPtr;
		ctrl.dwStyle	= WS_TABSTOP | ES_CENTER;	// WS_BORDER;
		ctrl.dwExStyle	= WS_EX_CLIENTEDGE;
		ctrl.iPosx		= x;
		ctrl.iPosy		= y;
		ctrl.iWidth		= wd;
		ctrl.iHeight	= ht;
		ctrl.idItem		= idItem;
		ctrl.fnWndProc	= fnWndProc;
		ctrl.vUnknowPtr = NULL;

		err = this->CreateController(&ctrl);
		break;
	}
	return err;
}


/**
 * @brief	建立 Button (資源檔建立或其他已建立的 Button)
 * @param	[in] hInst		Handle of module. 若為 NULL 將視為使用現行程序模組
 * @param	[in] hEdit		控制項 Handle
 * @param	[in] idItem		控制項 ID
 * @param	[in] fnWndProc	使用者自訂 Callback function 位址
 * @return	@c BOOL 型別 \n
 *			若函數操作成功返回非零值(non-zero), 失敗將返回零值(zero)
 */
BOOL CxFrameEditbox::CreateEditBox(HINSTANCE hInst, HWND hEdit, int idItem, WNDPROC fnWndProc)
{
	return this->CreateController(hInst, hEdit, idItem, fnWndProc);
}


/**
 * @brief	建立 Button (資源檔建立或其他已建立的 Button)
 * @param	[in] hInst		Handle of module. 若為 NULL 將視為使用現行程序模組
 * @param	[in] hParent	父視窗 Handle
 * @param	[in] idItem		控制項 ID
 * @param	[in] fnWndProc	User defined callback function address
 * @return	@c BOOL 型別 \n
 *			若函數操作成功返回非零值(non-zero), 失敗將返回零值(zero)
 */
BOOL CxFrameEditbox::CreateEditBoxEx(HINSTANCE hInst, HWND hParent, int idItem, WNDPROC fnWndProc)
{
	return this->CreateControllerEx(hInst, hParent, idItem, fnWndProc);
}


/**
 * 結束類別物件處理 (釋放配置記憶體與成員物件)
 *
 * 此為虛擬函數, 由衍生類別繼承 \n
 * 視窗進入關閉階段時進行運作此一函數, 確保類別內所配置的物件與記憶體都被釋放.
 * 壁面物件或記憶體未釋放造成 memory leek.
 */
void CxFrameEditbox::WindowInTheEnd()
{
	// TODO: 結束視窗處理
	CxFrameControl::WindowInTheEnd();
}
