#include "CstdlibAllocator.hpp"
#include <cstdlib>


void* CstdlibAllocator::Alloc(size_t size)
{
	return std::malloc(size);
}

void CstdlibAllocator::Free(void* ptr)
{
	std::free(ptr);
}
