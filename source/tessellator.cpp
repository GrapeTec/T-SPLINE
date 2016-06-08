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
2016/06/05: Yazui Liu
   - Tessellation OpenMP added.
-------------------------------------------------------------------------------
*/

#include <tessellator.h>
#include <extractor.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

TTessellator::TTessellator( const TGroupPtr &group ):
	_group(group)
{
	_finder = makePtr<TFinder>(_group);
	_spline = _finder->findTSpline();
}

TTessellator::TTessellator( const TSplinePtr &spline ):
	_spline(spline)
{
	_group = _spline->getCollector();
	_finder = makePtr<TFinder>(_group);
	setResolution(0.01);
}

void TTessellator::setResolution( Real resolution )
{
	_resolution_s = resolution;
	_resolution_t = resolution;
}

void TTessellator::interpolateFace(const TFacePtr &face, TriMeshPtr &tri_mesh)
{
	if (!face || !tri_mesh) return;
	calculateResolution(face);
	TFaceDerivatorPtr derivator = makePtr<TFaceDerivator>(_spline, face);
	TFaceTessellator tessellator(derivator);
	tessellator.process(tri_mesh);
}

TriMeshPtr TTessellator::interpolateFace( const TFacePtr &face )
{
	TriMeshPtr tri_mesh = makePtr<TriMesh>(face->getName());
	interpolateFace(face, tri_mesh);
	return tri_mesh;
}

TriMeshPtr TTessellator::interpolateFace( const std::string &face )
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
	for (int i = 0;i<faces.size();i++)
	{
		TFacePtr face = faces[i];
		TriMeshPtr trimesh = makePtr<TriMesh>(face->getName());

		trimesh = interpolateFace(face);
		trimeshes.push_back(trimesh);
	}

	TriMeshPtr tri_mesh = makePtr<TriMesh>(_spline->getName());
	TriMshVIterator it = trimeshes.begin();
	for (it;it!=trimeshes.end();it++)
	{
		tri_mesh->merge(*it);
	}
	return tri_mesh;
#else
	TFacVector faces;
	_finder->findObjects<TFace>(faces);
	TriMeshPtr tri_mesh = makePtr<TriMesh>(_spline->getName());
	TFacVIterator iter;
	for (iter=faces.begin();iter!=faces.end();iter++)
	{
		TFacePtr face = *iter;
		tri_mesh->faceBegin(face->getName());
		interpolateFace(face, tri_mesh);
		tri_mesh->faceEnd();
	}
	return tri_mesh;
#endif // USE_OMP

}

void TTessellator::calculateResolution( const TFacePtr &face, Real ratio /*= 0.1*/ )
{
	Real width = face->width();
	Real height = face->height();
	_resolution_s = width * ratio;
	_resolution_t = height * ratio;
}

TFaceTessellator::TFaceTessellator( const TFaceDerivatorPtr &derivator ) :
	_derivator(derivator), _boundary_ratio(0.002)
{
}

TFaceTessellator::~TFaceTessellator()
{

}

void TFaceTessellator::process(const TriMeshPtr &tri_mesh)
{
	processBoundary(tri_mesh);
	processInner(tri_mesh);
}

void TFaceTessellator::processBoundary(const TriMeshPtr &tri_mesh)
{
	TLnkVector nlinks, wlinks, slinks, elinks;
	Parameter pne, psw, pnw, pse;
	prepareLinksAndParameters(elinks, nlinks, wlinks, slinks, pnw, psw, pse, pne);

	processLinkParameterPair(elinks, psw, pse, tri_mesh);
	processLinkParameterPair(nlinks, pse, pne, tri_mesh);
	processLinkParameterPair(wlinks, pne, pnw, tri_mesh);
	processLinkParameterPair(slinks, pnw, psw, tri_mesh);
}

