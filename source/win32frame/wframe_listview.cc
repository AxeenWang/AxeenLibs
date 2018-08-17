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
	, m_nSelectItemCount(0)
	, m_nSelectItemIndex(0) { }

//! CxFrameListview 解構式
CxFrameListview::~CxFrameListview() { }

/**
 * @brief	刪除所有項目(Item)
 * @return	@c 型別: BOOL \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::DeleteItemAll()
{
	// LVM_DELETEALLITEMS
	// wParam = 未使用，必須為零
	// lParam = 未使用，必須為零
	return this->SendMessage(LVM_DELETEALLITEMS, 0, 0) != 0;
}

/**
 * @brief	刪除一個欄位(Column)
 * @param	[in] nIndex	欄位項目索引 (zero-base)
 * @return	@c 型別: BOOL \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::DeleteColumn(int nIndex)
{
	// LVM_DELETECOLUMN
	WPARAM wParam = static_cast<WPARAM>(nIndex);	// 欄位索引
	LPARAM lParam = 0;								// 未使用，必須為零
	return this->SendMessage(LVM_DELETECOLUMN, wParam, lParam) != 0;
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
 * @param	[in] nIndex	項目索引 (zero-base)
 * @return	@c 型別: BOOL \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::DeleteItem(int nIndex)
{
	// LVM_DELETEITEM
	WPARAM wParam = static_cast<WPARAM>(nIndex);	// 項目索引
	LPARAM lParam = 0;								// 未使用，必須為零
	return this->SendMessage(LVM_DELETEITEM, wParam, lParam) != 0;
}

/**
 * @brief	直接於項目欄位直接編輯(like editbox)
 * @param	[in] nIndex 項目索引(zero-base), 若要取消編輯輸入 -1
 * @return	此函數沒有返回值
 */
void CxFrameListview::EditLabel(int nIndex)
{
	// LVM_EDITLABEL
	WPARAM wParam = static_cast<WPARAM>(nIndex);	// 項目索引
	LPARAM lParam = 0;								// 未使用，必須為零
	this->SendMessage(LVM_EDITLABEL, wParam, lParam);
}

/**
 * @brief	取得指定欄位(Column)文字內容
 * @param	[in]  nIndex		欄位項目索引 (zero-base)
 * @param	[out] szColumnPtr	保存取得文字緩衝區位址
 * @param	[in]  ccMax			要取得字串長度 (in TCHAR)
 * @return	@c 型別: BOOL \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::GetColumn(int nIndex, LPTSTR szColumnPtr, int ccMax)
{
    LVCOLUMN lvc;

    if (NULL == szColumnPtr) return FALSE;
    ::memset((void*)&lvc, 0, sizeof(LVCOLUMN));
    lvc.mask = LVCF_TEXT;
	lvc.pszText = szColumnPtr;
    lvc.cchTextMax = ccMax;

	// LVM_GETCOLUMN
	WPARAM wParam = static_cast<WPARAM>(nIndex);	// 項目索引
	LPARAM lParam = reinterpret_cast<LPARAM>(&lvc);	// LVCOLUMN 結構資料位址
	return this->SendMessage(LVM_GETCOLUMN, wParam, lParam) != 0;
}

/**
 * @brief	取得欄位(Column)數量
 * @return	@c 型別: int \n
 *			Column 數量，若失敗傳回 -1
 * @remark	Win32 API 並無提供刪除所有 Column 的功能， \n
 *			所以必須先取得 ListView 的 HDM 然後去取得 Header 數量
 */
int CxFrameListview::GetColumnCount()
{
	// 取得 HDM Handle
	auto hWnd = reinterpret_cast<HWND>(::SendMessage(m_hWnd, LVM_GETHEADER, 0, 0));

	if (hWnd != NULL) {
		// HDM_GETITEMCOUNT
		// wParam = 未使用，必須為零
		// lParam = 未使用，必須為零
		return static_cast<int>(this->SendMessage(HDM_GETITEMCOUNT, 0, 0));
	}
	return -1;
}

