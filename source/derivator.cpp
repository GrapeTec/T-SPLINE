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

int TDerivator::pointDerive( const Parameter &parameter, Point3D &point )
{
	point.clear();
	TFacePtr tface = findTFaceByParameter(parameter);
	if (!tface)  return 0;

	BlendingEquationPtr equation = prepareEquationByTFace(tface);
	point = equation->computePoint(parameter.s(), parameter.t());

	return 1;
}

int TDerivator::normalDerive( const Parameter &parameter, Vector3D &normal )
{
	return 0;
}

int TDerivator::pointAndNormalDerive( const Parameter &parameter, Point3D &point, Vector3D &normal )
{
	point.clear();
	TFacePtr face = findTFaceByParameter(parameter);
	if (!face)  return 0;

	BlendingEquationPtr equation = prepareEquationByTFace(face);
	equation->computePointAndNormal(parameter, point, normal);

	return 1;
}

RBD_COMMON::Real TDerivator::normalCurvature( const Parameter &parameter, Real ds, Real dt )
{
	ColumnVector fform = firstAndSecondFundamentalForm(parameter);

	Real E = fform(1), F = fform(2), G = fform(3), L = fform(4), M = fform(5), N = fform(6);
	Real kn = (L*ds*ds + 2.0*M*ds*dt + N*dt*dt) / (E*ds*ds + 2.0*F*ds*dt + G*dt*dt);
	return kn;
}

void TDerivator::principalCurvature( const Parameter &parameter, Real &k1, Real &k2 )
{
	ColumnVector fform = firstAndSecondFundamentalForm(parameter);
	Real E = fform(1), F = fform(2), G = fform(3), L = fform(4), M = fform(5), N = fform(6);

	Real A = E*N - 2.0*F*M + G*L;
	Real B = sqrt((E*N - 2.0*F*M + G*L)*(E*N - 2.0*F*M + G*L) - 4.0*(E*G-F*F)*(N*L-M*M));
	Real C = 2.0*(E*G-F*F);

	k1 = (A + B) / C;
	k2 = (A - B) / C;
}

NEWMAT::ReturnMatrix TDerivator::firstPartialDeriveU( const Parameter &parameter )
{
	TFacePtr face = findTFaceByParameter(parameter);
	if (!face)  return 0;

	BlendingEquationPtr equation = prepareEquationByTFace(face);
	return equation->computeFirstDerivative(BlendingEquation::DER_U, parameter);
}

NEWMAT::ReturnMatrix TDerivator::firstPartialDeriveV( const Parameter &parameter )
{
	TFacePtr face = findTFaceByParameter(parameter);
	if (!face)  return 0;

	BlendingEquationPtr equation = prepareEquationByTFace(face);
	return equation->computeFirstDerivative(BlendingEquation::DER_V, parameter);
}

NEWMAT::ReturnMatrix TDerivator::secondPartialDeriveUU( const Parameter &parameter )
{
	TFacePtr face = findTFaceByParameter(parameter);
	if (!face)  return 0;

	BlendingEquationPtr equation = prepareEquationByTFace(face);
	return equation->computeSecondDerivative(BlendingEquation::DER_U, BlendingEquation::DER_U, parameter);
}

NEWMAT::ReturnMatrix TDerivator::secondPartialDeriveUV( const Parameter &parameter )
{
	TFacePtr face = findTFaceByParameter(parameter);
	if (!face)  return 0;

	BlendingEquationPtr equation = prepareEquationByTFace(face);
	return equation->computeSecondDerivative(BlendingEquation::DER_U, BlendingEquation::DER_V, parameter);
}

NEWMAT::ReturnMatrix TDerivator::secondPartialDeriveVV( const Parameter &parameter )
{
	TFacePtr face = findTFaceByParameter(parameter);
	if (!face)  return 0;

	BlendingEquationPtr equation = prepareEquationByTFace(face);
	return equation->computeSecondDerivative(BlendingEquation::DER_V, BlendingEquation::DER_V, parameter);
}

