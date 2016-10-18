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
	createTEdges();
	createTLinks();
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

void SimpleDemo2::createTEdges()
{
	_factory->createTEdge2("e0");
	_factory->createTEdge2("e1");
	_factory->createTEdge2("e2");
	_factory->createTEdge2("e3");
	_factory->createTEdge2("e4");
	_factory->createTEdge2("e5");
	_factory->createTEdge2("e6");
	_factory->createTEdge2("e7");
	_factory->createTEdge2("e8");
	_factory->createTEdge2("e9");
	_factory->createTEdge2("e10");
	_factory->createTEdge2("e11");
	_factory->createTEdge2("e12");
	_factory->createTEdge2("e13");
	_factory->createTEdge2("e14");
	_factory->createTEdge2("e15");
	_factory->createTEdge2("e16");
	_factory->createTEdge2("e17");
	_factory->createTEdge2("e18");
	_factory->createTEdge2("e19");
	_factory->createTEdge2("e20");
	_factory->createTEdge2("e21");
	_factory->createTEdge2("e22");
	_factory->createTEdge2("e23");
	_factory->createTEdge2("e24");
	_factory->createTEdge2("e25");
	_factory->createTEdge2("e26");
	_factory->createTEdge2("e27");
	_factory->createTEdge2("e28");
}

void SimpleDemo2::createTLinks()
{
	_factory->createTLink2("l0");
	_factory->createTLink2("l1");
	_factory->createTLink2("l2");
	_factory->createTLink2("l3");
	_factory->createTLink2("l4");
	_factory->createTLink2("l5");
	_factory->createTLink2("l6");
	_factory->createTLink2("l7");
	_factory->createTLink2("l8");
	_factory->createTLink2("l9");
	_factory->createTLink2("l10");
	_factory->createTLink2("l11");
	_factory->createTLink2("l12");
	_factory->createTLink2("l13");
	_factory->createTLink2("l14");
	_factory->createTLink2("l15");
	_factory->createTLink2("l16");
	_factory->createTLink2("l17");
	_factory->createTLink2("l18");
	_factory->createTLink2("l19");
	_factory->createTLink2("l20");
	_factory->createTLink2("l21");
	_factory->createTLink2("l22");
	_factory->createTLink2("l23");
	_factory->createTLink2("l24");
	_factory->createTLink2("l25");
	_factory->createTLink2("l26");
	_factory->createTLink2("l27");
	_factory->createTLink2("l28");
	_factory->createTLink2("l29");
	_factory->createTLink2("l30");
	_factory->createTLink2("l31");
	_factory->createTLink2("l32");
	_factory->createTLink2("l33");
	_factory->createTLink2("l34");
	_factory->createTLink2("l35");
	_factory->createTLink2("l36");
	_factory->createTLink2("l37");
	_factory->createTLink2("l38");
	_factory->createTLink2("l39");
	_factory->createTLink2("l40");
	_factory->createTLink2("l41");
	_factory->createTLink2("l42");
	_factory->createTLink2("l43");
	_factory->createTLink2("l44");
	_factory->createTLink2("l45");
	_factory->createTLink2("l46");
	_factory->createTLink2("l47");
	_factory->createTLink2("l48");
	_factory->createTLink2("l49");
	_factory->createTLink2("l50");
	_factory->createTLink2("l51");
	_factory->createTLink2("l52");
	_factory->createTLink2("l53");
	_factory->createTLink2("l54");
	_factory->createTLink2("l55");
	_factory->createTLink2("l56");
	_factory->createTLink2("l57");
}
