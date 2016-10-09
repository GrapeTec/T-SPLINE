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
//#include <test_time.h>
#ifdef use_namespace
namespace TSPLINE {
  using namespace NEWMAT;
#endif

//#define MATRIX_FORM 1

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
	switch ( domain(u) )
	{
	case TSPLINE::K5_OUT:
		return 0.0;
		break;
	case TSPLINE::K5_E1:
		{
			Real x1 = u - getKnot(1);
			return safeDivide(x1*x1*x1, _a0);
		}
		break;
	case TSPLINE::K5_E2:
		{
			Real x1 = u - getKnot(1);
			Real x2 = u - getKnot(2);
			Real x3 = u - getKnot(3);
			Real x4 = u - getKnot(4);
			Real x5 = u - getKnot(5);
			return safeDivide(x1*x1*x3, _b0) 
				+ safeDivide(x2*x1*x4, _b1) 
				+ safeDivide(x2*x2*x5, _b2);
		}
		break;
	case TSPLINE::K5_E3:
		{
			Real x1 = u - getKnot(1);
			Real x2 = u - getKnot(2);
			Real x3 = u - getKnot(3);
			Real x4 = u - getKnot(4);
			Real x5 = u - getKnot(5);
			return safeDivide(x1*x4*x4, _c0) 
				+ safeDivide(x2*x5*x4, _c1) 
				+ safeDivide(x3*x5*x5, _c2);
		}
		break;
	case TSPLINE::K5_E4:
		{
			Real x5 = u - getKnot(5);
			return safeDivide(x5*x5*x5, _d0);
		}
		break;
	default:
		return 0.0;
		break;
	}
}


Real CubicSpline::baseFunc_m( Real u ) const
{
	K5Domain dm = domain(u);
	if (dm == K5_OUT) return 0.0;
	RowVector h0 = H(dm).Row(1);
	ColumnVector up(4);	up << 1.0 << u << u*u << u*u*u;	
	return DotProduct(h0, up);
}

Real CubicSpline::baseFunc1st(Real u) const
{
	K5Domain dm = domain(u);

	switch (dm)
	{
	case TSPLINE::K5_OUT:
		return 0.0;
		break;
	case TSPLINE::K5_E1:
		{
			Real x1 = u - getKnot(1);
			return safeDivide(3*x1*x1, _a0);
		}
		break;
	case TSPLINE::K5_E2:
		{
			Real x1 = u - getKnot(1);
			Real x2 = u - getKnot(2);
			Real x3 = u - getKnot(3);
			Real x4 = u - getKnot(4);
			Real x5 = u - getKnot(5);
			return safeDivide(2*x1*x3+x1*x1, _b0)
				+ safeDivide(x1*x4+x2*x4+x2*x1, _b1)
				+ safeDivide(2*x2*x5+x2*x2, _b2);
		}
		break;
	case TSPLINE::K5_E3:
		{
			Real x1 = u - getKnot(1);
			Real x2 = u - getKnot(2);
			Real x3 = u - getKnot(3);
			Real x4 = u - getKnot(4);
			Real x5 = u - getKnot(5);
			return safeDivide(x4*x4+2*x1*x4, _c0)
				+ safeDivide(x5*x4+x2*x4+x2*x5, _c1)
				+ safeDivide(x5*x5+2*x3*x5, _c2);
		}
		break;
	case TSPLINE::K5_E4:
		{
			Real x5 = u - getKnot(5);
			return safeDivide(3*x5*x5, _d0);
		}
		break;
	default:
		return 0.0;
		break;
	}
}

Real CubicSpline::baseFunc1st_m( Real u ) const
{
	K5Domain dm = domain(u);
	if (dm == K5_OUT) return 0.0;
	RowVector h1 = H(dm).SubMatrix(2,2,1,3).AsRow();
	ColumnVector up(3);	up << 1.0 << u << u*u;
	return DotProduct(h1, up);
}

Real CubicSpline::baseFunc2nd( Real u ) const
{
	K5Domain dm = domain(u);

	switch (dm)
	{
	case TSPLINE::K5_OUT:
		return 0.0;
		break;
	case TSPLINE::K5_E1:
		{
			Real x1 = u - getKnot(1);
			return safeDivide(6.0*x1, _a0);
		}
		break;
	case TSPLINE::K5_E2:
		{
			Real x1 = u - getKnot(1);
			Real x2 = u - getKnot(2);
			Real x3 = u - getKnot(3);
			Real x4 = u - getKnot(4);
			Real x5 = u - getKnot(5);
			return safeDivide(2.0*x3+4.0*x1, _b0)
				+ safeDivide(2.0*(x4+x2+x1), _b1)
				+ safeDivide((2.0*x5+4.0*x2), _b2);
		}
		break;
	case TSPLINE::K5_E3:
		{
			Real x1 = u - getKnot(1);
			Real x2 = u - getKnot(2);
			Real x3 = u - getKnot(3);
			Real x4 = u - getKnot(4);
			Real x5 = u - getKnot(5);
			return safeDivide(2.0*x1+4.0*x4, _c0)
				+ safeDivide(2.0*(x4+x5+x2), _c1)
				+ safeDivide(2.0*x3+4.0*x5, _c2);
		}
		break;
	case TSPLINE::K5_E4:
		{
			Real x5 = u - getKnot(5);
			return safeDivide(6.0*x5, _d0);
		}
		break;
	default:
		return 0.0;
		break;
	}
}

