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

#include <tspline.h>
#include <extractor.h>


#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

int TObject::_obj_count = 0;

TObject::TObject(const std::string & name /* = "" */) : 
	_name(name), _physical_id(_obj_count), _logical_id(0)
{
	_obj_count++;
}

TObject::~TObject()
{

}

TObjectPtr TObject::asTObject()
{
	return castPtr<TObject>(shared_from_this());
}

TGroup::TGroup( const std::string & name /*= ""*/ ) :
	TObject(name)
{

}

TGroup::~TGroup()
{

}

TGroupPtr TGroup::asTGroup()
{
	return castPtr<TGroup>(shared_from_this());
}

bool TGroup::addObject( const TObjectPtr & object )
{
	_objects.push_back(object);
	return true;
}

bool TGroup::insertObject( unsigned int index, const TObjectPtr & object )
{
	_objects.insert(_objects.begin()+index, object);
	return true;
}

bool TGroup::removeObject( const TObjectPtr & object )
{
	TObjVIterator enditer;
	enditer = std::remove(_objects.begin(), _objects.end(), object);
	_objects.erase(enditer, _objects.end());
	return true;
}

bool TGroup::removeObject( unsigned int pos, unsigned int num /*= 1*/ )
{
	_objects.erase(_objects.begin() + pos, _objects.begin() + pos + num);
	return true;
}

bool TGroup::replaceObject( const TObjectPtr & old_object, \
						   const TObjectPtr & new_object )
{
	std::replace(_objects.begin(), _objects.end(), old_object, new_object);
	return true;
}

unsigned int TGroup::size() const
{
	return _objects.size();
}

TObjVIterator TGroup::iteratorBegin()
{
	return _objects.begin();
}

TObjVIterator TGroup::iteratorEnd()
{
	return _objects.end();
}

TMappableObject::TMappableObject( const std::string & name /*= ""*/ ) :
	TObject(name)
{

}

TMappableObject::~TMappableObject()
{

}

TMappableObjectPtr TMappableObject::asTMappableObject()
{
	return castPtr<TMappableObject>(shared_from_this());
}

void TMappableObject::addNode( const TNodePtr &node )
{
	_nodes.push_back(node);
}

void TMappableObject::removeNode( const TNodePtr &node )
{
	_nodes.erase(std::remove(_nodes.begin(), _nodes.end(), node), _nodes.end());
}

TNodVIterator TMappableObject::nodeIteratorBegin()
{
	return _nodes.begin();
}

TNodVIterator TMappableObject::nodeIteratorEnd()
{
	return _nodes.end();
}

long TMappableObject::sizeNodes() const
{
	return _nodes.size();
}

TVertex::TVertex(const std::string & name /* = "" */,
				 Real s /* = 0.0 */, 
				 Real t /* = 0.0 */) :
	TMappableObject(name), 
		_s(s),
		_t(t)
{

}

TVertexPtr TVertex::asTVertex()
{
	return castPtr<TVertex>(shared_from_this());
}

void TVertex::setNeighbours( const TLinkPtr &north, 
							const TLinkPtr &west, 
							const TLinkPtr &south, 
							const TLinkPtr &east )
{
	_north = north;
	_west = west;
	_south = south;
	_east = east;
}

TLinkPtr TVertex::checkNeighborhood( const TVertexPtr &vertex )
{
	if (!vertex) return 0;
	if (vertex == getEndVertex(_north)) return _north;
	if (vertex == getEndVertex(_west)) return _west;
	if (vertex == getEndVertex(_south)) return _south;
	if (vertex == getEndVertex(_east)) return _east;
}

TVertexPtr TVertex::getEndVertex( const TLinkPtr &link )
{
	if (link)
		return link->getEndVertex();
	else
		return 0;
}

int TVertex::numberOfNeighbors() const
{
	int number = 0;
	if (_north) number++;
	if (_west) number++;
	if (_south) number++;
	if (_east) number++;
	return number;
}

