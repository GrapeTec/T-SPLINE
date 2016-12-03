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


/**  @file  [trimesh]  
*  @brief  This file contains the classes for the triangular mesh.
  *  @author  <Wenlei Xiao>  
  *  @date  <2015.04.08>  
  *  @version  <v1.0>  
  *  @note  
  *  Provide simple triangular mesh constructing and managing functionalities.   
*/

#ifndef TRIMESH_H
#define TRIMESH_H

#include <basis.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif
	
/**  
  *  @struct  <Triangle> 
  *  @brief  Represent a triangle using three points with normals  
  *  @note  
  *  This struct holds the indices of points and normals referring to a global buffer, so as to reduce the storage.
*/
struct Triangle
{
	Word point_indices[3];
	Word normal_indices[3];
};
DECLARE_ASSISTANCES(Triangle, Tri)

/**  
  *  @struct  <TriFace> 
  *  @brief  Represent a triangular face constituted by a set of triangle meshes.
  *  @note  
  *  This struct holds the indices of points and normals referring to a global buffer, so as to reduce the storage.
*/
struct TriFace
{
	std::string name;
	Word start;
	Word end;
};
DECLARE_ASSISTANCES(TriFace, TriFac)

/**  
  *  @class  <TriEdge> 
  *  @brief  Represent a edge of a triangular face.
  *  @note  
  *  This struct holds the indices of start and end indices.
*/
struct TriEdge
{
	Word start;
	Word end;
};
DECLARE_ASSISTANCES(TriEdge, TriEdg)

/**  
  *  @class  <TriMesh> 
  *  @brief  Represent a triangular mesh.
  *  @note  
  *  TriMesh is a simple triangular mesh constructor and manager. 
  */
DECLARE_ASSISTANCES(TriMesh, TriMsh)
class TriMesh
{
public:
	TriMesh(const std::string &name = "");
	~TriMesh();

public:
	/** Set the name. */
	void setName(const std::string &name) {_name = name;}
	/** Get the name. */
	std::string getName() {return _name;}
	/** Return trimesh using newmat matrix form. */
	ReturnMatrix matrixTriMesh();

	/** Add a point (x, y, z). */
	void addPoint(Real x, Real y, Real z);
	/** Add a point of type Point3D. */
	void addPoint(const Point3D& p);
	/** Add a normal (i, j, k). */
	void addNormal(Real i, Real j, Real k);
	/** Add a normal of type Vector3D. */
	void addNormal(const Vector3D& n);
	/** Add a point of type Point3D and a normal of type Vector3D. */
	void addPointNormal(const Point3D& p, const Vector3D& n);
	/** Add a triangle of type Triangle. */
	void addTriangle(const Triangle &triangle);

	/** Start a new face (contains several triangles). */
	void faceBegin(const std::string &name = "");
	/** End a face. */
	void faceEnd();
	/** Start a new row. */
	void rowBegin();
	/** End a row. */
	void rowEnd();
	/** Start row buffers. */
	void clearRowBuffers();

	/** Start a new polygon. */
	void polygonBegin();
	/** Add a point (x, y, z) into a polygon. */
	void polygonAdd(Real x, Real y, Real z);
	/** End a polygon. */
	void polygonEnd();

	/** Merge another TriMesh. */
	void merge(const TriMeshPtr &mesh);

	/** Return the number of points. */
	long sizePoints() {return _points.size();}
	/** Return the number of normals. */
	long sizeNormals() {return _normals.size();}
	/** Return the number of triangles. */
	long sizeTriangles() {return _triangles.size();}
	/** Return the number of faces. */
	long sizeFaces() {return _faces.size();}
	/** Return the begin iterator of points. */
	P3dVIterator pointIteratorBegin() {return _points.begin();}
	/** Return the end iterator of points. */
	P3dVIterator pointIteratorEnd() {return _points.end();}
	/** Return the begin iterator of normals. */
	N3dVIterator normalIteratorBegin() {return _normals.begin();}
	/** Return the end iterator of normals. */
	N3dVIterator normalIteratorEnd() {return _normals.end();}
	/** Return the begin iterator of triangles. */
	TriVIterator triangleIteratorBegin() {return _triangles.begin();}
	/** Return the end iterator of triangles. */
	TriVIterator triangleIteratorEnd() {return _triangles.end();}
	/** Return the begin iterator of faces. */
	TriFacVIterator faceIteratorBegin() {return _faces.begin();}
	/** Return the end iterator of faces. */
	TriFacVIterator faceIteratorEnd() {return _faces.end();}
	/** Return the ith point. */
	Point3DPtr pointAt(unsigned int i) {return _points[i];}
	/** Return the ith normal. */
	Vector3DPtr normalAt(unsigned int i) {return _normals[i];}
protected:
	std::vector<long>& thisRow();
	std::vector<long>& lastRow();
	void generateTriangles(const std::vector<long> &row1, const std::vector<long> &row2);
	void generateTriangle(const TriEdgePtr &edge1, const TriEdgePtr &edge2);
private:
	std::string _name;
	P3dVector _points;
	N3dVector _normals;
	TriVector _triangles;
	TriFacVector _faces;

	std::vector<long> _odd_row_buffer;
	std::vector<long> _even_row_buffer;
	bool _row_odd_even;

	std::vector<long> _polygon_buffer;
};

#ifdef use_namespace
}
#endif

#endif