void TFaceTessellator::processInner( const TriMeshPtr &tri_mesh )
{
	TLnkVector nlinks, wlinks, slinks, elinks;
	Parameter pne, psw, pnw, pse;
	prepareLinksAndParameters(elinks, nlinks, wlinks, slinks, pnw, psw, pse, pne);
	
	TParameterSquareTessellator tessellator(_derivator, pnw, pse);
	tessellator.process(tri_mesh);
}

void TFaceTessellator::processLinkLoop( const TriMeshPtr &tri_mesh )
{
	TFacePtr face = _derivator->getFace();
	TLnkVector nlinks, wlinks, slinks, elinks;
	face->findNorthLinks(nlinks);
	face->findWestLinks(wlinks);
	face->findSouthLinks(slinks);
	face->findEastLinks(elinks);

	processLinkVector(elinks, tri_mesh);
	processLinkVector(nlinks, tri_mesh);
	processLinkVector(wlinks, tri_mesh);
	processLinkVector(slinks, tri_mesh);
}

void TFaceTessellator::processLinkVector( const TLnkVector &links, const TriMeshPtr &tri_mesh )
{
	TLnkVConstIterator iter;
	for (iter=links.cbegin();iter!=links.cend();iter++)
	{
		processLink(*iter, tri_mesh);
	}
}

void TFaceTessellator::processLink( const TLinkPtr &link, const TriMeshPtr &tri_mesh )
{
	TLinkTessellator tessellator(link, _derivator);
	tessellator.process(tri_mesh);
}

void TFaceTessellator::processLinkLoopOffset( const TriMeshPtr &tri_mesh, Real offset )
{
	TFacePtr face = _derivator->getFace();
	TVertexPtr vne = TExtractor::extractNorthEastTVertexFromTFace(face);
	TVertexPtr vsw = TExtractor::extractSouthWestTVertexFromTFace(face);
	Parameter pne = TExtractor::extractParameterFromTVertex(vne);
	Parameter psw = TExtractor::extractParameterFromTVertex(vsw);

	pne -= Parameter(offset, offset);
	psw += Parameter(offset, offset);

	Parameter pnw(psw.s(), pne.t());
	Parameter pse(pne.s(), psw.t());

	processParameters(psw, pse, tri_mesh);
	processParameters(pse, pne, tri_mesh);
	processParameters(pne, pnw, tri_mesh);
	processParameters(pnw, psw, tri_mesh);
}

void TFaceTessellator::processParameters( const Parameter &start, const Parameter &end, const TriMeshPtr &tri_mesh )
{
	TParameterTessellator tessellator(_derivator, start, end);
	tessellator.process(tri_mesh);
}

void TFaceTessellator::processLinkParameterPair( const TLnkVector &links, const Parameter &start, 
												const Parameter &end, const TriMeshPtr &tri_mesh )
{
	tri_mesh->clearRowBuffers();
	tri_mesh->rowBegin();
	processLinkVector(links, tri_mesh);
	tri_mesh->rowEnd();
	tri_mesh->rowBegin();
	processParameters(start, end, tri_mesh);
	tri_mesh->rowEnd();
}

Real TFaceTessellator::boundaryWidthS()
{
	TFacePtr face = _derivator->getFace();
	return _boundary_ratio * face->width();
}

Real TFaceTessellator::boundaryWidthT()
{
	TFacePtr face = _derivator->getFace();
	return _boundary_ratio * face->height();
}

void TFaceTessellator::prepareLinksAndParameters( TLnkVector &elinks, TLnkVector &nlinks, TLnkVector &wlinks, TLnkVector &slinks,
												 Parameter &nwpara, Parameter &swpara, Parameter &separa, Parameter &nepara )
{
	TFacePtr face = _derivator->getFace();
	Real offs = boundaryWidthS();
	Real offt = boundaryWidthT();

	face->findNorthLinks(nlinks);
	face->findWestLinks(wlinks);
	face->findSouthLinks(slinks);
	face->findEastLinks(elinks);

	TVertexPtr vne = TExtractor::extractNorthEastTVertexFromTFace(face);
	TVertexPtr vsw = TExtractor::extractSouthWestTVertexFromTFace(face);
	nepara = TExtractor::extractParameterFromTVertex(vne);
	swpara = TExtractor::extractParameterFromTVertex(vsw);

	nepara -= Parameter(offs, offt);
	swpara += Parameter(offs, offt);

	nwpara.s(swpara.s()); nwpara.t(nepara.t());
	separa.s(nepara.s()); separa.t(swpara.t());
}

