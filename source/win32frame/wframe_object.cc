/**************************************************************************//**
 * @file	wframe_object.cc
 * @brief	Win32 視窗操作基底類別 : 成員函式
 * @date	2000-10-10
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#include "win32frame/wframe_object.hh"

//! CxFrameObject 建構式
CxFrameObject::CxFrameObject()
	: m_hModule(NULL)
	, m_hWndParent(NULL)
	, m_hWnd(NULL)
	, m_fnOldWndProc(NULL)
	, m_idItem(NULL)
	, m_idEventTimer(EVENT_IDTIMER_NIL)
	, m_hFontUser(NULL)
	, m_eCtrlType(ECtrlEmpty)
	, m_dwError(ERROR_SUCCESS) {
	this->InitCommCtrl();
}

/**
 * @brief CxFrameObject 建構式
 * @param [in] eType 控制項種類索引
 *
 * 初始化控制項種類索引
 */
CxFrameObject::CxFrameObject(EECTRLTYPE eType)
	: m_hModule(NULL)
	, m_hWndParent(NULL)
	, m_hWnd(NULL)
	, m_fnOldWndProc(NULL)
	, m_idItem(NULL)
	, m_idEventTimer(EVENT_IDTIMER_NIL)
	, m_hFontUser(NULL)
	, m_eCtrlType(eType)
	, m_dwError(ERROR_SUCCESS) {
	this->InitCommCtrl();
}


//! CxFrameObject 解構式
CxFrameObject::~CxFrameObject() {  }


/**
 * @brief	取得錯誤碼
 * @return	@c 型別: DWORD \n
 *			回傳一個錯誤碼, 若傳回值為零(zero)則無錯誤紀錄.
 */
DWORD CxFrameObject::GetError() { return m_dwError; }


/**
 * @brief	設定錯誤碼
 * @param	[in] dwErrCode	錯誤碼
 * @param	[in] szPtr		錯誤訊息
 * @return	沒有返回值
 *
 * 函數運作中, 若有發生錯誤即可進行紀錄. \n
 * 調用函數後若發生失敗, 可調用 GetError 成員函數取得錯誤碼
 */
void CxFrameObject::SetError(DWORD dwErrCode, LPCTSTR szPtr)
{
	m_dwError = dwErrCode;
	// TODO: error message handling
}


/**
 * @brief	顯示錯誤資訊
 * @return	沒有返回值
 */
void CxFrameObject::ShowError()
{
	auto hCtrl = m_hWnd;
	auto dwErr = m_dwError;
	TCHAR sz[BUFF_SIZE_256];
	
	::wsprintf(sz, TEXT("Error Code = %ld (0x%08X)"), dwErr, dwErr);
	::MessageBox(hCtrl, sz, NULL, MB_OK | MB_ICONERROR);
}


/**
 * @brief	視窗訊息傳遞 (等待訊息處理結果)
 * @param	[in] uMessage	訊息碼
 * @param	[in] wParam		參數 1
 * @param	[in] lParam		參數 2
 * @return	@c 型別: LRESULT \n
 *			訊息處理結果，依據指定的訊息結果而定
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-postmessagea
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-postmessagew
 *
 * 這著函數實在沒必要做, 要做也是使用 inline 的方式, 目前只是為了程式美觀和一致性所以先放在這裡。\n
 * 若在頻繁使用時 (其實不可能在繪圖中頻繁使用) 那麼建議移到標頭檔用 inline 的方式
 */
LRESULT CxFrameObject::SendMessage(UINT uMessage, WPARAM wParam, LPARAM lParam)
{ 
	return ::SendMessage(m_hWnd, uMessage, wParam, lParam);
}

/**
* @brief	視窗訊息傳遞 (等待訊息處理結果)
* @param	[in] uMessage	訊息碼
* @param	[in] wParam		參數 1
* @param	[in] lParam		參數 2
* @return	@c 型別: LRESULT \n
*			訊息處理結果，依據指定的訊息結果而定
* @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-sendmessagea
* @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-sendmessagew
*
* 這著函數實在沒必要做, 要做也是使用 inline 的方式, 目前只是為了程式美觀和一致性所以先放在這裡。\n
* 若在頻繁使用時 (其實不可能在繪圖中頻繁使用) 那麼建議移到標頭檔用 inline 的方式
*/
BOOL CxFrameObject::PostMessage(UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	return ::PostMessage(m_hWnd, uMessage, wParam, lParam);
}


//! 離開視窗 (結束視窗或控制項)
void CxFrameObject::LeaveWindow() { this->PostMessage(WM_CLOSE, 0, 0); }


/**
 * @brief	更新視窗
 * @return	@c 型別: BOOL \n
 *			若視窗更新成功將返回非零值(non-zero), 若更新失敗將返回零值(zero).
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-updatewindow
 */
BOOL CxFrameObject::Update() { return ::UpdateWindow(m_hWnd); }


