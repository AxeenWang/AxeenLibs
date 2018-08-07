/**************************************************************************//**
 * @file	wframe_window.hh
 * @brief	Win32 視窗操作 : 視窗框架類別
 * @date	2010-10-10
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_WIN32FRAME_WINDOW_HH__
#define __AXEEN_WIN32FRAME_WINDOW_HH__
#include "wframe_object.hh"


 /**
 * @class	CxFrameWindow
 * @brief	視窗操作 : 視窗操作類別
 *
 * 用於操作與控制視窗, 自帶 WndProc callback function\n
 */
class CxFrameWindow : public CxFrameObject
{
protected:
	static	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
	virtual	LRESULT MessageDispose(UINT uMessage, WPARAM wParam, LPARAM lParam);
	LRESULT	DefaultWindowProc(UINT uMessage, WPARAM wParam, LPARAM lParam);
	int	RunPeekMessage();
	int	RunStayMessage();

public:
	CxFrameWindow();
	virtual ~CxFrameWindow();

	int		Run(BOOL bPeek=FALSE);
	BOOL	CreateWindow(LPSSFRAMEWINDOW swndPtr);
	BOOL	CreateSample(HINSTANCE hInstance);

protected:
	virtual void WindowInTheEnd() override;
	BOOL SysRegisterWindow(LPSSFRAMEWINDOW swndPtr);
	BOOL SysCreateWindow(LPSSFRAMEWINDOW swndPtr);
};

#endif	// !__AXEEN_WIN32FRAME_WINDOW_HH__
