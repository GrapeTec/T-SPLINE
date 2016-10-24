/*
T-SPLINE -- A T-spline object oriented library in C++
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
2016/03/31: Wenlei Xiao
- Doxygen comments added.
-------------------------------------------------------------------------------
*/

/**  @file  [factory]  
*  @brief  This file contains the classes of different crosses.
  *  @author  <Wenlei Xiao>  
  *  @date  <2015.04.08>  
  *  @version  <v1.0>  
  *  @note  
  *  The cross classes include the T-mapper cross, the T-vertex cross, the T-link cross, and the T-node cross.   
*/

#ifndef FACTORY2_H
#define FACTORY2_H

#include <factory.h>
#include <tspline2.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif
	
/**  
  *  @class  <TFactory> 
  *  @brief  Create T-objects using the factory patten.
  *  @note  
  * The TFactory class is used to create diverse T-objects.
  * The create functions are used to pre-allocate the memory for the wanted T-objects.
  * The patch functions are used to patch the parameters in the created T-objects.
  * The prepare functions are used to derive the missed optional attributes.
*/

DECLARE_SMARTPTR(TFactory2);
class TFactory2 : public TFactory
{
public:
	TFactory2();
	~TFactory2();
public:
	/** Create a T-image2 object*/
	TImage2Ptr createTImage2(const std::string &name);
	/** Create a T-vertex2 object with a coordinate (s, t)*/
	TVertex2Ptr createTVertex2(const std::string &name, Real r, Real s, Real t);
	/** Create a T-edge2 object*/
	TEdge2Ptr createTEdge2(const std::string &name);
	/** Create a T-link2 object*/
	TLink2Ptr createTLink2(const std::string &name);
	/** Create a T-face2 object*/
	TFace2Ptr createTFace2(const std::string &name);
	/** Create a T-node2 valence 6 object*/
	TNodeV6Ptr createTNodeV6(const std::string &name);
	/** Create a T-point2 object with a coordinate (x, y, z, c, w)*/
	TPoint2Ptr createTPoint2(const std::string &name, Real x = 0.0, Real y = 0.0, Real z = 0.0, Real c = 0.0, Real w = 1.0);

	/** Patch the T-pointset2 with needed attributes*/
	void patchTPointset2(const TPointsetPtr &tpoint_grid, const std::vector<std::string> &points);
	/** Patch the named T-pointset2 with needed attributes*/
	void patchTPointset2(const std::string &tpoint_grid, const std::vector<std::string> &points);

	/** Patch the T-vertex2 with needed attributes*/
	void patchTVertex2(const std::string &vertex, const std::string &up, const std::string &down,
		const std::string &north, const std::string &west, const std::string &south, const std::string &east);
	/** Patch the named T-vertex2 with needed attributes*/
	void patchTVertex2(const TVertex2Ptr &vertex, const std::string &up, const std::string &down,
		const std::string &north, const std::string &west, const std::string &south, const std::string &east);

	/** Patch the T-edge2 with needed attributes*/
	void patchTEdge2(const TEdge2Ptr &edge, const std::string &vstart_name, const std::string &vend_name, const std::string &lface_name, const std::string &rface_name, const std::string &aface_name, const std::string &bface_name);
	/** Patch the named T-edge2 with needed attributes*/
	void patchTEdge2(const std::string &edge, const std::string &vstart_name, const std::string &vend_name, const std::string &lface_name, const std::string &rface_name, const std::string &aface_name, const std::string &bface_name);

	//no need link
	//no need edge_condition

	/** Patch the T-node valence 6 with needed attributes*/
	void patchTNodeV6(const TNodeV6Ptr &node_v6, const std::string &mapper, const std::string &point, const std::string &north, const std::string &west, const std::string &south, const std::string &east, const std::string &up, const std::string &down);
	/** Patch the named T-node valence 6 with needed attributes*/
	void patchTNodeV6(const std::string &node_v6, const std::string &mapper, const std::string &point, const std::string &north, const std::string &west, const std::string &south, const std::string &east, const std::string &up, const std::string &down);

	//no need point

	/** Patch the T-vertex2 with needed attributes by T-vertex2 neighbors*/
	void patchTVertexByVertices2(const TVertex2Ptr &vertex, const std::string &up, const std::string &down,
		const std::string &north, const std::string &west, const std::string &south, const std::string &east);
	/** Patch the named T-vertex2 with needed attributes by T-vertex2 neighbors*/
	void patchTVertexByVertices2(const std::string &vertex, const std::string &up, const std::string &down,
		const std::string &north, const std::string &west, const std::string &south, const std::string &east);

	/** Prepare all the T-nodes' half linkages*/
	void prepareTNodeHalfLinkages();
	/** Prepare all T-junctions*/
	void prepareTJunctions();
};

#ifdef use_namespace
}
#endif


#endif