void TVertex::setNorth( const TLinkPtr &north )
{
	_north = north;
}

void TVertex::setWest( const TLinkPtr &west )
{
	_west = west;
}

void TVertex::setSouth( const TLinkPtr &south )
{
	_south = south;
}

void TVertex::setEast( const TLinkPtr &east )
{
	_east = east;
}

TVertexPtr TVertex::getNorthTVertex() const
{
	if (_north)
	{
		return _north->getEndVertex();
	}
	else
	{
		return 0;
	}
}

TVertexPtr TVertex::getWestTVertex() const
{
	if (_west)
	{
		return _west->getEndVertex();
	}
	else
	{
		return 0;
	}
}

TVertexPtr TVertex::getSouthTVertex() const
{
	if (_south)
	{
		return _south->getEndVertex();
	}
	else
	{
		return 0;
	}
}

TVertexPtr TVertex::getEastTVertex() const
{
	if (_east)
	{
		return _east->getEndVertex();
	}
	else
	{
		return 0;
	}
}

Real TVertex::width()
{
	return 0.0;
}

Real TVertex::height()
{
	return 0.0;
}

Real TVertex::area()
{
	return 0.0;
}

Parameter TVertex::northWest()
{
	return Parameter(_s, _t);
}

Parameter TVertex::southEast()
{
	return Parameter(_s, _t);
}

TEdge::TEdge( const std::string & name /*= ""*/) :
	TMappableObject(name), _boundary(false)
{

}

TEdgePtr TEdge::asTEdge()
{
	return castPtr<TEdge>(shared_from_this());
}

TVertexPtr TEdge::getNextVertex( bool orientation ) const
{
	return orientation? getEndVertex() : getStartVertex();
}

Real TEdge::length() const
{
	Real ds = _start->getS() - _end->getS();
	Real dt = _start->getT() - _end->getT();

	return sqrt(ds*ds + dt*dt);
}

bool TEdge::toNorth() const
{
	Real dt = _end->getT() - _start->getT();
	if (fabs(dt) > M_EPS)
	{
		return dt > 0.0;
	}
	else
	{
		return false;
	}
}

bool TEdge::toWest() const
{
	Real ds = _end->getS() - _start->getS();
	if (fabs(ds) > M_EPS)
	{
		return ds < 0.0;
	}
	else
	{
		return false;
	}
}

bool TEdge::toSouth() const
{
	Real dt = _end->getT() - _start->getT();
	if (fabs(dt) > M_EPS)
	{
		return dt < 0.0;
	}
	else
	{
		return false;
	}
}

bool TEdge::toEast() const
{
	Real ds = _end->getS() - _start->getS();
	if (fabs(ds) > M_EPS)
	{
		return ds > 0.0;
	}
	else
	{
		return false;
	}
}

Real TEdge::width()
{
	if (toNorth() || toSouth())
	{
		return 0.0;
	}
	else
	{
		return length();
	}
}

Real TEdge::height()
{
	if (toWest() || toEast())
	{
		return length();
	}
	else
	{
		return 0.0;
	}
}

Real TEdge::area()
{
	return 0.0;
}

Parameter TEdge::northWest()
{
	if (toNorth() || toWest())
	{
		return Parameter(_end->getS(), _end->getT());
	}
	else if(toSouth() || toEast())
	{
		return Parameter(_start->getS(), _start->getT());
	}
}

Parameter TEdge::southEast()
{
	if (toNorth() || toWest())
	{
		return Parameter(_start->getS(), _start->getT());
	}
	else if(toSouth() || toEast())
	{
		return Parameter(_end->getS(), _end->getT());
	}
}

TLink::TLink(const std::string & name /* = "" */) :
	TObject(name)
{

}

TLinkPtr TLink::asTLink()
{
	return castPtr<TLink>(shared_from_this());
}

