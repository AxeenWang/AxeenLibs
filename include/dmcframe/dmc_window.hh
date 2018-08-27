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

	BOOL Attach(HWND hWnd);
	HWND Detach();
	BOOL IsWindow();


	// inline function
	HWND GetSafeHandle() const { return m_hWnd; }
	operator HWND() const { return GetSafeHandle(); }

protected:
	virtual LRESULT WndProc(UINT uMessage, WPARAM wParam, LPARAM lParam);


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
