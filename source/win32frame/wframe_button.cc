/**************************************************************************//**
 * @file	wframe_button.cc
 * @brief	Win32 視窗操作 : 控制項 Button 類別 - 成員函式
 * @date	2000-10-10
 * @date	2018-07-24
 * @author	Swang
 *****************************************************************************/
#include "win32frame/wframe_button.hh"

//! CxFrameButton 建構式
CxFrameButton::CxFrameButton() : CxFrameControl(ECtrlButton) { }

//! CxFrameButton 解構式
CxFrameButton::~CxFrameButton() { }

/**
 * @brief	取得按鈕理想的大小
 * @details	如果存在圖像列表，則獲取最適合其文本和圖像的按鈕的大小。
 * @param	[in,out] sizePtr SIZE 結構資料位址
 *			- 若 SIZE.cx 與 SIZE.cy 皆為零，自動取得理想值
 *			- 若 SIZE.cx 不為零，則依據 cx 取得理想的 cy 值
 * @return	@c BOOL \n
 *			函數操作成功返回非零值(non-zero), 操作失敗返回零(zero)\n
 */
BOOL CxFrameButton::GetIdealSize(SIZE * sizePtr)
{
	// BCM_GETIDEALSIZE
	// wParam = 未使用，必須為零
	// lParam = SIZE 結構資料位址
	return (BOOL)this->SendMessage(BCM_GETIDEALSIZE, 0, reinterpret_cast<LPARAM>(sizePtr));
}


/**
 * @brief	取得按鈕的圖像列表
 * @param	[in,out] imlPtr BUTTON_IMAGELIST 結構資料位址
 * @return	@c BOOL \n
 *			函數操作成功返回非零值(non-zero), 操作失敗返回零(zero)\n
 */
BOOL CxFrameButton::GetImageList(BUTTON_IMAGELIST * imlPtr)
{
	// BCM_GETIDEALSIZE
	// wParam = 未使用，必須為零
	// lParam = BUTTON_IMAGELIST 結構資料位址
	return (BOOL)this->SendMessage(BCM_GETIMAGELIST, 0, reinterpret_cast<LPARAM>(imlPtr));
}


/**
 * @brief	取得連接控制項註解說明文本
 * @param	[out]		szNotePtr	緩衝區位址
 * @param	[in,out]	ccNotePtr	描述緩衝區大小的變數存放位址
 * @return	@c BOOL \n
 *			若返回值為非零值(non-zero), 則 szNotePtr 緩衝區的內容為當前命令與連接的控制項說明文本。\n
 *			若返回值為零(zero) 則 ccNotePtr 內容為實際需要緩衝區的大小。
 */
BOOL CxFrameButton::GetNote(LPTSTR szNotePtr, DWORD* ccNotePtr)
{
	// BCM_GETNOTE
	// wParam = [in ] 描述緩衝區大小 [out] 實際緩衝區大小
	// lParam = [out] 用於接收文本的字串緩衝區，緩衝區必須足夠大，大到可以容納 NULL 結尾符號。
	return (BOOL)this->SendMessage(
		BCM_GETNOTE,
		reinterpret_cast<WPARAM>(ccNotePtr),
		reinterpret_cast<LPARAM>(szNotePtr)
	);
}


/**
 * @brief	取得聯經控制項註解說明文本的大小
 * @return	@c DWORD \n
 *			單位 TCHAR 的文本長度，不包含 NULL 結尾符號。
 */
DWORD CxFrameButton::GetNoteLength()
{
	// BCM_GETNOTELENGTH
	// wParam = 未使用，必須為零
	// lParam = 未使用，必須為零
	return (DWORD)this->SendMessage(BCM_GETNOTELENGTH, 0, 0);
}


/**
 * @brief	發送按鈕 Click 訊息
 * @remark	額外說明
 *			- 模擬用戶單擊按鈕。
 *			- 此消息使按鈕接收 WM_LBUTTONDOWN 和 WM_LBUTTONUP 消息。
 *			- 按鈕的父窗口接收 BN_CLICKED 通知代碼。
 */
void CxFrameButton::Click()
{
	// BM_CLICK
	// wParam = 未使用，必須為零
	// lParam = 未使用，必須為零
	this->PostMessage(BM_CLICK, 0, 0);
}


/**
 * @brief	獲取單選按鈕或複選框(CheckBox)的檢查狀態
 * @return	@c LRESULT
 *			- BST_CHECKED		按鈕被選中
 *			- BST_INDETERMINATE	按鈕呈灰色，表示不確定狀態（僅在按鈕具有BS_3STATE或BS_AUTO3STATE樣式時適用）
 *			- BST_UNCHECKED		按鈕選中狀態被清除
 */
LRESULT CxFrameButton::GetCheck()
{
	// BM_GETCHECK
	// wParam = 未使用，必須為零
	// lParam = 未使用，必須為零
	return this->SendMessage(BM_GETCHECK, 0, 0);
}


