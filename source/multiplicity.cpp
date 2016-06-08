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

#include <multiplicity.h>
#include <finder.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

TPseudoNodeV4::TPseudoNodeV4( const TNodeV4Ptr &node ) :
	_node(node)
{

}

TPseudoNodeV4::~TPseudoNodeV4()
{

}


TPseudoNodeMatrix::TPseudoNodeMatrix( const TNodVIterator &begin, const TNodVIterator &end )
{
	initializePseudo(begin, end);
}

TPseudoNodeMatrix::~TPseudoNodeMatrix()
{

}

void TPseudoNodeMatrix::initializePseudo(const TNodVIterator &begin, const TNodVIterator &end)
{
	TNodVIterator iter;
	for (iter=begin;iter!=end;iter++)
	{
		TNodeV4Ptr node_v4 = (*iter)->asTNodeV4();
		TPseudoNodeV4Ptr pnode = makePtr<TPseudoNodeV4>(node_v4);
		_peuso_nodes.push_back(pnode);
	}

	TLocalFinder<TNodVIterator> finder(begin, end);
	TPsdNodV4VIterator piter = _peuso_nodes.begin();
	for (;piter!=_peuso_nodes.end();piter++)
	{
		TPseudoNodeV4Ptr pnode = *piter;
		TNodeV4Ptr north = pnode->getNorth();
		TNodeV4Ptr west = pnode->getWest();
		TNodeV4Ptr south = pnode->getSouth();
		TNodeV4Ptr east = pnode->getEast();
		if( finder.has(north) )
		{
			TPsdNodV4VIterator piter = std::find_if(_peuso_nodes.begin(), _peuso_nodes.end(), TPseudoNodeChecker(north));
			pnode->setPseudoNorth(*piter);
		}
		if( finder.has(west) )
		{
			TPsdNodV4VIterator piter = std::find_if(_peuso_nodes.begin(), _peuso_nodes.end(), TPseudoNodeChecker(west));
			pnode->setPseudoWest(*piter);
		}
		if( finder.has(south) )
		{
			TPsdNodV4VIterator piter = std::find_if(_peuso_nodes.begin(), _peuso_nodes.end(), TPseudoNodeChecker(south));
			pnode->setPseudoSouth(*piter);
		}
		if( finder.has(east) )
		{
			TPsdNodV4VIterator piter = std::find_if(_peuso_nodes.begin(), _peuso_nodes.end(), TPseudoNodeChecker(east));
			pnode->setPseudoEast(*piter);
		}
	}
}

TNodV4Vector TPseudoNodeMatrix::nodesNorth()
{
	TNodV4Vector nodes;
	TPsdNodV4Vector nodes_north = pseudoNodesNorth();
	TPsdNodV4VIterator iter = nodes_north.begin();
	for (;iter!=nodes_north.end();iter++)
	{
		nodes.push_back((*iter)->getNode());
	}
	return nodes;
}

TNodV4Vector TPseudoNodeMatrix::nodesWest()
{
	TNodV4Vector nodes;
	TPsdNodV4Vector nodes_west = pseudoNodesWest();
	TPsdNodV4VIterator iter = nodes_west.begin();
	for (;iter!=nodes_west.end();iter++)
	{
		nodes.push_back((*iter)->getNode());
	}
	return nodes;
}

TNodV4Vector TPseudoNodeMatrix::nodesSouth()
{
	TNodV4Vector nodes;
	TPsdNodV4Vector nodes_south = pseudoNodesSouth();
	TPsdNodV4VIterator iter = nodes_south.begin();
	for (;iter!=nodes_south.end();iter++)
	{
		nodes.push_back((*iter)->getNode());
	}
	return nodes;
}

TNodV4Vector TPseudoNodeMatrix::nodesEast()
{
	TNodV4Vector nodes;
	TPsdNodV4Vector nodes_east = pseudoNodesEast();
	TPsdNodV4VIterator iter = nodes_east.begin();
	for (;iter!=nodes_east.end();iter++)
	{
		nodes.push_back((*iter)->getNode());
	}
	return nodes;
}