/**
 * @brief	取得欄位(Column)寬度
 * @param	[in] nIndex	欄位項目索引 (zero-base)
 * @return	@c 型別: int \n
 *			函數操作成功返回值為寬度數據，若失敗則返回零(zero)
 */
int CxFrameListview::GetColumnWidth(int nIndex)
{
	// LVM_GETCOLUMNWIDTH
	WPARAM wParam = static_cast<WPARAM>(nIndex);		// 欄位索引
	LPARAM lParam = 0;									// 未使用，必須為零
	return static_cast<int>(this->SendMessage(LVM_GETCOLUMNWIDTH, wParam, lParam));
}

/**
 * @brief	取得目前可視範圍的項目數量
 * @return	@c 型別: int \n
 *			函數操作成功，返回當前可是範圍的項目數量 \n
 *			若為圖示或小圖示模式，將返回所有於 ListView 控制項的圖示數量
 */
int CxFrameListview::GetCountPerPage()
{
	// LVM_GETCOUNTPERPAGE
	// wParam = 未使用，必須為零
	// lParam = 未使用，必須為零
	return static_cast<int>(this->SendMessage(LVM_GETCOUNTPERPAGE, 0, 0));
}

/**
 * @brief	取得 EditBox Handle
 * @return	@c 型別: HWND \n
 *			若函數操作成功返回值為 editbox handle, 若失敗將返回 NULL
 * @see		https://docs.microsoft.com/en-us/windows/desktop/controls/lvm-geteditcontrol
 */
HWND CxFrameListview::GetEditControl()
{
	// LVM_GETEDITCONTROL
	// wParam = 未使用，必須為零
	// lParam = 未使用，必須為零
	// 都說 reinterpret_cast 暴力轉型要少用，但在呼叫 Win32API 好像很難不用，呵呵~
	return reinterpret_cast<HWND>(this->SendMessage(LVM_GETEDITCONTROL, 0, 0));
}

/**
 * @brief   取得 ListView 擴展樣式
 * @return	@c 型別: DWORD \n
 *			That represents the styles currently in use for a given list-view control.
 *
 *	Gets the extended styles \n
 *	that are currently in use for a given list-view control.
 */
DWORD CxFrameListview::GetExListViewStyle()
{
	// LVM_GETEXTENDEDLISTVIEWSTYLE
	// wParam = 未使用，必須為零
	// lParam = 未使用，必須為零
	return static_cast<DWORD>(this->SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0));
}

/**
 * @brief	取得項目(Item)數量
 * @return	@c 型別: int \n
 *			返回值為全部項目(Item)的數量
 */
int CxFrameListview::GetItemCount()
{
	// LVM_GETITEMCOUNT
	// wParam = 未使用，必須為零
	// lParam = 未使用，必須為零
	return static_cast<int>(this->SendMessage(LVM_GETITEMCOUNT, 0, 0));
}

/**
 * @brief	取得指定項目位置
 * @param	[in]  nIndex	項目索引 (zero-base)
 * @param	[out] stPtr		POINT 結構資料位址
 * @return	@c 型別: BOOL \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::GetItemPosition(int nIndex, LPPOINT stPtr)
{
	// LVM_GETITEMPOSITION
	WPARAM wParam = static_cast<WPARAM>(nIndex);		// 項目索引
	LPARAM lParam = reinterpret_cast<LPARAM>(stPtr);	// POINT 結構資料位址
	return this->SendMessage(LVM_GETITEMPOSITION, wParam, lParam) != 0;
}

/**
 * @brief	取得項目全部或部分矩形邊界範圍
 * @param	[in]		nIndex	項目索引 (zero-base)
 * @param	[in,out]	rcPtr	RECT 結構資料存放位址，必須在結構成員 left 填入要求返回參數
 *							- LVIR_BOUNDS		返回整個項目的範圍值
 *							- LVIR_ICON			返回 ICON (BIG or SMALL) 圖示範圍
 *							- LVIR_LABEL		返回 Text 區域範圍
 *							- LVIR_SELECTBOUNDS	返回 LVIR_ICON + LVIR_LABEL 範圍 
 * @return	@c 型別: BOOL \n
 *			若函數操作成功返回非零值(non-zero), 若操作失敗將返回零(zero)
 */
