/*
TSPLINE -- A T-spline object oriented package in C++
Copyright (C) 2015-  Wenlei Xiao

This library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation; either version 2.1 of the
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
2016/04/02: Wenlei Xiao
- Doxygen comments added.
2016/10/09: Wenlei Xiao, Yazui Liu
- Analytical and matrix forms of basis functions added.
-------------------------------------------------------------------------------
*/

#ifndef __cplusplus
#error Must use C++ for the spline
#endif
#ifndef SPLINEBASE_H
#define SPLINEBASE_H

/**  @file  [splbase]  
  *  @brief  Spline base classes
  *  @author  <Wenlei Xiao>  
  *  @date  <2015.04.08>  
  *  @version  <v1.1>  
  *  @note  
  *  The spline base classes provide some basic spline calculations.
*/

#include "basis.h"
#include <assert.h>

#ifdef use_namespace
namespace TSPLINE {
  using namespace NEWMAT;
#endif

DECLARE_SMARTPTR(SplineBase)

/**  
  *  @class  <SplineBase> 
  *  @brief  Base class of splines 
  *  @note  
  *  SplineBase provides a universal data structure and calculating functions.
*/
class SplineBase
{
public:
	SplineBase();
	SplineBase(unsigned int order);
	SplineBase(const std::vector<Real> &vnodes, unsigned int order);
	virtual ~SplineBase();
	
public:
	/** Initialize the knots using the stream operator*/
	void operator<<(const double* r);
	void operator<<(const float* r);
	void operator<<(const int* r);

	/** Get the knots as a column vector*/
	ColumnVector getKnots() const;
	Real getKnot(int i) const;
	/** Get the knots from a column vector*/
	void setKnots(const ColumnVector &k);

public:
	/** Calculate the basic derivation. (universal algorithm) */
	virtual Real baseFunc(Real u) const;
	virtual Real baseFunc_m(Real u) const;
	/** Calculate the first oder basic derivation. (universal algorithm) */
	virtual Real baseFunc1st(Real u) const;
	virtual Real baseFunc1st_m(Real u) const;
	/** Calculate the second oder basic derivation. (universal algorithm) */
	virtual Real baseFunc2nd(Real u) const;
	virtual Real baseFunc2nd_m(Real u) const;

protected:
	Real Nip(unsigned int i, unsigned int p, Real u) const;

	virtual void init() {}
	virtual void init_m() {}

private:
	ColumnVector _knots;	
	unsigned int _order;	
};

DECLARE_SMARTPTR(QuadraticSpline)
/**  
  *  @class  <QuadraticSpline> 
  *  @brief  Quadratic spline  
  *  @note
  *  Quadratic spline means the oder equals to 2.
*/
class QuadraticSpline : public SplineBase
{
public:
	QuadraticSpline();
	QuadraticSpline(const std::vector<Real> &vnodes);

	virtual ~QuadraticSpline();

public:
	/** Calculate the quadratic basis function. */
	virtual Real baseFunc(Real u) const;
	/** Calculate the first order of quadratic basis function. */
	virtual Real baseFunc1st(Real u) const;
	/** Calculate the second order of quadratic basis function. */
	virtual Real baseFunc2nd(Real u) const;
};

enum K5Domain {K5_OUT, K5_E1, K5_E2, K5_E3, K5_E4};
DECLARE_SMARTPTR(CubicSpline)
/**  
  *  @class  <CubicSpline> 
  *  @brief  Cubic spline 
  *  @note  
  *  Cubic spline means the oder equals to 3.
*/
class CubicSpline : public SplineBase
{
public:
	CubicSpline();
	CubicSpline(const std::vector<Real> &vnodes);

	virtual ~CubicSpline();

public:
	/** Calculate the cubic basis function. */
	virtual Real baseFunc(Real u) const;
	virtual Real baseFunc_m(Real u) const;
	/** Calculate the first order of cubic basis function. */
	virtual Real baseFunc1st(Real u) const;
	virtual Real baseFunc1st_m(Real u) const;
	/** Calculate the second order of cubic basis function. */
	virtual Real baseFunc2nd(Real u) const;
	virtual Real baseFunc2nd_m(Real u) const;

