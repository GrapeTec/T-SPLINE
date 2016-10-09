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

#include <extractor.h>
#include <visitor.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

TNodeV4Ptr TExtractor::extractWestFromTNodeV4( const TNodeV4Ptr &node, TNodeV4Ptr def /*= 0*/ )
{
	if (node) 
	{
		TNodeV4Ptr wnode = node->getWest();
		if (wnode)
			return wnode;
		else
			return def;
	}
	return def;
}

TNodeV4Ptr TExtractor::extractEastFromTNodeV4( const TNodeV4Ptr &node, TNodeV4Ptr def /*= 0*/ )
{
	if (node) 
	{
		TNodeV4Ptr enode = node->getEast();
		if (enode)
			return enode;
		else
			return def;
	}
	return def;
}

TNodeV4Ptr TExtractor::extractNorthFromTNodeV4( const TNodeV4Ptr &node, TNodeV4Ptr def /*= 0*/ )
{
	if (node)
	{
		TNodeV4Ptr nnode = node->getNorth();
		if (nnode)
			return nnode;
		else
			return def;
	}
	return def;
}

TNodeV4Ptr TExtractor::extractSouthFromTNodeV4( const TNodeV4Ptr &node, TNodeV4Ptr def /*= 0*/ )
{
	if (node) 
	{
		TNodeV4Ptr snode = node->getSouth();
		if (snode)
			return snode;
		else
			return def;
	}
	return def;
}

void TExtractor::extractCrossFromTNodeV4( const TNodeV4Ptr &node, TNodeV4CrossPtr &node_cross, int degree_s, int degree_t)
{
	if (degree_s == 3 && degree_t == 3)
	{
		TNodeV4Ptr kh1, kh2, kh3, kh4, kh5;
		TNodeV4Ptr kv1, kv2, kv3, kv4, kv5;
		kh3 = node; kv3 = node;

		kh2 = extractNonNullWestFromTNodeV4(kh3); kh1 = extractNonNullWestFromTNodeV4(kh2);
		kh4 = extractNonNullEastFromTNodeV4(kh3); kh5 = extractNonNullEastFromTNodeV4(kh4);

		kv2 = extractNonNullNorthFromTNodeV4(kv3); kv1 = extractNonNullNorthFromTNodeV4(kv2);
		kv4 = extractNonNullSouthFromTNodeV4(kv3); kv5 = extractNonNullSouthFromTNodeV4(kv4);

		node_cross->setNodeCenter(node);
		node_cross->addNodeNorth(kv2); node_cross->addNodeNorth(kv1); 
		node_cross->addNodeWest(kh2); node_cross->addNodeWest(kh1);
		node_cross->addNodeSouth(kv4); node_cross->addNodeSouth(kv5);
		node_cross->addNodeEast(kh4); node_cross->addNodeEast(kh5);
		node_cross->prepareRelationships();
	}
	else if (degree_s == 2 && degree_t == 2)
	{
		TNodeV4Ptr kh1, kh2, kh3;
		TNodeV4Ptr kv1, kv2, kv3;
		kh2 = node; kv2 = node;

		kh1 = extractNonNullWestFromTNodeV4(kh2);
		kh3 = extractNonNullEastFromTNodeV4(kh2);

		kv1 = extractNonNullNorthFromTNodeV4(kv2);
		kv3 = extractNonNullSouthFromTNodeV4(kv2);

		node_cross->setNodeCenter(node);
		node_cross->addNodeNorth(kv1);
		node_cross->addNodeWest(kh1);
		node_cross->addNodeSouth(kv3);
		node_cross->addNodeEast(kh3);
		node_cross->prepareRelationships();
	}
}

TNodeV4Ptr TExtractor::extractNonNullWestFromTNodeV4( const TNodeV4Ptr &node )
{
	return extractWestFromTNodeV4(node, node);
}

TNodeV4Ptr TExtractor::extractNonNullEastFromTNodeV4( const TNodeV4Ptr &node )
{
	return extractEastFromTNodeV4(node, node);
}

TNodeV4Ptr TExtractor::extractNonNullNorthFromTNodeV4( const TNodeV4Ptr &node )
{
	return extractNorthFromTNodeV4(node, node);
}

TNodeV4Ptr TExtractor::extractNonNullSouthFromTNodeV4( const TNodeV4Ptr &node )
{
	return extractSouthFromTNodeV4(node, node);
}

