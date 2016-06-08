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

#include <editor.h>
#include <finder.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

TEditor::TEditor()
{

}

TEditor::~TEditor()
{

}

TGroupEditor::TGroupEditor( const TGroupPtr &group ) :
	_group(group)
{

}

TGroupEditor::~TGroupEditor()
{

}

TSplineEditor::TSplineEditor( const TSplinePtr &spline ) :
	_spline(spline)
{
}

TSplineEditor::~TSplineEditor()
{

}

void TSplineEditor::movePointBy( const TPointPtr &point, Real x, Real y, Real z )
{
	if (point) point->setXYZW(point->getX()+x, point->getY()+y, point->getZ()+z, point->getW());
}

void TSplineEditor::movePointBy( const std::string &point_name, Real x, Real y, Real z )
{
	movePointBy(findPoint(point_name), x, y, z);
}

void TSplineEditor::movePointTo( const TPointPtr &point, Real x, Real y, Real z )
{
	if (point) point->setXYZW(x, y, z, point->getW());
}

void TSplineEditor::movePointTo( const std::string &point_name, Real x, Real y, Real z )
{
	movePointTo(findPoint(point_name), x, y, z);
}

void TSplineEditor::setPointWeight( const TPointPtr &point, Real weight )
{
	point->setXYZW(point->getX(), point->getY(), point->getZ(), weight);
}

void TSplineEditor::setPointWeight( const std::string &point_name, Real weight )
{
	setPointWeight(findPoint(point_name), weight);
}

void TSplineEditor::removePoint( const TPointPtr &point )
{
	removeNode(point->getTNode());
	_spline->getTPointset()->removeObject(point);
	_spline->getCollector()->removeObject(point);
}

void TSplineEditor::removePoint( const std::string &point_name )
{
	removePoint(findPoint(point_name));
}

void TSplineEditor::removeNode( const TNodePtr &node )
{
	TNodeV4Ptr nodev4 = node->asTNodeV4();
	TNodeV4Ptr north = nodev4->getNorth();
	TNodeV4Ptr west = nodev4->getWest();
	TNodeV4Ptr south = nodev4->getSouth();
	TNodeV4Ptr east = nodev4->getEast();

	if (north && north->getSouth()==nodev4)
	{
		north->setSouth(south);
	}
	if (west && west->getEast()==nodev4)
	{
		west->setEast(east);
	}
	if (south && south->getNorth()==nodev4)
	{
		south->setNorth(north);
	}
	if (east && east->getWest()==nodev4)
	{
		east->setWest(west);
	}

	node->getTVertex()->removeNode(node);
	node->getTPoint()->setTNode(0);
	_spline->getTConnect()->removeObject(node);
	_spline->getCollector()->removeObject(node);
}

void TSplineEditor::removeNode( const std::string &node_name )
{
	removeNode(findNode(node_name));
}

TPointPtr TSplineEditor::findPoint( const std::string& point_name )
{
	TPointsetPtr pointset =	_spline->getTPointset();
	TLocalFinder<TObjVIterator> finder(pointset->iteratorBegin(), pointset->iteratorEnd());
	TObjVIterator iter = finder.findObjectByName(point_name);
	if (iter!=pointset->iteratorEnd())
	{
		return (*iter)->asTPoint();
	}
	else
	{
		return 0;
	}
}

TNodePtr TSplineEditor::findNode( const std::string& node_name )
{
	TConnectPtr connect = _spline->getTConnect();
	TLocalFinder<TObjVIterator> finder(connect->iteratorBegin(), connect->iteratorEnd());
	TObjVIterator iter = finder.findObjectByName(node_name);
	if (iter!=connect->iteratorEnd())
	{
		return (*iter)->asTNode();
	}
	else
	{
		return 0;
	}
}

#ifdef use_namespace
}
#endif