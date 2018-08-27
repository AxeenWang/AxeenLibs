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
	assert(!this->IsWindow());		// 視窗早已被定義

	for (;;) {
		if (hWnd == NULL) {
			this->SetLastError(DMCERR::ERR_INVALID_HANDLE);
			break;
		}

		if (this->IsWindow()) {
			this->SetLastError(DMCERR::ERR_EXIST_HWND);
			break;
		}

		this->MatchToClass(hWnd);
		res = this->GetSafeHandle() != NULL;
		break;
	}
	return res;
}

/**
 * @brief	斷開連接視窗或控制項
 * @return	@c 型別: HWND \n
 *			若 class 有連接視窗或控制項傳回非零值(non-zero)為原連接視窗或控制項的 HWND \n
 *			若 class 沒有與視窗連接將傳回零(zero) NULL
 */
HWND DmWindow::Detach()
{
	auto fn = m_fnPrevWndProc;
	auto hWnd = HWND(NULL);

	assert(fn);

	for (;;) {
		if (fn == NULL) {
			this->SetLastError(DMCERR::ERR_INVALID_FUNCTION);
			break;
		}

		if (!this->IsWindow()) {
			this->SetLastError(DMCERR::ERR_INVALID_HWND);
			break;
		}

		hWnd = this->GetSafeHandle();
		::SetWindowLongPtr(hWnd, GWLP_USERDATA, 0);
		::SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(fn));
		m_hWnd = NULL;
		m_fnPrevWndProc = NULL;
		break;
	}
	return hWnd;
}

/**
 * @brief	檢驗是否為有效的視窗(控制項)操作代碼
 * @return	@c 型別: BOOL \n
 *			若為有效的視窗或控制項操作代碼則返回一個非零值(non-zero) \n
 *			若不是一個視窗或控制項操作代碼則返回零(zero)
 */
BOOL DmWindow::IsWindow()
{
	return ::IsWindow(*this);
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
LRESULT DmWindow::WndProc(UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	return LRESULT();
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
