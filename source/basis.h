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
2016/03/29: Wenlei Xiao
	- Doxygen comments added.
-------------------------------------------------------------------------------
*/

/**  @file  [basis]  
  *  @brief  Basic classes 
  *  @author  <Wenlei Xiao>  
  *  @date  <2016.03.29>  
  *  @version  <v1.0>  
  *  @note  
  *  This file contains several assistant classes for basic computations related to parameters, points, vertices and parametric squares.
*/ 


#ifndef BASIS_H
#define BASIS_H

#include <utils.h>

#ifdef use_namespace
namespace TSPLINE {
  using namespace NEWMAT;
#endif

DECLARE_ASSISTANCES(Parameter, Par);
DECLARE_ASSISTANCES(Point3D, P3d);
DECLARE_ASSISTANCES(Vector3D, N3d);
DECLARE_ASSISTANCES(Frame3D, F3d);
DECLARE_ASSISTANCES(ParameterSquare, ParaSqu);

/**  
  *  @class  <Parameter> 
  *  @brief  The parametric coordinate.
  *  @note  
  *  A Parameter is a 2D coordinate (s, t), it supports the similar operations like a built-in type. 
*/
class Parameter
{
public:
	Parameter(Real s = 0.0, Real t = 0.0) : _s(s), _t(t) {}
	~Parameter() {}

	/** Get the parameter s */
	Real s() const {return _s;}

	/** Set the parameter s */
	Real s(Real v) { _s = v; return _s;}

	/** Get the parameter t */
	Real t() const {return _t;}

	/** Set the parameter t */
	Real t(Real v) { _t = v; return _t;}
public:
	/** operator = */
	Parameter& operator=(const Parameter &p) { _s = p.s(); _t = p.t(); return *this;}
	/** operator += */
	Parameter& operator+=(const Parameter& p) {	_s += p.s(); _t += p.t(); return *this;}
	/** operator -= */
	Parameter& operator-=(const Parameter& p) { _s -= p.s(); _t -= p.t(); return *this;}
	/** operator *= */
	Parameter& operator*=(const Real f) { _s *= f; _t *= f; return *this;}
	/** operator /= */
	Parameter& operator/=(const Real f) { _s /= f; _t /= f; return *this;}
	/** operator + */
	Parameter operator+(const Parameter& p) {	Parameter tmp(*this); tmp += p;	return tmp; }
	/** operator - */
	Parameter operator-(const Parameter& p) {	Parameter tmp(*this); tmp -= p;	return tmp; }
	/** operator * */
	Parameter operator*(const Real f) { Parameter tmp(*this); tmp *= f; return tmp;}
	/** operator / */
	Parameter operator/(const Real f) { Parameter tmp(*this); tmp /= f; return tmp; }
public:
	/** Get the norm of parameter */
	Real norm() {return sqrt(_s*_s + _t*_t);}
	/** Normalize the parameter */
	Parameter& normalize() { Real n = norm(); _s /= n; _t /= n; return *this;}
private:
	Real _s, _t;
};

/**  
  *  @class  <Point3D> 
  *  @brief  The 3D Cartesian point.
  *  @note  
  *  A Point3D is a 3D coordinate (x, y, z), it supports the similar operations like a built-in type. 
*/
class Point3D
{
public:
	Point3D(Real x = 0.0, Real y = 0.0, Real z = 0.0) {_coordinates[0] = x; _coordinates[1] = y, _coordinates[2] = z;}
	~Point3D() {}

	/** x coordinate */
	Real x() const {return _coordinates[0];}
	Real x(Real v) {_coordinates[0] = v; return v;}
	/** y coordinate */
	Real y() const {return _coordinates[1];}
	Real y(Real v) {_coordinates[1] = v; return v;}
	/** z coordinate */
	Real z() const {return _coordinates[2];}
	Real z(Real v) {_coordinates[2] = v; return v;}

	ReturnMatrix asColumnVector() 
	{
		ColumnVector v(3);
		v << x() << y() << z();
		v.Release(); return v;
	}
public:
	/** operator = */
	Point3D& operator=(const Point3D &p) { x(p.x()); y(p.y()); z(p.z()); return *this;}
	/** operator += */
	Point3D& operator+=(const Point3D& p) {	x(x()+p.x()); y(y()+p.y()); z(z()+p.z()); return *this;}
	/** operator -= */
	Point3D& operator-=(const Point3D& p) {	x(x()-p.x()); y(y()-p.y()); z(z()-p.z()); return *this;}
	/** operator *= */
	Point3D& operator*=(const Real f) { x(x()*f); y(y()*f); z(z()*f); return *this; }
	/** operator /= */
	Point3D& operator/=(const Real f) { x(x()/f); y(y()/f); z(z()/f); return *this; }
	/** operator + */
	Point3D operator+(const Point3D& p) const {	Point3D tmp(*this); tmp += p; return tmp; }
	/** operator - */
	Point3D operator-(const Point3D& p) const {	Point3D tmp(*this); tmp -= p; return tmp; }
	/** operator * */
	Point3D operator*(const Real f) const { Point3D tmp(*this); tmp *= f; return tmp;}
	/** operator / */
	Point3D operator/(const Real f) const { Point3D tmp(*this); tmp /= f; return tmp; }
public:
	/** Clear the point to (0,0,0) */
	void clear() {x(0.0); y(0.0); z(0.0);}
	/** Calculate the norm */
	Real norm2() {return sqrt(x()*x()+y()*y()+z()*z());}
private:
	Real _coordinates[3];
};

/**  
  *  @class  <Vector3D> 
  *  @brief  The 3D Cartesian vector.
  *  @note  
  *  A Vector3D is a 3D vector (i, j, k), it supports the similar operations like a built-in type.   
*/ 
class Vector3D
{
public:
	Vector3D(Real i = 0.0, Real j = 0.0, Real k = 1.0) : _point(i, j, k) {}
	Vector3D(const Point3D &point) : _point(point) {}
	~Vector3D() {}
	/** i of vector */
	Real i() const {return _point.x();}
	Real i(Real v) {return _point.x(v);}
	/** j of vector */
	Real j() const {return _point.y();}
	Real j(Real v) {return _point.y(v);}
	/** k of vector */
	Real k() const {return _point.z();}
	Real k(Real v) {return _point.z(v);}

