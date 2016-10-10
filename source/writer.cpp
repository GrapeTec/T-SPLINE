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

#include <time.h>
#include <writer.h>
#include <finder.h>
#include <sstream>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

TWriter::TWriter( const std::string &file_name ) :
	_file_name(file_name), 
	_use_relative_path(false)
{
}

TWriter::~TWriter()
{
	closeFile();
}

void TWriter::openFile( const std::string &file_name, ios_base::openmode mode /*= ios::binary*/ )
{
	_wfile.open(file_name, mode);
}

void TWriter::closeFile()
{
	_wfile.close();
	_file_name.clear();
}

bool TWriter::valid()
{
	if (_wfile.is_open())
	{
		return true;
	}
	return false;
}

std::string TWriter::fileName()
{
	return _file_name;
}

std::string TWriter::fileNameShort()
{
	std::string short_name;
	int k = _file_name.find_last_of('.');
	for (int i=0;i<k;i++)
	{
		short_name += _file_name[i];
	}

	return short_name;
}

std::ofstream& TWriter::stream()
{
	return _wfile;
}

TriMeshWriter::TriMeshWriter( const std::string &file_name, const TriMeshPtr &tri_mesh) :
	TWriter(file_name), _tri_mesh(tri_mesh)
{
}

TriMeshWriter::~TriMeshWriter()
{

}

bool TriMeshWriter::valid()
{
	return TWriter::valid();
}

StlWriter::StlWriter(const std::string &file_name, const TriMeshPtr &tri_mesh) :
	TriMeshWriter(file_name+".stl", tri_mesh)
{

}

StlWriter::~StlWriter()
{

}

void StlWriter::writeStl( StlMode mode /*= E_STL_BINARY*/ )
{
	switch (mode)
	{
	case TSPLINE::E_STL_BINARY:
		writeStlBinary();
		break;
	case TSPLINE::E_STL_ACII:
		writeStlAcii();
		break;
	default:
		writeStlBinary();
		break;
	}
}

void StlWriter::writeStlBinary()
{
	openFile(fileName(), ios::binary);
	std::ofstream& wfile = stream();
	std::string header = fileNameShort();
	for (int i=0;i<80;i++)
	{
		char c=' ';
		if (int(header.length())>i)
			c=header[i];
		wfile << c;
	}
	TriMeshPtr mesh = triMesh();
	long trisize = mesh->sizeTriangles();
	wfile.write((char *)(&trisize), sizeof(trisize));

	TriVIterator iter;
	for (iter=mesh->triangleIteratorBegin();iter!=mesh->triangleIteratorEnd();iter++)
	{
		TrianglePtr triangle = *iter;
		Word v0 = triangle->point_indices[0];
		Word v1 = triangle->point_indices[1];
		Word v2 = triangle->point_indices[2];
		Point3DPtr point0 = mesh->pointAt(v0);
		Point3DPtr point1 = mesh->pointAt(v1);
		Point3DPtr point2 = mesh->pointAt(v2);

		StlNormal n = facetNormal(point0, point1, point2); 
		wfile.write((char*)(&n), sizeof(n));

		StlPoint p1, p2, p3;
		p1.x = point0->x(); p1.y = point0->y(); p1.z = point0->z();
		p2.x = point1->x(); p2.y = point1->y(); p2.z = point1->z();
		p3.x = point2->x(); p3.y = point2->y(); p3.z = point2->z();
		wfile.write((char*)(&(p1)), sizeof(p1));
		wfile.write((char*)(&(p2)), sizeof(p2));
		wfile.write((char*)(&(p3)), sizeof(p3));
		wfile << char(' ') << char(' ');
	}

	wfile.close();
}

void StlWriter::writeStlAcii()
{
	openFile(fileName(), ios::out);
	std::ofstream& wfile = stream();
	std::string header = fileNameShort();
	wfile << "solid " << header << std::endl;

	TriMeshPtr mesh = triMesh();
	TriVIterator iter;
	for (iter=mesh->triangleIteratorBegin();iter!=mesh->triangleIteratorEnd();iter++)
	{
		TrianglePtr triangle = *iter;
		Word v0 = triangle->point_indices[0];
		Word v1 = triangle->point_indices[1];
		Word v2 = triangle->point_indices[2];
		Point3DPtr point0 = mesh->pointAt(v0);
		Point3DPtr point1 = mesh->pointAt(v1);
		Point3DPtr point2 = mesh->pointAt(v2);

		StlNormal n = facetNormal(point0, point1, point2); 

		wfile << " facet normal " << n.i << " " << n.j << " " << n.k << std::endl;
		wfile << "  outer loop" << std::endl;

		wfile << "   vertex " << point0->x() << " " << point0->y() << " " << point0->z() << std::endl;
		wfile << "   vertex " << point1->x() << " " << point1->y() << " " << point1->z() << std::endl;
		wfile << "   vertex " << point2->x() << " " << point2->y() << " " << point2->z() << std::endl;

		wfile << "  endloop" << std::endl;
		wfile << " endfacet" << std::endl;
	}

	wfile << "endsolid";
	wfile.close();
}

StlNormal StlWriter::facetNormal( const Point3DPtr &p0, const Point3DPtr &p1, const Point3DPtr &p2 )
{
	StlNormal v1, v2, n;
	v1.i = p1->x() - p0->x(); v1.j = p1->y() - p0->y(); v1.k = p1->z() - p0->z();
	v2.i = p2->x() - p1->x(); v2.j = p2->y() - p1->y(); v2.k = p2->z() - p1->z();

	n.i = v1.j * v2.k - v1.k * v2.j;
	n.j = v1.k * v2.i - v1.i * v2.k;
	n.k = v1.i * v2.j - v1.j * v2.i;

	float r = sqrt(n.i*n.i+n.j*n.j+n.k*n.k);
	n.i /= r; n.j /= r; n.k /= r;

	return n;
}

ObjWriter::ObjWriter( const std::string &file_name, const TriMeshPtr &tri_mesh ) :
	TriMeshWriter(file_name+".obj", tri_mesh)
{

}

ObjWriter::~ObjWriter()
{

}

void ObjWriter::writeObj()
{
	openFile(fileName(), ios::out);
	std::ofstream& wfile = stream();
	wfile << "# " << std::endl;
	wfile << "# Wavefront OBJ file" << std::endl;
	wfile << "# Exported by the Open T-Spline Library 1.4" << std::endl;
	wfile << "# GrapeTec, VRLab, BUAA" << std::endl;
	wfile << "# www.grapetec.com" << std::endl;
	wfile << "# " << endl << std::endl;

	TriMeshPtr trimesh = triMesh();
	long offset = 0;
	if (trimesh)
	{
		writeObjMesh(trimesh, offset);
		offset += trimesh->sizePoints();
	}
	TriMshVIterator iter = _more_meshes.begin();
	for (;iter!=_more_meshes.end();iter++)
	{
		trimesh = *iter;
		if (trimesh)
		{
			writeObjMesh(trimesh, offset);
			offset += trimesh->sizePoints();
		}
	}

	wfile.close();
}

