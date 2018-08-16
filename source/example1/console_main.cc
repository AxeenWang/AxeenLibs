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

	res = create_a_window();
	std::wcout << TEXT("Exit Code = ") << res << std::endl;
	system("pause");
	return res;
}