	ReturnMatrix asColumnVector() { return _point.asColumnVector(); }
public:
	/** operator = */
	Vector3D& operator=(const Vector3D &n) {_point = n._point; return *this;}
	/** operator = */
	Vector3D& operator=(const Point3D &p) {_point = p; return *this;}
	/** operator += */
	Vector3D& operator+=(const Vector3D &n) {_point += n._point; return *this;}
	/** operator -= */
	Vector3D& operator-=(const Vector3D& n) {_point -= n._point; return *this;}
	/** operator *= */
	Vector3D& operator*=(const Real f) {_point *= f; return *this;}
	/** operator /= */
	Vector3D& operator/=(const Real f) {_point /= f; return *this;}
	/** operator + */
	Vector3D operator+(const Vector3D& n) {Vector3D tmp(*this); tmp += n; return tmp;}
	/** operator - */
	Vector3D operator-(const Vector3D& n) {Vector3D tmp(*this); tmp -= n; return tmp;}
	/** operator *, dot product */
	Vector3D operator*(const Real f) { Vector3D tmp(*this); tmp *= f; return tmp; }
	/** operator / */
	Vector3D operator/(const Real f) { Vector3D tmp(*this); tmp /= f; return tmp; }
	/** operator *, cross product */
	Vector3D operator*(const Vector3D& n) 
	{
		Real ii = j()*n.k() - k()*n.j();
		Real jj = k()*n.i() - i()*n.k();
		Real kk = i()*n.j() - j()*n.i();
		return Vector3D(ii, jj, kk);
	}

public:
	/** Clear the vector to (0.0, 0.0, 0.0) */
	void clear() {_point.x(0.0); _point.y(0.0); _point.z(1.0);}
	/** Calculate the norm of the vector */
	Real norm() {return _point.norm2();}
	/** Normalize the vector */
	Vector3D& normalize() { _point /= norm(); return *this;}
private:
	Point3D _point;
};

class Frame3D
{
public:
	Frame3D(const Point3D &origin, const Vector3D &axis_x, const Vector3D &axis_z);
	~Frame3D();
public:
	Point3D o() { return _origin; }
	Vector3D x() { return _axis_x; }
	Vector3D y() 
	{
		ColumnVector vx = _axis_x.asColumnVector();
		ColumnVector vz = _axis_z.asColumnVector();
		ColumnVector vy = CrossProduct(vz, vx);
		return Vector3D(vy(1), vy(2), vy(3));
	}
	Vector3D z() { return _axis_z; }
private:
	Point3D _origin;
	Vector3D _axis_x;
	Vector3D _axis_z;
};

/**  
  *  @class  <ParameterSquare> 
  *  @brief  A square in the parametric domain.   
  *  @note  
  *  A ParameterSquare is represented using two parametric points on the northwest and southeast corners.
*/ 
class ParameterSquare
{
public:
	ParameterSquare(const Parameter &parameter);
	ParameterSquare(Real s, Real t);
	ParameterSquare(const Parameter &northwest, const Parameter &southeast);
	~ParameterSquare();
public:
	/** Put a seed point into the parameter square */
	void seedParameter(const Parameter &parameter);
	/** Put two corners into the parameter square as seeds */
	void seedParameter(const Parameter &northwest, const Parameter &southeast);
	/** Extend the parameter square if the parameter is outside*/
	void extendParameter(const Parameter &parameter);

	/** Get and set the minimum s limit of the parameter */
	Real sMin() {return _northwest.s();}
	Real sMin(Real v) {return _northwest.s(v);}
	/** Get and set the maximum s limit of the parameter */
	Real sMax() {return _southeast.s();}
	Real sMax(Real v) {return _southeast.s(v);}
	/** Get and set the minimum t limit of the parameter */
	Real tMin() {return _southeast.t();}
	Real tMin(Real v) {return _southeast.t(v);}
	/** Get and set the maximum t limit of the parameter */
	Real tMax() {return _northwest.t();}
	Real tMax(Real v) {return _northwest.t(v);}
	/** Derive the width of the parameter square */
	Real width() {return sMax() - sMin();}
	/** Derive the height of the parameter square */
	Real height() {return tMax() - tMin();}

private:
	/** Parameter on the northwest corner */
	Parameter _northwest;
	/** parameter on the southeast corner */
	Parameter _southeast;
};

/** Safely divide a Real by a Real */
inline Real safeDivide( Real nominator, Real denominator )
{
	if (fabs(denominator) < M_EPS)
	{
		return 0.0;
	}
	else
	{
		return nominator / denominator;
	}
}

/** Safely divide a Real by a Point3D */
inline Point3D safeDivide( const Point3D &nominator, Real denominator )
{
	if (fabs(denominator) < M_EPS)
	{
		return nominator;
	}
	else
	{
		return nominator / denominator;
	}
}

#ifdef use_namespace
}
#endif

#endif

