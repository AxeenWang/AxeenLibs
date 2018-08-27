/**************************************************************************//**
 * @file	console_main.hh
 * @brief	Example1 - 程式進入口
 * @date	2018-04-20
 * @date	2018-07-25
 * @author	Swang
 *
 *	This program for test new function or class.
 *****************************************************************************/
#include "include/console_func.hh"

int _tmain(int argc, TCHAR* argv[])
{
	auto res = int(-1);

	// nothing! just do not see conpile warning.
	if (argc > 1) {
		std::wcout << argv[1] << std::endl;
	}

	// create a sample window
	//res = test_window();
	//std::wcout << TEXT("Exit Code = ") << res << std::endl;

	test_integer();

	system("pause");
	return res;
}