BOOL CxFrameListview::GetItemRect(int nIndex, LPRECT rcPtr)
{
	// LVM_GETITEMRECT
	WPARAM wParam = static_cast<WPARAM>(nIndex);
	LPARAM lParam = reinterpret_cast<LPARAM>(rcPtr);
	return this->SendMessage(LVM_GETITEMRECT, wParam, lParam) != 0;
}

/**
 * @brief	取得項目全部或部分矩形邊界範圍
 * @param	[in]		nIndex	項目索引 (zero-base)
 * @param	[in]		nMode	欲取得返回的模式
 *							- LVIR_BOUNDS		返回整個項目的範圍值
 *							- LVIR_ICON			返回 ICON (BIG or SMALL) 圖示範圍
 *							- LVIR_LABEL		返回 Text 區域範圍
 *							- LVIR_SELECTBOUNDS	返回 LVIR_ICON + LVIR_LABEL 範圍
 * @param	[in,out]	rcPtr	RECT 結構資料存放位址

 * @return	@c 型別: BOOL \n
 *			若函數操作成功返回非零值(non-zero), 若操作失敗將返回零(zero) \n
 *			操作成功 RECT 結構內容為指定要求取得內容
 */
BOOL CxFrameListview::GetItemRect(int nIndex, int nMode, LPRECT rcPtr)
{
	auto err = BOOL(FALSE);

	for (;;) {
		if (rcPtr == NULL) {
			break;
		}
		rcPtr->left = nMode;
		err = this->GetItemRect(nIndex, rcPtr);
		break;
	}
	return err;
}

/**
 * @brief	取得項目狀態
 * @param	[in] nIndex	項目索引(zero-base)
 * @param	[in] nMode	指定取得模式 (預設 LVIS_STATEIMAGEMASK)
 *					- LVIS_CUT
 *					- LVIS_DROPHILITED
 *					- LVIS_FOCUSED
 *					- LVIS_SELECTED
 *					- LVIS_OVERLAYMASK
 *					- LVIS_STATEIMAGEMASK
 * @return	@c 型別: int \n
 *			返回指定項的當前狀態，返回值與 lParam 的設定相對應。
 * @see		https://docs.microsoft.com/en-us/windows/desktop/controls/lvm-getitemstate
 */
int CxFrameListview::GetItemState(int nIndex, int nMode)
{
	// LVM_GETITEMSTATE
	WPARAM wParam = nIndex;
	LPARAM lParam = nMode;
	return static_cast<int>(LVM_GETITEMSTATE, wParam, lParam);
}

/**
 * @brief	取得指定項目 (Item) 文字內容
 * @param	[in]  nIndex	項目索引值   (zero-base)
 * @param	[in]  nSub		項目子欄位索引(zero-base)
 * @param	[out] szTextPtr	字串緩衝區位址
 * @param	[in]  ccLen		要取得字串的長度 (in TCHAR)
 * @return	@c 型別: BOOL \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 * @see		https://docs.microsoft.com/en-us/windows/desktop/controls/lvm-getitemtext
 */
BOOL CxFrameListview::GetItemText(int nIndex, int nSub, LPTSTR szTextPtr, int ccLen)
{
	LVITEM lvi;

	if (szTextPtr == NULL)
		return FALSE;
	
	// Setting properties Of members
	::memset((void*)&lvi, 0, sizeof(LVITEM));
	lvi.mask = LVIF_TEXT;		// LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	lvi.iItem = nIndex;			// choose item
	lvi.iSubItem = nSub;		// choose sub item
	lvi.pszText = szTextPtr;	// push string pointer
	lvi.cchTextMax = ccLen;		// the string length

	// LVM_GETITEMTEXT
	WPARAM wParam = static_cast<WPARAM>(nIndex);		// 項目索引
	LPARAM lParam = reinterpret_cast<LPARAM>(&lvi);		// LVITEM 結構資料位址
	return this->SendMessage(LVM_GETITEMTEXT, wParam, lParam) != 0;
}

