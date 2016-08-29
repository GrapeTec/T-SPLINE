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
-------------------------------------------------------------------------------
*/

#ifndef __cplusplus
#error Must use C++ for the type TSpline
#endif
#ifndef UTILS_H
#define UTILS_H

/**  @file  [utils]  
  *  @brief  Utils 
  *  @author  <Wenlei Xiao>
  *  @date  <2015.04.08>  
  *  @version  <v1.0>  
  *  @note  
  *  This file provides some useful functions for global usages.
*/

#ifdef _MSC_VER                         // Microsoft
#pragma warning (disable:4786)  /* Disable decorated name truncation warnings */
#endif
#include <stdio.h>
#include <limits>
#include <string>
#include <memory>
#include <vector>
#include <list>
#include <set>
//#include <hash_map>
#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>
#define WANT_STRING                  /* include.h will get string fns */
#define WANT_STREAM                  /* include.h will get stream fns */
#define WANT_FSTREAM                 /* include.h will get fstream fns */
#define WANT_MATH                    /* include.h will get math fns */
                                     /* newmatap.h will get include.h */

#include "newmatap.h"                /* need matrix applications */

#include "newmatio.h"                /* need matrix output routines */

#ifdef use_namespace
namespace TSPLINE {
  using namespace NEWMAT;
#endif
  
#define DECLARE_CLASS(nm) \
	class nm;

#define DECLARE_SMARTPTR(nm) \
	DECLARE_CLASS(nm) \
	typedef std::shared_ptr<nm> nm##Ptr;

#define DECLARE_TAG(nm) \
  struct nm##Tag {};

#define DECLARE_ASSISTANCES(nm, ab) \
	DECLARE_SMARTPTR(nm) \
	DECLARE_TAG(nm) \
	typedef std::vector<nm##Ptr> ab##Vector; \
	typedef ab##Vector::iterator ab##VIterator; \
	typedef ab##Vector::const_iterator ab##VConstIterator; \
	typedef std::list<nm##Ptr> ab##List; \
	typedef ab##List::iterator ab##LIterator; \
	typedef ab##List::const_iterator ab##LConstIterator; \
	typedef std::set<nm##Ptr> ab##Set; \
	typedef ab##Set::iterator ab##SIterator; \
	typedef ab##Set::const_iterator ab##SConstIterator;

#ifndef M_PI
#define M_PI 3.14159265358979
#endif

#ifndef M_EPS
#define M_EPS 0.000001
#endif

typedef unsigned int Word;

/** Make a smart pointer (0 parameter). */
template<typename T>
std::shared_ptr<T> makePtr()
{
	return std::make_shared<T>();
}

/** Make a smart pointer (1 parameter). */
template<typename T, typename P1>
std::shared_ptr<T> makePtr(P1 par)
{
	return std::make_shared<T>(par);
}

/** Make a smart pointer (2 parameters). */
template<typename T, typename P1, typename P2>
std::shared_ptr<T> makePtr(P1 par1, P2 par2)
{
	return std::make_shared<T>(par1, par2);
}

/** Make a smart pointer (3 parameters). */
template<typename T, typename P1, typename P2, typename P3>
std::shared_ptr<T> makePtr(P1 par1, P2 par2, P3 par3)
{
	return std::make_shared<T>(par1, par2, par3);
}

/** Cast a smart pointer T1 to a smart pointer T2. */
template<class T1, class T2>
std::shared_ptr<T1> castPtr(const std::shared_ptr<T2> &other)
{
	return std::static_pointer_cast<T1>(other);
}

/** Cast a smart pointer T1 to a bool. */
template<class T1>
bool castBool(const std::shared_ptr<T1> &other)
{
	return static_cast<bool>(other);
}

/** Check if the value is in between the start and end float numbers. */
inline bool inBetween(Real start, Real end, Real mid)
{
	if (start < end)
	{
		if (mid >= start && mid <= end)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (mid <= start && mid >= end)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

/** Check if integer value is odd. */
inline bool isOdd(int value)
{
	return (value % 2);
}

/** Check if integer value is even. */
inline bool isEven(int value)
{
	return !isOdd(value);
}

/** Check if float value is near to zero. */
inline bool isZero(Real value)
{
	if(fabs(value) < M_EPS)
		return true;
	else
		return false;
}

#ifdef use_namespace
}
#endif

#endif

