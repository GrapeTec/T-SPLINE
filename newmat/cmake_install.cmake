# Install script for directory: D:/Work/GrapeCore/T-SPLINE/tspline/newmat

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/tspline")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "D:/Work/GrapeCore/T-SPLINE/tspline/newmat/controlw.h"
    "D:/Work/GrapeCore/T-SPLINE/tspline/newmat/include.h"
    "D:/Work/GrapeCore/T-SPLINE/tspline/newmat/myexcept.h"
    "D:/Work/GrapeCore/T-SPLINE/tspline/newmat/newmat.h"
    "D:/Work/GrapeCore/T-SPLINE/tspline/newmat/newmatap.h"
    "D:/Work/GrapeCore/T-SPLINE/tspline/newmat/newmatio.h"
    "D:/Work/GrapeCore/T-SPLINE/tspline/newmat/newmatnl.h"
    "D:/Work/GrapeCore/T-SPLINE/tspline/newmat/newmatrc.h"
    "D:/Work/GrapeCore/T-SPLINE/tspline/newmat/newmatrm.h"
    "D:/Work/GrapeCore/T-SPLINE/tspline/newmat/precisio.h"
    "D:/Work/GrapeCore/T-SPLINE/tspline/newmat/solution.h"
    "D:/Work/GrapeCore/T-SPLINE/tspline/newmat/tmt.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/x86/release" TYPE STATIC_LIBRARY FILES "D:/Work/GrapeCore/T-SPLINE/tspline/Release/newmat.lib")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/x86/debug" TYPE STATIC_LIBRARY FILES "D:/Work/GrapeCore/T-SPLINE/tspline/Debug/newmat.lib")
  endif()
endif()

