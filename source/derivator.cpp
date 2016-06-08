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

#include <derivator.h>
#include <finder.h>
#include <extractor.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

TDerivator::TDerivator( const TSplinePtr &spline ) :
	_spline(spline)
{
}

TDerivator::~TDerivator()
{

}

int TDerivator::zeroOrderDerive( const Parameter &parameter, Point3D &point )
{
	point.clear();
	TFacePtr tface = findTFaceByParameter(parameter);
	if (!tface)  return 0;

	BlendingEquationPtr equation = prepareEquationByTFace(tface);
	point = equation->compute(parameter.s(), parameter.t());

	return 1;
}

int TDerivator::firstOrderDerive( const Parameter &parameter, Vector3D &normal )
{
	return 0;
}

int TDerivator::zeroAndFirstOrderDerive( const Parameter &parameter, Point3D &point, Vector3D &normal )
{
	point.clear();
	TFacePtr face = findTFaceByParameter(parameter);
	if (!face)  return 0;

	BlendingEquationPtr equation = prepareEquationByTFace(face);
	equation->computePointAndNormal(parameter, point, normal);

	return 1;
}

TFacePtr TDerivator::findTFaceByParameter( const Parameter &parameter )
{
	TFinderPtr finder = makePtr<TFinder>(_spline->getCollector());
	return finder->findTFaceByParameter(parameter);
}

BlendingEquationPtr TDerivator::prepareEquationByTFace( const TFacePtr &face )
{
	BlendingEquationPtr equation = makePtr<BlendingEquation>();
	TNodVIterator iter = face->blendingNodeIteratorBegin();
	for (;iter != face->blendingNodeIteratorEnd();iter++)
	{
		std::vector<Real> u_nodes, v_nodes;
		Point3D control_point; Real weight;
		TNodeV4Ptr node_v4 = castPtr<TNodeV4>(*iter);
		TExtractor::extractUVKnotsFromTNodeV4(node_v4, u_nodes, v_nodes);
		TExtractor::extractRationalPointFromTNodeV4(node_v4, control_point, weight);
		equation->addRationalPointWithNodes(u_nodes, v_nodes, control_point, weight);
	}
	return equation;
}

TFaceDerivator::TFaceDerivator( const TSplinePtr &spline, const TFacePtr &tface ) :
	TDerivator(spline), _face(tface)
{

}

TFaceDerivator::~TFaceDerivator()
{

}

int TFaceDerivator::zeroOrderDerive( const Parameter &parameter, Point3D &point )
{
	if (_face)  
	{
		BlendingEquationPtr equation = prepareEquationByTFace(_face);
		point = equation->compute(parameter.s(), parameter.t());
		return 1;
	}
	else
	{
		point.clear();
		return 0;
	}
}

int TFaceDerivator::firstOrderDerive( const Parameter &parameter, Vector3D &normal )
{
	if (_face)  
	{
		BlendingEquationPtr equation = prepareEquationByTFace(_face);
		normal = equation->computeNormal(parameter.s(), parameter.t());
		return 1;
	}
	else
	{
		normal.clear();
		return 0;
	}
}

int TFaceDerivator::zeroAndFirstOrderDerive( const Parameter &parameter, Point3D &point, Vector3D &normal )
{
	if (_face)  
	{
		BlendingEquationPtr equation = prepareEquationByTFace(_face);
		equation->computePointAndNormal(parameter, point, normal);
		return 1;
	}
	else
	{
		point.clear(); normal.clear();
		return 0;
	}
}

#ifdef use_namespace
}
#endif