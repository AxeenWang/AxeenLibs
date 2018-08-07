
#include "win32frame/wframe.hh"

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



int _tmain(int argc, TCHAR* argv[])
{
	auto res = int(-1);

	std::wcout << res << TEXT("\n");
	system("pause");

	res = create_a_window();
	std::wcout << res << TEXT("\n");
	system("pause");
	return 0;
}


