/**************************************************************************//**
 * @file	wframe_tab.cc
 * @brief	Win32 視窗操作 : 控制項 Tab 類別 - 成員函式
 * @date	2010-10-12
 * @date	2018-07-25
 * @author	Swang
 *****************************************************************************/
#include "win32frame/wframe_tab.hh"

//! CxFrameTab 建構式
CxFrameTab::CxFrameTab() : CxFrameControl(ECtrlSysTabControl32) { }

//! CxFrameTab 解構式
CxFrameTab::~CxFrameTab() { }

/**
 * @brief	調整標籤頁面工作區塊尺寸
 * @param	[in]	 bMode	使用模式
 * @param	[in,out] rcPtr	RECT 結構位址指標 
 * @return	此函數沒有返回值
 * @remark	bMode 會設定為 FALSE，採用使窗對應舉行區域。\n
 *			Set TRUE, specifies a display rectangle and receives the corresponding window rectangle \n
 *			Set FALSE, specifies a window rectangle and receives the corresponding display area.
 */
void CxFrameTab::AdjustRect(BOOL bMode, RECT* rcPtr)
{
	// TCM_ADJUSTRECT
	// wParam 使用模式
	// lParam RECT 結構資料位址
	this->SendMessage(TCM_ADJUSTRECT, static_cast<WPARAM>(bMode), reinterpret_cast<LPARAM>(rcPtr));
}

/**
 * @brief	刪除所有標籤
 * @return	@c BOOL \n
 *			若函數操作成功返回非零值(non-zero), 失敗將返回零值(zero)
 */
BOOL CxFrameTab::DeleteAllItem()
{
	// TCM_DELETEALLITEMS
	// wParam = 未使用，必須為零
	// lParam = 未使用，必須為零
	return (BOOL)this->SendMessage(TCM_DELETEALLITEMS, 0, 0);
}

/**
 * @brief	刪除一個標籤
 * @param	[in] index 項目索引 (zero-base)
 * @return	@c BOOL \n
 *			若函數操作成功返回非零值(non-zero), 失敗將返回零值(zero)
 */
BOOL CxFrameTab::DeleteItem(int index)
{
	// TCM_DELETEITEM
	// wParam = 標籤的索引 (zero-base)
	// lParam = 未使用，必須為零
	return (BOOL)this->SendMessage(TCM_DELETEITEM, static_cast<WPARAM>(index), 0);
}

/**
 * @brief	重置標籤(書籤)狀態
 * @param	[in] bDeSel	指定重置標籤範圍
 *			- TRUE	為當前被選定的標籤將被清除狀態
 *			- FALSE	為所有的標籤將被清除狀態
 *
 * MSDN 說明 \n
 * Resets items in a tab control. \n
 * Clearing any that were set to the TCIS_BUTTONPRESSED state
 */
void CxFrameTab::DeSelectAll(BOOL bDeSel)
{
	// TCM_DESELECTALL
	// wParam = 標示要清除的範圍
	// lParam = 未使用，必須為零
	this->SendMessage(TCM_DESELECTALL, static_cast<WPARAM>(bDeSel), 0);
}

/**
 * @brief	取得目前被選定標籤 (焦點)
 * @return	@c int 型別 \n
 *			函數超做操作成功返回值為標籤索引(zero-base), 若操作失敗返回 -1 
 */
int CxFrameTab::GetCurselFocus()
{
	// TCM_GETCURFOCUS
	// wParam = 未使用，必須為零
	// lParam = 未使用，必須為零
	return (int)this->SendMessage(TCM_GETCURFOCUS, 0, 0);
}

/**
 * @brief	取得被選定標籤
 * @return	@c int 型別 \n
 *			函數超做操作成功返回值為標籤索引(zero-base), 若操作失敗返回 -1
 */
int CxFrameTab::GetCursel()
{
	// TCM_GETCURSEL
	// wParam = 未使用，必須為零
	// lParam = 未使用，必須為零
	return (int)this->SendMessage(TCM_GETCURSEL, 0, 0);
}

/**
 * @brief	取得指定標籤訊息
 * @param	[in]  index	標籤索引 (zero-base)
 * @param	[out] tciPtr TCITEM 結構指標
 * @return	@c BOOL 型別 \n
 *			若函數操作成功返回非零值(non-zero), 失敗將返回零值(zero)
 */
BOOL CxFrameTab::GetItem(int index, TCITEM* tciPtr)
{
	// TCM_GETITEM
	// wParam = 標籤索引
	// lParam = TCITEM 結構資料位址
	return (BOOL)this->SendMessage(TCM_GETITEM, static_cast<WPARAM>(index), reinterpret_cast<LPARAM>(tciPtr));
}

