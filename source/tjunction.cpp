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

#include <tjunction.h>
#include <extractor.h>
#include <visitor.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

TJunction::TJunction( const TVertexPtr &vertex ) :
	_vertex(vertex), _orientation(E_CENTER)
{
	fill(vertex->getNorth(), vertex->getWest(), vertex->getSouth(), vertex->getEast());
}

TJunction::~TJunction()
{

}

void TJunction::fill( const TLinkPtr &north, const TLinkPtr &west, 
					 const TLinkPtr &south, const TLinkPtr &east )
{
	if (!north && west && south && east)
	{
		_middle = south;
		_left = west;
		_right = east;
		_orientation = E_NORTH;
	}
	else if (north && !west && south && east)
	{
		_middle = east;
		_left = south;
		_right = north;
		_orientation = E_WEST;
	}
	else if (north && west && !south && east)
	{
		_middle = north;
		_left = east;
		_right = west;
		_orientation = E_SOUTH;
	}
	else if (north && west && south && !east)
	{
		_middle = west;
		_left = north;
		_right = south;
		_orientation = E_EAST;
	}
}

void TJunction::fill( const TVertexPtr &vertex )
{
	cleanUp();
	_vertex = vertex;
	if (vertex)
	{
		fill(vertex->getNorth(), vertex->getWest(), vertex->getSouth(), vertex->getEast());
	}
}

void TJunction::patchVirtuals()
{
	if (valid())
	{
		switch (_orientation)
		{
		case E_NORTH: // north
			patchNorthVirtuals();
			break;
		case E_WEST: // west
			patchWestVirtuals();
			break;
		case E_SOUTH: // south
			patchSouthVirtuals();
			break;
		case E_EAST: // east
			patchEastVirtuals();
			break;
		}
	}
}

bool TJunction::valid()
{
	if (!_vertex || !_middle || !_left || !_right || _orientation == E_CENTER)
	{
		return false;
	}

	if (_left->isBoundary() && _right->isBoundary())
	{
		return false;
	}

	return true;
}

void TJunction::cleanUp()
{
	_vertex = 0;
	_left = 0;
	_right = 0;
	_orientation = E_CENTER;
}

void TJunction::patchNorthVirtuals()
{
	TFacePtr face1 = _left->getRightFace();
	Parameter p1 = intersectNorth(face1, _vertex->getS());
	patchNorthVirtual(_vertex, p1, face1);

	TFacVector face2s;
	face1->findNorthFaces(face2s);
	TFacVIterator iter1 = std::find_if(face2s.begin(), face2s.end(), TFaceVisitorCheckParameterInside(p1));
	TVertexPtr vertex1 = _vertex->getNorthTVertex();

	if (vertex1->isVirtual() && iter1!=face2s.end())
	{
		TFacePtr face2 = *iter1;
		Parameter p2 = intersectNorth(face2, p1.s());
		patchNorthVirtual(vertex1, p2, face2);
	}
}

void TJunction::patchWestVirtuals()
{
	TFacePtr face1 = _left->getRightFace();
	Parameter p1 = intersectWest(face1, _vertex->getT());
	patchWestVirtual(_vertex, p1, face1);

	TFacVector face2s;
	face1->findWestFaces(face2s);
	TFacVIterator iter1 = std::find_if(face2s.begin(), face2s.end(), TFaceVisitorCheckParameterInside(p1));
	TVertexPtr vertex1 = _vertex->getWestTVertex();

	if (vertex1->isVirtual() && iter1!=face2s.end())
	{
		TFacePtr face2 = *iter1;
		Parameter p2 = intersectWest(face2, p1.t());
		patchWestVirtual(vertex1, p2, face2);
	}
}

void TJunction::patchSouthVirtuals()
{
	TFacePtr face1 = _left->getRightFace();
	Parameter p1 = intersectSouth(face1, _vertex->getS());
	patchSouthVirtual(_vertex, p1, face1);

	TFacVector face2s;
	face1->findSouthFaces(face2s);
	TFacVIterator iter1 = std::find_if(face2s.begin(), face2s.end(), TFaceVisitorCheckParameterInside(p1));
	TVertexPtr vertex1 = _vertex->getSouthTVertex();

	if (vertex1->isVirtual() && iter1!=face2s.end())
	{
		TFacePtr face2 = *iter1;
		Parameter p2 = intersectSouth(face2, p1.s());
		patchSouthVirtual(vertex1, p2, face2);
	}
}

