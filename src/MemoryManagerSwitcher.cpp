#include "MemoryManagerSwitcher.hpp"
#include <cstdlib>

void* operator new(std::size_t count)
{
	void* result;
	if (MemoryManagerSwitcher::STACK_TOP == nullptr)
	{
		result = std::malloc(MemoryManagerSwitcher::SHIFT + count);
	}
	else
	{
		result = MemoryManagerSwitcher::STACK_TOP->managed_.Alloc(
				MemoryManagerSwitcher::SHIFT + count);
	}
	*reinterpret_cast<MemoryManagerSwitcher**>(result) = MemoryManagerSwitcher::STACK_TOP;
	return reinterpret_cast<char*>(result) + MemoryManagerSwitcher::SHIFT;
}

void* operator new[](std::size_t count)
{
	return ::operator new(count);
}

void operator delete(void* ptr) noexcept
{
	if (ptr == nullptr) return;
	
	void* actualBegin = 
		reinterpret_cast<char*>(ptr) - MemoryManagerSwitcher::SHIFT;
	MemoryManagerSwitcher* alloc = 
		*reinterpret_cast<MemoryManagerSwitcher**>(actualBegin);
	if (alloc == nullptr)
	{
		std::free(actualBegin);
	}
	else
	{
		alloc->managed_.Free(actualBegin);
	}
}

void operator delete[](void* ptr) noexcept
{
	::operator delete(ptr);
}

MemoryManagerSwitcher* MemoryManagerSwitcher::STACK_TOP = nullptr;

MemoryManagerSwitcher::MemoryManagerSwitcher(IMemoryManager& managed)
	: managed_(managed), previous_(MemoryManagerSwitcher::STACK_TOP)
{
	MemoryManagerSwitcher::STACK_TOP = this;
}

MemoryManagerSwitcher::~MemoryManagerSwitcher() noexcept
{
	MemoryManagerSwitcher::STACK_TOP = previous_;
}
