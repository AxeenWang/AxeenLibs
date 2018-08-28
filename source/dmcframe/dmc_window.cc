/**************************************************************************//**
 * @file	dmc_window.cc
 * @brief	DMC Frame Window 基底類別
 * @date	2000-10-10
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#include "dmcframe/dmc_window.hh"

//! DmWindow constructor
DmWindow::DmWindow()
	: DmObject()
	, m_hWnd(NULL)
	, m_fnPrevWndProc(NULL)
	, m_bAttach(FALSE) {
}

//! DmWindow deconstructor
DmWindow::~DmWindow() { }

/**
 * @brief	連接一個新的視窗(控制項)
 * @param	[in] hWnd 視窗操作 Handle (Handle of Window)
 * @return	@c 型別: BOOL \n
 *			若連接成功，返回非零值(non-zero), 若連接失敗返回值零(zero)
 */
BOOL DmWindow::Attach(HWND hWnd)
{
	auto res = BOOL(FALSE);

	assert(::IsWindow(hWnd));		// 有效的視窗操作代碼?
	assert(!this->IsWindow());		// 視窗已被定義

	for (;;) {
		if (hWnd == NULL) {
			this->SetError(DMCERR::ERR_INVALID_HANDLE);
			break;
		}

		if (this->IsWindow()) {
			this->SetError(DMCERR::ERR_EXIST_HWND);
			break;
		}

		this->AttachToClass(hWnd);
		res = this->GetSafeHwnd() != NULL;
		break;
	}
	return res;
}

/**
 * @brief	連接控制項
 * @param	[in] uID		控制項 ID
 * @param	[in] hWndParent	父視窗的 Handle (Handle of window)
 * @return	@c 型別: BOOL \n
 *			若連接成功，返回非零值(non-zero), 若連接失敗返回值零(zero)
 */
BOOL DmWindow::AttachDlgItem(UINT uID, HWND hWndParent)
{
	assert(::IsWindow(hWndParent));
	HWND hWnd = ::GetDlgItem(hWndParent, uID);
	return this->Attach(hWnd);
}

/**
 * @brief	斷開連接視窗或控制項
 * @return	@c 型別: HWND \n
 *			若 class 有連接視窗或控制項傳回非零值(non-zero)為原連接視窗或控制項的 Handle (Handle of window) \n
 *			若 class 沒有與視窗連接將傳回零(zero) NULL
 */
HWND DmWindow::Detach()
{
	auto fncc = m_fnPrevWndProc;
	auto hWnd = HWND(NULL);

	assert(fncc);
	for (;;) {
		if (fncc == NULL) {
			this->SetError(DMCERR::ERR_INVALID_FUNCTION);
			break;
		}

		if (!this->IsWindow()) {
			this->SetError(DMCERR::ERR_INVALID_HWND);
			break;
		}

		hWnd = this->GetSafeHwnd();
		::SetWindowLongPtr(hWnd, GWLP_USERDATA, 0);
		::SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(fncc));
		m_hWnd = NULL;
		m_fnPrevWndProc = NULL;
		break;
	}
	return hWnd;
}