void TExtractor::extractTFacesFromTNodeV4Cross( const TNodeV4CrossPtr &node_cross, TFacVector &faces )
{
	if (!node_cross->isPrepared())
		node_cross->prepareRelationships();
	node_cross->copyTFaces(faces);
}

void TExtractor::extractUVKnotsFromTNodeV4( const TNodeV4Ptr &node_v4, std::vector<Real> &u_nodes, std::vector<Real> &v_nodes )
{
	TNodeV4Ptr kh1, kh2, kh3, kh4, kh5;
	TNodeV4Ptr kv1, kv2, kv3, kv4, kv5;
	kh3 = node_v4; kv3 = node_v4;

	kh2 = extractNonNullWestFromTNodeV4(kh3); kh1 = extractNonNullWestFromTNodeV4(kh2);
	kh4 = extractNonNullEastFromTNodeV4(kh3); kh5 = extractNonNullEastFromTNodeV4(kh4);

	kv2 = extractNonNullNorthFromTNodeV4(kv3); kv1 = extractNonNullNorthFromTNodeV4(kv2);
	kv4 = extractNonNullSouthFromTNodeV4(kv3); kv5 = extractNonNullSouthFromTNodeV4(kv4);

	if (kh1) u_nodes.push_back(kh1->getTVertex()->getS());
	if (kh2) u_nodes.push_back(kh2->getTVertex()->getS());
	if (kh3) u_nodes.push_back(kh3->getTVertex()->getS());
	if (kh4) u_nodes.push_back(kh4->getTVertex()->getS());
	if (kh5) u_nodes.push_back(kh5->getTVertex()->getS());

	if (kv5) v_nodes.push_back(kv5->getTVertex()->getT());
	if (kv4) v_nodes.push_back(kv4->getTVertex()->getT());
	if (kv3) v_nodes.push_back(kv3->getTVertex()->getT());
	if (kv2) v_nodes.push_back(kv2->getTVertex()->getT());
	if (kv1) v_nodes.push_back(kv1->getTVertex()->getT());
}

void TExtractor::extractRationalPointFromTNodeV4( const TNodeV4Ptr &node_v4, Point3D &point, Real &weight )
{
	TPointPtr tpoint = node_v4->getTPoint();
	point.x(tpoint->getX());
	point.y(tpoint->getY());
	point.z(tpoint->getZ());
	weight = tpoint->getW();
}

void TExtractor::extractTFacesFromTNodeV4( const TNodeV4Ptr &node, TFacVector &faces, int degree_s /*= 3*/, int degree_t /*= 3*/ )
{
	TNodeV4CrossPtr node_cross = makePtr<TNodeV4Cross>();
	extractCrossFromTNodeV4(node, node_cross, degree_s, degree_t);
	extractTFacesFromTNodeV4Cross(node_cross, faces);
}

TVertexPtr TExtractor::extractNorthEastTVertexFromTFace( const TFacePtr &face )
{
	TLnkLIterator iter;
	TLnkLIterator biter = face->linkIteratorBegin();
	TLnkLIterator eiter = face->linkIteratorEnd();

	TVertexPtr north_east = (*biter)->getStartVertex();

	TLnkVector links;
	face->findNorthLinks(links);
	north_east = links.back()->getEndVertex();

// 	for (iter=biter;iter!=eiter;iter++)
// 	{
// 		TLinkPtr link = *iter;
// 		TVertexPtr start = link->getStartVertex();
// 		if (isZero(start->getS()) >= isZero(north_east->getS()) && isZero(start->getT()) >= isZero(north_east->getT()))
// 		{
// 			north_east = start;
// 		}
// 		TVertexPtr end = link->getEndVertex();
// 		if (isZero(end->getS()) >= isZero(north_east->getS()) && isZero(end->getT()) >= isZero(north_east->getT()))
// 		{
// 			north_east = end;
// 		}
// 	}
	return north_east;
}

TVertexPtr TExtractor::extractNorthWestTVertexFromTFace( const TFacePtr &face )
{
	TLnkLIterator iter;
	TLnkLIterator biter = face->linkIteratorBegin();
	TLnkLIterator eiter = face->linkIteratorEnd();

	TVertexPtr north_west = (*biter)->getStartVertex();

	TLnkVector links;
	face->findWestLinks(links);
	north_west = links.back()->getEndVertex();

// 	for (iter=biter;iter!=eiter;iter++)
// 	{
// 		TLinkPtr link = *iter;
// 		TVertexPtr start = link->getStartVertex();
// 		if (isZero(start->getS()) <= isZero(north_west->getS()) && isZero(start->getT()) >= isZero(north_west->getT()))
// 		{
// 			north_west = start;
// 		}
// 		TVertexPtr end = link->getEndVertex();
// 		if (isZero(end->getS()) <= isZero(north_west->getS()) && isZero(end->getT()) >= isZero(north_west->getT()))
// 		{
// 			north_west = end;
// 		}
// 	}
	return north_west;
}

