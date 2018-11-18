#include "gtest/gtest.h"

#define TESTING
#include "MemoryManagerSwitcher.hpp"
#include "DefaultAllocator.hpp"
#include "CstdlibAllocator.hpp"
#include "StackAllocatorWrapper.hpp"

struct SwollenStruct
{
	char swollness[1337];
};

template<typename T>
void TestAllocatedOn()
{
	SwollenStruct* swoll;
	ASSERT_NO_THROW(swoll = new SwollenStruct);

	char* swoll_raw = reinterpret_cast<char*>(swoll);
	swoll_raw -= MemoryManagerSwitcher::SHIFT;

	MemoryManagerSwitcher* current = *reinterpret_cast<MemoryManagerSwitcher**>(swoll_raw);
	ASSERT_NO_THROW(auto& tmp = dynamic_cast<T&>(current->managed_));

	ASSERT_NO_THROW(delete swoll);
}

TEST(MemoryManagerUnitTests, BasicSwitchingTest)
{
	// TestAllocatedOn<CstdlibAllocator>();

	{
		StackAllocatorWrapper manager2;
		MemoryManagerSwitcher switcher2(manager2);

		TestAllocatedOn<StackAllocatorWrapper>();
		{
			CstdlibAllocator manager1;
			MemoryManagerSwitcher switcher1(manager1);

			TestAllocatedOn<CstdlibAllocator>();		
		}
		TestAllocatedOn<StackAllocatorWrapper>();
	}

	// TestAllocatedOn<CstdlibAllocator>();
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
