/*
TSPLINE -- A T-spline object oriented package in C++
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
Beihang University (Beijing University of Aeronautics and Astronautics)
D-315, New Main Building, 
Beijing, P.R. China, 100191

email: xiaowenlei@buaa.edu.cn
-------------------------------------------------------------------------------
Revision_history:

2015/04/08: Wenlei Xiao
   - xxxxx.
-------------------------------------------------------------------------------
*/

/*! 
  @file simple.cpp
  @brief A demo file.

  Demos for T-spline, etc.
*/

#include "simple2.h"

#ifdef use_namespace
using namespace TSPLINE;
#endif

std::vector<std::string>& operator<<(std::vector<std::string> &container, const std::string &value);

SimpleDemo2::SimpleDemo2()
{
	_factory = makePtr<TFactory2>();
	createSimple();
}

SimpleDemo2::~SimpleDemo2()
{

}

void SimpleDemo2::createSimple()
{
	createTVertices();
}

void SimpleDemo2::createTSpline()
{
	_factory->createTSpline("simple");
}

void SimpleDemo2::createTImage()
{
	_factory->createTImage("image");
}

void SimpleDemo2::createTConnect()
{
	_factory->createTConnect("nodes");
}

void SimpleDemo2::createTPointset()
{
	_factory->createTPointset("points");
}

void SimpleDemo2::createTVertices()
{
	_factory->createTVertex2("v0", 1.0, 0.0, 0.0); // v
	_factory->createTVertex2("v1", 1.0, 0.5, 0.0); // v
	_factory->createTVertex2("v2", 1.0, 1.0, 0.0); // v
	_factory->createTVertex2("v3", 0.5, 0.0, 0.0); // v
	_factory->createTVertex2("v4", 0.5, 0.5, 0.0); // v
	_factory->createTVertex2("v5", 0.5, 1.0, 0.0); // v
	_factory->createTVertex2("v6", 0.0, 0.0, 0.0); // v
	_factory->createTVertex2("v7", 0.0, 1.0, 0.0); // v

	_factory->createTVertex2("v8", 1.0, 0.0, 1.0); // v
	_factory->createTVertex2("v9", 1.0, 0.5, 1.0); // v
	_factory->createTVertex2("v10", 1.0, 1.0, 1.0); // v
	_factory->createTVertex2("v11", 0.5, 0.0, 1.0); // v
	_factory->createTVertex2("v12", 0.5, 0.5, 1.0); // v
	_factory->createTVertex2("v13", 0.5, 1.0, 1.0); // v
	_factory->createTVertex2("v14", 0.0, 0.0, 1.0); // v
	_factory->createTVertex2("v15", 0.0, 1.0, 1.0); // v
}
