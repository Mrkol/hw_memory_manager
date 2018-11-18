#include "DefaultAllocator.hpp"
#include <cstdlib>


void* DefaultAllocator::Alloc(size_t size)
{
	return ::operator new(size);
}

void DefaultAllocator::Free(void* ptr)
{
	::operator delete(ptr);
}
