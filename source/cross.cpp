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

#include <cross.h>
#include <virtual.h>
#include <finder.h>
#include <sstream>
#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

TMapperCross::TMapperCross()
{
}

TMapperCross::~TMapperCross()
{

}

void TMapperCross::setCenter( const TMappableObjectPtr &mapper )
{
	_mapper_center = mapper;
}

void TMapperCross::addNorth( const TMappableObjectPtr &mapper )
{
	_mappers_north.push_back(mapper);
}

void TMapperCross::addWest( const TMappableObjectPtr &mapper )
{
	_mappers_west.push_back(mapper);
}

void TMapperCross::addSouth( const TMappableObjectPtr &mapper )
{
	_mappers_south.push_back(mapper);
}

void TMapperCross::addEast( const TMappableObjectPtr &mapper )
{
	_mappers_east.push_back(mapper);
}


ParameterSquarePtr TMapperCross::blendParameterSquare()
{
	ParameterSquarePtr square = makePtr<ParameterSquare>(_mapper_center->northWest(), _mapper_center->southEast());
	std::for_each(_mappers_north.begin(), _mappers_north.end(), ParameterExtender(square));
	std::for_each(_mappers_west.begin(), _mappers_west.end(), ParameterExtender(square));
	std::for_each(_mappers_south.begin(), _mappers_south.end(), ParameterExtender(square));
	std::for_each(_mappers_east.begin(), _mappers_east.end(), ParameterExtender(square));
	return square;
}

void TMapperCross::findFaces( TFacSet &faces )
{
	if (!_mapper_center) return;
	ParameterSquarePtr square = blendParameterSquare();
	TGroupPtr group = _mapper_center->getCollector();
	std::for_each(group->iteratorBegin(), group->iteratorEnd(), 
		OverlappedFaceFinder(square, faces));
}

void TMapperCross::unique()
{
	uniqueMappers(_mappers_north);
	uniqueMappers(_mappers_west);
	uniqueMappers(_mappers_south);
	uniqueMappers(_mappers_east);
}

void TMapperCross::clear()
{
	_mapper_center = 0;
	_mappers_north.clear();
	_mappers_west.clear();
	_mappers_south.clear();
	_mappers_east.clear();
}

void TMapperCross::uniqueMappers( TMapObjVector &mappers )
{
	TMapObjVIterator niter = std::unique(mappers.begin(), mappers.end());
	mappers.erase(niter, mappers.end());
}

void TMapperCross::ParameterExtender::operator()( const TMappableObjectPtr &mapper )
{
	_parameter_square->extendParameter(mapper->northWest());
	_parameter_square->extendParameter(mapper->southEast());
}


void TMapperCross::OverlappedFaceFinder::operator()( const TObjectPtr &object )
{
	if (TFacePtr face = object->asTFace())
	{
		ParameterSquarePtr face_square = makePtr<ParameterSquare>(face->northWest(), face->southEast());
		if (isOverlapped(face_square))
		{
			_faces.insert(face);
		}
	}
}

int TMapperCross::OverlappedFaceFinder::codeOfArea( Real v, Real vmin, Real vmax )
{
	if (v <= vmin) return -1;
	else if (v > vmin && v < vmax) return 0;
	else return 1;
}

bool TMapperCross::OverlappedFaceFinder::isOverlapped( const ParameterSquarePtr check_square )
{
	int smax = codeOfArea(check_square->sMax(), _target_square->sMin(), _target_square->sMax());
	int tmax = codeOfArea(check_square->tMax(), _target_square->tMin(), _target_square->tMax());
	int smin = codeOfArea(check_square->sMin(), _target_square->sMin(), _target_square->sMax());
	int tmin = codeOfArea(check_square->tMin(), _target_square->tMin(), _target_square->tMax());

	if (smax == -1 || smin == 1 || tmax == -1 || tmin == 1)
		return false;
	else
		return true;
}

TNodeV4Cross::TNodeV4Cross(int degree_s /*= 3*/, int degree_t /*= 3*/)
	: _degree_s(degree_s), _degree_t(degree_t), _prepared(false)
{
	_mapper_cross = makePtr<TMapperCross>();
}

TNodeV4Cross::~TNodeV4Cross()
{
}

void TNodeV4Cross::setNodeCenter( const TNodeV4Ptr &node )
{
	_node_center = node;
	_prepared = false;
}

void TNodeV4Cross::addNodeNorth( const TNodeV4Ptr &node )
{
	_nodes_north.push_back(node);
}

void TNodeV4Cross::addNodeWest( const TNodeV4Ptr &node )
{
	_nodes_west.push_back(node);
}

void TNodeV4Cross::addNodeSouth( const TNodeV4Ptr &node )
{
	_nodes_south.push_back(node);
}

void TNodeV4Cross::addNodeEast( const TNodeV4Ptr &node )
{
	_nodes_east.push_back(node);
}

bool TNodeV4Cross::isPrepared()
{
	return _prepared;
}

void TNodeV4Cross::clearRelationships()
{
	_mapper_cross->clear();
	_faces.clear();
}

void TNodeV4Cross::prepareRelationships()
{
	if (isPrepared())
		clearRelationships();
	prepareTMapperCross();
	prepareTFaces();
	_prepared = true;
}

void TNodeV4Cross::prepareTMapperCross()
{
	_mapper_cross->setCenter(findMapperOfNode(_node_center));
	for (int i=0;i<_nodes_north.size();i++)
	{
		_mapper_cross->addNorth(findMapperOfNode(_nodes_north[i]));
	}
	for (int i=0;i<_nodes_west.size();i++)
	{
		_mapper_cross->addWest(findMapperOfNode(_nodes_west[i]));
	}
	for (int i=0;i<_nodes_south.size();i++)
	{
		_mapper_cross->addSouth(findMapperOfNode(_nodes_south[i]));
	}
	for (int i=0;i<_nodes_east.size();i++)
	{
		_mapper_cross->addEast(findMapperOfNode(_nodes_east[i]));
	}
}

void TNodeV4Cross::prepareTFaces()
{
	_mapper_cross->findFaces(_faces);
}

TVertexPtr TNodeV4Cross::findVertexOfNode( const TNodeV4Ptr &node )
{
	if (node)
		return node->getTVertex();
	else
		return 0;
}

TMappableObjectPtr TNodeV4Cross::findMapperOfNode( const TNodeV4Ptr &node )
{
	if (node)
		return node->getTMapper();
	else
		return 0;
}

void TNodeV4Cross::copyTFaces( TFacVector &faces )
{
	faces.resize(_faces.size());
	std::copy(_faces.begin(), _faces.end(), faces.begin());
}


#ifdef use_namespace
}
#endif