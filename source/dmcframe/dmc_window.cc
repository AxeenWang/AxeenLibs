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
	, m_fnPrevWndProc(NULL) {
}

//! DmWindow deconstructor
DmWindow::~DmWindow() { }

/**
 * @brief	連接一個新的視窗(控制項)
 * @param	[in] hWnd 視窗操作代碼 (Handle of Window)
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

		this->MatchToClass(hWnd);
		res = this->GetSafeHwnd() != NULL;
		break;
	}
	return res;
}

/**
 * @brief	連接控制項
 * @param	[in] uID		控制項 ID
 * @param	[in] hWndParent	複視窗 HWND
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
 *			若 class 有連接視窗或控制項傳回非零值(non-zero)為原連接視窗或控制項的 HWND \n
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

void DmWindow::Destroy()
{
	if (this->IsWindow()) {
		::DestroyWindow(*this);
	}
}

/**
 * @brief	取得視窗或控制項操作碼
 * @return	@c 型別: HWND \n
 *			返回非零值(non-zero)為目前於類別物件內使用的視窗或控制項操作碼 \n
 *			若類別誤建尚未連結則傳回零(zero) NULL
 */
HWND DmWindow::GetSafeHwnd() const { return m_hWnd; }

/**
 * @brief	取得父視窗操作碼
 * @return	@c 型別: HWND \n
 *			若有父視窗將返回非零值(non-zero)為父視窗操作碼 \n
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
 * @brief	檢驗是否為有效的視窗(控制項)操作代碼
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
 * @param	[in] hWnd 視窗(控制項)操作碼
 * @remark	這是私有成員，僅供 DmWindow 內部運算用。
 */
DmWindow::DmWindow(HWND hWnd) : m_hWnd(NULL), m_fnPrevWndProc(NULL)
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
 * @param	[in] hWnd 視窗或控制項操作代碼
 */
void DmWindow::MatchToClass(HWND hWnd)
{
	assert(::IsWindow(hWnd));

	if (::IsWindow(hWnd)) {
		m_hWnd = hWnd;
		::SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);
		m_fnPrevWndProc = reinterpret_cast<WNDPROC>(::SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(DmWindow::StaticWindowProc)));
	}
}