void TLink::setOrientedEdge( const TEdgePtr &edge, bool orientation /*= true*/ )
{
	_edge = edge;
	_orientation = orientation;
}

TVertexPtr TLink::getStartVertex() const
{
	if (_edge) 
	{
		if (_orientation)
			return _edge->getStartVertex();
		else
			return _edge->getEndVertex();
	}
	else
	{
		return 0;
	}
}

TVertexPtr TLink::getEndVertex() const
{
	if (_edge)
	{
		if (_orientation)
			return _edge->getEndVertex();
		else
			return _edge->getStartVertex();
	}
	else
	{
		return 0;
	}
}

TFacePtr TLink::getLeftFace() const
{
	if (_edge)
	{
		if (_orientation)
			return _edge->getLeftFace();
		else
			return _edge->getRightFace();
	}
	else
	{
		return 0;
	}
}

TFacePtr TLink::getRightFace() const
{
	if (_edge)
	{
		if (_orientation)
			return _edge->getRightFace();
		else
			return _edge->getLeftFace();
	}
	else
	{
		return 0;
	}
}

Real TLink::length() const
{
	if (_edge)
	{
		return _edge->length();
	}
	return 0.0;
}

bool TLink::toNorth() const
{
	if (_orientation)
	{
		return _edge->toNorth();
	}
	else
	{
		return _edge->toSouth();
	}
}

bool TLink::toWest() const
{
	if (_orientation)
	{
		return _edge->toWest();
	}
	else
	{
		return _edge->toEast();
	}
}

bool TLink::toSouth() const
{
	if (_orientation)
	{
		return _edge->toSouth();
	}
	else
	{
		return _edge->toNorth();
	}
}

bool TLink::toEast() const
{
	if (_orientation)
	{
		return _edge->toEast();
	}
	else
	{
		return _edge->toWest();
	}
}

bool TLink::isBoundary() const
{
	return _edge->isBoundary();
}

TLinkLoop::TLinkLoop()
{

}

TLinkLoop::~TLinkLoop()
{

}

void TLinkLoop::organize()
{
}

void TLinkLoop::addLink( const TLinkPtr &link )
{
	_links.push_back(link);
}

void TLinkLoop::findNorthLinks( TLnkVector &north_links )
{
	TLnkLIterator iter;
	for (iter=_links.begin();iter!=_links.end();iter++)
	{
		TLinkPtr link = (*iter);
		if (link->toNorth())
		{
			north_links.push_back(link);
		}
	}
}

void TLinkLoop::findWestLinks( TLnkVector &west_links )
{
	TLnkLIterator iter;
	for (iter=_links.begin();iter!=_links.end();iter++)
	{
		TLinkPtr link = (*iter);
		if (link->toWest())
		{
			west_links.push_back(link);
		}
	}
}

void TLinkLoop::findSouthLinks( TLnkVector &south_links )
{
	TLnkLIterator iter;
	for (iter=_links.begin();iter!=_links.end();iter++)
	{
		TLinkPtr link = (*iter);
		if (link->toSouth())
		{
			south_links.push_back(link);
		}
	}
}

void TLinkLoop::findEastLinks( TLnkVector &east_links )
{
	TLnkLIterator iter;
	for (iter=_links.begin();iter!=_links.end();iter++)
	{
		TLinkPtr link = (*iter);
		if (link->toEast())
		{
			east_links.push_back(link);
		}
	}
}

TLnkLIterator TLinkLoop::linkIteratorBegin()
{
	return _links.begin();
}

TLnkLIterator TLinkLoop::linkIteratorEnd()
{
	return _links.end();
}

TFace::TFace(const std::string & name /* = "" */) :
	TMappableObject(name)
{
	_link_loop = makePtr<TLinkLoop>();
}

TFacePtr TFace::asTFace()
{
	return castPtr<TFace>(shared_from_this());
}

void TFace::addLink( const TLinkPtr link )
{
	_link_loop->addLink(link);
}

