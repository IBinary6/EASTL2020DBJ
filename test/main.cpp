///////////////////////////////////////////////////////////////////////////////
// Copyright (c) Electronic Arts Inc. All rights reserved.
///////////////////////////////////////////////////////////////////////////////

#include <EASTL/string.h>
#include <EASTL/array.h>
#include <EASTL/vector.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

///////////////////////////////////////////////////////////////////////////////


#ifndef EASTL_USER_DEFINED_ALLOCATOR
// 
// CAUTION! see allocator_eastl.cpp 
//          
void* __cdecl operator new[](size_t size, char const*, int, unsigned int, char const*, int)
{
	return calloc(size, sizeof(char));
}

// this is aligned allocation
// vector et. all do require this
// string does not
void* __cdecl operator new[](size_t size , size_t alignment , unsigned __int64, char const*, int, unsigned int, char const*, int)
{
	return _aligned_malloc(size, alignment);
	// return calloc(size, sizeof(char));
}
#endif // ! EASTL_USER_DEFINED_ALLOCATOR

///////////////////////////////////////////////////////////////////////////////
// Required by EASTL.
//
#if 0
	int Vsnprintf8(char* pDestination, size_t n, const char*  pFormat, va_list arguments)
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
		int Vsnprintf8(char8_t* pDestination, size_t n, const char8_t*  pFormat, va_list arguments)
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

///////////////////////////////////////////////////////////////////////////////
// EAMain
//
int main(int argc, char* argv[])
{
	using namespace eastl;

	// this requires C++17 or better
#ifdef __cpp_deduction_guides
	array a = {1,2,3,4};

	vector v = {1,2,3,4};
#endif

	string hello("Hello World!");

	printf("%s", hello.data() );

	return 42 ;
}








