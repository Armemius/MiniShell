cmake_minimum_required(VERSION 3.16)

project(MiniShell
  VERSION 1.0.0
  DESCRIPTION "A minimalistic shell implementation for Linux"
  LANGUAGES C CXX
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_EXTENSIONS OFF)
  include(CTest)

  find_package(Doxygen)
  if(Doxygen_FOUND)
    add_subdirectory(docs)
  else()
    message(STATUS "Doxygen not found, not building docs")
  endif()
endif()

include(cmake/fetch.cmake)
add_subdirectory(src)
add_subdirectory(apps)
include(cmake/install.cmake)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) AND BUILD_TESTING)
  add_subdirectory(tests)
endif()