void ObjWriter::addMesh( const TriMeshPtr &tri_mesh )
{
	_more_meshes.push_back(tri_mesh);
}

void ObjWriter::writeObjMesh( const TriMeshPtr &tri_mesh, const long offset /*= 0*/ )
{
	if (!tri_mesh) return;
	std::ofstream& wfile = stream();
	wfile << "# object " << tri_mesh->getName() << std::endl;
	wfile << "g " << tri_mesh->getName() << std::endl;
	P3dVIterator piter = tri_mesh->pointIteratorBegin();
	for (;piter!=tri_mesh->pointIteratorEnd();piter++)
	{
		Point3DPtr point = *piter;
		wfile << "v " << point->x() << " " << point->y() << " " << point->z()  << std::endl;
	}
	wfile << "# " << tri_mesh->sizePoints() << " vertices" << std::endl;

	N3dVIterator niter = tri_mesh->normalIteratorBegin();
	for (;niter!=tri_mesh->normalIteratorEnd();niter++)
	{
		Vector3DPtr normal = *niter;
		wfile << "vn " << normal->i() << " " << normal->j() << " " << normal->k()  << std::endl;
	}
	wfile << "# " << tri_mesh->sizeNormals() << " normals" << std::endl;

	TriVIterator titer = tri_mesh->triangleIteratorBegin();
	for (;titer!=tri_mesh->triangleIteratorEnd();titer++)
	{
		TrianglePtr triangle = *titer;
		wfile << "f " << triangle->point_indices[0]+offset+1 << "//" << triangle->normal_indices[0]+offset+1
			<< " " << triangle->point_indices[1]+offset+1 << "//" << triangle->normal_indices[1]+offset+1
			<< " " << triangle->point_indices[2]+offset+1 << "//" << triangle->normal_indices[2]+offset+1
			<< std::endl;
	}
}

DxfWriter::DxfWriter( const std::string &file_name, const TSplinePtr &spline ) :
	TWriter(file_name+".dxf"), _spline(spline)
{

}

DxfWriter::~DxfWriter()
{

}

void DxfWriter::writeDxfTImage()
{
	openFile(fileNameShort()+"-img.dxf", ios::out);
	std::ofstream& wfile = stream();
	wfile << 0 << std::endl << "SECTION" << std::endl;
	wfile << 2 << std::endl << "ENTITIES" << std::endl;

	TImagePtr image = _spline->getTImage();

	TVtxVIterator viter = image->vertexIteratorBegin();
	for (;viter!=image->vertexIteratorEnd();viter++)
	{
		TVertexPtr vertex = *viter;
		writeVertex(vertex);
	}

	TEdgVIterator eiter = image->edgeIteratorBegin();
	for (;eiter!=image->edgeIteratorEnd();eiter++)
	{
		TEdgePtr edge = *eiter;
		writeEdge(edge);
		
	}

	wfile << 0 << std::endl << "ENDSEC" << std::endl;
	wfile << 0 << std::endl << "EOF" << std::endl;
	wfile.close();
}

struct cmp_unique
{
	bool operator()(double index1, double index2)
	{
		return !isEqual(index1, index2);
	}
};

static void getUniqueST(const TVtxVIterator& vbegin, const TVtxVIterator& vend, std::vector<double> &uniques, std::vector<double> &uniquet)
{
	TVtxVIterator vit = vbegin;
	std::vector<double> alls,allt;
	for (vit;vit!=vend;vit++)
	{
		uniques.push_back((*vit)->getS());
		uniquet.push_back((*vit)->getT());
	}
	std::sort(uniques.begin(),uniques.end());
	std::sort(uniquet.begin(),uniquet.end());
	std::vector<double>::iterator its = std::unique(uniques.begin(),uniques.end(),cmp_unique());
	std::vector<double>::iterator itt = std::unique(uniquet.begin(),uniquet.end(),cmp_unique());
	uniques.erase(its,uniques.end());
	uniquet.erase(itt,uniquet.end());
};

template <class T>
struct cmp_find : std::binary_function<T, T, bool>
{
	bool operator()(T index1, T index2) const
	{
		if(!isZero(index1-index2))
			return true;
		return false;
	}
};

static void findVertexPosition(const TVertexPtr& vertex, std::vector<double>& uniques, std::vector<double>& uniquet, int& posx, int& posy)
{
	std::vector<double>::iterator results = std::find_if(uniques.begin(), uniques.end(), bind2nd(cmp_find<double>(),vertex->getS()));
	if(results != uniques.end())
	{
		posx = std::distance(uniques.begin(), results);
	}

	std::vector<double>::iterator resultt = std::find_if(uniquet.begin(), uniquet.end(), bind2nd(cmp_find<double>(),vertex->getT()));
	if(resultt != uniquet.end())
	{
		posy = std::distance(uniquet.begin(), resultt);
	}
}

void DxfWriter::writeEdgePosition(double posx1, double posy1, double posx2, double posy2, int color /*= 200*/, float layer /*= 0.0*/)
{
	std::ofstream& wfile = stream();
	wfile << 0 << std::endl << "LINE" << std::endl;
	wfile << 10 << std::endl << posx1 << std::endl;
	wfile << 20 << std::endl << posy1 << std::endl;
	wfile << 30 << std::endl << layer << std::endl;
	wfile << 11 << std::endl << posx2 << std::endl;
	wfile << 21 << std::endl << posy2 << std::endl;
	wfile << 31 << std::endl << layer << std::endl;
	wfile << 62 << std::endl << color <<std::endl;
}

