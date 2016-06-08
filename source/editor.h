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
2016/03/31: Wenlei Xiao
- Doxygen comments added.
-------------------------------------------------------------------------------
*/

/**  @file  [editor]  
*  @brief  Editor classes.
  *  @author  <Wenlei Xiao>  
  *  @date  <2016.03.31>  
  *  @version  <v1.0>  
  *  @note  
  *  The editor classes are used to edit the T-spline data structures.   
*/

#ifndef EDITOR_H
#define EDITOR_H

#include <utils.h>
#include <tspline.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif
	
/**  
  *  @class  <TEditor> 
  *  @brief  Base class of editors
  *  @note  
  *  Base class (under development).
*/
class TEditor
{
public:
	TEditor();
	virtual ~TEditor();

public:

};
DECLARE_ASSISTANCES(TEditor, TEdt)

/**  
  *  @class  <TGroupEditor> 
  *  @brief  T-group editor
  *  @note  
  *  The TGroupEditor is used to edit a T-group.
*/
class TGroupEditor
{
public:
	TGroupEditor(const TGroupPtr &group);
	virtual ~TGroupEditor();

public:
private:
	TGroupPtr _group;
};
DECLARE_ASSISTANCES(TGroupEditor, TGrpEdt)

/**  
  *  @class  <TSplineEditor> 
  *  @brief  T-spline editor
  *  @note  
  *  The TSplineEditor is used to edit a T-spline.
*/
class TSplineEditor
{
public:
	TSplineEditor(const TSplinePtr &spline);
	virtual ~TSplineEditor();
public:
	/** Move the T-point by (x, y, z). */
	void movePointBy(const TPointPtr &point, Real x, Real y, Real z);
	/** Move the named T-point by (x, y, z). */
	void movePointBy(const std::string &point_name, Real x, Real y, Real z);
	/** Move the T-point to (x, y, z). */
	void movePointTo(const TPointPtr &point, Real x, Real y, Real z);
	/** Move the named T-point to (x, y, z). */
	void movePointTo(const std::string &point_name, Real x, Real y, Real z);
	/** Set weight of a T-point. */
	void setPointWeight(const TPointPtr &point, Real weight);
	/** Set weight of a named T-point. */
	void setPointWeight(const std::string &point_name, Real weight);

public:
	/** Remove a T-point. */
	void removePoint(const TPointPtr &point);
	/** Remove a named T-point. */
	void removePoint(const std::string &point_name);
	/** Remove a T-node. */
	void removeNode(const TNodePtr &node);
	/** Remove a named T-node. */
	void removeNode(const std::string &node_name);

protected:
	TPointPtr findPoint(const std::string& point_name);
	TNodePtr findNode(const std::string& node_name);
private:
	TSplinePtr _spline;
};
DECLARE_ASSISTANCES(TSplineEditor, TSplEdt)

#ifdef use_namespace
}
#endif


#endif