TVertexPtr TExtractor::extractSouthWestTVertexFromTFace( const TFacePtr &face )
{
	TLnkLIterator iter;
	TLnkLIterator biter = face->linkIteratorBegin();
	TLnkLIterator eiter = face->linkIteratorEnd();

	TVertexPtr south_west = (*biter)->getStartVertex();

	TLnkVector links;
	face->findSouthLinks(links);
	south_west = links.back()->getEndVertex();

// 	for (iter=biter;iter!=eiter;iter++)
// 	{
// 		TLinkPtr link = *iter;
// 		TVertexPtr start = link->getStartVertex();
// 		if (isZero(start->getS()) <= isZero(south_west->getS()) && isZero(start->getT()) <= isZero(south_west->getT()))
// 		{
// 			south_west = start;
// 		}
// 		TVertexPtr end = link->getEndVertex();
// 		if (isZero(end->getS()) <= isZero(south_west->getS()) && isZero(end->getT()) <= isZero(south_west->getT()))
// 		{
// 			south_west = end;
// 		}
// 	}
	return south_west;
}

TVertexPtr TExtractor::extractSouthEastTVertexFromTFace( const TFacePtr &face )
{
	TLnkLIterator iter;
	TLnkLIterator biter = face->linkIteratorBegin();
	TLnkLIterator eiter = face->linkIteratorEnd();

	TVertexPtr south_east = (*biter)->getStartVertex();

	TLnkVector links;
	face->findEastLinks(links);
	south_east = links.back()->getEndVertex();

// 	for (iter=biter;iter!=eiter;iter++)
// 	{
// 		TLinkPtr link = *iter;
// 		TVertexPtr start = link->getStartVertex();
// 		if (isZero(start->getS()) >= isZero(south_east->getS()) && isZero(start->getT()) <= isZero(south_east->getT()))
// 		{
// 			south_east = start;
// 		}
// 		TVertexPtr end = link->getEndVertex();
// 		if (isZero(end->getS()) >= isZero(south_east->getS()) && isZero(end->getT()) <= isZero(south_east->getT()))
// 		{
// 			south_east = end;
// 		}
// 	}
	return south_east;
}

Parameter TExtractor::extractParameterFromTVertex( const TVertexPtr &vertex )
{
	if (vertex)
	{
		return Parameter(vertex->getS(), vertex->getT());
	}
	else
	{
		return Parameter(0.0, 0.0);
	}
}

TSPLINE::Parameter TExtractor::extractParameterFromTSpline(const TSplinePtr &spline)
{
	Parameter pa(0.0, 0.0);
	TImagePtr timage = spline->getTImage();
	for (TFacVIterator it = timage->faceIteratorBegin();
		it!=timage->faceIteratorEnd();it++)
	{
		if((*it)->southEast().s() > pa.s())
			pa.s((*it)->southEast().s());
		else if((*it)->northWest().s() > pa.s())
			pa.s((*it)->northWest().s());

		if((*it)->southEast().t() > pa.t())
			pa.t((*it)->southEast().t());
		else if((*it)->northWest().t() > pa.t())
			pa.t((*it)->northWest().t());
	}
	return pa;
}

TVtxVector TExtractor::extractTVerticesFromTFace( const TFacePtr &face )
{
	TVtxVector vertices;
	TLnkLIterator iter;
	for (iter=face->linkIteratorBegin();iter!=face->linkIteratorEnd();iter++)
	{
		TLinkPtr link = *iter;
		TVertexPtr vertex_start = link->getStartVertex();
		vertices.push_back(vertex_start);
	}
	return vertices;
}

TVertexPtr TExtractor::extractTVertexFromTFace( const TFacePtr &face, const Parameter &parameter )
{
	TVtxVector vertices = extractTVerticesFromTFace(face);
	TVtxVIterator iter = std::find_if(vertices.begin(), vertices.end(), TVertexVisitorCheckParameterCoincide(parameter));
	if (iter != vertices.end())
	{
		return *iter;
	}
	else
	{
		return 0;
	}
}