/**
 * @brief	取得項目索引，取得下一個被選取項目
 * @return	@c 型別: int \n
 *			函數操作成功返回值為項目(Item)的索引 (zero-base), 若操作失敗返回 -1
 * @see		https://docs.microsoft.com/en-us/windows/desktop/controls/lvm-getnextitem
 */
int CxFrameListview::GetNextSelectItem()
{
	auto nNext = m_nSelectItemIndex;

	// LVM_GETNEXTITEM
	WPARAM wParam = static_cast<WPARAM>(nNext);	// 用於開始搜索項目的索引，-1 以查找與指定標誌匹配的第一個項目，指定的項目本身將被排除在搜索之外。
	LPARAM lParam = LVNI_ALL;					// 指定項目搜尋方式
	nNext = static_cast<int>(this->SendMessage(LVM_GETNEXTITEM, wParam, lParam));

	m_nSelectItemIndex = nNext == -1 ? 0 : nNext;
	return nNext;
}

/**
 * @brief	取得項目索引，取得第一個被選取的項目索引 (選取累計)
 * @return	@c 型別: int \n
 *			函數操作成功返回值為項目(Item)的索引 (zero-base), 若操作失敗返回 -1
 * @see		https://docs.microsoft.com/en-us/windows/desktop/controls/lvm-getnextitem
 */
int CxFrameListview::GetFirstSelectItem()
{
	// LVM_GETNEXTITEM
	// wParam = 用於開始搜索項目的索引，-1 以查找與指定標誌匹配的第一個項目，指定的項目本身將被排除在搜索之外。
	// lParam = 指定項目搜尋方式
	m_nSelectItemCount = this->GetSelectCount();
	m_nSelectItemIndex = static_cast<int>(this->SendMessage(LVM_GETNEXTITEM, -1, LVNI_ALL));
	return m_nSelectItemIndex;
}

/**
 * @brief	取得項目索引，取得第一個被選取項目索引 (無累計，永遠取得第一個)
 * @return	@c 型別: int \n
 *			函數操作成功返回值為項目(Item)的索引 (zero-base), 若操作失敗返回 -1
 * @see		https://docs.microsoft.com/en-us/windows/desktop/controls/lvm-getnextitem
 */
int CxFrameListview::GetSelectItem()
{
	// LVM_GETNEXTITEM
	// wParam = 用於開始搜索項目的索引，-1 以查找與指定標誌匹配的第一個項目，指定的項目本身將被排除在搜索之外。
	// lParam = 指定項目搜尋方式
	return static_cast<int>(this->SendMessage(LVM_GETNEXTITEM, -1, LVNI_SELECTED));
}

/**
 * @brief	取得被選中項目(Item)數量 (光標 or 反白)
 * @return	@c 型別: int \n被選中項目(Item)的數量
 * @remark	取得目前列表上被選取的數量
 */
int CxFrameListview::GetSelectCount()
{
	// LVM_GETSELECTEDCOUNT
	// wParam = 未使用，必須為零
	// lParam = 未使用，必須為零
	return static_cast<int>(this->SendMessage(LVM_GETSELECTEDCOUNT, 0, 0));
}

/**
 * @brief	取得索引，在可視範圍內，於列表最上面項目的索引
 * @return	@c 型別: int \n
 *			位於可是範圍內最上面項目的索引 (zero-base)
 */
int CxFrameListview::GetTopIndex()
{
	// LVM_GETTOPINDEX
	// wParam = 未使用，必須為零
	// lParam = 未使用，必須為零
	return static_cast<int>(this->SendMessage(LVM_GETTOPINDEX, 0, 0));
}

