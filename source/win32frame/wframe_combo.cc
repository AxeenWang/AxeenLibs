/**************************************************************************//**
 * @file	wframe_combo.cc
 * @brief	Win32 視窗操作 : 控制項 ComboBox 類別 - 成員函式
 * @date	2000-10-10
 * @date	2018-07-25
 * @author	Swang
 *****************************************************************************/
#include "win32frame/wframe_combo.hh"

//! CxFrameCombo 建構式
CxFrameCombo::CxFrameCombo() : CxFrameControl(ECtrlComboBox) { }

//! CxFrameCombo 解構式
CxFrameCombo::~CxFrameCombo() { }

/**
 * @brief	新增項目、字串項目
 * @details	使用 AddItem 新增一個項目，所新增項目會被自動排序
 * @param	[in] szPtr	字串緩衝區位址
 * @return	@c int 型別 \n
 *			函數操作成功返回值為新增索引, 若操作失敗返回 CB_ERR
 */
int CxFrameCombo::AddItem(LPCTSTR szPtr)
{
	// CB_ADDSTRING
	WPARAM wParam = 0;									// 未使用，建議設為 0
	LPARAM lParam = reinterpret_cast<LPARAM>(szPtr);	// 字串存放位址
	return static_cast<int>(this->SendMessage(CB_ADDSTRING, wParam, lParam));
}

/**
 * @brief	刪除一個 Item
 * @param	[in] nIndex	欲刪除的索引碼 (zero-base)
 * @return	@c int 型別 \n
 *			函數操作成功返回值為目前 Item 數量, 操作失敗返回 CB_ERR
 */
int CxFrameCombo::DeleteItem(int nIndex)
{
	// CB_DELETESTRING
	WPARAM wParam = static_cast<WPARAM>(nIndex);	// 項目索引
	WPARAM lParam = 0;								// 未使用，必須為零
	return static_cast<int>(this->SendMessage(CB_DELETESTRING, wParam, lParam));
}

/**
 * @brief	取得項目數量
 * @return	@c int 型別 \n
 *			函數操作成功返回值為項目數量, 若操作失敗返回 CB_ERR
 */
int CxFrameCombo::GetCount()
{
	// CB_GETCOUNT
	// wParam 未使用，必須為零
	// lParam 未使用，必須為零
	return static_cast<int>(this->SendMessage(CB_GETCOUNT, 0, 0));
}

/**
 * @brief	取得光標所在位置
 * @return	@c int 型別 \n
 *			函數操作成功返回值為 cursel(光標) 位置 (zero-base), 若操作失敗返回 CB_ERR
 */
int CxFrameCombo::GetCursel()
{
	// CB_GETCURSEL
	// wParam 未使用，必須為零
	// lParam 未使用，必須為零
	return static_cast<int>(this->SendMessage(CB_GETCURSEL, 0, 0));
}

/**
 * @brief	取得項目字串
 * @param	[in]  nIndex	項目索引 (zero-base)
 * @param	[out] szPtr	字串緩衝區位址
 * @return	@c int 型別 \n
 *			函數操作成功返回值為指定 Item 的字串長度，單位 TCHAR (不含 NULL 結尾) \n
 *			若操作失敗則返回 CB_ERR
 */
int CxFrameCombo::GetItemText(int nIndex, LPTSTR szPtr)
{
	// CB_GETLBTEXT
	WPARAM wParam = static_cast<WPARAM>(nIndex);		// 項目索引
	LPARAM lParam = reinterpret_cast<LPARAM>(szPtr);	// 字串緩衝區位址
	return static_cast<int>(this->SendMessage(CB_GETLBTEXT, wParam, lParam));
}

/**
 * @brief	取得 Item 字串長度
 * @param	[in] nIndex	要取得字串長度的索引碼 (zero-base)
 * @return	@c int 型別 \n
 *			函數操作成功返回值為所指 Item 字串長度，單位 TCHAR (不含 Null 結尾) \n
 *			若操作失敗返回 CB_ERR
 */
int CxFrameCombo::GetItemTextLength(int nIndex)
{
	// CB_GETLBTEXTLEN
	WPARAM wParam = static_cast<WPARAM>(nIndex);	// 項目索引
	LPARAM lParam = 0;								// 未使用，必須為零
	return static_cast<int>(this->SendMessage(CB_GETLBTEXTLEN, wParam, lParam));
}

/**
 * @brief	新增項目、
 * @details	使用 InsertItem 新增一個項目 \n
 *			新增項為會依據指定位置插入，安插後原有項目 index 將往後遞增
 * @param	[in] nIndex	項目索引 (zero-base)
 * @param	[in] szPtr	字串緩衝區位址
 * @return	@c int 型別 \n
 *			函數操作成功返回值為新增索引, 若操作失敗返回 CB_ERR
 */
int CxFrameCombo::InsertItem(int nIndex, LPCTSTR szPtr)
{
	// CB_INSERTSTRING
	WPARAM wParam = static_cast<WPARAM>(nIndex);		// 項目索引
	LPARAM lParam = reinterpret_cast<LPARAM>(szPtr);	// 字串緩衝區位址
	return static_cast<int>(this->SendMessage(CB_INSERTSTRING, wParam, lParam));
}

