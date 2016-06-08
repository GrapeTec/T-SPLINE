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

#include <factory.h>
#include <visitor.h>
#include <extractor.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

std::vector<std::string> TFactory::_empty_nodes;

TFactory::TFactory()
{
	_objects = makePtr<TGroup>();
	_finder = makePtr<TFinder>(_objects);
}

TFactory::~TFactory()
{

}

TSplinePtr TFactory::createTSpline( const std::string &name )
{
	return createTObject<TSpline>(name);
}

TImagePtr TFactory::createTImage( const std::string &name )
{
	return createTObject<TImage>(name);
}

TConnectPtr TFactory::createTConnect( const std::string &name )
{
	return createTObject<TConnect>(name);
}

TPointsetPtr TFactory::createTPointset( const std::string &name )
{
	return createTObject<TPointset>(name);
}

TVertexPtr TFactory::createTVertex( const std::string &name, Real s, Real t )
{
	TVertexPtr obj = createTObject<TVertex>(name);
	obj->setST(s, t);
	return obj;
}

TEdgePtr TFactory::createTEdge( const std::string &name )
{
	return createTObject<TEdge>(name);
}

TLinkPtr TFactory::createTLink( const std::string &name )
{
	return createTObject<TLink>(name);
}

TEdgeConditionPtr TFactory::createTEdgeCondition( const std::string &name )
{
	return createTObject<TEdgeCondition>(name);
}

TFacePtr TFactory::createTFace( const std::string &name )
{
	return createTObject<TFace>(name);
}

TNodePtr TFactory::createTNode( const std::string &name )
{
	return createTObject<TNode>(name);
}

TNodeV4Ptr TFactory::createTNodeV4( const std::string &name )
{
	return createTObject<TNodeV4>(name);
}

TPointPtr TFactory::createTPoint( const std::string &name, Real x /*= 0.0*/, Real y /*= 0.0*/, Real z /*= 0.0*/, Real w /*= 1.0*/ )
{
	TPointPtr obj = createTObject<TPoint>(name);
	obj->setXYZW(x, y, z, w);
	return obj;
}

void TFactory::patchTSpline( const TSplinePtr &spline, const std::string &tmesh, const std::string &nodes, const std::string &points, int degree /*= 3*/ )
{
	spline->setTImage(findTObject<TImage>(tmesh));
	spline->setTConnect(findTObject<TConnect>(nodes));
	spline->setTPointset(findTObject<TPointset>(points));
	spline->setSDegree(degree);
	spline->setTDegree(degree);
}

void TFactory::patchTSpline( const std::string &spline, const std::string &tmesh, const std::string &nodes, const std::string &points, int degree /*= 3*/ )
{
	TSplinePtr spl = findTObject<TSpline>(spline);
	patchTSpline(spl, tmesh, nodes, points, degree);
}

void TFactory::patchTImage( const TImagePtr &tmesh, const std::vector<std::string> &faces, const std::vector<std::string> &links, const std::vector<std::string> &edges, const std::vector<std::string> &vertices )
{
	std::vector<std::string>::const_iterator iter;
	for (iter = faces.begin(); iter != faces.end(); iter++)
	{
		tmesh->addFace(findTObject<TFace>(*iter));
	}
	for (iter = links.begin(); iter != links.end(); iter++)
	{
		tmesh->addLink(findTObject<TLink>(*iter));
	}
	for (iter = edges.begin(); iter != edges.end(); iter++)
	{
		tmesh->addEdge(findTObject<TEdge>(*iter));
	}
	for (iter = vertices.begin(); iter != vertices.end(); iter++)
	{
		tmesh->addVertex(findTObject<TVertex>(*iter));
	}
}

void TFactory::patchTImage( const std::string &tmesh, const std::vector<std::string> &faces, const std::vector<std::string> &links, const std::vector<std::string> &edges, const std::vector<std::string> &vertices )
{
	patchTImage(findTObject<TImage>(tmesh), faces, links, edges, vertices);
}