/**
 * @brief	插入一個欄位 (Column)
 * @param	[in] nIndex		欄位項目索引 (zero-base)
 * @param	[in] wd			指定 Column 寬度
 * @param	[in] nAlign		指定對齊方式
 * @param	[in] szTextPtr	指定 Column 顯示文字位址
 * @return	@c 型別: BOOL \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::InsertColumn(int nIndex, int wd, int nAlign, LPTSTR szTextPtr)
{
    const static int aiAssign[] = { LVCFMT_LEFT, LVCFMT_RIGHT, LVCFMT_CENTER, LVCFMT_LEFT };
    LVCOLUMN lvc;

    // zero struct's Members
    ::memset((void*)&lvc, 0, sizeof(LVCOLUMN));
	if (nAlign >= LVCOLUMN_ALIGN_PASSEND) nAlign = LVCOLUMN_ALIGN_LEFT;

	// Setting properties of members
	lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_FMT; // LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvc.fmt = aiAssign[nAlign];
	lvc.pszText = szTextPtr;
    lvc.cchTextMax = static_cast<int>(_tcslen(lvc.pszText));
    lvc.cx = wd;

    // LVM_INSERTCOLUMN 訊息處理，若執行成功將傳回一個索引直，若執行失敗將傳回 -1
	WPARAM wParam = static_cast<WPARAM>(nIndex);	// 欄位索引 zero-base
	LPARAM lParam = reinterpret_cast<LPARAM>(&lvc);	// LVCOLUMN 結構資料位址
    return this->SendMessage(LVM_INSERTCOLUMN, wParam, lParam) != -1;
}

/**
 * @brief	插入一個項目 (Item) - 文字模式
 * @param	[in] nIndex	項目索引值   (zero-base)
 * @param	[in] nSub	項目子欄位索引(zero-base)
 * @param	[in] szTextPtr	字串緩衝區
 * @return	@c 型別: BOOL \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::InsertItem(int nIndex, int nSub, LPTSTR szTextPtr)
{
	LVITEM lvi;

	if (szTextPtr == NULL)
		return FALSE;

	// Setting properties of members
	::memset((void*)&lvi, 0, sizeof(LVITEM));
	lvi.mask = LVIF_TEXT;		// LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	lvi.iItem = nIndex;			// choose item
	lvi.iSubItem = nSub;		// choose sub item
	lvi.pszText = szTextPtr;	// set text
	lvi.cchTextMax = static_cast<int>(_tcslen(lvi.pszText));

	// LVM_INSERTITEM, 若運作失敗將傳回 -1
	WPARAM wParam = 0;								// 未使用，必須為零
	LPARAM lParam = reinterpret_cast<LPARAM>(&lvi);	// LVITEM 結構資料位址
	return this->SendMessage(LVM_INSERTITEM, wParam, lParam) != -1;
}

/**
 * @brief	設定背景顏色
 * @param	[in] dwColor 顏色(RGB)
 * @return	@c 型別: BOOL \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::SetBkColor(COLORREF dwColor)
{
	// LVM_SETBKCOLOR
	WPARAM wParam = 0;								// 未使用，必須為零
	LPARAM lParam = static_cast<LPARAM>(dwColor);	// COLORREF 型別, 背景顏色 RGB(若使用 CLR_NONE 定義值，則為無被景色)
	return this->SendMessage(LVM_SETBKCOLOR, wParam, lParam) != 0;
}

/**
 * @brief	設定指定欄位 (Column) 文字內容
 * @param	[in] nIndex		欄位項目索引 (zero-base)
 * @param	[in] szTextPtr	欲設定文字緩衝區
 * @return	@c 型別: BOOL \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::SetColumn(int nIndex, LPTSTR szTextPtr)
{
    LVCOLUMN lvc;

	if (szTextPtr == NULL)
		return FALSE;
    
	::memset((void*)&lvc, 0, sizeof(LVCOLUMN));
    lvc.mask = LVCF_TEXT;
	lvc.pszText = szTextPtr;

	// LVM_SETCOLUMN
	WPARAM wParam = static_cast<WPARAM>(nIndex);	// 欄位索引 (zero-base)
	LPARAM lParam = reinterpret_cast<LPARAM>(&lvc);	// lParam = LVCOLUMN 結構資料位址
	return this->SendMessage(LVM_SETCOLUMN, wParam, lParam) != 0;
}

/**
 * @brief	設定欄位(Column)寬度
 * @param	[in] nIndex	欄位項目索引 (zero-base)
 * @param	[in] nPixel	欄位寬度 (in pixel) 像素
 * @return	@c 型別: BOOL \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::SetColumnWidth(int nIndex, int nPixel)
{
	// LVM_GETCOLUMNWIDTH
	WPARAM wParam = static_cast<WPARAM>(nIndex);	// 欄位索引 (zero-base)
	LPARAM lParam = static_cast<LPARAM>(nPixel);	// 欄位寬度 (像素)
	return this->SendMessage(LVM_SETCOLUMNWIDTH, wParam, lParam) != 0;
}

/**
 * @brief   設定 ListView 擴展樣式
 * @param	[in] dwExStyle 擴展樣式
 *				- dwExStyle a specifies the extended list-view control style.
 * @return	@c 此函數沒有返回值
 *
 *	Sets the extended styles, \n
 *	that are currently in use for a given list-view control.
 */
