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
	return nodes;
}

TNodV6Vector TPseudoNodeMatrix2::nodesWest()
{
	TNodV6Vector nodes;
	return nodes;
}

TNodV6Vector TPseudoNodeMatrix2::nodesSouth()
{
	TNodV6Vector nodes;
	return nodes;
}

TNodV6Vector TPseudoNodeMatrix2::nodesEast()
{
	TNodV6Vector nodes;
	return nodes;
}

TNodV6Vector TPseudoNodeMatrix2::nodesUp()
{
	TNodV6Vector nodes;
	return nodes;
}

TNodV6Vector TPseudoNodeMatrix2::nodesDown()
{
	TNodV6Vector nodes;
	return nodes;
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





#ifdef use_namespace
}
#endif