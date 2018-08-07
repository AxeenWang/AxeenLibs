/**************************************************************************//**
 * @file	wframe_listbox.cc
 * @brief	Win32 視窗操作 : 控制項 List Box 類別 - 成員函式
 * @date	2000-10-10
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#include "win32frame/wframe_listbox.hh"

//! CxFrameListbox 建構式
CxFrameListbox::CxFrameListbox() : CxFrameControl(ECtrlListBox) { }

//! CxFrameListbox 解構式
CxFrameListbox::~CxFrameListbox() { }

/**
 * @brief	新增檔案項目
 * @param	[in] szFilePtr	檔案名稱字串緩衝區位址
 * @return	@c 型別: int \n
 *			函數操作成功返回值為新增項目項目的索引 (zero-base), 操作失敗返回 LB_ERR
 **/
int CxFrameListbox::AddFile(LPTSTR szFilePtr)
{
	// LB_ADDFILE
	WPARAM wParam = 0;										// 未使用，必須為零
	LPARAM lParam = reinterpret_cast<LPARAM>(szFilePtr);	// 檔案名稱存放位址
	return static_cast<int>(this->SendMessage(LB_ADDFILE, wParam, lParam));
}

/**
 * @brief	新增項目
 * @param	[in] szTextPtr	字串緩衝區位址
 * @return	@c 型別: int \n
 *			函數操作成功返回值為新增項目項目的索引 (zero-base), 操作失敗返回 LB_ERR
 */
int CxFrameListbox::AddItem(TCHAR * szTextPtr)
{
	// LB_ADDSTRING
	WPARAM wParam = 0;										// 未使用，必須為零
	LPARAM lParam = reinterpret_cast<LPARAM>(szTextPtr);	// 字串反衝區位址
	return static_cast<int>(this->SendMessage(LB_ADDSTRING, wParam, lParam));
}

/**
 * @brief	刪除一個項目
 * @param	[in] nIndex	項目索引 (zero-base)
 * @return	@c 型別: int \n
 *			函數操作成功返回值為現存項目數量, 操作失敗返回 LB_ERR
 */
int CxFrameListbox::DeleateItem(int nIndex)
{
	// LB_DELETESTRING
	WPARAM wParam = static_cast<WPARAM>(nIndex);		// 項目索引 (zero-base)
	LPARAM lParam = 0;									// 未使用，必須為零
	return static_cast<int>(this->SendMessage(LB_DELETESTRING, wParam, lParam));
}

/**
 * @brief	增加一個目錄下指定內容至列表
 * @param	[in] nAttrib	屬性
 *				- DDL_ARCHIVE	包括存檔文件
 *				- DDL_DIRECTORY	包括子目錄。子目錄名稱括在方括號（[]）中。
 *				- DDL_DRIVES	所有映射的驅動器都將添加到列表中。驅動器以[ - x - ] 的形式列出，其中x是驅動器號。
 *				- DDL_EXCLUSIVE	僅包含具有指定屬性的文件。默認情況下，即使未指定 DDL_READWRITE，也會列出讀/寫文件。
 *				- DDL_HIDDEN	包含隱藏文件。
 *				- DDL_READONLY	包括唯讀文件
 *				- DDL_READWRITE	包括沒有其他屬性的讀/寫文件。這是預設設置。
 *				- DDL_SYSTEM	包括系統文件。
 * @param	[in] szPathPtr	目錄路徑名稱或萬用檔案名稱
 *				- 例如, 路徑名稱 "c:\\folder\\"
 *				- 例如, 萬用名稱 "c:\\folder\\*.exe"
 * @return	@c 型別: int \n
 *			函數操作成功返回值為新增項目項目的索引(zero-base), 若操作失敗返回 LB_ERR
 */
int CxFrameListbox::AddDir(int nAttrib, LPTSTR szPathPtr)
{
	// LB_DIR
	WPARAM wParam = static_cast<WPARAM>(nAttrib);			// 屬性
	LPARAM lParam = reinterpret_cast<LPARAM>(szPathPtr);	// 目錄的路徑名稱字串位址
	return static_cast<int>(this->SendMessage(LB_DIR, wParam, lParam));
}

/**
 * @brief	於列表中找尋第一個與輸入字串相符的項目
 * @param	[in] nIndex		指定起始項目索引 (zero-base)
 * @param	[in] szTextPtr	字串存放位址
 * @return	@c 型別: int \n
 *			函數操作成功返回值為第一個吻合項目的索引(zero-base), 若操作失敗傳回: LB_ERR
 */
int CxFrameListbox::FindItem(int nIndex, LPTSTR szTextPtr)
{
	// LB_FINDSTRING
	WPARAM wParam = static_cast<WPARAM>(nIndex);			// 起始項目索引 (zero-base)
	LPARAM lParam = reinterpret_cast<LPARAM>(szTextPtr);	// 要找尋的字串位址
	return static_cast<int>(this->SendMessage(LB_FINDSTRING, wParam, lParam));
}

