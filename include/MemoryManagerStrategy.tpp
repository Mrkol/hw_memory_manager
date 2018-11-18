#include "MemoryManagerStrategy.hpp"


template<typename T>
void* MemoryManagerStrategy<T>::Alloc(size_t size)
{
	return MemoryManagerStrategy<T>::manager.Alloc(size);
}

template<typename T>
void MemoryManagerStrategy<T>::Free(void* ptr)
{
	MemoryManagerStrategy<T>::Free(ptr);
}

template<typename T>
T MemoryManagerStrategy<T>::manager;