//! 摧毀視窗
void DmWindow::Destroy()
{
	if (this->IsWindow()) {
		::DestroyWindow(*this);
	}
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
LRESULT DmWindow::SendMessage(UINT uMessage, WPARAM wParam, LPARAM lParam) const
{
	assert(this->IsWindow());
	return ::SendMessage(*this, uMessage, wParam, lParam);
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
BOOL DmWindow::PostMessage(UINT uMessage, WPARAM wParam, LPARAM lParam) const
{
	assert(this->IsWindow());
	return ::PostMessage(*this, uMessage, wParam, lParam);
}

/**
 * @brief	視窗訊息傳遞 (等待訊息處理結果)
 * @param	[in] hWnd		視窗操作碼
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
LRESULT DmWindow::SendMessage(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam) const
{
	assert(this->IsWindow());
	return ::SendMessage(hWnd, uMessage, wParam, lParam);
}

/**
* @brief	視窗訊息傳遞 (等待訊息處理結果)
* @param	[in] hWnd		視窗操作碼
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
BOOL DmWindow::PostMessage(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam) const
{
	assert(this->IsWindow());
	return ::PostMessage(hWnd, uMessage, wParam, lParam);
}

/**
 * @brief	傳送視窗訊息給先前的處理函數
 * @param	[in] lpPrevWndFunc	使用 SetWindowLongPtr 取得的訊息處理函數位址
 * @param	[in] uMessage		視窗訊息
 * @param	[in] wParam			參數 1
 * @param	[in] lParam			參數 2
 * @return	@c 型別: LRESULT \n
 *			訊息處理結果，依據指定的訊息結果而定
 */
LRESULT DmWindow::CallWindowProc(WNDPROC lpPrevWndFunc, UINT uMessage, WPARAM wParam, LPARAM lParam) const
{
	assert(this->IsWindow());
	return ::CallWindowProc(lpPrevWndFunc, *this, uMessage, wParam, lParam);
}

/**
 * @brief	調用預設視窗處理函數
 * @param	[in] uMessage		視窗訊息
 * @param	[in] wParam			參數 1
 * @param	[in] lParam			參數 2
 * @return	@c 型別: LRESULT \n
 *			訊息處理結果，依據指定的訊息結果而定
 *
 *	若使用者程序視窗不處理的訊息，則交由預設的視窗處理函數進行處理 \n
 *	此函數功能可確保處理每條訊息，使用參數與使用者視窗訊息處理函數相同。
 */
LRESULT DmWindow::DefWindowProc(UINT uMessage, WPARAM wParam, LPARAM lParam) const
{
	assert(this->IsWindow());
	return ::DefWindowProc(*this, uMessage, wParam, lParam);
}

/**
 * @brief	更新視窗
 * @return	@c 型別: BOOL \n
 *			若視窗更新成功將返回非零值(non-zero), 若更新失敗將返回零值(zero).
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-updatewindow
 */
BOOL DmWindow::UpdateWindow() const
{
	assert(this->IsWindow());
	return ::UpdateWindow(*this);
}

/**
 * @brief	啟用、禁用視窗或控制項操作
 * @param	[in] bEnable	啟用參數為 TEUE、禁用參數為 FALSE
 * @return	@c 型別: BOOL \n
 *			若視窗先前被禁用返回 TRUE, 若視窗先前非禁用返回 FALSE.
 */
BOOL DmWindow::EnableWindow(BOOL bEnable) const
{
	assert(this->IsWindow());
	return ::EnableWindow(*this, bEnable);
}

/**
 * @brief	啟用、禁用視窗或控制項操作
 * @return	@c 型別: BOOL \n
 *			若視窗先前被禁用返回 TRUE, 若視窗先前非禁用返回 FALSE.
 */
BOOL DmWindow::DisableWindow() const
{
	assert(this->IsWindow());
	return ::EnableWindow(m_hWnd, FALSE);
}

/**
 * @brief	顯示視窗或控制項
 * @param	[in] nCmdShow	顯示視窗命令參數, 預設使用 SW_SHOWNORMAL
 * @return	@c 型別: BOOL \n
 *			若視窗先前為顯示中返回值為 TRUE, 若視窗先前為隱藏中返回值為 FALSE.
 * @remark	顯示視窗命令參數 nCmdShow
 *			- SW_HIDE               隱藏視窗
 *			- SW_SHOWNORMAL         顯示視窗，如果視窗被最小化或最大化，系統將其恢復到原來的尺寸(最大化或最小化前的尺寸)
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
BOOL DmWindow::ShowWindow(int nCmdShow) const
{
	assert(this->IsWindow());
	return ::ShowWindow(*this, nCmdShow);
}

/**
 * @brief	隱藏視窗或控制項
 * @return	@c 型別: BOOL \n
 *			若視窗先前為顯示中返回值為 TRUE, 若視窗先前為隱藏中返回值為 FALSE.
 * @see		CxFrameObject::Show()
 */
BOOL DmWindow::HideWindow() const 
{
	assert(this->IsWindow());
	return ::ShowWindow(*this, SW_HIDE);
}

/**
 * @brief	取得視窗, 控制項矩形邊界尺寸
 * @param	[out] rcPtr	RECT 結構資料位址
 * @return	@c 型別: BOOL \n
 *			操作成功返回非零值(non-zero), 操作失敗返回零值(zero)
 */
BOOL DmWindow::GetWindowRect(RECT* rcPtr) const
{
	assert(this->IsWindow());
	assert(rcPtr);
	return ::GetWindowRect(*this, rcPtr);
}

/**
 * @brief	取得視窗, 控制項工作區, 矩形邊界尺寸
 * @param	[out] rcPtr	RECT 結構指標
 * @return	@c 型別: BOOL \n
 *			操作成功返回非零值(non-zero), 操作失敗返回零值(zero)
 */
BOOL DmWindow::GetClientRect(RECT* rcPtr) const
{
	assert(this->IsWindow());
	assert(rcPtr);
	return ::GetClientRect(*this, rcPtr);
}

/**
 * @brief	取得視窗工作區邊框尺寸
 * @return	@c 型別: int \n
 *			邊界尺寸 (in pixel), 若失敗返回 -1.
 * @remark	取得視窗與工作區的邊界尺寸, 藉以計算出兩者相差值. 視窗尺寸必定大於等於工作區尺寸.
 * @see		DmWindow::GetWindowRect
 * @see		DmWindow::GetClientRect
 */
int DmWindow::GetBorderSize()
{
	assert(this->IsWindow());

	auto hWnd = this->GetSafeHwnd();
	auto result = int(-1);
	RECT rcw, rcc;

	for (;;) {
		if (hWnd == NULL) {
			break;
		}

		if (!::GetClientRect(hWnd, &rcc)) {
			break;
		}

		if (!::GetWindowRect(hWnd, &rcw)) {
			break;
		}

		result = ((rcw.right - rcw.left) - rcc.right) >> 1;
		break;
	}

	return result;
}

/**
 * @brief	改變視窗位置 Z 順序及視窗尺寸
 * @param	[in] hWndInsertAfter	視窗 Handle，用於標示 Z 順序中定位視窗之前。\n
 *									若 uFlags 參數中設置了 SWP_NOZORDER 標記則本參數將被忽略。參數必須是視窗 Handle 或 參數值
 * @param	[in] x		以 client 座標指定視窗新位置 (左邊界)
 * @param	[in] y		以 client 座標指定視窗新位置 (上邊界)
 * @param	[in] cx		以像素 (pixel) 指定新視窗寬度
 * @param	[in] cy		以像素 (pixel) 指定新視窗高度
 * @param	[in] uFlags	視窗尺寸和定位的標誌
 * @return	@c 型別: BOOL \n
 *			如果函數成功，返回值為非零值(non-zero)。\n
 *			如果函數失敗，返回值為零, 若想獲得更多錯誤消息，請調用 GetLastError 函數函數
 *
 * @remark	@c hWndInsertAfter 參數值
 *		- HWND_BOTTOM		\n
 *			將視窗置於 Z 順序的底部如果參數的 hWnd 標識了一個頂層視窗，則視窗失去頂級位置，並且被置在其他視窗的底部。
 *		- HWND_NOTOPMOST	\n
 *			將視窗置於所有非頂層視窗之上（即在所有頂層視窗之後）如果視窗已經是非頂層視窗則該標誌不起作用。
 *		- HWND_TOP			\n
 *			將視窗置於 Z 順序的頂部。
 *		- HWND_TOPMOST		\n
 *			將視窗置於所有非頂層視窗之上即使視窗未被激活視窗也將保持頂級位置。
 *
 * @remark	@c uFlags 標示內容
 *		- SWP_ASYNCWINDOWPOS	\n
 *			如果調用進程不擁有視窗，系統會向擁有視窗的線程發出需求這就防止調用線程在其他線程處理需求的時候發生死鎖。
 *		- SWP_DEFERERASE		\n
 *			防止產生WM_SYNCPAINT訊息。
 *		- SWP_DRAWFRAME			\n
 *			在視窗周圍畫一個邊框（定義在視窗類描述中）。
 *		- SWP_FRAMECHANGED		\n
 *			給視窗發送 WM_NCCALCSIZE訊息，即使視窗尺寸沒有改變也會發送該訊息如果未指定這個標誌，只有在改變了視窗尺寸時才發送WM_NCCALCSIZE。
 *		- SWP_HIDEWINDOW		\n
 *			隱藏視窗。
 *		- SWP_NOACTIVATE		\n
 *			不激活視窗如果未設置標誌，則視窗被激活，並被設置到其他最高級視窗或非最高級組的頂部（根據參數hWndlnsertAfter設置）。
 *		- SWP_NOCOPYBITS		\n
 *			清除客戶區的所有內容如果未設置該標誌，客戶區的有效內容被保存並且在視窗尺寸更新和重定位後拷貝回客戶區。
 *		- SWP_NOMOVE			\n
 *			維持當前位置（忽略X和Ÿ參數）。
 *		- SWP_NOOWNERZORDER		\n
 *			不改變 Z 順序中的所有者視窗的位置。
 *		- SWP_NOREDRAW			\n
 *			不重畫改變的內容如果設置了這個標誌，則不發生任何重畫動作適用於客戶區和非客戶區（包括標題欄和滾動條）和任何由於窗回移動而露出的父視窗的所有部分。\n
 *			如果設置了這個標誌，應用程序必須明確地使視窗無效並區重畫視窗的任何部分和父視窗需要重畫的部分。
 *		- SWP_NOREPOSITION		\n
 *			與 SWP_NOOWNERZORDER 標誌相同。
 *		- SWP_NOSENDCHANGING	\n
 *			防止視窗接收WM_WINDOWPOSCHANGING訊息。
 *		- SWP_NOSIZE			\n
 *			維持當前尺寸（忽略CX和賽揚參數）。
 *		- SWP_NOZORDER			\n
 *			維持當前ž序（忽略hWndlnsertAfter參數）。
 *		- SWP_SHOWWINDOW		\n
 *			顯示視窗。
 * @see	https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-setwindowpos
 */
BOOL DmWindow::SetWindowPos(HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags) const
{
	assert(IsWindow());
	return ::SetWindowPos(*this, hWndInsertAfter, x, y, cx, cy, uFlags);
}

/**
 * @brief	開始向指定的視窗進行繪製
 * @param	[in] stPtr	pointer of PAINTSTRUCT structure
 * @return	@c 型別: HDC \n
 *			若操作成功返回非零值(non-zero)為視窗輸出顯示裝置 Handle \n
 *			若操作失敗返回零(zero) NULL, 表示沒有輸出裝置可用
 */
HDC DmWindow::BeginPaint(PAINTSTRUCT* stPtr) const
{
	assert(this->IsWindow());
	assert(stPtr);
	return ::BeginPaint(*this, stPtr);
}

/**
 * @brief	結束向指定的視窗繪製
 * @param	[in] stPtr	pointer of PAINTSTRUCT structure
 * @return	@c 型別: BOOL, 始終返回非零值(non-zero)
 * @remark	每次使用 BeginPaint 都要使用 EndPaint 來結束。
 */
BOOL DmWindow::EndPaint(const PAINTSTRUCT * stPtr) const
{
	assert(IsWindow());
	return ::EndPaint(*this, stPtr);
}

/**
 * @brief	變更視窗屬性
 * @param	[in] nIndex		指定變更項目
 *				- GWL_EXSTYLE
 *				- GWL_STYLE
 *				- GWLP_WNDPROC
 *				- GWLP_HINSTANCE
 *				- GWLP_HWNDPARENT
 *				- GWLP_ID
 *				- GWLP_USERDATA
 *				- DWLP_DLGPROC
 *				- DWLP_MSGRESULT
 *				- DWLP_USER
 * @return	@c 型別: LONG_PTR \n
 *			若函數操作成功返回值為提出需求的資訊 \n
 *			若操作失敗返回零，使用 GetLastError() 取得錯誤碼
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-getwindowlongptrw
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-getwindowlongptra
 */
LONG_PTR DmWindow::GetWindowLongPtr(int nIndex) const
{
	assert(IsWindow());
	return ::GetWindowLongPtr(*this, nIndex);
}

/**
 * @brief	變更視窗屬性
 * @param	[in] nIndex		指定變更項目
 *				- GWL_EXSTYLE
 *				- GWL_STYLE
 *				- GWLP_WNDPROC
 *				- GWLP_HINSTANCE
 *				- GWLP_HWNDPARENT
 *				- GWLP_ID
 *				- GWLP_USERDATA
 *				- DWLP_DLGPROC
 *				- DWLP_MSGRESULT
 *				- DWLP_USER
 * @param	[in] dwNewLong	變更內容
 * @return	@c 型別: LONG_PTR \n
 *			若函數操作成功返回值為變更前的資訊 \n
 *			若操作失敗返回零，使用 GetLastError() 取得錯誤碼
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-setwindowlongptrw
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-setwindowlongptra
 */
LONG_PTR DmWindow::SetWindowLongPtr(int nIndex, LONG_PTR dwNewLong) const
{
	assert(this->IsWindow());
	return ::SetWindowLongPtr(*this, nIndex, dwNewLong);
}

/**
 * @brief	取得視窗或控制項操作 Handle (Handle of window)
 * @return	@c 型別: HWND \n
 *			返回非零值(non-zero)為目前於類別物件內使用的視窗或控制項操作 Handle (Handle of window) \n
 *			若類別誤建尚未連結則傳回零(zero) NULL
 */
HWND DmWindow::GetSafeHwnd() const { return m_hWnd; }

/**
 * @brief	取得父視窗操作碼
 * @return	@c 型別: HWND \n
 *			若有父視窗將返回非零值(non-zero)為父視窗操作 Handle \n
 *			若沒有父視窗則返回零 (zero) NULL
 */
HWND DmWindow::GetParent() const
{
	assert(this->IsWindow());
	return ::GetParent(this->GetSafeHwnd());
}

/**
 * @brief	取得改變前的視窗(控制項) Callback function
 */
WNDPROC DmWindow::GetPrevWndProc() const { return m_fnPrevWndProc; }

/**
 * @brief	檢驗是否為有效的視窗(控制項)操作 Handle
 * @return	@c 型別: BOOL \n
 *			若為有效的視窗或控制項操作代碼則返回一個非零值(non-zero) \n
 *			若不是一個視窗或控制項操作代碼則返回零(zero)
 */
BOOL DmWindow::IsWindow() const { return ::IsWindow(*this); }

/**
 * @brief	對應返回值 HWND 自動型別轉換
 * @return	@c 型別: HWND \n
 *			返回目前類別誤建政再使用的視窗(控制項)操作碼
 * @see		DmWindow::GetSafeHwnd()
 */
DmWindow::operator HWND() const { return this->GetSafeHwnd(); }

/**
 * @brief	視窗訊息處理 Callback function
 * @param	[in] uMessage	視窗訊息
 * @param	[in] wParam		參數 1
 * @param	[in] lParam		參數 2
 * @return	@c LRESULT \n
 *			視窗操作結果, 依據視窗訊息操作有所不同.
 */
LRESULT DmWindow::DefaultWindowProc(UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	auto fncc = m_fnPrevWndProc;	
	if (fncc != NULL)
		return ::CallWindowProc(fncc, *this, uMessage, wParam, lParam);
	return ::DefWindowProc(*this, uMessage, wParam, lParam);
}

/**
 * @brief	視窗訊息處理 WM_CLOSE
 * @return	@c 此函數沒有返回值
 *
 *	視窗收到被關閉命令，可以繼續進行關閉式窗動作，呼叫 DestroyWindow 來摧毀視窗。
 *	亦可無式關閉動作，繼續使用視窗。
 */
void DmWindow::OnClose()
{
	::DestroyWindow(*this);
}

/**
 * @brief	視窗訊息處理 WM_DESTROY
 * @return	@c 此函數沒有返回值
 */
void DmWindow::OnDestroy()
{
	this->DeathOfWindow();
	::PostQuitMessage(0);
}

/**
 * @brief	視窗訊息處理 Callback function
 * @param	[in] uMessage	視窗訊息
 * @param	[in] wParam		參數 1
 * @param	[in] lParam		參數 2
 * @return	@c LRESULT \n
 *			視窗操作結果, 依據視窗訊息操作有所不同.
 */
LRESULT DmWindow::WndProc(UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_DESTROY:
		this->OnDestroy();
		break;
	case WM_CLOSE:
		this->OnClose();
		break;
	default:
		return this->DefaultWindowProc(uMessage, wParam, lParam);
	}
	return 0;
}

/**
 * @brief	視窗(控制項)結束了，進行善後處理。
 * @return	此函數沒有返回值
 *
 *	恢復被改變的對象或連結 \n
 *	刪除所有新增與視窗搭配的項目
 */
void DmWindow::DeathOfWindow()
{
	auto hWnd = this->GetSafeHwnd();
	assert(this->IsWindow());

	if (hWnd != NULL) {
		if (m_fnPrevWndProc != NULL) {
			::SetWindowLongPtr(hWnd, GWLP_USERDATA, 0);
			::SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_fnPrevWndProc));
		}
		m_hWnd = NULL;
		m_fnPrevWndProc = NULL;
	}

	// call base class 
	DmObject::ClassInTheEnd();
}

