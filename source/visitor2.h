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

/**  @file  [visitor]  
*  @brief  T-object visitors.
  *  @author  <Wenlei Xiao>  
  *  @date  <2015.04.08>  
  *  @version  <v1.0>  
  *  @note  
  *  This file contains the visitors which help traverse T-objects.
*/

#ifndef VISITORS2_H
#define VISITORS2_H

#include <utils.h>
#include <visitor.h>
#include <tspline2.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

struct TVertexVisitorCheckTNodes2
{
	TVertexVisitorCheckTNodes2(){}
	void operator()(const TVertex2Ptr &vertex);
private:
	void setCommonNorth(TNodV6Vector &nodes, TNodeV6Ptr north);
	void setCommonWest(TNodV6Vector &nodes, TNodeV6Ptr west);
	void setCommonSouth(TNodV6Vector &nodes, TNodeV6Ptr south);
	void setCommonEast(TNodV6Vector &nodes, TNodeV6Ptr east);
	void setCommonUp(TNodV6Vector &nodes, TNodeV6Ptr up);
	void setCommonDown(TNodV6Vector &nodes, TNodeV6Ptr down);
};

#ifdef use_namespace
}
#endif

#endif