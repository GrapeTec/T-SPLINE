# CMake configuration file spline root dir
#

cmake_minimum_required(VERSION 2.6)
# fixed

project(tspline)
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
if(UNIX)
  add_definitions(-std=c++11)
  if(NOT APPLE)
  
  endif(NOT APPLE)
endif(UNIX)
if(WIN32)
  if(NOT UNIX)
    if(NOT MINGW)
      add_definitions(-D_STANDARD_)
    endif(NOT MINGW)
  endif(NOT UNIX)
endif(WIN32)
subdirs(source newmat)
include_directories(source newmat)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})

FIND_PACKAGE(HTMLHelp)
FIND_PACKAGE(Doxygen)
OPTION(BUILD_DOCUMENTATION "Create and install the HTML based API documentation for tspline kernel (requires Doxygen)" ${DOXYGEN_FOUND})

IF(BUILD_DOCUMENTATION)
	IF(NOT DOXYGEN_FOUND)
		MESSAGE(FATAL_ERROR "Doxygen is needed to build the documentation.")
	ENDIF()
ENDIF()

SET(DOXYFILE_IN ${CMAKE_SOURCE_DIR}/doxy/Doxyfile.in)
SET(DOXYFILE ${CMAKE_SOURCE_DIR}/doxy/Doxyfile)
CONFIGURE_FILE(${DOXYFILE_IN} ${DOXYFILE} @ONLY)
ADD_CUSTOM_TARGET(doc COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE} WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/doxy COMMENT "Generating API documentation for tspline kernel." VERBATIM)
