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

#include <visitor.h>
#include <extractor.h>
#include <multiplicity.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

int TLinkVisitorCheckParameterIntersection::_count = 0;
int TLinkVisitorCheckParameterIntersection::_online = 0;

bool TFaceVisitorCheckParameterInside::operator()( const TFacePtr &tface )
{
	if (tface)
	{
		return pointInFace(tface, _p);
	}
	else
	{
		return false;
	}
}

bool TFaceVisitorCheckParameterInside::pointInFace( const TFacePtr &face, const Parameter &parameter )
{
	if (!face) return false;
	TLinkVisitorCheckParameterIntersection::reset();
	std::for_each(face->linkIteratorBegin(), face->linkIteratorEnd(), \
		TLinkVisitorCheckParameterIntersection(parameter));
	return TLinkVisitorCheckParameterIntersection::countIsOdd() || 
		TLinkVisitorCheckParameterIntersection::pointOnline();
}

void TLinkVisitorCheckParameterIntersection::operator()( TLinkPtr tlink )
{
	TVertexPtr v_start = tlink->getStartVertex();
	TVertexPtr v_end = tlink->getEndVertex();
// 	Parameter ps(v_start->getS(), v_start->getT());
// 	Parameter pe(v_end->getS(), v_end->getT());

// 	Parameter ves = pe - ps;
// 	Parameter vep = _p - pe;

	Real max_s = max(v_start->getS(), v_end->getS());
	Real min_s = min(v_start->getS(), v_end->getS());
	Real max_t = max(v_start->getT(), v_end->getT());
	Real min_t = min(v_start->getT(), v_end->getT());
	if (fabs(max_t-min_t) <= M_EPS)
	{
		if (_p.t() >= min_t && _p.t() <= max_t &&
			_p.s() >= min_s && _p.s() <= max_s)
		{
			_online++;
		}
		return;
	}
	else if (_p.t() > max_t || _p.t() < min_t)
	{
		return;
	}
	else
	{
		if (_p.s() > min_s)
		{
			_count++;
		}
		else if (_p.s() == min_s)
		{
			_online++;
		}
	}
}

