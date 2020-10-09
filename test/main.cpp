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
	// win_enable_vt_100_and_unicode();
	// ugly hack to enable VT100 on cmd.exe
	system(" ");
	// win_set_console_font(L"Consolas", 18);
#endif

#if EASTL_EXCEPTIONS_ENABLED
	try {
#endif // EASTL_EXCEPTIONS_ENABLED

		testing_sampling(argc, argv);

#if EASTL_EXCEPTIONS_ENABLED
	}
	catch (std::exception& x_)
	{
		fprintf(stderr, "\nstd::exception \"%s\"", x_.what());
	}
	catch (...)
	{
		fprintf(stderr, "\nUnknown exception ...?");
	}
#endif // EASTL_EXCEPTIONS_ENABLED

	#ifdef _MSC_VER
	system("@pause");
	#endif // _MSC_VER
	return 42;
}

#ifdef __cpp_deduction_guides
#include <EASTL/array.h>
// Also works with DBJ EASTL 2020
// Requires C++17 or better
static void test_eastl_deduction_guides() {
	{
		eastl::array a = { 1,2,3,4 };
		eastl::vector v = { 1,2,3,4 };

		(void(a));
		(void(v));
	}
}
#endif // __cpp_deduction_guides









