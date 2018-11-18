cmake_minimum_required(VERSION 3.5)

project(allocators CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

enable_testing()

set(SOURCES
	src/CstdlibAllocator.cpp
	src/DefaultAllocator.cpp
	src/MemoryManagerSwitcher.cpp
	src/StackAllocatorWrapper.cpp
	)

add_executable(memory_manager_unit_tests
	src/memory_manager_unit_tests.cpp
	${SOURCES}
	)

target_include_directories(memory_manager_unit_tests PUBLIC "./include")

target_link_libraries(memory_manager_unit_tests 
	PUBLIC GTest::GTest)

add_test(memory_manager_tests memory_manager_unit_tests)



add_executable(memory_manager_speed_test
	src/memory_manager_speed_tests.cpp
	${SOURCES}
	)

target_include_directories(memory_manager_speed_test PUBLIC "./include")
