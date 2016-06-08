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

#ifndef VISITORS_H
#define VISITORS_H

#include <utils.h>
#include <tjunction.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif
	

/**  
  *  @struct  <TFaceVisitorCheckParameterInside> 
  *  @brief  A T-face visitor.   
  *  @note  
  *  A T-face visitor to check if the specified parameter is inside.
*/ 
struct TFaceVisitorCheckParameterInside
{
	TFaceVisitorCheckParameterInside(Parameter p) : _p(p) {}
	bool operator() (const TFacePtr &tface);
protected:
	bool pointInFace(const TFacePtr &face, const Parameter &parameter);
private:
	Parameter _p;
};

/**  
  *  @struct  <TLinkVisitorCheckParameterIntersection> 
  *  @brief  A T-link visitor.   
  *  @note  
  *  A T-link visitor to check if the specified parameter intersect with it.
*/ 
struct TLinkVisitorCheckParameterIntersection
{
	TLinkVisitorCheckParameterIntersection(Parameter p) : _p(p) {}

	void operator() (TLinkPtr tlink);

	/** Reset the static attributes. */
	static void reset() { _count = 0; _online = 0; }
	/** Get the static count. */
	static int getCount() { return _count; }
	/** Get the static online. */
	static int getOnline() { return _online; }
	/** Check if the count is even. */
	static bool countIsEven() { return (_count % 2) == 0; }
	/** Check if the count is odd. */
	static bool countIsOdd() { return (_count % 2) != 0; }
	/** Check if the point is on line. */
	static bool pointOnline() { return _online != 0; }
private:
	Parameter _p;
	static int _count;
	static int _online;
};

/**  
  *  @struct  <TVertexVisitorCheckParameterCoincide> 
  *  @brief  A T-vertex visitor.   
  *  @note  
  *  A T-vertex visitor to check if the specified parameter coincide with it.
*/ 
struct TVertexVisitorCheckParameterCoincide
{
	TVertexVisitorCheckParameterCoincide(const Parameter &p) : _p(p) {}
	bool operator() (const TVertexPtr &vertex);
private:
	Parameter _p;
};

/**  
  *  @struct  <TLinkVisitorCheckStartEndVertices> 
  *  @brief  A T-link visitor.   
  *  @note  
  *  A T-link visitor to check if the T-link contains the specified start and end T-vertices.
*/ 
struct TLinkVisitorCheckStartEndVertices
{
	TLinkVisitorCheckStartEndVertices(const TVertexPtr &start, const TVertexPtr &end)
		: _start(start), _end(end) {}

	bool operator() (const TLinkPtr &link);
private:
	TVertexPtr _start;
	TVertexPtr _end;
};

/**  
  *  @struct  <TVertexVisitorCheckTJunctions> 
  *  @brief  A T-vertex visitor.   
  *  @note  
  *  A T-vertex visitor to check if the T-vertex is a T-junction.
*/ 
struct TVertexVisitorCheckTJunctions
{
	TVertexVisitorCheckTJunctions() {}
	void operator() (const TVertexPtr &vertex);
private:

};

/**  
  *  @struct  <TVertexVisitorCheckTNodes> 
  *  @brief  A T-vertex visitor.   
  *  @note  
  *  A T-vertex visitor to set common neighbors.
*/ 
struct TVertexVisitorCheckTNodes
{
	TVertexVisitorCheckTNodes() {}
	void operator() (const TVertexPtr &vertex);
private:
	void setCommonNorth(TNodV4Vector &nodes, TNodeV4Ptr north);
	void setCommonWest(TNodV4Vector &nodes, TNodeV4Ptr west);
	void setCommonSouth(TNodV4Vector &nodes, TNodeV4Ptr south);
	void setCommonEast(TNodV4Vector &nodes, TNodeV4Ptr east);
};

/**  
  *  @struct  <TMapperVisitorCheckTNodes> 
  *  @brief  A T-mapper visitor.   
  *  @note  
  *  A T-mapper visitor to set common neighbors.
*/ 
struct TMapperVisitorCheckTNodes
{
public:
	TMapperVisitorCheckTNodes() {}
	void operator() (const TMappableObjectPtr &mapper);
private:
	void setCommonNorth(TNodV4Vector &nodes, TNodeV4Ptr north);
	void setCommonWest(TNodV4Vector &nodes, TNodeV4Ptr west);
	void setCommonSouth(TNodV4Vector &nodes, TNodeV4Ptr south);
	void setCommonEast(TNodV4Vector &nodes, TNodeV4Ptr east);
};

#ifdef use_namespace
}
#endif

#endif