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

#include <basis.h>

#ifdef use_namespace
namespace TSPLINE {
  using namespace NEWMAT;
#endif

ParameterSquare::ParameterSquare( const Parameter &parameter )
{
	seedParameter(parameter);
}

ParameterSquare::ParameterSquare( Real s, Real t )
{
	seedParameter(Parameter(s, t));
}

ParameterSquare::ParameterSquare( const Parameter &north_west, const Parameter &south_east )
{
	seedParameter(north_west, south_east);
}

ParameterSquare::~ParameterSquare()
{

}

void ParameterSquare::seedParameter( const Parameter &parameter )
{
	_northwest = parameter;
	_southeast = parameter;
}

void ParameterSquare::seedParameter( const Parameter &north_west, const Parameter &south_east )
{
	seedParameter(north_west);
	extendParameter(south_east);
}

void ParameterSquare::extendParameter( const Parameter &parameter )
{
	if (parameter.s() > sMax()) sMax(parameter.s());
	if (parameter.s() < sMin()) sMin(parameter.s());
	if (parameter.t() > tMax()) tMax(parameter.t());
	if (parameter.t() < tMin()) tMin(parameter.t());
}


#ifdef use_namespace
}
#endif