/**
 * @brief	啟用、禁用視窗或控制項操作
 * @param	[in] bEnable	啟用參數為 TEUE、禁用參數為 FALSE
 * @return	@c 型別: BOOL \n
 *			若視窗先前被禁用返回 TRUE, 若視窗先前非禁用返回 FALSE.
 */
BOOL CxFrameObject::Enable(BOOL bEnable) { return ::EnableWindow(m_hWnd, bEnable); }


/**
 * @brief	啟用、禁用視窗或控制項操作
 * @return	@c 型別: BOOL \n
 *			若視窗先前被禁用返回 TRUE, 若視窗先前非禁用返回 FALSE.
 */
BOOL CxFrameObject::Disable() { return ::EnableWindow(m_hWnd, FALSE); }


/**
 * @brief	顯示視窗或控制項
 * @param	[in] nCmdShow	顯示視窗命令參數
 * @return	@c 型別: BOOL \n
 *			若視窗先前為顯示中返回值為 TRUE, 若視窗先前為隱藏中返回值為 FALSE.
 * @remark	顯示視窗命令參數 nCmdShow
 *			- SW_HIDE               隱藏視窗
 *			- SW_SHOWNORMAL         顯示視窗，如果視窗被最小化或最大化，系統將其恢復到原來的尺寸和大小 (初始建立時的大小)
 *			- SW_SHOWMINIMIZED      顯示視窗並以最小化顯示
 *			- SW_SHOWMAXIMIZED      顯示視窗並以最大化顯示
 *			- SW_MAXIMIZE           最大化顯示視窗
 *			- SW_SHOWNOACTIVATE     以視窗最近一次的大小和狀態顯示，活耀狀態視窗仍維活耀狀態。
 *			- SW_SHOW               以原來大小及位置顯示視窗
 *			- SW_MINIMIZE           顯示視窗並最小化，交出活耀狀態給下一個 Z 順位
 *			- SW_SHOWMINNOACTIVE    視窗最小化，但仍保持活耀狀態
 *			- SW_SHOWNA             以原來的狀態顯示視窗，活耀狀態視窗仍維活耀狀態
 *			- SW_RESTORE            顯示視窗並呈現活耀狀態，如果視窗最小化或最大化，則係統將視窗恢復到原來的尺寸和位置，在恢復最小化視窗時，應該指定使用這個方式。
 *			- SW_SHOWDEFAULT        依據在 STARTUPINFO 結構中指定的 FLAG 標誌設定顯示狀態,STARTUPINFO 結構是由啟動應用程序的程序傳遞給 CreateProcess 函數。
 *			- SW_FORCEMINIMIZE      在 Windows NT5.0 中最小化視窗,即使擁有視窗的線程被激活也會最小化。在從其他線程最小化視窗時才使用這個參數。
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-showwindow
 */
BOOL CxFrameObject::Show(int nCmdShow) { return ::ShowWindow(m_hWnd, nCmdShow); }


/**
 * @brief	隱藏視窗或控制項
 * @return	@c 型別: BOOL \n
 *			若視窗先前為顯示中返回值為 TRUE, 若視窗先前為隱藏中返回值為 FALSE.
 * @see		CxFrameObject::Show()
 */
BOOL CxFrameObject::Hide() { return ::ShowWindow(m_hWnd, SW_HIDE); }


/**
 * @brief	取得視窗, 控制項矩形邊界尺寸
 * @param	[out] rcPtr	RECT 結構資料位址
 * @return	@c 型別: BOOL \n
 *			操作成功返回非零值(non-zero), 操作失敗返回零值(zero) \n
 *			失敗可由 CxFrameObject::GetError 或衍生類別取得錯誤碼
 */
BOOL CxFrameObject::GetWindowRect(LPRECT rcPtr)
{
	auto res = ::GetWindowRect(m_hWnd, rcPtr);
	
	if (!res) {
		this->SetError(::GetLastError());
	}
	return res;
}


/**
 * @brief	取得視窗, 控制項工作區, 矩形邊界尺寸
 * @param	[out] rcPtr	RECT 結構指標
 * @return	@c 型別: BOOL \n
 *			操作成功返回非零值(non-zero), 操作失敗返回零值(zero) \n
 *			失敗可由 CxFrameObject::GetError 或衍生類別取得錯誤碼
 */
BOOL CxFrameObject::GetClientRect(LPRECT rcPtr)
{
	auto res = ::GetClientRect(m_hWnd, rcPtr);

	if (!res) {
		this->SetError(::GetLastError());
	}
	return res;
}


/**
 * @brief	取得視窗工作區邊框尺寸
 * @return	@c 型別: int \n
 *			邊界尺寸 (in pixel), 若失敗返回 -1.
 * @remark	取得視窗與工作區的邊界尺寸, 藉以計算出兩者相差值. 視窗尺寸必定大於等於工作區尺寸.
 * @see		CxFrameObject::GetRect
 * @see		CxFrameObject::GetClientRect
 */
