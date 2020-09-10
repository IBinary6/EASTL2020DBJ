
// #include <EASTL/internal/config.h>
#include <EASTL/allocator.h>

namespace dbj {
#ifndef EASTL_USER_DEFINED_ALLOCATOR	
		#if EASTL_NAME_ENABLED
			const char* const heap::name{ EASTL_NAME_VAL(EASTL_ALLOCATOR_DEFAULT_NAME) } ;
		#endif

// this is a default implementation
// if you think it is feasible to changes it, please do

void* heap::allocate(size_t size_  , int /*flags_ = 0 */) noexcept 
{
	return calloc( 1, size_ ) ;
}
void  heap::deallocate(void* pointer_  , size_t size_ ) noexcept
{
	free( pointer_ ) ;
}
void* heap::allocate_aligned(size_t size_, size_t alignment_ , size_t /*offset*/, int /*flags = 0 */ ) noexcept
{
	return calloc( 1, size_ ) ;
}
void  heap::deallocate_aligned(void* pointer_ , size_t /*size_*/ ) noexcept
{
	free( pointer_ ) ;
}

#endif  // EASTL_USER_DEFINED_ALLOCATOR	
}// dbj