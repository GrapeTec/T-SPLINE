/*
TSPLINE -- A T-spline object oriented package in C++
Copyright (C) 2015-  Wenlei Xiao

This library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation; either version 3.0 of the
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
2016/06/06: Yazui Liu
- Add TriMesh::merge() function.
-------------------------------------------------------------------------------
*/

#include <trimesh.h>
#include <sstream>
#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

std::string convertToString(Real val)
{
	ostringstream os;
	if (os << val)
		return os.str();
	return "";
}

TriMesh::TriMesh(const std::string &name /*= ""*/) :
	_name(name)
{
	clearRowBuffers();
}

TriMesh::~TriMesh()
{

}

void TriMesh::addPoint( Real x, Real y, Real z )
{
	Point3DPtr point = makePtr<Point3D>(x, y, z);
	_points.push_back(point);
	std::vector<long>& this_row = thisRow();
	this_row.push_back(sizePoints()-1);
}

void TriMesh::addPoint( const Point3D& p )
{
	_points.push_back(makePtr<Point3D>(p));
	std::vector<long>& this_row = thisRow();
 	this_row.push_back(sizePoints()-1);
}

void TriMesh::addNormal( Real i, Real j, Real k )
{
	Vector3DPtr normal = makePtr<Vector3D>(i, j, k);
	_normals.push_back(normal);
}

void TriMesh::addNormal( const Vector3D& n )
{
	_normals.push_back(makePtr<Vector3D>(n));
}

void TriMesh::addPointNormal( const Point3D& p, const Vector3D& n )
{
	addPoint(p); addNormal(n);
}

void TriMesh::addTriangle( const Triangle &triangle )
{
	_triangles.push_back(makePtr<Triangle>(triangle));
}

void TriMesh::faceBegin(const std::string &name /*= ""*/)
{
	_faces.push_back(makePtr<TriFace>());
	TriFacVIterator iter = faceIteratorEnd();	iter--;
	TriFacePtr face = *iter;
	face->name = name;
	face->start = _triangles.size();
	clearRowBuffers();
}

void TriMesh::faceEnd()
{
	TriFacVIterator iter = faceIteratorEnd();	iter--;
	TriFacePtr face = *iter;
	face->end = sizeTriangles() - 1;
	if (face->start > face->end)
	{
		_faces.pop_back();
	}
	clearRowBuffers();
}

void TriMesh::rowBegin()
{
	_row_odd_even = !_row_odd_even;
	thisRow().clear();
}

void TriMesh::rowEnd()
{
	generateTriangles(lastRow(), thisRow());
}

void TriMesh::clearRowBuffers()
{
	_odd_row_buffer.clear();
	_even_row_buffer.clear();
	_row_odd_even = false;
}

std::vector<long>& TriMesh::thisRow()
{
	if (_row_odd_even)
	{
		return _odd_row_buffer;
	}
	else
	{
		return _even_row_buffer;
	}
}

std::vector<long>& TriMesh::lastRow()
{
	if (_row_odd_even)
	{
		return _even_row_buffer;
	}
	else
	{
		return _odd_row_buffer;
	}
}

void TriMesh::polygonBegin()
{
	_polygon_buffer.clear();
}

void TriMesh::polygonAdd( Real x, Real y, Real z )
{
	_points.push_back(makePtr<Point3D>(x, y, z));
	_polygon_buffer.push_back(sizePoints()-1);
	long buf_size = _polygon_buffer.size();
	if (buf_size >= 3)
	{
		Triangle triangle;
		triangle.point_indices[0] = _polygon_buffer[0];
		triangle.point_indices[1] = _polygon_buffer[buf_size-2];
		triangle.point_indices[2] = _polygon_buffer[buf_size-1];
		addTriangle(triangle);
	}
}

void TriMesh::polygonEnd()
{
	if (_polygon_buffer.size() < 3)
	{
		for (int i=0;i<_polygon_buffer.size();i++)
		{
			P3dVIterator iter = pointIteratorBegin() + _polygon_buffer[i];
			_points.erase(iter);
		}
	}
	_polygon_buffer.clear();
}