/**
 * @brief	於列表中找尋第一個與輸入字串完全相符的項目 (不區分大小寫)
 * @param	[in] nIndex	指定起始項目索引 (zero-base)
 * @param	[in] szTextPtr	字串存放位址
 * @return	@c 型別: int \n
 *			函數操作成功返回值為第一個完全相符項目的索引(zero-base), 操作失敗返回 LB_ERR
 */
int CxFrameListbox::FindItemEx(int nIndex, LPTSTR szTextPtr)
{
	// LB_FINDSTRINGEXACT
	WPARAM wParam = static_cast<WPARAM>(nIndex);			// 起始項目索引 (zero-base)
	LPARAM lParam = reinterpret_cast<LPARAM>(szTextPtr);	// 要找尋的字串位址
	return static_cast<int>(this->SendMessage(LB_FINDSTRINGEXACT, wParam, lParam));
}

/**
 * @brief	取得目前列表中項目數量
 * @return	@c 型別: int \n
 *			函數操作成功返回值為現存項目數量, 若操作失敗返回 LB_ERR
 */
int CxFrameListbox::GetCount()
{
	// LB_GETCOUNT
	// wParam = 未使用，必須為零
	// lParam = 未使用，必須為零
	return static_cast<int>(this->SendMessage(LB_GETCOUNT, 0, 0));
}

/**
 * @brief	取得列表選擇光棒索引 (當前被選取的項目索引)
 * @return	@c 型別: int \n
 *			函數操作成功返回值為目前列表光棒索引 (當前被選取項目索引) (zero-base) \n
 *			若操作失敗傳回: LB_ERR
 */
int CxFrameListbox::GetCursel()
{
	// LB_GETCURSEL
	// wParam = 未使用，必須為零
	// lParam = 未使用，必須為零
	return static_cast<int>(this->SendMessage(LB_GETCURSEL, 0, 0));
}

/**
 * @brief	取得指定項目的矩形資料 (此項目必須於列表顯示中)
 * @param	[in]		nIndex	指定項目索引 (zero-base)
 * @param	[in,out]	rcPtr	RECT 結構指標
 * @return	@c 型別: int \n
 *			函數操作成功返回不為 LB_ERR 的任意值, 若操作失敗傳回 LB_ERR
 */
int CxFrameListbox::GetItemRect(int nIndex, LPRECT rcPtr)
{
	// LB_GETITEMRECT
	WPARAM wParam = static_cast<WPARAM>(nIndex);			// 項目索引 (zero-base)
	LPARAM lParam = reinterpret_cast<LPARAM>(rcPtr);		// RECT 結構資料存放位址
	return static_cast<int>(this->SendMessage(LB_GETITEMRECT, wParam, lParam));
}

/**
 * @brief	取得指定項目的被選用狀態
 * @param	[in]	nIndex	指定項目索引 (zero-base)
 * @return	@c 型別: int \n
 *			函數操作成功返回非零值 = 項目被選用中, (零 = 項目沒有被選用) \n
 *			若操作失敗傳回: LB_ERR
 */
int CxFrameListbox::GetSelectionState(int nIndex)
{
	// LB_GETSEL
	WPARAM wParam = static_cast<WPARAM>(nIndex);			// 項目索引 (zero-base)
	LPARAM lParam = 0;										// 未使用，必須為零
	return static_cast<int>(this->SendMessage(LB_GETSEL, wParam, lParam));
}

/**
 * @brief	取得被選取項目數量 (若列表風格被設定為 single-selection, 必定傳回 LB_ERR)
 * @return	@c 型別: int \n
 *			函數操作成功返回值為被選取項目的數量, 操作失敗返回 LB_ERR
 **/
int CxFrameListbox::GetSelectionCount()
{
	// LB_GETSELCOUNT
	// wParam = 未使用，必須為零
	// lParam = 未使用，必須為零
	return static_cast<int>(this->SendMessage(LB_GETSELCOUNT, 0, 0));
}

/**
 * @brief	取得指定項目的文字內容
 * @param	[in]		nIndex		項目索引 (zero-base)
 * @param	[in,out]	szTextPtr	存放項目字串位址
 * @return	@c 型別: int \n
 *			函數操作成功返回值為指定項目文字長度, 單位 TCHAR (不含結尾 null) \n
 *			若操作失敗返回 LB_ERR
 */
int CxFrameListbox::GetItemText(int nIndex, LPTSTR szTextPtr)
{
	// LB_GETTEXT
	WPARAM wParam = static_cast<WPARAM>(nIndex);			// 項目索引 (zero-base)
	LPARAM lParam = reinterpret_cast<LPARAM>(szTextPtr);	// 欲存放項目字串的位址
	return static_cast<int>(this->SendMessage(LB_GETTEXT, wParam, lParam));
}