/**
 * @brief	取得標籤數量
 * @return	@c int 型別 \n
 *			函數操作成功返回值為標籤數量, 若操作失敗則覽回零(zero)
 */
int CxFrameTab::GetItemCount()
{
	// TCM_GETITEMCOUNT
	// wParam 未使用，必須為零
	// lParam 未使用，必須為零
	return (int)this->SendMessage(TCM_GETITEMCOUNT, 0, 0);
}

/**
 * @brief	取得標籤邊界尺寸
 * @param	[in]  index	標籤索引 (zero-base)
 * @param	[out] rcPtr	RECT 結構指標
 * @return	@c BOOL 型別 \n
 *			若函數操作成功返回非零值(non-zero), 失敗將返回零值(zero)
 */
BOOL CxFrameTab::GetItemRect(int index, RECT* rcPtr)
{
	// TCM_GETITEMRECT
	// wParam = 標籤索引
	// lParam = RECT 結構資料位址
	return (BOOL)this->SendMessage(TCM_GETITEMRECT, static_cast<WPARAM>(index), reinterpret_cast<LPARAM>(rcPtr));
}

/**
 * @brief	插入一個標籤
 * @param	[in] index	要插入標籤的索引 (zero-base)
 * @param	[in] tciPtr	TCITEM 結構資料指標
 * @return	@c BOOL 型別 \n
 *			若函數操作成功返回非零值(non-zero), 失敗將返回零值(zero)
 */
BOOL CxFrameTab::InsertItem(int index, TCITEM* tciPtr)
{
	// TCM_INSERTITEM
	// wParam = 標籤索引
	// lParam = TCITEM 結構資料位址
	return (BOOL)this->SendMessage(TCM_INSERTITEM, static_cast<WPARAM>(index), reinterpret_cast<LPARAM>(tciPtr)) >= 0;
}

/**
 * @brief	插入一個文字標籤
 * @param	[in] index	標籤索引 (zero-base)
 * @param	[in] szPtr	文字緩衝區位址
 * @return	@c BOOL 型別 \n
 *			若函數操作成功返回非零值(non-zero), 失敗將返回零值(zero)
 */
BOOL CxFrameTab::InsertItem(int index, LPCTSTR szPtr)
{
	const BOOL err = FALSE;

    TCITEM tci;
	TCHAR szText[MAX_PATH];
	
	if (szPtr == NULL) return err;
	::lstrcpy(szText, szPtr);
    tci.mask = TCIF_TEXT | TCIF_IMAGE; 
    tci.iImage = -1; 
	tci.pszText = szText;
    return this->InsertItem(index, &tci);
}


/**
 * @brief	設定被選定標籤 (焦點)
 * @param	[in] index	標籤索引 (zero-base)
 * @return	此函數沒有返回值
 */
void CxFrameTab::SetCurselFocus(int index)
{
	// TCM_SETCURFOCUS
	// wParam = 標籤索引 (zero-base)
	// lParam = 未使用、必須為零
	this->SendMessage(TCM_SETCURFOCUS, static_cast<WPARAM>(index), 0);
}

/**
 * @brief	設定指定標籤被選定
 * @param	[in] index	書籤索引值 (zero-base)
 * @return	@c int 型別 \n
 *			函數操作成功返回值為標籤索引 (zero-base), 若操作失敗則返回 -1
 */
int CxFrameTab::SetCursel(int index)
{
	// TCM_SETCURSEL
	// wParam = 標籤索引
	// lParam = 未使用、必須為零
	return (int)this->SendMessage(TCM_SETCURSEL, static_cast<WPARAM>(index), 0);
}

/**
 * @brief	設定指定標籤訊息
 * @param	[in]  index	 標籤索引 (zero-base)
 * @param	[out] tciPtr TCITEM 結構指標
 * @return	@c BOOL 型別 \n
 *			若函數操作成功返回非零值(non-zero), 失敗將返回零值(zero)
 */
BOOL CxFrameTab::SetItem(int index, TCITEM* tciPtr)
{
	// TCM_SETITEM
	// wParam = 標籤索引
	// lParam = TCITEM 結構資料指標
	return (BOOL)this->SendMessage(TCM_SETITEM, (WPARAM)index, (LPARAM)tciPtr);
}

/**
 * @brief	設定標籤尺寸
 * @details	Setsthe width and height of tabs in a fixed-width or owner-drawn tab control.
 * @param	[in] wd	寬度
 * @param	[in] ht	高度
 * @return	@c LRESULT 型別 \n
 *			舊的標籤尺寸資訊 HIWORD 為高度、LOWORD 為寬度
 */