bool hasNorth(const TNodeV4Ptr &node)
{
	return (node && node->getNorth());
}

bool hasWest(const TNodeV4Ptr &node)
{
	return (node && node->getWest());
}

bool hasSouth(const TNodeV4Ptr &node)
{
	return (node && node->getSouth());
}

bool hasEast(const TNodeV4Ptr &node)
{
	return (node && node->getEast());
}

TNodeV4Ptr TPseudoNodeMatrix::nodeTipNorth()
{
	TNodV4Vector norths = nodesNorth();
	TNodV4VIterator iter = std::find_if(norths.begin(), norths.end(), hasNorth);
	if (iter!=norths.end())
	{
		return (*iter)->getNorth()->getSouth();
	}
	else
	{
		return 0;
	}
}

TNodeV4Ptr TPseudoNodeMatrix::nodeTipWest()
{
	TNodV4Vector wests = nodesWest();
	TNodV4VIterator iter = std::find_if(wests.begin(), wests.end(), hasWest);
	if (iter!=wests.end())
	{
		return (*iter)->getWest()->getEast();
	}
	else
	{
		return 0;
	}
}

TNodeV4Ptr TPseudoNodeMatrix::nodeTipSouth()
{
	TNodV4Vector souths = nodesSouth();
	TNodV4VIterator iter = std::find_if(souths.begin(), souths.end(), hasSouth);
	if (iter!=souths.end())
	{
		return (*iter)->getSouth()->getNorth();
	}
	else
	{
		return 0;
	}
}

TNodeV4Ptr TPseudoNodeMatrix::nodeTipEast()
{
	TNodV4Vector easts = nodesEast();
	TNodV4VIterator iter = std::find_if(easts.begin(), easts.end(), hasEast);
	if (iter!=easts.end())
	{
		return (*iter)->getEast()->getWest();
	}
	else
	{
		return 0;
	}
}

TNodeV4Ptr TPseudoNodeMatrix::nodeCenter()
{
	TNodeV4Ptr west = nodeTipWest();
	TNodeV4Ptr north = nodeTipNorth();
	TNodeV4Ptr east = nodeTipEast();//lyz
	TNodeV4Ptr south = nodeTipSouth();

	if(north == south)
		return north;
	if(east == west)
		return east;
	if(north)
		return north->getSouth();
	if(south)
		return south->getNorth();
	if(west)
		return west->getEast();
	if(east)
		return east->getWest();
	
	return 0;
}

TPsdNodV4Vector TPseudoNodeMatrix::pseudoNodesNorth()
{
	TPsdNodV4VIterator iter = _peuso_nodes.begin();
	for (;iter!=_peuso_nodes.end();iter++)
	{
		TPseudoNodeV4Ptr node = *iter;
		TPsdNodV4Vector row = extendToNodesRow(node);
		if (!nodesRowHasNorth(row))
		{
			return row;
		}
	}
	TPsdNodV4Vector empty;
	return empty;
}

TPsdNodV4Vector TPseudoNodeMatrix::pseudoNodesWest()
{
	TPsdNodV4VIterator iter = _peuso_nodes.begin();
	for (;iter!=_peuso_nodes.end();iter++)
	{
		TPseudoNodeV4Ptr node = *iter;
		TPsdNodV4Vector col = extendToNodesCol(node);
		if (!nodesColHasWest(col))
		{
			return col;
		}
	}
	TPsdNodV4Vector empty;
	return empty;
}

TPsdNodV4Vector TPseudoNodeMatrix::pseudoNodesSouth()
{
	TPsdNodV4VIterator iter = _peuso_nodes.begin();
	for (;iter!=_peuso_nodes.end();iter++)
	{
		TPseudoNodeV4Ptr node = *iter;
		TPsdNodV4Vector row = extendToNodesRow(node);
		if (!nodesRowHasSouth(row))
		{
			return row;
		}
	}
	TPsdNodV4Vector empty;
	return empty;
}