void DxfWriter::writeNodePosition(const TImagePtr& img, int color/* = 100*/, double offset/* = 0.2*/, double scale/* = 0.03*/)
{
	TVtxVIterator viter = img->vertexIteratorBegin();
	std::vector<double> uniques, uniquet;
	getUniqueST(img->vertexIteratorBegin(), img->vertexIteratorEnd(), uniques, uniquet);
	for (;viter!=img->vertexIteratorEnd();viter++)
	{
		TVertexPtr vertex = *viter;
		TPseudoNodeMatrix pnode_matrix(vertex->nodeIteratorBegin(), vertex->nodeIteratorEnd());
		TNodeV4Ptr north_tip = pnode_matrix.nodeTipNorth();
		TNodeV4Ptr west_tip = pnode_matrix.nodeTipWest();
		TNodeV4Ptr south_tip = pnode_matrix.nodeTipSouth();
		TNodeV4Ptr east_tip = pnode_matrix.nodeTipEast();
		TNodeV4Ptr center = pnode_matrix.nodeCenter();
		int posx, posy;
		findVertexPosition(vertex, uniques, uniquet, posx, posy);
		if(north_tip && (north_tip!=center))
		{
			writeEdgePosition(posx, posy, posx, posy+offset, color);
			writeText(north_tip->getName(), posx, posy+offset, 0.0, scale);
		}
		if(south_tip && (south_tip!=center))
		{
			writeEdgePosition(posx, posy, posx, posy-offset, color);
			writeText(south_tip->getName(), posx, posy-offset, 0.0, scale);
		}
		if(west_tip && (west_tip!=center))
		{
			writeEdgePosition(posx, posy, posx-offset, posy, color);
			writeText(west_tip->getName(), posx-offset, posy, 0.0, scale);
		}
		if(east_tip && (east_tip!=center))
		{
			writeEdgePosition(posx, posy, posx+offset, posy, color);
			writeText(east_tip->getName(), posx+offset, posy, 0.0, scale);
		}
		if((north_tip!=center) && (west_tip!=center) && (north_tip) && (west_tip) && (north_tip->getWest())==(west_tip->getNorth()) && (west_tip->getNorth()))
		{
			writeEdgePosition(posx, posy+offset, posx-offset, posy+offset, color);
			writeEdgePosition(posx-offset, posy, posx-offset, posy+offset, color);
			writeText(west_tip->getNorth()->getName(), posx-offset, posy+offset, 0.0, scale);
		}
		if((north_tip!=center) && (east_tip!=center) && (north_tip) && (east_tip) && (north_tip->getEast())==(east_tip->getNorth()) && (east_tip->getNorth()))
		{
			writeEdgePosition(posx, posy+offset, posx+offset, posy+offset, color);
			writeEdgePosition(posx+offset, posy, posx+offset, posy+offset, color);
			writeText(east_tip->getNorth()->getName(), posx+offset, posy+offset, 0.0, scale);
		}
		if((south_tip!=center) && (west_tip!=center) && (south_tip) && (west_tip) && (south_tip->getWest())==(west_tip->getSouth()) && (west_tip->getSouth()))
		{
			writeEdgePosition(posx, posy-offset, posx-offset, posy-offset, color);
			writeEdgePosition(posx-offset, posy, posx-offset, posy-offset, color);
			writeText(west_tip->getSouth()->getName(), posx-offset, posy-offset, 0.0, scale);
		}
		if((south_tip!=center) && (east_tip!=center) && (south_tip) && (east_tip) && (south_tip->getEast())==(east_tip->getSouth()) && (east_tip->getSouth()))
		{
			writeEdgePosition(posx, posy-offset, posx+offset, posy-offset, color);
			writeEdgePosition(posx+offset, posy, posx+offset, posy-offset, color);
			writeText(east_tip->getSouth()->getName(), posx+offset, posy-offset, 0.0, scale);
		}

		writeText(center->getName(), posx, posy, 0.0, scale);
	}
}

void DxfWriter::writeDxfTConnect()
{
	openFile(fileNameShort()+"-cnt.dxf", ios::out);
	std::ofstream& wfile = stream();
	wfile << 0 << std::endl << "SECTION" << std::endl;
	wfile << 2 << std::endl << "ENTITIES" << std::endl;

	TImagePtr image = _spline->getTImage();
	std::vector<double> uniques, uniquet;
	getUniqueST(image->vertexIteratorBegin(), image->vertexIteratorEnd(), uniques, uniquet);

	TEdgVIterator eiter = image->edgeIteratorBegin();
	for (;eiter!=image->edgeIteratorEnd();eiter++)
	{
		TEdgePtr edge = *eiter;
		int posx1, posy1, posx2, posy2;
		findVertexPosition(edge->getStartVertex(), uniques, uniquet, posx1, posy1);
		findVertexPosition(edge->getEndVertex(), uniques, uniquet, posx2, posy2);
		writeEdgePosition(posx1, posy1, posx2, posy2);
	}

	writeNodePosition(image);

	wfile << 0 << std::endl << "ENDSEC" << std::endl;
	wfile << 0 << std::endl << "EOF" << std::endl;
	wfile.close();
}

void DxfWriter::writeDxfTPointset()
{
	openFile(fileNameShort()+"-pts.dxf", ios::out);
	std::ofstream& wfile = stream();
	wfile << 0 << std::endl << "SECTION" << std::endl;
	wfile << 2 << std::endl << "ENTITIES" << std::endl;

	TPointsetPtr pointset = _spline->getTPointset();
	TObjVIterator piter = pointset->iteratorBegin();
	for (;piter!=pointset->iteratorEnd();piter++)
	{
		TPointPtr point = (*piter)->asTPoint();
		writePoint(point);
		writeText(point->getName(), point->getX(), point->getY(), point->getZ(), 0.1f);
	}

	TConnectPtr connect = _spline->getTConnect();
	TObjVIterator niter = connect->iteratorBegin();
	for (;niter!=connect->iteratorEnd();niter++)
	{
		TNodeV4Ptr node = (*niter)->asTNode()->asTNodeV4();
		TNodeV4Ptr north = node->getNorth();
		TNodeV4Ptr west = node->getWest();

		if (north && !north->isVirtual() && north->getSouth() == node) 
		{
			writeLine(node->getTPoint(), north->getTPoint());
		}
		if (west && !west->isVirtual() && west->getEast() == node) 
		{
			writeLine(node->getTPoint(), west->getTPoint());
		}
	}

	wfile << 0 << std::endl << "ENDSEC" << std::endl;
	wfile << 0 << std::endl << "EOF" << std::endl;
	wfile.close();
}

void DxfWriter::writeVertex( const TVertexPtr &vertex, float layer /*= 0.0*/ )
{
	std::ofstream& wfile = stream();
	wfile << 0 << std::endl << "POINT" <<std::endl;
	wfile << 10 << std::endl << vertex->getS() << std::endl;
	wfile << 20 << std::endl << vertex->getT() << std::endl;
	wfile << 30 << std::endl << layer << std::endl;
	writeText(vertex->getName(), vertex->getS(), vertex->getT(), 0.0);
}