TNodeV4Ptr TExtractor::extractNorthNodeFromTVertex( const TVertexPtr &vertex )
{
	TNodVIterator node_begin = vertex->nodeIteratorBegin();
	TNodVIterator node_end = vertex->nodeIteratorEnd();

	TNodVector norths;
	extractNorthNodesFromTVertex(vertex, norths);

	if (norths.empty())
	{
		return 0;
	}
	else if (norths.size() == 1)
	{
		return norths[0]->asTNodeV4();
	}
	else
	{
		TNodeV4Ptr node_v4 = norths[0]->asTNodeV4();
		TNodeV4Ptr north = node_v4->getNorth();
		if (north && north->getSouth())
		{
			return north->getSouth();
		}
		else
		{
			TNodeV4Ptr middle = extractMiddleNodeFromTVertex(vertex, E_NORTH);
			TNodeV4Ptr col = middle;
			while ( col && col->getNorth() &&
				(node_end != std::find(node_begin, node_end, col->getNorth())) )
			{
				col = col->getNorth();
			}
			return col;
		}
	}
}

TNodeV4Ptr TExtractor::extractWestNodeFromTVertex( const TVertexPtr &vertex )
{
	TNodVIterator node_begin = vertex->nodeIteratorBegin();
	TNodVIterator node_end = vertex->nodeIteratorEnd();

	TNodVector wests;
	extractNorthNodesFromTVertex(vertex, wests);

	if (wests.empty())
	{
		return 0;
	}
	else if (wests.size() == 1)
	{
		return wests[0]->asTNodeV4();
	}
	else
	{
		TNodeV4Ptr node_v4 = wests[0]->asTNodeV4();
		TNodeV4Ptr west = node_v4->getWest();
		if (west && west->getEast())
		{
			return west->getEast();
		}
		else
		{
			TNodeV4Ptr middle = extractMiddleNodeFromTVertex(vertex, E_WEST);
			TNodeV4Ptr row = middle;
			while ( row && row->getWest() &&
				(node_end != std::find(node_begin, node_end, row->getWest())) )
			{
				row = row->getWest();
			}
			return row;
		}
	}
}

TNodeV4Ptr TExtractor::extractSouthNodeFromTVertex( const TVertexPtr &vertex )
{
	TNodVIterator node_begin = vertex->nodeIteratorBegin();
	TNodVIterator node_end = vertex->nodeIteratorEnd();

	TNodVector souths;
	extractNorthNodesFromTVertex(vertex, souths);

	if (souths.empty())
	{
		return 0;
	}
	else if (souths.size() == 1)
	{
		return souths[0]->asTNodeV4();
	}
	else
	{
		TNodeV4Ptr node_v4 = souths[0]->asTNodeV4();
		TNodeV4Ptr south = node_v4->getSouth();
		if (south && south->getNorth())
		{
			return south->getNorth();
		}
		else
		{
			TNodeV4Ptr middle = extractMiddleNodeFromTVertex(vertex, E_SOUTH);
			TNodeV4Ptr col = middle;
			while ( col && col->getSouth() &&
				(node_end != std::find(node_begin, node_end, col->getSouth())) )
			{
				col = col->getSouth();
			}
			return col;
		}
	}
}

TNodeV4Ptr TExtractor::extractEastNodeFromTVertex( const TVertexPtr &vertex )
{
	TNodVIterator node_begin = vertex->nodeIteratorBegin();
	TNodVIterator node_end = vertex->nodeIteratorEnd();

	TNodVector easts;
	extractNorthNodesFromTVertex(vertex, easts);

	if (easts.empty())
	{
		return 0;
	}
	else if (easts.size() == 1)
	{
		return easts[0]->asTNodeV4();
	}
	else
	{
		TNodeV4Ptr node_v4 = easts[0]->asTNodeV4();
		TNodeV4Ptr east = node_v4->getEast();
		if (east && east->getWest())
		{
			return east->getWest();
		}
		else
		{
			TNodeV4Ptr middle = extractMiddleNodeFromTVertex(vertex, E_EAST);
			TNodeV4Ptr row = middle;
			while ( row && row->getEast() &&
				(node_end != std::find(node_begin, node_end, row->getEast())) )
			{
				row = row->getEast();
			}
			return row;
		}
	}
}

void TExtractor::extractNorthNodesFromTVertex( const TVertexPtr &vertex, TNodVector &nodes )
{
	TNodVIterator node_begin = vertex->nodeIteratorBegin();
	TNodVIterator node_end = vertex->nodeIteratorEnd();

	for (TNodVIterator iter = node_begin;iter!=node_end;iter++)
	{
		TNodeV4Ptr node_v4 = castPtr<TNodeV4>(*iter);
		TNodeV4Ptr north = node_v4->getNorth();
		if (!north || node_end == std::find(node_begin, node_end, north))
		{
			nodes.push_back(node_v4);
		}
	}
}

