/**************************************************************************//**
 * @file	dmc_object.hh
 * @brief	DMC Frame 基底類別
 * @date	2000-10-10
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_DMCFRAME_OBJECT_HH__
#define __AXEEN_DMCFRAME_OBJECT_HH__
#include "axeen/axeen_setup.hh"
#include "axeen/axeen_ement.hh"

/**
 * @class DmObject
 * @brief DMC-Frame base class
 */
class DmObject
{
public:
	DmObject();
	virtual ~DmObject();

protected:
	virtual void ClassInTheEnd();
};

#endif // !__AXEEN_DMCFRAME_OBJECT_HH__
