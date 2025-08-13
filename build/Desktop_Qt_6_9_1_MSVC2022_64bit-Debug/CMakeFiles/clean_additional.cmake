# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\imageResize_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\imageResize_autogen.dir\\ParseCache.txt"
  "imageResize_autogen"
  )
endif()
