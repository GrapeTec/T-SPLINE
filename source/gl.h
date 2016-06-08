/*
T-SPLINE -- A T-spline object oriented library in C++
Copyright (C) 2015-  Wenlei Xiao

This library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation; either version 2.1 of the
License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


Report problems and direct all questions to:

Wenlei Xiao, Ph.D
School of Mechanical Engineering and Automation
Beijing University of Aeronautics and Astronautics
D-315, New Main Building,
Beijing, P.R. China, 100191

email: xiaowenlei@buaa.edu.cn


/**************************************************************
* For the "viewer" project the source code of Nehe            *
* project  "ArcBall Rotation" have been used.                 *
* Authors Name of ArcBall Rotation project: Terence J. Grant  *
***************************************************************/


/************************************************************************************************************
* Usage  instructions:                                                                                      *
* To build the Win32 project glu32.lib, glut32.lib, opengl32.lib or the similar libraries must be provided  *
* To run an executable file viewer.exe the name of the *.tsm file must be provided as an argument           *
* (location of the *.tsm file is "../rhino" folder)                                                         *
* For navigation mouse and UP DOWN buttons can be used                                                      *
*************************************************************************************************************/

#ifndef GL_FRAMEWORK__INCLUDED
#define GL_FRAMEWORK__INCLUDED

#include <windows.h>								// Header File For Windows
#include <string>

typedef struct {									// Structure For Keyboard Stuff
	BOOL keyDown [256];								// Holds TRUE / FALSE For Each Key
} Keys;												// Keys

typedef struct {									// Contains Information Vital To Applications
	HINSTANCE		hInstance;						// Application Instance
	const char*		className;						// Application ClassName
} Application;										// Application

typedef struct {									// Window Creation Info
	Application*		application;				// Application Structure
	char*				title;						// Window Title
	int					width;						// Width
	int					height;						// Height
	int					bitsPerPixel;				// Bits Per Pixel
	BOOL				isFullScreen;				// FullScreen?
} GL_WindowInit;									// GL_WindowInit

typedef struct {									// Contains Information Vital To A Window
	Keys*				keys;						// Key Structure
	HWND				hWnd;						// Window Handle
	HDC					hDC;						// Device Context
	HGLRC				hRC;						// Rendering Context
	GL_WindowInit		init;						// Window Init
	BOOL				isVisible;					// Window Visible?
	DWORD				lastTickCount;				// Tick Counter
} GL_Window;										// GL_Window

void TerminateApplication (GL_Window* window);		// Terminate The Application

void ToggleFullscreen (GL_Window* window);			// Toggle Fullscreen / Windowed Mode

// These Are The Function You Must Provide
BOOL Initialize (GL_Window* window, Keys* keys);	// Performs All Your Initialization

void Deinitialize (void);							// Performs All Your DeInitialization

void Update (DWORD milliseconds);					// Perform Motion Updates

void Draw (const std::string &filename);			// Perform All Your Scene Drawing



#endif												// GL_FRAMEWORK__INCLUDED
