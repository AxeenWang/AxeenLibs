/**************************************************************************//**
 * @file	wframe_listview.cc
 * @brief	Win32 視窗操作 : 控制項 ListView 類別 - 成員函式
 * @date	2000-10-10
 * @date	2018-07-25
 * @author	Swang
 *****************************************************************************/
#include "win32frame/wframe_listview.hh"

//! CxFrameListview 建構式
CxFrameListview::CxFrameListview()
	: CxFrameControl(ECtrlSysListView32)
	, m_iSelectItemCount(0)
	, m_iSelectItemIndex(0) { }

//! CxFrameListview 解構式
CxFrameListview::~CxFrameListview() { }

/**
 * @brief	刪除所有項目(Item)
 * @return	@c BOOL 型別 \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::DeleteItemAll()
{
	// LVM_DELETEALLITEMS
	// wParam = 沒有使用，必須為零
	// lParam = 沒有使用，必須為零
	return (BOOL)this->SendMessage(LVM_DELETEALLITEMS, 0, 0);
}

/**
 * @brief	刪除一個欄位(Column)
 * @param	[in] index	欄位項目索引 (zero-base)
 * @return	@c BOOL 型別 \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::DeleteColumn(int index)
{
	// LVM_DELETECOLUMN
	// wParam = 欄位索引
	// lParam = 沒有使用，必須為零
	return (BOOL)this->SendMessage(LVM_DELETECOLUMN, (WPARAM)index, 0);
}

/**
 * @brief	刪除所有的欄位(Column)
 * @return	此函數沒有返回值
 */
void CxFrameListview::DeleteColumnAll()
{
	int count = this->GetColumnCount();
	if (count > 0) {
		for (int colIndex = 0; colIndex < count; ++colIndex) {
			this->DeleteColumn(0);
		}
	}
}

/**
 * @brief	刪除一個項目(Item)
 * @param	[in] index	項目索引 (zero-base)
 * @return	@c BOOL 型別 \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::DeleteItem(int index)
{
	// LVM_DELETEITEM
	// wParam = 項目索引
	// lParam = 沒有使用，必須為零
	return (BOOL)this->SendMessage(LVM_DELETEITEM, (WPARAM)index, 0);
}

/**
 * @brief	取得指定欄位(Column)文字內容
 * @param	[in]  index	欄位項目索引 (zero-base)
 * @param	[out] psz	保存取得文字緩衝區位址
 * @param	[in]  cch	要取得字串長度 (in TCHAR)
 * @return	@c BOOL 型別 \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::GetColumn(int index, LPTSTR psz, int cch)
{
    LVCOLUMN lvc;

    if (NULL == psz) return FALSE;
    ::memset((void*)&lvc, 0, sizeof(LVCOLUMN));
    lvc.mask = LVCF_TEXT;
	lvc.pszText = psz;
    lvc.cchTextMax = cch;

	// LVM_GETCOLUMN
	// wParam = 項目索引
	// lParam = LVCOLUMN 結構資料位址
    return (BOOL)this->SendMessage(LVM_GETCOLUMN, (WPARAM)index, (LPARAM)&lvc);
}

/**
 * @brief	取得欄位(Column)數量
 * @return	@c int 型別\n
 *			Column 數量，若失敗傳回 -1
 * @remark	Win32 API 並無提供刪除所有 Column 的功能， \n
 *			所以必須先取得 ListView 的 HDM 然後去取得 Header 數量
 */
int CxFrameListview::GetColumnCount()
{
	// 取得 HDM Handle
	HWND hWnd = (HWND)::SendMessage(m_hWnd, LVM_GETHEADER, 0, 0);
	if (hWnd != NULL) {
		// HDM_GETITEMCOUNT
		// wParam = 沒有使用，必須為零
		// lParam = 沒有使用，必須為零
		return (int)this->SendMessage(HDM_GETITEMCOUNT, 0, 0);
	}
	return -1;
}