int CxFrameObject::GetBorderSize()
{
	auto hWnd = m_hWnd;
	auto result = int(-1);
	RECT rcw, rcc;

	this->SetError(ERROR_SUCCESS);
	
	for (;;) {
		if (hWnd == NULL) {
			this->SetError(ERROR_INVALID_HANDLE);
			break;
		}

		if (!::GetClientRect(hWnd, &rcc)) {
			this->SetError(::GetLastError());
			break;
		}

		if (!::GetWindowRect(hWnd, &rcw)) {
			this->SetError(::GetLastError());
			break;
		}

		result = ((rcw.right - rcw.left) - rcc.right) >> 1;
		break;
	}

	return result;
}


/**
 * @brief	設定(變更)視窗位置
 * @param	[in] x	視窗左上座標 X
 * @param	[in] y	視窗左上座標 Y
 * @return	@c 型別: BOOL \n
 *			操作成功返回非零值(non-zero), 操作失敗返回零值(zero) \n
 *			失敗可由 CxFrameObject::GetError 或衍生類別取得錯誤碼
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-setwindowpos
 */
BOOL CxFrameObject::SetPosition(int x, int y)
{
	const UINT flag = SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE;
	auto res = ::SetWindowPos(m_hWnd, NULL, x, y, 0, 0, flag);

	if (!res) this->SetError(::GetLastError());
	return res;
}


/**
 * @brief	設定(變更)視窗控制項矩形尺寸
 * @param	[in] wd	視窗寬度
 * @param	[in] ht	視窗高度
 * @return	@c 型別: BOOL \n
 *			操作成功返回非零值(non-zero), 操作失敗返回零值(zero) \n
 *			失敗可由 CxFrameObject::GetError 或衍生類別取得錯誤碼
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-setwindowposs
 */
BOOL CxFrameObject::SetSize(int wd, int ht)
{
	const UINT flag = SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE;
	auto res = ::SetWindowPos(m_hWnd, NULL, 0, 0, wd, ht, flag);

	if (!res) this->SetError(::GetLastError());
	return res;
}


/**
 * @brief	設定視窗工作區矩形邊界尺寸
 * @param	[in] wd	視窗寬度
 * @param	[in] ht	視窗高度
 * @return	@c 型別: BOOL \n
 *			操作成功返回非零值, 操作失敗返回零值(zero)\n
 *			失敗可由 CxFrameObject::GetError 或衍生類別取得錯誤碼
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-setwindowposs
 */
BOOL CxFrameObject::SetClientSize(int wd, int ht)
{
	const UINT flag = SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE;
	HWND hWnd = m_hWnd;
	RECT rc;
	BOOL res = FALSE;

	for (;;) {
		if (!::SetRect(&rc, 0, 0, wd, ht)) {
			this->SetError(ERROR_INVALID_FUNCTION);
			break;
		}

		if (!::AdjustWindowRectEx(&rc, ::GetWindowLong(hWnd, GWL_STYLE), ::GetMenu(hWnd) != NULL, 0)) {
			this->SetError(::GetLastError());
			break;
		}

		wd = static_cast<int>(rc.right - rc.left);
		ht = static_cast<int>(rc.bottom - rc.top);

		if (!::SetWindowPos(hWnd, NULL, 0, 0, wd, ht, flag)) {
			this->SetError(::GetLastError());
			break;
		}
		res += TRUE;
		break;
	}

	return res;
}


/**
 * @brief	設定視窗、控制項居中顯示
 * @return	此函數沒有返回值
 * @remark	若發現有父視窗存在, 將會以父視窗為基準. \n
 *			若無父視窗存在, 將以桌面左為基準.
 * @see		CxFrameObject::SetPosition
 * @see		CxFrameObject::SetSize
 * @see		CxFrameObject::SetClientSize
 */
void CxFrameObject::SetCenterPosition()
{
	HWND hWnd = m_hWnd;
	HWND hParent = NULL;

	int  x, y, w, h;
	RECT rc;

	for (;;) {
		if (hWnd == NULL) {
			this->SetError(ERROR_INVALID_HANDLE);
			break;
		}

		if ((hParent = ::GetParent(hWnd)) == NULL) {
			// 取得作業環境畫面邊界
			x = ::GetSystemMetrics(SM_CXSCREEN);
			y = ::GetSystemMetrics(SM_CYSCREEN);
		}
		else {
			// 取得父視窗工作區邊界 (加 1 的用意為了防止被除數 = 0)
			::GetClientRect(hParent, &rc);
			x = static_cast<int>(rc.right - rc.left + 1);
			y = static_cast<int>(rc.bottom - rc.top + 1);
		}

		if (this->GetWindowRect(&rc)) {
			// 計算居中值
			w = static_cast<int>(rc.right - rc.left);
			h = static_cast<int>(rc.bottom - rc.top);
			x = (x - w) >> 1;
			y = (y - h) >> 1;
			this->SetPosition(x, y);
		}
		break;
	}
}


/**
 * @brief	取得當前輸入焦點視窗
 * @return	@c 型別: HWND \n
 *			操作成功返回非零值, 目前焦點的視窗 HANDLE \n
 *			若沒有任何視窗焦點則返回 NULL.
 */
