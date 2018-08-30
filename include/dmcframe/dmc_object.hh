/**************************************************************************//**
 * @file	dmc_object.hh
 * @brief	DMC Frame 基底類別
 * @date	2000-10-10
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_DMCFRAME_OBJECT_HH__
#define __AXEEN_DMCFRAME_OBJECT_HH__
#include "dmc_define.hh"

// Forward declarations.
class DmObject;
class DmThread;
class DmWinApp;
class DmWindow;
DmWinApp& GetAPP();

/**
 * @class DmObject
 * @brief DMC-Frame base class
 */
class DmObject
{
public:
	DmObject();
	virtual ~DmObject();

	HINSTANCE GetSaeModule() const;

private:
	DmObject(const DmObject&) = delete;				// Disable copy construction
	DmObject& operator=(const DmObject&) = delete;	// Disable assignment operator
};

#endif // !__AXEEN_DMCFRAME_OBJECT_HH__
