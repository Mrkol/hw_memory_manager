#pragma once

#include <cstddef>


class IMemoryManager
{
public:
	virtual void* Alloc(size_t size) = 0;
	virtual void Free(void* ptr) = 0;
};
