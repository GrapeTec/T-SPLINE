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

#include <windows.h>											// Header File For Windows
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include <gl\glaux.h>											// Header File For The GLaux Library

#include "math.h"                                               
#include "rotation.h"                                          



void ArcBall_t::_mapToSphere(const Point2fT* NewPt, Vector3fT* NewVec) const
{
	Point2fT TempPt;
	GLfloat length;

	//Copy paramter into temp point
	TempPt = *NewPt;

	//Adjust point coords and scale down to range of [-1 ... 1]
	TempPt.s.X = (TempPt.s.X * this->AdjustWidth) - 1.0f;
	TempPt.s.Y = 1.0f - (TempPt.s.Y * this->AdjustHeight);

	//Compute the square of the length of the vector to the point from the center
	length = (TempPt.s.X * TempPt.s.X) + (TempPt.s.Y * TempPt.s.Y);

	//If the point is mapped outside of the sphere... (length > radius squared)
	if (length > 1.0f)
	{
		GLfloat norm;

		//Compute a normalizing factor (radius / sqrt(length))
		norm = 1.0f / FuncSqrt(length);

		//Return the "normalized" vector, a point on the sphere
		NewVec->s.X = TempPt.s.X * norm;
		NewVec->s.Y = TempPt.s.Y * norm;
		NewVec->s.Z = 0.0f;
	}
	else    //Else it's on the inside
	{
		//Return a vector to a point mapped inside the sphere sqrt(radius squared - length)
		NewVec->s.X = TempPt.s.X;
		NewVec->s.Y = TempPt.s.Y;
		NewVec->s.Z = FuncSqrt(1.0f - length);
	}
}

//Create/Destroy
ArcBall_t::ArcBall_t(GLfloat NewWidth, GLfloat NewHeight)
{
	//Clear initial values
	this->StVec.s.X =
		this->StVec.s.Y =
		this->StVec.s.Z =

		this->EnVec.s.X =
		this->EnVec.s.Y =
		this->EnVec.s.Z = 0.0f;

	//Set initial bounds
	this->setBounds(NewWidth, NewHeight);
}

//Mouse down
void    ArcBall_t::click(const Point2fT* NewPt)
{
	//Map the point to the sphere
	this->_mapToSphere(NewPt, &this->StVec);
}

//Mouse drag, calculate rotation
void    ArcBall_t::drag(const Point2fT* NewPt, Quat4fT* NewRot)
{
	//Map the point to the sphere
	this->_mapToSphere(NewPt, &this->EnVec);

	//Return the quaternion equivalent to the rotation
	if (NewRot)
	{
		Vector3fT  Perp;

		//Compute the vector perpendicular to the begin and end vectors
		Vector3fCross(&Perp, &this->StVec, &this->EnVec);

		//Compute the length of the perpendicular vector
		if (Vector3fLength(&Perp) > Epsilon)    //if its non-zero
		{
			//We're ok, so return the perpendicular vector as the transform after all
			NewRot->s.X = Perp.s.X;
			NewRot->s.Y = Perp.s.Y;
			NewRot->s.Z = Perp.s.Z;
			//In the quaternion values, w is cosine (theta / 2), where theta is rotation angle
			NewRot->s.W = Vector3fDot(&this->StVec, &this->EnVec);
		}
		else                                    //if its zero
		{
			//The begin and end vectors coincide, so return an identity transform
			NewRot->s.X =
				NewRot->s.Y =
				NewRot->s.Z =
				NewRot->s.W = 0.0f;
		}
	}
}

//Mouse wheel ivent
void mouseWheel(int button, int dir, int x, int y)
{
	if (dir > 0)
	{
		// Zoom in
	}
	else
	{
		// Zoom out
	}

	return;
}

