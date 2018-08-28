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
	int		GetBorderSize();

	BOOL	SetWindowPos(HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags) const;

	HDC		BeginPaint(PAINTSTRUCT* stPtr) const;
	BOOL	EndPaint(const PAINTSTRUCT* stPtr) const;

	LONG_PTR GetWindowLongPtr(int nIndex) const;
	LONG_PTR SetWindowLongPtr(int nIndex, LONG_PTR dwNewLong) const;

	// 取得連接視窗操作 Handle 及 callback function
	HWND	GetSafeHwnd() const;
	HWND	GetParent() const;
	WNDPROC	GetPrevWndProc() const;
	BOOL	IsWindow() const;
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
