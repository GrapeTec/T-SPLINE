/*
T-SPLINE -- A T-spline object oriented library in C++
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
2016/03/31: Wenlei Xiao
- Doxygen comments added.
-------------------------------------------------------------------------------
*/


/**  @file  [derivator]  
*  @brief  Derivator classes.
  *  @author  <Wenlei Xiao>  
  *  @date  <2016.03.31>  
  *  @version  <v1.0>  
  *  @note  
  *  The derivator classes include a global derivator (TDerivator) and a T-face derivator, which derive the points and normals of a T-spline.   
*/

#ifndef DERIVATOR_H
#define DERIVATOR_H

#include <utils.h>
#include <tspline.h>
#include <splbase.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

DECLARE_ASSISTANCES(TDerivator, TDrv)
DECLARE_ASSISTANCES(TFaceDerivator, TFacDrv)

/**  
  *  @class  <TDerivator> 
  *  @brief  Base class of derivators
  *  @note  
  *  The derivator is used to derive the points and normals on a T-spline surface.
*/
class TDerivator
{
public:
	TDerivator(const TSplinePtr &spline);
	virtual ~TDerivator();
public:
	/** Derive the zero oder point on the T-spline surface. */
	virtual int pointDerive(const Parameter &parameter, Point3D &point);
	/** Derive the first oder normal on the T-spline surface. */
	virtual int normalDerive(const Parameter &parameter, Vector3D &normal);
	/** Derive both the zero and the first oder point and normal on the T-spline surface. */
	virtual int pointAndNormalDerive(const Parameter &parameter, Point3D &point, Vector3D &normal);

	Real normalCurvature(const Parameter &parameter, Real ds, Real dt);
	void principalCurvature(const Parameter &parameter, Real &k1, Real &k2);

	virtual ReturnMatrix firstPartialDeriveU(const Parameter &parameter);
	virtual ReturnMatrix firstPartialDeriveV(const Parameter &parameter);
	virtual ReturnMatrix secondPartialDeriveUU(const Parameter &parameter);
	virtual ReturnMatrix secondPartialDeriveUV(const Parameter &parameter);
	virtual ReturnMatrix secondPartialDeriveVV(const Parameter &parameter);
	virtual ReturnMatrix secondPartialDerive(const Parameter &parameter);//uu uv vv u v s

	ReturnMatrix firstAndSecondFundamentalForm(const Parameter &parameter);
	
protected:
	TFacePtr findTFaceByParameter(const Parameter &parameter);
	BlendingEquationPtr prepareEquationByTFace(const TFacePtr &tface);
private:
	TSplinePtr _spline;
};

/**
  *  @class  <TFaceDerivator> 
  *  @brief  T-face derivator
  *  @note  
  *  The face derivator is used to derive the points and normals on a patch of a T-spline surface.
*/
class TFaceDerivator : public TDerivator
{
public:
	TFaceDerivator(const TSplinePtr &spline, const TFacePtr &face);
	virtual ~TFaceDerivator();
public:
	/** Get the specified T-face. */
	TFacePtr getFace() {return _face;}
	/** Derive the zero oder point on the T-face. */
	virtual int pointDerive(const Parameter &parameter, Point3D &point);
	/** Derive the first oder normal on the T-face. */
	virtual int normalDerive(const Parameter &parameter, Vector3D &normal);
	/** Derive both the zero and the first oder point and normal on the T-face. */
	virtual int pointAndNormalDerive(const Parameter &parameter, Point3D &point, Vector3D &normal);

	virtual ReturnMatrix firstPartialDeriveU(const Parameter &parameter);
	virtual ReturnMatrix firstPartialDeriveV(const Parameter &parameter);
	virtual ReturnMatrix secondPartialDeriveUU(const Parameter &parameter);
	virtual ReturnMatrix secondPartialDeriveUV(const Parameter &parameter);
	virtual ReturnMatrix secondPartialDeriveVV(const Parameter &parameter);
	virtual ReturnMatrix secondPartialDerive(const Parameter &parameter);//uu uv vv u v s

protected:

private:
	TFacePtr _face;
	BlendingEquationPtr _equation;
	Matrix _xtm;
	Matrix _ytm;
	Matrix _ztm;
	Matrix _1tm;
};

#ifdef use_namespace
}
#endif


#endif