void TFactory::patchTConnect( const TConnectPtr &tnode_grid, const std::vector<std::string> &nodes )
{
	std::vector<std::string>::const_iterator iter;
	for (iter = nodes.begin(); iter != nodes.end(); iter++)
	{
		TNodeV4Ptr node = findTObject<TNodeV4>(*iter);
		tnode_grid->addObject(node);
	}
}

void TFactory::patchTConnect( const std::string &tnode_grid, const std::vector<std::string> &nodes )
{
	patchTConnect(findTObject<TConnect>(tnode_grid), nodes);
}

void TFactory::patchTPointset( const TPointsetPtr &tpoint_grid, const std::vector<std::string> &points )
{
	std::vector<std::string>::const_iterator iter;
	for (iter = points.begin(); iter != points.end(); iter++)
	{
		TPointPtr point = findTObject<TPoint>(*iter);
		tpoint_grid->addObject(point);
	}
}

void TFactory::patchTPointset( const std::string &tpoint_grid, const std::vector<std::string> &points )
{
	patchTPointset(findTObject<TPointset>(tpoint_grid), points);
}

void TFactory::patchTVertex( const TVertexPtr &vertex, const std::string &north, const std::string &west, const std::string &south, const std::string &east )
{
	TLinkPtr link_north = findTObject<TLink>(north);
	TLinkPtr link_west = findTObject<TLink>(west);
	TLinkPtr link_south = findTObject<TLink>(south);
	TLinkPtr link_east = findTObject<TLink>(east);
	vertex->setNeighbours(link_north, link_west, link_south, link_east);
}

void TFactory::patchTVertex( const std::string &vertex, const std::string &north, const std::string &west, const std::string &south, const std::string &east )
{
	patchTVertex(findTObject<TVertex>(vertex), north, west, south, east);
}

void TFactory::patchTVertexByVertices( const TVertexPtr &vertex, const std::string &north, const std::string &west, const std::string &south, const std::string &east )
{
	TVertexPtr vertex_north = findTObject<TVertex>(north);
	TVertexPtr vertex_west = findTObject<TVertex>(west);
	TVertexPtr vertex_south = findTObject<TVertex>(south);
	TVertexPtr vertex_east = findTObject<TVertex>(east);
	
	TLinkPtr link_north = findTLinkByStartEndVertices(vertex, vertex_north);
	TLinkPtr link_west = findTLinkByStartEndVertices(vertex, vertex_west);
	TLinkPtr link_south = findTLinkByStartEndVertices(vertex, vertex_south);
	TLinkPtr link_east = findTLinkByStartEndVertices(vertex, vertex_east);
	
	vertex->setNeighbours(link_north, link_west, link_south, link_east);
}

void TFactory::patchTVertexByVertices( const std::string &vertex, const std::string &north, const std::string &west, const std::string &south, const std::string &east )
{
	patchTVertexByVertices(findTObject<TVertex>(vertex), north, west, south, east);
}

void TFactory::patchTEdge( const TEdgePtr &edge, const std::string &vstart_name, const std::string &vend_name, const std::string &lface_name, const std::string &rface_name )
{
	edge->setStartVertex(findTObject<TVertex>(vstart_name));
	edge->setEndVertex(findTObject<TVertex>(vend_name));
	edge->setLeftFace(findTObject<TFace>(lface_name));
	edge->setRightFace(findTObject<TFace>(rface_name));
}

void TFactory::patchTEdge( const std::string &edge, const std::string &vstart_name, const std::string &vend_name, const std::string &lface_name, const std::string &rface_name )
{
	patchTEdge(findTObject<TEdge>(edge), vstart_name, vend_name, lface_name, rface_name);
}

void TFactory::patchTLink( const TLinkPtr &link, const std::string &edge_name, bool orientation /* = true */ )
{
	link->setOrientedEdge(findTObject<TEdge>(edge_name), orientation);
}

void TFactory::patchTLink( const std::string &link, const std::string &edge_name, bool orientation /*= true*/ )
{
	patchTLink(findTObject<TLink>(link), edge_name, orientation);
}

void TFactory::patchTEdgeCondition( const TEdgeConditionPtr &edge_condition, const std::string &edge, bool boundary_condition )
{
	edge_condition->setEdgeCondition(findTObject<TEdge>(edge), boundary_condition);
}