void DxfWriter::writeEdge(const TEdgePtr &edge, float layer /*= 0.0*/ )
{
	std::ofstream& wfile = stream();
	wfile << 0 << std::endl << "LINE" << std::endl;
	wfile << 10 << std::endl << edge->getStartVertex()->getS() << std::endl;
	wfile << 20 << std::endl << edge->getStartVertex()->getT() << std::endl;
	wfile << 30 << std::endl << layer << std::endl;
	wfile << 11 << std::endl << edge->getEndVertex()->getS() << std::endl;
	wfile << 21 << std::endl << edge->getEndVertex()->getT()	<< std::endl;
	wfile << 31 << std::endl << layer << std::endl;
}

void DxfWriter::writePoint( const TPointPtr &point )
{
	std::ofstream& wfile = stream();
	wfile << 0 << std::endl << "POINT" <<std::endl;
	wfile << 10 << std::endl << point->getX() << std::endl;
	wfile << 20 << std::endl << point->getY() << std::endl;
	wfile << 30 << std::endl << point->getZ() << std::endl;
}

void DxfWriter::writeLine( const TPointPtr &start, const TPointPtr &end )
{
	std::ofstream& wfile = stream();
	wfile << 0 << std::endl << "LINE" << std::endl;
	wfile << 10 << std::endl << start->getX() << std::endl;
	wfile << 20 << std::endl << start->getY() << std::endl;
	wfile << 30 << std::endl << start->getZ() << std::endl;
	wfile << 11 << std::endl << end->getX() << std::endl;
	wfile << 21 << std::endl << end->getY()	<< std::endl;
	wfile << 31 << std::endl << end->getZ()	<< std::endl;
}

void DxfWriter::writeText( const std::string &text, float x, float y, float z,
						  float height /*= 0.1f*/, float angle /*= 0.0f*/, float scale /*= 1.0f*/ )
{
	std::ofstream& wfile = stream();
	wfile << 0 << std::endl << "TEXT" << std::endl;
	wfile << 1 << std::endl << text << std::endl;
	wfile << 10 << std::endl << x << std::endl;
	wfile << 20 << std::endl << y << std::endl;
	wfile << 30 << std::endl << z << std::endl;
	wfile << 40 << std::endl << height << std::endl;
	wfile << 50 << std::endl << angle << std::endl;
	wfile << 41 << std::endl << scale << std::endl;
}


StepWriter::StepWriter( const std::string &file_name,  const TGroupPtr &objects) :
	TWriter(file_name+".stp"), _objects(objects)
{
}

StepWriter::~StepWriter()
{

}

void StepWriter::writeStep()
{
	openFile(fileName(), ios::out);
	std::ofstream& file = stream();
	const time_t t = time(NULL);
	struct tm* current_time = localtime(&t);
	file << "ISO-10303-21;" << std::endl;
	//////////////////////////////////////////////////////////////////////////
	// HEADER SECTION
	file << "HEADER;" << std::endl;
	file << "FILE_DESCRIPTION(('T-SPLINE EXAMPLE',''),'1');" << std::endl;
	file << "FILE_NAME('" << fileName() << "',"
		 << "'" << current_time->tm_mday << "-"<< (1 + current_time->tm_mon) << "-" << (1900 + current_time->tm_year) << "'"
		 <<",('WENLEI XIAO','RUI LI','WEI WANG','GANG ZHAO'),('GrapeTec, BUAA'),$,'ISO 10303-238e1',$);" << std::endl;
	file << "FILE_SCHEMA(('integrated_cnc_schema'));" << std::endl;
	file << "ENDSEC;" << std::endl << std::endl;

	//////////////////////////////////////////////////////////////////////////
	// DATA SECTION
	allocateStepIds();
	file << "DATA;" << std::endl;
	TObjVIterator iter;
	for (iter=_objects->iteratorBegin();iter!=_objects->iteratorEnd();iter++)
	{
		TObjectPtr object = *iter;
		if (TVertexPtr vertex = object->asTVertex())
		{
			writeTVertex(vertex);
		}
		else if (TEdgePtr edge = object->asTEdge())
		{
			writeTEdge(edge);
		}
		else if (TLinkPtr link = object->asTLink())
		{
			writeTLink(link);
		}
		else if (TFacePtr face = object->asTFace())
		{
			writeTFace(face);
		}
		else if (TEdgeConditionPtr edge_condition = object->asTEdgeCondition())
		{
			writeTEdgeCondition(edge_condition);
		}
		else if (TNodePtr node = object->asTNode())
		{
			if (TNodeV4Ptr node_v4 = node->asTNodeV4())
			{
				writeTNodeV4(node_v4);
			}
		}
		else if (TPointPtr point = object->asTPoint())
		{
			writeTPoint(point);
		}
		else if (TImagePtr image = object->asTImage())
		{
			writeTImage(image);
		}
		else if (TGroupPtr group = object->asTGroup())
		{
			if (TConnectPtr node_grid = group->asTConnect())
			{
				writeTConnect(node_grid);
			}
			else if (TPointsetPtr point_grid = group->asTPointset())
			{
				writeTPointset(point_grid);
			}
		}
		else if (TSplinePtr spline = object->asTSpline())
		{
			writeTSpline(spline);
		}
	}	
	file << "ENDSEC;" << std::endl;

	file << "END-ISO-10303-21;" << std::endl;
}

void StepWriter::allocateStepIds()
{
	long step_id = 1;
	TObjVIterator iter;
	for (iter=_objects->iteratorBegin();iter!=_objects->iteratorEnd();iter++)
	{
		TObjectPtr object = *iter;
		if (TVertexPtr vertex = object->asTVertex())
		{
			step_id++; // reserved for point_on_surface
			vertex->setId(step_id);	step_id++;
		}
		else if (TEdgePtr edge = object->asTEdge())
		{
			edge->setId(step_id); step_id++;
		}
		else if (TLinkPtr link = object->asTLink())
		{
			link->setId(step_id); step_id++;
		}
		else if (TFacePtr face = object->asTFace())
		{
			step_id++; // reserved for edge_loop
			step_id++; // reserved for face_bound
			face->setId(step_id); step_id++;
		}
		else if (TEdgeConditionPtr edge_condition = object->asTEdgeCondition())
		{
			edge_condition->setId(step_id); step_id++;
		}
		else if (TNodePtr node = object->asTNode())
		{
			if (TNodeV4Ptr node_v4 = node->asTNodeV4())
			{
				node_v4->setId(step_id); step_id++;
			}
		}
		else if (TPointPtr point = object->asTPoint())
		{
			point->setId(step_id); step_id++;
		}
		else if (TImagePtr image = object->asTImage())
		{
			image->setId(step_id); step_id++;
		}
		else if (TGroupPtr group = object->asTGroup())
		{
			if (TConnectPtr node_grid = group->asTConnect())
			{
				node_grid->setId(step_id); step_id++;
			}
			else if (TPointsetPtr point_grid = group->asTPointset())
			{
				point_grid->setId(step_id); step_id++;
			}
		}
		else if (TSplinePtr spline = object->asTSpline())
		{
			spline->setId(step_id); step_id++;
		}
	}	
}

