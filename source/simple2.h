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
-------------------------------------------------------------------------------
Revision_history:

2015/04/08: Wenlei Xiao
- Created.
2016/04/02: Wenlei Xiao
- Doxygen comments added.
-------------------------------------------------------------------------------
*/


/**  @file  [simple]  
*  @brief  A simple T-spline example.
  *  @author  <Wenlei Xiao>  
  *  @date  <2015.04.08>  
  *  @version  <v1.0>  
  *  @note  
  *  This file gives an simple surface example described by T-spline.
*/

#ifndef SIMPLE2_H
#define SIMPLE2_H

#include "factory2.h"

#ifdef use_namespace
using namespace TSPLINE;
#endif

/**  
  *  @class  <SimpleDemo> 
  *  @brief Simple demo class
  *  @note  
  *  The SimpleDemo creates a simple surface using T-spline.
*/ 
class SimpleDemo2
{
public:
	SimpleDemo2();
	~SimpleDemo2();
public:
	/** Create the simple surface. */
	void createSimple();
protected:
	void createTSpline();
	void createTImage();
	void createTConnect();
	void createTPointset();
	void createTVertices();
	void createTEdges();
	void createTLinks();
	void createTEdgeConditions();
	void createTFaces();
	void createTNodes();
	void createTPoints();

	void patchTSpline();
	void patchTImage();
	void patchTConnect();
	void patchTPointset();
	void patchTVertices();
	void patchTEdges();
	void patchTLinks();
	void patchTEdgeConditions();
	void patchTFaces();
	void patchTNodes();
	void patchTPoints();

	void prepareTObjects();
private:
	TFactory2Ptr _factory;
};

DECLARE_SMARTPTR(SimpleDemo2);

#endif