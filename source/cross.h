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
2016/03/31: Wenlei Xiao
   - Doxygen comments added.
-------------------------------------------------------------------------------
*/

/**  @file  [cross]  
*  @brief  Cross classes
  *  @author  <Wenlei Xiao>  
  *  @date  <2016.03.31>  
  *  @version  <v1.0>  
  *  @note  
  *  The cross classes include the T-mapper cross, the T-vertex cross, the T-link cross, and the T-node cross.   
*/
#ifndef CROSS_H
#define CROSS_H

#include <tspline.h>

#include <unordered_set>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif
	
DECLARE_ASSISTANCES(TMapperCross, TMapCrs)
DECLARE_ASSISTANCES(TVertexCross, TVtxCrs)
DECLARE_ASSISTANCES(TLinkCross, TLnkCrs)
DECLARE_ASSISTANCES(TNodeV4Cross, TNodV4Crs)

/**  
  *  @class  <TMapperCross> 
  *  @brief  T-mapper cross
  *  @note  
  *  A T-mapper cross contains a center, and branched T-mappers in the north, west, south and east directions.
*/
class TMapperCross
{
public:
	TMapperCross();
	~TMapperCross();
public:
	/** Set the center mapper. */
	void setCenter(const TMappableObjectPtr &mapper);
	/** Add the north mapper. */
	void addNorth(const TMappableObjectPtr &mapper);
	/** Add the west mapper. */
	void addWest(const TMappableObjectPtr &mapper);
	/** Add the south mapper. */
	void addSouth(const TMappableObjectPtr &mapper);
	/** Add the east mapper. */
	void addEast(const TMappableObjectPtr &mapper);

	/** Find all the T-faces covered by the cross. */
	void findFaces(TFacSet &faces);

	/** Make all the four T-mapper branches contain unique T-mappers. */
	void unique();
	/** Clear the T-mapper cross. */
	void clear();
	/** Get the size of the north branch. */
	int sizeNorth() { return _mappers_north.size(); }
	/** Get the size of the west branch. */
	int sizeWest() { return _mappers_west.size(); }
	/** Get the size of the south branch. */
	int sizeSouth() { return _mappers_south.size(); }
	/** Get the size of the east branch. */
	int sizeEast() { return _mappers_east.size(); }
protected:
	void uniqueMappers(TMapObjVector &mappers);
	ParameterSquarePtr blendParameterSquare();
private:
	TMappableObjectPtr _mapper_center;	
	TMapObjVector _mappers_north;		
	TMapObjVector _mappers_west;		
	TMapObjVector _mappers_south;		
	TMapObjVector _mappers_east;		
	
	/** Assister to extend the parameter square. */
	class ParameterExtender
	{
	public:
		ParameterExtender(const ParameterSquarePtr &parameter_square) : 
			_parameter_square(parameter_square) {}
		~ParameterExtender() {}
		void operator()(const TMappableObjectPtr &mapper);
	private:
		ParameterSquarePtr _parameter_square;
	};
	/** Assister to find the overlapped T-faces. */
	class OverlappedFaceFinder
	{
	public:
		OverlappedFaceFinder(const ParameterSquarePtr &target_square, TFacSet &faces) : 
			_target_square(target_square), _faces(faces) {}
		~OverlappedFaceFinder() {}
		void operator()(const TObjectPtr &object);

	protected:
		int codeOfArea(Real v, Real vmin, Real vmax);
		bool isOverlapped(const ParameterSquarePtr check_square);
	private:
		ParameterSquarePtr _target_square;
		TFacSet &_faces;
	};
};

/**  
  *  @class  <TNodeV4Cross> 
  *  @brief  The T-node (valance 4) cross
  *  @note 
  *  A T-node cross contains a center T-node, and branched T-nodes in the north, west, south and east directions.
*/
class TNodeV4Cross
{
public:
	TNodeV4Cross(int degree_s = 3, int degree_t = 3);
	~TNodeV4Cross();

public:
	/** Set the center node. */
	void setNodeCenter(const TNodeV4Ptr &node);

	/** Add the north node. */
	void addNodeNorth(const TNodeV4Ptr &node);
	/** Add the west node. */
	void addNodeWest(const TNodeV4Ptr &node);
	/** Add the south node. */
	void addNodeSouth(const TNodeV4Ptr &node);
	/** Add the east node. */
	void addNodeEast(const TNodeV4Ptr &node);

	bool isPrepared();
	/** Prepare the mapper and faces. */
	void prepareRelationships();
	/** Clear the mapper and faces. */
	void clearRelationships();

	void copyTFaces(TFacVector &faces);

protected:
	/** Prepare the mapper cross. */
	void prepareTMapperCross();
	/** Prepare the faces. */
	void prepareTFaces();
	/** Find the vertex of node. */
	TVertexPtr findVertexOfNode(const TNodeV4Ptr &node);
	/** Find the mapper of node. */
	TMappableObjectPtr findMapperOfNode(const TNodeV4Ptr &node);
private:
	TNodeV4Ptr _node_center;	
	TNodV4Vector _nodes_north;	
	TNodV4Vector _nodes_west;	
	TNodV4Vector _nodes_south;	
	TNodV4Vector _nodes_east;	

	bool _prepared;					
	TMapperCrossPtr _mapper_cross;	
	TFacSet _faces;					
	int _degree_s;					
	int _degree_t;					
};

#ifdef use_namespace
}
#endif


#endif