cmake_minimum_required(VERSION 3.12.0)

project(fraction VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(FRACTION_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")

find_package(GTest QUIET)

include_directories(${FRACTION_INCLUDE_DIRS})

file(GLOB FRACTION_TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")

file(GLOB FRACTION_EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp")

foreach(EXAMPLE_SOURCE ${FRACTION_EXAMPLE_SOURCES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples")

    add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE})
endforeach()

enable_testing()

if(GTEST_FOUND)
    foreach(TEST_SOURCE ${FRACTION_TEST_SOURCES})
        get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)

        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests")

        add_executable(${TEST_NAME} ${TEST_SOURCE})

        target_link_libraries(${TEST_NAME} ${GTEST_BOTH_LIBRARIES})

        gtest_add_tests(TARGET ${TEST_NAME})
    endforeach()
endif()