/**
 * @brief	取得欄位(Column)寬度
 * @param	[in] index	欄位項目索引 (zero-base)
 * @return	@c int 型別 \n
 *			函數操作成功返回值為寬度數據，若失敗則返回零(zero)
 */
int CxFrameListview::GetColumnWidth(int index)
{
	// LVM_GETCOLUMNWIDTH
	// wParam = 欄位索引
	// lParam = 沒有使用，必須為零
	return (int)this->SendMessage(LVM_GETCOLUMNWIDTH, (WPARAM)index, 0);
}

/**
 * @brief	取得目前可視範圍的項目數量
 * @return	@c int 型別 \n
 *			函數操作成功，返回當前可是範圍的項目數量 \n
 *			若為圖示或小圖示模式，將返回所有於 ListView 控制項的圖示數量
 */
int CxFrameListview::GetCountPerPage()
{
	// LVM_GETCOUNTPERPAGE
	// wParam = 沒有使用，必須為零
	// lParam = 沒有使用，必須為零
	return (int)this->SendMessage(LVM_GETCOUNTPERPAGE, 0, 0);
}

/**
 * @brief   取得 ListView 擴展樣式
 * @return	@c DWORD 型別 \n
 *			That represents the styles currently in use for a given list-view control.
 *
 *	Gets the extended styles \n
 *	that are currently in use for a given list-view control.
 */
DWORD CxFrameListview::GetExListViewStyle()
{
	// LVM_GETEXTENDEDLISTVIEWSTYLE
	// wParam = 沒有使用，必須為零
	// lParam = 沒有使用，必須為零
	return (DWORD)this->SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0);
}

/**
 * @brief	取得項目(Item)數量
 * @return	@c int 型別 \n
 *			全部項目(Item)的數量
 */
int CxFrameListview::GetItemCount()
{
	// LVM_GETITEMCOUNT
	// wParam = 沒有使用，必須為零
	// lParam = 沒有使用，必須為零
	return (int)this->SendMessage(LVM_GETITEMCOUNT, 0, 0);
}

/**
 * @brief	取得指定項目位置
 * @param	[in]  index	項目索引
 * @param	[out] aPtr	POINT 結構資料位址
 * @return	@c BOOL 型別 \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::GetItemPosition(int index, LPPOINT aPtr)
{
	// LVM_GETITEMPOSITION
	// wParam = 項目索引
	// lParam = POINT 結構資料位址
	return (BOOL)this->SendMessage(LVM_GETITEMPOSITION, (WPARAM)index, (LPARAM)aPtr);
}

/**
 * @brief	取得指定項目 (Item) 文字內容
 * @param	[in]  index	項目索引值   (zero-base)
 * @param	[in]  isubs	項目子欄位索引(zero-base)
 * @param	[out] psz	字串緩衝區位址
 * @param	[in]  cch	要取得字串的長度 (in TCHAR)
 * @return	@c BOOL 型別 \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::GetItemText(int index, int isubs, LPTSTR psz, int cch)
{
    LVITEM lvi;

    if (NULL == psz) return FALSE;
    // Setting properties Of members
    memset((void*)&lvi, 0, sizeof(LVITEM));
    lvi.mask = LVIF_TEXT;   // LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
    lvi.iItem = index;      // choose item
    lvi.iSubItem = isubs;   // choose sub item
    lvi.pszText = psz;      // push string pointer
    lvi.cchTextMax = cch;   // the string length

	// LVM_GETITEMTEXT
	// wParam = 項目索引
	// lParam = LVITEM 結構資料位址
    return this->SendMessage(LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&lvi) > 0;
}

/**
 * @brief	取得項目索引，取得下一個被選取項目
 * @return	@c int 型別 \n
 *			函數操作成功返回值為項目(Item)的索引 (zero-base), 若操作失敗返回 -1
 */
