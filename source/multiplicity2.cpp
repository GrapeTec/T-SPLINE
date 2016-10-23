/*
TSPLINE -- A T-spline object oriented package in C++
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
2016/04/02: Wenlei Xiao
- Doxygen comments added.
2016/04/27: Yazui Liu
- Modify TPseudoNodeMatrix::nodeCenter function.
-------------------------------------------------------------------------------
*/

#include <multiplicity2.h>
#include <finder.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

TPseudoNodeV6::TPseudoNodeV6(const TNodeV6Ptr &node) :
	_node(node)
{

}

TPseudoNodeV6::~TPseudoNodeV6()
{

}

TPseudoNodeMatrix2::TPseudoNodeMatrix2( const TNodVIterator &begin, const TNodVIterator &end )
{
	initializePseudo(begin, end);
}

TPseudoNodeMatrix2::~TPseudoNodeMatrix2()
{

}

TNodV6Vector TPseudoNodeMatrix2::nodesNorth()
{
	TNodV6Vector nodes;
	TPsdNodV6Vector nodes_north = pseudoNodesNorth();
	TPsdNodV6VIterator iter = nodes_north.begin();
	for (;iter!=nodes_north.end();iter++)
	{
		nodes.push_back((*iter)->getNode());
	}
	return nodes;
}

TNodV6Vector TPseudoNodeMatrix2::nodesWest()
{
	TNodV6Vector nodes;
	TPsdNodV6Vector nodes_west = pseudoNodesWest();
	TPsdNodV6VIterator iter = nodes_west.begin();
	for (;iter!=nodes_west.end();iter++)
	{
		nodes.push_back((*iter)->getNode());
	}
	return nodes;
}

TNodV6Vector TPseudoNodeMatrix2::nodesSouth()
{
	TNodV6Vector nodes;
	TPsdNodV6Vector nodes_south = pseudoNodesSouth();
	TPsdNodV6VIterator iter = nodes_south.begin();
	for (;iter!=nodes_south.end();iter++)
	{
		nodes.push_back((*iter)->getNode());
	}
	return nodes;
}

TNodV6Vector TPseudoNodeMatrix2::nodesEast()
{
	TNodV6Vector nodes;
	TPsdNodV6Vector nodes_east = pseudoNodesEast();
	TPsdNodV6VIterator iter = nodes_east.begin();
	for (;iter!=nodes_east.end();iter++)
	{
		nodes.push_back((*iter)->getNode());
	}
	return nodes;
}

TNodV6Vector TPseudoNodeMatrix2::nodesUp()
{
	TNodV6Vector nodes;
	TPsdNodV6Vector nodes_up = pseudoNodesUp();
	TPsdNodV6VIterator iter = nodes_up.begin();
	for (;iter!=nodes_up.end();iter++)
	{
		nodes.push_back((*iter)->getNode());
	}
	return nodes;
}

TNodV6Vector TPseudoNodeMatrix2::nodesDown()
{
	TNodV6Vector nodes;
	TPsdNodV6Vector nodes_down = pseudoNodesDown();
	TPsdNodV6VIterator iter = nodes_down.begin();
	for (;iter!=nodes_down.end();iter++)
	{
		nodes.push_back((*iter)->getNode());
	}
	return nodes;
}

bool hasNorth(const TNodeV6Ptr &node)
{
	return (node && node->getNorth());
}

bool hasWest(const TNodeV6Ptr &node)
{
	return (node && node->getWest());
}

bool hasSouth(const TNodeV6Ptr &node)
{
	return (node && node->getSouth());
}

bool hasEast(const TNodeV6Ptr &node)
{
	return (node && node->getEast());
}

bool hasUp(const TNodeV6Ptr &node)
{
	return (node && node->getUp());
}

bool hasDown(const TNodeV6Ptr &node)
{
	return (node && node->getDown());
}

TNodeV6Ptr TPseudoNodeMatrix2::nodeTipNorth()
{
	return 0;
}

TNodeV6Ptr TPseudoNodeMatrix2::nodeTipWest()
{
	return 0;
}

TNodeV6Ptr TPseudoNodeMatrix2::nodeTipSouth()
{
	return 0;
}

