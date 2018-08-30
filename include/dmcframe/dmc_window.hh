/**************************************************************************//**
 * @file	dmc_window.cc
 * @brief	DMC Frame Window 基底類別
 * @date	2000-10-10
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_DMCFRAME_WINDOW_HH__
#define __AXEEN_DMCFRAME_WINDOW_HH__
#include "dmc_object.hh"

/**
 * @class DmWindow
 * @brief Provides the base functionality of all window classes in the Axeen Class Library.
 */
class DmWindow : public DmObject
{
public:
	DmWindow();
	virtual ~DmWindow();

	// 此區為虛擬函數可進行繼承覆蓋，改寫所需所需內容。
	virtual BOOL Attach(HWND hWnd);
	virtual BOOL AttachDlgItem(UINT uID, HWND hWndParent);
	virtual HWND Detach();
	virtual HWND Create();
	virtual HWND CreateEx();
	virtual void Destroy();

	// 包裝 Win32 API 函數, 此區函數不要進行覆蓋
	LRESULT SendMessage(UINT uMessage, WPARAM wParam, LPARAM lParam) const;
	BOOL	PostMessage(UINT uMessage, WPARAM wParam, LPARAM lParam) const;
	LRESULT SendMessage(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam) const;
	BOOL	PostMessage(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam) const;
	LRESULT CallWindowProc(WNDPROC lpPrevWndFunc, UINT uMessage, WPARAM wParam, LPARAM lParam) const;
	LRESULT DefWindowProc(UINT uMessage, WPARAM wParam, LPARAM lParam) const;

	BOOL	UpdateWindow() const;
	BOOL	EnableWindow(BOOL bEnable = TRUE) const;
	BOOL	DisableWindow() const;
	BOOL	ShowWindow(int nCmdShow = SW_SHOWNORMAL) const;
	BOOL	HideWindow() const;

	BOOL	GetWindowRect(RECT* rcPtr) const;
	BOOL	GetClientRect(RECT* rcPtr) const;
	int		GetBorderSize() const;
	BOOL	ClientToScreen(POINT* ptPtr) const;
	BOOL	ClientToScreen(RECT* rcPtr) const;

	BOOL	SetWindowPos(HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags) const;
	BOOL	SetWindowPosition(int x, int y) const;
	BOOL	SetWindowSize(int w, int h) const;
	BOOL	SetClientSize(int w, int h) const;
	BOOL	SetCenterPosition() const;
	HDWP	DeferWindowPos(HDWP hWinPosInfo, HWND hWndInsertAfter, int  x, int  y, int  cx, int  cy, UINT uFlags) const;

	HDC		BeginPaint(PAINTSTRUCT* stPtr) const;
	BOOL	EndPaint(const PAINTSTRUCT* stPtr) const;
	HDC		GetDC() const;
	HDC		GetDCEx(HRGN hrgnClip, DWORD flags) const;
	BOOL	DrawMenuBar() const;

	BOOL	BringWindowToTop() const;

	int		GetClassName(TCHAR* szClassNamePtr, int cchMax) const;
	int		GetWindowTextLength() const;
	int		GetWindowText(TCHAR* szTextPtr, size_t cchMax) const;
	BOOL	SetWindowText(const TCHAR* szTextPtr) const;
	UINT	GetDlgItemInt(int nIDDlgItem, BOOL bSigned) const;
	UINT	GetDlgItemInt(int nIDDlgItem, BOOL* bTranslatedPtr, BOOL bSigned) const;
	UINT	GetDlgItemText(int nIDDlgItem, TCHAR* szTextPtr, int cchMax) const;
	BOOL	SetDlgItemText(int nIDDlgItem, const TCHAR* szTextPtr) const;

	BOOL	CheckDlgButton(int nIDButton, UINT uCheck) const;
	BOOL	GetScrollInfo(int nBar, SCROLLINFO* siPtr) const;

	DWORD	GetStyle() const;
	DWORD	GetExStyle() const;
	DWORD	SetStyle(DWORD dwStyle) const;
	DWORD	SetExStyle(DWORD dwStyle) const;

	HWND	GetParent() const;
	HWND	GetAncestor(UINT uFlags = GA_ROOTOWNER) const;
	HWND	GetActiveWindow() const;
	HWND	GetDesktopWindow() const;
	HWND	GetDlgItem(int nIDDlgItem) const;
	int		GetDlgCtrlID() const;

	HWND	GetFocus() const;
	HWND	SetFocus() const;
	HWND	SetCapture() const;
	HWND	GetCapture() const;
	BOOL	ReleaseCapture() const;

	HFONT	GetFont() const;
	void	SetFont(HFONT hFont, BOOL bRedraw = TRUE);

	HICON	GetIcon(int nType) const;
	HICON	SetIcon(HICON hIcon, int nType) const;

	UINT_PTR	SetTimer(UINT_PTR nIDEvent, UINT uElapse, TIMERPROC lpTimerFunc) const;
	BOOL		KillTimer(UINT_PTR uIDEvent) const;

	LONG_PTR	GetWindowLongPtr(int nIndex) const;
	LONG_PTR	SetWindowLongPtr(int nIndex, LONG_PTR dwNewLong) const;
	ULONG_PTR	GetClassLongPtr(int nIndex) const;
	ULONG_PTR	SetClassLongPtr(int nIndex, LONG_PTR dwNewLong) const;

	// 取得連接視窗操作 Handle 及 callback function
	HWND	GetSafeHwnd() const;
	WNDPROC	GetPrevWndProc() const;
	BOOL	IsWindow() const;
	BOOL	IsChild(HWND hWndChild) const;
	BOOL	IsWindowEnable() const;
	BOOL	IsWindowVisible() const;
	operator HWND() const;

protected:
	// These virtual functions can be overridden
	virtual LRESULT	DefaultWindowProc(UINT uMessage, WPARAM wParam, LPARAM lParam);
	virtual void	OnClose();
	virtual void	OnDestroy();
	virtual LRESULT WndProc(UINT uMessage, WPARAM wParam, LPARAM lParam);
	virtual void	DeathOfWindow();

private:
	DmWindow(const DmWindow&);					// Disable copy construction
	DmWindow& operator=(const DmWindow&);		// Disable assignment operator
	DmWindow(HWND hWnd);						// Private constructor used internally

	static LRESULT CALLBACK StaticWindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
	void AttachToClass(HWND hWnd);

protected:
	HWND	m_hWnd;				//!< 視窗(控制項)操作碼
	WNDPROC	m_fnPrevWndProc;	//!< 視窗訊息處理 Callback function 位址
	BOOL	m_bAttach;			//!< 是否使用 Attach 連接
};

#endif // !__AXEEN_DMCFRAME_WINDOW_HH__
