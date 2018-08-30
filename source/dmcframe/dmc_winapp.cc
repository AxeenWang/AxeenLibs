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
 * @return	@c ���O: HINSTANCE, ��^��e�{�ǹ�ҥN�X
 */
HINSTANCE DmWinApp::GetInstanceHandle() const { return m_hInstance; }

/**
 * @brief	Get resource instance handle
 * @return	@c ���O: HINSTANCE, ��^��e�귽��ҥN�X
 */
HINSTANCE DmWinApp::GetResourceHandle() const { return m_hResource; }


/**
 * @brief	�]�w Callback function
 *
 * �]�w�����{�ǨϥΰT���B�z callback function (WndProc) ��}
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

		// �V�t�ε��U����
		if (::RegisterClass(&wc) == 0) {
			break;
		}

		// �V�t�Ψ��o�������U�T��
		::memset(&wc, 0, sizeof(wc));
		::GetClassInfo(hModule, szClassName, &wc);

		// �V�t�Ψ����������U (�ϵ��U�B���P)
		if (::UnregisterClass(szClassName, hModule) == 0) {
			break;
		}

		if (wc.lpfnWndProc == NULL) {
			break;
		}

		// �O�s���
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
 * @return	@c ���O: DmWinApp \n
 *			�Y��^�D�s��(nonzero) ����e windows application thread �� pointer \n
 *			�Y��^�s�ȥN���e�� windows application thread �|���N��
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