int OBJ2ID(const TObjectPtr &object)
{
	if (object) return object->getId();
	else return 0;
}

std::string ID2REF(int id)
{
	std::stringstream ss;
	std::string str;
	if (id > 0) ss << "#" << id;
	else ss << "$";
	ss >> str;
	return str;
}

std::string BOOL2STR(bool val)
{
	if (val) 
		return ".T.";
	else
		return ".F.";
}

void StepWriter::writeTVertex( const TVertexPtr &vertex )
{
	std::ofstream& file = stream();
	TFinder finder(_objects);
	TImagePtr image = castPtr<TImage>(finder.findObjectByType(E_TIMAGE));

	TLinkPtr north = vertex->getNorth();
	TLinkPtr west = vertex->getWest();
	TLinkPtr south = vertex->getSouth();
	TLinkPtr east = vertex->getEast();

	file << ID2REF(vertex->getId()-1) << "=POINT_ON_SURFACE("
		<< "''" << "," 
		<< ID2REF(image->getId()) << ","
		<< std::setiosflags(ios::fixed) << vertex->getS() << "," << vertex->getT()
		<< ");" << std::endl;

	file << ID2REF(vertex->getId()) << "=T_VERTEX("
		<< "'" << vertex->getName() << "'" << "," 
		<< ID2REF(vertex->getId()-1) << ","
		<< ID2REF(OBJ2ID(north)) << "," << ID2REF(OBJ2ID(west)) << ","
		<< ID2REF(OBJ2ID(south)) << "," << ID2REF(OBJ2ID(east))
		<< ");" << std::endl;
}

void StepWriter::writeTEdge( const TEdgePtr &edge )
{
	std::ofstream& file = stream();
	TVertexPtr vstart =	edge->getStartVertex();
	TVertexPtr vend = edge->getEndVertex();
	TFacePtr lface = edge->getLeftFace();
	TFacePtr rface = edge->getRightFace();
	bool isboundary = edge->isBoundary();
	file << ID2REF(edge->getId()) << "=T_EDGE("
		<< "'" << edge->getName() << "'" << "," 
		<< ID2REF(OBJ2ID(vstart)) << "," << ID2REF(OBJ2ID(vend)) << ","
		<< ID2REF(OBJ2ID(lface)) << "," << ID2REF(OBJ2ID(rface)) << ","
		<< BOOL2STR(isboundary)	<< ");" << std::endl;
}

void StepWriter::writeTLink( const TLinkPtr &link )
{
	std::ofstream& file = stream();
	TEdgePtr edge = link->getTEdge();
	bool orientation = link->getOrientation();

	file << ID2REF(link->getId()) << "=T_LINK("
		<< "'" << link->getName() << "'" << "," 
		<< "*" << "," << "*" << ","
		<< ID2REF(OBJ2ID(edge)) << "," << BOOL2STR(orientation)
		<< ");" << std::endl;
}

void StepWriter::writeTFace( const TFacePtr &face )
{
	std::ofstream& file = stream();
	//////////////////////////////////////////////////////////////////////////
	// edge_loop
	file << ID2REF(face->getId()-2) << "=EDGE_LOOP("
		<< "''" << "," 
		<< "(";
	TLnkLIterator iter=face->linkIteratorBegin();
	TLinkPtr link = *iter;
	file << "#" << link->getId();
	for (iter++;iter!=face->linkIteratorEnd();iter++)
	{
		TLinkPtr link = *iter;
		file << "," << "#" << link->getId();
	}
	file << "));" << std::endl;

	//////////////////////////////////////////////////////////////////////////
	// face_bound
	file << ID2REF(face->getId()-1) << "=FACE_BOUND("
		<< "''," << ID2REF(face->getId()-2) << ","
		<< ".T.);" << std::endl;

	//////////////////////////////////////////////////////////////////////////
	// t_face
	file << ID2REF(face->getId()) << "=T_FACE("
		<< "'" << face->getName() << "'" << "," 
		<< "(" << ID2REF(face->getId()-1) << ")"
		<< ");" << std::endl;
}

void StepWriter::writeTEdgeCondition( const TEdgeConditionPtr &edge_condition )
{
	std::ofstream& file = stream();
	TEdgePtr edge = edge_condition->getEdge();
	bool boundary_condition = edge_condition->getBoundaryCondtion();

	file << ID2REF(edge_condition->getId()) << "=T_EDGE_CONDITION("
		<< "'" << edge_condition->getName() << "'" << "," 
		<< ID2REF(OBJ2ID(edge)) << "," << BOOL2STR(boundary_condition)
		<< ");" << std::endl;
}

void StepWriter::writeTNodeV4( const TNodeV4Ptr &node_v4 )
{
	std::ofstream& file = stream();

	TVertexPtr vertex = node_v4->getTVertex();
	TPointPtr point = node_v4->getTPoint();
	TNodeV4Ptr north = node_v4->getNorth();
	TNodeV4Ptr west = node_v4->getWest();
	TNodeV4Ptr south = node_v4->getSouth();
	TNodeV4Ptr east = node_v4->getEast();

	file << ID2REF(node_v4->getId()) << "=T_NODE_V4("
		<< "'" << node_v4->getName() << "'" << "," 
		<< ID2REF(OBJ2ID(vertex)) << "," << ID2REF(OBJ2ID(point)) << ","
		<< ID2REF(OBJ2ID(north)) << "," << ID2REF(OBJ2ID(west)) << ","
		<< ID2REF(OBJ2ID(south)) << "," << ID2REF(OBJ2ID(east)) 
		<< ");" << std::endl;
}

void StepWriter::writeTPoint( const TPointPtr &point )
{
	std::ofstream& file = stream();

	file << ID2REF(point->getId()) << "=RATIONAL_POINT("
		<< "'" << point->getName() << "'" << "," << std::setiosflags(ios::fixed)
		<< "(" <<  point->getX() << "," << point->getY() << "," << point->getZ() << "),"
		<< point->getW() << ");" << std::endl;
}

