#include "AllocatedWith.hpp"


template<typename Manager>
void* AllocatedWith<Manager>::operator new(std::size_t count)
{
	return Manager::Alloc(count);
}

template<typename Manager>
void* AllocatedWith<Manager>::operator new[](std::size_t count)
{
	return Manager::Alloc(count);
}

template<typename Manager>
void AllocatedWith<Manager>::operator delete(void* ptr) noexcept
{
	Manager::Free(ptr);
}

template<typename Manager>
void AllocatedWith<Manager>::operator delete[](void* ptr) noexcept
{
	Manager::Free(ptr);
}
