# This file is part of TSplineViewer.
# 
# Copyright 2016. All rights reserved. 


TEMPLATE = app
TARGET = TSplineViewer
QT += core opengl widgets gui
CONFIG += debug_and_release
DEFINES += WIN64 QT_DLL QT_OPENGL_LIB QT_WIDGETS_LIB

exists($$(TSPLINE)){
}
else{
error("please set TSPLINE library environment")
}

exists($$(GLC)){
}
else{
error("please set GLC library environment")
}

win32 {
	INCLUDEPATH += 	$$(TSPLINE)/include \
					$$(GLC)/include
	
	!contains(QMAKE_TARGET.arch, x86_64){
		## windows 32bit
		CONFIG(debug, debug|release){
			## config debug
			message("x86 debug build")
			DESTDIR = ./win32/Debug
			LIBS += -L$$(TSPLINE)/lib/x86/debug \
					-L$$(GLC)/lib/x86/debug \
					-lopengl32 \
					-lglu32 \
					-lGLC_lib2s \
					-lnewmat \
					-lrhino \
					-ltspline
		}else{
			## config release
			message("x86 release build")
			DESTDIR = ./win32/Release
			LIBS += -L$$(TSPLINE)/lib/x86/release \
					-L$$(GLC)/lib/x86/release \
					-lopengl32 \
					-lglu32 \
					-lGLC_lib2s \
					-lnewmat \
					-lrhino \
					-ltspline
		}
	}else{
		## windows 64bit
		CONFIG(debug, debug|release){
			## config debug
			message("x64 debug build")
			DESTDIR = ./x64/Debug
			LIBS += -L$$(TSPLINE)/lib/x64/debug \
					-L$$(GLC)/lib/x64/debug \
					-lopengl32 \
					-lglu32 \
					-lGLC_lib2s \
					-lnewmat \
					-lrhino \
					-ltspline
		}else{
			## config release
			message("x64 release build")
			DESTDIR = ./x64/Release
			LIBS += -L$$(TSPLINE)/lib/x64/release \
					-L$$(GLC)/lib/x64/release \
					-lopengl32 \
					-lglu32 \
					-lGLC_lib2s \
					-lnewmat \
					-lrhino \
					-ltspline
		}
	}
	
}

macs{
	INCLUDEPATH += 	$$(TSPLINE)/include \
					$$(GLC)/include
	LIBS += -L$$(TSPLINE)/lib/x64/release \
			-L$$(GLC)/lib/x64/release \
			-llibGLC_lib.a \
			-llibnewmat.a \
			-llibrhino.a \
			-llibtspline.a				
}

INCLUDEPATH += "source"

FORMS += ui/tsplineviewer.ui

HEADERS += 	source/glwidget.h \
			source/tsplineviewer.h
		
SOURCES +=	source/glwidget.cpp \
			source/tsplineviewer.cpp \
			source/main.cpp