/*
TSPLINE -- A T-spline object oriented package in C++
Copyright (C) 2015-  Wenlei Xiao

This library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation; either version 3.0 of the
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
-------------------------------------------------------------------------------
Revision_history:

2015/04/08: Wenlei Xiao
   - Created.
-------------------------------------------------------------------------------
*/

#include <virtual.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

VirtualTNodeV4::VirtualTNodeV4(const std::string &name /*= ""*/) :
	TNodeV4(name)
{
}

VirtualTNodeV4::~VirtualTNodeV4()
{
}

VirtualTVertex::VirtualTVertex(const std::string &name /*= ""*/) :
	TVertex(name)
{
}

VirtualTVertex::~VirtualTVertex()
{
}

VirtualTEdge::VirtualTEdge( const std::string &name /*= ""*/ ) :
	TEdge(name)
{
}

VirtualTEdge::~VirtualTEdge()
{
}

VirtualTLink::VirtualTLink( const std::string &name /*= ""*/ ) :
	TLink(name)
{
}

VirtualTLink::~VirtualTLink()
{
}

VirtualTFace::VirtualTFace( const std::string &name /*= ""*/ ) :
	TFace(name), _width(0.0), _height(0.0)
{
}

VirtualTFace::~VirtualTFace()
{
}

TFacePtr VirtualTFace::getReal()
{
	return _real_face;
}
void VirtualTFace::setReal( const TFacePtr &face )
{
	_real_face = face;
}

void VirtualTFace::setSize( Real width, Real height )
{
	_width = width;
	_height = height;
}

Real VirtualTFace::width()
{
	return _width;
}

Real VirtualTFace::height()
{
	return _height;
}

void VirtualTFace::findNorthFaces( TFacVector &faces )
{
	if (_real_face) _real_face->findNorthFaces(faces);
}

void VirtualTFace::findWestFaces( TFacVector &faces )
{
	if (_real_face) _real_face->findWestFaces(faces);
}

void VirtualTFace::findSouthFaces( TFacVector &faces )
{
	if (_real_face) _real_face->findSouthFaces(faces);
}

void VirtualTFace::findEastFaces( TFacVector &faces )
{
	if (_real_face) _real_face->findEastFaces(faces);
}

#ifdef use_namespace
}
#endif