HWND CxFrameObject::GetFocus() { return ::GetFocus(); }


/**
 * @brief	設定視窗為輸入焦點
 * @return	@c 型別: HWND \n
 *			先前擁有輸入焦點的視窗物件的指標, 如果沒有此視窗, 則傳回 NULL
 * @remark	傳回的 HANDLE 指標是暫時的, 所以不應被儲存或轉給給其他函式使用.
 */
HWND CxFrameObject::SetFocus() { return ::SetFocus(m_hWnd); }


/**
 * @brief	取得目前位於最上層的子控制項 Handle
 * @return	@c 型別: HWND \n
 *			操作成功返回, 最上層子控制項 HWND \n
 *			操作失敗返回, NULL，調用 CxFrameObject::GetError 或衍生類別取得錯誤訊息
 * @remark	識別在子視窗連結清單的最上層子視窗，如果子視窗不存在，這個值是 NULL。\n
 *			傳回的指標可能是暫時的，而且不應儲存或供之後使用。
 */
HWND CxFrameObject::GetTopWindow()
{
	auto handle = ::GetTopWindow(m_hWnd);

	if (handle == NULL) {
		this->SetError(::GetLastError());
	}

	return handle;
}


/**
 * @brief	取得視窗或控制項的文字
 * @param	szTextPtr	要接收存放文字字串的緩衝區位址
 * @param	ccLen		要接收多少文字, (in TCHAR)
 * @return	@c 型別: int \n
 *			返回值為實際取得文字數量 (in TCHAR)
 * @see		https://docs.microsoft.com/en-us/windows/desktop/winmsg/wm-gettext
 */
int CxFrameObject::GetText(LPTSTR szTextPtr, size_t ccLen)
{
	// WM_GETTEXT
	WPARAM wParam = static_cast<WPARAM>(ccLen);				// 要接收多少文字 (in TCHAR)
	LPARAM lParam = reinterpret_cast<LPARAM>(szTextPtr);	// 字串的緩衝區位址
	return static_cast<int>(::SendMessage(m_hWnd, WM_GETTEXT, wParam, lParam));
}


/**
 * @brief	取得視窗或控制項的文字長度
 * @return	@c 型別: int \n
 *			返回視窗或控制項文字字串之長度 (不包含字串結尾 NULL), (in TCHAR). \n
 *			若執行失敗將返回 0
 * @see		https://docs.microsoft.com/en-us/windows/desktop/winmsg/wm-gettextlength
 */
int CxFrameObject::GetTextLength()
{
	// WM_GETTEXTLENGTH
	// wParam = 未使用, 必須為零
	// lParam = 未使用, 必須為零
	return static_cast<int>(::SendMessage(m_hWnd, WM_GETTEXTLENGTH, 0, 0));
}


/**
 * @brief	設定文字到視窗或控制項
 * @param	[in] szTextPtr 文字字串存放位址
 * @return	@c 型別: BOOL \n
 *			如果文字設定成功, 返回值為 TRUE.\n
 *			設定失敗返回值 FALSE
 * @see		https://docs.microsoft.com/en-us/windows/desktop/winmsg/wm-settext
  */
BOOL CxFrameObject::SetText(LPCTSTR szTextPtr)
{
	// WM_SETTEXT
	WPARAM wParam = 0;										// 未使用，建議為零
	LPARAM lParam = reinterpret_cast<LPARAM>(szTextPtr);	// 字串位址
	return static_cast<BOOL>(::SendMessage(m_hWnd, WM_SETTEXT, wParam, lParam));
}


/**
 * @brief	取得視窗或控制項的 ICON
 * @param	[in] nType	欲取得圖示的模式.
 *						- ICON_BIG		大圖示
 *						- ICON_SMALL	小圖示
 *						- ICON_SMALL2	小圖示2
 * @return	@c 型別: HICON \n
 *			返回指定模式的圖示 Handle, \n
 *			若沒有設定過圖示，將自動取得系統預設指派的圖示 Handle
 * @see		https://docs.microsoft.com/en-us/windows/desktop/winmsg/wm-geticon
 */
HICON CxFrameObject::GetIcon(int nType)
{
	// Get the window or controller icon
	// WM_GETICON
	WPARAM wParam = static_cast<WPARAM>(nType);	// 取得模式
	LPARAM lParam = 0;							// 未使用，必須為零
	auto icon = reinterpret_cast<HICON>(::SendMessage(m_hWnd, WM_GETICON, wParam, lParam));
	
	// Alternative method. Get from the window class
	if (icon == NULL) {
		icon = reinterpret_cast<HICON>(::GetClassLongPtr(m_hWnd, GCLP_HICONSM));
	}
	// Alternative method: get the first icon from the main module (executable image of the process)
	if (icon == NULL) {
		icon = ::LoadIcon(::GetModuleHandle(0), MAKEINTRESOURCE(0));
	}
	// Alternative method. Use OS default icon
	if (icon == NULL) {
		icon = ::LoadIcon(NULL, IDI_APPLICATION);
	}
	return icon;
}


