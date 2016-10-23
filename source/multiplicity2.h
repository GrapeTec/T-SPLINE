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
#include <tspline2.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

DECLARE_ASSISTANCES(TPseudoNodeV6, TPsdNodV6)

/**  
  *  @class  <TPseudoNodeV6> 
  *  @brief  Pseudo T-node valence 6 
  *  @note  
  *  TPseudoNodeV6 has very similar structure with TNodeV6, while its neighborhood is slightly different.
*/
class TPseudoNodeV6
{
public:
	TPseudoNodeV6(const TNodeV6Ptr &node);
	~TPseudoNodeV6();
public:
	/** Set the pseudo north nodev6. */
	void setPseudoNorth(const TPseudoNodeV6Ptr &node) {_north = node;}
	/** Set the pseudo west nodev6. */
	void setPseudoWest(const TPseudoNodeV6Ptr &node) {_west = node;}
	/** Set the pseudo south nodev6. */
	void setPseudoSouth(const TPseudoNodeV6Ptr &node) {_south = node;}
	/** Set the pseudo east nodev6. */
	void setPseudoEast(const TPseudoNodeV6Ptr &node) {_east = node;}
	/** Set the pseudo up nodev6. */
	void setPseudoUp(const TPseudoNodeV6Ptr &node) {_up = node;}
	/** Set the pseudo down nodev6. */
	void setPseudoDown(const TPseudoNodeV6Ptr &node) {_down = node;}

	/** Return the pseudo north nodev6. */
	TPseudoNodeV6Ptr getPseudoNorth() {return _north;}
	/** Return the pseudo west nodev6. */
	TPseudoNodeV6Ptr getPseudoWest() {return _west;}
	/** Return the pseudo south nodev6. */
	TPseudoNodeV6Ptr getPseudoSouth() {return _south;}
	/** Return the pseudo east nodev6. */
	TPseudoNodeV6Ptr getPseudoEast() {return _east;}
	/** Return the pseudo up nodev6. */
	TPseudoNodeV6Ptr getPseudoUp() {return _up;}
	/** Return the pseudo down nodev6. */
	TPseudoNodeV6Ptr getPseudoDown() {return _down;}

	/** Return the nodev4. */
	TNodeV6Ptr getNode() {return _node;}
	/** Return the north nodes of the nodev6. */
	TNodeV6Ptr getNorth() {return _node->getNorth();}
	/** Return the west nodes of the nodev6. */
	TNodeV6Ptr getWest() {return _node->getWest();}
	/** Return the south nodes of the nodev6. */
	TNodeV6Ptr getSouth() {return _node->getSouth();}
	/** Return the east nodes of the nodev6. */
	TNodeV6Ptr getEast() {return _node->getEast();}
	/** Return the up nodes of the nodev6. */
	TNodeV6Ptr getUp() {return _node->getUp();}
	/** Return the down nodes of the nodev6. */
	TNodeV6Ptr getDown() {return _node->getDown();}
private:
	TNodeV6Ptr _node;
	TPseudoNodeV6Ptr _north;
	TPseudoNodeV6Ptr _west;
	TPseudoNodeV6Ptr _south;
	TPseudoNodeV6Ptr _east;
	TPseudoNodeV6Ptr _up;
	TPseudoNodeV6Ptr _down;
};

/**  
  *  @class  <TPseudoNodeChecker2> 
  *  @brief  Check if the TPseudoNodeV4 is valid
  *  @note  
  *  If the center T-node of a TPseudoNodeV4 is null, it is invalid.
*/
struct TPseudoNodeChecker2
{
	TPseudoNodeChecker2(const TNodeV6Ptr &node): _node(node) {}
	bool operator() (const TPseudoNodeV6Ptr &pnode)
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
	TNodeV6Ptr _node;
};

/**  
  *  @class  <TPseudoNodeMatrix> 
  *  @brief  Pseudo T-node matrix
  *  @note  
  *  TPseudoNodeMatrix is used to derive the multiplicity of a T-vertex.
*/
class TPseudoNodeMatrix2
{
public:
	TPseudoNodeMatrix2(const TNodVIterator &begin, const TNodVIterator &end);
	~TPseudoNodeMatrix2();
public:
	/** Find all the north T-nodes*/
	TNodV6Vector nodesNorth();
	/** Find all the west T-nodes*/
	TNodV6Vector nodesWest();
	/** Find all the south T-nodes*/
	TNodV6Vector nodesSouth();
	/** Find all the east T-nodes*/
	TNodV6Vector nodesEast();
	/** Find all the up T-nodes*/
	TNodV6Vector nodesUp();
	/** Find all the down T-nodes*/
	TNodV6Vector nodesDown();

	/** Find the north tip T-node*/
	TNodeV6Ptr nodeTipNorth();
	/** Find the west tip T-node*/
	TNodeV6Ptr nodeTipWest();
	/** Find the south tip T-node*/
	TNodeV6Ptr nodeTipSouth();
	/** Find the east tip T-node*/
	TNodeV6Ptr nodeTipEast();
	/** Find the up tip T-node*/
	TNodeV6Ptr nodeTipUp();
	/** Find the down tip T-node*/
	TNodeV6Ptr nodeTipDown();
	/** Find the center T-node*/
	TNodeV6Ptr nodeCenter();
protected:
	void initializePseudo(const TNodVIterator &begin, const TNodVIterator &end);

	TPsdNodV6Vector pseudoNodesNorth();
	TPsdNodV6Vector pseudoNodesWest();
	TPsdNodV6Vector pseudoNodesSouth();
	TPsdNodV6Vector pseudoNodesEast();
	TPsdNodV6Vector pseudoNodesUp();
	TPsdNodV6Vector pseudoNodesDown();

	TPsdNodV6Vector extendToNodesNorthSouthPlane(const TPseudoNodeV6Ptr &node);
	TPsdNodV6Vector extendToNodesWestEastPlane(const TPseudoNodeV6Ptr &node);
	TPsdNodV6Vector extendToNodesUpDownPlane(const TPseudoNodeV6Ptr &node);

	void pushFrontWests(TPsdNodV6Vector &nodes, TPseudoNodeV6Ptr node);
	void pushBackEasts(TPsdNodV6Vector &nodes, TPseudoNodeV6Ptr node);
	void pushFrontNorths(TPsdNodV6Vector &nodes, TPseudoNodeV6Ptr node);
	void pushBackSouths(TPsdNodV6Vector &nodes, TPseudoNodeV6Ptr node);
	void pushFrontUps(TPsdNodV6Vector &nodes, TPseudoNodeV6Ptr node);
	void pushBackDowns(TPsdNodV6Vector &nodes, TPseudoNodeV6Ptr node);

	bool nodesNorthSouthPlaneHasNorth(TPsdNodV6Vector &nodes);
	bool nodesNorthSouthPlaneHasSouth(TPsdNodV6Vector &nodes);
	bool nodesWestEastPlaneHasWest(TPsdNodV6Vector &nodes);
	bool nodesWestEastPlaneHasEast(TPsdNodV6Vector &nodes);
	bool nodesUpDownPlaneHasUp(TPsdNodV6Vector &nodes);
	bool nodesUpDownPlaneHasDown(TPsdNodV6Vector &nodes);
private:
	TPsdNodV6Vector _peuso_nodes;
};

#ifdef use_namespace
}
#endif

#endif