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

#include <windows.h>												// Header File For Windows
#include <gl\gl.h>													// Header File For The OpenGL32 Library
#include <gl\glu.h>													// Header File For The GLu32 Library
#include <gl\glaux.h>												// Header File For The GLaux Library
#include "gl.h"													    // Header File For GL

#include "tspline.h"
#include "tessellator.h"
#include "trimesh.h"
#include "rhbuilder.h"
#include "math.h"												   
#include "rotation.h"

#ifndef CDS_FULLSCREEN												// CDS_FULLSCREEN Is Not Defined By Some
#define CDS_FULLSCREEN 4											
#endif		



GL_Window*	g_window;
Keys*		g_keys;

// User Defined Variables
GLUquadricObj *quadratic;											// Used For Our Quadric

Matrix4fT   Transform = { 1.0f,  0.0f,  0.0f,  0.0f,				// NEW: Final Transform
0.0f,  1.0f,  0.0f,  0.0f,
0.0f,  0.0f,  1.0f,  0.0f,
0.0f,  0.0f,  0.0f,  1.0f };

Matrix3fT   LastRot = { 1.0f,  0.0f,  0.0f,					        // NEW: Last Rotation
0.0f,  1.0f,  0.0f,
0.0f,  0.0f,  1.0f };

Matrix3fT   ThisRot = { 1.0f,  0.0f,  0.0f,					        // NEW: This Rotation
0.0f,  1.0f,  0.0f,
0.0f,  0.0f,  1.0f };

ArcBallT    ArcBall(640.0f, 480.0f);				                // NEW: ArcBall Instance
Point2fT    MousePt;												// NEW: Current Mouse Point
bool        isClicked = false;										// NEW: Clicking The Mouse?
bool        isRClicked = false;										// NEW: Clicking The Right Mouse Button?
bool        isDragging = false;					                    // NEW: Dragging The Mouse?


bool drawChanged = true;
GLuint drawIndex;
GLfloat drawScale = 1.0;

BOOL Initialize(GL_Window* window, Keys* keys)						// Any GL Init Code & User Initialiazation Goes Here
{
	g_window = window;
	g_keys = keys;

	// Start Of User Initialization
	isClicked = false;								                // NEW: Clicking The Mouse?
	isDragging = false;							                    // NEW: Dragging The Mouse?
	 
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);						    // Black Background
	glClearDepth(1.0f);											    // Depth Buffer Setup
	glDepthFunc(GL_LEQUAL);										    // The Type Of Depth Testing (Less Or Equal)
	glEnable(GL_DEPTH_TEST);									    // Enable Depth Testing
	glShadeModel(GL_FLAT);									        // Select Flat Shading (Nice Definition Of Objects)
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			    // Set Perspective Calculations To Most Accurate

	quadratic = gluNewQuadric();								    // Create A Pointer To The Quadric Object
	gluQuadricNormals(quadratic, GLU_SMOOTH);						// Create Smooth Normals
	gluQuadricTexture(quadratic, GL_TRUE);							// Create Texture Coords

	glEnable(GL_LIGHT0);											// Enable Default Light
	glEnable(GL_LIGHTING);											// Enable Lighting

	glEnable(GL_COLOR_MATERIAL);									// Enable Color Material

	return TRUE;													// Return TRUE (Initialization Successful)
}

void Deinitialize(void)											   
{
	gluDeleteQuadric(quadratic);
}

