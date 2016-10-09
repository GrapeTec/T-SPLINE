1. Download and install GLC library from:
http://www.glc-lib.net/?q=node/5
for VisualStudio on Windows, you can use QT addin to open the 'glc_lib.pro' and compile the library in the VisualStudio.
2. Create the library folders for TSPLINE and GLC_lib. For TSPLINE, you can use 'install' project to install the INCLUDE and LIBRARY files to you computer; for GLC_lib, you need to create the cooresponding folders in your computer using the structure like this:
--GLC
  |_include
  |_lib
    |_x86
	  |_debug
	  |_release
	|_x64
	  |_debug
	  |_release
3. Set the ENVIRONMENT. you need to set the environment named 'TSPLINE' and 'GLC' using the cooresponding installed path in you computer.
4. Generate the VisualStudio project. In the TSplineViewer directory, using 'qmake -tp vc' to generate the TSplineViewer VisualStudio project.