void TFaceTessellator::processParameterSquare( const Parameter &nwpara, const Parameter &separa, const TriMeshPtr &tri_mesh )
{
	Parameter start, end;

	processParameters(start, end, tri_mesh);
}

TLinkTessellator::TLinkTessellator( const TLinkPtr &link, const TFaceDerivatorPtr &derivator ) :
	_link(link), _derivator(derivator), _ratio(0.1)
{

}

TLinkTessellator::~TLinkTessellator()
{

}

void TLinkTessellator::process( const TriMeshPtr &tri_mesh )
{
	Real step = _ratio * _link->length();
	long count = _link->length() / step;
	Parameter ps = TExtractor::extractParameterFromTVertex(_link->getStartVertex());
	Parameter pe = TExtractor::extractParameterFromTVertex(_link->getEndVertex());
	Parameter se = (pe - ps); 
	Parameter dp = se.normalize() * step;

	Point3D point; Vector3D normal;
	for (long i=0;i<count;i++)
	{
		if (_derivator->zeroAndFirstOrderDerive(ps, point, normal))
		{
			tri_mesh->addPointNormal(point, normal);
		}
		ps += dp;
	}

	if (_derivator->zeroAndFirstOrderDerive(pe, point, normal))
	{
		tri_mesh->addPointNormal(point, normal);
	}
}


TParameterTessellator::TParameterTessellator(  const TFaceDerivatorPtr &derivator, const Parameter &start, const Parameter &end ) :
	_derivator(derivator), _start(start), _end(end), _ratio(0.1)
{

}

TParameterTessellator::~TParameterTessellator()
{

}

void TParameterTessellator::process( const TriMeshPtr &tri_mesh )
{
	Parameter se = _end - _start;
	Real step = se.norm() * _ratio;
	long count = se.norm() / step;
	Parameter dp = se.normalize() * step;

	Parameter ps = _start;
	Point3D point; Vector3D normal;
	for (long i=0;i<count;i++)
	{
		if (_derivator->zeroAndFirstOrderDerive(ps, point, normal))
		{
			tri_mesh->addPointNormal(point, normal);
		}
		ps += dp;
	}

	if (_derivator->zeroAndFirstOrderDerive(_end, point, normal))
	{
		tri_mesh->addPointNormal(point, normal);
	}
}

TParameterSquareTessellator::TParameterSquareTessellator(const TFaceDerivatorPtr &derivator, 
														 const Parameter &north_west, 
														 const Parameter &south_east) :
_derivator(derivator), _north_west(north_west), _south_east(south_east), _ratio(0.1)
{

}

TParameterSquareTessellator::~TParameterSquareTessellator()
{

}

void TParameterSquareTessellator::process( const TriMeshPtr &tri_mesh )
{
	Parameter north_east(_south_east.s(), _north_west.t());
	Parameter south_west(_north_west.s(), _south_east.t());
	Real height = _north_west.t() - _south_east.t();
	Real step = height * _ratio;
	long count = height / step;

	Parameter start = _north_west;
	Parameter end = north_east;

	tri_mesh->clearRowBuffers();
	for (long i=0;i<count;i++)
	{
		TParameterTessellator tessellator(_derivator, start, end);
		tri_mesh->rowBegin();
		tessellator.process(tri_mesh);
		tri_mesh->rowEnd();
		start.t(start.t()-step);
		end.t(end.t()-step);
	}

	TParameterTessellator tessellator(_derivator, south_west, _south_east);
	tri_mesh->rowBegin();
	tessellator.process(tri_mesh);
	tri_mesh->rowEnd();
}

#ifdef use_namespace
}
#endif