/**************************************************************************//**
 * @file	wframe_tab.hh
 * @brief	Win32 視窗操作 : 控制項 Tab 類別
 * @date	2010-10-12
 * @date	2018-07-25
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_WIN32FRAME_TAB_HH__
#define __AXEEN_WIN32FRAME_TAB_HH__
#include "wframe_control.hh"

/**************************************************//**
 * @class	CxFrameTab
 * @brief	標籤、標籤頁控制項操作類別
 * @author	Swang
 * @note	繼承 CxFrameControl, 控制項 Tab 操作類別
 *****************************************************/
class CxFrameTab : public CxFrameControl
{
public:
	CxFrameTab();
	virtual ~CxFrameTab();

	// --- 標示為尚未實作

	void AdjustRect(BOOL bMode, RECT* rcPtr);					// TCM_ADJUSTRECT
	BOOL DeleteAllItem();										// TCM_DELETEALLITEMS
	BOOL DeleteItem(int index);									// TCM_DELETEITEM
	void DeSelectAll(BOOL bDeSel);								// TCM_DESELECTALL
	int  GetCurselFocus();										// TCM_GETCURFOCUS
	int  GetCursel();											// TCM_GETCURSEL
	// --- TCM_GETEXTENDEDSTYLE
	// --- TCM_GETIMAGELIST
	BOOL GetItem(int index, TCITEM* tciPtr);					// TCM_GETITEM
	int  GetItemCount();										// TCM_GETITEMCOUNT
	BOOL GetItemRect(int index, RECT* rcPtr);					// TCM_GETITEMRECT
	// --- TCM_GETROWCOUNT
	// --- TCM_GETTOOLTIPS
	// --- TCM_GETUNICODEFORMAT
	// --- TCM_HIGHLIGHTITEM
	// --- TCM_HITTEST
	BOOL InsertItem(int index, TCITEM* tciPtr);					// TCM_INSERTITEM
	BOOL InsertItem(int index, LPCTSTR szPtr);
	// --- TCM_REMOVEIMAGE
	void SetCurselFocus(int index);								// TCM_SETCURFOCUS
	int  SetCursel(int index);									// TCM_SETCURSEL
	// --- TCM_SETEXTENDEDSTYLE
	// --- TCM_SETIMAGELIST
	BOOL SetItem(int index, TCITEM* tciPtr);					// TCM_SETITEM
	// --- TCM_SETITEMEXTRA
	LRESULT SetItemSize(int wd, int ht);						// TCM_SETITEMSIZE
	INT  SetMinTabWidth(int wd);								// TCM_SETMINTABWIDTH
	// --- TCM_SETPADDING
	// --- TCM_SETTOOLTIPS
	// --- TCM_SETUNICODEFORMAT

	BOOL CreateTab(LPCTSTR szCaptionPtr, int x, int y, int wd, int ht, HWND hParent, int idItem, HINSTANCE hInst, WNDPROC fnWndProc = NULL);
	BOOL CreateTab(HINSTANCE hInst, HWND hTab, int idItem, WNDPROC fnWndProc = NULL);
	BOOL CreateTabEx(HINSTANCE hInst, HWND hParent, int idItem, WNDPROC fnWndProc = NULL);

protected:
	virtual void WindowInTheEnd() override;
};

#endif // !__AXEEN_WIN32FRAME_TAB_HH__
