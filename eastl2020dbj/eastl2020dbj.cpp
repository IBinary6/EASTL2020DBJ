// eastl2020dbj.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"

// D :\DEVL\vcpkg\installed\x86 - windows\include \EASTL\internal
#include <EASTL/internal/config.h>


extern "C" {
const char * const EASTL2020DBJ ( void ) 
{ 
	static char buf_[0xFF] = {0};

	if ( buf_[0] == '\0' ) 
	_snprintf_s(buf_, 0xFF, 0xFF, "%s %d", DBJ_EASTL_VERSION,
                    DBJ_EASTL_VERSION_N);

	return buf_;
}
}
