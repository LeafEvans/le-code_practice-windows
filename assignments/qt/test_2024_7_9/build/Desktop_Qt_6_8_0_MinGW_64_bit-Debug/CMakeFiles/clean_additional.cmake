# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\test_2024_7_9_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\test_2024_7_9_autogen.dir\\ParseCache.txt"
  "test_2024_7_9_autogen"
  )
endif()
