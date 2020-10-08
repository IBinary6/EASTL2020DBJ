/* (c) 2019-2020 by dbj.org   -- LICENSE DBJ -- https://dbj.org/license_dbj/ */

#if 0
int Vsnprintf8(char* pDestination, size_t n, const char* pFormat, va_list arguments)
{
	return EA::StdC::Vsnprintf(pDestination, n, pFormat, arguments);
}

int Vsnprintf16(char16_t* pDestination, size_t n, const char16_t* pFormat, va_list arguments)
{
	return EA::StdC::Vsnprintf(pDestination, n, pFormat, arguments);
}

int Vsnprintf32(char32_t* pDestination, size_t n, const char32_t* pFormat, va_list arguments)
{
	return EA::StdC::Vsnprintf(pDestination, n, pFormat, arguments);
}

#if defined(EA_CHAR8_UNIQUE) && EA_CHAR8_UNIQUE
int Vsnprintf8(char8_t* pDestination, size_t n, const char8_t* pFormat, va_list arguments)
{
	return EA::StdC::Vsnprintf(pDestination, n, pFormat, arguments);
}
#endif

#if defined(EA_WCHAR_UNIQUE) && EA_WCHAR_UNIQUE
int VsnprintfW(wchar_t* pDestination, size_t n, const wchar_t* pFormat, va_list arguments)
{
	return EA::StdC::Vsnprintf(pDestination, n, pFormat, arguments);
}
#endif
#endif

//
#include "infrastructure/dbj_common.h"
//
extern "C" int testing_sampling(const int argc, char** argv);
//
int main(int argc, char* argv[])
{

#ifdef _WIN32
	win_enable_vt_100_and_unicode();
	win_set_console_font(L"Consolas", 24 );
#endif

#if EASTL_EXCEPTIONS_ENABLED
	try {
#endif // EASTL_EXCEPTIONS_ENABLED

		testing_sampling(argc, argv);

#if EASTL_EXCEPTIONS_ENABLED
	}
	catch (std::exception& x_)
	{
		printf("\nstd::exception \"%s\"", x_.what());
	}
	catch (...)
	{
		printf("\nUnknown exception ...?");
	}
#endif // EASTL_EXCEPTIONS_ENABLED

#if 0
	using namespace eastl;

	// this requires C++17 or better
#ifdef __cpp_deduction_guides
	array a = { 1,2,3,4 };

	vector v = { 1,2,3,4 };
#endif

	string hello("Hello World!");

	printf("%s", hello.data());
#endif

	#ifdef _MSC_VER
	system("@pause");
	#endif // _MSC_VER
	return 42;
}








