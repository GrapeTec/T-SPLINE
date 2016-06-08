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


/**  @file  [tjunction]  
*  @brief  This file contains a TJunction class to deal with T shaped T-vertices.
  *  @author  <Wenlei Xiao>  
  *  @date  <2015.04.08>  
  *  @version  <v1.0>  
  *  @note  
  *  TJunction class can help to check and remend T-junctions.   
*/

#ifndef TJUNCTION_H
#define TJUNCTION_H

#include <basis.h>
#include <tspline.h>
#include <virtual.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

DECLARE_SMARTPTR(TJunction);

/**  
  *  @class  <TJunction> 
  *  @brief  T-junction class.
  *  @note  
  *  TJunction requires a T-vertex to be set, it will then derive the shape of the T-junction and patch necessary virtual T-objects.
*/
class TJunction
{
public:
	TJunction(const TVertexPtr &vertex);
	~TJunction();

public:
	/** Fill a T-vertex. */
	void fill(const TVertexPtr &vertex);
	/** Check if the T-junction is valid. */
	bool valid();
	/** Patch the virtual T-objects. */
	void patchVirtuals();

protected:
	void fill(const TLinkPtr &north, const TLinkPtr &west, 
		const TLinkPtr &south, const TLinkPtr &east);
	void cleanUp();

	void patchNorthVirtuals();
	void patchWestVirtuals();
	void patchSouthVirtuals();
	void patchEastVirtuals();

	Parameter intersectNorth(const TFacePtr &face, Real s);
	Parameter intersectWest(const TFacePtr &face, Real t);
	Parameter intersectSouth(const TFacePtr &face, Real s);
	Parameter intersectEast(const TFacePtr &face, Real t);

	VirtualTLinkPtr createVirtualLink(const TVertexPtr &vertex, Parameter p, const TFacePtr &face);
	VirtualTNodeV4Ptr createVirtualNodeV4(const TVertexPtr &vertex);
	void patchNorthVirtual(const TVertexPtr &vertex, Parameter p, const TFacePtr &face);
	void patchWestVirtual(const TVertexPtr &vertex, Parameter p, const TFacePtr &face);
	void patchSouthVirtual(const TVertexPtr &vertex, Parameter p, const TFacePtr &face);
	void patchEastVirtual(const TVertexPtr &vertex, Parameter p, const TFacePtr &face);

protected:
	void splitTFaceWestEast(const TFacePtr face, Real s, 
		VirtualTFacePtr &west, VirtualTFacePtr &east);
	void splitTFaceNorthSouth(const TFacePtr face, Real t, 
		VirtualTFacePtr &north, VirtualTFacePtr &south);
private:
	TVertexPtr _vertex;
	TLinkPtr _middle;
	TLinkPtr _left;
	TLinkPtr _right;
	int _orientation;
};

#ifdef use_namespace
}
#endif

#endif