void TriMesh::merge(const TriMeshPtr &mesh)
{
	this->faceBegin(mesh->getName());
	int offset = _points.size();

	P3dVIterator pit = mesh->pointIteratorBegin();
	N3dVIterator nit = mesh->normalIteratorBegin();
	for (pit;pit!=mesh->pointIteratorEnd();pit++,nit++)
	{
		this->addPointNormal(*(*pit).get(), *(*nit).get());
	}

	TriVIterator tit = mesh->triangleIteratorBegin();
	for (tit;tit!=mesh->triangleIteratorEnd();tit++)
	{
		Triangle tri;
		tri.point_indices[0] = (*tit)->point_indices[0] + offset;
		tri.point_indices[1] = (*tit)->point_indices[1] + offset;
		tri.point_indices[2] = (*tit)->point_indices[2] + offset;
		tri.normal_indices[0] = (*tit)->normal_indices[0] + offset;
		tri.normal_indices[1] = (*tit)->normal_indices[1] + offset;
		tri.normal_indices[2] = (*tit)->normal_indices[2] + offset;
		this->addTriangle(tri);
	}
	this->faceEnd();
}

void TriMesh::generateTriangles( const std::vector<long> &row1, const std::vector<long> &row2 )
{
	long length1 = row1.size();
	long length2 = row2.size();
	if (length1 == 0 || length2 == 0)
	{
		return;
	}

	TriEdgVector edges;
	if (length1 > length2)
	{
		double average = (double)length1/(double)length2;
		double step = 0.0; long j = 0;
		for (long i=0;i<length2;i++)
		{
			step += average;
			while (step >= 1.0)
			{
				TriEdgePtr edge = makePtr<TriEdge>(); 
				edge->start = row1[j]; edge->end = row2[i];
				edges.push_back(edge);
				j++; step -= 1.0;
			}
		}
	}
	else if (length1 < length2)
	{
		double average = (double)length2/(double)length1;
		double step = 0.0; long j = 0;
		for (long i=0;i<length1;i++)
		{
			step += average;
			while (step >= 1.0)
			{
				TriEdgePtr edge = makePtr<TriEdge>();
				edge->start = row1[i]; edge->end = row2[j];
				edges.push_back(edge);
				j++; step -= 1.0;
			}
		}
	}
	else
	{
		for (long i=0;i<length1;i++)
		{
			TriEdgePtr edge = makePtr<TriEdge>();
			edge->start = row1[i]; edge->end = row2[i];
			edges.push_back(edge);
		}
	}

	TriEdgVIterator iter = edges.begin();
	for (iter++;iter!=edges.end();iter++)
	{
		TriEdgePtr edge1 = *(iter-1);
		TriEdgePtr edge2 = *(iter);
		generateTriangle(edge1, edge2);
	}
}

void TriMesh::generateTriangle( const TriEdgePtr &edge1, const TriEdgePtr &edge2 )
{
	if (edge1->start == edge2->start && edge1->end != edge2->end)
	{
		Triangle triangle;
		triangle.point_indices[0] = triangle.normal_indices[0] = edge1->start;
		triangle.point_indices[1] = triangle.normal_indices[1] = edge1->end;
		triangle.point_indices[2] = triangle.normal_indices[2] = edge2->end;
		addTriangle(triangle);
	}
	else if (edge1->start != edge2->start && edge1->end == edge2->end)
	{
		Triangle triangle;
		triangle.point_indices[0] = triangle.normal_indices[0] = edge1->start;
		triangle.point_indices[1] = triangle.normal_indices[1] = edge1->end;
		triangle.point_indices[2] = triangle.normal_indices[2] = edge2->start;
		addTriangle(triangle);
	}
	else if (edge1->start != edge2->start && edge1->end != edge2->end)
	{
		Triangle triangle1;
		triangle1.point_indices[0] = triangle1.normal_indices[0] = edge1->start;
		triangle1.point_indices[1] = triangle1.normal_indices[1] = edge1->end;
		triangle1.point_indices[2] = triangle1.normal_indices[2] = edge2->end;
		addTriangle(triangle1);
		Triangle triangle2;
		triangle2.point_indices[0] = triangle2.normal_indices[0] = edge1->start;
		triangle2.point_indices[1] = triangle2.normal_indices[1] = edge2->end;
		triangle2.point_indices[2] = triangle2.normal_indices[2] = edge2->start;
		addTriangle(triangle2);
	}
}

#ifdef use_namespace
}
#endif