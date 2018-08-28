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

	virtual BOOL Attach(HWND hWnd);
	virtual BOOL AttachDlgItem(UINT uID, HWND hWndParent);
	virtual HWND Detach();
	virtual HWND Create();
	virtual HWND CreateEx();
	virtual void Destroy();

	HWND	GetSafeHwnd() const;
	HWND	GetParent() const;
	WNDPROC	GetPrevWndProc() const;


	BOOL IsWindow() const;
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
	void MatchToClass(HWND hWnd);

protected:
	HWND	m_hWnd;
	WNDPROC	m_fnPrevWndProc;
};

#endif // !__AXEEN_DMCFRAME_WINDOW_HH__
