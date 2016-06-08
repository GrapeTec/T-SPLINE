# CMake configuration file roboop newmat dir
# 

project(newmat)
add_library(newmat
  bandmat.cpp
  cholesky.cpp
  evalue.cpp
  fft.cpp
  hholder.cpp
  jacobi.cpp
  myexcept.cpp
  newmat1.cpp
  newmat2.cpp
  newmat3.cpp
  newmat4.cpp
  newmat5.cpp
  newmat6.cpp
  newmat7.cpp
  newmat8.cpp
  newmat9.cpp
  newmatex.cpp
  newmatnl.cpp
  newmatrm.cpp
  solution.cpp
  sort.cpp
  submat.cpp
  svd.cpp
  newfft.cpp
  nm_misc.cpp)

FILE(GLOB_RECURSE include_list "*.h")
INSTALL(FILES ${include_list} DESTINATION include)

IF(CMAKE_CL_64)
	INSTALL(TARGETS newmat DESTINATION lib/x64/release CONFIGURATIONS Release)
	INSTALL(TARGETS newmat DESTINATION lib/x64/debug CONFIGURATIONS Debug)
ELSE()
	INSTALL(TARGETS newmat DESTINATION lib/x86/release CONFIGURATIONS Release)
	INSTALL(TARGETS newmat DESTINATION lib/x86/debug CONFIGURATIONS Debug)
ENDIF()