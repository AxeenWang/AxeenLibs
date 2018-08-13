/**************************************************************************//**
 * @file	console_func.hh
 * @brief	Example1 - Console Test function member
 * @date	2018-04-20
 * @date	2018-07-25
 * @author	Swang
 *****************************************************************************/
#include "include/console_func.hh"

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
int swap(int* a, int* b)
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
int create_a_window()
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


int test_mrstream()
{
	MRSRESULT err;
	HMRSTREAM hmrs = NULL;
	TCHAR szVersion[BUFF_SIZE_128];

	for (;;) {

		err = GetMRStreamVersionText(szVersion, size_t(szVersion));
		if (err == 0) {
			std::wcout << TEXT("The MRStream dynamic library version = ") << szVersion << std::endl;
		}

		hmrs = MRStream_Carlist_Create(NULL, 0);
		if (hmrs == NULL) {
			std::wcout << TEXT("Create Catlist object fail") << std::endl;
		}
		else {
			std::wcout << TEXT("Carlist Object pointer value = 0x") << hmrs << std::endl;
		}

		if (MRStream_Carlist_GetText(hmrs, szVersion) != ERR_MRS_SUCCESS) {
			std::wcout << TEXT("Get MRStream Carlest Text fail") << std::endl;
		}
		else {
			std::wcout << TEXT("Get MRStream Carlest Text = ") << szVersion << std::endl;
		}

		MRStream_Carlist_Release(&hmrs);
		std::wcout << TEXT("Release Carlist Object pointer value = 0x") << hmrs << std::endl;
		break;
	}

	return err == 0;
}
