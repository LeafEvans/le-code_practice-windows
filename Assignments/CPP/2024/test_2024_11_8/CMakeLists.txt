cmake_minimum_required(VERSION 3.28.0)
project(test_2024_11_8 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(fmt REQUIRED)

add_executable(test_2024_11_8 main.cpp test.cpp)

target_link_libraries(test_2024_11_8 PRIVATE fmt::fmt)

include(CTest)
enable_testing()

add_test(NAME SimpleTest COMMAND test_2024_11_8)

# 配置 CPack 打包信息
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
