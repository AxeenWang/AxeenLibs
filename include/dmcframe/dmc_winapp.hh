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

public:
	DmWinApp();
	virtual ~DmWinApp();

private:
	DmWinApp(const DmWinApp&);				// Disable copy construction
	DmWinApp& operator = (const DmWinApp&);	// Disable assignment operator

	static DmWinApp* SetnGetThis(DmWinApp* thisPtr = NULL);
};


#endif // !__AXEEN_DMCFRAME_WINAPP_HH__