void TFactory::patchTEdgeCondition( const std::string &edge_condition, const std::string &edge, bool boundary_condition )
{
	patchTEdgeCondition(findTObject<TEdgeCondition>(edge_condition), edge, boundary_condition);
}

void TFactory::patchTFace( const TFacePtr &face, const std::vector<std::string> &link_loop, const std::vector<std::string> &nodes )
{
	std::vector<std::string>::const_iterator iter;
	for (iter = link_loop.begin(); iter != link_loop.end(); iter++)
	{
		face->addLink(findTObject<TLink>(*iter));
	}
	for (iter = nodes.begin(); iter != nodes.end(); iter++)
	{
		face->addBlendingNode(findTObject<TNodeV4>(*iter));
	}
}

void TFactory::patchTFace( const std::string &face, const std::vector<std::string> &link_loop, const std::vector<std::string> &nodes )
{
	patchTFace(findTObject<TFace>(face), link_loop, nodes);
}

void TFactory::patchTNode( const TNodePtr &node, const std::string &mapper, const std::string &point )
{
	node->setTMappableObject(findTObject<TMappableObject>(mapper));
	node->setTPoint(findTObject<TPoint>(point));
}

void TFactory::patchTNodeV4( const TNodeV4Ptr &node_v4,  const std::string &mapper, const std::string &point, const std::string &north, const std::string &west, const std::string &south, const std::string &east )
{
	patchTNode(node_v4, mapper, point);
	node_v4->setNeighbours(findTObject<TNodeV4>(north), findTObject<TNodeV4>(west), findTObject<TNodeV4>(south), findTObject<TNodeV4>(east));
}

void TFactory::patchTNodeV4( const std::string &node_v4, const std::string &mapper, const std::string &point, const std::string &north, const std::string &west, const std::string &south, const std::string &east )
{
	patchTNodeV4(findTObject<TNodeV4>(node_v4), mapper, point, north, west, south, east);
}

void TFactory::patchTPoint( const TPointPtr &point, const std::string &node )
{
	point->setTNode(findTObject<TNodeV4>(node));
}

void TFactory::patchTPoint( const std::string &point, const std::string &node )
{
	patchTPoint(findTObject<TPoint>(point), node);
}

void TFactory::findTObjectNames( std::vector<std::string> &names, TObjType type )
{
	_finder->findObjectNamesByType(names, type);
}

TSplinePtr TFactory::findTSpline()
{
	return _finder->findTSpline();
}

void TFactory::prepareImageConnect()
{
	TSplinePtr spline = findTSpline();
	TNodV4Vector nodes;
	_finder->findObjects<TNodeV4>(nodes);
	TNodV4VIterator iter;
	for (iter=nodes.begin();iter!=nodes.end();iter++)
	{
		TNodeV4Ptr node = *iter;
		TFacVector faces;
		TExtractor::extractTFacesFromTNodeV4(node, faces, spline->getSDegree());

		TFacVIterator fiter;
		for (fiter=faces.begin();fiter!=faces.end();fiter++)
		{
			TFacePtr face = *fiter;
			if (face) face->addBlendingNode(node);
		}
	}
}

TLinkPtr TFactory::findTLinkByStartEndVertices( const TVertexPtr &start, const TVertexPtr &end )
{
	TLnkVector links;
	_finder->findObjects<TLink>(links);

	TLnkVIterator link_iter = std::find_if(links.begin(), links.end(), 
		TLinkVisitorCheckStartEndVertices(start, end));

	if (link_iter != links.end())
	{
		return *link_iter;
	}
	else
	{
		return 0;
	}
}

void TFactory::prepareTJunctions()
{
	TVtxVector vertices;
	_finder->findObjects<TVertex>(vertices);
	std::for_each(vertices.begin(), vertices.end(), TVertexVisitorCheckTJunctions());
}

void TFactory::prepareTNodeHalfLinkages()
{
	TVtxVector vertices;
	_finder->findObjects<TVertex>(vertices);
	std::for_each(vertices.begin(), vertices.end(), TVertexVisitorCheckTNodes());
}

TGroupPtr TFactory::findTGroup()
{
	return _objects;
}

#ifdef use_namespace
}
#endif