void StepWriter::writeTImage( const TImagePtr &image )
{
	std::ofstream& file = stream();
	TFinder finder(_objects);

	file << ID2REF(image->getId()) << "=T_IMAGE("
		<< "'" << image->getName() << "'" << ",";
	file << "(";
	TFacVIterator fiter = image->faceIteratorBegin();
	file << ID2REF(OBJ2ID(*fiter));
	for (fiter++;fiter!=image->faceIteratorEnd();fiter++)
	{
		file << "," << ID2REF(OBJ2ID(*fiter));
	}
	file << "),";
	file << "(";
	TLnkVIterator liter = image->linkIteratorBegin();
	file << ID2REF(OBJ2ID(*liter));
	for (liter++;liter!=image->linkIteratorEnd();liter++)
	{
		file << "," << ID2REF(OBJ2ID(*liter));
	}
	file << "),";
	file << "(";
	TEdgVIterator eiter = image->edgeIteratorBegin();
	file << ID2REF(OBJ2ID(*eiter));
	for (eiter++;eiter!=image->edgeIteratorEnd();eiter++)
	{
		file << "," << ID2REF(OBJ2ID(*eiter));
	}
	file << "),";
	file << "(";
	TVtxVIterator viter = image->vertexIteratorBegin();
	file << ID2REF(OBJ2ID(*viter));
	for (viter++;viter!=image->vertexIteratorEnd();viter++)
	{
		file << "," << ID2REF(OBJ2ID(*viter));
	}
	file << ")";

	file << ");" << std::endl;
}

void StepWriter::writeTConnect( const TConnectPtr &node_grid )
{
	std::ofstream& file = stream();

	file << ID2REF(node_grid->getId()) << "=T_CONNECT("
		<< "'" << node_grid->getName() << "'" << ",";

	file << "(";
	TObjVIterator iter = node_grid->iteratorBegin();
	file << ID2REF(OBJ2ID(*iter));
	for (iter++;iter!=node_grid->iteratorEnd();iter++)
	{
		file << "," << ID2REF(OBJ2ID(*iter));
	}
	file << ")";

	file << ");" << std::endl;
}

void StepWriter::writeTPointset( const TPointsetPtr &point_grid )
{
	std::ofstream& file = stream();

	file << ID2REF(point_grid->getId()) << "=T_POINTSET("
		<< "'" << point_grid->getName() << "'" << ",";

	file << "(";
	TObjVIterator iter = point_grid->iteratorBegin();
	file << ID2REF(OBJ2ID(*iter));
	for (iter++;iter!=point_grid->iteratorEnd();iter++)
	{
		file << "," << ID2REF(OBJ2ID(*iter));
	}
	file << ")";

	file << ");" << std::endl;
}

void StepWriter::writeTSpline( const TSplinePtr &spline )
{
	std::ofstream& file = stream();

	file << ID2REF(spline->getId()) << "=T_SPLINE_SURFACE("
		<< "'" << spline->getName() << "'" << ","
		<< spline->getSDegree() << "," << spline->getTDegree() << "," 
		<< BOOL2STR(spline->getForceBezierEndCondition()) << ","
		//<< BOOL2STR(spline->getCapType()) << "," << BOOL2STR(spline->getStarSmoothness()) << ","
		<< ID2REF(OBJ2ID(spline->getTImage())) << ","
		<< ID2REF(OBJ2ID(spline->getTConnect())) << ","
		<< ID2REF(OBJ2ID(spline->getTPointset())) 
		<< ");" << std::endl;
}


// Gnuplot Writer
/////////////////////////////////////////////////////////////////////////////

GnuplotWriter::GnuplotWriter(const std::string &file_name, const TriMeshPtr &tri_mesh, const TSplinePtr &spline) :
	TriMeshWriter(file_name + ".plt", tri_mesh), _spline(spline)
{

}

GnuplotWriter::~GnuplotWriter()
{

}
//  Write Gnuplot Mesh file "*-mesh.plt"
void GnuplotWriter::writeGnuplMesh()
{
	openFile(fileNameShort() + "-mesh.plt", ios::out);
	std::ofstream& wfile = stream();
	wfile << "# " << std::endl;
	wfile << "# Gnuplot-mesh file" << std::endl;
	wfile << "# Exported by the Open T-Spline Library 1.4" << std::endl;
	wfile << "# GrapeTec, VRLab, BUAA" << std::endl;
	wfile << "# www.grapetec.com" << std::endl;
	wfile << "# " << std::endl;
	wfile << "# Some useful functions for view modifications: " << std::endl;
	wfile << "set palette rgb \"green\"   # - optional color modification" << std::endl;
	wfile << "# set palette gray  # - optional color modification" << endl << std::endl;
	wfile << "# unset tics" << std::endl;
	wfile << "# unset border" << std::endl;
	wfile << "# "  << std::endl;
	wfile << "set pm3d" << std::endl;
	wfile << "set style data pm3d" << std::endl;
	wfile << "set view equal xyz" << std::endl;	
	wfile << "splot \"-\" notitle" << std::endl;
	wfile << "# " << std::endl;

	TriMeshPtr mesh = triMesh();
	TriVIterator iter;
	for (iter = mesh->triangleIteratorBegin(); iter != mesh->triangleIteratorEnd(); iter++)
	{
		TrianglePtr triangle = *iter;
		Word v0 = triangle->point_indices[0];
		Word v1 = triangle->point_indices[1];
		Word v2 = triangle->point_indices[2];
		Point3DPtr point0 = mesh->pointAt(v0);
		Point3DPtr point1 = mesh->pointAt(v1);
		Point3DPtr point2 = mesh->pointAt(v2);

		wfile << point0->x() << " " << point0->y() << " " << point0->z() << std::endl;
		wfile << point1->x() << " " << point1->y() << " " << point1->z() << std::endl;
		wfile << std::endl;
		wfile << point2->x() << " " << point2->y() << " " << point2->z() << std::endl;
		wfile << point2->x() << " " << point2->y() << " " << point2->z() << std::endl;

		wfile  << std::endl;
		wfile  << std::endl;
	}

	wfile << "#";
	wfile.close();
}
//////////////////////////////////////////////////////////////////////////////