NEWMAT::ReturnMatrix TDerivator::secondPartialDerive(const Parameter &parameter)
{
	TFacePtr face = findTFaceByParameter(parameter);
	if (!face)  return 0;

	BlendingEquationPtr equation = prepareEquationByTFace(face);
	return equation->computeUpToSecondDerivatives(parameter);
}

ReturnMatrix TDerivator::firstAndSecondFundamentalForm( const Parameter &parameter )
{
	Matrix derivatives = secondPartialDerive(parameter);
	ColumnVector Sss = derivatives.Column(1);
	ColumnVector Sst = derivatives.Column(2);
	ColumnVector Stt = derivatives.Column(3);
	ColumnVector Ss = derivatives.Column(4);
	ColumnVector St = derivatives.Column(5);
	ColumnVector S = derivatives.Column(6);

	Real E = DotProduct(Ss, Ss);
	Real F = DotProduct(Ss, St);
	Real G = DotProduct(St, St);
	Real L = 1.0/(sqrt(E*G-F*F)) * DotProduct(CrossProduct(Sss, Ss), St);
	Real M = 1.0/(sqrt(E*G-F*F)) * DotProduct(CrossProduct(Sst, Ss), St);
	Real N = 1.0/(sqrt(E*G-F*F)) * DotProduct(CrossProduct(Stt, Ss), St);

	ColumnVector fform(6);
	fform << E << F << G << L << M << N;

	fform.Release();
	return fform;
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
	TDerivator(spline), _face(tface), _equation(0)
{
	if (_face)  
	{
		_equation = prepareEquationByTFace(_face);
	}
}

TFaceDerivator::~TFaceDerivator()
{

}

int TFaceDerivator::pointDerive( const Parameter &parameter, Point3D &point )
{
// 	if (_equation)  
// 	{
		point = _equation->computePoint(parameter.s(), parameter.t());
		return 1;
// 	}
// 	else
// 	{
// 		point.clear();
// 		return 0;
// 	}
}

int TFaceDerivator::normalDerive( const Parameter &parameter, Vector3D &normal )
{
// 	if (_equation)  
// 	{
		normal = _equation->computeNormal(parameter.s(), parameter.t());
		return 1;
// 	}
// 	else
// 	{
// 		normal.clear();
// 		return 0;
// 	}
}

int TFaceDerivator::pointAndNormalDerive( const Parameter &parameter, Point3D &point, Vector3D &normal )
{
// 	if (_equation)  
// 	{
		_equation->computePointAndNormal(parameter, point, normal);
		return 1;
// 	}
// 	else
// 	{
// 		point.clear(); normal.clear();
// 		return 0;
// 	}
}

ReturnMatrix TFaceDerivator::firstPartialDeriveU( const Parameter &parameter )
{
	return _equation->computeFirstDerivative(BlendingEquation::DER_U, parameter);
}

ReturnMatrix TFaceDerivator::firstPartialDeriveV( const Parameter &parameter )
{
	return _equation->computeFirstDerivative(BlendingEquation::DER_V, parameter);
}

ReturnMatrix TFaceDerivator::secondPartialDeriveUU( const Parameter &parameter )
{
	return _equation->computeSecondDerivative(BlendingEquation::DER_U, BlendingEquation::DER_U, parameter);
}

ReturnMatrix TFaceDerivator::secondPartialDeriveUV( const Parameter &parameter )
{
	return _equation->computeSecondDerivative(BlendingEquation::DER_U, BlendingEquation::DER_V, parameter);
}

ReturnMatrix TFaceDerivator::secondPartialDeriveVV( const Parameter &parameter )
{
	return _equation->computeSecondDerivative(BlendingEquation::DER_V, BlendingEquation::DER_V, parameter);
}

ReturnMatrix TFaceDerivator::secondPartialDerive( const Parameter &parameter )
{
	return _equation->computeUpToSecondDerivatives(parameter);
}

ReturnMatrix TFaceDerivator::firstAndSecondFundamentalForm(const Parameter &parameter)
{
	return _equation->computeUpToSecondDerivatives(parameter);
}

#ifdef use_namespace
}
#endif