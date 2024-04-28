cmake_minimum_required(VERSION 3.27)
project(test_2024_4_26 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(test_2024_4_26 main.cpp test.cpp test.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
