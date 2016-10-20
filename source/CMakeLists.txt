# CMake configuration file tspline source dir
# 

project(tspline)
add_library(tspline 
			utils.cpp
			basis.cpp
			basis2.cpp
			splbase.cpp
			tspline.cpp
			tspline2.cpp
			factory.cpp
			factory2.cpp
			virtual.cpp
			tjunction.cpp
			multiplicity.cpp
			visitor.cpp
			finder.cpp
			extractor.cpp
			editor.cpp
			derivator.cpp
			cross.cpp
			trimesh.cpp
			tessellator.cpp
			writer.cpp
			validator.cpp)
add_library(rhino 
			rhparser.cpp
			rhbuilder.cpp
			rhspreader.cpp)
add_executable(demo 
			demo.cpp 
			mouse.cpp 
			simple.cpp
			simple2.cpp)
target_link_libraries(demo rhino tspline newmat)
add_executable(tsm2stl 
			tsm2stl.cpp)
target_link_libraries(tsm2stl rhino tspline newmat)
add_executable(tsm2obj 
			tsm2obj.cpp)
target_link_libraries(tsm2obj rhino tspline newmat)
add_executable(tsm2dxf 
			tsm2dxf.cpp)
target_link_libraries(tsm2dxf rhino tspline newmat)
add_executable(tsm2gpl 
			tsm2gpl.cpp)
target_link_libraries(tsm2gpl rhino tspline newmat)
add_executable(tsm2stp 
			tsm2stp.cpp)
target_link_libraries(tsm2stp rhino tspline newmat)

option(MATRIX_FORM "Using matrix form for the calculation of basis function" ON)
if(MATRIX_FORM)
add_definitions(-DMATRIX_FORM)
endif()


FILE(GLOB_RECURSE include_list "*.h")
INSTALL(FILES ${include_list} DESTINATION include)


IF(CMAKE_CL_64)
	INSTALL(TARGETS tspline rhino DESTINATION lib/x64/release CONFIGURATIONS Release)
	INSTALL(TARGETS tspline rhino DESTINATION lib/x64/debug CONFIGURATIONS Debug)
ELSE()
	INSTALL(TARGETS tspline rhino DESTINATION lib/x86/release CONFIGURATIONS Release)
	INSTALL(TARGETS tspline rhino DESTINATION lib/x86/debug CONFIGURATIONS Debug)
ENDIF()
