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


/**  @file  [virtual]  
*  @brief  Virtual T-objects.
  *  @author  <Wenlei Xiao>  
  *  @date  <2015.04.08>  
  *  @version  <v1.0>  
  *  @note  
  *  This file contains the virtual T-objects to facilitate the blending calculation.
*/

#ifndef VIRTUALS_H
#define VIRTUALS_H

#include <utils.h>
#include <tspline.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif
	
/**  
  *  @class  <VirtualTNodeV4> 
  *  @brief  Virtual T-node valence 4 class
  *  @note  
  *  A VirtualTNodeV4 represents a virtually created T-node valence 4.
*/ 
class VirtualTNodeV4 : public TNodeV4
{
public:
	VirtualTNodeV4(const std::string &name = "");
	virtual ~VirtualTNodeV4();
public:
	/** Check if the T-node valence 4 is virtual. */
	virtual bool isVirtual() { return true; }
protected:

private:

};
DECLARE_ASSISTANCES(VirtualTNodeV4, VTNodV4)

/**  
  *  @class  <VirtualTVertex> 
  *  @brief  Virtual T-vertex class 
  *  @note  
  *  A VirtualTVertex represents a virtually created T-vertex.
*/ 
class VirtualTVertex : public TVertex
{
public:
	VirtualTVertex(const std::string &name = "");
	virtual ~VirtualTVertex();

public:

public:
	/** Check if the T-vertex is virtual. */
	virtual bool isVirtual() { return true; }
private:

};
DECLARE_ASSISTANCES(VirtualTVertex, VTVtx)

/**  
  *  @class  <VirtualTEdge> 
  *  @brief  Virtual T-edge class 
  *  @note  
  *  A VirtualTEdge represents a virtually created T-edge.
*/ 
class VirtualTEdge : public TEdge
{
public:
	VirtualTEdge(const std::string &name = "");
	virtual ~VirtualTEdge();

public:
	/** Check if the T-edge is virtual. */
	virtual bool isVirtual() { return true; }
private:
};
DECLARE_ASSISTANCES(VirtualTEdge, VTEdg)

/**  
  *  @class  <VirtualTLink> 
  *  @brief  The virtual T-link class   
  *  @note  
  *  A VirtualTLink represents a virtually created T-link.
*/ 
class VirtualTLink : public TLink
{
public:
	VirtualTLink(const std::string &name = "");
	virtual ~VirtualTLink();
public:
	/** Check if the T-link is virtual. */
	virtual bool isVirtual() { return true; }

private:
};
DECLARE_ASSISTANCES(VirtualTLink, VTLnk)

/**  
  *  @class  <VirtualTFace> 
  *  @brief  Virtual T-face class   
  *  @note  
  *  A VirtualTFace represents a virtually created T-face.
*/ 
class VirtualTFace : public TFace
{
public:
	VirtualTFace(const std::string &name = "");
	virtual ~VirtualTFace();
public:
	/** Check if the T-face is virtual. */
	virtual bool isVirtual() { return true; }

	/** Find the north adjacent T-faces. */
	virtual void findNorthFaces(TFacVector &faces);
	/** Find the west adjacent T-faces. */
	virtual void findWestFaces(TFacVector &faces);
	/** Find the south adjacent T-faces. */
	virtual void findSouthFaces(TFacVector &faces);
	/** Find the east adjacent T-faces. */
	virtual void findEastFaces(TFacVector &faces);

	/** Get the width of the virtual T-face. */
	virtual Real width();
	/** Get the height of the virtual T-face. */
	virtual Real height();

	/** Set the size of the virtual T-face. */
	void setSize(Real width, Real height);
	/** Get the real T-face. */
	TFacePtr getReal();
	/** Set the real T-face. */
	void setReal(const TFacePtr &face);
private:
	TFacePtr _real_face;
	Real _width;
	Real _height;
};
DECLARE_ASSISTANCES(VirtualTFace, VTFac)

#ifdef use_namespace
}
#endif

#endif