/**
 * @brief	取得指定項目的文字長度
 * @param	[in] nIndex	項目索引 (zero-base)
 * @return	@c 型別: int \n
 *			函數操作成功返回值為指定項目文字長度, 單位 TCHAR (不含結尾 null) \n
 *			若操作失敗返回 LB_ERR
 */
int CxFrameListbox::GetItemTextLength(int nIndex)
{
	// LB_GETTEXTLEN
	WPARAM wParam = static_cast<WPARAM>(nIndex);			// 項目索引 (zero-base)
	LPARAM lParam = 0;										// 未使用，必須為零
	return static_cast<int>(this->SendMessage(LB_GETTEXTLEN, wParam, lParam));
}

/**
 * @brief	插入一個項目
 * @param	[in] nIndex		指定項目索引 (zero-base), 若此參數被設定為 -1, 則插入到列表最後
 * @param	[in] szTextPtr	欲插入字串的位址
 * @return	@c 型別: int \n
 *			函數操作成功返回值為新增項目索引 (zero-base), 若操作失敗返回 LB_ERR
 */
int CxFrameListbox::InsertItem(int nIndex, LPTSTR szTextPtr)
{
	// LB_INSERTSTRING
	WPARAM wParam = static_cast<WPARAM>(nIndex);			// 項目索引
	LPARAM lParam = reinterpret_cast<LPARAM>(szTextPtr);	// 要新增的字串位址
	return static_cast<int>(this->SendMessage(LB_INSERTSTRING, wParam, lParam));
}

/**
 * @brief	設定選取光標位置
 * @param	[in] nIndex	指定項目索引 (zero-base), 若此參數被設定為 -1, 則取消選擇光棒
 * @return	@c 型別: int \n
 *			函數操作成功返回值為目前列表光棒索引 (當前被選取項目索引) (zero-base) \n
 *			若操作失敗返回 LB_ERR
 */
int CxFrameListbox::SetCursel(int nIndex)
{
	// LB_SETCURSEL
	WPARAM wParam = static_cast<WPARAM>(nIndex);	// 項目索引 (zero-base)
	LPARAM lParam = 0;								// lParam = 未使用，必須為零
	return static_cast<int>(this->SendMessage(LB_SETCURSEL, wParam, lParam));
}

/**
 * @brief	設定被選取狀態
 * @param	[in] nIndex	項目索引 (zero-base)
 * @param	[in] bState	被選取狀態
 *			- TRUE	= 設定被選取 (加入 multiple-selection 群)
 *			- FALSE	= 取消被選取
 * @return	@c 型別: int \n
 *			函數操作成功返回值為非 LB_ERR 的任意值 \n
 *			若操作失敗傳回: LB_ERR
 */
int CxFrameListbox::SetSelectionState(int nIndex, BOOL bState)
{
	// LB_SETSEL
	WPARAM wParam = static_cast<WPARAM>(bState);	// 被選取狀態，(TRUE 被選取)、(FALSE 取消選取)
	LPARAM lParam = static_cast<LPARAM>(nIndex);	// 項目索引 (zero-base)
	return static_cast<int>(this->SendMessage(LB_SETSEL, wParam, lParam));
}

/**
 * @brief	建立 List Box (資源檔建立或其他已建立的 List Box)
 * @param	[in] hInst		Handle of module. 若為 NULL 將視為使用現行程序模組
 * @param	[in] hList		控制項 Handle
 * @param	[in] idItem		控制項 ID
 * @param	[in] fnWndProc	使用者自訂 Callback function 位址
 * @return	@c 型別: BOOL \n
 *			若函數操作成功返回非零值(non-zero), 失敗將返回零值(zero)
 */
BOOL CxFrameListbox::CreateListbox(HINSTANCE hInst, HWND hList, int idItem, WNDPROC fnWndProc)
{
	return this->CreateController(hInst, hList, idItem, fnWndProc);
}

/**
* @brief	建立 List Box (資源檔建立或其他已建立的 List Box)
* @param	[in] hInst		Handle of module. 若為 NULL 將視為使用現行程序模組
* @param	[in] hParent	父視窗 Handle
* @param	[in] idItem		控制項 ID
* @param	[in] fnWndProc	User defined callback function address
* @return	@c 型別: BOOL \n
*			若函數操作成功返回非零值(non-zero), 失敗將返回零值(zero)
*/
BOOL CxFrameListbox::CreateListboxEx(HINSTANCE hInst, HWND hParent, int idItem, WNDPROC fnWndProc)
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
void CxFrameListbox::WindowInTheEnd()
{
	// TODO: 結束視窗處理
	CxFrameControl::WindowInTheEnd();
}
