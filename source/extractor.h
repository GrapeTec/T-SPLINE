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
2016/03/31: Wenlei Xiao
- Doxygen comments added.
-------------------------------------------------------------------------------
*/


/**  @file  [extractor]  
*  @brief  This file contains a fully static class TExtractor to help users extract needed information.
  *  @author  <Wenlei Xiao>  
  *  @date  <2015.04.08>  
  *  @version  <v1.0>  
  *  @note  
  *  TExtractor extract the needed information that can not be directly accessed from the entry object.   
*/

#ifndef EXTRACTOR_H
#define EXTRACTOR_H

#include <tspline.h>
#include <cross.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

/**  
  *  @class  <TExtractor> 
  *  @brief  A set extracting functions.
  *  @note  
  *  TExtractor is used to extract various information from the entry object. (Fully Static Class).
  *  Usually the information can not be directly accessed.
*/

// fixed
class TExtractor
{
public:
	/** Extract the west neighbor from a T-node valence 4. (Set to def when is null) */
	static TNodeV4Ptr extractWestFromTNodeV4(const TNodeV4Ptr &node, TNodeV4Ptr def = 0);
	/** Extract the east neighbor from a T-node valence 4. (Set to def when is null) */
	static TNodeV4Ptr extractEastFromTNodeV4(const TNodeV4Ptr &node, TNodeV4Ptr def = 0);
	/** Extract the north neighbor from a T-node valence 4. (Set to def when is null) */
	static TNodeV4Ptr extractNorthFromTNodeV4(const TNodeV4Ptr &node, TNodeV4Ptr def = 0);
	/** Extract the south neighbor from a T-node valence 4. (Set to def when is null) */
	static TNodeV4Ptr extractSouthFromTNodeV4(const TNodeV4Ptr &node, TNodeV4Ptr def = 0);
	/** Make sure do not extract a null west T-node, set to itself as default*/
	static TNodeV4Ptr extractNonNullWestFromTNodeV4(const TNodeV4Ptr &node);
	/** Make sure do not extract a null east T-node, set to itself as default*/
	static TNodeV4Ptr extractNonNullEastFromTNodeV4(const TNodeV4Ptr &node);
	/** Make sure do not extract a null north T-node, set to itself as default*/
	static TNodeV4Ptr extractNonNullNorthFromTNodeV4(const TNodeV4Ptr &node);
	/** Make sure do not extract a null south T-node, set to itself as default*/
	static TNodeV4Ptr extractNonNullSouthFromTNodeV4(const TNodeV4Ptr &node);

	/** Extract the middle T-node linked by the T-vertex*/
	static TNodeV4Ptr extractMiddleNodeFromTVertex(const TVertexPtr &vertex, int ttype = E_CENTER);
	/** Extract the major north T-node linked by the T-vertex*/
	static TNodeV4Ptr extractNorthNodeFromTVertex(const TVertexPtr &vertex);
	/** Extract the major west T-node linked by the T-vertex*/
	static TNodeV4Ptr extractWestNodeFromTVertex(const TVertexPtr &vertex);
	/** Extract the major south T-node linked by the T-vertex*/
	static TNodeV4Ptr extractSouthNodeFromTVertex(const TVertexPtr &vertex);
	/** Extract the major east T-node linked by the T-vertex*/
	static TNodeV4Ptr extractEastNodeFromTVertex(const TVertexPtr &vertex);

	/** Extract the north T-nodes linked by the T-vertex*/
	static void extractNorthNodesFromTVertex(const TVertexPtr &vertex, TNodVector &nodes);
	/** Extract the west T-nodes linked by the T-vertex*/
	static void extractWestNodesFromTVertex(const TVertexPtr &vertex, TNodVector &nodes);
	/** Extract the south T-nodes linked by the T-vertex*/
	static void extractSouthNodesFromTVertex(const TVertexPtr &vertex, TNodVector &nodes);
	/** Extract the east T-nodes linked by the T-vertex*/
	static void extractEastNodesFromTVertex(const TVertexPtr &vertex, TNodVector &nodes);

	/** Extract the T-node cross with the T-node valence 4 at the center*/
	static void extractCrossFromTNodeV4(const TNodeV4Ptr &node, TNodeV4CrossPtr &node_cross, int degree_s, int degree_t);
	/** Extract the T-faces covered by the T-node cross*/
	static void extractTFacesFromTNodeV4Cross(const TNodeV4CrossPtr &node_cross, TFacVector &faces);
	/** Extract the T-faces from the T-node valence 4*/
	static void extractTFacesFromTNodeV4(const TNodeV4Ptr &node, TFacVector &faces, int degree_s = 3, int degree_t = 3);

	/** Extract the u and v knots from the T-node valence 4*/
	static void extractUVKnotsFromTNodeV4(const TNodeV4Ptr &node_v4, std::vector<Real> &u_nodes, std::vector<Real> &v_nodes);
	/** Extract the rational point with weight from the T-node valence 4*/
	static void extractRationalPointFromTNodeV4(const TNodeV4Ptr &node_v4, Point3D &point, Real &weight);

	/** Extract the northeast T-vertex from a T-face*/
	static TVertexPtr extractNorthEastTVertexFromTFace(const TFacePtr &face);
	/** Extract the northwest T-vertex from a T-face*/
	static TVertexPtr extractNorthWestTVertexFromTFace(const TFacePtr &face);
	/** Extract the southeast T-vertex from a T-face*/
	static TVertexPtr extractSouthEastTVertexFromTFace(const TFacePtr &face);
	/** Extract the southwest T-vertex from a T-face*/
	static TVertexPtr extractSouthWestTVertexFromTFace(const TFacePtr &face);

	/** Extract the parameter from a T-vertex*/
	static Parameter extractParameterFromTVertex(const TVertexPtr &vertex);
	
	/** Extract the maximum parameter from a T-spline*/
	static Parameter extractParameterFromTSpline(const TSplinePtr &spline);

	/** Extract T-vertices from a T-face*/
	static TVtxVector extractTVerticesFromTFace(const TFacePtr &face);
	/** Extract a T-vertex from a T-face*/
	static TVertexPtr extractTVertexFromTFace(const TFacePtr &face, const Parameter &parameter);
};

DECLARE_SMARTPTR(TExtractor)

#ifdef use_namespace
}
#endif

#endif