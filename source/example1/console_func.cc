/**************************************************************************//**
 * @file	console_func.hh
 * @brief	Example1 - Console Test function member
 * @date	2018-04-20
 * @date	2018-07-25
 * @author	Swang
 *****************************************************************************/
#include "include/console_func.hh"

BOOL IsTrue(int a)
{
	return a != 0;
}

/**
 * @brief	兩數交換
 * @param	a	變數存放位址
 * @param	b	變數存放位址
 * @return	@c a+b 兩數總和
 * @remark	不借用第三方記憶體或 assembly push pop 等語法完成兩數交換。
 *
 *	這是我於仁寶面試新人時突發奇想的問題，當時面試著一個超高學歷的「台大台大」生。
 *	當時會想到這個題目，是因為在組合語言對這類處理是家常便飯，想看看 c 會如何辦到。\n
 *	還真沒想到當時放到網路上之後，居然在網路上得到熱烈的迴響，所以自己將此列為個人程式的經典。
 */
int test_swap(int* a, int* b)
{
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
	return *a + *b;
}


/**
 * @brief	建立一個視窗 (測試 AxeenLibs library 用)
 * @return	@c 型別: int \n
 *			視窗結束後返回的結束碼
 * @remark	為什麼要在 new 前使用 std::nothrow 語句? \n
 *			實際上使用 new 時，若配置失敗，系統會發出一個 throw, 你可用 try.... catch 去處理. \n
 *			所以要配置失敗直接返回 NULL 給自己判斷，配置是否成功，那麼就必須使用 std::nothrow 了.\n
 *			就看個人習慣哪種錯誤處理方式了。 
 * @code
 *		int Example()
 *		{
 *			Task* pmain = NULL;
 *
 *			try {
 *				pmain = new Task();	// <-- 若成功當然沒話說，返回值必定不為 NULL, 若錯誤發生將拋出一個 throw, 而不是返回 NULL 值
 *				SAFE_DELETE(pmain);
 *			}
 *			catch (...) {
 *				// 配置 CxFrameWindow 給 pmain 失敗
 *				std::cout << "except happen" << std::endl;
 *			}
 *
 *			// 換個寫法
 *			pmain = new Task();
 *			if (pmain == NULL) {	// <-- 根本不用判斷了, 因為只有配置成功程式才會跑到這 因為若配置 CxFrameWindow 失敗就跑出 Exception 了, 根本到不了這裡。
 *				// Error handling ...
 *				return -1;
 *			}
 *			SAFE_DELETE(pmain);
 *
 *			// 所以要自己判斷使用 new 配置是否成功，那麼就必須採用 std::nothrow
 *			pmain = new (std::nothrow) Task();
 *			if (pmain == NULL) {	// <-- 因為 new 失敗不出出異常了, 失敗直接返回 NULL 讓使用者自行判斷取處理了
 *				// Error handling ...
 *				return -1;
 *			}
 *			SAFE_DELETE(pmain);
 *			return 0;
 *		}
 * @endcode
 */
int test_window()
{
	auto pmain = new (std::nothrow) CxFrameWindow();
	auto err = int(-1);

	for (;;) {
		if (pmain == NULL)
			break;
		if (!pmain->CreateSample(NULL)) {
			pmain->ShowError();
			break;
		}
		err = pmain->Run();
		break;
	}
	SAFE_DELETE(pmain);
	return err;
}


/**
 * @brief	浮點轉整數
 * @return	@c int \n
 *			此函數返回值無意義
 * @remark	@c 引用 math \n
 *			floor(), ceil(), round()
 *
 *	各種浮點數轉整數方式，無條件去尾、四捨五入、向上取整、向下取整
 */
