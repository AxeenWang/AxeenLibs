/**************************************************************************//**
 * @file	dmc_winapp.hh
 * @brief	DmcFrame class ibrary, the windows application entry point
 * @date	2000-10-10
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_DMCFRAME_WINAPP_HH__
#define __AXEEN_DMCFRAME_WINAPP_HH__
#include "dmc_thread.hh"

/**
 * @class DmWinApp
 * @brief The window process entry
 */
class DmWinApp : public DmThread
{
	friend class DmWindow;
	friend DmWinApp& GetAPP();

public:
	DmWinApp();
	virtual ~DmWinApp();

	BOOL IsReady() const;
	HINSTANCE GetInstanceHandle() const;
	HINSTANCE GetResourceHandle() const;

private:
	DmWinApp(const DmWinApp&) = delete;				// Disable copy construction
	DmWinApp& operator=(const DmWinApp&) = delete;	// Disable assignment operator

	void SetCallback();
	static DmWinApp* SetnGetThis(DmWinApp* thisPtr = NULL);

private:
	HINSTANCE	m_hInstance;
	HINSTANCE	m_hResource;
	WNDPROC		m_fnCallback;
};


#endif // !__AXEEN_DMCFRAME_WINAPP_HH__