TNodeV6Ptr TPseudoNodeMatrix2::nodeTipEast()
{
	return 0;
}

TNodeV6Ptr TPseudoNodeMatrix2::nodeTipUp()
{
	return 0;
}

TNodeV6Ptr TPseudoNodeMatrix2::nodeTipDown()
{
	return 0;
}

TNodeV6Ptr TPseudoNodeMatrix2::nodeCenter()
{
	return 0;
}

void TPseudoNodeMatrix2::initializePseudo( const TNodVIterator &begin, const TNodVIterator &end )
{
	TNodVIterator iter;
	for (iter = begin; iter!=end; iter++)
	{
		TNodeV6Ptr node_v6 = (*iter)->asTNodeV6();
		TPseudoNodeV6Ptr pnode = makePtr<TPseudoNodeV6>(node_v6);
		_peuso_nodes.push_back(pnode);
	}

	TLocalFinder<TNodVIterator> finder(begin, end);
	TPsdNodV6VIterator piter = _peuso_nodes.begin();
	for (;piter!=_peuso_nodes.end();piter++)
	{
		TPseudoNodeV6Ptr pnode = *piter;
		TNodeV6Ptr north = pnode->getNorth();
		TNodeV6Ptr west = pnode->getWest();
		TNodeV6Ptr south = pnode->getSouth();
		TNodeV6Ptr east = pnode->getEast();
		TNodeV6Ptr up = pnode->getUp();
		TNodeV6Ptr down = pnode->getDown();
		if( finder.has(north) )
		{
			TPsdNodV6VIterator piter = std::find_if(_peuso_nodes.begin(), _peuso_nodes.end(), TPseudoNodeChecker2(north));
			pnode->setPseudoNorth(*piter);
		}
		if( finder.has(west) )
		{
			TPsdNodV6VIterator piter = std::find_if(_peuso_nodes.begin(), _peuso_nodes.end(), TPseudoNodeChecker2(west));
			pnode->setPseudoWest(*piter);
		}
		if( finder.has(south) )
		{
			TPsdNodV6VIterator piter = std::find_if(_peuso_nodes.begin(), _peuso_nodes.end(), TPseudoNodeChecker2(south));
			pnode->setPseudoSouth(*piter);
		}
		if( finder.has(east) )
		{
			TPsdNodV6VIterator piter = std::find_if(_peuso_nodes.begin(), _peuso_nodes.end(), TPseudoNodeChecker2(east));
			pnode->setPseudoEast(*piter);
		}
		if( finder.has(up) )
		{
			TPsdNodV6VIterator piter = std::find_if(_peuso_nodes.begin(), _peuso_nodes.end(), TPseudoNodeChecker2(up));
			pnode->setPseudoUp(*piter);
		}
		if( finder.has(down) )
		{
			TPsdNodV6VIterator piter = std::find_if(_peuso_nodes.begin(), _peuso_nodes.end(), TPseudoNodeChecker2(down));
			pnode->setPseudoDown(*piter);
		}
	}
}

TPsdNodV6Vector TPseudoNodeMatrix2::pseudoNodesNorth()
{
	TPsdNodV6VIterator iter = _peuso_nodes.begin();
	for (;iter!=_peuso_nodes.end();iter++)
	{
		TPsdNodV6Vector north_south_plane = extendToNodesNorthSouthPlane(*iter);
		if (!nodesNorthSouthPlaneHasNorth(north_south_plane))
		{
			return north_south_plane;
		}
	}
	TPsdNodV6Vector empty;
	return empty;
}

TPsdNodV6Vector TPseudoNodeMatrix2::pseudoNodesWest()
{
	TPsdNodV6VIterator iter = _peuso_nodes.begin();
	for (;iter!=_peuso_nodes.end();iter++)
	{
		TPsdNodV6Vector west_east_plane = extendToNodesWestEastPlane(*iter);
		if (!nodesWestEastPlaneHasWest(west_east_plane))
		{
			return west_east_plane;
		}
	}
	TPsdNodV6Vector empty;
	return empty;
}

