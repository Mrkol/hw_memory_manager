#pragma once

#include "IMemoryManager.hpp"
#include "CstdlibAllocator.hpp"


void* operator new(std::size_t count);
void* operator new[](std::size_t count);

void operator delete(void* ptr) noexcept;
void operator delete[](void* ptr) noexcept;

class MemoryManagerSwitcher final
{
	friend void* operator new (std::size_t count);
	friend void operator delete(void* ptr) noexcept;
public:
	explicit MemoryManagerSwitcher(IMemoryManager& managed);
	MemoryManagerSwitcher(const MemoryManagerSwitcher&) = delete;
	MemoryManagerSwitcher& operator=(const MemoryManagerSwitcher&) = delete;

	~MemoryManagerSwitcher() noexcept;

#ifndef TESTING
private:
#endif

	IMemoryManager& managed_;
	MemoryManagerSwitcher* previous_;

	static MemoryManagerSwitcher* STACK_TOP;
	static constexpr std::size_t SHIFT =
		((sizeof(MemoryManagerSwitcher*) - 1)/sizeof(std::max_align_t) + 1)
			* sizeof(std::max_align_t);
};
