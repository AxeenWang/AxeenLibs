/**************************************************************************//**
 * @file	axeen_undef.hh
 * @brief	Undefine windows ement macros
 * @date	2010-03-25
 * @date	2010-03-25
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_AXEENUNDEF_HH__
#define __AXEEN_AXEENUNDEF_HH__

#if defined(__WINDOWS__)

// **********************************************
#ifdef SendMessage
#undef SendMessage
inline LRESULT WINAPI SendMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	#ifdef __UNICODE__
	return ::SendMessageW(hWnd, uMsg, wParam, lParam);
	#else
	return ::SendMessageA(hWnd, uMsg, wParam, lParam);
	#endif
}
#endif

// **********************************************
#ifdef PostMessage
#undef PostMessage
inline BOOL WINAPI PostMessage(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	#ifdef __UNICODE__
	return ::PostMessageW(hWnd, Msg, wParam, lParam);
	#else
	return ::PostMessageA(hWnd, Msg, wParam, lParam);
	#endif
}
#endif

// **********************************************
#ifdef CallWindowProc
#undef CallWindowProc
inline LRESULT CallWindowProc(WNDPROC lpPrevWndFunc, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	#ifdef __UNICODE__
	return ::CallWindowProcW(lpPrevWndFunc, hWnd, uMsg, wParam, lParam);
	#else
	return ::CallWindowProcA(lpPrevWndFunc, hWnd, uMsg, wParam, lParam);
	#endif
}
#endif

// **********************************************
#ifdef DefWindowProc
#undef DefWindowProc
inline LRESULT DefWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	#ifdef __UNICODE__
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
	#else
	return ::DefWindowProcA(hWnd, uMsg, wParam, lParam);
	#endif
}
#endif

// **********************************************
#ifdef MessageBox
#undef MessageBox
inline int MessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType)
{
	#ifdef __UNICODE__
	return ::MessageBoxW(hWnd, lpText, lpCaption, uType);
	#else
	return ::MessageBoxA(hWnd, lpText, lpCaption, uType);
	#endif
}
#endif

// **********************************************
#ifdef RegisterClass
#undef RegisterClass
inline ATOM WINAPI RegisterClass(const WNDCLASS* pwc)
{
	#ifdef __UNICODE__
	return ::RegisterClassW(pwc);
	#else
	return ::RegisterClassA(pwc);
	#endif
}
#endif

// **********************************************
#ifdef RegisterClassEx
#undef RegisterClassEx
inline ATOM WINAPI RegisterClassEx(const WNDCLASSEX *pwcex)
{
	#ifdef __UNICODE__
	return ::RegisterClassExW(pwcex);
	#else
	return ::RegisterClassExA(pwcex);
	#endif
}
#endif

// **********************************************
#ifdef CreateWindow
#undef CreateWindow
inline HWND WINAPI CreateWindow(LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	#ifdef __UNICODE__
	return ::CreateWindowW(lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	#else
	return ::CreateWindowA(lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	#endif
}
#endif

// **********************************************
#ifdef CreateWindowEx
#undef CreateWindowEx
inline HWND WINAPI CreateWindowEx(DWORD dwExStyle, LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	#ifdef __UNICODE__
	return ::CreateWindowExW(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	#else
	return ::CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	#endif
}
#endif

// **********************************************
#ifdef CreateDialog
#undef CreateDialog
inline HWND CreateDialog(HINSTANCE hInstance, LPCTSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
	#ifdef __UNICODE__
	return ::CreateDialogParamW(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
	#else
	return ::CreateDialogParamA(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
	#endif
}
#endif

// **********************************************
#ifdef GetDlgItemText
#undef GetDlgItemText
inline UINT GetDlgItemText(HWND hDlg, int nIDDlgItem, LPTSTR lpString, int cchMax)
{
	#ifdef __UNICODE__
	return ::GetDlgItemTextW(hDlg, nIDDlgItem, lpString,cchMax);
	#else
	return ::GetDlgItemTextA(hDlg, nIDDlgItem, lpString, cchMax);
	#endif
}
#endif

// **********************************************
#ifdef CreateFont
#undef CreateFont
inline HFONT CreateFont(int nHeight, int nWidth, int nEscapement, int nOrientation, int fnWeight, DWORD fdwItalic, DWORD fdwUnderline, DWORD fdwStrikeOut, DWORD fdwCharSet, DWORD fdwOutputPrecision, DWORD fdwClipPrecision, DWORD fdwQuality, DWORD fdwPitchAndFamily, LPCTSTR lpszFace)
{
	#ifdef __UNICODE__
	return CreateFontW(nHeight, nWidth, nEscapement, nOrientation, fnWeight, fdwItalic, fdwUnderline, fdwStrikeOut, fdwCharSet, fdwOutputPrecision, fdwClipPrecision, fdwQuality, fdwPitchAndFamily, lpszFace);
	#else
	return CreateFontA(nHeight, nWidth, nEscapement, nOrientation, fnWeight, fdwItalic, fdwUnderline, fdwStrikeOut, fdwCharSet, fdwOutputPrecision, fdwClipPrecision, fdwQuality, fdwPitchAndFamily, lpszFace);
	#endif
	}
#endif

// **********************************************
#ifdef GetModuleHandle
#undef GetModuleHandle
inline HMODULE WINAPI GetModuleHandle(LPCTSTR lpModuleName)
{
	#ifdef __UNICODE__
	return ::GetModuleHandleW(lpModuleName);
	#else
	return ::GetModuleHandleA(lpModuleName);
	#endif
}
#endif

// **********************************************
#ifdef GetClassLong
#undef GetClassLong
inline DWORD WINAPI GetClassLong(HWND hWnd, int nIndex)
{
	#ifdef __UNICODE__
	return ::GetClassLongW(hWnd, nIndex);
	#else
	return ::GetClassLongA(hWnd, nIndex);
	#endif
}
#endif

// **********************************************
#ifdef GetClassLongPtr
#undef GetClassLongPtr
inline ULONG_PTR WINAPI GetClassLongPtr(HWND hWnd, int nIndex)
{
	#ifdef __UNICODE__
	return ::GetClassLongPtrW(hWnd, nIndex);
	#else
	return ::GetClassLongPtrA(hWnd, nIndex);
	#endif
}
#endif

// **********************************************
#ifdef GetWindowLong
#undef GetWindowLong
inline LONG GetWindowLong(HWND hWnd, int  nIndex)
{
	#ifdef __UNICODE__
	return ::GetWindowLongW(hWnd, nIndex);
	#else
	return ::GetWindowLongA(hWnd, nIndex);
	#endif
}
#endif

// **********************************************
#ifdef GetWindowLongPtr
#undef GetWindowLongPtr
inline LONG_PTR GetWindowLongPtr(HWND hWnd, int nIndex)
{
	#ifdef __UNICODE__
	return ::GetWindowLongPtrW(hWnd, nIndex);
	#else
	return ::GetWindowLongPtrA(hWnd, nIndex);
	#endif
}
#endif

// **********************************************
#ifdef SetWindowLong
#undef SetWindowLong
inline LONG SetWindowLong(HWND hWnd, int nIndex, LONG dwNewLong)
{
	#ifdef __UNICODE__
	return ::SetWindowLongW(hWnd, nIndex, dwNewLong);
	#else
	return ::SetWindowLongA(hWnd, nIndex, dwNewLong);
	#endif
}
#endif

// **********************************************
#ifdef SetWindowLongPtr
#undef SetWindowLongPtr
inline LONG_PTR SetWindowLongPtr(HWND hWnd, int nIndex, LONG_PTR dwNewLong)
{
	#ifdef __UNICODE__
	return ::SetWindowLongPtrW(hWnd, nIndex, dwNewLong);
	#else
	return ::SetWindowLongPtrA(hWnd, nIndex, dwNewLong);
	#endif
}
#endif

// **********************************************
#ifdef LoadIcon
#undef LoadIcon
inline HICON LoadIcon(HINSTANCE hInstance, LPCTSTR lpIconName)
{
	#ifdef __UNICODE__
	return ::LoadIconW(hInstance, lpIconName);
	#else
	return ::LoadIconA(hInstance, lpIconName);
	#endif
}
#endif

#ifdef GetModuleFileName
#undef GetModuleFileName
inline DWORD GetModuleFileName(HMODULE hModule, LPTSTR lpFilename, DWORD nSize)
{
	#ifdef __UNICODE__
	return ::GetModuleFileNameW(hModule, lpFilename, nSize);
	#else
	return ::GetModuleFileNameA(hModule, lpFilename, nSize);
	#endif
}
#endif




#endif	// !WINDOWS
#endif	// !__AXEEN_AXEENUNDEF_HH__
