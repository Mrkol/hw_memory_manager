#pragma once

#include "IMemoryManager.hpp"
#include "StdAllocator.hpp"
#include "StackAllocator.hpp"

template<typename T>
class MemoryManagerStrategy
{
public:
	static void* Alloc(size_t size);
	static void Free(void* ptr);

private:
	static T manager;
};

using StdAllocatorStrategy = MemoryManagerStrategy<StdAllocator>;
using StackAllocatorStrategy = MemoryManagerStrategy<StackAllocator>;

#include "MemoryManagerStrategy.tpp"
