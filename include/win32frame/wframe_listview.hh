/**************************************************************************//**
 * @file	wframe_listview.hh
 * @brief	Win32 視窗操作 : 控制項 ListView 類別
 * @date	2000-10-10
 * @date	2018-07-25
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_WIN32FRAME_LISTVIEW_HH__
#define __AXEEN_WIN32FRAME_LISTVIEW_HH__
#include "wframe_control.hh"

/**
 * @class	CxFrameListview
 * @brief	ListView 控制項操作類別
 *
 *	繼承 CxFrameControl, 控制項 ListView 操作類別
 */
class CxFrameListview : public CxFrameControl
{
public:
	CxFrameListview();
	virtual ~CxFrameListview();

	// --- 代表尚未實作之功能

	// --- LVM_APPROXIMATEVIEWRECT
	// --- LVM_ARRANGE
	// --- LVM_CREATEDRAGIMAGE
	BOOL	DeleteItemAll();											// LVM_DELETEALLITEMS
	BOOL	DeleteColumn(int nIndex);									// LVM_DELETECOLUMN
	void	DeleteColumnAll();
	BOOL	DeleteItem(int nIndex);										// LVM_DELETEITEM
	void	EditLabel(int nIndex);										// LVM_EDITLABEL
	// --- LVM_ENSUREVISIBLE
	// --- LVM_FINDITEM
	// --- LVM_GETBKCOLOR
	// --- LVM_GETCALLBACKMASK
	BOOL	GetColumn(int nIndex, LPTSTR szColumnPtr, int ccMax);		// LVM_GETCOLUMN
	int		GetColumnCount();
	// --- LVM_GETCOLUMNORDERARRAY
	int		GetColumnWidth(int nIndex);									// LVM_GETCOLUMNWIDTH
	int		GetCountPerPage();											// LVM_GETCOUNTPERPAGE
	HWND	GetEditControl();											// LVM_GETEDITCONTROL
	DWORD	GetExListViewStyle();										// LVM_GETEXTENDEDLISTVIEWSTYLE
	// --- LVM_GETHEADER
	// --- LVM_GETIMAGELIST
	// --- LVM_GETISEARCHSTRING
	// --- LVM_GETITEM
	int		GetItemCount();												// LVM_GETITEMCOUNT
	BOOL	GetItemPosition(int nIndex, LPPOINT stPtr);					// LVM_GETITEMPOSITION
	BOOL	GetItemRect(int nIndex, LPRECT rcPtr);						// LVM_GETITEMRECT
	BOOL	GetItemRect(int nIndex, int nMode, LPRECT rcPtr);
	// --- LVM_GETITEMSPACING
	int		GetItemState(int nIndex, int nMode= LVIS_STATEIMAGEMASK);	// LVM_GETITEMSTATE
	BOOL	GetItemText(int nIndex, int nSub, LPTSTR szTextPtr, int ccLen);// LVM_GETITEMTEXT
	int		GetNextSelectItem();										// LVM_GETNEXTITEM
	int		GetFirstSelectItem();
	int		GetSelectItem();
	// --- LVM_GETNUMBEROFWORKAREAS
	// --- LVM_GETORIGIN
	int		GetSelectCount();											// LVM_GETSELECTEDCOUNT
	// --- LVM_GETSELECTIONMARK
	// --- LVM_GETSTRINGWIDTH
	// --- LVM_GETSUBITEMRECT
	// --- LVM_GETTEXTBKCOLOR
	// --- LVM_GETTEXTCOLOR
	int		GetTopIndex();												// LVM_GETTOPINDEX
	// --- LVM_GETVIEWRECT
	// --- LVM_GETWORKAREAS
	// --- LVM_HITTEST
	BOOL	InsertColumn(int nIndex, int wd, int nAlign, LPTSTR szTextPtr);// LVM_INSERTCOLUMN
	BOOL	InsertItem(int nIndex, int nSub, LPTSTR szTextPtr);			// LVM_INSERTITEM
	// --- LVM_REDRAWITEMS
	// --- LVM_SCROLL
	BOOL	SetBkColor(COLORREF dwColor);								// LVM_SETBKCOLOR
	// --- LVM_SETCALLBACKMASK
	BOOL	SetColumn(int nIndex, LPTSTR szTextPtr);					// LVM_SETCOLUMN
	// --- LVM_SETCOLUMNORDERARRAY
	BOOL	SetColumnWidth(int nIndex, int nPixel);						// LVM_SETCOLUMNWIDTH
	void	SetExListViewStyle(DWORD dwExStyle);						// LVM_SETEXTENDEDLISTVIEWSTYLE
	// --- LVM_SETICONSPACING
	// --- LVM_SETIMAGELIST
	// --- LVM_SETITEM
	// --- LVM_SETITEMCOUNT
	// --- LVM_SETITEMPOSITION
	// --- LVM_SETITEMPOSITION32
	BOOL	SetItemState(int nIndex, LPLVITEM lvitemPtr);				// LVM_SETITEMSTATE
	BOOL	SetItemState(int nIndex, BOOL bState);
	BOOL	SetItemText(int nIndex, int nSub, LPTSTR szTextPtr);		// LVM_SETITEMTEXT
	// --- LVM_SETSELECTIONMARK
	BOOL	SetTextBkColor(COLORREF dwColor);							// LVM_SETTEXTBKCOLOR
	BOOL	SetTextColor(COLORREF dwColor);								// LVM_SETTEXTCOLOR
	// --- LVM_SETWORKAREAS
	// --- LVM_SORTITEMS
	// --- LVM_SUBITEMHITTEST
	// --- LVM_UPDATE

	BOOL CreateListview(LPCTSTR szCaptionPtr, int x, int y, int wd, int ht, HWND hParent, int idItem, HINSTANCE hInst, WNDPROC fnWndProc = NULL);
	BOOL CreateListview(HINSTANCE hInst, HWND hListv, int idItem, WNDPROC fnWndProc = NULL);
	BOOL CreateListviewEx(HINSTANCE hInst, HWND hParent, int idItem, WNDPROC fnWndProc = NULL);

protected:
	virtual void DefaultReportStyle();
	virtual void WindowInTheEnd() override;
	COLORREF ColorShade(COLORREF c, float fPercent);

private:
	void Example1(WPARAM wParam, LPARAM lParam);

protected:
	int m_nSelectItemCount;		//!< 被選取項目總數
	int m_nSelectItemIndex;		//!< 當前選取的索引
};


/**
 * @brief	建立顏色陰影
 * @param	[in] c			COLORREF 格式，顏色值
 * @param	[in] fPercent	陰影階層
 * @return	@c COLORREF 型別 \n 返回值為指定顏色陰影值
 */
inline COLORREF CxFrameListview::ColorShade(COLORREF c, float fPercent)
{
	//	create a lighter shade (by fPercent %) of a given colour
	return RGB((BYTE)((float)GetRValue(c) * fPercent / 100.0),
		(BYTE)((float)GetGValue(c) * fPercent / 100.0),
		(BYTE)((float)GetBValue(c) * fPercent / 100.0));
}

#endif	// !__AXEEN_WIN32FRAME_LISTVIEW_HH__