int CxFrameListview::GetNextSelectItem()
{
	// LVM_GETNEXTITEM
	// wParam 用於開始搜索項目的索引，-1 以查找與指定標誌匹配的第一個項目，指定的項目本身將被排除在搜索之外。
	// lParam 指定項目搜尋方式
	m_iSelectItemIndex = (int)this->SendMessage(LVM_GETNEXTITEM, m_iSelectItemIndex, LVNI_ALL);
	return m_iSelectItemIndex;
}

/**
 * @brief	取得項目索引，取得第一個被選取的項目索引 (選取累計)
 * @return	@c int 型別 \n
 *			函數操作成功返回值為項目(Item)的索引 (zero-base), 若操作失敗返回 -1
 */
int CxFrameListview::GetFirstSelectItem()
{
	// LVM_GETNEXTITEM
	// wParam = 用於開始搜索項目的索引，-1 以查找與指定標誌匹配的第一個項目，指定的項目本身將被排除在搜索之外。
	// lParam = 指定項目搜尋方式
	m_iSelectItemCount = this->GetSelectCount();
	m_iSelectItemIndex = (int)this->SendMessage(LVM_GETNEXTITEM, -1, LVNI_ALL);
	return m_iSelectItemIndex;
}

/**
 * @brief	取得項目索引，取得第一個被選取項目索引 (無累計，永遠取得第一個)
 * @return	@c int 型別 \n
 *			函數操作成功返回值為項目(Item)的索引 (zero-base), 若操作失敗返回 -1
 */
int CxFrameListview::GetSelectItem()
{
	// LVM_GETNEXTITEM
	// wParam = 用於開始搜索項目的索引，-1 以查找與指定標誌匹配的第一個項目，指定的項目本身將被排除在搜索之外。
	// lParam = 指定項目搜尋方式
	return (int)this->SendMessage(LVM_GETNEXTITEM, -1, LVNI_SELECTED);
}

/**
 * @brief	取得被選中項目(Item)數量 (光標 or 反白)
 * @return	@c int 型別 \n被選中項目(Item)的數量
 * @remark	取得目前列表上被選取的數量
 */
int CxFrameListview::GetSelectCount()
{
	// LVM_GETSELECTEDCOUNT
	// wParam = 沒有使用，必須為零
	// lParam = 沒有使用，必須為零
	return (int)this->SendMessage(LVM_GETSELECTEDCOUNT, 0, 0);
}

/**
 * @brief	取得索引，在可視範圍內，於列表最上面項目的索引
 * @return	@c int 型別 \n位於可是範圍內最上面項目的 index (zero-base)
 */
int CxFrameListview::GetTopIndex()
{
	// LVM_GETTOPINDEX
	// wParam = 沒有使用，必須為零
	// lParam = 沒有使用，必須為零
	return (int)this->SendMessage(LVM_GETTOPINDEX, 0, 0);
}