	//////////////////////////////////////////////////////////////////////////
	ReturnMatrix H0() { return _H0; }
	ReturnMatrix H1() { return _H1; }
	ReturnMatrix H2() { return _H2; }
	ReturnMatrix H3() { return _H3; }

	K5Domain domain(Real u) const;
	ReturnMatrix H(const K5Domain d) const
	{
		switch (d)
		{
		case TSPLINE::K5_OUT:
			return Matrix();
			break;
		case TSPLINE::K5_E1:
			return _H0;
			break;
		case TSPLINE::K5_E2:
			return _H1;
			break;
		case TSPLINE::K5_E3:
			return _H2;
			break;
		case TSPLINE::K5_E4:
			return _H3;
			break;
		default:
			return Matrix();
			break;
		}
	}

protected:
	virtual void init();
	virtual void init_m();
private:
	Real _a0, _b0, _b1, _b2, _c0, _c1, _c2, _d0;
	Matrix _H0, _H1, _H2, _H3;
};

DECLARE_SMARTPTR(CrossSpline)
/**  
  *  @class  <CrossSpline> 
  *  @brief  Cross spline  
  *  @note  
  *  CrossSpline contains two one-dimension splines to construct a two-dimension spline.
*/
class CrossSpline
{
public:
	CrossSpline(const SplineBasePtr &spline_u, const SplineBasePtr &spline_v);
	virtual ~CrossSpline();
public:
	/** Calculate the cross basis function. */
	Real baseFunc(Real u, Real v) const;
	Real baseFunc_m(Real u, Real v) const;
	/** Calculate the U first order of cross basis function. */
	Real baseFunc1stU(Real u, Real v) const;
	Real baseFunc1stU_m(Real u, Real v) const;
	/** Calculate the V first order of cross basis function. */
	Real baseFunc1stV(Real u, Real v) const;
	Real baseFunc1stV_m(Real u, Real v) const;
	/** Calculate the U second order of cross basis function. */
	Real baseFunc2ndU(Real u, Real v) const;
	Real baseFunc2ndU_m(Real u, Real v) const;
	/** Calculate the V second order of cross basis function. */
	Real baseFunc2ndV(Real u, Real v) const;
	Real baseFunc2ndV_m(Real u, Real v) const;
	/** Calculate the UV second order of cross basis function. */
	Real baseFunc2ndUV(Real u, Real v) const;
	Real baseFunc2ndUV_m(Real u, Real v) const;

	SplineBasePtr spline_u() { return _spline_u; }
	SplineBasePtr spline_v() { return _spline_v; }
public:
	/** Set the UV knots. */
	virtual void setUVNodes(const ColumnVector &ku, const ColumnVector &kv);
private:
	SplineBasePtr _spline_u;	
	SplineBasePtr _spline_v;	
};

DECLARE_SMARTPTR(CrossQuadraticSpline)
/**  
  *  @class  <CrossQuadraticSpline> 
  *  @brief  Cross quadratic spline  
  *  @note  
  *  CrossQuadraticSpline contains two one-dimension quadratic splines.
*/
class CrossQuadraticSpline : public CrossSpline
{
public:
	CrossQuadraticSpline();
	CrossQuadraticSpline(const QuadraticSplinePtr &spline_u, const QuadraticSplinePtr &spline_v);
	virtual ~CrossQuadraticSpline();
public:
	/** Set the UV knots. */
	virtual void setUVNodes(const ColumnVector &ku, const ColumnVector &kv);
};

DECLARE_SMARTPTR(CrossCubicSpline)
/**  
  *  @class  <CrossCubicSpline> 
  *  @brief  Cross cubic spline  
  *  @note  
  *  CrossCubicSpline contains two one-dimension cubic splines.
*/
class CrossCubicSpline : public CrossSpline
{
public:
	CrossCubicSpline();
	CrossCubicSpline(const CubicSplinePtr &spline_u, const CubicSplinePtr &spline_v);
	~CrossCubicSpline();
public:
	/** Set the UV knots. */
	virtual void setUVNodes(const ColumnVector &ku, const ColumnVector &kv);
};

DECLARE_SMARTPTR(BlendingEquation)
/**  
  *  @class  <BlendingEquation> 
  *  @brief  Blending equation  
  *  @note  
  *  BlendingEquation is used to compute the points and normals on a spline surface.
*/
class BlendingEquation
{
public:
	BlendingEquation();
	~BlendingEquation();

