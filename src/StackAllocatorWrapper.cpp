#include "StackAllocatorWrapper.hpp"


void* StackAllocatorWrapper::Alloc(size_t size)
{
	return impl_.allocate(size);
}

void StackAllocatorWrapper::Free(void* ptr)
{
	impl_.deallocate(reinterpret_cast<char*>(ptr));
}
