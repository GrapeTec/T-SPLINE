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

#include <splbase.h>

#ifdef use_namespace
namespace TSPLINE {
  using namespace NEWMAT;
#endif


QuadraticSpline::QuadraticSpline() : SplineBase(2)
{

}

QuadraticSpline::QuadraticSpline( const std::vector<Real> &vnodes ) : SplineBase(vnodes, 2)
{

}

QuadraticSpline::~QuadraticSpline()
{

}

Real QuadraticSpline::baseFunc( Real u ) const
{
	Real result = 0.0;
	ColumnVector knots = getKnots();
	Real k1 = knots(1), k2 = knots(2), k3 = knots(3), k4 = knots(4);

	if((k1<=u && u<k2) || (k4==k3&&k4==k2&&u==k4))
	{
		result = safeDivide((u-k1)*(u-k1),(k3-k1)*(k2-k1));
	}
	else if((k2<=u && u<k3) || (k4==k3&&u==k4))
	{
		result = safeDivide((u-k1)*(k3-u),(k3-k1)*(k3-k2))
			+ safeDivide((k4-u)*(u-k2),(k4-k2)*(k3-k2));
	}
	else if(k3<=u && u<=k4)
	{
		result = safeDivide((k4-u)*(k4-u),(k4-k2)*(k4-k3));
	}
	return result;
}

Real QuadraticSpline::baseFunc1st( Real u ) const
{
	Real result = 0.0;
	ColumnVector knots = getKnots();
	Real k1 = knots(1), k2 = knots(2), k3 = knots(3), k4 = knots(4);

	if((k1<=u && u<k2) || (k4==k3&&k4==k2&&u==k4))
	{
		result = safeDivide(2*(u-k1),(k3-k1)*(k2-k1));
	}
	else if((k2<=u && u<k3) || (k4==k3&&u==k4))
	{
		result = safeDivide((k1+k3-2*u),(k3-k1)*(k3-k2))
			+ safeDivide((k2+k4-2*u),(k4-k2)*(k3-k2));
	}
	else if(k3<=u && u<=k4)
	{
		result = safeDivide(2*(u-k4),(k4-k2)*(k4-k3));
	}
	return result;
}

Real QuadraticSpline::baseFunc2nd( Real u ) const
{
	Real result = 0.0;
	ColumnVector knots = getKnots();
	Real k1 = knots(1), k2 = knots(2), k3 = knots(3), k4 = knots(4);

	if((k1<=u && u<k2) || (k4==k3&&k4==k2&&u==k4))
	{
		result = safeDivide(2.0, ((k3-k1)*(k2-k1)));
	}
	else if((k2<=u && u<k3) || (k4==k3&&u==k4))
	{
		result = safeDivide(-2.0, ((k3-k1)*(k3-k2))-2/((k4-k2)*(k3-k2)));
	}
	else if(k3<=u && u<=k4)
	{
		result = safeDivide(2.0, ((k4-k2)*(k4-k3)));
	}
	return result;	
}

CubicSpline::CubicSpline() : SplineBase(3)
{

}

CubicSpline::CubicSpline( const std::vector<Real> &vnodes ) : SplineBase(vnodes, 3)
{

}

CubicSpline::~CubicSpline()
{

}

Real CubicSpline::baseFunc(Real u) const
{
	double result(0);
	ColumnVector knots = getKnots();
	Real k1 = knots(1), k2 = knots(2), k3 = knots(3), k4 = knots(4), k5 = knots(5);

	if((k1<=u && k2>u) || (k5==k4&&k5==k3&&k5==k2&&u==k5))
	{
		result=safeDivide((u-k1)*(u-k1)*(u-k1),(k4-k1)*(k3-k1)*(k2-k1));
	}
	else if((k2<=u && k3>u) || (k5==k4&&k5==k3&&u==k5))
	{
		result = safeDivide((u-k1)*(u-k1)*(k3-u),(k3-k2)*(k4-k1)*(k3-k1))
			+ safeDivide((u-k2)*(u-k1)*(k4-u),(k4-k2)*(k3-k2)*(k4-k1))
			+ safeDivide((u-k2)*(u-k2)*(k5-u),(k5-k2)*(k4-k2)*(k3-k2));
	}
	else if((k3<=u && k4>u) || (k5==k4&&u==k5))
	{
		result = safeDivide((u-k1)*(k4-u)*(k4-u),(k4-k3)*(k4-k2)*(k4-k1))
			+ safeDivide((u-k2)*(k5-u)*(k4-u),(k5-k2)*(k4-k3)*(k4-k2))
			+ safeDivide((u-k3)*(k5-u)*(k5-u),(k5-k3)*(k5-k2)*(k4-k3));
	}
	else if(k4<=u && k5>=u)
	{
		result = safeDivide((k5-u)*(k5-u)*(k5-u),(k5-k4)*(k5-k3)*(k5-k2));
	}
	if((k1<=u && k2>u) || (k5==k4&&k5==k3&&k5==k2&&u==k5))
	{
		result=safeDivide((u-k1)*(u-k1)*(u-k1),(k4-k1)*(k3-k1)*(k2-k1));
	}
	else if((k2<=u && k3>u) || (k5==k4&&k5==k3&&u==k5))
	{
		result = safeDivide((u-k1)*(u-k1)*(k3-u),(k3-k2)*(k4-k1)*(k3-k1))
			+ safeDivide((u-k2)*(u-k1)*(k4-u),(k4-k2)*(k3-k2)*(k4-k1))
			+ safeDivide((u-k2)*(u-k2)*(k5-u),(k5-k2)*(k4-k2)*(k3-k2));
	}
	else if((k3<=u && k4>u) || (k5==k4&&u==k5))
	{
		result = safeDivide((u-k1)*(k4-u)*(k4-u),(k4-k3)*(k4-k2)*(k4-k1))
			+ safeDivide((u-k2)*(k5-u)*(k4-u),(k5-k2)*(k4-k3)*(k4-k2))
			+ safeDivide((u-k3)*(k5-u)*(k5-u),(k5-k3)*(k5-k2)*(k4-k3));
	}
	else if(k4<=u && k5>=u)
	{
		result = safeDivide((k5-u)*(k5-u)*(k5-u),(k5-k4)*(k5-k3)*(k5-k2));
	}
	return result;
}

Real CubicSpline::baseFunc1st(Real u) const
{
	ColumnVector nodes = getKnots();
	double result(0.0);
	Real k1 = nodes(1), k2 = nodes(2), k3 = nodes(3), k4 = nodes(4), k5 = nodes(5);

	if((k1<=u && k2>u) || (k5==k4&&k5==k3&&k5==k2&&u==k5))
	{
		result = safeDivide(3*(u-k1)*(u-k1),(k4-k1)*(k3-k1)*(k2-k1));
	}
	else if((k2<=u && k3>u) || (k5==k4&&k5==k3&&u==k5))
	{
		result = safeDivide(2*(u-k1)*(k3-u)-(u-k1)*(u-k1),(k3-k2)*(k4-k1)*(k3-k1))
			+ safeDivide((u-k1)*(k4-u)+(u-k2)*(k4-u)-(u-k2)*(u-k1),(k4-k2)*(k3-k2)*(k4-k1))
			+ safeDivide(2*(u-k2)*(k5-u)-(u-k2)*(u-k2),(k5-k2)*(k4-k2)*(k3-k2));
	}
	else if((k3<=u && k4>u) || (k5==k4&&u==k5))
	{
		result = safeDivide((k4-u)*(k4-u)-2*(u-k1)*(k4-u),(k4-k3)*(k4-k2)*(k4-k1))
			+ safeDivide((k5-u)*(k4-u)-(u-k2)*(k4-u)-(u-k2)*(k5-u),(k5-k2)*(k4-k3)*(k4-k2))
			+ safeDivide((k5-u)*(k5-u)-2*(u-k3)*(k5-u),(k5-k3)*(k5-k2)*(k4-k3));
	}
	else if(k4<=u && k5>=u)
	{
		result = safeDivide(-3*(k5-u)*(k5-u),(k5-k4)*(k5-k3)*(k5-k2));
	}
	return result;
}

Real CubicSpline::baseFunc2nd( Real u ) const
{
	ColumnVector nodes = getKnots();
	double result(0.0);
	Real k1 = nodes(1), k2 = nodes(2), k3 = nodes(3), k4 = nodes(4), k5 = nodes(5);

	if((k1<=u && k2>u) || (k5==k4&&k5==k3&&k5==k2&&u==k5))
	{
		result=safeDivide(6*(u-k1),(k4-k1)*(k3-k1)*(k2-k1));
	}
	else if((k2<=u && k3>u) || (k5==k4&&k5==k3&&u==k5))
	{
		result = safeDivide((2*k3+4*k1-6*u),(k3-k2)*(k4-k1)*(k3-k1))
			+ safeDivide((2*k4+2*k2+2*k1-6*u),(k4-k2)*(k3-k2)*(k4-k1))
			+ safeDivide((2*k5+4*k2-6*u),(k5-k2)*(k4-k2)*(k3-k2));
	}
	else if((k3<=u && k4>u) || (k5==k4&&u==k5))
	{
		result = safeDivide((-4*k4-2*k1+6u),(k4-k3)*(k4-k2)*(k4-k1))
			+ safeDivide((-2*k4-2*k5-2*k2+6*u),(k5-k2)*(k4-k3)*(k4-k2))
			+ safeDivide((-4*k5-2*k3+6*u),(k5-k3)*(k5-k2)*(k4-k3));
	}
	else if(k4<=u && k5>=u)
	{
		result = safeDivide(6*(k5-u),(k5-k4)*(k5-k3)*(k5-k2));
	}
	return result;
}

SplineBase::SplineBase() : _order(3)
{

}

SplineBase::SplineBase( unsigned int order ) : _order(order)
{

}

SplineBase::SplineBase( const std::vector<Real> &vnodes, unsigned int order ) : _order(order)
{
	for (int i=0;i<vnodes.size();i++)
	{
		_knots << vnodes[i];
	}
}

SplineBase::~SplineBase()
{

}

Real SplineBase::baseFunc(Real u) const
{
	 Real Nip;
 	/*计算基函数nip*/
 	//U节点矢量数组，_order次数，m 节点下标最大值（m+1个节点），i 起始位置，u变量
 	//输出Nip
	unsigned int i = 0;
	unsigned int m = _knots.size()-1;

 	if((i==0&&u==_knots(1))||(i==m-_order-1&&u==_knots(m+1)))
 	{
 		Nip=1.0;return Nip;
 	}
 	if((u < _knots(i+1)) || (u > _knots(i+_order+1+1)) )
 	{
 		return 0.0;
 	}
 	//初始化0次基函数
 	std::vector<Real> N;
 	for(int j=0;j<=_order;j++)
 	{
 		if(u>=_knots(i+1) && u<_knots(i+_order+1+1))
 		{
 			if(u>=_knots(i+j+1)&&u<_knots(i+j+1+1))//左闭右开
 				N.push_back(1.0);
 			else
 			{
 				N.push_back(0.0);
 			}
 		}
 		else if(_knots(i+_order+1+1)==u)
 		{
 			if(u>_knots(i+j+1)&&u<=_knots(i+j+1+1))//左闭右开
 				N.push_back(1.0);
 			else
 			{
 				N.push_back(0.0);
 			}
 		}
 	}
 	double saved,Uleft,Uright,temp;
 	//计算三角形表
 	for(int k=1;k<=_order;k++)
 	{
 		if(N[0]==0.0)
 			saved=0.0;
 		else 
 			saved=((u-_knots(i+1))*N[0])/(_knots(i+k+1)-_knots(i+1));
 
 		for(int j=0;j<_order-k+1;j++)
 		{
 			Uleft=_knots(i+j+1+1);
 			Uright=_knots(i+j+k+1+1);
 
 			if(N[j+1]==0.0)
 			{
 				N[j]=saved;
 				saved=0.0;
 			}
 			else
 			{
 				temp=N[j+1]/(Uright-Uleft);
 				N[j]=saved+(Uright-u)*temp;
 				saved=(u-Uleft)*temp;
 			}
 		}
 	}
 	Nip=N[0];
 	return Nip;
}

ColumnVector SplineBase::getKnots() const
{
	return _knots;
}

void SplineBase::setKnots( const ColumnVector &k )
{
	_knots = k;
}

Real SplineBase::baseFunc1st( Real u ) const
{
	return 0.0;
}

Real SplineBase::baseFunc2nd( Real u ) const
{
	return 0.0;
}

Real SplineBase::Nip( unsigned int i, unsigned int p, Real u ) const
{
	if (p == 0)
	{
		if (u>=_knots(i+1) && u<=_knots(i+2)) return 1.0; return 0.0;
	}
	else
	{
		Real alpha, beta;
		alpha = safeDivide((u-_knots(i+1)), (_knots(i+p+1)-_knots(i+1))) * Nip(i, p-1, u);
		beta = safeDivide((_knots(i+p+2)-u), (_knots(i+p+2)-_knots(i+2))) * Nip(i+1, p-1, u);
		return alpha + beta;
	}
}

CrossSpline::CrossSpline( const SplineBasePtr &spline_u, const SplineBasePtr &spline_v ) :
	_spline_u(spline_u), _spline_v(spline_v)
{

}

CrossSpline::~CrossSpline()
{

}

Real CrossSpline::baseFunc( Real u, Real v ) const
{
	return (_spline_u->baseFunc(u))* (_spline_v->baseFunc(v));
}

Real CrossSpline::baseFunc1stU( Real u, Real v ) const
{
	return (_spline_u->baseFunc1st(u))*(_spline_v->baseFunc(v));
}

Real CrossSpline::baseFunc1stV( Real u, Real v ) const
{
	return (_spline_u->baseFunc(u))*(_spline_v->baseFunc1st(v));
}

Real CrossSpline::baseFunc2ndU( Real u, Real v ) const
{
	return (_spline_u->baseFunc2nd(u))*(_spline_v->baseFunc(v));
}

Real CrossSpline::baseFunc2ndV( Real u, Real v ) const
{
	return (_spline_u->baseFunc(u))*(_spline_v->baseFunc2nd(v));
}

void CrossSpline::setUVNodes( const ColumnVector &ku, const ColumnVector &kv )
{
	_spline_u->setKnots(ku);
	_spline_v->setKnots(kv);
}

CrossQuadraticSpline::CrossQuadraticSpline() :
	CrossSpline(makePtr<QuadraticSpline>(), makePtr<QuadraticSpline>())
{

}

CrossQuadraticSpline::CrossQuadraticSpline( const QuadraticSplinePtr &spline_u, const QuadraticSplinePtr &spline_v ) :
	CrossSpline(spline_u, spline_v)
{

}

CrossQuadraticSpline::~CrossQuadraticSpline()
{

}

void CrossQuadraticSpline::setUVNodes( const ColumnVector &ku, const ColumnVector &kv )
{
	assert(ku.size() == 4 && kv.size() == 4);
	CrossSpline::setUVNodes(ku, kv);
}

CrossCubicSpline::CrossCubicSpline() : 
	CrossSpline(makePtr<CubicSpline>(), makePtr<CubicSpline>())
{

}

CrossCubicSpline::CrossCubicSpline( const CubicSplinePtr &spline_u, const CubicSplinePtr &spline_v ) :
	CrossSpline(spline_u, spline_v)
{

}

CrossCubicSpline::~CrossCubicSpline()
{

}

void CrossCubicSpline::setUVNodes( const ColumnVector &ku, const ColumnVector &kv )
{
	assert(ku.size() == 5 && kv.size() == 5);
	CrossSpline::setUVNodes(ku, kv);
}

BlendingEquation::BlendingEquation()
{
	_cross_spline = makePtr<CrossCubicSpline>();
}

BlendingEquation::~BlendingEquation()
{

}

Point3D BlendingEquation::compute(Real u, Real v)
{
	Point3D numerator(0.0, 0.0, 0.0);
	Real denominator = 0.0;
	VRPVK::iterator iter;
	for (iter = _rational_points_with_knots.begin(); \
		iter != _rational_points_with_knots.end(); iter++)
	{
		_cross_spline->setUVNodes(iter->getUNodesAsColumnVector(),
			iter->getVNodesAsColumnVector());
		Real nuv = _cross_spline->baseFunc(u, v);
		Point3D point(iter->x(), iter->y(), iter->z());
		Real w = (iter->weight);
		numerator += (point * nuv * w);
		denominator += (nuv * w);
	}
	return safeDivide(numerator, denominator);
}

Point3D BlendingEquation::compute( const Parameter &p )
{
	return compute(p.s(), p.t());
}

Vector3D BlendingEquation::computeNormal( Real u, Real v )
{
	Vector3D normal;
	Point3D pbw, pdbuw, pdbvw;
	Real bw = 0.0, dbuw = 0.0, dbvw = 0.0;
	VRPVK::iterator iter;
	for (iter = _rational_points_with_knots.begin(); \
		iter != _rational_points_with_knots.end(); iter++)
	{
		_cross_spline->setUVNodes(iter->getUNodesAsColumnVector(),
			iter->getVNodesAsColumnVector());
		Real nuv = _cross_spline->baseFunc(u, v);
		Real dnu = _cross_spline->baseFunc1stU(u, v);
		Real dnv = _cross_spline->baseFunc1stV(u, v);
		Point3D point(iter->x(), iter->y(), iter->z());
		Real w = (iter->weight);
		pbw += (point * nuv * w);
		bw += (nuv * w);
		pdbuw += (point * dnu * w);
		dbuw += (dnu * w);
		pdbvw += (point * dnv * w);
		dbvw += (dnv * w);
	}

	Point3D suv = pbw / bw;
	Vector3D dsdu = (pdbuw - suv*dbuw)*(1/bw);
	Vector3D dsdv = (pdbvw - suv*dbvw)*(1/bw);
	
	normal = dsdu * dsdv; normal.normalize();

	return normal;
}

Vector3D BlendingEquation::computeNormal( const Parameter &p )
{
	return computeNormal(p.s(), p.t());
}

void BlendingEquation::computePointAndNormal( Real u, Real v, Point3D &point, Vector3D &normal )
{
	Point3D pbw, pdbuw, pdbvw;
	Real bw = 0.0, dbuw = 0.0, dbvw = 0.0;
	VRPVK::iterator iter;
	for (iter = _rational_points_with_knots.begin(); \
		iter != _rational_points_with_knots.end(); iter++)
	{
		_cross_spline->setUVNodes(iter->getUNodesAsColumnVector(),
			iter->getVNodesAsColumnVector());
		Real nuv = _cross_spline->baseFunc(u, v);
		Real dnu = _cross_spline->baseFunc1stU(u, v);
		Real dnv = _cross_spline->baseFunc1stV(u, v);
		Point3D point(iter->x(), iter->y(), iter->z());
		Real w = (iter->weight);
		pbw += (point * nuv * w);
		bw += (nuv * w);
		pdbuw += (point * dnu * w);
		dbuw += (dnu * w);
		pdbvw += (point * dnv * w);
		dbvw += (dnv * w);
	}

	point = pbw / bw;
	Vector3D dsdu = (pdbuw - point*dbuw)*(1/bw);
	Vector3D dsdv = (pdbvw - point*dbvw)*(1/bw);

	normal = dsdu * dsdv; normal.normalize();
}

void BlendingEquation::computePointAndNormal( const Parameter &p, Point3D &point, Vector3D &normal )
{
	computePointAndNormal(p.s(), p.t(), point, normal);
}

void BlendingEquation::addRationalPointWithNodes( const std::vector<Real> &u_knots, const std::vector<Real> &v_knots, Point3D &point, Real weight )
{
	RationalPoint3DWithUVNodes rpwk(point.x(), point.y(), point.z(), weight);
	
	rpwk.setUNodes(u_knots);
	rpwk.setVNodes(v_knots);

	_rational_points_with_knots.push_back(rpwk);
}


#ifdef use_namespace
}
#endif