void CxFrameListview::SetExListViewStyle(DWORD dwExStyle)
{
	// LVM_SETEXTENDEDLISTVIEWSTYLE
	WPARAM wParam = 0;								// 未使用，必須為零
	LPARAM lParam = static_cast<LPARAM>(dwExStyle);	// Extended List-View Styles. (延伸風格資料)
	this->SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, wParam, lParam);
}

/**
 * @brief	設定項目(Item) 被選取狀態
 * @param	[in] nIndex		項目索引 (zero-base)
 * @param	[in] lvitemPtr	LVITEM 結構資料位址
 * @return	@c 型別: BOOL \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::SetItemState(int nIndex, LPLVITEM lvitemPtr)
{
	// LVM_SETITEMSTATE
	WPARAM wParam = static_cast<WPARAM>(nIndex);			// 項目索引
	LPARAM lParam = reinterpret_cast<LPARAM>(lvitemPtr);	// LVITEM 結構資料位址
	return this->SendMessage(LVM_SETITEMSTATE, wParam, lParam) != 0;
}

/**
 * @brief	設定指定項目(Item)被選中
 * @param	[in] nIndex	項目索引值 (zero-base)
 * @param	[in] bState	選擇狀態 (TRUE為設定被選擇, FALSE為取消被選擇)
 * @return	@c 型別: BOOL \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::SetItemState(int nIndex, BOOL bState)
{
    LVITEM lvi;
    ::memset((void*)&lvi, 0, sizeof(LVITEM));
    lvi.stateMask = LVIS_SELECTED | LVIS_FOCUSED;
    lvi.state = bState ? LVIS_SELECTED | LVIS_FOCUSED : 0;
    return this->SetItemState(nIndex, &lvi);
}

/**
 * @brief	設定指定項目 (Item) 文字內容
 * @param	[in] nIndex		項目索引值   (zero-base)
 * @param	[in] nSub		項目子欄位索引(zero-base)
 * @param	[in] szTextPtr	字串緩衝區位址
 * @return	@c 型別: BOOL \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 * @see		https://docs.microsoft.com/en-us/windows/desktop/controls/lvm-setitemtext
 */
