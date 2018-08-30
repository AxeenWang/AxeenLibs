/**************************************************************************//**
 * @file	dmc_winapp.cc
 * @brief	DmcFrame, The Windows application start
 * @date	2018-08-30
 * @date	2010-08-30
 * @author	Swang
 *****************************************************************************/
#include "dmcframe/dmc_winapp.hh"
#include "dmcframe/dmc_window.hh"

//! DmWinApp constructor
DmWinApp::DmWinApp() : DmThread(), m_hInstance(NULL), m_hResource(NULL), m_fnCallback(NULL)
{
	this->SetnGetThis(this);
	this->SetCallback();
}

//! DmWinApp destructor
DmWinApp::~DmWinApp() { }

BOOL DmWinApp::IsReady() const
{
	if (m_fnCallback == NULL || m_hInstance == NULL || m_hResource == NULL)
		return FALSE;
	return TRUE;

	/*
	auto bRes = BOOL(FALSE);
	for (;;) {
		if (m_fnCallback == NULL) break;
		if (m_hInstance == NULL) break;
		if (m_hResource == NULL) break;
		bRes = TRUE;
	}
	return bRes;
	*/
}

/**
 * @brief	Get instance handle
 * @return	@c 型別: HINSTANCE, 返回當前程序實例代碼
 */
HINSTANCE DmWinApp::GetInstanceHandle() const { return m_hInstance; }

/**
 * @brief	Get resource instance handle
 * @return	@c 型別: HINSTANCE, 返回當前資源實例代碼
 */
HINSTANCE DmWinApp::GetResourceHandle() const { return m_hResource; }


/**
 * @brief	設定 Callback function
 *
 * 設定視窗程序使用訊息處理 callback function (WndProc) 位址
 */
void DmWinApp::SetCallback()
{
	const TCHAR* szClassName = TEXT("Axeen DmcFrame Class");
	HMODULE hModule;	
	WNDCLASS wc;

	for (;;) {
		
		if ((hModule = ::GetModuleHandle(NULL)) == NULL) {
			break;
		}

		::memset(&wc, 0, sizeof(wc));
		wc.hInstance = hModule;
		wc.lpfnWndProc = DmWindow::StaticWindowProc;
		wc.lpszClassName = szClassName;

		// 向系統註冊視窗
		if (::RegisterClass(&wc) == 0) {
			break;
		}

		// 向系統取得視窗註冊訊息
		::memset(&wc, 0, sizeof(wc));
		::GetClassInfo(hModule, szClassName, &wc);

		// 向系統取消視窗註冊 (反註冊、註銷)
		if (::UnregisterClass(szClassName, hModule) == 0) {
			break;
		}

		if (wc.lpfnWndProc == NULL) {
			break;
		}

		// 保存資料
		m_fnCallback = wc.lpfnWndProc;
		m_hInstance = hModule;
		m_hResource = hModule;
		return;
	}

	m_fnCallback = NULL;
}

/**
 * @brief	set and get DmWinApp opinter
 * @param	[in] thisPtr	Pointer of class DmWindow
 * @return	@c 型別: DmWinApp \n
 *			若返回非零值(nonzero) 為當前 windows application thread 的 pointer \n
 *			若返回零值代表當前的 windows application thread 尚未就緒
 */
DmWinApp* DmWinApp::SetnGetThis(DmWinApp* thisPtr)
{
	static DmWinApp* dmWinAppPtr = NULL;

	if (reinterpret_cast<DmWinApp*>(-1) == thisPtr) {
		dmWinAppPtr = NULL;
	}
	else if (NULL == dmWinAppPtr) {
		dmWinAppPtr = thisPtr;
	}

	return dmWinAppPtr;
}

DmWinApp& GetAPP() { DmWinApp::SetnGetThis(); }