//  Write Gnuplot T-image file "*-img.plt"
void GnuplotWriter::writeGnuplTImage()
{
	openFile(fileNameShort() + "-img.plt", ios::out);
	std::ofstream& wfile = stream();
	wfile << "# " << std::endl;
	wfile << "# Gnuplot-img file" << std::endl;
	wfile << "# Exported by the Open T-Spline Library 1.4" << std::endl;
	wfile << "# GrapeTec, VRLab, BUAA" << std::endl;
	wfile << "# www.grapetec.com" << std::endl;
	wfile << "# " << std::endl;
	wfile << "set lmargin at screen 0.15" << std::endl;
	wfile << "set rmargin at screen 0.85" << std::endl;
	wfile << "set bmargin at screen 0.10" << std::endl;
	wfile << "set tmargin at screen 0.90" << std::endl;
	wfile << "unset tics" << std::endl;
	wfile << "unset border" << std::endl;
	wfile << "set style line 1 lc rgb 'red' pt 7   # circle" << std::endl;
	
	TImagePtr image = _spline->getTImage();

	TVtxVIterator viter = image->vertexIteratorBegin();
	for (;viter!=image->vertexIteratorEnd();viter++)
	{
		TVertexPtr vertex = *viter;
		writeVertex(vertex);
	}
	
	wfile << "#" << std::endl;
	wfile << "plot \"-\" notitle with linespoints ls 1" << std::endl;
	wfile << "#" << std::endl;

	TEdgVIterator eiter = image->edgeIteratorBegin();
	for (; eiter != image->edgeIteratorEnd(); eiter++)
	{
		TEdgePtr edge = *eiter;
		writeEdge(edge);
	}
	wfile.close();
}

void GnuplotWriter::writeVertex(const TVertexPtr &vertex, double view_offset/* = 0.05*/)
{
	std::ofstream& wfile = stream();
	writeText(vertex->getName(), vertex->getS()+view_offset, vertex->getT()+view_offset, 0.0);	
}

void GnuplotWriter::writeEdge(const TEdgePtr &edge)
{
	std::ofstream& wfile = stream();
	wfile << edge->getStartVertex()->getS() << " ";
	wfile << edge->getStartVertex()->getT() << std::endl;
	wfile << edge->getEndVertex()->getS() << " ";
	wfile << edge->getEndVertex()->getT() << std::endl;
	wfile << std::endl;
	wfile << std::endl;
}

void GnuplotWriter::writeEdgePosition(double posx1, double posy1, double posx2, double posy2)
{
	std::ofstream& wfile = stream();
	wfile << posx1 << " ";
	wfile << posy1 << std::endl;
	wfile << posx2 << " ";
	wfile << posy2 << std::endl;
	wfile << std::endl;
	wfile << std::endl;
	
}

void GnuplotWriter::writeNodePosition(const TImagePtr& img, double offset/* = 0.2*/)
{
	TVtxVIterator viter = img->vertexIteratorBegin();
	std::vector<double> uniques, uniquet;
	getUniqueST(img->vertexIteratorBegin(), img->vertexIteratorEnd(), uniques, uniquet);
	for (;viter!=img->vertexIteratorEnd();viter++)
	{
		TVertexPtr vertex = *viter;
		TPseudoNodeMatrix pnode_matrix(vertex->nodeIteratorBegin(), vertex->nodeIteratorEnd());
		TNodeV4Ptr north_tip = pnode_matrix.nodeTipNorth();
		TNodeV4Ptr west_tip = pnode_matrix.nodeTipWest();
		TNodeV4Ptr south_tip = pnode_matrix.nodeTipSouth();
		TNodeV4Ptr east_tip = pnode_matrix.nodeTipEast();
		TNodeV4Ptr center = pnode_matrix.nodeCenter();
		int posx, posy;
		findVertexPosition(vertex, uniques, uniquet, posx, posy);
		if(north_tip && (north_tip!=center))
		{
			writeEdgePosition(posx, posy, posx, posy+offset);
		}
		if(south_tip && (south_tip!=center))
		{
			writeEdgePosition(posx, posy, posx, posy-offset);
		}
		if(west_tip && (west_tip!=center))
		{
			writeEdgePosition(posx, posy, posx-offset, posy);		
		}
		if(east_tip && (east_tip!=center))
		{
			writeEdgePosition(posx, posy, posx+offset, posy);			
		}
		if((north_tip!=center) && (west_tip!=center) && (north_tip) && (west_tip) && (north_tip->getWest())==(west_tip->getNorth()) && (west_tip->getNorth()))
		{
			writeEdgePosition(posx, posy+offset, posx-offset, posy+offset);
			writeEdgePosition(posx-offset, posy, posx-offset, posy+offset);		
		}
		if((north_tip!=center) && (east_tip!=center) && (north_tip) && (east_tip) && (north_tip->getEast())==(east_tip->getNorth()) && (east_tip->getNorth()))
		{
			writeEdgePosition(posx, posy+offset, posx+offset, posy+offset);
			writeEdgePosition(posx+offset, posy, posx+offset, posy+offset);		
		}
		if((south_tip!=center) && (west_tip!=center) && (south_tip) && (west_tip) && (south_tip->getWest())==(west_tip->getSouth()) && (west_tip->getSouth()))
		{
			writeEdgePosition(posx, posy-offset, posx-offset, posy-offset);
			writeEdgePosition(posx-offset, posy, posx-offset, posy-offset);		
		}
		if((south_tip!=center) && (east_tip!=center) && (south_tip) && (east_tip) && (south_tip->getEast())==(east_tip->getSouth()) && (east_tip->getSouth()))
		{
			writeEdgePosition(posx, posy-offset, posx+offset, posy-offset);
			writeEdgePosition(posx+offset, posy, posx+offset, posy-offset);		
		}
	}
}


void GnuplotWriter::writeTextPosition(const TImagePtr& img, double offset/* = 0.2*/,  double view_offset/* = 0.05*/)
{
	TVtxVIterator viter = img->vertexIteratorBegin();
	std::vector<double> uniques, uniquet;
	getUniqueST(img->vertexIteratorBegin(), img->vertexIteratorEnd(), uniques, uniquet);
	for (;viter!=img->vertexIteratorEnd();viter++)
	{
		TVertexPtr vertex = *viter;
		TPseudoNodeMatrix pnode_matrix(vertex->nodeIteratorBegin(), vertex->nodeIteratorEnd());
		TNodeV4Ptr north_tip = pnode_matrix.nodeTipNorth();
		TNodeV4Ptr west_tip = pnode_matrix.nodeTipWest();
		TNodeV4Ptr south_tip = pnode_matrix.nodeTipSouth();
		TNodeV4Ptr east_tip = pnode_matrix.nodeTipEast();
		TNodeV4Ptr center = pnode_matrix.nodeCenter();
		int posx, posy;
		findVertexPosition(vertex, uniques, uniquet, posx, posy);
		if(north_tip && (north_tip!=center))
		{
			writeText(north_tip->getName(), posx, posy+offset, 0.0);
		}
		if(south_tip && (south_tip!=center))
		{
			writeText(south_tip->getName(), posx, posy-offset, 0.0);
		}
		if(west_tip && (west_tip!=center))
		{			
			writeText(west_tip->getName(), posx-offset, posy-view_offset, 0.0);
		}
		if(east_tip && (east_tip!=center))
		{
			writeText(east_tip->getName(), posx+offset, posy-view_offset, 0.0);
		}
		if((north_tip!=center) && (west_tip!=center) && (north_tip) && (west_tip) && (north_tip->getWest())==(west_tip->getNorth()) && (west_tip->getNorth()))
		{
			writeText(west_tip->getNorth()->getName(), posx-offset, posy+offset, 0.0);
		}
		if((north_tip!=center) && (east_tip!=center) && (north_tip) && (east_tip) && (north_tip->getEast())==(east_tip->getNorth()) && (east_tip->getNorth()))
		{
			writeText(east_tip->getNorth()->getName(), posx+offset, posy+offset, 0.0);
		}
		if((south_tip!=center) && (west_tip!=center) && (south_tip) && (west_tip) && (south_tip->getWest())==(west_tip->getSouth()) && (west_tip->getSouth()))
		{
			writeText(west_tip->getSouth()->getName(), posx-offset, posy-offset, 0.0);
		}
		if((south_tip!=center) && (east_tip!=center) && (south_tip) && (east_tip) && (south_tip->getEast())==(east_tip->getSouth()) && (east_tip->getSouth()))
		{
			writeText(east_tip->getSouth()->getName(), posx+offset, posy-offset, 0.0);
		}

		writeText(center->getName(), posx, posy-view_offset, 0.0);
	}
}

