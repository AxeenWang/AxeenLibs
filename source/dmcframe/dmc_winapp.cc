/**************************************************************************//**
 * @file	dmc_winapp.cc
 * @brief	DmcFrame, The Windows application start
 * @date	2018-08-30
 * @date	2010-08-30
 * @author	Swang
 *****************************************************************************/
#include "dmcframe/dmc_winapp.hh"

//! DmWinApp constructor
DmWinApp::DmWinApp() : DmThread()
{

}

//! DmWinApp destructor
DmWinApp::~DmWinApp() { }

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
