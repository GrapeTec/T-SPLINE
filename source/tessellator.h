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
2016/04/02: Wenlei Xiao
- Doxygen comments added.
2016/06/05: Yazui Liu
- Tessellation OpenMP added.
-------------------------------------------------------------------------------
*/


/**  @file  [tessellator]  
*  @brief  This file contains the classes for tessellation.
  *  @author  <Wenlei Xiao>  
  *  @date  <2015.04.08>
  *  @version  <v1.0>  
  *  @note  
  *  Tessellation classes can be used to convert a T-spline surface to a trianglar mesh.   
*/

#ifndef TTESSELLATOR_H
#define TTESSELLATOR_H

#include <utils.h>
#include <tspline.h>
#include <finder.h>
#include <trimesh.h>
#include <derivator.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

DECLARE_ASSISTANCES(TTessellator, TTes)
DECLARE_ASSISTANCES(TFaceTessellator, TFacTes)
DECLARE_ASSISTANCES(TLinkTessellator, TLnkTes)
DECLARE_ASSISTANCES(TParameterTessellator, TParTes)
DECLARE_ASSISTANCES(TParameterSquareTessellator, TParSqrTes)

/**  
  *  @class  <TTessellator> 
  *  @brief  T-spline tessellation.
  *  @note  
  *  TTessellator require the target T-spline to be set, and will implement the global tessellation on it.
*/
class TTessellator
{
public:
	TTessellator(const TGroupPtr &group);
	TTessellator(const TSplinePtr &spline);

public:
	/** Set the required resolution. */
	void setResolution(Real resolution);

protected:
	void calculateResolution(const TFacePtr &face, Real ratio = 0.1);

public:
	/** Convert all T-faces into a Trimesh. */
	TriMeshPtr interpolateAll();
	/** Convert a T-face into a Trimesh. */
	TriMeshPtr interpolateFace(const TFacePtr &face);
	/** Convert a named T-face into a Trimesh. */
	TriMeshPtr interpolateFace(const std::string &face);
	/** Convert and add a T-face into a Trimesh. */
	void interpolateFace(const TFacePtr &face, TriMeshPtr &tri_mesh);

private:
	TSplinePtr _spline;
	TGroupPtr _group;
	TFinderPtr _finder;
	Real _resolution_s;
	Real _resolution_t;
};

/**  
  *  @class  <TFaceTessellator> 
  *  @brief  T-face tessellation.
  *  @note  
  *  TFaceTessellator require the target T-face to be set, and will implement the local tessellation on it.
*/
class TFaceTessellator
{
public:
	TFaceTessellator(const TFaceDerivatorPtr &derivator);
	~TFaceTessellator();

public:
	/** Set the boundary ratio for adjacent T-patches. */
	void setBoundaryRatio(Real boundary_ratio) {_boundary_ratio = boundary_ratio;}
	/** Process the tessellation of the T-face into a TriMesh. */
	void process(const TriMeshPtr &tri_mesh);
	/** Process the tessellation of the T-face boundary into a TriMesh. */
	void processBoundary(const TriMeshPtr &tri_mesh);
	/** Process the tessellation of the T-face inner into a TriMesh. */
	void processInner(const TriMeshPtr &tri_mesh);

protected:
	void processLinkLoop(const TriMeshPtr &tri_mesh);
	void processLinkLoopOffset(const TriMeshPtr &tri_mesh, Real offset);
	void processLinkVector(const TLnkVector &links, const TriMeshPtr &tri_mesh);
	void processLink(const TLinkPtr &link, const TriMeshPtr &tri_mesh);
	void processParameters(const Parameter &start, const Parameter &end, const TriMeshPtr &tri_mesh);
	void processLinkParameterPair(const TLnkVector &links, const Parameter &start, const Parameter &end, const TriMeshPtr &tri_mesh);
	void processParameterSquare(const Parameter &nwpara, const Parameter &separa, const TriMeshPtr &tri_mesh);

	Real boundaryWidthS();
	Real boundaryWidthT();
	void prepareLinksAndParameters(TLnkVector &elinks, TLnkVector &nlinks, TLnkVector &wlinks, TLnkVector &slinks,
		Parameter &nwpara, Parameter &swpara, Parameter &separa, Parameter &nepara);
private:
	TFaceDerivatorPtr _derivator;
	Real _boundary_ratio;
};

/**  
  *  @class  <TLinkTessellator> 
  *  @brief  T-face tessellation.
  *  @note  
  *  TLinkTessellator require the target T-face to be set, and will implement the local tessellation on it.
*/
class TLinkTessellator
{
public:
	TLinkTessellator(const TLinkPtr &link, const TFaceDerivatorPtr &derivator);
	~TLinkTessellator();

public:
	/** Set the ratio. */
	void setRatio(Real ratio) {_ratio = ratio;}
	/** Process the tessellation of a T-link into a TriMesh. */
	void process(const TriMeshPtr &tri_mesh);

private:
	TLinkPtr _link;
	Real _ratio;
	TFaceDerivatorPtr _derivator;
};

/**  
  *  @class  <TEditor> 
  *  @brief  The client class of validation.
  *  @note  
  *  
*/
class TParameterTessellator
{
public:
	TParameterTessellator( const TFaceDerivatorPtr &derivator, const Parameter &start, const Parameter &end);
	~TParameterTessellator();
public:
	/** Set the ratio. */
	void setRatio(Real ratio) {_ratio = ratio;}
	/** Process the tessellation of a Parameter into a TriMesh. */
	void process(const TriMeshPtr &tri_mesh);
private:
	TFaceDerivatorPtr _derivator;
	Parameter _start;
	Parameter _end;
	Real _ratio;
};

/**  
  *  @class  <TEditor> 
  *  @brief  The client class of validation.
  *  @note  
  *  
*/
class TParameterSquareTessellator
{
public:
	TParameterSquareTessellator(const TFaceDerivatorPtr &derivator, const Parameter &north_west, const Parameter &south_east);
	~TParameterSquareTessellator();
public:
	/** Set the ratio. */
	void setRatio(Real ratio) {_ratio = ratio;}
	/** Process the tessellation of a parametric square into a TriMesh. */
	void process(const TriMeshPtr &tri_mesh);
private:
	TFaceDerivatorPtr _derivator;
	Parameter _north_west;
	Parameter _south_east;
	Real _ratio;
};

#ifdef use_namespace
}
#endif


#endif