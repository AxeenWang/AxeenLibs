/**************************************************************************//**
 * @file	wframe_window.cc
 * @brief	Win32 視窗操作 : 視窗框架類別 - 成員函數
 * @date	2010-10-10
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#include "win32frame/wframe_window.hh"

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
LRESULT CALLBACK CxFrameWindow::WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	CxFrameWindow* fmObj = NULL;

	// Is Window create message?
	if (uMessage == WM_CREATE) {
		// fmObj = (CxFrameWindow*)((LPCREATESTRUCT)lParam)->lpCreateParams;
		fmObj = reinterpret_cast<CxFrameWindow*>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);
		if (fmObj != NULL) {
			// Save the CxFrameWindow object
			::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(fmObj));
			fmObj->m_hWnd = hWnd;
		}
	}
    
	// get user saved data form "GWLP_USERDATA" mode
	if ((fmObj = (CxFrameWindow*)::GetWindowLongPtr(hWnd, GWLP_USERDATA)) == NULL) {
		// transfer window message in system default callback function
		return ::DefWindowProc(hWnd, uMessage, wParam, lParam);
	}

	/*
	// 事先處理視窗結束動作
	if (uMessage == WM_CLOSE)
		fmObj->SysCloseWindow();
	else if (uMessage == WM_DESTROY)
		fmObj->SysDestroyWindow();
	*/

	// transfer window message in user callback function
	return fmObj->MessageDispose(uMessage, wParam, lParam);
}

/**
 * @brief	視窗訊息處理
 * @param	[in] uMessage	視窗訊息
 * @param	[in] wParam		參數 1
 * @param	[in] lParam		參數 2
 * @return	@c LRESULT		視窗訊息處理後結果
 * @remark	此為虛擬函數，提供 WndProc 調用由衍生類別進行內容變更.
 * @warning	@c 注意!! 結束視窗或控制項說明:\n
 *			當使用 DestroyWindow 結束視窗或控制項之前, 需先清除記憶體配置以及物件配置.\n
 *			否則必須手動釋放已建立之物件與記憶體配置, 否則必造成 memory leak.
 */
LRESULT CxFrameWindow::MessageDispose(UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_CREATE:
		break;
	case WM_DESTROY:
		this->SysDestroyWindow();
		break;
	case WM_CLOSE:
		this->SysCloseWindow();
		break;
	default:
		return ::DefWindowProc(m_hWnd, uMessage, wParam, lParam);
	}
	return 0;
}


/**
 * @brief	視窗訊息處理迴圈，採用 Peek message 機制
 * @return	@c int 視窗結束狀態碼
 */
int CxFrameWindow::RunPeekMessage()
{
	MSG message = { 0 };

	while (TRUE)
	{
		while (::PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			//::TranslateMessage(&message);
			::DispatchMessage(&message);
		}

		if (message.message == WM_QUIT)
			break;

		// TODO: 要處理動作項目 (如動態 UI，計時或遊戲)
		// ...
	}
	return (int)message.wParam;
}


/**
 * @brief	視窗訊息處理迴圈，採用 get message 機制
 * @return	@c int 視窗結束狀態碼
 */
BOOL CxFrameWindow::RunStayMessage()
{
	MSG message = { 0 };

	while (::GetMessage(&message, NULL, 0, 0)) {
		// If wanna WS_TABSTOP work, must join this check
		if (!::IsDialogMessage(m_hWnd, &message)) {
			::TranslateMessage(&message);
			::DispatchMessage(&message);
		}
	}
	return (int)message.wParam;
}


//! CxFrameWindow 建構式
CxFrameWindow::CxFrameWindow() : CxFrameObject() { }

//! CxFrameWindow 解構式
CxFrameWindow::~CxFrameWindow() { }


/**
 * @brief	視窗訊息處理迴圈 (The windows porcess main thread)
 * @param	[in] bPeek	是否採用 Peek 訊息模 (預設: 否)
 * @return	@c int	視窗結束狀態碼
 * @remark	一個視窗模組程式必須建立一個訊息迴圈，已取得系統提供之訊息
*/
int CxFrameWindow::Run(BOOL bPeek)
{
	return bPeek ? this->RunPeekMessage() : this->RunStayMessage();
}