/**
 * @brief	取得按鈕的圖像 Handle
 * @param	[in] iType 圖像類型
 *			- IMAGE_BITMAP	取得 Bitmap
 *			- IMAGE_ICON	取得 Icon
 * @return	@c LRESULT \n
 *			函數操作成功返回圖像 Handle, 若操作失敗返回 NULL
 */
LRESULT CxFrameButton::GetImage(int iType)
{
	// BM_GETIMAGE
	// wParam = 圖像種類
	// lParam = 未使用，必須為零
	return this->SendMessage(BM_GETIMAGE, (WPARAM)iType, 0);
}


/**
 * @brief	取得按鈕的圖像 Handle
 * @return	@c HBITMAP
 *			函數操作成功返回圖像 Handle, 若操作失敗返回 NULL
 */
HBITMAP CxFrameButton::GetImageBitmap()
{
	return reinterpret_cast<HBITMAP>(this->GetImage(IMAGE_BITMAP));
}


/**
 * @brief	取得按鈕的圖像 Handle
 * @return	@c HICON
 *			函數操作成功返回圖像 Handle, 若操作失敗返回 NULL
 */
HICON CxFrameButton::GetImageIcon()
{
	return reinterpret_cast<HICON>(this->GetImage(IMAGE_ICON));
}


/**
 * @brief	取得單選按鈕或複選框狀態
 * @return	@c LRESULT
 *			- BST_CHECKED			該按鈕被選中
 *			- BST_DROPDOWNPUSHED	Windows Vista。該按鈕處於下拉狀態。僅當按鈕具有TBSTYLE_DROPDOWN樣式時才適用
 *			- BST_FOCUS				該按鈕具有鍵盤焦點
 *			- BST_HOT				火熱狀態，也就是說，滑鼠游標停在它上面
 *			- BST_INDETERMINATE		按鈕的狀態是不確定的，僅當按鈕具有BS_3STATE或BS_AUTO3STATE樣式時才適用
 *			- BST_PUSHED			按鈕顯示處於按下狀態
 *			- BST_UNCHECKED			為被選中，沒有特殊的狀態，相當於零
 */
LRESULT CxFrameButton::GetState()
{
	// BM_GETSTATE
	// wParam = 未使用，必須為零
	// lParam = 未使用，必須為零
	return this->SendMessage(BM_GETSTATE, 0, 0);
}

/**
 * @brief	設置單選按鈕或複選框的檢查狀態
 * @param	[in] iCheck	設定按鈕 Cechk 狀態值
 *			- BST_CHECKED		將按鈕狀態設置為選中(選取中)
 *			- BST_INDETERMINATE	將按鈕狀態設置為灰色，表示不確定狀態。僅當按鈕具有BS_3STATE或BS_AUTO3STATE樣式時才使用此值。
 *			- BST_UNCHECKED		將按鈕狀態設置為清除(未選取)
 * @return	@c LRESULT	傳回值始終為零
 */
LRESULT CxFrameButton::SetCheck(int iCheck)
{
	// BM_SETCHECK
	// wParam = iCheck
	// lParam = 未使用，必須為零
	return this->SendMessage(BM_SETCHECK, (WPARAM)iCheck, 0);
}

/**
 * @brief	單選按鈕上設置狀態。
 * @param	[in] bState	設定按鈕 State 狀態值
 *			- TRUE	設定按鈕為觸發狀態(按下、被選中、發光)
 *			- FALSE	清除按鈕所有被設定狀態
 */
void CxFrameButton::SetRadioClick(BOOL bState)
{
	// BM_SETDONTCLICK 傳回值始終為 0
	// wParam = 狀態值
	// lParam = 未使用，必須為零
	// this->SendMessage(BM_SETDONTCLICK, (WPARAM)bState, 0);
	this->PostMessage(BM_SETDONTCLICK, (WPARAM)bState, 0);
}

/**
 * @brief	設定按鈕的圖像
 * @param	[in] iType 圖像類型
 *			- IMAGE_BITMAP	取得 Bitmap
 *			- IMAGE_ICON	取得 Icon
 * @param	[in] vPtr	圖像 HANDLE
 * @return	@c LRESULT \n
 *			若先前有圖像返回值為圖像 HANDLE, 若先前無圖像則返回 NULL
 */
LRESULT CxFrameButton::SetImage(int iType, void * vPtr)
{
	if (iType != IMAGE_BITMAP && iType != IMAGE_ICON)
		return NULL;

	// BM_SETIMAGE
	// wParam = 圖像種類
	// lParam = 圖像 HANDLE
	return this->SendMessage(BM_SETIMAGE, iType, reinterpret_cast<LPARAM>(vPtr));
}


