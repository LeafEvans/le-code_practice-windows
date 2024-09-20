# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\FlightBookingSystem_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\FlightBookingSystem_autogen.dir\\ParseCache.txt"
  "FlightBookingSystem_autogen"
  )
endif()