Real CubicSpline::baseFunc2nd_m( Real u ) const
{
	K5Domain dm = domain(u);
	if (dm == K5_OUT) return 0.0;
	RowVector h2 = H(dm).SubMatrix(3,3,1,2).AsRow();
	ColumnVector up(2);	up << 1.0 << u;
	return DotProduct(h2, up);
}

void CubicSpline::init()
{
	ColumnVector nodes = getKnots();
	Real t0 = nodes(1), t1 = nodes(2), t2 = nodes(3), t3 = nodes(4), t4 = nodes(5);
	_a0 = (t3-t0)*(t2-t0)*(t1-t0);
	_b0 = -(t2-t1)*(t3-t0)*(t2-t0);
	_b1 = -(t3-t1)*(t2-t1)*(t3-t0);
	_b2 = -(t4-t1)*(t3-t1)*(t2-t1);
	_c0 = (t3-t2)*(t3-t1)*(t3-t0);
	_c1 = (t4-t1)*(t3-t2)*(t3-t1);
	_c2 = (t4-t2)*(t4-t1)*(t3-t2);
	_d0 = -(t4-t3)*(t4-t2)*(t4-t1);
}

void CubicSpline::init_m()
{
	ColumnVector nodes = getKnots();
	Real t0 = nodes(1), t1 = nodes(2), t2 = nodes(3), t3 = nodes(4), t4 = nodes(5);
	init();
	Matrix alpha(1,3);
	alpha << -t0*t0*t0 << 3.0*t0*t0 << -3.0*t0;
	Matrix beta(3,3);
	beta << -t0*t0*t2 << t0*(t0+2.0*t2) << -(2.0*t0+t2) \
		<< -t0*t1*t3 << (t0*t1+t0*t3+t1*t3) << -(t0+t1+t3) \
		<< -t1*t1*t4 << t1*(t1+2.0*t4) << -(2.0*t1+t4);
	Matrix gamma(3,3);
	gamma << -t3*t3*t0 << t3*(t3+2.0*t0) << -(2.0*t3+t0) \
		<< -t4*t1*t3 << (t4*t1+t4*t3+t1*t3) << -(t4+t1+t3) \
		<< -t4*t4*t2 << t4*(t4+2.0*t2) << -(2.0*t4+t2);
	Matrix delta(1,3);
	delta << -t4*t4*t4 << 3.0*t4*t4 << -3.0*t4;

	Real tmp0, tmp1, tmp2, tmp3;

	if (!isZero(_a0))
	{
		_H0 = Matrix(4,4);
		tmp0 = alpha(1,1)/_a0;
		tmp1 = alpha(1,2)/_a0;
		tmp2 = alpha(1,3)/_a0;
		tmp3 = 1.0/_a0;
		_H0 << tmp0 << tmp1 << tmp2 << tmp3 \
			<< tmp1 << 2.0*tmp2 << 3.0*tmp3 << 0.0 \
			<< 2.0*tmp2 << 6.0*tmp3 << 0.0 << 0.0 \
			<< 6.0*tmp3 << 0.0 << 0.0 << 0.0;
	}

	if (!isZero(_b0) && !isZero(_b1) && !isZero(_b2))
	{
		_H1 = Matrix(4,4);
		tmp0 = beta(1,1)/_b0 + beta(2,1)/_b1 + beta(3,1)/_b2;
		tmp1 = beta(1,2)/_b0 + beta(2,2)/_b1 + beta(3,2)/_b2;
		tmp2 = beta(1,3)/_b0 + beta(2,3)/_b1 + beta(3,3)/_b2;
		tmp3 = 1.0/_b0 + 1.0/_b1 + 1.0/_b2;
		_H1 << tmp0 << tmp1 << tmp2 << tmp3 \
			<< tmp1 << 2.0*tmp2 << 3.0*tmp3 << 0.0 \
			<< 2.0*tmp2 << 6.0*tmp3 << 0.0 << 0.0 \
			<< 6.0*tmp3 << 0.0 << 0.0 << 0.0;
	}

	if (!isZero(_c0) && !isZero(_c1) && !isZero(_c2))
	{
		_H2 = Matrix(4,4);
		tmp0 = gamma(1,1)/_c0 + gamma(2,1)/_c1 + gamma(3,1)/_c2;
		tmp1 = gamma(1,2)/_c0 + gamma(2,2)/_c1 + gamma(3,2)/_c2;
		tmp2 = gamma(1,3)/_c0 + gamma(2,3)/_c1 + gamma(3,3)/_c2;
		tmp3 = 1.0/_c0 + 1.0/_c1 + 1.0/_c2;
		_H2 << tmp0 << tmp1 << tmp2 << tmp3 \
			<< tmp1 << 2.0*tmp2 << 3.0*tmp3 << 0.0 \
			<< 2.0*tmp2 << 6.0*tmp3 << 0.0 << 0.0 \
			<< 6.0*tmp3 << 0.0 << 0.0 << 0.0;
	}

	if (!isZero(_d0))
	{
		_H3 = Matrix(4,4);
		tmp0 = delta(1,1)/_d0;
		tmp1 = delta(1,2)/_d0;
		tmp2 = delta(1,3)/_d0;
		tmp3 = 1.0/_d0;
		_H3 << tmp0 << tmp1 << tmp2 << tmp3 \
			<< tmp1 << 2.0*tmp2 << 3.0*tmp3 << 0.0 \
			<< 2.0*tmp2 << 6.0*tmp3 << 0.0 << 0.0 \
			<< 6.0*tmp3 << 0.0 << 0.0 << 0.0;
	}
}