/**
 * @brief	建立一個視窗
 * @param	[in] swndPtr SSFRAMEWINDOW 結構資料位址
 * @return	@c BOOL \n
 *			若函數操作成功返回非零值(non-zero), 失敗將返回零值(zero) \n
 *
 * 建立一個視窗基礎框架, 在 SSFRAMEWINDOW 結構中定義要建立視窗的各項內容. \n
 * 不須額外建立 WndProc callback function, 來做訊息處理. \n
 * 訊息處理只要重載虛擬函數 MessageDispose, 即可在衍生類別進行的訊息處理. \n
 */
BOOL CxFrameWindow::CreateWindow(LPSSFRAMEWINDOW swndPtr)
{
	BOOL err = FALSE;

	for (;;) {
		if (!this->SysRegisterWindow(swndPtr))
			break;

		if (!this->SysCreateWindow(swndPtr))
			break;

		err += TRUE;
		break;
	}
	return err;
}


/**
 * @brief	建立一個範例視窗
 * @param	[in] hInstance	程序運作模組 Handle
 */
BOOL CxFrameWindow::CreateSample(HINSTANCE hInstance)
{
	SSFRAMEWINDOW swnd;

	if (hInstance != NULL) {
		// 填寫 SWINDOW 結構內容
		::memset((void*)&swnd, 0, sizeof(SSFRAMEWINDOW));
		swnd.hInstance = hInstance;
		swnd.hWndParent = NULL;
		swnd.fnWndProc = CxFrameWindow::WndProc;
		swnd.pszClassName = TEXT(DEFAULT_SWND_CLASS);
		swnd.pszTitleName = TEXT(DEFAULT_SWND_TITLE);
		swnd.iPosx = 0;
		swnd.iPosy = 0;
		swnd.iWidth = DEFAULT_SWND_WIDTH;
		swnd.iHeight = DEFAULT_SWND_HEIGHT;
		swnd.uClassStyle = 0;
		swnd.hBackground = (HBRUSH)(COLOR_BTNFACE + 1);
		swnd.hIcon = NULL;
		swnd.hIconSm = NULL;
		swnd.hCursor = NULL;
		swnd.dwStyle = DEFAULT_SWND_STYLE;
		swnd.dwExStyle = 0;
		swnd.hMenuOrIdItem = 0;

		/*
		// 註冊視窗
		if (this->SysRegisterWindow(&swnd)) {
			// 建立視窗
			if (this->SysCreateWindow(&swnd)) {
				this->SetClientSize(DEFAULT_SWND_WIDTH, DEFAULT_SWND_HEIGHT);
				this->SetCenterPosition();
				this->Show();
				this->Update();
				return TRUE;
			}
		}
		*/

		if (this->CreateWindow(&swnd)) {
			this->SetClientSize(DEFAULT_SWND_WIDTH, DEFAULT_SWND_HEIGHT);
			this->SetCenterPosition();
			this->Show();
			this->Update();
			return TRUE;
		}
	}
	return FALSE;
}


/**
 * 結束類別物件處理 (釋放配置記憶體與成員物件)
 *
 * 此為虛擬函數, 由衍生類別繼承 \n
 * 視窗進入關閉階段時進行運作此一函數, 確保類別內所配置的物件與記憶體都被釋放.
 * 壁面物件或記憶體未釋放造成 memory leek.
 */
void CxFrameWindow::WindowInTheEnd()
{
	// TODO 視窗結束處理

	// 呼叫父類別繼續處理
	CxFrameObject::WindowInTheEnd();
}


/**
 * @brief	向系統註冊一個視窗
 * @param	[in] swndPtr SSWINDOW 結構資料位址
 * @return	@c BOOL \n
 *			操作成功將返回非零值(non-zero), 若操作失敗將返回零(zero)值.
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-registerclassexa
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-registerclassexw
 */
