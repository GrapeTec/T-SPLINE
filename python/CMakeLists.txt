find_package(PythonInterp)
find_package(PythonLibs)
EXECUTE_PROCESS(COMMAND ${PYTHON_EXECUTABLE} -c 
"from distutils.sysconfig import get_python_lib; print(get_python_lib())"
OUTPUT_VARIABLE python_libs OUTPUT_STRIP_TRAILING_WHITESPACE )
include_directories( ${PYTHON_INCLUDE_DIRS})

SET(PYTHON_INSTALL_DIR ${python_libs}/tspline)

add_library(_tspline SHARED tspline_pyext.cpp)
set_target_properties(_tspline PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tspline)
set_target_properties(_tspline PROPERTIES PREFIX "")

target_link_libraries(_tspline rhino tspline newmat)

configure_file(__init__.py "../tspline/__init__.py" COPYONLY)

install(DIRECTORY "./" DESTINATION ${PYTHON_INSTALL_DIR} FILES_MATCHING PATTERN "*.py")
install(TARGETS _tspline DESTINATION ${PYTHON_INSTALL_DIR})