TPsdNodV6Vector TPseudoNodeMatrix2::pseudoNodesSouth()
{
	TPsdNodV6VIterator iter = _peuso_nodes.begin();
	for (;iter!=_peuso_nodes.end();iter++)
	{
		TPsdNodV6Vector north_south_plane = extendToNodesNorthSouthPlane(*iter);
		if (!nodesNorthSouthPlaneHasSouth(north_south_plane))
		{
			return north_south_plane;
		}
	}
	TPsdNodV6Vector empty;
	return empty;
}

TPsdNodV6Vector TPseudoNodeMatrix2::pseudoNodesEast()
{
	TPsdNodV6VIterator iter = _peuso_nodes.begin();
	for (;iter!=_peuso_nodes.end();iter++)
	{
		TPsdNodV6Vector west_east_plane = extendToNodesWestEastPlane(*iter);
		if (!nodesWestEastPlaneHasEast(west_east_plane))
		{
			return west_east_plane;
		}
	}
	TPsdNodV6Vector empty;
	return empty;
}

TPsdNodV6Vector TPseudoNodeMatrix2::pseudoNodesUp()
{
	TPsdNodV6VIterator iter = _peuso_nodes.begin();
	for (;iter!=_peuso_nodes.end();iter++)
	{
		TPsdNodV6Vector up_down_plane = extendToNodesUpDownPlane(*iter);
		if (!nodesUpDownPlaneHasUp(up_down_plane))
		{
			return up_down_plane;
		}
	}
	TPsdNodV6Vector empty;
	return empty;
}

TPsdNodV6Vector TPseudoNodeMatrix2::pseudoNodesDown()
{
	TPsdNodV6VIterator iter = _peuso_nodes.begin();
	for (;iter!=_peuso_nodes.end();iter++)
	{
		TPsdNodV6Vector up_down_plane = extendToNodesUpDownPlane(*iter);
		if (!nodesUpDownPlaneHasDown(up_down_plane))
		{
			return up_down_plane;
		}
	}
	TPsdNodV6Vector empty;
	return empty;
}

TPsdNodV6Vector TPseudoNodeMatrix2::extendToNodesNorthSouthPlane(const TPseudoNodeV6Ptr &node)
{
	TPsdNodV6Vector nodes;
	if(!node) return nodes;

	//west<->east * up<->down
	TPsdNodV6Vector nodes_scan;
	pushFrontUps(nodes_scan, node);
	nodes_scan.push_back(node);
	pushBackDowns(nodes_scan, node);

	TPsdNodV6VIterator iter = nodes_scan.begin();
	for (;iter!=nodes_scan.end();iter++)
	{
		pushFrontWests(nodes, *iter);
		nodes.push_back(*iter);
		pushBackEasts(nodes, *iter);
	}

	return nodes;
}

TPsdNodV6Vector TPseudoNodeMatrix2::extendToNodesWestEastPlane(const TPseudoNodeV6Ptr &node)
{
	TPsdNodV6Vector nodes;
	if(!node) return nodes;

	//north<->south * up<->down
	TPsdNodV6Vector nodes_scan;
	pushFrontUps(nodes_scan, node);
	nodes_scan.push_back(node);
	pushBackDowns(nodes_scan, node);

	TPsdNodV6VIterator iter = nodes_scan.begin();
	for (;iter!=nodes_scan.end();iter++)
	{
		pushFrontNorths(nodes, *iter);
		nodes.push_back(*iter);
		pushBackSouths(nodes, *iter);
	}

	return nodes;
}

TPsdNodV6Vector TPseudoNodeMatrix2::extendToNodesUpDownPlane(const TPseudoNodeV6Ptr &node)
{
	TPsdNodV6Vector nodes;
	if(!node) return nodes;

	//west<->east * north<->south
	TPsdNodV6Vector nodes_scan;
	pushFrontWests(nodes_scan, node);
	nodes_scan.push_back(node);
	pushBackEasts(nodes_scan, node);

	TPsdNodV6VIterator iter = nodes_scan.begin();
	for (;iter!=nodes_scan.end();iter++)
	{
		pushFrontNorths(nodes, *iter);
		nodes.push_back(*iter);
		pushBackSouths(nodes, *iter);
	}

	return nodes;
}

void TPseudoNodeMatrix2::pushFrontWests(TPsdNodV6Vector &nodes, TPseudoNodeV6Ptr node)
{
	if(!node) return;
	TPseudoNodeV6Ptr west = node->getPseudoWest();
	while (west)
	{
		nodes.insert(nodes.begin(), west);
		west = west->getPseudoWest();
	}
}

