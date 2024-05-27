# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Manager_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Manager_autogen.dir\\ParseCache.txt"
  "Manager_autogen"
  )
endif()