BOOL CxFrameListview::SetItemText(int nIndex, int nSub, LPTSTR szTextPtr)
{
	LVITEM lvi;

	if (NULL == szTextPtr) return FALSE;
	// Setting properties Of members
	::memset((void*)&lvi, 0, sizeof(LVITEM));
	lvi.mask = LVIF_TEXT;		// LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	lvi.iItem = nIndex;			// choose item
	lvi.iSubItem = nSub;		// choose sub item
	lvi.pszText = szTextPtr;	// push the string
	lvi.cchTextMax = ::lstrlen(lvi.pszText);

	// LVM_SETITEMTEXT
	WPARAM wParam = static_cast<WPARAM>(nIndex);	// 項目索引
	LPARAM lParam = reinterpret_cast<LPARAM>(&lvi);	// LVITEM 結構資料位址
	return this->SendMessage(LVM_SETITEMTEXT, wParam, lParam) != 0;
}

/**
 * @brief	設定文字背景顏色
 * @param	[in] dwColor 顏色(RGB)
 * @return	@c 型別: BOOL \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::SetTextBkColor(COLORREF dwColor)
{
	// LVM_SETTEXTBKCOLOR
	WPARAM wParam = 0;								// 未使用，必須為零
	LPARAM lParam = static_cast<LPARAM>(dwColor);	// COLORREF 型別, 背景顏色 RGB(若使用 CLR_NONE 定義值，則為無被景色)
	return this->SendMessage(LVM_SETTEXTBKCOLOR, wParam, lParam) != 0;
}

/**
 * @brief	設定文字顏色
 * @param	[in] dwColor 顏色(RGB)
 * @return	@c 型別: BOOL \n
 *			函數操作成功返回非零值(non-zero), 若失敗返回零(zero)
 */
BOOL CxFrameListview::SetTextColor(COLORREF dwColor)
{
	// LVM_SETTEXTCOLOR
	WPARAM wParam = 0;								// 未使用，必須為零
	LPARAM lParam = static_cast<LPARAM>(dwColor);	// COLORREF 型別, 背景顏色 RGB
	return (BOOL)this->SendMessage(LVM_SETTEXTCOLOR, wParam, lParam);
}

/**
 * @brief	建立 List view controller
 * @param	[in] szCaptionPtr	ListView 名稱字串位址 (ListView 用不著，填入 NULL 即可)
 * @param	[in] x				起始座標 (對應父視窗左上座標 X)
 * @param	[in] y				起始座標 (對應父視窗左上座標 Y)
 * @param	[in] wd				寬度
 * @param	[in] ht				高度
 * @param	[in] hParent		父視窗 Handle
 * @param	[in] idItem			控制項 ID
 * @param	[in] hInst			Handle of module, 若此值為 NULL, 將視為使用現行的程序模組
 * @param	[in] fnWndProc		pointer of callback function
 * @return	@c BOOL \n
 *			函數操作成功返回非零值(non-zero), 操作失敗返回零(zero)\n
 *			操作失敗可調用 CxFrameObject::GetError() 或衍生類別取得失敗錯誤碼.
 */
BOOL CxFrameListview::CreateListview(LPCTSTR szCaptionPtr, int x, int y, int wd, int ht, HWND hParent, int idItem, HINSTANCE hInst, WNDPROC fnWndProc)
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

		ctrl.hParent = hParent;
		ctrl.eType = ECtrlSysListView32;
		ctrl.szNamePtr = NULL;
		ctrl.dwStyle = LVS_REPORT | LVS_SHOWSELALWAYS; // LVS_EDITLABELS;
		ctrl.dwExStyle = 0;
		ctrl.iPosx = x;
		ctrl.iPosy = y;
		ctrl.iWidth = wd;
		ctrl.iHeight = ht;
		ctrl.idItem = idItem;	// conctrller item id
		ctrl.fnWndProc = fnWndProc;
		err = this->CreateController(&ctrl);
		break;
	}
	return err;
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
 * @brief	使用自訂 ListView Report 預設樣式
 * @return	此函數沒有返回值
 */
void CxFrameListview::DefaultReportStyle()
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
 * @remark	如何獲取 ListView 控制項行與列被滑鼠點擊出發事件 \n
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
