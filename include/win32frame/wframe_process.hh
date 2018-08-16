/**************************************************************************//**
 * @file	wframe_process.hh
 * @brief	程序操作基底類別
 * @date	2002-01-15
 * @date	2018-04-02
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_WIN32FRAME_PROCESS_HH__
#define __AXEEN_WIN32FRAME_PROCESS_HH__
#include "wframe_define.hh"

/**
 * @class	CxFrameProcess
 * @brief	程序操作基底類別
 *
 * 取得於系統運行中之程序模組操作
 */
class CxFrameProcess
{
public:
	CxFrameProcess();
	virtual ~CxFrameProcess();
	DWORD	SearchProcess(LPCTSTR szModulePtr);
	HANDLE  OpenProcess(DWORD dwProcessID);

	SIZE_T	ReadMemory(LPCVOID aBasePtr, LPVOID aBuffPtr, SIZE_T uSize);
	SIZE_T	WriteMemory(LPVOID aBasePtr, LPCVOID aBuffPtr, SIZE_T uSize);
	
	HANDLE	GetProcessHandle();
	DWORD	GetProcessID();

protected:
	virtual void ClassInTheEnd();

private:
	BOOL StrCompare(LPCTSTR szDstPtr, LPCTSTR szSrcPtr, BOOL bCase);
	void StrUpper(LPTSTR szPtr);
	void StrLower(LPTSTR szPtr);

protected:
    HANDLE  m_hProcess;		//!< Handle of Process
    DWORD   m_idProcess;	//!< ProcessID
};


#endif  // !__AXEEN_WIN32FRAME_PROCESS_HH__
