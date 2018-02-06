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
	DECLARE_ASSISTANCES(DiscretedEdge, DsctEdg)

	/**
	*  @class  <DiscretedEdge>
	*  @brief  Discreted T-edge.
	*  @note
	*  DiscretedEdge requires the name of T-edge to be set, and will store the discreted result of a T-edge.
	*/
	class DiscretedEdge
	{
	public:
		DiscretedEdge(const std::string &name = "");
		~DiscretedEdge();

	public:
		/** Set the name. */
		void setName(const std::string &name) { _name = name; }
		/** Get the name. */
		std::string getName() { return _name; }

		void setDisperseParameters(const std::vector<Parameter> &parameters) { _disperse_parameters = parameters;}
		std::vector<Parameter> getDisperseParameters() { return _disperse_parameters; }

	private:
		std::string _name;
		std::vector<Parameter> _disperse_parameters;
	};


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
		/** Set the required chordal error. */
		void setResolution(Real chordal_error);

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
		Real _chordal_error;
		DsctEdgVector _discreted_edges;
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
		/** Set the required chordal error for boundary of the TFace */
		void setBoundaryRatio(Real boundary_chordal_error) { _boundary_chordal_error = boundary_chordal_error; }
		/** Set the required chordal error for inner of the TFace */
		void setInnerResolution(Real chordal_error) { _chordal_error = chordal_error; }
		/** Process the tessellation of the T-face into a TriMesh. */
		void process(const TriMeshPtr &tri_mesh, DsctEdgVector &discreted_edges);

	protected:
		void processLinkVector(const TLnkVector &links, DsctEdgVector &discreted_edges);
		std::vector<Parameter> processLink(const TLinkPtr &link);

	private:
		/** Process the tessellation of the T-face boundary into a TriMesh. */
		TriVector processBoundary(DsctEdgVector &discreted_edges);
		/** Process the tessellation of the T-face inner into a TriMesh. */
		TriVector processInner(const TriVector &triangles);

		ReturnMatrix setParameterRange();
		TriVector delaunayWatson();
		TrianglePtr getSuperTriangle();
		bool triangleInCircle(const Parameter &parameter, const TrianglePtr &triangle);
		Parameter getTriangleCircleCenter(const TrianglePtr &triangle);
		void generationTriangles(TriVector &triangles, int start_index, int end_index);
		void purifyParameters(int start_index);
		bool isTriangle(const TrianglePtr &triangle);

	private:
		TFaceDerivatorPtr _derivator;
		Real _boundary_chordal_error;
		Real _chordal_error;
		std::vector<Parameter> _parameters;
		int _size_boundary_parameters;
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
		/** Set the chordal error. */
		void setRatio(Real chordal_error) { _chordal_error = chordal_error; }
		/** Process the tessellation of a T-link into a TriMesh. */
		std::vector<Parameter> process();

	private:
		Real computeForwardSteps(const ColumnVector &form, bool u_direction);
		Real computeChordal(const ColumnVector &form, Real e, bool u_direction);

	private:
		TLinkPtr _link;
		Real _chordal_error;
		TFaceDerivatorPtr _derivator;
	};

	/** Calculate the plane function by three points. */
	inline ReturnMatrix planeFunction(const ColumnVector& p1, const ColumnVector& p2, const ColumnVector& p3)
	{
		ColumnVector plane_funciton(4);
		plane_funciton(1) = ((p2(2) - p1(2))*(p3(3) - p1(3)) - (p2(3) - p1(3))*(p3(2) - p1(2)));
		plane_funciton(2) = ((p2(3) - p1(3))*(p3(1) - p1(1)) - (p2(1) - p1(1))*(p3(3) - p1(3)));
		plane_funciton(3) = ((p2(1) - p1(1))*(p3(2) - p1(2)) - (p2(2) - p1(2))*(p3(1) - p1(1)));
		plane_funciton(4) = - (plane_funciton(1)*p1(1) + plane_funciton(2)*p1(2) + plane_funciton(3)*p1(3));
		return plane_funciton;
	}

	/** Calculate the distance between a point and a plane. */
	inline Real distancePointToPlane(const ColumnVector &point, const ColumnVector &plane_function)
	{
		return fabs(plane_function(1)*point(1) + plane_function(2)*point(2) + plane_function(3)*point(3)
			+ plane_function(4)) / sqrt(plane_function(1)*plane_function(1) + plane_function(2)*plane_function(2)
				+ plane_function(3)*plane_function(3));
	}

#ifdef use_namespace
}
#endif


#endif