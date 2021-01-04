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
-------------------------------------------------------------------------------
*/

#include <tessellator.h>
#include <extractor.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

	DiscretedEdge::DiscretedEdge(const std::string &name /*= ""*/) :
		_name(name)
	{

	}

	DiscretedEdge::~DiscretedEdge()
	{

	}

	TTessellator::TTessellator(const TGroupPtr &group) :
		_group(group)
	{
		_finder = makePtr<TFinder>(_group);
		_spline = _finder->findTSpline();
	}

	TTessellator::TTessellator(const TSplinePtr &spline) :
		_spline(spline)
	{
		_group = _spline->getCollector();
		_finder = makePtr<TFinder>(_group);
		setResolution(0.1);
	}

	void TTessellator::setResolution(Real chordal_error)
	{
		_chordal_error = chordal_error;
	}

	void TTessellator::interpolateFace(const TFacePtr &face, TriMeshPtr &tri_mesh)
	{
		if (!face || !tri_mesh) return;
		TFaceDerivatorPtr derivator = makePtr<TFaceDerivator>(_spline, face);
		TFaceTessellator tessellator(derivator);
		tessellator.setBoundaryRatio(_chordal_error);
		tessellator.setInnerResolution(_chordal_error);
		tessellator.process(tri_mesh, _discreted_edges);
	}

	TriMeshPtr TTessellator::interpolateFace(const TFacePtr &face)
	{
		TriMeshPtr tri_mesh = makePtr<TriMesh>(face->getName());
		interpolateFace(face, tri_mesh);
		return tri_mesh;
	}

	TriMeshPtr TTessellator::interpolateFace(const std::string &face)
	{
		return interpolateFace(_finder->findByName<TFace>(face));
	}

	TriMeshPtr TTessellator::interpolateAll()
	{
#ifdef USE_OMP
		TriMshVector trimeshes;
		TFacVector faces;
		_finder->findObjects<TFace>(faces);

#pragma omp parallel for
		for (int i = 0; i<faces.size(); i++)
		{
			TFacePtr face = faces[i];
			TriMeshPtr trimesh = makePtr<TriMesh>(face->getName());

			trimesh = interpolateFace(face);
			trimeshes.push_back(trimesh);
		}

		TriMeshPtr tri_mesh = makePtr<TriMesh>(_spline->getName());
		TriMshVIterator it = trimeshes.begin();
		for (it; it != trimeshes.end(); it++)
		{
			tri_mesh->merge(*it);
		}
		return tri_mesh;
#else
		TFacVector faces;
		_finder->findObjects<TFace>(faces);
		TriMeshPtr tri_mesh = makePtr<TriMesh>(_spline->getName());
		TFacVIterator iter;
		for (iter = faces.begin(); iter != faces.end(); iter++)
		{
			TFacePtr face = *iter;
			tri_mesh->faceBegin(face->getName());
			interpolateFace(face, tri_mesh);
			tri_mesh->faceEnd();
		}
		return tri_mesh;
#endif // USE_OMP
	}

	TFaceTessellator::TFaceTessellator(const TFaceDerivatorPtr &derivator) :
		_derivator(derivator), _boundary_chordal_error(0.1), _chordal_error(0.1)
	{
	}

	TFaceTessellator::~TFaceTessellator()
	{

	}

	ReturnMatrix TFaceTessellator::setParameterRange()
	{
		ColumnVector box(4);

		TFacePtr face = _derivator->getFace();
		TVertexPtr vne = TExtractor::extractNorthEastTVertexFromTFace(face);
		TVertexPtr vsw = TExtractor::extractSouthWestTVertexFromTFace(face);
		Parameter nepara = TExtractor::extractParameterFromTVertex(vne);
		Parameter swpara = TExtractor::extractParameterFromTVertex(vsw);

		if (nepara.s() < swpara.s())
		{
			box(1) = nepara.s();
			box(2) = swpara.s();
		}
		else
		{
			box(2) = nepara.s();
			box(1) = swpara.s();
		}

		if (nepara.t() < swpara.t())
		{
			box(3) = nepara.t();
			box(4) = swpara.t();
		}
		else
		{
			box(4) = nepara.t();
			box(3) = swpara.t();
		}
		return box;
	}

	void TFaceTessellator::process(const TriMeshPtr &tri_mesh, DsctEdgVector &discreted_edges)
	{
		TriVector triangles;
		triangles = processBoundary(discreted_edges);
		_parameters.erase(_parameters.end() - 3, _parameters.end());	//delete the super triangle vertices
		triangles = processInner(triangles);

		//points and normals added to trimesh
		Point3D point; Vector3D normal;
		for (auto iter = _parameters.begin(); iter != _parameters.end(); iter++)
		{
			if (_derivator->pointAndNormalDerive(*iter, point, normal))
				tri_mesh->addPointNormal(point, normal);
		}
		//triangles added to trimesh
		for (TriVIterator iter = triangles.begin(); iter != triangles.end(); iter++)
		{
			(*iter)->normal_indices[0] = (*iter)->point_indices[0];
			(*iter)->normal_indices[1] = (*iter)->point_indices[1];
			(*iter)->normal_indices[2] = (*iter)->point_indices[2];
			tri_mesh->addTriangle(**iter);
		}
	}

	TriVector TFaceTessellator::processBoundary(DsctEdgVector &discreted_edges)
	{
		TFacePtr face = _derivator->getFace();
		TLnkVector nlinks, wlinks, slinks, elinks;

		face->findEastLinks(elinks);
		face->findNorthLinks(nlinks);
		face->findSouthLinks(wlinks);
		face->findWestLinks(slinks);

		processLinkVector(elinks, discreted_edges);
		processLinkVector(nlinks, discreted_edges);
		processLinkVector(slinks, discreted_edges);
		processLinkVector(wlinks, discreted_edges);

		purifyParameters(0);

		return delaunayWatson();
	}

	TriVector TFaceTessellator::processInner(const TriVector &triangles)
	{
		TriVector final_triangles = triangles;
		Parameter triangle_center;

		bool flag = true;	//true shows triangles should be subdivided
		while (flag)
		{
			flag = false;
			int num_parameters = _parameters.size();

			for (TriVIterator iter = final_triangles.begin(); iter != final_triangles.end(); iter++)
			{
				triangle_center.s((_parameters[(*iter)->point_indices[0]].s() + _parameters[(*iter)->point_indices[1]].s() + _parameters[(*iter)->point_indices[2]].s()) / 3);
				triangle_center.t((_parameters[(*iter)->point_indices[0]].t() + _parameters[(*iter)->point_indices[1]].t() + _parameters[(*iter)->point_indices[2]].t()) / 3);
				Point3D center_point;
				_derivator->pointDerive(triangle_center, center_point);

				Point3D point1, point2, point3;
				_derivator->pointDerive(_parameters[(*iter)->point_indices[0]], point1);
				_derivator->pointDerive(_parameters[(*iter)->point_indices[1]], point2);
				_derivator->pointDerive(_parameters[(*iter)->point_indices[2]], point3);
				ColumnVector plane_funciton = planeFunction(point1.asColumnVector(), point2.asColumnVector(), point3.asColumnVector());

				Real distance = distancePointToPlane(center_point.asColumnVector(), plane_funciton);
				if (distance > _chordal_error)
				{
					flag = true;
					_parameters.push_back(triangle_center);
				}
			}

			purifyParameters(num_parameters);
			generationTriangles(final_triangles, num_parameters, _parameters.size());
		}
		return final_triangles;
	}

	void TFaceTessellator::processLinkVector(const TLnkVector &links, DsctEdgVector &discreted_edges)
	{
		std::vector<Parameter> disperse_link_parameter;
		TLnkVConstIterator iter = links.begin();
		for (; iter != links.end(); iter++)
		{
			TEdgePtr edge = (*iter)->getTEdge();
			std::vector<DiscretedEdgePtr>::iterator it = std::find_if(discreted_edges.begin(), discreted_edges.end(),
				[edge](const DiscretedEdgePtr &discreted_edge)
			{
				return discreted_edge->getName() == edge->getName();
			});
			if (it != discreted_edges.end())	//if the edge is already dispersed 
			{
				disperse_link_parameter = (*it)->getDisperseParameters();
			}
			else
			{
				disperse_link_parameter = processLink(*iter);

				DiscretedEdgePtr discreted_edge = makePtr<DiscretedEdge>(edge->getName());
				discreted_edge->setDisperseParameters(disperse_link_parameter);
				discreted_edges.push_back(discreted_edge);
			}
			for (auto iter = disperse_link_parameter.begin(); iter != disperse_link_parameter.end(); iter++)
			{
				_parameters.push_back(*iter);
			}
		}
	}

	void TFaceTessellator::purifyParameters(int start_index)
	{
		if (_parameters.size() == 0)	return;
		for (int i = start_index; i < _parameters.size() - 1; i++)
		{
			for (int j = i + 1; j < _parameters.size(); j++)
			{
				if (isZero(sqrtf((_parameters[i].s() - _parameters[j].s())*(_parameters[i].s() - _parameters[j].s()) + (_parameters[i].t() - _parameters[j].t())*(_parameters[i].t() - _parameters[j].t()))))
				{
					_parameters.erase(_parameters.begin() + j);
				}
			}
		}
	}

	std::vector<Parameter> TFaceTessellator::processLink(const TLinkPtr &link)
	{
		TLinkTessellator tessellator(link, _derivator);
		tessellator.setRatio(_boundary_chordal_error);
		return tessellator.process();
	}

	void TFaceTessellator::generationTriangles(TriVector &triangles, int start_index, int end_index)
	{
		for (int i = start_index; i < end_index; i++)
		{
			TriEdgVector triangle_edges;
			//get the triangles whose circumcircle contains the parameter
			for (int j = 0; j < triangles.size(); j++)
			{
				bool flag = triangleInCircle(_parameters[i], triangles[j]);
				if (flag)	//delete triangle and store the edges of this triangle
				{
					TriEdgePtr tri_edge1 = makePtr<TriEdge>();
					tri_edge1->start = triangles[j]->point_indices[0];
					tri_edge1->end = triangles[j]->point_indices[1];
					triangle_edges.push_back(tri_edge1);
					TriEdgePtr tri_edge2 = makePtr<TriEdge>();
					tri_edge2->start = triangles[j]->point_indices[1];
					tri_edge2->end = triangles[j]->point_indices[2];
					triangle_edges.push_back(tri_edge2);
					TriEdgePtr tri_edge3 = makePtr<TriEdge>();
					tri_edge3->start = triangles[j]->point_indices[2];
					tri_edge3->end = triangles[j]->point_indices[0];
					triangle_edges.push_back(tri_edge3);

					triangles.erase(triangles.begin() + j);
					j--;
				}
			}

			//find all the common edges
			std::vector<int> edge_common;
			int nun_triangle_edges = triangle_edges.size();
			for (int j = 0; j < nun_triangle_edges - 1; j++)
			{
				for (int k = j + 1; k < nun_triangle_edges; k++)
				{
					if (((triangle_edges[j]->start == triangle_edges[k]->end) && (triangle_edges[j]->end == triangle_edges[k]->start))
						|| ((triangle_edges[j]->start == triangle_edges[k]->start) && (triangle_edges[j]->end == triangle_edges[k]->end)))
					{
						edge_common.push_back(j);
						edge_common.push_back(k);
					}
				}
			}
			//delete all the common edges
			std::sort(edge_common.begin(), edge_common.end(), greater<int>());
			auto pos = std::unique(edge_common.begin(), edge_common.end());
			edge_common.erase(pos, edge_common.end());
			for (auto iter = edge_common.begin(); iter != edge_common.end(); iter++)
			{
				triangle_edges.erase(triangle_edges.begin() + (*iter));
			}

			//generate triangles
			for (int j = 0; j < triangle_edges.size(); j++)
			{
				TrianglePtr triangle_t = makePtr<Triangle>();
				triangle_t->point_indices[0] = triangle_edges[j]->start;
				triangle_t->point_indices[1] = triangle_edges[j]->end;
				triangle_t->point_indices[2] = i;

				//check the legality of triangle
				if (isTriangle(triangle_t))
				{
					triangles.push_back(triangle_t);
				}
			}
		}
	}

	bool TFaceTessellator::isTriangle(const TrianglePtr &triangle)
	{
		Parameter pa1 = _parameters[triangle->point_indices[0]];
		Parameter pa2 = _parameters[triangle->point_indices[1]];
		Parameter pa3 = _parameters[triangle->point_indices[2]];

		Real a1 = pa2.t() - pa1.t();
		Real b1 = pa1.s() - pa2.s();
		Real a2 = pa3.t() - pa2.t();
		Real b2 = pa2.s() - pa3.s();

		if ((isZero(a1) && isZero(a2)) || (isZero(b1) && isZero(b2)))	// collinear in horizontal or vertical direction
		{
			return false;
		}

		Real value = a1*b2 - a2*b1;
		if (isZero(value) && (!isZero(a1*b2)))	//collinear
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	TriVector TFaceTessellator::delaunayWatson()
	{
		TriVector triangles;

		TrianglePtr super_triangle = getSuperTriangle();
		triangles.push_back(super_triangle);

		generationTriangles(triangles, 0, _size_boundary_parameters);

		//delete triangles related to super triangle
		int i = 0;
		while (i < triangles.size())
		{
			if (triangles[i]->point_indices[0] >= _size_boundary_parameters || triangles[i]->point_indices[1] >= _size_boundary_parameters || triangles[i]->point_indices[2] >= _size_boundary_parameters)
			{
				triangles.erase(triangles.begin() + i);
				i--;
			}
			i++;
		}
		return triangles;
	}

	bool TFaceTessellator::triangleInCircle(const Parameter &parameter, const TrianglePtr &triangle)
	{
		Real xp = parameter.s();
		Real yp = parameter.t();
		Real x2 = _parameters[triangle->point_indices[1]].s();
		Real y2 = _parameters[triangle->point_indices[1]].t();

		Parameter center = getTriangleCircleCenter(triangle);
		Real xc = center.s();
		Real yc = center.t();

		Real dx = x2 - xc;
		Real dy = y2 - yc;
		Real rsqr = dx * dx + dy * dy;
		dx = xp - xc;
		dy = yp - yc;
		Real drsqr = dx * dx + dy * dy;

		if ((drsqr > rsqr) || isZero(drsqr - rsqr))
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	Parameter TFaceTessellator::getTriangleCircleCenter(const TrianglePtr &triangle)
	{
		Real x1 = _parameters[triangle->point_indices[0]].s();
		Real y1 = _parameters[triangle->point_indices[0]].t();
		Real x2 = _parameters[triangle->point_indices[1]].s();
		Real y2 = _parameters[triangle->point_indices[1]].t();
		Real x3 = _parameters[triangle->point_indices[2]].s();
		Real y3 = _parameters[triangle->point_indices[2]].t();
		Real m1, m2, mx1, mx2, my1, my2, xc, yc;

		if (isZero(y1 - y2) && isZero(y2 - y3))
		{
			cout << "collinear in horizontal direction! \n" << endl;
			return NULL;
		}
		if (!isZero(x1 - x2) || !isZero(x2 - x3) || !isZero(x1 - x3))
		{
			if (isZero(y2 - y1))
			{
				m2 = -(x3 - x2) / (y3 - y2);
				mx2 = (x2 + x3) / 2;
				my2 = (y2 + y3) / 2;
				xc = (x2 + x1) / 2;
				yc = m2 * (xc - mx2) + my2;
			}
			else
			{
				if (isZero(y3 - y2))
				{
					m1 = -(x2 - x1) / (y2 - y1);
					mx1 = (x1 + x2) / 2;
					my1 = (y1 + y2) / 2;
					xc = (x3 + x2) / 2;
					yc = m1 * (xc - mx1) + my1;
				}
				else
				{
					m1 = -(x2 - x1) / (y2 - y1);
					m2 = -(x3 - x2) / (y3 - y2);
					if (isZero(m1 - m2))
					{
						cout << "collinear with angle£¡\n" << endl;
						return NULL;
					}
					else
					{
						mx1 = (x1 + x2) / 2;
						mx2 = (x2 + x3) / 2;
						my1 = (y1 + y2) / 2;
						my2 = (y2 + y3) / 2;
						xc = (m1 * mx1 - m2 * mx2 + my2 - my1) / (m1 - m2);
						yc = m1 * (xc - mx1) + my1;
					}
				}
			}
		}
		else
		{
			cout << "collinear in vertical direction£¡\n" << endl;
			return NULL;
		}
		return Parameter(xc, yc);
	}

	TrianglePtr TFaceTessellator::getSuperTriangle()
	{
		_size_boundary_parameters = _parameters.size();
		//std::sort(_paramenters.begin(), _paramenters.end(),
		//[](const Parameter &p1, const Parameter &p2) {return p1.s() < p2.s(); });

		//box(1):min_s     box(2):max_s     box(3):min_t     box(4):max_t
		ColumnVector box = setParameterRange();
		Real dmax;
		Real ds = box(2) - box(1);
		Real dt = box(4) - box(3);
		if (ds > dt)
			dmax = ds;
		else
			dmax = dt;

		Real mid_s = (box(2) + box(1)) / 2;
		Real mid_t = (box(4) + box(3)) / 2;

		//generate super triangle
		TrianglePtr super_triangle = makePtr<Triangle>();
		_parameters.push_back(Parameter((mid_s - 2 * dmax), (mid_t - dmax)));
		_parameters.push_back(Parameter((mid_s), (mid_t + 2 * dmax)));
		_parameters.push_back(Parameter((mid_s + 2 * dmax), (mid_t - dmax)));
		super_triangle->point_indices[0] = _parameters.size() - 3;
		super_triangle->point_indices[1] = _parameters.size() - 2;
		super_triangle->point_indices[2] = _parameters.size() - 1;

		return super_triangle;
	}

	TLinkTessellator::TLinkTessellator(const TLinkPtr &link, const TFaceDerivatorPtr &derivator) :
		_link(link), _derivator(derivator), _chordal_error(0.1)
	{

	}

	TLinkTessellator::~TLinkTessellator()
	{

	}

	std::vector<Parameter> TLinkTessellator::process()
	{
		std::vector<Parameter> disperse_link_parameter;

		TVertexPtr start_vertex = _link->getStartVertex();
		Parameter start_p(start_vertex->getS(), start_vertex->getT());
		TVertexPtr end_vertex = _link->getEndVertex();
		Parameter end_p(end_vertex->getS(), end_vertex->getT());

		if ((end_p.s() < start_p.s()) || (end_p.t() < start_p.t()))
		{
			Parameter p_t = start_p;
			start_p = end_p;
			end_p = p_t;
		}
		disperse_link_parameter.push_back(start_p);

		bool u_direction = true;
		if (isZero(end_p.s() - start_p.s()))
			u_direction = false;

		Parameter p = start_p;
		if (u_direction)
		{
			//limit the step length
			Real length_edge = end_p.s() - start_p.s();
			Real limit_forward_step = length_edge / 5;

			while (p.s() < end_p.s())
			{
				ColumnVector form = _derivator->firstAndSecondFundamentalForm(p);
				Real forward_step = computeForwardSteps(form, u_direction);

				forward_step = min(forward_step, limit_forward_step);

				p.s(p.s() + forward_step);
				if (p.s() < end_p.s())
					disperse_link_parameter.push_back(p);
			}
		}
		else
		{
			Real length_edge = end_p.t() - start_p.t();
			Real limit_forward_step = length_edge / 5;
			while (p.t() < end_p.t())
			{
				ColumnVector form = _derivator->firstAndSecondFundamentalForm(p);
				Real forward_step = computeForwardSteps(form, u_direction);
				forward_step = min(forward_step, limit_forward_step);

				p.t(p.t() + forward_step);
				if (p.t()<end_p.t())
					disperse_link_parameter.push_back(p);
			}
		}
		disperse_link_parameter.push_back(end_p);

		return disperse_link_parameter;
	}

	Real TLinkTessellator::computeForwardSteps(const ColumnVector &form, bool u_direction)
	{
		return computeChordal(form, _chordal_error, u_direction);
	}

	Real TLinkTessellator::computeChordal(const ColumnVector &form, Real e, bool u_direction)
	{
		Real E = form(1), F = form(2), G = form(3), L = form(4), M = form(5), N = form(6);
		Real d = 0.1;
		if (u_direction)
		{
			if (isZero(L))
			{
				return d;
			}
			else
			{
				d = sqrt(fabs(8.0*e / L - 4.0*e*e / E));
			}
		}
		else
		{
			if (isZero(N))
			{
				return d;
			}
			else
			{
				d = sqrt(fabs(8.0*e / N - 4.0*e*e / G));
			}
		}
		return d;
	}

#ifdef use_namespace
}
#endif