bool TVertexVisitorCheckParameterCoincide::operator()( const TVertexPtr &vertex )
{
	Parameter pv = TExtractor::extractParameterFromTVertex(vertex);
	Parameter dis = pv - _p;
	if (dis.norm() <= M_EPS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool TLinkVisitorCheckStartEndVertices::operator()( const TLinkPtr &link )
{
	return (link->getStartVertex() == _start && link->getEndVertex() == _end);
}

void TVertexVisitorCheckTJunctions::operator()( const TVertexPtr &vertex )
{
	if (vertex->numberOfNeighbors() == 3)
	{
		TJunctionPtr junction = makePtr<TJunction>(vertex);
		junction->patchVirtuals();
	}
}

void TVertexVisitorCheckTNodes::operator()( const TVertexPtr &vertex )
{
	TPseudoNodeMatrix pnode_matrix(vertex->nodeIteratorBegin(), vertex->nodeIteratorEnd());
	TNodV4Vector norths = pnode_matrix.nodesNorth();
	TNodV4Vector wests = pnode_matrix.nodesWest();
	TNodV4Vector souths = pnode_matrix.nodesSouth();
	TNodV4Vector easts = pnode_matrix.nodesEast();

	TNodeV4Ptr north_tip = pnode_matrix.nodeTipNorth();
	TNodeV4Ptr west_tip = pnode_matrix.nodeTipWest();
	TNodeV4Ptr south_tip = pnode_matrix.nodeTipSouth();
	TNodeV4Ptr east_tip = pnode_matrix.nodeTipEast();

	if (north_tip) setCommonNorth(norths, north_tip->getNorth());
	if (west_tip) setCommonWest(wests, west_tip->getWest());
	if (south_tip) setCommonSouth(souths, south_tip->getSouth());
	if (east_tip) setCommonEast(easts, east_tip->getEast());
}

void TVertexVisitorCheckTNodes::setCommonNorth( TNodV4Vector &nodes, TNodeV4Ptr north )
{
	TNodV4VIterator iter = nodes.begin();
	for (;iter!=nodes.end();iter++)
	{
		TNodeV4Ptr node = *iter;
		node->setNorth(north);
	}
}

void TVertexVisitorCheckTNodes::setCommonWest( TNodV4Vector &nodes, TNodeV4Ptr west )
{
	TNodV4VIterator iter = nodes.begin();
	for (;iter!=nodes.end();iter++)
	{
		TNodeV4Ptr node = *iter;
		node->setWest(west);
	}
}

void TVertexVisitorCheckTNodes::setCommonSouth( TNodV4Vector &nodes, TNodeV4Ptr south )
{
	TNodV4VIterator iter = nodes.begin();
	for (;iter!=nodes.end();iter++)
	{
		TNodeV4Ptr node = *iter;
		node->setSouth(south);
	}
}

void TVertexVisitorCheckTNodes::setCommonEast( TNodV4Vector &nodes, TNodeV4Ptr east )
{
	TNodV4VIterator iter = nodes.begin();
	for (;iter!=nodes.end();iter++)
	{
		TNodeV4Ptr node = *iter;
		node->setEast(east);
	}
}

void TMapperVisitorCheckTNodes::operator()( const TMappableObjectPtr &mapper )
{
	TPseudoNodeMatrix pnode_matrix(mapper->nodeIteratorBegin(), mapper->nodeIteratorEnd());
	TNodV4Vector norths = pnode_matrix.nodesNorth();
	TNodV4Vector wests = pnode_matrix.nodesWest();
	TNodV4Vector souths = pnode_matrix.nodesSouth();
	TNodV4Vector easts = pnode_matrix.nodesEast();

	TNodeV4Ptr north_tip = pnode_matrix.nodeTipNorth();
	TNodeV4Ptr west_tip = pnode_matrix.nodeTipWest();
	TNodeV4Ptr south_tip = pnode_matrix.nodeTipSouth();
	TNodeV4Ptr east_tip = pnode_matrix.nodeTipEast();

	if (north_tip) setCommonNorth(norths, north_tip->getNorth());
	if (west_tip) setCommonWest(wests, west_tip->getWest());
	if (south_tip) setCommonSouth(souths, south_tip->getSouth());
	if (east_tip) setCommonEast(easts, east_tip->getEast());
}

void TMapperVisitorCheckTNodes::setCommonNorth( TNodV4Vector &nodes, TNodeV4Ptr north )
{
	TNodV4VIterator iter = nodes.begin();
	for (;iter!=nodes.end();iter++)
	{
		TNodeV4Ptr node = *iter;
		node->setNorth(north);
	}
}

void TMapperVisitorCheckTNodes::setCommonWest( TNodV4Vector &nodes, TNodeV4Ptr west )
{
	TNodV4VIterator iter = nodes.begin();
	for (;iter!=nodes.end();iter++)
	{
		TNodeV4Ptr node = *iter;
		node->setWest(west);
	}
}

void TMapperVisitorCheckTNodes::setCommonSouth( TNodV4Vector &nodes, TNodeV4Ptr south )
{
	TNodV4VIterator iter = nodes.begin();
	for (;iter!=nodes.end();iter++)
	{
		TNodeV4Ptr node = *iter;
		node->setSouth(south);
	}
}

void TMapperVisitorCheckTNodes::setCommonEast( TNodV4Vector &nodes, TNodeV4Ptr east )
{
	TNodV4VIterator iter = nodes.begin();
	for (;iter!=nodes.end();iter++)
	{
		TNodeV4Ptr node = *iter;
		node->setEast(east);
	}
}


#ifdef use_namespace
}
#endif