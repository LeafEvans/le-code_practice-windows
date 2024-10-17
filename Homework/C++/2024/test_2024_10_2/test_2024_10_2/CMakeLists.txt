
add_executable (test_2024_10_2 "main.cpp" "test.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET test_2024_10_2 PROPERTY CXX_STANDARD 20)
endif()