int test_integer()
{
	const float fnum1 = 2.5f;
	const float fnum2 = 2.4f;
	const float fnum3 = -2.5f;
	const float fnum4 = -2.4f;

	std::wcout << TEXT("The original float number") << std::endl;
	std::wcout << TEXT("fnum1 = ") << std::setw(8) << fnum1 << std::endl;
	std::wcout << TEXT("fnum2 = ") << std::setw(8) << fnum2 << std::endl;
	std::wcout << TEXT("fnum3 = ") << std::setw(8) << fnum3 << std::endl;
	std::wcout << TEXT("fnum4 = ") << std::setw(8) << fnum4 << std::endl;
	system("pause");

	std::wcout << TEXT("The original hinden cast") << std::endl;
	std::wcout << TEXT("fnum1 = ") << std::setw(8) << fnum1 << std::setw(4) << TEXT(" ---> ") << std::setw(4) << (int)fnum1 << std::endl;
	std::wcout << TEXT("fnum2 = ") << std::setw(8) << fnum2 << std::setw(4) << TEXT(" ---> ") << std::setw(4) << (int)fnum2 << std::endl;
	std::wcout << TEXT("fnum3 = ") << std::setw(8) << fnum3 << std::setw(4) << TEXT(" ---> ") << std::setw(4) << (int)fnum3 << std::endl;
	std::wcout << TEXT("fnum4 = ") << std::setw(8) << fnum4 << std::setw(4) << TEXT(" ---> ") << std::setw(4) << (int)fnum4 << std::endl;
	system("pause");

	std::wcout << TEXT("The original static cast") << std::endl;
	std::wcout << TEXT("fnum1 = ") << std::setw(8) << fnum1 << std::setw(4) << TEXT(" ---> ") << std::setw(4) << static_cast<int>(fnum1) << std::endl;
	std::wcout << TEXT("fnum2 = ") << std::setw(8) << fnum2 << std::setw(4) << TEXT(" ---> ") << std::setw(4) << static_cast<int>(fnum2) << std::endl;
	std::wcout << TEXT("fnum3 = ") << std::setw(8) << fnum3 << std::setw(4) << TEXT(" ---> ") << std::setw(4) << static_cast<int>(fnum3) << std::endl;
	std::wcout << TEXT("fnum4 = ") << std::setw(8) << fnum4 << std::setw(4) << TEXT(" ---> ") << std::setw(4) << static_cast<int>(fnum4) << std::endl;
	system("pause");

	std::wcout << std::endl;
	std::wcout << TEXT("The math floor function") << std::endl;
	std::wcout << TEXT("floor(fnum1) = ") << std::setw(8) << fnum1 << std::setw(4) << TEXT(" ---> ") << std::setw(4) << floor(fnum1) << std::endl;
	std::wcout << TEXT("floor(fnum2) = ") << std::setw(8) << fnum2 << std::setw(4) << TEXT(" ---> ") << std::setw(4) << floor(fnum2) << std::endl;
	std::wcout << TEXT("floor(fnum3) = ") << std::setw(8) << fnum3 << std::setw(4) << TEXT(" ---> ") << std::setw(4) << floor(fnum3) << std::endl;
	std::wcout << TEXT("floor(fnum4) = ") << std::setw(8) << fnum4 << std::setw(4) << TEXT(" ---> ") << std::setw(4) << floor(fnum4) << std::endl;
	system("pause");

	std::wcout << std::endl;
	std::wcout << TEXT("The math ceil function") << std::endl;
	std::wcout << TEXT("ceil(fnum1) = ") << std::setw(8) << fnum1 << std::setw(4) << TEXT(" ---> ") << std::setw(4) << ceil(fnum1) << std::endl;
	std::wcout << TEXT("ceil(fnum2) = ") << std::setw(8) << fnum2 << std::setw(4) << TEXT(" ---> ") << std::setw(4) << ceil(fnum2) << std::endl;
	std::wcout << TEXT("ceil(fnum3) = ") << std::setw(8) << fnum3 << std::setw(4) << TEXT(" ---> ") << std::setw(4) << ceil(fnum3) << std::endl;
	std::wcout << TEXT("ceil(fnum4) = ") << std::setw(8) << fnum4 << std::setw(4) << TEXT(" ---> ") << std::setw(4) << ceil(fnum4) << std::endl;
	system("pause");

	std::wcout << std::endl;
	std::wcout << TEXT("The math round function") << std::endl;
	std::wcout << TEXT("round(fnum1) = ") << std::setw(8) << fnum1 << std::setw(4) << TEXT(" ---> ") << std::setw(4) << round(fnum1) << std::endl;
	std::wcout << TEXT("round(fnum2) = ") << std::setw(8) << fnum2 << std::setw(4) << TEXT(" ---> ") << std::setw(4) << round(fnum2) << std::endl;
	std::wcout << TEXT("round(fnum3) = ") << std::setw(8) << fnum3 << std::setw(4) << TEXT(" ---> ") << std::setw(4) << round(fnum3) << std::endl;
	std::wcout << TEXT("round(fnum4) = ") << std::setw(8) << fnum4 << std::setw(4) << TEXT(" ---> ") << std::setw(4) << round(fnum4) << std::endl;

	return 0;
}