/**
 * @brief	插入一個欄位 (Column)
 * @param	[in] index	欄位項目索引 (zero-base)
 * @param	[in] wd		指定 Column 寬度
 * @param	[in] align	指定對齊方式
 * @param	[in] psz	指定 Column 顯示文字位址
 * @return	@c BOOL 型別 \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::InsertColumn(int index, int wd, int align, LPTSTR psz)
{
    const static int aiAssign[] = { LVCFMT_LEFT, LVCFMT_RIGHT, LVCFMT_CENTER, LVCFMT_LEFT };
    LVCOLUMN lvc;

    // zero struct's Members
    ::memset((void*)&lvc, 0, sizeof(LVCOLUMN));
	if (align >= LVCOLUMN_ALIGN_PASSEND) align = LVCOLUMN_ALIGN_LEFT;

	// Setting properties Of members
	lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_FMT; // LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvc.fmt = aiAssign[align];
	lvc.pszText = psz;
    lvc.cchTextMax = ::lstrlen(lvc.pszText);
    lvc.cx = wd;

    // LVM_INSERTCOLUMN 訊息處理，若執行成功將傳回一個索引直，若執行失敗將傳回 -1
	// wParam = 欄位索引 zero-base
	// lParam = LVCOLUMN 結構資料位址
    return this->SendMessage(LVM_INSERTCOLUMN, (WPARAM)index, (LPARAM)&lvc) != -1;
}

/**
 * @brief	插入一個項目 (Item) - 文字模式
 * @param	[in] index	項目索引值   (zero-base)
 * @param	[in] isubs	項目子欄位索引(zero-base)
 * @param	[in] psz	字串緩衝區
 * @return	@c BOOL 型別 \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::InsertItem(int index, int isubs, LPTSTR psz)
{
    LVITEM lvi;

	if (NULL == psz) return FALSE;
    // Setting properties Of members
    ::memset((void*)&lvi, 0, sizeof(LVITEM));
    lvi.mask = LVIF_TEXT;   // LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
    lvi.iItem = index;      // choose item
    lvi.iSubItem = isubs;   // choose sub item
	lvi.pszText = psz;      // set text
    lvi.cchTextMax = ::lstrlen(lvi.pszText);

	// LVM_INSERTITEM, 若運作失敗將傳回 -1
	// wParam = 沒有使用，必須為零
	// lParam = LVITEM 結構資料位址
    return this->SendMessage(LVM_INSERTITEM, 0, (LPARAM)&lvi) != -1;
}

/**
 * @brief	設定背景顏色
 * @param	[in] dwColor 顏色(RGB)
 * @return	@c BOOL 型別 \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::SetBkColor(COLORREF dwColor)
{
	// LVM_SETBKCOLOR
	// wParam 必須為零
	// lParam COLORREF 型別, 背景顏色 RGB (若使用 CLR_NONE 定義值，則為無被景色)
	return (BOOL)this->SendMessage(LVM_SETBKCOLOR, 0, (LPARAM)dwColor);
}

/**
 * @brief	設定指定欄位 (Column) 文字內容
 * @param	[in] index	欄位項目索引 (zero-base)
 * @param	[in] psz	欲設定文字緩衝區
 * @return	@c BOOL 型別 \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::SetColumn(int index, LPTSTR psz)
{
    LVCOLUMN lvc;

	if (NULL == psz) return FALSE;
    ::memset((void*)&lvc, 0, sizeof(LVCOLUMN));
    lvc.mask = LVCF_TEXT;
	lvc.pszText = psz;

	// LVM_SETCOLUMN
	// wParam = 欄位索引 zero-base
	// lParam = LVCOLUMN 結構資料位址
    return (BOOL)this->SendMessage(LVM_SETCOLUMN, (WPARAM)index, (LPARAM)&lvc);
}

/**
 * @brief	設定欄位(Column)寬度
 * @param	[in] index	欄位項目索引 (zero-base)
 * @param	[in] pixel	欄位寬度 (in pixel) 像素
 * @return	@c BOOL 型別 \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::SetColumnWidth(int index, int pixel)
{
	// LVM_GETCOLUMNWIDTH
	// wParam = 欄位索引 zero-base
	// lParam = 欄位寬度 (像素)
	return (BOOL)this->SendMessage(LVM_SETCOLUMNWIDTH, (WPARAM)index, (LPARAM)pixel);
}

/**
 * @brief   設定 ListView 擴展樣式
 * @param	[in] dwExStyle 擴展樣式
 *			- dwExStyle a specifies the extended list-view control style.
 *
 *	Sets the extended styles, \n
 *	that are currently in use for a given list-view control.
 */
void CxFrameListview::SetExListViewStyle(DWORD dwExStyle)
{
	// LVM_SETEXTENDEDLISTVIEWSTYLE
	// wParam = 沒有使用，必須為零
	// lParam = Extended List-View Styles. (延伸風格資料)
	this->SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)dwExStyle);
}

