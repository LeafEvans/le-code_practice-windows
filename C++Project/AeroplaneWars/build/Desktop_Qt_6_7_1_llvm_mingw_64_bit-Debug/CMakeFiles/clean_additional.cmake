# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "AeroplaneWars_autogen"
  "CMakeFiles\\AeroplaneWars_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\AeroplaneWars_autogen.dir\\ParseCache.txt"
  )
endif()