K5Domain CubicSpline::domain( Real u ) const
{
	Real k1 = getKnot(1), k2 = getKnot(2), k3 = getKnot(3), k4 = getKnot(4), k5 = getKnot(5);

// #ifdef MATRIX_FORM
// 	int s0 = _H0.size(), s1= _H1.size(), s2 = _H2.size(), s3 = _H3.size();
// 	if (s0>0 && (s1+s2+s3)==0)
// 	{
// 		return K5_E1;
// 	}
// 	else if (s1>0 && (s0+s2+s3)==0)
// 	{
// 		return K5_E2;
// 	}
// 	else if (s2>0 && (s0+s1+s3)==0)
// 	{
// 		return K5_E3;
// 	}
// 	else if (s3>0 && (s0+s1+s2)==0)
// 	{
// 		return K5_E4;
// 	}
// #endif

	if( (k1<=u && k2>u) || (isEqual(k5,k2) && isEqual(u,k2)) )
	{
		return K5_E1;
	}
	else if((k2<=u && k3>u) || (isEqual(k5,k3) && isEqual(u,k3)))
	{
		return K5_E2;
	}
	else if((k3<=u && k4>u) || (isEqual(k5,k4) && isEqual(u,k4)))
	{
		return K5_E3;
	}
	else if(k4<=u && k5>=u)
	{
		return K5_E4;
	}
	else
	{
		return K5_OUT;
	}
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

Real SplineBase::getKnot( int i ) const
{
	return _knots(i);
}

void SplineBase::setKnots( const ColumnVector &k )
{
	_knots = k;
#ifndef MATRIX_FORM
	init();
#else
	init_m();
#endif
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

RBD_COMMON::Real SplineBase::baseFunc_m( Real u ) const
{
	return 0.0;
}

RBD_COMMON::Real SplineBase::baseFunc1st_m( Real u ) const
{
	return 0.0;
}

RBD_COMMON::Real SplineBase::baseFunc2nd_m( Real u ) const
{
	return 0.0;
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

Real CrossSpline::baseFunc_m( Real u, Real v ) const
{
	return (_spline_u->baseFunc_m(u))* (_spline_v->baseFunc_m(v));
}

Real CrossSpline::baseFunc1stU( Real u, Real v ) const
{
	return (_spline_u->baseFunc1st(u))*(_spline_v->baseFunc(v));
}

Real CrossSpline::baseFunc1stU_m( Real u, Real v ) const
{
	return (_spline_u->baseFunc1st_m(u))*(_spline_v->baseFunc_m(v));
}

Real CrossSpline::baseFunc1stV( Real u, Real v ) const
{
	return (_spline_u->baseFunc(u))*(_spline_v->baseFunc1st(v));
}

Real CrossSpline::baseFunc1stV_m( Real u, Real v ) const
{
	return (_spline_u->baseFunc_m(u))*(_spline_v->baseFunc1st_m(v));
}

Real CrossSpline::baseFunc2ndU( Real u, Real v ) const
{
	return (_spline_u->baseFunc2nd(u))*(_spline_v->baseFunc(v));
}

Real CrossSpline::baseFunc2ndU_m( Real u, Real v ) const
{
	return (_spline_u->baseFunc2nd_m(u))*(_spline_v->baseFunc_m(v));
}

Real CrossSpline::baseFunc2ndV( Real u, Real v ) const
{
	return (_spline_u->baseFunc(u))*(_spline_v->baseFunc2nd(v));
}

Real CrossSpline::baseFunc2ndV_m( Real u, Real v ) const
{
	return (_spline_u->baseFunc_m(u))*(_spline_v->baseFunc2nd_m(v));
}

Real CrossSpline::baseFunc2ndUV( Real u, Real v ) const
{
	return (_spline_u->baseFunc1st(u))*(_spline_v->baseFunc1st(v));
}

Real CrossSpline::baseFunc2ndUV_m( Real u, Real v ) const
{
	return (_spline_u->baseFunc1st_m(u))*(_spline_v->baseFunc1st_m(v));
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
	:_tmx(4,4), _tmy(4,4), _tmz(4,4), _tm1(4,4)
{
	_cross_spline = makePtr<CrossCubicSpline>();
	_tmx = 0, _tmy = 0,	_tmz = 0, _tm1 = 0;
}

BlendingEquation::~BlendingEquation()
{

}

Point3D BlendingEquation::computePoint(Real u, Real v)
{
	Point3D numerator(0.0, 0.0, 0.0);
	Real denominator = 0.0;
	VRPVK::iterator iter;
	for (iter = _rational_points_with_knots.begin(); \
		iter != _rational_points_with_knots.end(); iter++)
	{
		_cross_spline->setUVNodes(iter->getUNodesAsColumnVector(),
			iter->getVNodesAsColumnVector());
#ifndef MATRIX_FORM
		Real nuv = _cross_spline->baseFunc(u, v);
#else
		Real nuv = _cross_spline->baseFunc_m(u, v);
#endif
		Point3D point(iter->x(), iter->y(), iter->z());
		Real w = (iter->weight);
		numerator += (point * nuv * w);
		denominator += (nuv * w);
	}
	return safeDivide(numerator, denominator);
}

Point3D BlendingEquation::computePoint( const Parameter &p )
{
	return computePoint(p.s(), p.t());
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
#ifndef MATRIX_FORM
		Real nuv = _cross_spline->baseFunc(u, v);
		Real dnu = _cross_spline->baseFunc1stU(u, v);
		Real dnv = _cross_spline->baseFunc1stV(u, v);
#else
		Real nuv = _cross_spline->baseFunc_m(u, v);
		Real dnu = _cross_spline->baseFunc1stU_m(u, v);
		Real dnv = _cross_spline->baseFunc1stV_m(u, v);
#endif
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
#ifndef MATRIX_FORM
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

//   	Real nuv = _cross_spline->baseFunc_m(u, v);
// 		Real dnu = _cross_spline->baseFunc1stU_m(u, v);
// 		Real dnv = _cross_spline->baseFunc1stV_m(u, v);

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
#else
	std::vector<K5Domain> domainu,domainv;
	getDomain(u, v, domainu, domainv);

	if(_lastu.empty() || _lastv.empty())
	{
		initializeTensorMatrices(u, v);
	}
	else
	{
		if((domainu == _lastu) && (domainv == _lastv))
		{
		}
		else
		{
			updateTensorMatrices(domainu, domainv);	
		}
	}

	_lastu = domainu;
	_lastv = domainv;

	ColumnVector uup(4), vup(4);
	uup << 1 << u << u*u << u*u*u;
	vup << 1 << v << v*v << v*v*v;
	Matrix mx = uup.AsRow() * _tmx * vup.AsColumn();
	Matrix my = uup.AsRow() * _tmy * vup.AsColumn();
	Matrix mz = uup.AsRow() * _tmz * vup.AsColumn();
	Matrix mw = uup.AsRow() * _tm1 * vup.AsColumn();
	
	point = Point3D(mx(1,1)/mw(1,1), my(1,1)/mw(1,1), mz(1,1)/mw(1,1));

	Point3D pdbuw, pdbvw;
	Real dbuw = 0.0, dbvw = 0.0;
	ColumnVector duup(4), dvup(4);
	duup << 0 << 1 << 2*u << 3*u*u;
	dvup << 0 << 1 << 2*v << 3*v*v;
	Matrix dmxu = duup.AsRow() * _tmx * vup.AsColumn();
	Matrix dmyu = duup.AsRow() * _tmy * vup.AsColumn();
	Matrix dmzu = duup.AsRow() * _tmz * vup.AsColumn();
	Matrix dmu = duup.AsRow() * _tm1 * vup.AsColumn();

	Matrix dmxv = uup.AsRow() * _tmx * dvup.AsColumn();
	Matrix dmyv = uup.AsRow() * _tmy * dvup.AsColumn();
	Matrix dmzv = uup.AsRow() * _tmz * dvup.AsColumn();
	Matrix dmv = uup.AsRow() * _tm1 * dvup.AsColumn();

	pdbuw = Point3D(dmxu(1,1), dmyu(1,1), dmzu(1,1));
	pdbvw = Point3D(dmxv(1,1), dmyv(1,1), dmzv(1,1));
	dbuw = dmu(1,1);
	dbvw = dmv(1,1);
	
	Vector3D dsdu = (pdbuw - point*dbuw)*(1/mw(1,1));
	Vector3D dsdv = (pdbvw - point*dbvw)*(1/mw(1,1));

	normal = dsdu * dsdv; normal.normalize();
#endif
}

void BlendingEquation::computePointAndNormal( const Parameter &p, Point3D &point, Vector3D &normal )
{
	computePointAndNormal(p.s(), p.t(), point, normal);
}

NEWMAT::ReturnMatrix BlendingEquation::computeFirstDerivative( const DERIVE_SUFFIX der, const Real u, const Real v )
{
	ColumnVector B(3), dB(3), S(3);
	B = 0, dB = 0, S = 0;//lyz
	Real W = 0, dW = 0.0;

	for (VRPVK::iterator iter = _rational_points_with_knots.begin(); \
		iter != _rational_points_with_knots.end(); iter++)
	{
		CrossSplinePtr cross_spline = (*iter).cross_spline;
// 		cross_spline->setUVNodes(iter->getUNodesAsColumnVector(),
// 			iter->getVNodesAsColumnVector());
#ifndef MATRIX_FORM
		Real Bi = cross_spline->baseFunc(u, v);
#else
		Real Bi = cross_spline->baseFunc_m(u, v);
#endif
		Real dBi = 0.0;
		switch (der)
		{
		case DER_U:
#ifndef MATRIX_FORM
			dBi = cross_spline->baseFunc1stU(u, v);
#else
			dBi = cross_spline->baseFunc1stU_m(u, v);
#endif
			break;
		case  DER_V:
#ifndef MATRIX_FORM
			dBi = cross_spline->baseFunc1stV(u, v);
#else
			dBi = cross_spline->baseFunc1stV_m(u, v);
#endif
			break;
		}

		Real Wi = (iter->weight);
		ColumnVector Pi(3);	Pi << iter->x() << iter->y() << iter->z();

		B += Pi * Bi * Wi;
		W += Bi * Wi;
		dW += dBi * Wi;
		dB += Pi * dBi * Wi;
	}

	S = B/W;
	ColumnVector dS = (1.0/W) * (dB - dW * S);
	dS.Release();
	return dS;
}

NEWMAT::ReturnMatrix BlendingEquation::computeFirstDerivative( const DERIVE_SUFFIX der, const Parameter &p )
{
	return computeFirstDerivative(der, p.s(), p.t());
}

NEWMAT::ReturnMatrix BlendingEquation::computeUpToFirstDerivatives( const Real u, const Real v )
{
	ColumnVector B(3), dB_u(3), dB_v(3);
	B = 0, dB_u = 0, dB_v = 0;//lyz
	Real W = 0, dW_u = 0.0, dW_v = 0.0;

	for (VRPVK::iterator iter = _rational_points_with_knots.begin(); \
		iter != _rational_points_with_knots.end(); iter++)
	{
		CrossSplinePtr cross_spline = (*iter).cross_spline;
// 		_cross_spline->setUVNodes(iter->getUNodesAsColumnVector(),
// 			iter->getVNodesAsColumnVector());
#ifndef MATRIX_FORM
		Real Bi = cross_spline->baseFunc(u, v);
		Real dBi_u = cross_spline->baseFunc1stU(u, v);
		Real dBi_v = cross_spline->baseFunc1stV(u, v);
#else
		Real Bi = cross_spline->baseFunc_m(u, v);
		Real dBi_u = cross_spline->baseFunc1stU_m(u, v);
		Real dBi_v = cross_spline->baseFunc1stV_m(u, v);
#endif
		Real Wi = (iter->weight);
		ColumnVector Pi(3);	Pi << iter->x() << iter->y() << iter->z();

		B += Pi * Bi * Wi;
		W += Bi * Wi;
		dW_u += dBi_u * Wi;
		dW_v += dBi_v * Wi;
		dB_u += Pi * dBi_u * Wi;
		dB_v += Pi * dBi_v * Wi;
	}

	ColumnVector S = B / W;
	ColumnVector dS_u = (1.0/W) * (dB_u - dW_u * S);
	ColumnVector dS_v = (1.0/W) * (dB_v - dW_v * S);

	Matrix Ss = dS_u | dS_v | S;
	Ss.Release();
	return Ss;
}

NEWMAT::ReturnMatrix BlendingEquation::computeUpToFirstDerivatives( const Parameter &p )
{
	return computeUpToFirstDerivatives(p.s(), p.t());
}

NEWMAT::ReturnMatrix BlendingEquation::computeSecondDerivative( const DERIVE_SUFFIX der1, const DERIVE_SUFFIX der2, const Real u, const Real v )
{
	ColumnVector B(3), dB_u(3), dB_v(3), ddB_uu(3), ddB_vv(3), ddB_uv(3);
	B = 0, dB_u = 0, dB_v = 0, ddB_uu = 0, ddB_vv = 0, ddB_uv = 0;//lyz
	Real W = 0, dW_u = 0.0, dW_v = 0.0, ddW_uu = 0.0, ddW_vv= 0.0, ddW_uv= 0.0;

	for (VRPVK::iterator iter = _rational_points_with_knots.begin(); \
		iter != _rational_points_with_knots.end(); iter++)
	{
		ColumnVector Pi(3);	Pi << iter->x() << iter->y() << iter->z();
		Real Wi = (iter->weight);

		CrossSplinePtr cross_spline = (*iter).cross_spline;
// 		_cross_spline->setUVNodes(iter->getUNodesAsColumnVector(),
// 			iter->getVNodesAsColumnVector());
#ifndef MATRIX_FORM
		Real Bi = cross_spline->baseFunc(u, v);
#else
		Real Bi = cross_spline->baseFunc_m(u, v);
#endif
		Real dBi_u = 0.0, dBi_v=0.0, ddBi_uu = 0.0, ddBi_vv = 0.0, ddBi_uv = 0.0;
		B += Pi * Bi * Wi;
		W += Bi * Wi;

		if (der1 == DER_U && der2 == DER_U)
		{
#ifndef MATRIX_FORM
			dBi_u = cross_spline->baseFunc1stU(u, v);
			ddBi_uu = cross_spline->baseFunc2ndU(u, v);
#else
			dBi_u = cross_spline->baseFunc1stU_m(u, v);
			ddBi_uu = cross_spline->baseFunc2ndU_m(u, v);
#endif
			dW_u += dBi_u * Wi;
			ddW_uu += ddBi_uu * Wi;
			ddB_uu += Pi * ddBi_uu * Wi;
			dB_u += Pi * dBi_u * Wi;
		}
		else if (der1 == DER_V && der2 == DER_V)
		{
#ifndef MATRIX_FORM
			dBi_v = cross_spline->baseFunc1stV(u, v);
			ddBi_vv = cross_spline->baseFunc2ndV(u, v);
#else
			dBi_v = cross_spline->baseFunc1stV_m(u, v);
			ddBi_vv = cross_spline->baseFunc2ndV_m(u, v);
#endif
			dW_v += dBi_v * Wi;
			ddW_vv += ddBi_vv * Wi;
			ddB_vv += Pi * ddBi_vv * Wi;
			dB_v += Pi * dBi_v * Wi;
		}
		else
		{
#ifndef MATRIX_FORM
			dBi_u = cross_spline->baseFunc1stU(u, v);
			dBi_v = cross_spline->baseFunc1stV(u, v);
			ddBi_uu = cross_spline->baseFunc2ndU(u, v);
			ddBi_vv = cross_spline->baseFunc2ndV(u, v);
			ddBi_uv = cross_spline->baseFunc2ndUV(u, v);
#else
			dBi_u = cross_spline->baseFunc1stU_m(u, v);
			dBi_v = cross_spline->baseFunc1stV_m(u, v);
			ddBi_uu = cross_spline->baseFunc2ndU_m(u, v);
			ddBi_vv = cross_spline->baseFunc2ndV_m(u, v);
			ddBi_uv = cross_spline->baseFunc2ndUV_m(u, v);
#endif

			dW_u += dBi_u * Wi;
			dB_u += Pi * dBi_u * Wi;

			dW_v += dBi_v * Wi;
			dB_v += Pi * dBi_v * Wi;

			ddW_uv += ddBi_uv * Wi;
			ddB_uv += Pi * ddBi_uv * Wi;

			ddW_uu += ddBi_uu * Wi;
			ddB_uu += Pi * ddBi_uu * Wi;

			ddW_vv += ddBi_vv * Wi;
			ddB_vv += Pi * ddBi_vv * Wi;
		}
	}

	ColumnVector S = B / W;
	ColumnVector ddS(3);
	if (der1 == DER_U && der2 == DER_U)
	{
		ColumnVector dS_u = (1.0/W) * (dB_u - dW_u*S);
		ddS = (1.0/W) * (ddB_uu - 2.0*dW_u*dS_u - ddW_uu*S);
	}
	else if (der1 == DER_V && der2 == DER_V)
	{
		ColumnVector dS_v = (1/W) * (dB_v - dW_v*S);
		ddS = (1.0/W) * (ddB_vv - 2.0*dW_v*dS_v - ddW_vv*S);//lyz
	}
	else
	{
		ColumnVector dS_u = (1.0/W) * (dB_u - dW_u*S);
		ColumnVector dS_v = (1.0/W) * (dB_v - dW_v*S);//lyz
		ddS = (1.0/W) * (ddB_uv - ddW_uv*S - dW_u*dS_v - dW_v*dS_u);
	}

	ddS.Release();
	return ddS;
}

NEWMAT::ReturnMatrix BlendingEquation::computeSecondDerivative( const DERIVE_SUFFIX der1, const DERIVE_SUFFIX der2, const Parameter &p )
{
	return computeSecondDerivative(der1, der2, p.s(), p.t());
}

NEWMAT::ReturnMatrix BlendingEquation::computeUpToSecondDerivatives( const Real u, const Real v )
{
	ColumnVector B(3), dB_u(3), dB_v(3), ddB_uu(3), ddB_vv(3), ddB_uv(3);
	B = 0, dB_u = 0, dB_v = 0, ddB_uu = 0, ddB_vv = 0, ddB_uv = 0;//lyz
	Real W = 0, dW_u = 0.0, dW_v = 0.0, ddW_uu = 0.0, ddW_vv= 0.0, ddW_uv= 0.0;

	for (VRPVK::iterator iter = _rational_points_with_knots.begin(); \
		iter != _rational_points_with_knots.end(); iter++)
	{
		ColumnVector Pi(3);	Pi << iter->x() << iter->y() << iter->z();
		Real Wi = (iter->weight);

		CrossSplinePtr cross_spline = (*iter).cross_spline;
// 		_cross_spline->setUVNodes(iter->getUNodesAsColumnVector(),
// 			iter->getVNodesAsColumnVector());
#ifndef MATRIX_FORM
		Real Bi = cross_spline->baseFunc(u, v);
#else
		Real Bi = cross_spline->baseFunc_m(u, v);
#endif
		Real dBi_u = 0.0, dBi_v=0.0, ddBi_uu = 0.0, ddBi_vv = 0.0, ddBi_uv = 0.0;
		B += Pi * Bi * Wi;
		W += Bi * Wi;

#ifndef MATRIX_FORM
		dBi_u = cross_spline->baseFunc1stU(u, v);
		ddBi_uu = cross_spline->baseFunc2ndU(u, v);
		dBi_v = cross_spline->baseFunc1stV(u, v);
		ddBi_vv = cross_spline->baseFunc2ndV(u, v);
		ddBi_uv = cross_spline->baseFunc2ndUV(u, v);
#else
		dBi_u = cross_spline->baseFunc1stU_m(u, v);
		ddBi_uu = cross_spline->baseFunc2ndU_m(u, v);
		dBi_v = cross_spline->baseFunc1stV_m(u, v);
		ddBi_vv = cross_spline->baseFunc2ndV_m(u, v);
		ddBi_uv = cross_spline->baseFunc2ndUV_m(u, v);
#endif

		dW_u += dBi_u * Wi;
		dB_u += Pi * dBi_u * Wi;
		ddW_uu += ddBi_uu * Wi;
		ddB_uu += Pi * ddBi_uu * Wi;

		dW_v += dBi_v * Wi;
		dB_v += Pi * dBi_v * Wi;
		ddW_vv += ddBi_vv * Wi;
		ddB_vv += Pi * ddBi_vv * Wi;

		ddW_uv += ddBi_uv * Wi;
		ddB_uv += Pi * ddBi_uv * Wi;
	}

	ColumnVector S = B / W;
	ColumnVector dS_u = (1.0/W) * (dB_u - dW_u*S);
	ColumnVector dS_v = (1.0/W) * (dB_v - dW_v*S);

	ColumnVector ddS_uu = (1.0/W) * (ddB_uu - 2.0*dW_u*dS_u - ddW_uu*S);
	ColumnVector ddS_vv = (1.0/W) * (ddB_vv - 2.0*dW_v*dS_v - ddW_vv*S);
	ColumnVector ddS_uv = (1.0/W) * (ddB_uv - ddW_uv*S - dW_u*dS_v - dW_v*dS_u);

	Matrix Ss = ddS_uu | ddS_uv | ddS_vv | dS_u | dS_v | S;

	Ss.Release(); return Ss;
}

NEWMAT::ReturnMatrix BlendingEquation::computeUpToSecondDerivatives( const Parameter &p )
{
	return computeUpToSecondDerivatives(p.s(), p.t());
}

void BlendingEquation::addRationalPointWithNodes( const std::vector<Real> &u_knots, const std::vector<Real> &v_knots, Point3D &point, Real weight )
{
	RationalPoint3DWithUVNodes rpwk(point.x(), point.y(), point.z(), weight);
	
	rpwk.setUNodes(u_knots);
	rpwk.setVNodes(v_knots);
	rpwk.setCrossSpline();

	_rational_points_with_knots.push_back(rpwk);
}

#ifdef MATRIX_FORM
void BlendingEquation::computeTensorMatrices( Matrix &tmx, Matrix &tmy, Matrix &tmz, Matrix &tm1, 
											 Real u, Real v, std::vector<K5Domain> lastu, 
											 std::vector<K5Domain> lastv)
{
// 	tmx = TensorProduct(ColumnVector(4), ColumnVector(4));
// 	tmy = TensorProduct(ColumnVector(4), ColumnVector(4));
// 	tmz = TensorProduct(ColumnVector(4), ColumnVector(4));
// 	tm1 = TensorProduct(ColumnVector(4), ColumnVector(4));
	tmx = Matrix(4,4);
	tmy = Matrix(4,4);
	tmz = Matrix(4,4);
	tm1 = Matrix(4,4);
	tmx = 0; tmy = 0; tmz = 0; tm1 = 0;

	CrossCubicSplinePtr cross_spline = makePtr<CrossCubicSpline>();
	VRPVK::iterator iter;
	for (iter = _rational_points_with_knots.begin(); \
		iter != _rational_points_with_knots.end(); iter++)
	{
		cross_spline->setUVNodes(iter->getUNodesAsColumnVector(),
			iter->getVNodesAsColumnVector());
		CubicSplinePtr su = castPtr<CubicSpline>(cross_spline->spline_u());
		CubicSplinePtr sv = castPtr<CubicSpline>(cross_spline->spline_v());
		Point3D point(iter->x(), iter->y(), iter->z());
		Real w = (iter->weight);

		K5Domain current_domainu = su->domain(u);
		K5Domain current_domainv = sv->domain(v);
		Matrix hu = su->H(su->domain(u));
		Matrix hv = sv->H(sv->domain(v));

		Matrix tp(4,4);
		if(hu.size() == 0 || hv.size() == 0)
			tp = 0;
		else
			tp = TensorProduct(hu.row(1), hv.row(1));
		tmx += iter->x() * tp;
		tmy += iter->y() * tp;
		tmz += iter->z() * tp;
		tm1 += tp;


	}
}

void BlendingEquation::getDomain( Real u, Real v, std::vector<K5Domain> &domainu, std::vector<K5Domain> &domainv )
{
	VRPVK::iterator iter;
	for (iter = _rational_points_with_knots.begin(); \
		iter != _rational_points_with_knots.end(); iter++)
	{
		CubicSplinePtr su = castPtr<CubicSpline>((*iter).cross_spline->spline_u());
		CubicSplinePtr sv = castPtr<CubicSpline>((*iter).cross_spline->spline_v());

		domainu.push_back(su->domain(u));
		domainv.push_back(sv->domain(v));
	}
}

void BlendingEquation::initializeTensorMatrices(Real u, Real v)
{
	VRPVK::iterator iter;
	for (iter = _rational_points_with_knots.begin(); \
		iter != _rational_points_with_knots.end(); iter++)
	{
		CubicSplinePtr su = castPtr<CubicSpline>((*iter).cross_spline->spline_u());
		CubicSplinePtr sv = castPtr<CubicSpline>((*iter).cross_spline->spline_v());

		Matrix hu = su->H(su->domain(u));
		Matrix hv = sv->H(sv->domain(v));

		Matrix tp(4,4);
		if(hu.size() == 0 || hv.size() == 0)
		{
			tp = 0;
		}
		else
		{
			tp = KP(hu.row(1).AsColumn(), hv.row(1));
		}
		_tmx += (iter->x() * iter->weight) * tp ;
		_tmy += (iter->y() * iter->weight) * tp ;
		_tmz += (iter->z() * iter->weight) * tp ;
		_tm1 += tp * iter->weight;
	}
}

void BlendingEquation::updateTensorMatrices( std::vector<K5Domain> domainu, std::vector<K5Domain> domainv )
{
	std::vector<int> difu, difv;
	if(domainu != _lastu)
	{
		std::transform(domainu.begin(), domainu.end(), _lastu.begin(), std::back_inserter(difu), 
			[&](K5Domain a, K5Domain b){return a-b;});
	}
	if(domainv != _lastv)
	{
		std::transform(domainv.begin(), domainv.end(), _lastv.begin(), std::back_inserter(difv),
			[&](K5Domain a, K5Domain b){return a-b;});
	}
		
	std::vector<int> updateposu, updateposv;
	if(!difu.empty())
	{
		for (std::vector<int>::iterator it = difu.begin();
			it != difu.end();it++)
		{
			if(*it != 0)
				updateposu.push_back(std::distance(difu.begin(), it));
		}
	}
	
	if(!difv.empty())
	{
		for (std::vector<int>::iterator it = difv.begin();
			it != difv.end();it++)
		{
			if(*it != 0)
				updateposv.push_back(std::distance(difv.begin(), it));
		}
	}
	
	std::vector<int> updatepos;
	if(updateposu.empty())
	{
		updatepos = updateposv;
	}
	else if(updateposv.empty())
	{
		updatepos = updateposu;
	}
	else
	{
		updatepos.resize(updateposu.size() + updateposv.size());
		std::vector<int>::iterator it = std::set_union(updateposu.begin(), updateposu.end(),
			updateposv.begin(), updateposv.end(), updatepos.begin());
		updatepos.resize(it - updatepos.begin());
	}
	
	for (std::vector<int>::iterator it_pos = updatepos.begin();
		it_pos != updatepos.end();it_pos++)
	{
		RationalPoint3DWithUVNodes rpvk = _rational_points_with_knots[*it_pos];
		CubicSplinePtr su = castPtr<CubicSpline>(rpvk.cross_spline->spline_u());
		CubicSplinePtr sv = castPtr<CubicSpline>(rpvk.cross_spline->spline_v());

		Matrix tp_old(4,4), tp_new(4,4);
		if(_lastu[*it_pos] == K5_OUT || _lastv[*it_pos] == K5_OUT)
		{
			tp_old = 0;
		}
		else
		{
			Matrix hu = su->H(_lastu[*it_pos]);
			Matrix hv = sv->H(_lastv[*it_pos]);
			tp_old = KP(hu.row(1).AsColumn(), hv.row(1));
		}
		if(domainu[*it_pos] == K5_OUT || domainv[*it_pos] == K5_OUT)
		{
			tp_new = 0;
		}
		else
		{
			Matrix hu = su->H(domainu[*it_pos]);
			Matrix hv = sv->H(domainv[*it_pos]);
			tp_new = KP(hu.row(1).AsColumn(), hv.row(1));
		}

		_tmx = _tmx + (rpvk.x() * rpvk.weight) * (tp_new - tp_old) ;
		_tmy = _tmy + (rpvk.y() * rpvk.weight) * (tp_new - tp_old) ;
		_tmz = _tmz + (rpvk.z() * rpvk.weight) * (tp_new - tp_old) ;
		_tm1 = _tm1 + (tp_new - tp_old) * rpvk.weight;
	}
}

#endif


#ifdef use_namespace
}
#endif