/**
 * @brief	設定 ICON 圖示到視窗或控制項
 * @param	[in] hIcon	圖示的 Handle
 * @param	[in] nType	要變更的圖示模式
 *						- ICON_BIG,		大圖示
 *						- ICON_SMALL,	小圖示
 * @return	@c 型別: HICON \n
 *			返回上一個所設定的圖示 Handle, 若先前沒有圖示設定, 將返回 NULL.
 * @see		https://docs.microsoft.com/en-us/windows/desktop/winmsg/wm-seticon
 */
HICON CxFrameObject::SetIcon(HICON hIcon, int nType)
{
	// WM_SETICON
	WPARAM wParam = static_cast<WPARAM>(nType);			// 大圖或小圖模式
	LPARAM lParam = reinterpret_cast<LPARAM>(hIcon);	// Handle of icon
	return reinterpret_cast<HICON>(::SendMessage(m_hWnd, WM_SETICON, wParam, lParam));
}


/**
 * @brief	建立邏輯字型
 * @param	[in] fontFace	字型名稱
 * @param	[in] nSize		字型尺寸
 * @param	[in] bBlod		是否要粗體
 * @param	[in] nCharset	指定字符集
 * @return	@c 型別: HFONT \n
 *			如果字型建立成功，返回值是建立字型的 HANDLE \n
 *			如果字型建立失敗，將返回 NULL
 * @remark	利用 Win32 API CreateFontIndirect 函數以 LOGFONT 結構與所述所指定的特徵的邏輯字型 。\n
 *			使用 SelectObject 函數選擇此字型時，GDI的字體映射器會嘗試將邏輯字體與現有的物理字體進行匹配。\n
 *			如果找不到完全匹配，它提供了一個替代方案，其特徵與盡可能多的請求特徵相匹配。
 * @see https://docs.microsoft.com/en-us/windows/desktop/api/wingdi/nf-wingdi-createfontindirectw
 * @see https://docs.microsoft.com/en-us/windows/desktop/api/wingdi/nf-wingdi-createfontindirecta
 */