void TFace::addBlendingNode( const TNodePtr node )
{
	_blending_nodes.push_back(node);
}

void TFace::findNorthLinks( TLnkVector &links )
{
	_link_loop->findNorthLinks(links);
}

void TFace::findWestLinks( TLnkVector &links )
{
	_link_loop->findWestLinks(links);
}

void TFace::findSouthLinks( TLnkVector &links )
{
	_link_loop->findSouthLinks(links);
}

void TFace::findEastLinks( TLnkVector &links )
{
	_link_loop->findEastLinks(links);
}

Real TFace::width()
{
	TLnkVector links;
	findEastLinks(links);
	Real lengths = 0.0;
	TLnkVIterator iter;
	for (iter=links.begin();iter!=links.end();iter++)
	{
		lengths += (*iter)->length();
	}
	return lengths;
}

Real TFace::height()
{
	TLnkVector links;
	findNorthLinks(links);
	Real lengths = 0.0;
	TLnkVIterator iter;
	for (iter=links.begin();iter!=links.end();iter++)
	{
		lengths += (*iter)->length();
	}
	return lengths;
}

Real TFace::area()
{
	return width() * height();
}

void TFace::findNorthFaces( TFacVector &faces )
{
	TLnkVector links;
	findWestLinks(links);
	findRightFaces(links, faces);
}

void TFace::findWestFaces( TFacVector &faces )
{
	TLnkVector links;
	findSouthLinks(links);
	findRightFaces(links, faces);
}

void TFace::findSouthFaces( TFacVector &faces )
{
	TLnkVector links;
	findEastLinks(links);
	findRightFaces(links, faces);
}

void TFace::findEastFaces( TFacVector &faces )
{
	TLnkVector links;
	findNorthLinks(links);
	findRightFaces(links, faces);
}

void TFace::findRightFaces( const TLnkVector &links, TFacVector &faces )
{
	TFacSet sfaces;
	TLnkVConstIterator iter;
	for (iter=links.begin();iter!=links.end();iter++)
	{
		TLinkPtr link = *iter;
		sfaces.insert(link->getRightFace());
	}
	faces.resize(sfaces.size());
	std::copy(sfaces.begin(), sfaces.end(), faces.begin());
}

TLnkLIterator TFace::linkIteratorBegin()
{
	return _link_loop->linkIteratorBegin();
}

TLnkLIterator TFace::linkIteratorEnd()
{
	return _link_loop->linkIteratorEnd();
}

TNodVIterator TFace::blendingNodeIteratorBegin()
{
	return _blending_nodes.begin();
}

TNodVIterator TFace::blendingNodeIteratorEnd()
{
	return _blending_nodes.end();
}

Parameter TFace::northWest()
{
	TVertexPtr vertex = TExtractor::extractNorthWestTVertexFromTFace(asTFace());
	return TExtractor::extractParameterFromTVertex(vertex);
}

Parameter TFace::southEast()
{
	TVertexPtr vertex = TExtractor::extractSouthEastTVertexFromTFace(asTFace());
	return TExtractor::extractParameterFromTVertex(vertex);
}

TEdgeCondition::TEdgeCondition(const std::string & name /* = "" */) :
	TObject(name)
{

}

TEdgeConditionPtr TEdgeCondition::asTEdgeCondition()
{
	return castPtr<TEdgeCondition>(shared_from_this());
}

void TEdgeCondition::setEdgeCondition( const TEdgePtr &edge, bool boundary_condition )
{
	_edge = edge;
	_boundary_condition = boundary_condition;
	if (_edge)
	{
		_edge->setBoundary(boundary_condition);
	}
}

TImage::TImage(const std::string & name /* = "" */) :
	TObject(name)
{

}

TImagePtr TImage::asTImage()
{
	return castPtr<TImage>(shared_from_this());
}

void TImage::addFace( const TFacePtr &face )
{
	_faces.push_back(face);
}

void TImage::addEdge( const TEdgePtr &edge )
{
	_edges.push_back(edge);
}