/**
 * @brief	設定項目(Item) 被選取狀態
 * @param	[in] index	項目索引 (zero-base)
 * @param	[in] plvi	LVITEM 結構資料位址
 * @return	@c BOOL 型別 \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::SetItemState(int index, LPLVITEM plvi)
{
	// LVM_SETITEMSTATE
	// wParam = 項目索引
	// lParam = LVITEM 結構資料位址
	return (BOOL)this->SendMessage(LVM_SETITEMSTATE, (WPARAM)index, (LPARAM)plvi);
}

/**
 * @brief	設定指定項目(Item)被選中
 * @param	[in] index	項目索引值 (zero-base)
 * @param	[in] bState	選擇狀態 ( TRUE為設定被選擇, FALSE為取消被選擇)
 * @return	@c BOOL 型別 \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::SetItemState(int index, BOOL bState)
{
    LVITEM lvi;
    ::memset((void*)&lvi, 0, sizeof(LVITEM));
    lvi.stateMask = LVIS_SELECTED | LVIS_FOCUSED;
    lvi.state = bState ? LVIS_SELECTED | LVIS_FOCUSED : 0;
    return this->SetItemState(index, &lvi);
}

/**
 * @brief	設定指定項目 (Item) 文字內容
 * @param	[in] index	項目索引值   (zero-base)
 * @param	[in] isubs	項目子欄位索引(zero-base)
 * @param	[in] psz	字串緩衝區位址
 * @return	@c BOOL 型別 \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::SetItemText(int index, int isubs, LPTSTR psz)
{
    LVITEM lvi;

    if (NULL == psz) return FALSE;
    // Setting properties Of members
    ::memset((void*)&lvi, 0, sizeof(LVITEM));
    lvi.mask = LVIF_TEXT;   // LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
    lvi.iItem = index;      // choose item
    lvi.iSubItem = isubs;   // choose sub item
    lvi.pszText = psz;      // push the string
    lvi.cchTextMax = ::lstrlen(lvi.pszText);

	// LVM_SETITEMTEXT
	// wParam = 項目索引
	// lParam = LVITEM 結構資料位址
    return (BOOL)this->SendMessage(LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&lvi);
}

/**
 * @brief	設定文字背景顏色
 * @param	[in] dwColor 顏色(RGB)
 * @return	@c BOOL 型別 \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::SetTextBkColor(COLORREF dwColor)
{
	// LVM_SETTEXTBKCOLOR
	// wParam = 沒有使用，必須為零
	// lParam COLORREF 型別, 背景顏色 RGB (若使用 CLR_NONE 定義值，則為無被景色)
	return (BOOL)this->SendMessage(LVM_SETTEXTBKCOLOR, 0, (LPARAM)dwColor);
}

/**
 * @brief	設定文字顏色
 * @param	[in] dwColor 顏色(RGB)
 * @return	@c BOOL 型別 \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::SetTextColor(COLORREF dwColor)
{
	// LVM_SETTEXTCOLOR
	// wParam = 沒有使用、必須為零
	// lParam = COLORREF 型別, 顏色定義。
	return (BOOL)this->SendMessage(LVM_SETTEXTCOLOR, 0, (LPARAM)dwColor);
}


/**
 * @brief	建立 ListView (資源檔建立或其他已建立的 ListView)
 * @param	[in] hInst		Handle of module. 若為 NULL 將視為使用現行程序模組
 * @param	[in] hListv		控制項 Handle
 * @param	[in] idItem		控制項 ID
 * @param	[in] fnWndProc	使用者自訂 Callback function 位址
 * @return	@c BOOL \n
 *			若函數操作成功返回非零值(non-zero), 失敗將返回零值(zero)
 */
BOOL CxFrameListview::CreateListview(HINSTANCE hInst, HWND hListv, int idItem, WNDPROC fnWndProc)
{
	return this->CreateController(hInst, hListv, idItem, fnWndProc);
}