void TPseudoNodeMatrix2::pushBackEasts(TPsdNodV6Vector &nodes, TPseudoNodeV6Ptr node)
{
	if(!node) return;
	TPseudoNodeV6Ptr east = node->getPseudoEast();
	while (east)
	{
		nodes.push_back(east);
		east = east->getPseudoEast();
	}
}

void TPseudoNodeMatrix2::pushFrontNorths(TPsdNodV6Vector &nodes, TPseudoNodeV6Ptr node)
{
	if(!node) return;
	TPseudoNodeV6Ptr north = node->getPseudoNorth();
	while (north)
	{
		nodes.insert(nodes.begin(), north);
		north = north->getPseudoNorth();
	}
}

void TPseudoNodeMatrix2::pushBackSouths(TPsdNodV6Vector &nodes, TPseudoNodeV6Ptr node)
{
	if(!node) return;
	TPseudoNodeV6Ptr south = node->getPseudoSouth();
	while (south)
	{
		nodes.push_back(south);
		south = south->getPseudoSouth();
	}
}

void TPseudoNodeMatrix2::pushFrontUps(TPsdNodV6Vector &nodes, TPseudoNodeV6Ptr node)
{
	if(!node) return;
	TPseudoNodeV6Ptr up = node->getPseudoUp();
	while (up)
	{
		nodes.insert(nodes.begin(), up);
		up = up->getPseudoUp();
	}
}

void TPseudoNodeMatrix2::pushBackDowns(TPsdNodV6Vector &nodes, TPseudoNodeV6Ptr node)
{
	if(!node) return;
	TPseudoNodeV6Ptr down = node->getPseudoDown();
	while (down)
	{
		nodes.push_back(down);
		down = down->getPseudoDown();
	}
}

bool TPseudoNodeMatrix2::nodesNorthSouthPlaneHasNorth(TPsdNodV6Vector &nodes)
{
	TPsdNodV6VIterator iter = nodes.begin();
	for (;iter!=nodes.end();iter++)
	{
		TPseudoNodeV6Ptr node = *iter;
		if(node->getPseudoNorth())
			return true;
	}
	return false;
}

bool TPseudoNodeMatrix2::nodesNorthSouthPlaneHasSouth(TPsdNodV6Vector &nodes)
{
	TPsdNodV6VIterator iter = nodes.begin();
	for (;iter!=nodes.end();iter++)
	{
		TPseudoNodeV6Ptr node = *iter;
		if(node->getPseudoSouth())
			return true;
	}
	return false;
}

bool TPseudoNodeMatrix2::nodesWestEastPlaneHasWest(TPsdNodV6Vector &nodes)
{
	TPsdNodV6VIterator iter = nodes.begin();
	for (;iter!=nodes.end();iter++)
	{
		TPseudoNodeV6Ptr node = *iter;
		if(node->getPseudoWest())
			return true;
	}
	return false;
}

bool TPseudoNodeMatrix2::nodesWestEastPlaneHasEast(TPsdNodV6Vector &nodes)
{
	TPsdNodV6VIterator iter = nodes.begin();
	for (;iter!=nodes.end();iter++)
	{
		TPseudoNodeV6Ptr node = *iter;
		if(node->getPseudoEast())
			return true;
	}
	return false;
}

bool TPseudoNodeMatrix2::nodesUpDownPlaneHasUp(TPsdNodV6Vector &nodes)
{
	TPsdNodV6VIterator iter = nodes.begin();
	for (;iter!=nodes.end();iter++)
	{
		TPseudoNodeV6Ptr node = *iter;
		if(node->getPseudoUp())
			return true;
	}
	return false;
}

bool TPseudoNodeMatrix2::nodesUpDownPlaneHasDown(TPsdNodV6Vector &nodes)
{
	TPsdNodV6VIterator iter = nodes.begin();
	for (;iter!=nodes.end();iter++)
	{
		TPseudoNodeV6Ptr node = *iter;
		if(node->getPseudoDown())
			return true;
	}
	return false;
}





#ifdef use_namespace
}
#endif