BOOL CxFrameWindow::SysRegisterWindow(LPSSFRAMEWINDOW swndPtr)
{
	UINT        uStyle = (CS_HREDRAW | CS_VREDRAW);    // | CS_DBLCLKS;
	HINSTANCE   hInst = NULL;
	HCURSOR     hCusr = NULL;
	HICON       hIcon = NULL;
	HBRUSH      hBrsh = NULL;
	WNDPROC     fnWndProc = NULL;
	WNDCLASSEX  wcex;

	if (swndPtr == NULL) {
		this->SetError(ERROR_INVALID_DATA);
		return FALSE;
	}

	// 填入註冊數據
	hInst = swndPtr->hInstance;
	fnWndProc = swndPtr->fnWndProc;
	uStyle |= swndPtr->uClassStyle;
	hCusr = swndPtr->hCursor;
	hIcon = swndPtr->hIcon;
	hBrsh = swndPtr->hBackground;

	// Check handle of module
	if (hInst == NULL) {
		if ((hInst = ::GetModuleHandle(NULL)) == NULL) {
			this->SetError(ERROR_INVALID_MODULETYPE);
			return FALSE;
		}
	}

	// Check and set cursor
	if (hCusr == NULL)
		hCusr = ::LoadCursor(NULL, IDC_ARROW);

	// Check and set icon (use default application icon)
	if (hIcon == NULL)
		hIcon = ::LoadIcon(NULL, IDI_APPLICATION);

	// Check and set back ground color
	if (hBrsh == NULL)
		hBrsh = (HBRUSH)(COLOR_WINDOW + 1);
	
	// Check and set the callback function
	if (NULL == fnWndProc)
		fnWndProc = CxFrameWindow::WndProc;

	// regist the window class
	::memset((void*)&wcex, 0, sizeof(wcex));
	wcex.cbSize = sizeof(WNDCLASSEX);	// size of the WNDCLASSEX structure
	wcex.style = uStyle;				// the window style
	wcex.lpfnWndProc = fnWndProc;		// the callback function
	wcex.cbClsExtra = 0;				// nothing to do, always 0
	wcex.cbWndExtra = 0;				// nothing to do, always 0
	wcex.hInstance = hInst;				// handle of module
	wcex.hIcon = hIcon;					// handle of icon
	wcex.hCursor = hCusr;				// handle of cursor
	wcex.hbrBackground = hBrsh;			// handle of background
	wcex.lpszMenuName = NULL;			// pointer of menu name (string)
	wcex.lpszClassName = swndPtr->pszClassName;	// pointer of class name (string)
	wcex.hIconSm = hIcon;				// pointer of icon for small icon using

	m_hModule = hInst;
	auto res = ::RegisterClassEx(&wcex);
	if (!res) {
		this->SetError(::GetLastError());
	}
	return static_cast<BOOL>(res);
}


/**
 * @brief	建立視窗
 * @param	[in] swndPtr SWINDOW 結構資料位址
 * @return	BOOL 型別 \n
 *			操作成功將返回非零值(non-zero), 若操作失敗將返回零(zero)值.
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-createwindowexa
 * @see		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-createwindowexw
 */
BOOL CxFrameWindow::SysCreateWindow(LPSSFRAMEWINDOW swndPtr)
{
	HWND	hWnd = NULL;
	DWORD	dwStyle = 0;    // WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX;
	DWORD	dwExStyle = 0;
	int		x, y, wd, ht;

	if (swndPtr == NULL) {
		this->SetError(ERROR_INVALID_DATA);
		return FALSE;
	}

	// save window sample info
	dwStyle |= swndPtr->dwStyle;
	dwExStyle |= swndPtr->dwExStyle;
	x = swndPtr->iPosx;
	y = swndPtr->iPosy;
	wd = swndPtr->iWidth;
	ht = swndPtr->iHeight;

	// Is using default window style?
	if (dwStyle == 0) dwStyle = DEFAULT_SWND_STYLE;

	// Create window
	hWnd = ::CreateWindowEx(
		dwExStyle,				// window extern style
		swndPtr->pszClassName,	// window class name
		swndPtr->pszTitleName,	// window name
		dwStyle,				// window style, "WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX"
		x,						// window position
		y,						// window position
		wd,						// window width
		ht,						// window height
		swndPtr->hWndParent,	// handle of parent window
		swndPtr->hMenuOrIdItem,	// handle of menu or Item ID
		m_hModule,				// handle of instance
		(LPVOID)this);			// pointer of parameter
	if (hWnd == NULL) {
		this->SetError(::GetLastError());
	}
	return hWnd != NULL;
}