HFONT CxFrameObject::CreateFont(LPCTSTR fontFace, int nSize, BOOL bBlod, int nCharset)
{
	HDC		hDC = NULL;
	int		iHeight;
	LOGFONT lf;

	this->DeleteFont();
	hDC = ::GetDC(m_hWnd);
	iHeight = -MulDiv(nSize, ::GetDeviceCaps(hDC, LOGPIXELSY), 72);
	::ReleaseDC(m_hWnd, hDC);

	// 設定 LONGFONT 結構內容
	memset((void*)&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = iHeight;                      // 字型高度
	lf.lfWidth = 0;                             // 字型闊度
	lf.lfEscapement = 0;                        // 字型斜度
	lf.lfOrientation = 0;                       // 底線斜度
	lf.lfWeight = bBlod ? FW_BOLD : FW_NORMAL;  // 使用粗體嗎? FW_BOLD : FW_NORMAL
	lf.lfItalic = FALSE;                        // 設定字型為斜體
	lf.lfUnderline = FALSE;                     // 設定字型底線
	lf.lfStrikeOut = FALSE;                     // 設定刪線
	lf.lfCharSet = nCharset;                    // 設定字元集
	lf.lfOutPrecision = OUT_DEFAULT_PRECIS;     // 字型輸出解析度
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;   // 字型擷取解析度
	lf.lfQuality = DEFAULT_QUALITY;             // 字型輪廓質素
	lf.lfPitchAndFamily = 0;                    // 字型的外觀參考(沒有所需字體時用)
	_tcscpy(lf.lfFaceName, fontFace);			// 字型名稱

	// 建立字型
	return ::CreateFontIndirect(&lf);
}


/**
 * @brief	刪除字型
 * @param	[in] hFontPtr 存放字型 HANDLE 位址
 * @return	@c 型別: BOOL \n
 *			如果函數執行成功, 則返回為非零值.\n
 *			如果指定的字型 (handle of font) 無效或被選入DC選用中, 則返回值為零.
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/wingdi/nf-wingdi-deleteobject
 *
 * 刪除自行是利用 Win32 API DeleteObject 進行刪除動作. \n
 * DeleteObject 的相關限制請參照原函數說明.
 */
BOOL CxFrameObject::DeleteFont(HFONT* hFontPtr)
{
	auto err = BOOL(FALSE);

	for (;;) {
		if (hFontPtr == NULL) {
			this->SetError(ERROR_INVALID_DATA);
			break;
		}

		if (*hFontPtr == NULL) {
			this->SetError(ERROR_INVALID_HANDLE);
			break;
		}

		if (!::DeleteObject(*hFontPtr)) {
			this->SetError(ERROR_BUSY);
			break;
		}
		*hFontPtr = NULL;
		err += TRUE;
		break;
	}
	return err;
}


/**
 * @brief	刪除字型 (刪除類別內建立的使用者字型)
 * @return	@c 型別: BOOL 如果函數執行成功, 則返回為非零值.
 */
BOOL CxFrameObject::DeleteFont()
{
	auto err = this->DeleteFont(&m_hFontUser);

	if (err == ERROR_INVALID_HANDLE) {
		// 類別視窗沒有自己建立字型, 所以不算錯誤.
		err += TRUE;
	}
	return err;
}

/**
 * @brief	取得字型 (類別內建立的使用者字型)
 * @return	@c 型別: HFONT 如果函數操作成功返回值為 HFONT, 則返回為非零值.
 */
 HFONT CxFrameObject::GetFont()
 {
	 auto font = m_hFontUser;
	 
	 if (font == NULL) {
		 // WM_GETFONT
		 // wParam = 未使用, 必須為零
		 // lParam = 未使用, 必須為零
		 font = reinterpret_cast<HFONT>(this->SendMessage(WM_GETFONT, 0, 0));
	 }
	 return font;
 }


/**
 * @brief	設定視窗或控制項字型
 * @param	[in] hFont		字型 Handle, 若此值為 NULL 代表指定使用系統預設字型.
 * @param	[in] bRedraw	低字元 (low-word) 表示設定字型時是否立即重新繪製.\n
 *							如果此參數為 TRUE，視窗或控制項本身將會自動重繪。
 * @return	此函數沒有返回值
 * @see		https://docs.microsoft.com/zh-tw/windows/desktop/winmsg/wm-setfont
 */
void CxFrameObject::SetFont(HFONT hFont, BOOL bRedraw)
{
	// WM_SETFONT
	WPARAM wParam = reinterpret_cast<WPARAM>(hFont);	// Handle of font
	LPARAM lParam = static_cast<LPARAM>(bRedraw);		// The control redraws itself? (TRUE or FALSE)
	::SendMessage(m_hWnd, WM_SETFONT, wParam, lParam);
}


/**
 * @brief	設定視窗或控制項字型
 * @param	[in] fontFace	字型名稱
 * @param	[in] nSize		字型尺寸
 * @param	[in] bBlod		是否要粗體
 * @param	[in] nCharset	指定字符集
 * @param	[in] bRedraw	是否立即重新繪製.
 * @return	此函數沒有返回值
 * @see		CreateFont
 */
void CxFrameObject::SetFont(LPCTSTR fontFace, int nSize, BOOL bBlod, int nCharset, BOOL bRedraw)
{
	auto font = HFONT(NULL);

	this->DeleteFont();
	font = this->CreateFont(fontFace, nSize, bBlod, nCharset);

	if (font != NULL) {
		this->SetFont(font);
		m_hFontUser = font;
	}
}


/**
 * @brief	取得視窗、控制項樣式 (Style)
 * @return	@c 型別: DWORD \n
 *			操作成功返回 Sytle 值, 操作失敗返回零(zero) \n
 *			失敗調用 CxFrameObject::GetError 或衍生類別取得錯誤訊息
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-getwindowlongptra
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-getwindowlongptrw
 */
DWORD CxFrameObject::GetStyle()
{
	auto res = ::GetWindowLongPtr(m_hWnd, GWL_STYLE);

	if (!res) {
		this->SetError(::GetLastError());
	}

	return static_cast<DWORD>(res);
}

/**************************************************//**
 * @brief	設定視窗、控制項樣式 (Style)
 * @param	[in] dwStyle 視窗樣式
 * @return	@c 型別: DWORD \n
 *			操作成功返回設定前的 Style 值, 操作失敗返回零(zero). \n
 *			失敗調用 CxFrameObject::GetError 或衍生類別取得錯誤訊息
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-setwindowlongptra
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-setwindowlongptrw
 *****************************************************/
DWORD CxFrameObject::SetStyle(DWORD dwStyle)
{
	auto res = ::SetWindowLongPtr(m_hWnd, GWL_STYLE, (LONG_PTR)dwStyle);

	if (!res) {
		this->SetError(::GetLastError());
	}

	return static_cast<DWORD>(res);
}

/**
 * @brief	取得視窗、控制項擴展樣式 (ExStyle)
 * @return	@c 型別: DWORD \n
 *			操作成功返回 Sytle 擴展值, 操作失敗返回零(zero) \n
 *			失敗調用 CxFrameObject::GetError 或衍生類別取得錯誤訊息
 * @see		CxFrameObject::GetStyle
 */
DWORD CxFrameObject::GetExStyle()
{
	auto res = ::GetWindowLongPtr(m_hWnd, GWL_EXSTYLE);

	if (!res) {
		this->SetError(::GetLastError());
	}

	return static_cast<DWORD>(res);
}

/**
 * @brief	設定視窗、控制項擴展樣式 (ExStyle)
 * @param	[in] dwExStyle	視窗擴展樣式
 * @return	@c 型別: DWORD \n
 *			操作成功返回設定前的 Sytle 擴展值, 操作失敗返回零(zero) \n
 *			失敗調用 CxFrameObject::GetError 或衍生類別取得錯誤訊息
 * @see		CxFrameObject::SetStyle
 */
DWORD CxFrameObject::SetExStyle(DWORD dwExStyle)
{
	auto res = ::SetWindowLongPtr(m_hWnd, GWL_EXSTYLE, (LONG_PTR)dwExStyle);

	if (!res) {
		this->SetError(::GetLastError());
	}

	return static_cast<DWORD>(res);
}


/**
 * @brief	建立計時器
 * @param	[in] nIDEvent		計時器 ID
 * @param	[in] uElapse		延遲時間 (ms) 多少時間觸發一次
 * @param	[in] fnTimerFunc	Timer Callback
 *			- 定時觸發時間是件至指定 Callback
 *			- 若此值為 NULL 計時器會對對視窗發出 WM_TIMER 訊息
 * @return	@c 型別: UINT_PTR
 *			- 如果函數成功並且 hWnd 參數為 NULL，則返回值是標識新計時器的整數。\n
 *			  應用程序可以將此值傳遞給 KillTimer 函數以銷毀計時器。
 *			- 如果函數成功且 hWnd 參數不為 NULL，則返回值為非零整數。\n
 *			  應用程序可以將 nIDEvent 參數的值傳遞給 KillTimer 函數以銷毀計時器。
 * @remark	若此類別物件已存在計時器, 那麼此類別物件會將先前所配置的計時器停止, 並且設定新的計時器.
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-settimer
 **/
UINT_PTR CxFrameObject::SetTimer(UINT_PTR nIDEvent, UINT uElapse, TIMERPROC fnTimerFunc)
{
	auto hCtrl	= m_hWnd;
	auto uTimer	= m_idEventTimer;
	auto err	= UINT_PTR(EVENT_IDTIMER_NIL);

	for (;;) {
		if (hCtrl == NULL) {
			this->SetError(ERROR_INVALID_HANDLE);
			break;
		}

		if (!this->KillTimer()) {
			break;
		}

		// 建立計時器
		if ((uTimer = ::SetTimer(hCtrl, nIDEvent, uElapse, fnTimerFunc)) == 0) {
			this->SetError(::GetLastError());
			break;
		}

		// 為何保存 nIDEvent 而非保存返回值 uTimer?
		// 因為建立時若沒有指定視窗 handle 才必須保存返回值.
		m_idEventTimer = err = nIDEvent;
		break;
	}
	return err;
}

/**************************************************//**
 * @brief	刪除計時器
 * @return	@c 型別: BOOL \n
 *			函數操作成功返回非零值(non-zero), 若操作失敗返回零(zero) \n
 *			若失敗可使用 CxFrameObject::GetError 或衍生類別取得錯誤碼
 *****************************************************/
BOOL CxFrameObject::KillTimer()
{
	auto	hCtrl	= m_hWnd;
	auto	uTimer	= m_idEventTimer;
	auto	err		= BOOL(FALSE);

	for (;;) {
		if (hCtrl == NULL) {
			this->SetError(ERROR_INVALID_HANDLE);
			break;
		}

		if (!uTimer) {
			// 沒有配置計時器，在這不算錯誤。
			this->SetError(ERROR_TIMER_RESOLUTION_NOT_SET);
			err += TRUE;
			break;
		}

		if (!::KillTimer(hCtrl, uTimer)) {
			// 刪除計時器真的出錯了
			this->SetError(::GetLastError());
			break;
		}

		m_idEventTimer = EVENT_IDTIMER_NIL;
		err += TRUE;
		break;
	}

	return err;
}


/**
 * @brief	取得程序模組 Handle
 * @return	@c 型別: HINSTANCE \n
 *			返回程序模組 hanlde，若視窗尚未建立將傳回 NULL
 */
HINSTANCE CxFrameObject::GetModule() { return m_hModule; }


/**
 * @brief	取得父視窗操作 Handle
 * @return	@c 型別: HWND \n
 *			返回父視窗操作 handle，若非子項目將傳回 NULL
 */
HWND CxFrameObject::GetParent()
{
	auto hCtrl		= m_hWnd;
	auto hParent	= m_hWndParent;
	auto err		= BOOL(FALSE);

	for (;;) {
		if (hCtrl == NULL) {
			this->SetError(ERROR_INVALID_WINDOW_HANDLE);
			break;
		}

		if (hParent == NULL) {
			if ((hParent = ::GetParent(hCtrl)) == NULL) {
				this->SetError(::GetLastError());
				// 只保取得錯誤資訊，因為有可能根本沒父視窗，所以此函數不列為錯誤
				err += TRUE;
				break;
			}
		}
		break;
	}
	return hParent;
}


/**
 * @brief	取得視窗或控制項操作 Handle
 * @return	@c 型別: HWND \n
 *			返回視窗操作 handle，若視窗尚未建立將傳回 NULL
 */
HWND CxFrameObject::GetHandle() { return m_hWnd; }


/**
 * @brief	取得視窗或控制項操作 ID
 * @return	@c 型別: inc	\n 
 *			返回值為視窗或控制項 ID \n
 *			若控制項已建立將返回控制項ID, 若控制項尚未建立將返回零值(zero)
 */
int  CxFrameObject::GetControlID() { return m_idItem; }


/**
 * @brief	驗證是否建立視窗或控制項
 * @return	@c 型別: BOOL \n
 *			視窗或控制項已存在將返回非零值(non-zero), 尚未建立視窗或控制項將返回零值(zero)
 */
BOOL CxFrameObject::IsExist() { return m_hWnd != NULL; }


/**
 * 視窗結束處理 (釋放配置記憶體與成員物件)
 *
 * 此為虛擬函數, 由衍生類別繼承 \n
 * 視窗進入關閉階段時進行運作此一函數, 確保類別內所配置的物件與記憶體都被釋放. \n
 * 壁面物件或記憶體未釋放造成 memory leek.
 */
void CxFrameObject::WindowInTheEnd()
{
	auto hCtrl	= m_hWnd;
	auto fnProc = m_fnOldWndProc;

	// Stop or delete in window object or memory setting
	if (::IsWindow(hCtrl)) {
		this->KillTimer();

		// back to old callback function
		if (fnProc != NULL) {
			::SetWindowLongPtr(hCtrl, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(fnProc));
			m_fnOldWndProc = NULL;
		}
	}

	// Other Object
	this->DeleteFont();
}


/**
* @brief	關閉視窗處理
* @return	@c 型別: 此函數沒有返回值
* @remark	使用者處理視窗終結前動作 \n
*			完畢後呼叫 Win32 API - DestroyWindow 摧毀視窗或控制項
*/
void CxFrameObject::SysCloseWindow()
{
	this->WindowInTheEnd();
	::DestroyWindow(m_hWnd);
}


/**
* @brief	視窗被摧毀處理
* @param	[in] nExitCode 結束視窗返回碼
* @return	此函數沒有返回值
* @remark	使用者摧毀處理, 完畢後呼叫 Win32API PostQuitMessage 結束訊息迴圈
*/
void CxFrameObject::SysDestroyWindow(int nExitCode)
{
	// The window has been destroyed, Any thing to do?
	::PostQuitMessage(nExitCode);
}


/**
 * @brief	設定 WndProc callback 呼叫位址
 * @param	[in] fnWndProc 新的 callback function 位址
 * @return	@c 型別: BOOL \n
 *			函數操作成功返回非零值(non-zero), 失敗返回零值(zero) \n
 *			失敗調用 CxFrameObject::GetError 或衍生類別取得錯誤碼
 */
BOOL CxFrameObject::SysSetWindowProcess(WNDPROC fnWndProc)
{
	auto hCtrl	= m_hWnd;
	auto fnProc	= m_fnOldWndProc;
	auto result	= LONG_PTR(0);
	auto param	= LONG_PTR(0);

	for (;;)  {
		if (hCtrl == NULL) {
			this->SetError(ERROR_INVALID_HANDLE);
			break;
		}

		if (fnWndProc == NULL) {
			this->SetError(ERROR_NO_CALLBACK_ACTIVE);
			break;
		}

		if (fnProc != NULL) {
			// 保存資料中有使用者 WndProc 紀錄, 進行恢復改變前的 WndProc
			param = reinterpret_cast<LONG_PTR>(fnProc);
			::SetLastError(0);
			result = ::SetWindowLongPtr(hCtrl, GWLP_WNDPROC, param);
			if (!result) {
				this->SetError(::GetLastError());
				break;
			}
			m_fnOldWndProc = fnProc = NULL;
		}

		param = reinterpret_cast<LONG_PTR>(fnWndProc);
		::SetLastError(0);
		result = ::SetWindowLongPtr(hCtrl, GWLP_WNDPROC, param);
		if (!result) {
			this->SetError(::GetLastError());
			break;
		}

		m_fnOldWndProc = fnProc = reinterpret_cast<WNDPROC>(result);
		break;
	}
	return fnProc != NULL;
}


/**
 * 指定使用擴展通用 Window 控制項
 *
 * 指定使用 ComboBox, ListView Tab...等等的擴充控制項. \n
 * 若採用 XP-Style 呈現 Windows 各版本風格樣式, 那麼就必須運作此函數。
 */
void CxFrameObject::InitCommCtrl()
{
	// 在此設定一個靜態識別旗標，令所有繼承者，不會重複指定通用控制項
	static auto bCommctrl = BOOL(FALSE);
	INITCOMMONCONTROLSEX icce;

	if (!bCommctrl) {
		// 指定啟用全部控制項
		icce.dwSize = sizeof(INITCOMMONCONTROLSEX);
		icce.dwICC = ICC_WIN95_CLASSES;
		if (::InitCommonControlsEx(&icce)) bCommctrl = TRUE;
	}
}