void TImage::addLink( const TLinkPtr &link )
{
	_links.push_back(link);
}

void TImage::addVertex( const TVertexPtr &vertex )
{
	_vertices.push_back(vertex);
}

TFacVIterator TImage::faceIteratorBegin()
{
	return _faces.begin();
}

TFacVIterator TImage::faceIteratorEnd()
{
	return _faces.end();
}

TLnkVIterator TImage::linkIteratorBegin()
{
	return _links.begin();
}

TLnkVIterator TImage::linkIteratorEnd()
{
	return _links.end();
}

TVtxVIterator TImage::vertexIteratorBegin()
{
	return _vertices.begin();
}

TVtxVIterator TImage::vertexIteratorEnd()
{
	return _vertices.end();
}

TEdgVIterator TImage::edgeIteratorBegin()
{
	return _edges.begin();
}

TEdgVIterator TImage::edgeIteratorEnd()
{
	return _edges.end();
}

TNode::TNode(const std::string & name /* = "" */) :
	TObject(name)
{

}

TNodePtr TNode::asTNode()
{
	return castPtr<TNode>(shared_from_this());
}

void TNode::setTMappableObject( const TMappableObjectPtr &mapper )
{
	_mapper = mapper;
	if (_mapper)
	{
		_mapper->addNode(asTNode());
	}
}

void TNode::setTVertex( const TVertexPtr &vertex )
{
	setTMappableObject(vertex);
}

void TNode::setTEdge( const TEdgePtr &edge )
{
	setTMappableObject(edge);
}

void TNode::setTFace( const TFacePtr &face )
{
	setTMappableObject(face);
}

void TNode::setTPoint( const TPointPtr &point )
{
	_point = point;
}

TNodeV4::TNodeV4(const std::string & name /* = "" */) :
	TNode(name)
{

}

TNodeV4Ptr TNodeV4::asTNodeV4()
{
	return castPtr<TNodeV4>(shared_from_this());
}

void TNodeV4::setNeighbours( const TNodeV4Ptr north, const TNodeV4Ptr west, const TNodeV4Ptr south, const TNodeV4Ptr east )
{
	_north = north;
	_west = west;
	_south = south;
	_east = east;
}

TConnect::TConnect(const std::string & name /* = "" */) :
	TGroup(name)
{

}

TConnectPtr TConnect::asTConnect()
{
	return castPtr<TConnect>(shared_from_this());
}

TPoint::TPoint(const std::string & name /* = "" */,
			   Real x /* = 0.0 */, 
			   Real y /* = 0.0 */,
			   Real z /* = 0.0 */, 
			   Real w /* = 1.0 */) :
	TObject(name),
		_x(x),
		_y(y),
		_z(z),
		_w(w)
{

}

TPointPtr TPoint::asTPoint()
{
	return castPtr<TPoint>(shared_from_this());
}

TPointset::TPointset(const std::string & name /* = "" */) :
	TGroup(name)
{

}

TPointsetPtr TPointset::asTPointset()
{
	return castPtr<TPointset>(shared_from_this());
}


// TSpline::TSpline(const std::string & name /* = "" */, 
// 				 int degree /* = 3 */, 
// 				 bool force_bezier_end_condition /* = false */, 
// 				 bool cap_type /* = false */, 
// 				 bool star_smoothness /* = true */) :
TSpline::TSpline(const std::string & name /* = "" */, 
				 int degree /* = 3 */, 
				 bool force_bezier_end_condition /* = false */) :
	TObject(name), 
		_s_degree(degree),
		_t_degree(degree),
		_force_bezier_end_condition(force_bezier_end_condition) //,
// 		_cap_type(cap_type),
// 		_star_smoothness(star_smoothness)
{

}

TSplinePtr TSpline::asTSpline()
{
	return castPtr<TSpline>(shared_from_this());
}

#ifdef use_namespace
}
#endif