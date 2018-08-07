/**************************************************************************//**
 * @file	wframe_control.hh
 * @brief	Win32 視窗操作 : 控制項操作項基底類別
 * @date	2000-10-10
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_WIN32FRAME_CONTROL_HH__
#define __AXEEN_WIN32FRAME_CONTROL_HH__
#include "wframe_object.hh"

/**
 * @class	CxFrameControl
 * @brief	視窗操作 : 控制項操作項基底類別
 * @note	繼承 CxFrameObject, 控制項操作基礎類別.
 */
class CxFrameControl : public CxFrameObject
{
public:
	CxFrameControl();
	CxFrameControl(EECTRLTYPE eType);
	virtual ~CxFrameControl();

	BOOL	CreateController(LPSSCTRL ctrlPtr);
	BOOL	CreateController(HINSTANCE hInst, HWND hCtrl, int idItem, WNDPROC fnWndProc = NULL);
	BOOL	CreateControllerEx(HINSTANCE hInst, HWND hWndParent, int idItem, WNDPROC fnWndProc = NULL);

protected:
	virtual void  WindowInTheEnd() override;
	LPCTSTR GetControlClassName(EECTRLTYPE index);
};

#endif  // !__AXEEN_WIN32FRAME_CONTROL_HH__
