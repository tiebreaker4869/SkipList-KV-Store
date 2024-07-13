cmake_minimum_required(VERSION 3.22.1)

project(SkipListKV)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    include 
    src/include
)

# 查找 clang-format
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    file(GLOB_RECURSE ALL_CXX_SOURCE_FILES
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/*.hpp"
        "${CMAKE_SOURCE_DIR}/include/*.hpp"
        "${CMAKE_SOURCE_DIR}/tests/*.cpp"
    )
    add_custom_target(format
        COMMAND ${CLANG_FORMAT} -i ${ALL_CXX_SOURCE_FILES}
        COMMENT "Running clang-format on source files"
    )
endif()

# 查找 Boost 库
find_package(Boost REQUIRED COMPONENTS system filesystem)

# 包含 Boost 头文件目录
include_directories(${Boost_INCLUDE_DIRS})

# 包含 Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# 添加测试文件
add_executable(all_tests tests/skiplist_test.cpp)

# 链接 Google Test 库
target_link_libraries(all_tests GTest::GTest GTest::Main)