void TJunction::patchEastVirtuals()
{
	TFacePtr face1 = _left->getRightFace();
	Parameter p1 = intersectEast(face1, _vertex->getT());
	patchEastVirtual(_vertex, p1, face1);

	TFacVector face2s;
	face1->findEastFaces(face2s);
	TFacVIterator iter1 = std::find_if(face2s.begin(), face2s.end(), TFaceVisitorCheckParameterInside(p1));
	TVertexPtr vertex1 = _vertex->getEastTVertex();

	if (vertex1->isVirtual() && iter1!=face2s.end())
	{
		TFacePtr face2 = *iter1;
		Parameter p2 = intersectEast(face2, p1.t());
		patchEastVirtual(vertex1, p2, face2);
	}
}

Parameter TJunction::intersectNorth( const TFacePtr &face, Real s )
{
	if (!face) return Parameter(0.0, 0.0);
	TLnkVector links;
	face->findWestLinks(links);
	TLnkVIterator iter = links.begin();
	TVertexPtr vertex = (*iter)->getStartVertex();
	return Parameter(s, vertex->getT());
}

Parameter TJunction::intersectWest( const TFacePtr &face, Real t )
{
	if (!face) return Parameter(0.0, 0.0);
	TLnkVector links;
	face->findEastLinks(links);
	TLnkVIterator iter = links.begin();
	TVertexPtr vertex = (*iter)->getStartVertex();
	return Parameter(vertex->getS(), t);
}

Parameter TJunction::intersectSouth( const TFacePtr &face, Real s )
{
	if (!face) return Parameter(0.0, 0.0);
	TLnkVector links;
	face->findEastLinks(links);
	TLnkVIterator iter = links.begin();
	TVertexPtr vertex = (*iter)->getStartVertex();
	return Parameter(s, vertex->getT());
}

Parameter TJunction::intersectEast( const TFacePtr &face, Real t )
{
	if (!face) return Parameter(0.0, 0.0);
	TLnkVector links;
	face->findWestLinks(links);
	TLnkVIterator iter = links.begin();
	TVertexPtr vertex = (*iter)->getStartVertex();
	return Parameter(vertex->getS(), t);
}

VirtualTLinkPtr TJunction::createVirtualLink( const TVertexPtr &vertex, Parameter p, const TFacePtr &face )
{
	TVertexPtr next_vertex = TExtractor::extractTVertexFromTFace(face, p);
	if (!next_vertex)
	{
		next_vertex = makePtr<VirtualTVertex>("vv");
		next_vertex->setST(p.s(), p.t());
	}

	VirtualTEdgePtr vedge = makePtr<VirtualTEdge>("ve");
	vedge->setStartVertex(vertex);
	vedge->setEndVertex(next_vertex);

	VirtualTFacePtr vface_left, vface_right;
	if (vedge->toNorth())
	{
		splitTFaceWestEast(face, p.s(), vface_left, vface_right);
	}
	else if (vedge->toWest())
	{
		splitTFaceNorthSouth(face, p.t(), vface_right, vface_left);
	}
	else if (vedge->toSouth())
	{
		splitTFaceWestEast(face, p.s(), vface_right, vface_left );
	}
	else if (vedge->toEast())
	{
		splitTFaceNorthSouth(face, p.t(), vface_left, vface_right);
	}
	vedge->setLeftFace(vface_left);	vedge->setRightFace(vface_right);

	VirtualTLinkPtr vlink = makePtr<VirtualTLink>("vl");
	vlink->setOrientedEdge(vedge, true);

	return vlink;
}

VirtualTNodeV4Ptr TJunction::createVirtualNodeV4( const TVertexPtr &vertex )
{
	VirtualTNodeV4Ptr vnode_v4 = makePtr<VirtualTNodeV4>();
	vnode_v4->setTVertex(vertex);
	return vnode_v4;
}

void TJunction::patchNorthVirtual( const TVertexPtr &vertex, Parameter p,
								  const TFacePtr &face)
{
	TLinkPtr link = createVirtualLink(vertex, p, face);
	vertex->setNorth(link);
	TVertexPtr next_vertex = vertex->getNorthTVertex();
	TNodeV4Ptr next_node_v4;
	TNodVIterator iter;
	if (next_vertex->isVirtual())
	{
		next_node_v4 = createVirtualNodeV4(next_vertex);
	}
	else
	{
		next_node_v4 = TExtractor::extractSouthNodeFromTVertex(next_vertex);
	}

	TNodVector node_norths;
	TExtractor::extractNorthNodesFromTVertex(vertex, node_norths);
	for (iter=node_norths.begin();iter!=node_norths.end();iter++)
	{
		TNodeV4Ptr node_v4 = castPtr<TNodeV4>(*iter);
		node_v4->setNorth(next_node_v4);
	}
}

