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

2016/10/17: Wenlei Xiao
	- Created.
-------------------------------------------------------------------------------
*/

#ifndef BASIS2_H
#define BASIS2_H

#include <basis.h>

#ifdef use_namespace
namespace TSPLINE {
  using namespace NEWMAT;
#endif

class Parameter2 : public Parameter
{
public:
	Parameter2(Real r = 0.0, Real s = 0.0, Real t = 0.0) : _r(r), Parameter(s, t) {}
	virtual ~Parameter2() {}

	/** Get the parameter r */
	Real r() const {return _r;}

	/** Set the parameter r */
	Real r(Real v) { _r = v; return _r;}
public:
	/** operator = */
	Parameter2& operator=(const Parameter2 &p) { r(p.r()); s(p.s()); t(p.t()); return *this;}
	/** operator += */
	Parameter2& operator+=(const Parameter2& p) { r(r()+p.r()); s(s()+p.s()); t(t()+p.t()); return *this;}
	/** operator -= */
	Parameter2& operator-=(const Parameter2& p) { r(r()-p.r()); s(s()-p.s()); t(t()-p.t()); return *this;}
	/** operator *= */
	Parameter2& operator*=(const Real f) { r(r()*f); s(s()*f); t(t()*f); return *this;}
	/** operator /= */
	Parameter2& operator/=(const Real f) { r(r()/f); s(s()/f); t(t()/f); return *this;}
	/** operator + */
	Parameter2 operator+(const Parameter2& p) {	Parameter2 tmp(*this); tmp += p; return tmp; }
	/** operator - */
	Parameter2 operator-(const Parameter2& p) {	Parameter2 tmp(*this); tmp -= p; return tmp; }
	/** operator * */
	Parameter2 operator*(const Real f) { Parameter2 tmp(*this); tmp *= f; return tmp;}
	/** operator / */
	Parameter2 operator/(const Real f) { Parameter2 tmp(*this); tmp /= f; return tmp; }
public:
	/** Get the norm of parameter */
	virtual Real norm() {return sqrt(r()*r() + s()*s() + t()*t());}
	/** Normalize the parameter */
	virtual Parameter2& normalize() { Real n = norm(); *this /= n; return *this;}
private:
	Real _r;
};

#ifdef use_namespace
}
#endif

#endif

