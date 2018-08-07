/**************************************************************************//**
 * @file	wframe_object.hh
 * @brief	Win32 視窗、控制項操作基底類別
 * @date	2000-10-10
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_WIN32FRAME_OBJECT_HH__
#define __AXEEN_WIN32FRAME_OBJECT_HH__
#include "wframe_define.hh"

/**
 * @class	CxFrameObject
 * @brief	視窗操作基底類別
 * @author	Swang
 * 
 * 視窗與控制項操作基底類別, 負責視窗與控制項通用函數處理.
 */
class CxFrameObject
{
public:
	CxFrameObject();
	CxFrameObject(EECTRLTYPE eType);
	virtual ~CxFrameObject();

	DWORD	GetError();
	void	SetError(DWORD dwErrCode, LPCTSTR szPtr = NULL);
	void	ShowError();

	LRESULT	SendMessage(UINT uMessage, WPARAM wParam, LPARAM lParam);
	BOOL	PostMessage(UINT uMessage, WPARAM wParam, LPARAM lParam);
	void	LeaveWindow();

	BOOL	Update();
	BOOL	Enable(BOOL bEnable = TRUE);
	BOOL	Disable();
	BOOL	Show(int nCmdShow = SW_SHOW);
	BOOL	Hide();

	BOOL	GetWindowRect(LPRECT rcPtr);
	BOOL	GetClientRect(LPRECT rcPtr);
	int		GetBorderSize();

	BOOL	SetPosition(int x, int y);
	BOOL	SetSize(int wd, int ht);
	BOOL	SetClientSize(int wd, int ht);
	void	SetCenterPosition();

	HWND	GetFocus();
	HWND	SetFocus();
	HWND	GetTopWindow();

	int		GetText(LPTSTR szTextPtr, size_t ccLen);
	int		GetTextLength();
	BOOL	SetText(LPCTSTR szTextPtr);

	HICON	GetIcon(int nType);
	HICON	SetIcon(HICON hIcon, int nType);

	HFONT	CreateFont(LPCTSTR fontFace, int nSize, BOOL bBlod, int nCharset = DEFAULT_CHARSET);
	BOOL	DeleteFont(HFONT* hFontPtr);
	BOOL	DeleteFont();
	HFONT	GetFont();
	void	SetFont(HFONT hFont, BOOL bRedraw = TRUE);
	void	SetFont(LPCTSTR fontFace, int nSize, BOOL bBlod, int nCharset = DEFAULT_CHARSET, BOOL bRedraw = TRUE);

	DWORD	GetStyle();
	DWORD	SetStyle(DWORD dwStyle);
	DWORD	GetExStyle();
	DWORD	SetExStyle(DWORD dwExStyle);

	UINT_PTR	SetTimer(UINT_PTR nIDEvent, UINT uElapse, TIMERPROC fnTimerFunc);
	BOOL		KillTimer();

	HINSTANCE	GetModule();
	HWND		GetParent();
	HWND		GetHandle();
	int			GetControlID();
	BOOL		IsExist();

protected:
	virtual void WindowInTheEnd();
	void SysCloseWindow();
	void SysDestroyWindow(int nExitCode = 0);
	BOOL SysSetWindowProcess(WNDPROC fnWndProc);
	void InitCommCtrl();

protected:
	HINSTANCE	m_hModule;		//!< 程序模組	handle
	HWND		m_hWndParent;	//!< 父視窗	handle
	HWND		m_hWnd;			//!< 自視窗	handle
	WNDPROC		m_fnOldWndProc;	//!< 原有視窗	Callback 指標
	int			m_idItem;		//!< 控制項 ID
	
	UINT_PTR	m_idEventTimer;	//!< 計時器 ID
	HFONT		m_hFontUser;	//!< 保存建立字型 Handle
	EECTRLTYPE	m_eCtrlType;	//!< 紀錄控制項視窗 Type (見 EmCTRLS)
	DWORD		m_dwError;		//!< 保存錯誤碼 
};

#endif // !__AXEEN_WIN32FRAME_OBJECT_HH__
