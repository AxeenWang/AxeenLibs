/**************************************************************************//**
 * @file	dmc_thread.cc
 * @brief	DMC Frame Thread 控制類別成員函數
 * @date	2000-10-10
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#include "dmcframe/dmc_thread.hh"

//! DmThread construct
DmThread::DmThread() : DmObject() { }

//! DmObject deconstruct
DmThread::~DmThread() { }

/**
 * @brief	視窗訊息迴圈
 * @remark	標準訊息迴圈，等待訊息及進行對應處理
 * @return	@c 型別: int, 返回值為視窗結束碼
 */
int DmThread::MessageLoopNormal()
{
	MSG message;

	::memset(&message, 0, sizeof(message));
	while (::GetMessage(&message, NULL, 0, 0)) {
		::TranslateMessage(&message);
		::DispatchMessage(&message);
	}
	return (int)message.wParam;
}

/**
 * @brief	視窗訊息迴圈
 * @remark	訊息處理迴圈，不等等待訊息
 * @return	@c 型別: int, 返回值為視窗結束碼
 */
int DmThread::MessageLoopPeek()
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
	}
	return (int)message.wParam;
}

//! 類別結束處理
void DmThread::ClassInTheEnd()
{

	// Pass to base class
	DmObject::ClassInTheEnd();
}
