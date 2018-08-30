/**************************************************************************//**
 * @file	dmc_thread.hh
 * @brief	DMC Frame Thread 控制類別
 * @date	2000-10-10
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_DMCFRAME_THREAD_HH__
#define __AXEEN_DMCFRAME_THREAD_HH__
#include "dmc_object.hh"

class DmThread : public DmObject
{
public:
	DmThread();
	virtual ~DmThread();

	// Overridables
	virtual int	MessageLoop(int bPreek);

protected:
	// These virtual functions can be overridden
	virtual int MessageLoopNormal();
	virtual int MessageLoopPeek();
};

#endif // !__AXEEN_DMCFRAME_THREAD_HH__