void Update(DWORD milliseconds)									   // Perform Motion Updates Here
{
	if (g_keys->keyDown[VK_ESCAPE] == TRUE)						   // Is ESC Being Pressed?
		TerminateApplication(g_window);							   // Terminate The Program
	   

	if (g_keys->keyDown[VK_F1] == TRUE)							   // Is F1 Being Pressed?
		ToggleFullscreen(g_window);								   // Toggle Fullscreen Mode

	if (isRClicked)													// If Right Mouse Clicked, Reset All Rotations
	{
		Matrix3fSetIdentity(&LastRot);								// Reset Rotation
		Matrix3fSetIdentity(&ThisRot);								// Reset Rotation
		Matrix4fSetRotationFromMatrix3f(&Transform, &ThisRot);		// Reset Rotation
	}

	if (g_keys->keyDown[VK_UP] == TRUE)						        // Is UP Being Pressed?
		drawScale *= 1.01;
	if (g_keys->keyDown[VK_DOWN] == TRUE)						    // Is DOWN Being Pressed?
		drawScale /= 1.01;

	if (!isDragging)												// Not Dragging
	{
		if (isClicked)												// First Click
		{
			isDragging = true;										// Prepare For Dragging
			LastRot = ThisRot;										// Set Last Static Rotation To Last Dynamic One
			ArcBall.click(&MousePt);								// Update Start Vector And Prepare For Dragging
		}
	}
	else
	{
		if (isClicked)												// Still Clicked, So Still Dragging
		{
			Quat4fT     ThisQuat;

			ArcBall.drag(&MousePt, &ThisQuat);						// Update End Vector And Get Rotation As Quaternion
			Matrix3fSetRotationFromQuat4f(&ThisRot, &ThisQuat);		// Convert Quaternion Into Matrix3fT
			Matrix3fMulMatrix3f(&ThisRot, &LastRot);				// Accumulate Last Rotation Into This One
			Matrix4fSetRotationFromMatrix3f(&Transform, &ThisRot);	// Set Our Final Transform's Rotation From This One
		}
		else // No Longer Dragging
			isDragging = false;
	}
}



#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

void renderTspline(const std::string &filename)
{
	if(drawChanged)
	{
		RhBuilderPtr reader = makePtr<RhBuilder>(filename);
		TSplinePtr spline = reader->findTSpline();
		TTessellator tessellator(spline);
		TriMeshPtr trimeshes = tessellator.interpolateAll();

		TriMeshPtr trimesh = makePtr<TriMesh>(spline->getName());
	
		drawIndex = glGenLists(1);
		glNewList(drawIndex, GL_COMPILE);
	

		glBegin(GL_TRIANGLES);									

		TriVIterator titer = trimesh->triangleIteratorBegin();
		for (; titer !=  trimesh->triangleIteratorEnd() ; titer++)
		{
			TrianglePtr triangle = *titer;

			P3dVIterator pbegin = trimesh->pointIteratorBegin();
			P3dVIterator piter1 = pbegin + triangle->point_indices[0];
			P3dVIterator piter2 = pbegin + triangle->point_indices[1];
			P3dVIterator piter3 = pbegin + triangle->point_indices[2];
			Point3DPtr p1 = *piter1;
			Point3DPtr p2 = *piter2;
			Point3DPtr p3 = *piter3;

			N3dVIterator nbegin = trimesh->normalIteratorBegin();
			N3dVIterator niter1 = nbegin + triangle->normal_indices[0];
			N3dVIterator niter2 = nbegin + triangle->normal_indices[1];
			N3dVIterator niter3 = nbegin + triangle->normal_indices[2];
			Vector3DPtr n1 = *niter1;
			Vector3DPtr n2 = *niter2;
			Vector3DPtr n3 = *niter3;

			glNormal3f(n1->i(), n1->j(), n1->k());
			glVertex3f(p1->x(), p1->y(), p1->z());

			glNormal3f(n2->i(), n2->j(), n2->k());
			glVertex3f(p2->x(), p2->y(), p2->z());

			glNormal3f(n3->i(), n3->j(), n3->k());
			glVertex3f(p3->x(), p3->y(), p3->z());
		}

		glEnd();
		glEndList();
		drawChanged = false;
	}
	
	glCallList(drawIndex);
}

#ifdef use_namespace
}// namespace TSPLINE
#endif

void Draw(const std::string &filename)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				
	glLoadIdentity();												
	glTranslatef(0.0f, 0.0f, -6.0f);									

	glPushMatrix();													// NEW: Prepare Dynamic Transform
	glMultMatrixf(Transform.M);										// NEW: Apply Dynamic Transform
	glColor3f(0.5f, 0.5f, 1.0f);
	glScalef(drawScale, drawScale, drawScale);
	
	renderTspline(filename);
	glPopMatrix();														
	glFlush();														// Flush The GL Rendering Pipeline
}
