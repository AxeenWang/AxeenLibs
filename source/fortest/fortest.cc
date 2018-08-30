/**************************************************************************//**
 * @file	fortest.cc
 * @brief	ForTest process entry
 * @date	2018-08-30
 * @date	2018-08-30
 * @author	Swang
 *****************************************************************************/
#include "include/fortest_define.hh"

#define CONSOLE_ENTER	std::wcout << std::endl
#define CONSOLE_PAUSE	::system("pause")

class foo
{
	friend foo& GetFoo();
	friend foo* GetFooPointer();

public:
	foo() { this->SetnGetThis(this); }
	virtual ~foo() { this->SetnGetThis(reinterpret_cast<foo*>(-1)); }

	ULONG_PTR GetThisPointer() { return reinterpret_cast<ULONG_PTR>(this); }


private:

	static foo* SetnGetThis(foo* thisPtr) {
		static foo* fooPtr = NULL;

		if (reinterpret_cast<foo*>(-1) == thisPtr) {
			fooPtr = NULL;
		}
		else if (NULL == fooPtr) {
			fooPtr = thisPtr;
		}
		return fooPtr;
	}
};

foo& GetFoo() { return *foo::SetnGetThis(NULL); }

foo* GetFooPointer() { return foo::SetnGetThis(NULL); }

int main()
{
	CONSOLE_ENTER;
	std::wcout << TEXT("Hello! ForTest.exe") << std::endl << std::endl;
	CONSOLE_PAUSE;
	CONSOLE_ENTER;

	foo myFoo;

	std::wcout << L"0x" << std::hex << myFoo.GetThisPointer() << std::endl;
	std::wcout << L"0x" << std::hex << &myFoo << std::endl;
	std::wcout << L"0x" << std::hex << &GetFoo() << std::endl;
	std::wcout << L"0x" << std::hex << GetFooPointer() << std::endl;
	std::wcout << L"0x" << std::hex << GetFoo().GetThisPointer() << std::endl;
	CONSOLE_PAUSE;
	CONSOLE_ENTER;

	return 0;
}
