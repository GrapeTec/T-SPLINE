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
	/** Derive the normal curvature of the point on the T-spline surface. */
	Real normalCurvature(const Parameter &parameter, Real ds, Real dt);
	/** Derive the principal curvature of the point on the T-spline surface. */
	void principalCurvature(const Parameter &parameter, Real &k1, Real &k2);
	/** Calculate the U first partial derivative of the point on the T-spline surface. */
	virtual ReturnMatrix firstPartialDeriveU(const Parameter &parameter);
	/** Calculate the V first partial derivative of the point on the T-spline surface. */
	virtual ReturnMatrix firstPartialDeriveV(const Parameter &parameter);
	/** Calculate the U second partial derivative of the point on the T-spline surface. */
	virtual ReturnMatrix secondPartialDeriveUU(const Parameter &parameter);
	/** Calculate the second mixed partial derivative of the point on the T-spline surface. */
	virtual ReturnMatrix secondPartialDeriveUV(const Parameter &parameter);
	/** Calculate the V second partial derivative of the point on the T-spline surface. */
	virtual ReturnMatrix secondPartialDeriveVV(const Parameter &parameter);
	/** Calculate the first and second partial derivatives of the point on the T-spline surface and store them using a 3*6 matrix with column major order
	1th column:	 U second partial derivative;
	2th column:	 second mixed partial derivative;
	3th column:	 V second partial derivative;
	4th column:	 U first partial derivative;
	5th column:	 V first partial derivative;
	6th column:	 point on the T-spline surface.
	*/
	virtual ReturnMatrix secondPartialDerive(const Parameter &parameter);//uu uv vv u v s
	/** Calculate the first and second fundamental form coefficients and store them using a column vector
	E F G L M N
	*/
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
	/** Calculate the U first partial derivative of the point on the T-spline surface. */
	virtual ReturnMatrix firstPartialDeriveU(const Parameter &parameter);
	/** Calculate the V first partial derivative of the point on the T-spline surface. */
	virtual ReturnMatrix firstPartialDeriveV(const Parameter &parameter);
	/** Calculate the U second partial derivative of the point on the T-spline surface. */
	virtual ReturnMatrix secondPartialDeriveUU(const Parameter &parameter);
	/** Calculate the second mixed partial derivative of the point on the T-spline surface. */
	virtual ReturnMatrix secondPartialDeriveUV(const Parameter &parameter);
	/** Calculate the V second partial derivative of the point on the T-spline surface. */
	virtual ReturnMatrix secondPartialDeriveVV(const Parameter &parameter);
	/** Calculate the first and second partial derivatives of the point on the T-spline surface and store them using a 3*6 matrix with column major order
	1th column:	 U second partial derivative;
	2th column:	 second mixed partial derivative;
	3th column:	 V second partial derivative;
	4th column:	 U first partial derivative;
	5th column:	 V first partial derivative;
	6th column:	 point on the T-spline surface.
	*/
	virtual ReturnMatrix secondPartialDerive(const Parameter &parameter);

protected:

private:
	TFacePtr _face;
	BlendingEquationPtr _equation;
};

#ifdef use_namespace
}
#endif


#endif