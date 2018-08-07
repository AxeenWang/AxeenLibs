/**************************************************************************//**
 * @file	wframe_dialog.hh
 * @brief	Win32 視窗操作 : 控制項 Dialog 類別
 * @date	2000-10-10
 * @date	2018-07-24
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_WIN32FRAME_DIALOG_HH__
#define __AXEEN_WIN32FRAME_DIALOG_HH__
#include "wframe_object.hh"

/******************************************************//**
 * @class	CxFrameDialog
 * @brief	視窗操作 : 控制項 Dialog 類別
 * @author	Swang
 * @note	繼承 CxFrameControl, 控制項 Dialog 操作類別
 *********************************************************/
class CxFrameDialog : public CxFrameObject
{
protected:
	static  INT_PTR CALLBACK DialogProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
	virtual INT_PTR MessageDispose(UINT uMessage, WPARAM wParam, LPARAM lParam);

public:
	CxFrameDialog();
	virtual ~CxFrameDialog();
	BOOL CreateDialog(HWND hParent, int idItem, BOOL bModule = FALSE);

protected:
	virtual void WindowInTheEnd() override;
};

#endif  // !__AXEEN_WIN32FRAME_DIALOG_HH__
