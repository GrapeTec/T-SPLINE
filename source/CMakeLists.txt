# CMake configuration file tspline source dir
# 

project(tspline)
add_library(tspline 
			utils.cpp
			basis.cpp
			splbase.cpp
			tspline.cpp
			factory.cpp
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
			simple.cpp)
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

find_package(OpenMP)
if(OPENMP_FOUND)
option(OpenMP "Using OpenMP" ON)
message("OpenMP Found")
endif()

if(OpenMP)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
add_definitions(-DUSE_OMP)
endif()

#if(WIN32)
#add_executable(viewer WIN32 
#			viewer.cpp
#			viewer_model.cpp
#			viewer_motions.cpp)
#target_link_libraries(viewer rhino tspline newmat)
#endif(WIN32)

FILE(GLOB_RECURSE include_list "*.h")
INSTALL(FILES ${include_list} DESTINATION include)


IF(CMAKE_CL_64)
	INSTALL(TARGETS tspline rhino DESTINATION lib/x64/release CONFIGURATIONS Release)
	INSTALL(TARGETS tspline rhino DESTINATION lib/x64/debug CONFIGURATIONS Debug)
ELSE()
	INSTALL(TARGETS tspline rhino DESTINATION lib/x86/release CONFIGURATIONS Release)
	INSTALL(TARGETS tspline rhino DESTINATION lib/x86/debug CONFIGURATIONS Debug)
ENDIF()
