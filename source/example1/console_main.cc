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

	int a = 10;
	int b = 5;
	int c;

	std::wcout << TEXT("a = ") << a << TEXT(", b = ") << b << std::endl;
	system("pause");

	c = swap(&a, &b);
	std::wcout << TEXT("a = ") << a << TEXT(", b = ") << b << std::endl;
	std::wcout << TEXT("a + b = ") << c << std::endl;

	system("pause");
	res = create_a_window();
	std::wcout << TEXT("Exit Code = ") << res << std::endl;
	system("pause");
	return 0;
}