LRESULT CxFrameTab::SetItemSize(int wd, int ht)
{
	LPARAM lParam = static_cast<LPARAM>(ht);
	lParam = (lParam << 16) | static_cast<LPARAM>(wd);
	
	// TCM_SETITEMSIZE
	// wParam = 未使用、必須為零
	// lParam = 頁簽尺寸 (HIWORD = 高) (LOWORD = 寬)
	return (int)this->SendMessage(TCM_SETITEMSIZE, 0, lParam);
}

/**
 * @brief	設定標籤最小寬度
 * @param	[in] wd	標籤寬度 (in pixel)
 * @return	@c INT 型別 \n
 *			An INT value that represents the previous minimum tab width.
 *
 *	Minimum width to be set for a tab control item.
 *	If this parameter is set to -1, the control will use the default tab width.
 */
INT CxFrameTab::SetMinTabWidth(int wd)
{
	// TCM_SETMINTABWIDTH
	// wParam = 未使用、必須為零
	// lParam = 標籤項目最小寬度，如果此參數為-1，則使用預設寬度。
	return (INT)this->SendMessage(TCM_SETMINTABWIDTH, 0, (LPARAM)wd);
}


/**
 * @brief	建立 Tab 控制項
 * @param	[in] szCaptionPtr	控制項標題字串位址, 在 Tab 控制項始終為 NULL
 * @param	[in] x				起始位置 X
 * @param	[in] y				起始位置 Y
 * @param	[in] wd				寬度, 若為零表示使用父視窗工作區之寬度
 * @param	[in] ht				高度, 若為零表示使用父視窗工作區之高度
 * @param	[in] hParent		父視窗操作 handle
 * @param	[in] idItem			ID
 * @param	[in] hInst			Handle of module, 若此值為 NULL, 將視為使用現行的程序模組
 * @return	@c BOOL \n
 *			函數操作成功返回非零值(non-zero), 若操作失敗返回零(zero)
 */
BOOL CxFrameTab::CreateTab(LPCTSTR szCaptionPtr, int x, int y, int wd, int ht, HWND hParent, int idItem, HINSTANCE hInst, WNDPROC fnWndProc)
{
	SSCTRL	ctrl;	// Structure for controller
	RECT	rc;
	BOOL	err = FALSE;

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

		// 初始 DMCWNDCTRLS 內容
		::memset(&ctrl, 0, sizeof(SSCTRL));

		// 取得父視窗邊界資訊
		::GetClientRect(hParent, &rc);

		// 指定寬度為零 ==> 代表使用父視窗工作區寬度
		if (wd == 0) wd = (int)rc.right - rc.left;

		// 指定高度為零 ==> 代表使用父視窗工作區高度
		if (ht == 0) ht = (int)rc.bottom - rc.top;

		// 建立 DMCWNDCTRLS 內容
		ctrl.hInstance = hInst;
		ctrl.hParent = hParent;
		ctrl.eType = ECtrlSysTabControl32;
		ctrl.szNamePtr = NULL;
		ctrl.dwStyle = 0;
		ctrl.dwExStyle = 0;
		ctrl.iPosx = x;
		ctrl.iPosy = y;
		ctrl.iWidth = wd;
		ctrl.iHeight = ht;
		ctrl.idItem = idItem; // conctrller item id
		ctrl.fnWndProc = NULL;
		err = this->CreateController(&ctrl);
		break;
	}
	return err;
}


/**
 * @brief	建立 Tab (資源檔建立或其他已建立的 Tab)
 * @param	[in] hInst		Handle of module. 若為 NULL 將視為使用現行程序模組
 * @param	[in] hTab		控制項 Handle
 * @param	[in] idItem		控制項 ID
 * @param	[in] fnWndProc	使用者自訂 Callback function 位址
 * @return	@c BOOL \n
 *			若函數操作成功返回非零值(non-zero), 失敗將返回零值(zero)
 */
BOOL CxFrameTab::CreateTab(HINSTANCE hInst, HWND hTab, int idItem, WNDPROC fnWndProc)
{
	return this->CreateController(hInst, hTab, idItem, fnWndProc);
}


/**
* @brief	建立 Tab (資源檔建立或其他已建立的 Tab)
* @param	[in] hInst		Handle of module. 若為 NULL 將視為使用現行程序模組
* @param	[in] hParent	父視窗 Handle
* @param	[in] idItem		控制項 ID
* @param	[in] fnWndProc	User defined callback function address
* @return	@c BOOL \n
*			若函數操作成功返回非零值(non-zero), 失敗將返回零值(zero)
*/
BOOL CxFrameTab::CreateTabEx(HINSTANCE hInst, HWND hParent, int idItem, WNDPROC fnWndProc)
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
void CxFrameTab::WindowInTheEnd()
{
	// TODO: 結束視窗處理
	CxFrameControl::WindowInTheEnd();
}
