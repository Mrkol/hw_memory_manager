#include <iostream>
#include <list>
#include <random>
#include <chrono>
#include "MemoryManagerSwitcher.hpp"
#include "StackAllocatorWrapper.hpp"
#include "CstdlibAllocator.hpp"


using Integer = long long;

struct SwollenStruct
{
	char swollness[1337];
};

double test(const size_t swollCount)
{
	using Clock = std::chrono::high_resolution_clock;
	Clock::time_point beg = Clock::now();
	for (int i = 0; i < swollCount; ++i)
	{
		SwollenStruct* tmp = new SwollenStruct;
		++tmp->swollness[0];
		delete tmp;
	}
	Clock::time_point end = Clock::now();

	return 
		std::chrono::duration_cast<std::chrono::duration<double>>
			(end - beg).count();
}


int main()
{
	const size_t COUNT = 10000;

	std::cout << "Mallocs: ";
	std::cout << test(COUNT);
	std::cout << std::endl;

	{
		StackAllocatorWrapper all2;
		MemoryManagerSwitcher switcher(all2);
		std::cout << "Stackalloc: ";
		std::cout << test(COUNT);
		std::cout << std::endl;
	}

	std::cout << "Mallocs again: ";
	std::cout << test(COUNT);
	std::cout << std::endl;
	
	return 0;
}
