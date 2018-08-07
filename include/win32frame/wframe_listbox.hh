/**************************************************************************//**
 * @file	wframe_listbox.hh
 * @brief	Win32 視窗操作 : 控制項 List Box 類別
 * @date	2000-10-10
 * @date	2018-07-27
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_WIN32FRAME_LISTBOX_HH__
#define __AXEEN_WIN32FRAME_LISTBOX_HH__
#include "wframe_control.hh"

/**
 * @class	CxFrameListbox
 * @brief	視窗操作 : 控制項 List Box 類別
 * @author	Swang
 * @note	繼承 CxFrameControl, 控制項 List Box 操作類別
 */
class CxFrameListbox : public CxFrameControl
{
public:
	CxFrameListbox();
	virtual ~CxFrameListbox();

	// --- 標示為尚未實作

	int AddFile(TCHAR* szName);										// LB_ADDFILE
	int	AddItem(TCHAR* szText);										// LB_ADDSTRING
	int DeleateItem(int index);										// LB_DELETESTRING
	int AddDir(int iAttrib, TCHAR* szPath);							// LB_DIR
	int FindItem(int index, TCHAR* szText);							// LB_FINDSTRING
	int FindItemEx(int index, TCHAR* szText);						// LB_FINDSTRINGEXACT
	// --- LB_GETANCHORINDEX
	// --- LB_GETCARETINDEX
	int GetCount();													// LB_GETCOUNT
	int GetCursel();												// LB_GETCURSEL
	// --- LB_GETHORIZONTALEXTENT
	// --- LB_GETITEMDATA
	// --- LB_GETITEMHEIGHT
	int GetItemRect(int index, RECT* rcPtr);						// LB_GETITEMRECT
	// --- LB_GETLISTBOXINFO
	// --- LB_GETLOCALE
	int GetSelectionState(int index);								// LB_GETSEL
	int GetSelectionCount();										// LB_GETSELCOUNT
	// --- LB_GETSELITEMS
	int GetItemText(int index, TCHAR* szBuff);						// LB_GETTEXT
	int GetItemTextLength(int index);								// LB_GETTEXTLEN
	// --- LB_GETTOPINDEX
	// --- LB_INITSTORAGE
	int InsertItem(int index, TCHAR* szText);						// LB_INSERTSTRING
	// --- LB_ITEMFROMPOINT
	// --- LB_RESETCONTENT
	// --- LB_SELECTSTRING
	// --- LB_SELITEMRANGE
	// --- LB_SELITEMRANGEEX
	// --- LB_SETANCHORINDEX
	// --- LB_SETCARETINDEX
	// --- LB_SETCOLUMNWIDTH
	// --- LB_SETCOUNT
	int SetCursel(int index);										// LB_SETCURSEL
	// --- LB_SETHORIZONTALEXTENT
	// --- LB_SETITEMDATA
	// --- LB_SETITEMHEIGHT
	// --- LB_SETLOCALE
	int SetSelectionState(int index, BOOL bState);					// LB_SETSEL
	// --- LB_SETTABSTOPS
	// --- LB_SETTOPINDEX

	BOOL CreateListbox(HINSTANCE hInst, HWND hList, int idItem, WNDPROC fnWndProc = NULL);
	BOOL CreateListboxEx(HINSTANCE hInst, HWND hParent, int idItem, WNDPROC fnWndProc = NULL);

protected:
	virtual void WindowInTheEnd() override;
};

#endif // !__AXEEN_WIN32FRAME_LISTBOX_HH__