void TExtractor::extractWestNodesFromTVertex( const TVertexPtr &vertex, TNodVector &nodes )
{
	TNodVIterator node_begin = vertex->nodeIteratorBegin();
	TNodVIterator node_end = vertex->nodeIteratorEnd();

	for (TNodVIterator iter = node_begin;iter!=node_end;iter++)
	{
		TNodeV4Ptr node_v4 = castPtr<TNodeV4>(*iter);
		TNodeV4Ptr west = node_v4->getWest();
		if (!west || node_end == std::find(node_begin, node_end, west))
		{
			nodes.push_back(node_v4);
		}
	}
}

void TExtractor::extractSouthNodesFromTVertex( const TVertexPtr &vertex, TNodVector &nodes )
{
	TNodVIterator node_begin = vertex->nodeIteratorBegin();
	TNodVIterator node_end = vertex->nodeIteratorEnd();

	for (TNodVIterator iter = node_begin;iter!=node_end;iter++)
	{
		TNodeV4Ptr node_v4 = castPtr<TNodeV4>(*iter);
		TNodeV4Ptr south = node_v4->getSouth();
		if (!south || node_end == std::find(node_begin, node_end, south))
		{
			nodes.push_back(node_v4);
		}
	}
}

void TExtractor::extractEastNodesFromTVertex( const TVertexPtr &vertex, TNodVector &nodes )
{
	TNodVIterator node_begin = vertex->nodeIteratorBegin();
	TNodVIterator node_end = vertex->nodeIteratorEnd();

	for (TNodVIterator iter = node_begin;iter!=node_end;iter++)
	{
		TNodeV4Ptr node_v4 = castPtr<TNodeV4>(*iter);
		TNodeV4Ptr east = node_v4->getEast();
		if (!east || node_end == std::find(node_begin, node_end, east))
		{
			nodes.push_back(node_v4);
		}
	}
}

TNodeV4Ptr TExtractor::extractMiddleNodeFromTVertex( const TVertexPtr &vertex, int ttype /*= E_CENTER*/ )
{
	TNodVIterator node_begin = vertex->nodeIteratorBegin();
	TNodVIterator node_end = vertex->nodeIteratorEnd();
	switch (ttype)
	{
	case E_CENTER:
	case E_SOUTH:
	case E_EAST:
		{
			TNodVector norths, wests;
			extractNorthNodesFromTVertex(vertex, norths);
			TNodeV4Ptr first_north = norths[norths.size()/2]->asTNodeV4();
			TNodeV4Ptr north_north = first_north->getNorth();
			TNodeV4Ptr north = north_north->getSouth();

			extractWestNodesFromTVertex(vertex, wests);
			TNodeV4Ptr first_west = wests[wests.size()/2]->asTNodeV4();
			TNodeV4Ptr west_west = first_west->getWest();
			TNodeV4Ptr west = west_west->getEast();

			TNodeV4Ptr row = west;
			for (int i=0;(i<norths.size() && row);i++)
			{
				TNodeV4Ptr col = north;
				for (int j=0;(j<wests.size() && col);j++)
				{
					if (row == col)
					{
						return row;
					}
					col = col->getSouth();
				}
				row = row->getEast();
			}
		}
		break;
	case E_NORTH:
	case E_WEST:
		{
			TNodVector souths, easts;
			extractSouthNodesFromTVertex(vertex, souths);
			TNodeV4Ptr first_south = souths[souths.size()/2]->asTNodeV4();
			TNodeV4Ptr south_south = first_south->getSouth();
			TNodeV4Ptr south = south_south->getNorth();

			extractEastNodesFromTVertex(vertex, easts);
			TNodeV4Ptr first_east = easts[easts.size()/2]->asTNodeV4();
			TNodeV4Ptr east_east = first_east->getEast();
			TNodeV4Ptr east = east_east->getWest();

			TNodeV4Ptr row = east;
			for (int i=0;(i<souths.size() && row);i++)
			{
				TNodeV4Ptr col = south;
				for (int j=0;(j<easts.size() && col);j++)
				{
					if (row == col)
					{
						return row;
					}
					col = col->getNorth();
				}
				row = row->getWest();
			}
		}
		break;
	default:
		break;
	}
	return 0;
}

#ifdef use_namespace
}
#endif