	/** Add a rational point with UV knots. */
	void addRationalPointWithNodes(const std::vector<Real> &u_knots, const std::vector<Real> &v_knots,
		Point3D &point, Real weight);
	/** Computer the point. */
	Point3D computePoint(Real u, Real v);
	/** Computer the point. */
	Point3D computePoint(const Parameter &p);
	/** Computer the normal. */
	Vector3D computeNormal(Real u, Real v);
	/** Computer the normal. */
	Vector3D computeNormal(const Parameter &p);
	/** Computer the point and normal. */
	void computePointAndNormal(Real u, Real v, Point3D &point, Vector3D &normal);
	/** Computer the point and normal. */
	void computePointAndNormal(const Parameter &p, Point3D &point, Vector3D &normal);

	enum DERIVE_SUFFIX{DER_U, DER_V};

	ReturnMatrix computeFirstDerivative(const DERIVE_SUFFIX der, const Real u, const Real v);
	ReturnMatrix computeFirstDerivative(const DERIVE_SUFFIX der, const Parameter &p);

	ReturnMatrix computeUpToFirstDerivatives(const Real u, const Real v);
	ReturnMatrix computeUpToFirstDerivatives(const Parameter &p);

	ReturnMatrix computeSecondDerivative(const DERIVE_SUFFIX der1, const DERIVE_SUFFIX der2, const Real u, const Real v);
	ReturnMatrix computeSecondDerivative(const DERIVE_SUFFIX der1, const DERIVE_SUFFIX der2, const Parameter &p);
	
	ReturnMatrix computeUpToSecondDerivatives(const Real u, const Real v);
	ReturnMatrix computeUpToSecondDerivatives(const Parameter &p);

	//////////////////////////////////////////////////////////////////////////
	void computeTensorMatrices(Matrix &tmx, Matrix &tmy, Matrix &tmz, Matrix &tm1,
		Real u, Real v, std::vector<K5Domain> lastu, std::vector<K5Domain> lastv);
	void initializeTensorMatrices(Real u, Real v);
	void updateTensorMatrices(std::vector<K5Domain> domainu, std::vector<K5Domain> domainv);

private:
	class RationalPoint3DWithUVNodes : public Point3D
	{
	public:
		RationalPoint3DWithUVNodes(Real x, Real y, Real z, Real w) : Point3D(x, y, z), weight(w) {cross_spline = makePtr<CrossCubicSpline>();}
		~RationalPoint3DWithUVNodes() {}
	public:
		Real weight;				
		std::vector<Real> u_knots;	
		std::vector<Real> v_knots;
		CrossSplinePtr cross_spline;
		void setCrossSpline()
		{
			cross_spline->setUVNodes(getUNodesAsColumnVector(), getVNodesAsColumnVector());
		}
		/** Set the U knots. */
		void setUNodes(const std::vector<Real> &vals)
		{
			u_knots.resize(vals.size());
			std::copy(vals.begin(), vals.end(), u_knots.begin());
		}
		/** Set the V knots. */
		void setVNodes(const std::vector<Real> &vals)
		{
			v_knots.resize(vals.size());
			std::copy(vals.begin(), vals.end(), v_knots.begin());
		}
		/** Return the U knots. */
		ColumnVector getUNodesAsColumnVector()
		{
			ColumnVector unodes(u_knots.size());
			for (int i=0;i<u_knots.size();i++)
			{
				unodes(i+1) = u_knots[i];
			}
			return unodes;
		}
		/** Return the V knots. */
		ColumnVector getVNodesAsColumnVector()
		{
			ColumnVector vnodes(v_knots.size());
			for (int i=0;i<v_knots.size();i++)
			{
				vnodes(i+1) = v_knots[i];
			}
			return vnodes;
		}
	};
	typedef std::vector<RationalPoint3DWithUVNodes> VRPVK;
	CrossSplinePtr _cross_spline;			
	VRPVK _rational_points_with_knots;

	Matrix _tmx, _tmy, _tmz, _tm1;

	std::vector<K5Domain> _lastu;
	std::vector<K5Domain> _lastv;
	void getDomain(Real u, Real v, std::vector<K5Domain> &domainu, std::vector<K5Domain> &domainv);
};

#ifdef use_namespace
}
#endif


#endif 