/**
 * @brief	清除所有 ComboBox 列表內容內容
 * @return	此函數沒有返回值
 * @see		RemoveAllItem
 */
void CxFrameCombo::ResetContent()
{
	// CB_RESETCONTENT
	// wParam = 未使用，必須為零
	// lParam = 未使用，必須為零
	this->SendMessage(CB_RESETCONTENT, 0, 0);
}

/**
 * @brief	移除所有 ComboBox 列表內容內容
 * @return	此函數沒有返回值
 */
void CxFrameCombo::RemoveAllItem()
{
	// CB_RESETCONTENT
	// wParam = 未使用，必須為零
	// lParam = 未使用，必須為零
	this->SendMessage(CB_RESETCONTENT, 0, 0);
}


/**
 * @brief	設定目前清單上 Cursel (光標? 反白?) 位置
 * @param	[in] nIndex	欲設定 cursel 位置索引碼 (zero-base)
 * @return	@c int 型別 \n
 *			函數操作成功返回值為當前 cursel 位置 (zero-base), 操作失敗則返回 CB_ERR
 */
int CxFrameCombo::SetCursel(int nIndex)
{
	// CB_SETCURSEL
	WPARAM wParam = static_cast<WPARAM>(nIndex);	// 項目索引
	LPARAM lParam = 0;								// 未使用，必須為零
	return static_cast<int>(this->SendMessage(CB_SETCURSEL, wParam, lParam));
}


/**
 * @brief	建立 Combo Box
 * @param	[in] szCaptionPtr	不使用直接填入 NULL
 * @param	[in] x				按鈕起始位置 (對應父視窗左上座標 X)
 * @param	[in] y				按鈕起始位置 (對應父視窗左上座標 Y)
 * @param	[in] wd				按鈕寬度
 * @param	[in] ht				按鈕高度
 * @param	[in] hParent		父視窗 Handle
 * @param	[in] idItem			控制項 ID
 * @param	[in] hInst			Handle of module, 若此值為 NULL, 將視為使用現行的程序模組
 * @param	[in] fnWndProc		pointer of callback function
 * @return	@c BOOL \n
 *			函數操作成功返回非零值(non-zero), 操作失敗返回零(zero)\n
 *			操作失敗可調用 CxFrameObject::GetError() 或衍生類別取得失敗錯誤碼.
 */
BOOL CxFrameCombo::CreateCombo(LPCTSTR szCaptionPtr, int x, int y, int wd, int ht, HWND hParent, int idItem, HINSTANCE hInst, WNDPROC fnWndProc)
{
	auto	err = BOOL(FALSE);
	SSCTRL	ctrl;

	for (;;) {
		if ((hInst = ::GetModuleHandle(NULL)) == NULL) {
			this->SetError(::GetLastError());
			break;
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
		ctrl.hParent	= hParent;
		ctrl.eType		= ECtrlComboBox;
		ctrl.szNamePtr	= NULL;	// szCaptionPtr; 不使用
		ctrl.dwStyle	= WS_TABSTOP | CBS_DROPDOWN;
		ctrl.dwExStyle	= 0;
		ctrl.iPosx		= x;
		ctrl.iPosy		= y;
		ctrl.iWidth		= wd;
		ctrl.iHeight	= ht;
		ctrl.idItem		= idItem;
		ctrl.fnWndProc	= fnWndProc;
		err = this->CreateController(&ctrl);
		break;
	}
	return err;
}


/**
 * @brief	建立 Combo Box (資源檔建立或其他已建立的 Combo Box)
 * @param	[in] hInst		Handle of module. 若為 NULL 將視為使用現行程序模組
 * @param	[in] hCombo		控制項 Handle
 * @param	[in] idItem		控制項 ID
 * @param	[in] fnWndProc	使用者自訂 Callback function 位址
 * @return	@c BOOL \n
 *			若函數操作成功返回非零值(non-zero), 失敗將返回零值(zero)
 */
BOOL CxFrameCombo::CreateCombo(HINSTANCE hInst, HWND hCombo, int idItem, WNDPROC fnWndProc)
{
	return this->CreateController(hInst, hCombo, idItem, fnWndProc);
}

/**
* @brief	建立 Combo Box (資源檔建立或其他已建立的 Combo Box)
* @param	[in] hInst		Handle of module. 若為 NULL 將視為使用現行程序模組
* @param	[in] hParent	父視窗 Handle
* @param	[in] idItem		控制項 ID
* @param	[in] fnWndProc	User defined callback function address
* @return	@c BOOL \n
*			若函數操作成功返回非零值(non-zero), 失敗將返回零值(zero)
*/
BOOL CxFrameCombo::CreateComboEx(HINSTANCE hInst, HWND hParent, int idItem, WNDPROC fnWndProc)
{
	return this->CreateControllerEx(hInst, hParent, idItem, fnWndProc);
}


/**
* 視窗結束處理 (釋放配置記憶體與成員物件)
*
* 此為虛擬函數, 由衍生類別繼承 \n
* 視窗進入關閉階段時進行運作此一函數, 確保類別內所配置的物件與記憶體都被釋放.
* 壁面物件或記憶體未釋放造成 memory leek.
*/
void CxFrameCombo::WindowInTheEnd()
{
	// TODO: 結束視窗處理
	CxFrameControl::WindowInTheEnd();
}