void TJunction::patchWestVirtual( const TVertexPtr &vertex, Parameter p, const TFacePtr &face )
{
	TLinkPtr link = createVirtualLink(vertex, p, face);
	vertex->setWest(link);
	TVertexPtr next_vertex = vertex->getWestTVertex();
	TNodeV4Ptr next_node_v4;
	TNodVIterator iter;
	if (next_vertex->isVirtual())
	{
		next_node_v4 = createVirtualNodeV4(next_vertex);
	}
	else
	{
		next_node_v4 = TExtractor::extractEastNodeFromTVertex(next_vertex);
	}

	TNodVector node_wests;
	TExtractor::extractWestNodesFromTVertex(vertex, node_wests);
	for (iter=node_wests.begin();iter!=node_wests.end();iter++)
	{
		TNodeV4Ptr node_v4 = castPtr<TNodeV4>(*iter);
		node_v4->setWest(next_node_v4);
	}
}

void TJunction::patchSouthVirtual( const TVertexPtr &vertex, Parameter p, const TFacePtr &face )
{
	TLinkPtr link = createVirtualLink(vertex, p, face);
	vertex->setSouth(link);
	TVertexPtr next_vertex = vertex->getSouthTVertex();
	TNodeV4Ptr next_node_v4;
	TNodVIterator iter;
	if (next_vertex->isVirtual())
	{
		next_node_v4 = createVirtualNodeV4(next_vertex);
	}
	else
	{
		next_node_v4 = TExtractor::extractNorthNodeFromTVertex(next_vertex);
	}

	TNodVector node_souths;
	TExtractor::extractSouthNodesFromTVertex(vertex, node_souths);
	for (iter=node_souths.begin();iter!=node_souths.end();iter++)
	{
		TNodeV4Ptr node_v4 = castPtr<TNodeV4>(*iter);
		node_v4->setSouth(next_node_v4);
	}
}

void TJunction::patchEastVirtual( const TVertexPtr &vertex, Parameter p, const TFacePtr &face )
{
	TLinkPtr link = createVirtualLink(vertex, p, face);
	vertex->setEast(link);
	TVertexPtr next_vertex = vertex->getEastTVertex();
	TNodeV4Ptr next_node_v4;
	TNodVIterator iter;
	if (next_vertex->isVirtual())
	{
		next_node_v4 = createVirtualNodeV4(next_vertex);
	}
	else
	{
		next_node_v4 = TExtractor::extractWestNodeFromTVertex(next_vertex);
	}

	TNodVector node_easts;
	TExtractor::extractEastNodesFromTVertex(vertex, node_easts);
	for (iter=node_easts.begin();iter!=node_easts.end();iter++)
	{
		TNodeV4Ptr node_v4 = castPtr<TNodeV4>(*iter);
		node_v4->setEast(next_node_v4);
	}
}

void TJunction::splitTFaceWestEast( const TFacePtr face, Real s, 
								   VirtualTFacePtr &west, VirtualTFacePtr &east )
{
	if (!west) west = makePtr<VirtualTFace>("vf");
	if (!east) east = makePtr<VirtualTFace>("vf");

	TVertexPtr sw_vertex = TExtractor::extractSouthWestTVertexFromTFace(face);
	Real wwidth = s - sw_vertex->getS();
	Real ewidth = face->width() - wwidth;
	Real height = face->height();

	west->setReal(face); east->setReal(face);
	west->setSize(wwidth, height); east->setSize(ewidth, height);
}

void TJunction::splitTFaceNorthSouth( const TFacePtr face, Real t, 
									 VirtualTFacePtr &north, VirtualTFacePtr &south )
{
	if (!north) north = makePtr<VirtualTFace>("vf");
	if (!south) south = makePtr<VirtualTFace>("vf");

	TVertexPtr sw_vertex = TExtractor::extractSouthWestTVertexFromTFace(face);
	Real width = face->width();
	Real sheight = t - sw_vertex->getT();
	Real nheight = face->height() - sheight;

	north->setReal(face); south->setReal(face);
	north->setSize(width, nheight); south->setSize(width, sheight);
}

#ifdef use_namespace
}
#endif