//  Write Gnuplot T-connect file "*-cnt.plt"
void GnuplotWriter::writeGnuplTConnect()
{
	openFile(fileNameShort()+"-cnt.plt", ios::out);
	std::ofstream& wfile = stream();
	wfile << "# " << std::endl;
	wfile << "# Gnuplot-cnt file" << std::endl;
	wfile << "# Exported by the Open T-Spline Library 1.4" << std::endl;
	wfile << "# GrapeTec, VRLab, BUAA" << std::endl;
	wfile << "# www.grapetec.com" << std::endl;
	wfile << "# " << std::endl;
	wfile << "set lmargin at screen 0.15" << std::endl;
	wfile << "set rmargin at screen 0.85" << std::endl;
	wfile << "set bmargin at screen 0.10" << std::endl;
	wfile << "set tmargin at screen 0.90" << std::endl;
	wfile << "unset tics" << std::endl;
	wfile << "unset border" << std::endl;
	wfile << "set style line 1 lc rgb 'blue' pt 7   # circle" << std::endl;
	wfile << "set style line 2 lc rgb 'red' pt 3   # star" << std::endl;
	wfile << "#" << std::endl;

	TImagePtr image = _spline->getTImage();
	std::vector<double> uniques, uniquet;
	getUniqueST(image->vertexIteratorBegin(), image->vertexIteratorEnd(), uniques, uniquet);

	writeTextPosition(image);

	wfile << "# unset label" << std::endl;
	wfile << "#" << std::endl;
	wfile << "plot \"-\" notitle with linespoints ls 1, \\" << std::endl;
	wfile << "\"-\" notitle with linespoints ls 2" << std::endl;
	wfile << "#" << std::endl;

	TEdgVIterator eiter = image->edgeIteratorBegin();
	for (;eiter!=image->edgeIteratorEnd();eiter++)
	{
		TEdgePtr edge = *eiter;
		int posx1, posy1, posx2, posy2;
		findVertexPosition(edge->getStartVertex(), uniques, uniquet, posx1, posy1);
		findVertexPosition(edge->getEndVertex(), uniques, uniquet, posx2, posy2);
		writeEdgePosition(posx1, posy1, posx2, posy2);	
	}

	wfile << "EOF" << std::endl;
	wfile << std::endl;
	wfile << std::endl;

	writeNodePosition(image);
	wfile << "EOF" << std::endl;

	wfile.close();
}


//  Write Gnuplot T-pointset file "*-pts.plt"
void GnuplotWriter::writeGnuplTPointset()
{
	openFile(fileNameShort() + "-pts.plt", ios::out);
	std::ofstream& wfile = stream();
	wfile << "# " << std::endl;
	wfile << "# Gnuplot-pts file" << std::endl;
	wfile << "# Exported by the Open T-Spline Library 1.4" << std::endl;
	wfile << "# GrapeTec, VRLab, BUAA" << std::endl;
	wfile << "# www.grapetec.com" << std::endl;
	wfile << "# " << std::endl;
	wfile << "set view equal xyz" << std::endl;
	wfile << "unset tics" << std::endl;
	wfile << "unset border" << std::endl;
	wfile << "set style line 1 lc rgb 'blue' pt 7   # circle" << std::endl;
	wfile << "#" << std::endl;
	
	TPointsetPtr pointset = _spline->getTPointset();
	TObjVIterator piter = pointset->iteratorBegin();
	for (; piter != pointset->iteratorEnd(); piter++)
	{
		TPointPtr point = (*piter)->asTPoint();	
		writeText(point->getName(), point->getX(), point->getY(), point->getZ());
	}

	wfile << "# unset label" << std::endl;
	wfile << "#" << std::endl;
	wfile << "#" << std::endl;
	wfile << "splot \"-\" notitle with linespoints ls 1" << std::endl;
	wfile << "#" << std::endl;

	TConnectPtr connect = _spline->getTConnect();
	TObjVIterator niter = connect->iteratorBegin();
	for (; niter != connect->iteratorEnd(); niter++)
	{
		TNodeV4Ptr node = (*niter)->asTNode()->asTNodeV4();
		TNodeV4Ptr north = node->getNorth();
		TNodeV4Ptr west = node->getWest();

		if (north && !north->isVirtual() && north->getSouth() == node)
		{
			writeLine(node->getTPoint(), north->getTPoint());
		}
		if (west && !west->isVirtual() && west->getEast() == node)
		{
			writeLine(node->getTPoint(), west->getTPoint());
		}
	}
		
	wfile << "EOF" << std::endl;
	wfile.close();
}


void GnuplotWriter::writeLine(const TPointPtr &start, const TPointPtr &end)
{
	std::ofstream& wfile = stream();
	wfile << start->getX() << " ";
	wfile << start->getY() << " ";
	wfile << start->getZ() << std::endl;
	wfile << end->getX() << " ";
	wfile << end->getY() << " ";
	wfile << end->getZ() << std::endl;
	wfile << std::endl;
	wfile << std::endl;

}

void GnuplotWriter::writeText( const std::string &text, float x, float y, float z)
{
	std::ofstream& wfile = stream();
	wfile << "set label  at " << x << ", " << y << ", " << z << " '" << text << "'" << " front" << std::endl;
}



#ifdef use_namespace
}
#endif
