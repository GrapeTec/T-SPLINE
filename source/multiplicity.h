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
2016/04/27: Yazui Liu
- Modify TPseudoNodeMatrix::nodeCenter function.
-------------------------------------------------------------------------------
*/


/**  @file  [multiplicity]  
*  @brief  This file contains the classes to deal with the multiplicity.
  *  @author  <Wenlei Xiao>  
  *  @date  <2015.04.08>
  *  @version  <v1.0>  
  *  @note  
  *  This file introduces a new concept of pseudo T-node to help derive the multiplicity accordingly.   
*/

#ifndef MULTIPLICITY_H
#define MULTIPLICITY_H

#include <utils.h>
#include <tspline.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif


DECLARE_ASSISTANCES(TPseudoNodeV4, TPsdNodV4)

/**  
  *  @class  <TPseudoNodeV4> 
  *  @brief  Pseudo T-node valence 4 
  *  @note  
  *  TPseudoNodeV4 has very similar structure with TNodeV4, while its neighborhood is slightly different.
*/
class TPseudoNodeV4
{
public:
	TPseudoNodeV4(const TNodeV4Ptr &node);
	~TPseudoNodeV4();
public:
	/** Set the pseudo north nodev4. */
	void setPseudoNorth(const TPseudoNodeV4Ptr &node) {_north = node;}
	/** Set the pseudo west nodev4. */
	void setPseudoWest(const TPseudoNodeV4Ptr &node) {_west = node;}
	/** Set the pseudo south nodev4. */
	void setPseudoSouth(const TPseudoNodeV4Ptr &node) {_south = node;}
	/** Set the pseudo east nodev4. */
	void setPseudoEast(const TPseudoNodeV4Ptr &node) {_east = node;}

	/** Return the pseudo north nodev4. */
	TPseudoNodeV4Ptr getPseudoNorth() {return _north;}
	/** Return the pseudo west nodev4. */
	TPseudoNodeV4Ptr getPseudoWest() {return _west;}
	/** Return the pseudo south nodev4. */
	TPseudoNodeV4Ptr getPseudoSouth() {return _south;}
	/** Return the pseudo east nodev4. */
	TPseudoNodeV4Ptr getPseudoEast() {return _east;}

	/** Return the nodev4. */
	TNodeV4Ptr getNode() {return _node;}
	/** Return the north nodes of the nodev4. */
	TNodeV4Ptr getNorth() {return _node->getNorth();}
	/** Return the west nodes of the nodev4. */
	TNodeV4Ptr getWest() {return _node->getWest();}
	/** Return the south nodes of the nodev4. */
	TNodeV4Ptr getSouth() {return _node->getSouth();}
	/** Return the east nodes of the nodev4. */
	TNodeV4Ptr getEast() {return _node->getEast();}
private:
	TNodeV4Ptr _node;			
	TPseudoNodeV4Ptr _north;	
	TPseudoNodeV4Ptr _west;		
	TPseudoNodeV4Ptr _south;	
	TPseudoNodeV4Ptr _east;		
};

/**  
  *  @class  <TPseudoNodeChecker> 
  *  @brief  Check if the TPseudoNodeV4 is valid
  *  @note  
  *  If the center T-node of a TPseudoNodeV4 is null, it is invalid.
*/
struct TPseudoNodeChecker
{
	TPseudoNodeChecker(const TNodeV4Ptr &node): _node(node) {}
	bool operator() (const TPseudoNodeV4Ptr &pnode)
	{
		if(pnode->getNode() == _node)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
private:
	TNodeV4Ptr _node;
};

/**  
  *  @class  <TPseudoNodeMatrix> 
  *  @brief  Pseudo T-node matrix
  *  @note  
  *  TPseudoNodeMatrix is used to derive the multiplicity of a T-vertex.
*/
class TPseudoNodeMatrix
{
public:
	TPseudoNodeMatrix(const TNodVIterator &begin, const TNodVIterator &end);
	~TPseudoNodeMatrix();
public:
	/** Find all the north T-nodes*/
	TNodV4Vector nodesNorth();
	/** Find all the west T-nodes*/
	TNodV4Vector nodesWest();
	/** Find all the south T-nodes*/
	TNodV4Vector nodesSouth();
	/** Find all the east T-nodes*/
	TNodV4Vector nodesEast();

	/** Find the north tip T-node*/
	TNodeV4Ptr nodeTipNorth();
	/** Find the west tip T-node*/
	TNodeV4Ptr nodeTipWest();
	/** Find the south tip T-node*/
	TNodeV4Ptr nodeTipSouth();
	/** Find the east tip T-node*/
	TNodeV4Ptr nodeTipEast();
	/** Find the center T-node*/
	TNodeV4Ptr nodeCenter();

protected:
	void initializePseudo(const TNodVIterator &begin, const TNodVIterator &end);

	TPsdNodV4Vector pseudoNodesNorth();
	TPsdNodV4Vector pseudoNodesWest();
	TPsdNodV4Vector pseudoNodesSouth();
	TPsdNodV4Vector pseudoNodesEast();
	
	TPsdNodV4Vector extendToNodesRow(const TPseudoNodeV4Ptr &node);
	TPsdNodV4Vector extendToNodesCol(const TPseudoNodeV4Ptr &node);

	void pushFrontWests(TPsdNodV4Vector &nodes, TPseudoNodeV4Ptr node);
	void pushBackEasts(TPsdNodV4Vector &nodes, TPseudoNodeV4Ptr node);
	void pushFrontNorths(TPsdNodV4Vector &nodes, TPseudoNodeV4Ptr node);
	void pushBackSouths(TPsdNodV4Vector &nodes, TPseudoNodeV4Ptr node);

	bool nodesRowHasNorth(TPsdNodV4Vector &nodes);
	bool nodesRowHasSouth(TPsdNodV4Vector &nodes);
	bool nodesColHasWest(TPsdNodV4Vector &nodes);
	bool nodesColHasEast(TPsdNodV4Vector &nodes);
private:
	 TPsdNodV4Vector _peuso_nodes;	
};

#ifdef use_namespace
}
#endif

#endif