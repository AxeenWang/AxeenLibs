/**************************************************************************//**
 * @file	wframe_button.hh
 * @brief	Win32 視窗操作 : 控制項 Button 類別
 * @date	2000-10-10
 * @date	2018-07-25
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_WIN32FRAME_BUTTON_HH__
#define __AXEEN_WIN32FRAME_BUTTON_HH__
#include "wframe_control.hh"

/**
 * @class	CxFrameButton
 * @brief	視窗操作 : 控制項 Button 類別
 *
 * 繼承 CxFrameControl, 控制項 Button 操作類別
 */
class CxFrameButton : public CxFrameControl
{
public:
	CxFrameButton();
	virtual ~CxFrameButton();

	// --- 尚未實作功能之標示

	BOOL	GetIdealSize(SIZE* sizePtr);				// BCM_GETIDEALSIZE
	BOOL	GetImageList(BUTTON_IMAGELIST* imlPtr);		// BCM_GETIMAGELIST
	BOOL	GetNote(LPTSTR szNotePtr, DWORD* ccNotePtr);// BCM_GETNOTE
	DWORD	GetNoteLength();							// BCM_GETNOTELENGTH
	// --- BCM_GETSPLITINFO
	// --- BCM_GETTEXTMARGIN
	// --- BCM_SETDROPDOWNSTATE
	// --- BCM_SETIMAGELIST
	// --- BCM_SETNOTE
	// --- BCM_SETSHIELD
	// --- BCM_SETSPLITINFO
	// --- BCM_SETTEXTMARGIN
	void	Click();									// BM_CLICK
	LRESULT	GetCheck();									// BM_GETCHECK
	LRESULT	GetImage(int iType);						// BM_GETIMAGE
	HBITMAP	GetImageBitmap();
	HICON	GetImageIcon();
	LRESULT GetState();									// BM_GETSTATE
	LRESULT SetCheck(int iCheck);						// BM_SETCHECK
	void	SetRadioClick(BOOL bState);					// BM_SETDONTCLICK
	LRESULT	SetImage(int iType, void* vPtr);			// BM_SETIMAGE
	LRESULT	SetImageBitmap(HBITMAP hBitmap);
	LRESULT	SetImageIcon(HICON hIcon);
	LRESULT SetState(BOOL bState);						// BM_SETSTATE
	void	SetStyle(DWORD dwStyle, BOOL bRepaint);		// BM_SETSTYLE

	BOOL	CreateButton(LPCTSTR szCaptionPtr, int x, int y, int wd, int ht, HWND hParent, int idItem, HINSTANCE hInst, WNDPROC fnWndProc = NULL);
	BOOL	CreateButton(HINSTANCE hInst, HWND hButton, int idItem, WNDPROC fnWndProc = NULL);
	BOOL	CreateButtonEx(HINSTANCE hInst, HWND hParent, int idItem, WNDPROC fnWndProc = NULL);

protected:
	virtual void WindowInTheEnd() override;
};

#endif	// !__AXEEN_WIN32FRAME_BUTTON_HH__
