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
-------------------------------------------------------------------------------
*/

#include <visitor2.h>
#include <multiplicity2.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif


void TVertexVisitorCheckTNodes2::operator()(const TVertex2Ptr &vertex)
{
	TPseudoNodeMatrix2 pnode_matrix(vertex->nodeIteratorBegin(), vertex->nodeIteratorEnd());
	TNodV6Vector norths = pnode_matrix.nodesNorth();
	TNodV6Vector wests = pnode_matrix.nodesWest();
	TNodV6Vector souths = pnode_matrix.nodesSouth();
	TNodV6Vector easts = pnode_matrix.nodesEast();
	TNodV6Vector ups = pnode_matrix.nodesUp();
	TNodV6Vector downs = pnode_matrix.nodesDown();

	TNodeV6Ptr north_tip = pnode_matrix.nodeTipNorth();
	TNodeV6Ptr west_tip = pnode_matrix.nodeTipWest();
	TNodeV6Ptr south_tip = pnode_matrix.nodeTipSouth();
	TNodeV6Ptr east_tip = pnode_matrix.nodeTipEast();
	TNodeV6Ptr up_tip = pnode_matrix.nodeTipUp();
	TNodeV6Ptr down_tip = pnode_matrix.nodeTipDown();
	
	if(north_tip)
		setCommonNorth(norths, north_tip->getNorth());
	if(west_tip)
		setCommonWest(wests, west_tip->getWest());
	if(south_tip)
		setCommonSouth(souths, south_tip->getSouth());
	if(east_tip)
		setCommonEast(easts, east_tip->getEast());
	if(up_tip)
		setCommonUp(ups, up_tip->getUp());
	if(down_tip)
		setCommonDown(downs, down_tip->getDown());
}

void TVertexVisitorCheckTNodes2::setCommonNorth(TNodV6Vector &nodes, TNodeV6Ptr north)
{
	TNodV6VIterator iter = nodes.begin();
	for (;iter!=nodes.end();iter++)
	{
		(*iter)->setNorth(north);
	}
}

void TVertexVisitorCheckTNodes2::setCommonWest(TNodV6Vector &nodes, TNodeV6Ptr west)
{
	TNodV6VIterator iter = nodes.begin();
	for (;iter!=nodes.end();iter++)
	{
		(*iter)->setWest(west);
	}
}

void TVertexVisitorCheckTNodes2::setCommonSouth(TNodV6Vector &nodes, TNodeV6Ptr south)
{
	TNodV6VIterator iter = nodes.begin();
	for (;iter!=nodes.end();iter++)
	{
		(*iter)->setSouth(south);
	}
}

void TVertexVisitorCheckTNodes2::setCommonEast(TNodV6Vector &nodes, TNodeV6Ptr east)
{
	TNodV6VIterator iter = nodes.begin();
	for (;iter!=nodes.end();iter++)
	{
		(*iter)->setEast(east);
	}
}

void TVertexVisitorCheckTNodes2::setCommonUp(TNodV6Vector &nodes, TNodeV6Ptr up)
{
	TNodV6VIterator iter = nodes.begin();
	for (;iter!=nodes.end();iter++)
	{
		(*iter)->setUp(up);
	}
}

void TVertexVisitorCheckTNodes2::setCommonDown(TNodV6Vector &nodes, TNodeV6Ptr down)
{
	TNodV6VIterator iter = nodes.begin();
	for (;iter!=nodes.end();iter++)
	{
		(*iter)->setDown(down);
	}
}

void TVertexVisitorCheckTJunctions2::operator()( const TVertex2Ptr &vertex )
{
	if (vertex->numberOfNeighbors() == 4)
	{
		//T-junctions
	}
}

#ifdef use_namespace
}
#endif