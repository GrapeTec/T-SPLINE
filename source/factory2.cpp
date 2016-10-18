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

#include <factory2.h>
#include <visitor.h>
#include <extractor.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

TFactory2::TFactory2()
{

}

TFactory2::~TFactory2()
{

}

TImage2Ptr TFactory2::createTImage2( const std::string &name )
{
	return createTObject<TImage2>(name);
}

TVertex2Ptr TFactory2::createTVertex2( const std::string &name, Real r, Real s, Real t )
{
	TVertex2Ptr obj = createTObject<TVertex2>(name);
	obj->setRST(r, s, t);
	return obj;
}

TEdge2Ptr TFactory2::createTEdge2( const std::string &name )
{
	return createTObject<TEdge2>(name);
}

TLink2Ptr TFactory2::createTLink2( const std::string &name )
{
	return createTObject<TLink2>(name);
}

TFace2Ptr TFactory2::createTFace2( const std::string &name )
{
	return createTObject<TFace2>(name);
}

TNodeV6Ptr TFactory2::createTNodeV6( const std::string &name )
{
	return createTObject<TNodeV6>(name);
}

#ifdef use_namespace
}
#endif