/**
 * @brief	DmWindow constructor
 * @param	[in] hWnd 視窗(控制項)操作 Handle
 * @remark	這是私有成員，僅供 DmWindow 內部運算用。
 */
DmWindow::DmWindow(HWND hWnd) : m_hWnd(NULL), m_fnPrevWndProc(NULL), m_bAttach(FALSE)
{
	if (hWnd == NULL) {
		this->SetError(DMCERR::ERR_INVALID_HWND);
		return;
	}
	m_hWnd = hWnd;
}

/**
 * @brief	視窗訊息處理 Callback function
 * @param	[in] hWnd		視窗 Handle
 * @param	[in] uMessage	視窗訊息
 * @param	[in] wParam		參數 1
 * @param	[in] lParam		參數 2
 * @return	@c LRESULT \n
 *			視窗操作結果, 依據視窗訊息操作有所不同.
 * @remark	此項必須為靜態函數，為視窗 Callback function
 */
LRESULT DmWindow::StaticWindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	DmWindow* fmObj = NULL;

	// If use CreateWindow() or CreateWindowEx create a window will be have this message
	if (uMessage == WM_CREATE) {
		fmObj = (DmWindow*)((LPCREATESTRUCT)lParam)->lpCreateParams;
		if (fmObj != NULL) {
			fmObj->m_hWnd = hWnd;
			::SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)fmObj);
		}
	}

	// get user saved data form "GWLP_USERDATA" mode
	if ((fmObj = (DmWindow*)::GetWindowLongPtr(hWnd, GWLP_USERDATA)) == NULL) {
		return ::DefWindowProc(hWnd, uMessage, wParam, lParam);
	}

	// transfer window message in user callback function
	return fmObj->WndProc(uMessage, wParam, lParam);
}

/**
 * @brief	設定新增子視窗或控制項處理
 * @param	[in] hWnd 視窗或控制項操作 Handle
 */
void DmWindow::AttachToClass(HWND hWnd)
{
	assert(::IsWindow(hWnd));

	if (::IsWindow(hWnd)) {
		m_hWnd = hWnd;
		m_bAttach = TRUE;
		::SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);
		m_fnPrevWndProc = reinterpret_cast<WNDPROC>(::SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(DmWindow::StaticWindowProc)));
	}
}
