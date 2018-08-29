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
 *			若連接成功，返回非零值(nonzero), 若連接失敗返回值零(zero)
 */
BOOL DmWindow::Attach(HWND hWnd)
{
	auto res = BOOL(FALSE);

	assert(::IsWindow(hWnd));		// 有效的視窗操作代碼?
	assert(!this->IsWindow());		// 視窗已被定義

	for (;;) {
		if (hWnd == NULL) {
			// error handling at here
			break;
		}

		if (this->IsWindow()) {
			// error handling at here
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
 *			若連接成功，返回非零值(nonzero), 若連接失敗返回值零(zero)
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
 *			若 class 有連接視窗或控制項傳回非零值(nonzero)為原連接視窗或控制項的 Handle (Handle of window) \n
 *			若 class 沒有與視窗連接將傳回零(zero) NULL
 */
HWND DmWindow::Detach()
{
	auto fncc = m_fnPrevWndProc;
	auto hWnd = HWND(NULL);

	assert(fncc);
	assert(!this->IsWindow());

	for (;;) {
		if (fncc == NULL) {
			// error handling at here
			break;
		}

		if (!this->IsWindow()) {
			// error handling at here
			break;
		}

		hWnd = this->GetSafeHwnd();
		::SetWindowLongPtr(hWnd, GWLP_USERDATA, 0);
		::SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(fncc));
		m_hWnd = NULL;
		m_bAttach = FALSE;
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
 *			若視窗更新成功將返回非零值(nonzero), 若更新失敗將返回零值(zero).
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
	return ::EnableWindow(*this, FALSE);
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
 * @see		DmWindow::ShowWindow
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
 *			操作成功返回非零值(nonzero), 操作失敗返回零值(zero)
 */
BOOL DmWindow::GetWindowRect(RECT* rcPtr) const
{
	assert(rcPtr);
	assert(this->IsWindow());
	return ::GetWindowRect(*this, rcPtr);
}

/**
 * @brief	取得視窗, 控制項工作區, 矩形邊界尺寸
 * @param	[out] rcPtr	RECT 結構指標
 * @return	@c 型別: BOOL \n
 *			操作成功返回非零值(nonzero), 操作失敗返回零值(zero)
 */
BOOL DmWindow::GetClientRect(RECT* rcPtr) const
{
	assert(rcPtr);
	assert(this->IsWindow());
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
int DmWindow::GetBorderSize() const
{
	auto hWnd = this->GetSafeHwnd();
	auto result = int(-1);
	RECT rcw, rcc;

	assert(this->IsWindow());

	for (;;) {
		if (hWnd == NULL) {
			// error handling at here
			break;
		}

		if (!::GetClientRect(hWnd, &rcc)) {
			// error handling at here
			break;
		}

		if (!::GetWindowRect(hWnd, &rcw)) {
			// error handling at here
			break;
		}

		result = ((rcw.right - rcw.left) - rcc.right) >> 1;
		break;
	}

	return result;
}

/**
 * @brief	將 client-area 座標轉化成桌面座標
 * @param	[in,out] ptPtr	POINT 結構資料存放位址
 * @return	@c 型別: BOOL \n
 *			若函數操作成功返回非零值(nonzero) \n
 *			若含數操作失敗返回零值(zero)
 * @remark	@c ptPtr 參數
 *			- 輸入 client-area 座標
 *			- 輸出 若函數操作成功則會保存轉化後結果
 */
BOOL DmWindow::ClientToScreen(POINT* ptPtr) const
{
	assert(ptPtr);
	assert(this->IsWindow());
	return ::ClientToScreen(*this, ptPtr);
}

/**
 * @brief	將 client-area 座標轉化成桌面座標
 * @param	[in,out] rcPtr	RECT 結構資料存放位址
 * @return	@c 型別: BOOL \n
 *			若函數操作成功返回非零值(nonzero) \n
 *			若含數操作失敗返回零值(zero)
 * @remark	使用 MapWindowPoints 方式
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-mapwindowpoints
 */
BOOL DmWindow::ClientToScreen(RECT* rcPtr) const
{
	assert(IsWindow());

	// MapWindowPoints (
	//	HWND    hWndFrom,	//!< 來源視窗，若值為 NULL 或 HWND_DESKTOP, 則以桌面作為目標
	//	HWND    hWndTo,		//!< 目標視窗，若值為 NULL 或 HWND_DESKTOP, 則以桌面作為目標
	//	LPPOINT lpPoints,	//!< 來源是座標
	//	UINT    cPoints		//!< 傳入了多少組 POINT, 若傳入 RECT 結構，此值必須填寫為 2
	// );
	return static_cast<BOOL>(::MapWindowPoints(*this, NULL, reinterpret_cast<LPPOINT>(rcPtr), 2));
}

/**
 * @brief	改變視窗位置、 Z軸順序、視窗尺寸
 * @param	[in] hWndInsertAfter	視窗 Handle，用於標示 Z 順序中定位視窗之前。
 * @param	[in] x		client-area 座標指定視窗新位置 (左邊界)
 * @param	[in] y		client-area	座標指定視窗新位置 (上邊界)
 * @param	[in] cx		以像素 (pixel) 指定新視窗寬度
 * @param	[in] cy		以像素 (pixel) 指定新視窗高度
 * @param	[in] uFlags	視窗尺寸和定位的標誌
 * @return	@c 型別: BOOL \n
 *			如果函數成功，返回值為非零值(nonzero)。\n
 *			如果函數失敗，返回值為零, 若想獲得更多錯誤消息調用 GetLastError
 *
 * @remark	@c hWndInsertAfter 參數值額外說明 \n
 *			若 uFlags 參數中設置了 SWP_NOZORDER 標記則本參數將被忽略。參數必須是視窗 Handle 或 參數值
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
	assert(this->IsWindow());
	return ::SetWindowPos(*this, hWndInsertAfter, x, y, cx, cy, uFlags);
}

/**
 * @brief	設定視窗顯示位置
 * @param	[in] x 於父視窗 client-area 座標 x (左邊界)
 * @param	[in] y 於父視窗 client-area 座標 y (上邊界)
 * @return	@c 型別: BOOL \n
 *			如果函數成功，返回值為非零值(nonzero)。\n
 *			如果函數失敗，返回值為零, 若想獲得更多錯誤消息，請調用 GetLastError 函數函數
 * @see		DmWindow::SetWindowPos
 */
BOOL DmWindow::SetWindowPosition(int x, int y) const
{
	const UINT flag = SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE;
	assert(this->IsWindow());
	return ::SetWindowPos(*this, NULL, x, y, 0, 0, flag);
}

/**
 * @brief	設定視窗尺寸
 * @param	[in] w 寬度
 * @param	[in] h 高度
 * @return	@c 型別: BOOL \n
 *			如果函數成功，返回值為非零值(nonzero)。\n
 *			如果函數失敗，返回值為零, 若想獲得更多錯誤消息，請調用 GetLastError 函數函數
 * @see		DmWindow::SetWindowPos
 */
BOOL DmWindow::SetWindowSize(int w, int h) const
{
	const UINT flag = SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE;
	assert(this->IsWindow());
	return ::SetWindowPos(*this, NULL, 0, 0, w, h, flag);
}

/**
 * @brief	設定視窗工作區矩形邊界尺寸
 * @param	[in] wd	視窗寬度
 * @param	[in] ht	視窗高度
 * @return	@c 型別: BOOL \n
 *			操作成功返回非零值, 操作失敗返回零值(zero)\n
 *			如果函數操作失敗，調用 GetLastError 取得錯誤碼
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-setwindowposs
 */
BOOL DmWindow::SetClientSize(int w, int h) const
{
	const UINT flag = SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE;
	auto hWnd = this->GetSafeHwnd();
	auto res = BOOL(FALSE);
	RECT rc;

	assert(this->IsWindow());

	for (;;) {
		if (!::SetRect(&rc, 0, 0, w, h)) {
			// error handling at here
			break;
		}

		// 具有 menu ?
		if (!::AdjustWindowRectEx(&rc, ::GetWindowLong(hWnd, GWL_STYLE), ::GetMenu(hWnd) != NULL, 0)) {
			// error handling at here
			break;
		}

		w = static_cast<int>(rc.right - rc.left);
		h = static_cast<int>(rc.bottom - rc.top);
		res = ::SetWindowPos(hWnd, NULL, 0, 0, w, h, flag);
		break;
	}

	return res;
}

/**
 * @brief	設定視窗、控制項居中顯示
 * @return	此函數沒有返回值
 * @remark	若發現有父視窗存在, 將會以父視窗為基準. \n
 *			若無父視窗存在, 將以桌面左為基準.
 * @see		DmWindow::SetWindowPosition
 * @see		DmWindow::SetWindowSize
 */
BOOL DmWindow::SetCenterPosition() const
{
	HWND hWnd = *this;
	HWND hParent;
	BOOL res = FALSE;
	int  x, y, w, h;
	RECT rc;

	assert(this->IsWindow());

	for (;;) {
		if (hWnd == NULL) {
			// error handling at here
			break;
		}

		if ((hParent = ::GetParent(hWnd)) == NULL) {
			// 沒有父視窗，就取得桌面邊界尺寸
			x = ::GetSystemMetrics(SM_CXSCREEN);
			y = ::GetSystemMetrics(SM_CYSCREEN);
		}
		else {
			// 取得父視窗工作區邊界
			::GetClientRect(hParent, &rc);
			x = static_cast<int>(rc.right - rc.left);
			y = static_cast<int>(rc.bottom - rc.top);
		}

		if (this->GetWindowRect(&rc)) {
			// 計算居中值
			w = static_cast<int>(rc.right - rc.left);
			h = static_cast<int>(rc.bottom - rc.top);

			if (x > w) x = (x - w) >> 1;
			if (y > h) y = (y - h) >> 1;
			res = this->SetWindowPosition(x, y);
		}
		break;
	}
	return res;
}

/**
 * @brief	改變視窗位置、 Z軸順序、視窗尺寸
 * @param	[in] HDWP hWinPosInfo	多視窗定位結構 handle
 * @param	[in] hWndInsertAfter	視窗 Handle，用於標示 Z 順序中定位視窗之前。
 * @param	[in] x		client-area 座標指定視窗新位置 (左邊界)
 * @param	[in] y		client-area 座標指定視窗新位置 (上邊界)
 * @param	[in] cx		以像素 (pixel) 指定新視窗寬度
 * @param	[in] cy		以像素 (pixel) 指定新視窗高度
 * @param	[in] uFlags	視窗尺寸和定位的標誌
 * @remark	@c hWinPosInfo 參數說明 \n
 *			多視窗定位結構的 Handle，該結構包含著一個或多個視窗的尺寸和定位訊息 \n
 *			可以由函數 BeginDeferWindowPos 返回該結構或是返回最近一次 由 DeferWindowPos 調用的多結構 handle。
 * @see		DmWindow::SetWindowPos
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-deferwindowpos
 */
HDWP DmWindow::DeferWindowPos(HDWP hWinPosInfo, HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags) const
{
	assert(IsWindow());
	return ::DeferWindowPos(hWinPosInfo, *this, hWndInsertAfter, x, y, cx, cy, uFlags);
}

/**
 * @brief	開始向指定的視窗進行繪製
 * @param	[in] stPtr	pointer of PAINTSTRUCT structure
 * @return	@c 型別: HDC \n
 *			若操作成功返回非零值(nonzero)為視窗輸出顯示裝置 Handle \n
 *			若操作失敗返回零(zero) NULL, 表示沒有輸出裝置可用
 */
HDC DmWindow::BeginPaint(PAINTSTRUCT* stPtr) const
{
	assert(stPtr);
	assert(this->IsWindow());
	return ::BeginPaint(*this, stPtr);
}

/**
 * @brief	結束向指定的視窗繪製
 * @param	[in] stPtr	pointer of PAINTSTRUCT structure
 * @return	@c 型別: BOOL, 始終返回非零值(nonzero)
 * @remark	每次使用 BeginPaint 都要使用 EndPaint 來結束。
 */
BOOL DmWindow::EndPaint(const PAINTSTRUCT * stPtr) const
{
	assert(IsWindow());
	return ::EndPaint(*this, stPtr);
}

/**
 * @brief	取得視窗 client-area device context handle
 * @return	@c 型別: HDC \n
 *			若函數操作成功返回視窗 client-area device context handle \n
 *			若函數操作失敗返回 NULL
 *@remark	dc is device context
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-getdc
 *
 *	取得 client-area device context handle \n
 *	之後即可利用 GDI 各函數中可以使用該 handle 在 dc 進行繪製
 */
HDC DmWindow::GetDC() const
{
	assert(this->IsWindow());
	return ::GetDC(*this);
}

/**
 * @brief	取得整視窗或螢幕 dc handle
 * @param	[in] hrgnClip	指定一剪切區域，它可以與 dc 環境的可見區域相結合。
 * @param	[in] flags		指定如何建立 dc 環境
 * @return	@c 型別: HDC \n
 *			若函數操作成功返回視窗或整個螢幕的 dc handle \n
 *			若函數操作失敗返回 NULL
 * @remark	dc is device context
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-getdcex
 *
 *	取得 client-area, 整個視窗或整個螢幕的顯示 device context handle \n
 *	之後即可利用 GDI 各函數中可以使用該 handle 在 dc 進行繪製
 */
HDC DmWindow::GetDCEx(HRGN hrgnClip, DWORD flags) const
{
	assert(this->IsWindow());
	return ::GetDCEx(*this, hrgnClip, flags);
}

/**
 * @brief	重繪選單欄位，若有發生修改選單項目就必須使用此函數進行重繪
 * @return	@c 型別: BOOL \n
 *			若函數操作成功返回非零值(nonzero) \n
 *			若函數操作失敗返回零(zero)，調用 GetLastError 取得錯誤碼
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-drawmenubar
 */
BOOL DmWindow::DrawMenuBar() const
{
	assert(IsWindow());
	return ::DrawMenuBar(*this);
}

/**
 * @brief	指定視窗於 Z 順序中移至最上層, 若指定視窗為子視窗，則連最基底父視窗一併移至最上層
 * @return	@c 型別: BOOL \n
 *			若函數操作成功返回非零值 (nonzero)
 *			若含數操作失敗則返回零(zero), 使用 GetLastError 取得錯誤碼
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-bringwindowtotop
 */
BOOL DmWindow::BringWindowToTop() const
{
	assert(this->IsWindow());
	return ::BringWindowToTop(*this);
}

/**
 * @brief	取得視窗或控制項於系統註冊視窗名稱 (RegisterClassEx)
 * @param	[out] szClassNamePtr	要存放字串緩衝區位址
 * @param	[in]  cchMax			要取字串的最大長度 (in TCHAR)
 */
int DmWindow::GetClassName(TCHAR* szClassNamePtr, int cchMax) const
{
	assert(this->IsWindow());
	return ::GetClassName(*this, szClassNamePtr, cchMax);
}

/**
 * @brief	取得視窗或控制項文字長度 (若該視窗或控制項有 Title bar 或 控制項名稱)
 * @return	@c 型別: int \n
 *			若函數操作成功返回不為負數的非零值, 返回值該視窗或控制項文字內容字數數量 (不含 NULL 結尾) \n
 *			若操作失敗或沒有文字項目則返回零(zero)
 */
int DmWindow::GetWindowTextLength() const
{
	assert(this->IsWindow());
	return ::GetWindowTextLength(*this);
}

/**
 * @brief	取得視窗或控制項的文字內容
 * @param	szTextPtr	要接收存放文字字串的緩衝區位址 (TCHAR)
 * @param	cchMax		要接收多少文字 (in TCHAR)
 * @return	@c 型別: int \n
 *			返回值為實際取得文字數量 (in TCHAR)
 * @see		https://docs.microsoft.com/en-us/windows/desktop/winmsg/wm-gettext
 */
int DmWindow::GetWindowText(TCHAR* szTextPtr, size_t cchMax) const
{
	assert(this->IsWindow());
	return ::GetWindowText(*this, static_cast<LPTSTR>(szTextPtr), static_cast<int>(cchMax));
}

/**
 * @brief	設定視窗或控制項文字
 * @param	[in] szTextPtr 要設定的文字字串位址 (TCHAR and NULL end)
 * @return	@c 型別: BOOL \n
 *			若函數操作成功返回非零值(nonzero) \n
 *			若函數操作失敗返回零(zero), 調用 GetLastError 取得錯誤碼
 */
BOOL DmWindow::SetWindowText(const TCHAR* szTextPtr) const
{
	 assert(this->IsWindow());
	 return ::SetWindowText(*this, static_cast<LPCTSTR>(szTextPtr));
}

/**
 * @brief	取得控制項文字轉數值
 * @param	[in] nIDDlgItem	控制項 ID
 * @param	[in] bSigned	是否取得有號數數值
 * @return	@c 型別: UINT \n
 *			若函數操作成功將返回一整數數值 \n
 *			若函數操作失敗返回零(zero), 返回零並不代表就是失敗, 因為有可能該文字就是 '0'
 */
UINT DmWindow::GetDlgItemInt(int nIDDlgItem, BOOL bSigned) const
{
	auto bTranslated = BOOL(FALSE);
	assert(this->IsWindow());
	return ::GetDlgItemInt(*this, nIDDlgItem, &bTranslated, bSigned);



	UINT GetDlgItemInt(
		HWND hDlg,
		int  nIDDlgItem,
		BOOL *lpTranslated,
		BOOL bSigned
	);
}

/**
 * @brief	取得控制項文字轉數值
 * @param	[in]		nIDDlgItem		控制項 ID
 * @param	[in,out]	bTranslatedPtr	保存轉換成功或失敗訊息, 若成功將被設定為 TRUE, 失敗將被設定為 FALSE
 * @param	[in]		bSigned			是否取得有號數數值
 * @return	@c 型別: UINT \n
 *			若函數操作成功將返回一整數數值 \n
 *			若函數操作失敗返回零(zero), 返回零並不代表就是失敗, 因為有可能該文字就是 '0'
 * @remark	若 lpTranslated 參數為 NULL, 表示不接收成功與失敗訊息
 */
UINT DmWindow::GetDlgItemInt(int nIDDlgItem, BOOL* bTranslatedPtr, BOOL bSigned) const
{
	assert(this->IsWindow());
	return ::GetDlgItemInt(*this, nIDDlgItem, bTranslatedPtr, bSigned);
}

/**
 * @brief	取得控制項文字內容
 * @param	[in]	nIDDlgItem	控制項 ID
 * @param	[out]	szTextPtr	要存放文字字串的緩衝區位址
 * @param	[in]	cchMax		要取得字串的醉到長度(容量) (in TCHAR)
 * @return	@c 型別: UINT \n
 *			若函數操作成功返回取得字串的長度, 不含 NULL 結尾標記 \n
 *			若函數操作失敗返回零(zero), 表示取得字串失敗或字串長度為零
 */
UINT DmWindow::GetDlgItemText(int nIDDlgItem, TCHAR* szTextPtr, int cchMax) const
{
	assert(this->IsWindow());
	return ::GetDlgItemText(*this, nIDDlgItem, szTextPtr, cchMax);
}

/**
 * @brief	設定控制項文字
 * @param	[in] nIDDlgItem	控制項 ID
 * @param	[in] szTextPtr	要設定的文字字串位址 (TCHAR and NULL end)
 * @return	@c 型別: BOOL \n
 *			若函數操作成功返回非零值(nonzero) \n
 *			若函數操作失敗返回零(zero), 調用 GetLastError 取得錯誤碼
 */
BOOL DmWindow::SetDlgItemText(int nIDDlgItem, const TCHAR* szTextPtr) const
{
	return 0;
}

/**
 * @brief	取得視窗、控制項樣式 (Style)
 * @return	@c 型別: DWORD \n
 *			若函數操作成功返回非零值(nonzero), 該值為 視窗或控制項 Sytle 值 \n
 *			若函數操作失敗返回零(zero), 調用 GetLastError 取得錯誤碼
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-getwindowlongptra
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-getwindowlongptrw
 */
DWORD DmWindow::GetStyle() const
{
	assert(this->IsWindow());
	return static_cast<DWORD>(::GetWindowLongPtr(*this, GWL_STYLE));
}

/**
 * @brief	取得視窗、控制項擴展樣式 (ExStyle)
 * @return	@c 型別: DWORD \n
 *			若函數操作成功返回非零值(nonzero), 該值為 視窗或控制項 Sytle 擴展值 \n
 *			若函數操作失敗返回零(zero), 調用 GetLastError 取得錯誤碼
 * @see		DmWindow::GetStyle
 */
DWORD DmWindow::GetExStyle() const
{
	assert(this->IsWindow());
	return static_cast<DWORD>(::GetWindowLongPtr(*this, GWL_EXSTYLE));
}

/**************************************************//**
 * @brief	設定視窗、控制項樣式 (Style)
 * @param	[in] dwStyle 視窗樣式
 * @return	@c 型別: DWORD \n
 *			若函數操作成功返回值為先前的 Style 值 \n
 *			若函數操作失敗返回零(zero), 調用 GetLastError 取得錯誤碼
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-setwindowlongptra
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-setwindowlongptrw
 *****************************************************/
DWORD DmWindow::SetStyle(DWORD dwStyle) const
{
	assert(this->IsWindow());
	return static_cast<DWORD>(::SetWindowLongPtr(*this, GWL_STYLE, static_cast<LONG_PTR>(dwStyle)));
}

/**
 * @brief	設定視窗、控制項擴展樣式 (ExStyle)
 * @param	[in] dwExStyle 視窗擴展樣式
 * @return	@c 型別: DWORD \n
 *			若函數操作成功返回值為先前的 Style 擴展值 \n
 *			若函數操作失敗返回零(zero), 調用 GetLastError 取得錯誤碼
 * @see		DmWindow::SetStyle
 */
DWORD DmWindow::SetExStyle(DWORD dwExStyle) const
{
	assert(this->IsWindow());
	return static_cast<DWORD>(::SetWindowLongPtr(*this, GWL_EXSTYLE, static_cast<LONG_PTR>(dwExStyle)));
}

/**
 * @brief	取得父視窗代碼(Handle)
 * @return	@c 型別: HWND \n
 *			若有父視窗將返回非零值(nonzero)為父視窗操作 Handle \n
 *			若沒有父視窗則返回零 (zero) NULL
 */
HWND DmWindow::GetParent() const
{
	assert(this->IsWindow());
	return ::GetParent(this->GetSafeHwnd());
}

/**
 * @brief	取得鼻祖視窗代碼(Handle)
 * @param	[in] uFlags	取得目標方式, 預設使用 GA_ROOTOWNER
 *				- GA_PARENT:	取得父視窗(同 GetParent)
 *				- GA_ROOT:		追根到底, 遍歷父視窗鏈, 取得鼻祖視窗
 *				- GA_ROOTOWNER:	追根到底, 遍歷父視窗鏈與擁有者視窗, 取得鼻祖視窗
 * @return	@c 型別: HWND, 鼻祖視窗代碼(Handle)
 */
HWND DmWindow::GetAncestor(UINT uFlags) const
{
	assert(this->IsWindow());
	return ::GetAncestor(*this, uFlags);
}

/**
 * @brief	取得活動中的視窗代碼(Handle)
 * @return	@c 型別: HWND \n
 *			若函數操作成功返回當前活動中的視窗代碼(Handle) \n
 *			若含數操作失敗返回零(zero) NULL
 */
HWND DmWindow::GetActiveWindow() const { return ::GetActiveWindow(); }

/**
 * @brief	取得桌面視窗代碼(Handle)
 * @return	@c 型別: HWND, 桌面視窗代碼(Handle)
 */
HWND DmWindow::GetDesktopWindow() const
{
	return ::GetDesktopWindow();
}

/**
 * @brief	取得控制項視窗代碼(Handle)
 * @param	[in] nIDDlgItem	控制項 ID
 * @return	@c 型別: HWND \n
 *			若函數操作成功返回非零值(nonzero)為指定控制項的視窗代碼(Handle) \n
 *			若函數操作失敗返回零(zero), 使用 GetLastError 取得錯誤碼
 */
HWND DmWindow::GetDlgItem(int nIDDlgItem) const
{
	assert(this->IsWindow());
	return ::GetDlgItem(*this, nIDDlgItem);
}

/**
 * @brief	取得控制項 ID (標示識別碼)
 * @return	@c 型別: int \n
 *			若函數操作成功返回非零值(nonzero)為控制項的 ID \n
 *			若函數操作失敗返回零(zero), 調用 GetLastError 取得錯誤碼
 */
int DmWindow::GetDlgCtrlID() const
{
	assert(this->IsWindow());
	return ::GetDlgCtrlID(*this);
}

/**
 * @brief	取得當前輸入焦點視窗
 * @return	@c 型別: HWND \n
 *			若函數操作成功返回非零值(nonzero), 該值目前焦點的視窗代碼(Handle) \n
 *			若函數操作失敗或若沒有任何視窗焦點則返回 NULL.
 */
HWND DmWindow::GetFocus() const { return ::GetFocus(); }

/**
 * @brief	設定視窗為輸入焦點
 * @return	@c 型別: HWND \n
 *			若函數操作成功返回非零值(nonzero), 該值為先前擁有輸入焦點的視窗代碼(Handle) \n
 *			若函數操作失敗或沒有此視窗則返回零(zero) NULL
 * @remark	傳回的 HANDLE 指標是暫時的, 所以不應被儲存或轉給給其他函式使用.
 */
HWND DmWindow::SetFocus() const {
	assert(this->IsWindow());
	return ::SetFocus(*this);
}

/**
 * @brief	設定要持續取得滑鼠遊標訊息接收
 * @return	@c 型別: HWND \n
 *			先前捕獲滑鼠游標的的視窗代碼(Handle), 若先前沒有這樣的視窗則返回 NULL
 * @remark	設定指定視窗即使不再活動中, 不再滑鼠游標當前所在視窗依然可以持續取得滑鼠游標訊息 \n
 *			直到 ReleaseCapture 或點擊其他視窗成為活動中視窗
 */
HWND DmWindow::SetCapture() const
{
	assert(this->IsWindow());
	return ::SetCapture(*this);
}

/**
 * @brief	取得當前滑鼠游標停留位置的視窗代碼(Handle)
 * @return	@c 型別: HWND \n
 *			返回當前線程中捕獲滑鼠游標位置的視窗代碼(Handle) \n
 *			若當前線程沒有捕獲到滑鼠游標位置則返回 NULL \n
 *			返回 NULL 不代表失敗, 只是代表當前的(發出 GetCapture)的線程沒有捕獲到滑鼠游標
 * @remark	同時間只有一個線程可以取得全域滑鼠游標訊息, 若要改變此一狀態，只要調用 SetCapture \n
 *			則享有全域滑鼠遊標訊息。
 */
HWND DmWindow::GetCapture() const
{
	return ::GetCapture();
}

/**
 * @brief	重當前線程釋放滑鼠或取方式, 回到正常的獲取滑鼠游標資訊。
 * @return	@c 型別: BOOL \n
 *			若函數操作成功返回非零值(nonzero) \n
 *			若函數操作失敗返回零(zero), 調用 GetLasterror 取得錯誤碼
 */
BOOL DmWindow::ReleaseCapture() const
{
	return ::ReleaseCapture();
}

/**
 * @brief	取得字型 (類別內建立的使用者字型)
 * @return	@c 型別: HFONT \n
 *			若函數操作成功返回非零值(nonzero), 該值為字型代碼(Handle) \n
 *			若函數操作失敗則返回為零(zero)
 */
HFONT DmWindow::GetFont() const
{
	assert(this->IsWindow());

	// WM_GETFONT
	// wParam = 未使用, 必須為零
	// lParam = 未使用, 必須為零
	return reinterpret_cast<HFONT>(this->SendMessage(WM_GETFONT, 0, 0));
}

/**
 * @brief	設定視窗或控制項字型
 * @param	[in] hFont		字型 Handle, 若此值為 NULL 代表指定使用系統預設字型.
 * @param	[in] bRedraw	低字元 (low-word) 表示設定字型時是否立即重新繪製.\n
 *							如果此參數為 TRUE，視窗或控制項本身將會自動重繪。
 * @return	此函數沒有返回值
 * @see		https://docs.microsoft.com/zh-tw/windows/desktop/winmsg/wm-setfont
 */
void DmWindow::SetFont(HFONT hFont, BOOL bRedraw)
{
	// WM_SETFONT
	WPARAM wParam = reinterpret_cast<WPARAM>(hFont);	// Handle of font
	LPARAM lParam = static_cast<LPARAM>(bRedraw);		// The control redraws itself? (TRUE or FALSE)
	::SendMessage(*this, WM_SETFONT, wParam, lParam);
}

/**
 * @brief	取得視窗或控制項的 ICON
 * @param	[in] nType	欲取得圖示的模式.
 *				- ICON_BIG		大圖示
 *				- ICON_SMALL	小圖示
 *				- ICON_SMALL2	小圖示2
 * @return	@c 型別: HICON \n
 *			若函數操作成功返回值為指定模式的圖示代碼(Handle) \n
 *			若視窗或控制項沒有設定過圖示, 將自動取得系統預設指派的圖示代碼(Handle)
 * @see		https://docs.microsoft.com/en-us/windows/desktop/winmsg/wm-geticon
 */
HICON DmWindow::GetIcon(int nType) const
{
	// Get the window or controller icon
	// WM_GETICON
	WPARAM wParam = static_cast<WPARAM>(nType);	// 取得模式
	LPARAM lParam = 0;							// 未使用，必須為零
	auto icon = reinterpret_cast<HICON>(::SendMessage(*this, WM_GETICON, wParam, lParam));

	// Alternative method. Get from the window class
	if (icon == NULL) {
		icon = reinterpret_cast<HICON>(::GetClassLongPtr(*this, GCLP_HICONSM));
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
 * @param	[in] hIcon	圖示代碼(Handle)
 * @param	[in] nType	要變更的圖示模式
 *				- ICON_BIG,		大圖示
 *				- ICON_SMALL,	小圖示
 * @return	@c 型別: HICON \n
 *			若函數操作成功返回上一個所設定的圖示代碼(Handle) \n
 *			若視窗或控制項沒有設定過圖示則返回零(zero) NULL
 * @see		https://docs.microsoft.com/en-us/windows/desktop/winmsg/wm-seticon
 */
HICON DmWindow::SetIcon(HICON hIcon, int nType) const
{
	assert(this->IsWindow());
	// WM_SETICON
	WPARAM wParam = static_cast<WPARAM>(nType);			// 大圖或小圖模式
	LPARAM lParam = reinterpret_cast<LPARAM>(hIcon);	// Handle of icon
	return reinterpret_cast<HICON>(::SendMessage(*this, WM_SETICON, wParam, lParam));
}

/**
 * @brief	建立計時器
 * @param	[in] nIDEvent		計時器 ID
 * @param	[in] uElapse		延遲時間 (ms) 多少時間觸發一次
 * @param	[in] fnTimerFunc	Timer Callback
 *				- 定時觸發時間是件至指定 Callback
 *				- 若此值為 NULL 計時器會對對視窗發出 WM_TIMER 訊息
 * @return	@c 型別: UINT_PTR
 *				- 若函數操作成功且 hWnd 參數為 NULL，則返回值是標識新計時器的整數。\n
 *				  應用程序可以將此值傳遞給 KillTimer 函數以銷毀計時器。
 *				- 若函數操作成功且 hWnd 參數不為 NULL，則返回值為非零整數。\n
 *				  應用程序可以將 nIDEvent 參數的值傳遞給 KillTimer 函數以銷毀計時器。
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-settimer
 **/
UINT_PTR DmWindow::SetTimer(UINT_PTR nIDEvent, UINT uElapse, TIMERPROC fnTimerFunc) const
{
	assert(this->IsWindow());
	return ::SetTimer(*this, nIDEvent, uElapse, fnTimerFunc);
}

/**
 * @brief	刪除計時器
 * @return	@c 型別: BOOL \n
 *			若函數操作成功返回非零值(nonzero) \n
 *			若函數操作失敗返回零(zero), 調用 GetLastError 取得錯誤碼 \n
 */
BOOL DmWindow::KillTimer(UINT_PTR uIDEvent) const
{
	assert(this->IsWindow());
	return ::KillTimer(*this, uIDEvent);
}

/**
 * @brief	變更視窗屬性
 * @param	[in] nIndex 要檢索的項目
 *				- GWL_EXSTYLE		擴展式視窗樣式
 *				- GWL_STYLE			視窗樣式
 *				- GWLP_WNDPROC		視窗 Callback function
 *				- GWLP_HINSTANCE	視窗 Module of Handle
 *				- GWLP_HWNDPARENT	父視窗代碼(Handle)
 *				- GWLP_ID			視窗的 ID
 *				- GWLP_USERDATA		給是用者用的變數 (初始內容為 0)
 *				- DWLP_DLGPROC		對話框 Dialog 的 callback function
 *				- DWLP_MSGRESULT	對話框訊息返回值
 *				- DWLP_USER			對話框額外訊息
 * @return	@c 型別: LONG_PTR \n
 *			若函數操作成功返回值檢索項目資訊 \n
 *			若操作失敗返回零，使用 GetLastError() 取得錯誤碼
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-getwindowlongptrw
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-getwindowlongptra
 */
LONG_PTR DmWindow::GetWindowLongPtr(int nIndex) const
{
	assert(this->IsWindow());
	return ::GetWindowLongPtr(*this, nIndex);
}

/**
 * @brief	變更視窗屬性
 * @param	[in] nIndex		檢索項目
 * @param	[in] dwNewLong	變更內容
 * @return	@c 型別: LONG_PTR \n
 *			若函數操作成功返回值為變更前檢索項目資訊 \n
 *			若操作失敗返回零，使用 GetLastError() 取得錯誤碼
 * @see		DmWindow::GetWindowLongPtr
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-setwindowlongptrw
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-setwindowlongptra
 */
LONG_PTR DmWindow::SetWindowLongPtr(int nIndex, LONG_PTR dwNewLong) const
{
	assert(this->IsWindow());
	return ::SetWindowLongPtr(*this, nIndex, dwNewLong);
}

/**
 * @brief	取得視窗關聯的 WNDCLASSEX 結構中要檢索內容
 * @param	[in] nIndex	檢索項目
 *				- GCW_ATOM (-32) \n
 *				檢索唯一標識視窗類的 ATOM值。這與 RegisterClassEx 函數返回的值相同。
 *				- GCL_CBCLSEXTRA (-20)		\n
 *				檢索與類關聯的額外記憶體的大小（以 WORD 為單位）。
 *				- GCL_CBWNDEXTRA (-18)		\n
 *				檢索與類中每個視窗關聯的額外視窗記憶體的大小（以字節為單位）。有關如何訪問此記憶體的訊息，請參閱GetWindowLongPtr。
 *				- GCLP_HBRBACKGROUND (-10)	\n
 *				檢索與類關聯的背景畫筆的句柄。
 *				- GCLP_HCURSOR (-12)		\n
 *				檢索與類關聯的游標的句柄。
 *				- GCLP_HICON (-14)			\n
 *				檢索與類關聯的圖標的句柄。
 *				- GCLP_HICONSM (-34)		\n
 *				檢索與該類關聯的小圖標的句柄。
 *				- GCLP_HMODULE (-16)		\n
 *				檢索註冊該類的模塊的句柄。
 *				- GCLP_MENUNAME (-8)		\n
 *				檢索指向菜單名稱字符串的指針。該字符串標識與該類關聯的菜單資源。
 *				- GCL_STYLE (-26)			\n
 *				檢索視窗類樣式位。
 *				- GCLP_WNDPROC (-24)		\n
 *				檢索視窗過程的地址，或表示視窗過程地址的句柄。您必須使用CallWindowProc函數來調用視窗過程。
 * @return	@c 型別: ULONG_PTR \n
 *			若函數操作成功返回值檢索項目資訊 \n
 *			若操作失敗返回零，使用 GetLastError() 取得錯誤碼
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-getwindowlongptrw
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-getwindowlongptra
 *
 *	視窗向系統註冊的資訊 WNDCLASSEX, 利用此函數能夠調閱當前於系統中的視窗class內容.
 */
ULONG_PTR DmWindow::GetClassLongPtr(int nIndex) const
{
	assert(this->IsWindow());
	return ::GetClassLongPtr(*this, nIndex);
}


/**
 * @brief	取得視窗關聯的 WNDCLASSEX 結構中要檢索內容
 * @param	[in] nIndex		檢索項目
 * @param	[in] dwNewLong	變更內容
 * @return	@c 型別: UNLONG_PTR \n
 *			若函數操作成功返回值為變更前檢索項目資訊 \n
 *			若操作失敗返回零，使用 GetLastError() 取得錯誤碼
 * @see		DmWindow::GetClassLongPtr
 */
ULONG_PTR DmWindow::SetClassLongPtr(int nIndex, LONG_PTR dwNewLong) const
{
	assert(this->IsWindow());
	return ::SetClassLongPtr(*this, nIndex, dwNewLong);
}

/**
 * @brief	取得視窗或控制項操作 Handle (Handle of window)
 * @return	@c 型別: HWND \n
 *			返回非零值(nonzero)為目前於類別物件內使用的視窗或控制項操作 Handle (Handle of window) \n
 *			若類別誤建尚未連結則傳回零(zero) NULL
 */
HWND DmWindow::GetSafeHwnd() const { return m_hWnd; }

/**
 * @brief	取得改變前的視窗(控制項) Callback function
 */
WNDPROC DmWindow::GetPrevWndProc() const { return m_fnPrevWndProc; }

/**
 * @brief	檢驗是否為有效的視窗(控制項)操作 Handle
 * @return	@c 型別: BOOL \n
 *			若為有效的視窗或控制項操作代碼則返回一個非零值(nonzero) \n
 *			若不是一個視窗或控制項操作代碼則返回零(zero)
 */
BOOL DmWindow::IsWindow() const { return ::IsWindow(*this); }

/**
 * @britf	確定視窗是指定父視窗的子項目或是後代視窗
 * @param	[in] hWndChild	視窗或控制項代碼(Handle)
 * @return	@c 型別: BOOL \n
 *			若視窗是指定父視窗的子視窗或後代視窗，則返回值為非零。
 *			若視窗不是指定父視窗的子視窗或後代視窗，則返回值為零。
 */
BOOL DmWindow::IsChild(HWND hWndChild) const
{
	assert(this->IsWindow());
	return ::IsChild(*this, hWndChild);
}

/**
 * @brief 確認視窗或控制項使否為啟用狀態 (滑鼠與鍵盤進行能否輸入)
 * @return @c 型別: BOOL \n
 *			If the window is enabled, the return value is nonzero.	\n
 *			If the window is not enabled, the return value is zero.
 */
BOOL DmWindow::IsWindowEnable() const
{
	assert(this->IsWindow());
	return ::IsWindowEnabled(*this);
}

/**
 * @brief	Determines the visibility state of the specified window.
 * @return	@c 型別: BOOL \n
 *			若指定的視窗或控制項，其父視窗及各祖輩視窗皆具有 WS_VISIBLE 樣式, 則返回值為非零, 否則返回值為零. \n
 *			返回值為指定視窗或控制項是否具有 WS_VISIBLE 樣式, 所以即使視窗或控制項被其他窗口完全遮擋, 它也可能不為零。
 */
BOOL DmWindow::IsWindowVisible() const
{
	assert(this->IsWindow());
	return (::GetWindowLongPtr(*this, GWL_STYLE) & WS_VISIBLE) != 0;
}

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
}

/**
 * @brief	DmWindow constructor
 * @param	[in] hWnd 視窗(控制項)操作 Handle
 * @remark	這是私有成員，僅供 DmWindow 內部運算用。
 */
DmWindow::DmWindow(HWND hWnd) : m_hWnd(NULL), m_fnPrevWndProc(NULL), m_bAttach(FALSE)
{
	if (hWnd == NULL) {
		// error handling at here
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