/**
 * @brief	設定按鈕的圖像
 * @param	[in] hBitmap 圖像 HANDLE
 * @return	@c LRESULT \n
 *			若先前有圖像返回值為圖像 HANDLE, 若先前無圖像則返回 NULL
 */
LRESULT CxFrameButton::SetImageBitmap(HBITMAP hBitmap)
{
	// BM_SETIMAGE
	// wParam = 圖像種類
	// lParam = 圖像 HANDLE
	return this->SendMessage(BM_SETIMAGE, IMAGE_BITMAP, reinterpret_cast<LPARAM>(hBitmap));
}


/**
 * @brief	設定按鈕的圖像
 * @param	[in] hIcon 圖像 HANDLE
 * @return	@c LRESULT \n
 *			若先前有圖像返回值為圖像 HANDLE, 若先前無圖像則返回 NULLL
 */
LRESULT CxFrameButton::SetImageIcon(HICON hIcon)
{
	// BM_SETIMAGE
	// wParam = 圖像種類
	// lParam = 圖像 HANDLE
	return this->SendMessage(BM_SETIMAGE, IMAGE_ICON, reinterpret_cast<LPARAM>(hIcon));
}


/**
 * @brief	設定單選按鈕或複選框狀態
 * @param	[in] bState	設定按鈕 State 狀態值
 *			- TRUE	設定按鈕為觸發狀態(按下、被選中、發光)
 *			- FALSE	清除按鈕所有被設定狀態
 * @return	@c LRESULT	傳回值始終為零
 */
LRESULT CxFrameButton::SetState(BOOL bState)
{
	// BM_SETSTATE
	// wParam = 指定按鈕狀態
	// lParam = 未使用，必須為 0
	return this->SendMessage(BM_SETSTATE, (WPARAM)bState, 0);
}

/**
 * @brief	設定按鈕樣式
 * @param	[in] dwStyle	按鈕樣式
 * @param	[in] bRepaint	使否重繪 TRUE/FALSE
 * @see		ButtonStyleDocument
 */
void CxFrameButton::SetStyle(DWORD dwStyle, BOOL bRepaint)
{
	// BM_SETSTYLE
	// wParam = Style (樣式)
	// lParam = 是否重繪 (存於 LOWORD)
	this->PostMessage(BM_SETSTYLE, static_cast<WPARAM>(dwStyle), static_cast<LPARAM>(bRepaint));
}


/**
 * @brief	建立 Button
 * @param	[in] szCaptionPtr	按鈕名稱字串位址
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
BOOL CxFrameButton::CreateButton(LPCTSTR szCaptionPtr, int x, int y, int wd, int ht, HWND hParent, int idItem, HINSTANCE hInst, WNDPROC fnWndProc)
{
	BOOL		err = FALSE;
	SSCTRL		ctrl;

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
		ctrl.hParent = hParent;
		ctrl.eType = ECtrlButton;
		ctrl.szNamePtr = szCaptionPtr;
		ctrl.dwStyle = WS_TABSTOP | BS_PUSHBUTTON;
		ctrl.dwExStyle = 0;
		ctrl.iPosx = x;
		ctrl.iPosy = y;
		ctrl.iWidth = wd;
		ctrl.iHeight = ht;
		ctrl.idItem = idItem;
		ctrl.fnWndProc = fnWndProc;
		ctrl.vUnknowPtr = NULL;	// pointer of user data
		err = this->CreateController(&ctrl);
		break;
	}
	return err;
}

/**
 * @brief	建立 Button (資源檔建立或其他已建立的 Button)
 * @param	[in] hInst		Handle of module. 若為 NULL 將視為使用現行程序模組
 * @param	[in] hButton	控制項 Handle
 * @param	[in] idItem		控制項 ID
 * @param	[in] fnWndProc	使用者自訂 Callback function 位址
 * @return	@c BOOL \n
 *			若函數操作成功返回非零值(non-zero), 失敗將返回零值(zero)
 */
BOOL CxFrameButton::CreateButton(HINSTANCE hInst, HWND hButton, int idItem, WNDPROC fnWndProc)
{
	return this->CreateController(hInst, hButton, idItem, fnWndProc);
;
}


/**
 * @brief	建立 Button (資源檔建立或其他已建立的 Button)
 * @param	[in] hInst		Handle of module. 若為 NULL 將視為使用現行程序模組
 * @param	[in] hParent	父視窗 Handle
 * @param	[in] idItem		控制項 ID
 * @param	[in] fnWndProc	User defined callback function address
 * @return	@c BOOL \n
 *			若函數操作成功返回非零值(non-zero), 失敗將返回零值(zero)
 */
BOOL CxFrameButton::CreateButtonEx(HINSTANCE hInst, HWND hParent, int idItem, WNDPROC fnWndProc)
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
void CxFrameButton::WindowInTheEnd()
{
	// TODO: 結束視窗處理
	CxFrameControl::WindowInTheEnd();
}
