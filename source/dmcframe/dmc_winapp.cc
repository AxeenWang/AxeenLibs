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
