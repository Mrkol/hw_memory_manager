#pragma once

#include <cstddef>

template<typename Manager>
class AllocatedWith
{
	void* operator new(std::size_t count);
	void* operator new[](std::size_t count);
	void operator delete(void* ptr) noexcept;
	void operator delete[](void* ptr) noexcept;
};

#include "AllocatedWith.hpp"