TPsdNodV4Vector TPseudoNodeMatrix::pseudoNodesEast()
{
	TPsdNodV4VIterator iter = _peuso_nodes.begin();
	for (;iter!=_peuso_nodes.end();iter++)
	{
		TPseudoNodeV4Ptr node = *iter;
		TPsdNodV4Vector col = extendToNodesCol(node);
		if (!nodesColHasEast(col))
		{
			return col;
		}
	}
	TPsdNodV4Vector empty;
	return empty;
}

TPsdNodV4Vector TPseudoNodeMatrix::extendToNodesRow( const TPseudoNodeV4Ptr &node )
{
	TPsdNodV4Vector nodes;
	if (!node) return nodes;

	pushFrontWests(nodes, node);
	nodes.push_back(node);
	pushBackEasts(nodes, node);

	return nodes;
}

TPsdNodV4Vector TPseudoNodeMatrix::extendToNodesCol( const TPseudoNodeV4Ptr &node )
{
	TPsdNodV4Vector nodes;
	if (!node) return nodes;

	pushFrontNorths(nodes, node);
	nodes.push_back(node);
	pushBackSouths(nodes, node);

	return nodes;
}

void TPseudoNodeMatrix::pushFrontWests( TPsdNodV4Vector &nodes, TPseudoNodeV4Ptr node )
{
	if (!node) return;
	TPseudoNodeV4Ptr west = node->getPseudoWest();
	while (west)
	{
		nodes.insert(nodes.begin(), west);
		west = west->getPseudoWest();
	}
}

void TPseudoNodeMatrix::pushBackEasts( TPsdNodV4Vector &nodes, TPseudoNodeV4Ptr node )
{
	if (!node) return;
	TPseudoNodeV4Ptr east = node->getPseudoEast();
	while (east)
	{
		nodes.push_back(east);
		east = east->getPseudoEast();
	}
}

void TPseudoNodeMatrix::pushFrontNorths( TPsdNodV4Vector &nodes, TPseudoNodeV4Ptr node )
{
	if (!node) return;
	TPseudoNodeV4Ptr north = node->getPseudoNorth();
	while (north)
	{
		nodes.insert(nodes.begin(), north);
		north = north->getPseudoNorth();
	}
}

void TPseudoNodeMatrix::pushBackSouths( TPsdNodV4Vector &nodes, TPseudoNodeV4Ptr node )
{
	if (!node) return;
	TPseudoNodeV4Ptr south = node->getPseudoSouth();
	while (south)
	{
		nodes.push_back(south);
		south = south->getPseudoSouth();
	}
}

bool TPseudoNodeMatrix::nodesRowHasNorth( TPsdNodV4Vector &nodes )
{
	TPsdNodV4VIterator iter = nodes.begin();
	for (;iter!=nodes.end();iter++)
	{
		TPseudoNodeV4Ptr node = *iter;
		if (node->getPseudoNorth())
		{
			return true;
		}
	}
	return false;
}

bool TPseudoNodeMatrix::nodesRowHasSouth( TPsdNodV4Vector &nodes )
{
	TPsdNodV4VIterator iter = nodes.begin();
	for (;iter!=nodes.end();iter++)
	{
		TPseudoNodeV4Ptr node = *iter;
		if (node->getPseudoSouth())
		{
			return true;
		}
	}
	return false;
}

bool TPseudoNodeMatrix::nodesColHasWest( TPsdNodV4Vector &nodes )
{
	TPsdNodV4VIterator iter = nodes.begin();
	for (;iter!=nodes.end();iter++)
	{
		TPseudoNodeV4Ptr node = *iter;
		if (node->getPseudoWest())
		{
			return true;
		}
	}
	return false;
}

bool TPseudoNodeMatrix::nodesColHasEast( TPsdNodV4Vector &nodes )
{
	TPsdNodV4VIterator iter = nodes.begin();
	for (;iter!=nodes.end();iter++)
	{
		TPseudoNodeV4Ptr node = *iter;
		if (node->getPseudoEast())
		{
			return true;
		}
	}
	return false;
}

#ifdef use_namespace
}
#endif