#pragma once

#include "IMemoryManager.hpp"


class DefaultAllocator : public IMemoryManager
{
public:
	virtual void* Alloc(size_t size) override;
	virtual void Free(void* ptr) override;
};
