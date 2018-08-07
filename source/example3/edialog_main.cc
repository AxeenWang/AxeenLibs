/**************************************************************************//**
 * @file	edialog_main.cc
 * @brief	Example3 - Dialog 程序進入口
 * @date	2010-12-05
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#include "include/edialog_frame.hh"

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, LPTSTR tCmdPtr, int iCmdShow)
{
	auto frmObj = new (std::nothrow) CxExamaleDialog();
	auto exitCode = 0;

	for (;;) {
		if (frmObj == NULL) {
			// Error handling
			break;
		}

		frmObj->CreateDialog(NULL, IDD_MAINFRAME, TRUE);
		break;
	}

	SAFE_DELETE(frmObj);
	return exitCode;
}


