/**************************************************************************//**
 * @file	wframe_editbox.hh
 * @brief	Win32 視窗操作 : 控制項 Edit Box 類別
 * @date	2000-10-10
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_WIN32FRAME_EDITBOX_HH__
#define __AXEEN_WIN32FRAME_EDITBOX_HH__
#include "wframe_control.hh"

/**
 * @class	CxFrameEditbox
 * @brief	視窗控制 - 控制項基底類別
 *
 * 繼承 CxFrameControl, 控制項 EditBox 操作類別
 **/
class CxFrameEditbox : public CxFrameControl
{
public:
	CxFrameEditbox();
	virtual ~CxFrameEditbox();

	// --- 標示為尚未實作

	BOOL CanUndo();									// EM_CANUNDO
	// --- EM_CHARFROMPOS
	// --- EM_EMPTYUNDOBUFFER
	// --- EM_FMTLINES
	// --- EM_GETCUEBANNER
	// --- EM_GETFIRSTVISIBLELINE
	// --- EM_GETHANDLE
	// --- EM_GETHILITE
	// --- EM_GETIMESTATUS
	int GetLimitText();								// EM_GETLIMITTEXT
	// --- EM_GETLINE
	// --- EM_GETLINECOUNT
	// --- EM_GETMARGINS
	// --- EM_GETMODIFY
	// --- EM_GETPASSWORDCHAR
	void  GetRect(LPRECT rcPtr);					// EM_GETRECT
	DWORD GetSelect(DWORD* dwPtr, DWORD* ddPtr);	// EM_GETSEL
	// --- EM_GETTHUMB
	// --- EM_GETWORDBREAKPROC
	// --- EM_HIDEBALLOONTIP
	// --- EM_LIMITTEXT
	// --- EM_LINEFROMCHAR
	// --- EM_LINEINDEX
	// --- EM_LINELENGTH
	// --- EM_LINESCROLL
	// --- EM_NOSETFOCUS
	// --- EM_POSFROMCHAR
	// --- EM_REPLACESEL
	// --- EM_SCROLL
	// --- EM_SCROLLCARET
	// --- EM_SETCUEBANNER
	// --- EM_SETHANDLE
	// --- EM_SETHILITE
	// --- EM_SETIMESTATUS
	void SetLimitText(int ccMax);
	// --- EM_SETMARGINS
	// --- EM_SETMODIFY
	// --- EM_SETPASSWORDCHAR
	BOOL SetReadonly(BOOL bEnable);					// EM_SETREADONLY
	void SetRect(LPRECT rcPtr);						// EM_SETRECT
	// --- EM_SETRECTNP
	void SetSelect(DWORD starting, DWORD ending);	// EM_SETSEL
	// --- EM_SETTABSTOPS
	// --- EM_SETWORDBREAKPROC
	// --- EM_SHOWBALLOONTIP
	// --- EM_TAKEFOCUS
	BOOL Undo();									// EM_UNDO, WM_UNDO

	BOOL	CreateEditBox(LPCTSTR szCaptionPtr, int x, int y, int wd, int ht, HWND hParent, int idItem, HINSTANCE hInst, WNDPROC fnWndProc = NULL);
	BOOL	CreateEditBox(HINSTANCE hInst, HWND hEdit, int idItem, WNDPROC fnWndProc = NULL);
	BOOL	CreateEditBoxEx(HINSTANCE hInst, HWND hParam, int idItem, WNDPROC fnWndProc = NULL);


protected:
	virtual void WindowInTheEnd() override;
};

#endif // !__AXEEN_WIN32FRAME_EDITBOX_HH__
