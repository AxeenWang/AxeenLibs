/**************************************************************************//**
 * @file	wframe_combo.hh
 * @brief	Win32 視窗操作 : 控制項 ComboBox 類別
 * @date	2000-10-10
 * @date	2018-07-25
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_WIN32FRAME_COMBO_HH__
#define __AXEEN_WIN32FRAME_COMBO_HH__
#include "wframe_control.hh"

/**
 * @class	CxFrameCombo
 * @brief	視窗操作 : 控制項 ComboBox 類別
 * @author	Swang
 * @note	繼承 CxFrameControl, 控制項 Combo Box 操作類別
 */
class CxFrameCombo : public CxFrameControl
{
public:
	CxFrameCombo();
	virtual ~CxFrameCombo();

	// --- 標示為尚未實作

	int  AddItem(LPCTSTR szPtr);								// CB_ADDSTRING
	int  DeleteItem(int nIndex);								// CB_DELETESTRING
	// --- CB_DIR
	// --- CB_FINDSTRING
	// --- CB_FINDSTRINGEXACT
	// --- CB_GETCOMBOBOXINFO
	int  GetCount();											// CB_GETCOUNT
	// --- CB_GETCUEBANNER
	int  GetCursel();											// CB_GETCURSEL
	// --- CB_GETDROPPEDCONTROLRECT
	// --- CB_GETDROPPEDSTATE
	// --- CB_GETDROPPEDWIDTH
	// --- CB_GETEDITSEL
	// --- CB_GETEXTENDEDUI
	// --- CB_GETHORIZONTALEXTENT
	// --- CB_GETITEMDATA
	// --- CB_GETITEMHEIGHT
	int GetItemText(int nIndex, LPTSTR szPtr);					// CB_GETLBTEXT
	int GetItemTextLength(int nIndex);							// CB_GETLBTEXTLEN
	// --- CB_GETLOCALE
	// --- CB_GETMINVISIBLE
	// --- CB_GETTOPINDEX
	// --- CB_INITSTORAGE
	int  InsertItem(int index, LPCTSTR szPtr);					// CB_INSERTSTRING
	// --- CB_LIMITTEXT
	void ResetContent();										// CB_RESETCONTENT
	void RemoveAllItem();
	// --- CB_SELECTSTRING
	// --- CB_SETCUEBANNER
	int  SetCursel(int nIndex);									// CB_SETCURSEL
	// --- CB_SETDROPPEDWIDTH
	// --- CB_SETEDITSEL
	// --- CB_SETEXTENDEDUI
	// --- CB_SETHORIZONTALEXTENT
	// --- CB_SETITEMDATA
	// --- CB_SETITEMHEIGHT
	// --- CB_SETLOCALE
	// --- CB_SETMINVISIBLE
	// --- CB_SETTOPINDEX
	// --- CB_SHOWDROPDOWN

	BOOL CreateCombo(LPCTSTR szCaptionPtr, int x, int y, int wd, int ht, HWND hParent, int idItem, HINSTANCE hInst, WNDPROC fnWndProc = NULL);
	BOOL CreateCombo(HINSTANCE hInst, HWND hCombo, int idItem, WNDPROC fnWndProc = NULL);
	BOOL CreateComboEx(HINSTANCE hInst, HWND hParent, int idItem, WNDPROC fnWndProc = NULL);

protected:
	virtual void WindowInTheEnd() override;

};

#endif	// !__AXEEN_WIN32FRAME_COMBO_HH__