/**
* @brief	建立 ListView (資源檔建立或其他已建立的 ListView)
* @param	[in] hInst		Handle of module. 若為 NULL 將視為使用現行程序模組
* @param	[in] hParent	父視窗 Handle
* @param	[in] idItem		控制項 ID
* @param	[in] fnWndProc	User defined callback function address
* @return	@c BOOL \n
*			若函數操作成功返回非零值(non-zero), 失敗將返回零值(zero)
*/
BOOL CxFrameListview::CreateListviewEx(HINSTANCE hInst, HWND hParent, int idItem, WNDPROC fnWndProc)
{
	return this->CreateControllerEx(hInst, hParent, idItem, fnWndProc);
}


/**
 * @brief	使用自訂 ListView 預設樣式
 * @return	此函數沒有返回值
 */
void CxFrameListview::DefaultStyle()
{
    // LVS_REPORT           : 設定成 Report 樣式
    // LVS_SHOWSELALWAYS    : 非當前使用視窗時，被選定 Item 仍以高亮反白顯示
    // LVS_EDITLABELS       : 子項目欄位可編輯
    DWORD dwStyle = LVS_REPORT | LVS_SHOWSELALWAYS;

    // LVS_EX_FULLROWSELECT     : 選擇時，以全行高亮反白
    // LVS_EX_GRIDLINES         : 使用網格
    // LVS_EX_CHECKBOXES        : 帶有 Check Box
    // LVS_EX_HEADERDRAGDROP    : 讓 Listview Header(表頭) 顯示位置甩曳交換
    // LVS_EX_ONECLICKACTIVATE  : 單擊觸發
    // LVS_EX_TWOCLICKACTIVATE  : 雙擊觸發
    // LVS_EX_MULTIWORKAREAS    : 多工作區 (可複選項目)
    DWORD dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP;

    dwStyle   |= this->GetStyle();
    dwExStyle |= this->GetExStyle();
    this->SetStyle(dwStyle);
	// this->SetExListViewStyle(dwExStyle);
    this->SetExStyle(dwExStyle);
}


/**
 * 視窗結束處理 (釋放配置記憶體與成員物件)
 *
 * 此為虛擬函數, 由衍生類別繼承 \n
 * 視窗進入關閉階段時進行運作此一函數, 確保類別內所配置的物件與記憶體都被釋放.
 * 壁面物件或記憶體未釋放造成 memory leek.
 */
void CxFrameListview::WindowInTheEnd()
{
	// TODO: 結束視窗處理
	CxFrameControl::WindowInTheEnd();
}


/**
 * @brief	範例程式 - 如何取得 ListView 行與列的訊息
 * @param	[in] wParam	參數 1 (仿視窗訊息處理函式)
 * @param	[in] lParam 參數 2 (仿視窗訊息處理函式)
 * @note	如何獲取 ListView 控制項行與列被滑鼠點擊出發事件 \n
 *			假設父視窗 A 中有一個 ListView 控制項 B，B 的 style 為 report \n
 *			使用者點擊了 B 的內部，我們如何知道用戶點擊了哪一個單元格呢？ \n
 *			使用者點擊 B 的內部時，B 會向父視窗 A 發送 WM_NOTIFY 訊息。 \n
 *			假設使用者單擊了 B 的內部，B 的 ID 為 ID_LV，那麼我們在父視窗 A 訊息處理程式中，可以追加程式碼。
 *
 * @code
 *	case WM_NOTIFY:
 *	{
 *		switch (LOWORD(wParam))
 *		{
 *		case ID_LV:
 *			if (((LPNMHDR)lParam)->code == NM_CLICK) {
 *				int iItem = ((LPNMITEMACTIVATE)lParam)->iItem;
 *				int iSubItem = ((LPNMITEMACTIVATE)lParam)->iSubItem;
 *				if (iItem >= 0 && iSubItem > 1) {
 *					// 這樣就成功獲取了行和列的資訊
 *					return 0;
 *				}
 *			}
 *			break;
 *		}
 *		break;
 *	}
 * @endcode
 *****************************************************/
void CxFrameListview::Example1(WPARAM wParam, LPARAM lParam) { }
