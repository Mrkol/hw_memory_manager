#pragma once

#include "StackAllocator.hpp"
#include "IMemoryManager.hpp"


class StackAllocatorWrapper : public IMemoryManager
{
public:
	virtual void* Alloc(size_t size) override;
	virtual void Free(void* ptr) override;

private:
	StackAllocator<char, 65536> impl_;
};
