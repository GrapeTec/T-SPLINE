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

/**  @file  [writer]  
*  @brief  This file contains the writer classes.
  *  @author  <Wenlei Xiao>  
  *  @date  <2015.04.08>  
  *  @version  <v1.0>  
  *  @note  
  *  The writer classes help to convert the T-spline data structure into other file formats (stl, obj, stp, dxf, etc.).   
*/

#ifndef WRITER_H
#define WRITER_H

#include <utils.h>
#include <trimesh.h>
#include <tspline.h>
#include <multiplicity.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif
	
/**  
  *  @class  <TWriter> 
  *  @brief  Base class of the writers 
  *  @note  
  *  TWriter is the abstract base class of all other writers which generates the corresponding exchange data files.
*/
class TWriter
{
public:
	TWriter();
	TWriter(const std::string &file_name);
	virtual ~TWriter();

	/** Open a target file with a specified mode ( ios::binary as default). */
	void openFile(const std::string &file_name, ios_base::openmode mode = ios::binary);
	/** Close the file. */
	void closeFile();

	/** Check if the writer is valid. */
	virtual bool valid();

	/** Get the file name as string. */
	std::string fileName();
	/** Get the pure file name as string. */
	std::string fileNameShort();
protected:
	std::ofstream& stream();
private:
	std::ofstream _wfile;
	std::string _file_path;
	std::string _file_name;
	bool _use_relative_path;
};
DECLARE_ASSISTANCES(TWriter, TWtr)

/**  
  *  @class  <TriMeshWriter> 
  *  @brief  Base class of the writers 
  *  @note  
  *  TriMeshWriter is the base class for the writers which generates triangle mesh files (stl and obj).
*/
class TriMeshWriter : public TWriter
{
public:
	TriMeshWriter();
	TriMeshWriter(const std::string &file_name, const TriMeshPtr &tri_mesh);
	virtual ~TriMeshWriter();

public:
	/** Set the triangle mesh pointer. */
	void triMesh(const TriMeshPtr &tri_mesh) {_tri_mesh = tri_mesh;}
	/** Get the triangle mesh pointer. */
	TriMeshPtr triMesh(){ return _tri_mesh; }
	/** Check if the writer is valid. */
	virtual bool valid();
protected:
	
private:
	TriMeshPtr _tri_mesh;
};
DECLARE_ASSISTANCES(TriMeshWriter, TriMshWtr)

struct StlNormal
{
	float i, j, k;
};

struct StlPoint
{
	float x, y, z;
};
enum StlMode {E_STL_BINARY, E_STL_ACII};

/**  
  *  @class  <StlWriter> 
  *  @brief  Base class of the writers 
  *  @note  
  *  StlWriter generates the STL file in either binary or ACSII modes.
*/
class StlWriter : public TriMeshWriter
{
public:
	StlWriter(const std::string &file_name, const TriMeshPtr &tri_mesh);
	virtual ~StlWriter();
public:
	/** Write the STL file as the specified mode (binary or ascii, binary as default). */
	void writeStl(StlMode mode = E_STL_BINARY);
	/** Write the STL file as binary. */
	void writeStlBinary();
	/** Write the STL file as ascii. */
	void writeStlAcii();
protected:
	StlNormal facetNormal(const Point3DPtr &p0, const Point3DPtr &p1, const Point3DPtr &p2);
private:

};
DECLARE_ASSISTANCES(StlWriter, StlWtr)

/**  
  *  @class  <ObjWriter> 
  *  @brief  Base class of the writers 
  *  @note  
  *  ObjWriter generates the OBJ file.
*/
class ObjWriter : public TriMeshWriter
{
public:
	ObjWriter(const std::string &file_name, const TriMeshPtr &tri_mesh);
	virtual ~ObjWriter();
public:
	/** Add a triangle mesh pointer. */
	void addMesh(const TriMeshPtr &tri_mesh);
	/** Write the OBJ file. */
	void writeObj();
protected:
	void writeObjMesh(const TriMeshPtr &tri_mesh, const long offset = 0);
private:
	TriMshVector _more_meshes;
};
DECLARE_ASSISTANCES(ObjWriter, ObjWtr)

/**  
  *  @class  <DxfWriter> 
  *  @brief  Base class of the writers 
  *  @note  
  *  DxfWriter generates the DXF files (T-image, T-connect, and T-pointset).
*/
class DxfWriter : public TWriter
{
public:
	DxfWriter(const std::string &file_name, const TSplinePtr &spline);
	virtual ~DxfWriter();
public:
	/** Write the T-image data into a DXF file. */
	void writeDxfTImage();
	/** Write the T-connect data into a DXF file. */
	void writeDxfTConnect();
	/** Write the T-pointset data into a DXF file. */
	void writeDxfTPointset();
protected:
	void writeVertex(const TVertexPtr &vertex, float layer = 0.0);
	void writeEdge(const TEdgePtr &edge, float layer = 0.0);
	void writePoint(const TPointPtr &point);
	void writeLine(const TPointPtr &start, const TPointPtr &end);
	void writeText(const std::string &text, float x, float y, float z, float height = 0.1f, float angle = 0.0f, float scale = 1.0f);
	void writeEdgePosition(double posx1, double posy1, double posx2, double posy2, int color = 200, float layer = 0.0);
	void writeNodePosition(const TImagePtr& img, int color = 100, double offset = 0.2, double scale = 0.03);
private:
	TSplinePtr _spline;
};
DECLARE_ASSISTANCES(DxfWriter, DxfWtr)

/**  
  *  @class  <StepWriter> 
  *  @brief  Base class of the writers 
  *  @note  
  *  StepWriter generates the STEP file.
*/
class StepWriter : public TWriter
{
public:
	StepWriter(const std::string &file_name, const TGroupPtr &objects);
	virtual ~StepWriter();
public:
	/** Write the T-spline data into a STEP file. */
	void writeStep();

protected:
	void allocateStepIds();
	void writeTVertex(const TVertexPtr &vertex);
	void writeTEdge(const TEdgePtr &edge);
	void writeTLink(const TLinkPtr &link);
	void writeTFace(const TFacePtr &face);
	void writeTEdgeCondition(const TEdgeConditionPtr &edge_condition);
	void writeTNodeV4(const TNodeV4Ptr &node_v4);
	void writeTPoint(const TPointPtr &point);
	void writeTImage(const TImagePtr &image);
	void writeTConnect(const TConnectPtr &node_grid);
	void writeTPointset(const TPointsetPtr &point_grid);
	void writeTSpline(const TSplinePtr &spline);
private:
	TGroupPtr _objects;
};
DECLARE_ASSISTANCES(StepWriter, StpWtr);


/**
*  @class  <GnuplotWriter>
*  @brief  Base class of the writers
*  @note
*  GnuplotWriter generates the GNUplot files.
*/

class GnuplotWriter : public TriMeshWriter
{
public:
	GnuplotWriter(const std::string &file_name, const TriMeshPtr &tri_mesh, const TSplinePtr &spline);
	virtual ~GnuplotWriter();
public:
	/** Write the Gpl mesh file. */
	void writeGnuplMesh();
	/** Write the Gpl T-image file. */
	void writeGnuplTImage();
	/** Write the Gpl T-connect file. */
	void writeGnuplTConnect();
	/** Write the Gpl T-pointset file. */
	void writeGnuplTPointset();
protected:
	void writeEdge(const TEdgePtr &edge);
	void writeText(const std::string &text, float x, float y, float z);
	void writeEdgePosition(double posx1, double posy1, double posx2, double posy2);
	void writeNodePosition(const TImagePtr& img, double offset = 0.2);
	void writeTextPosition(const TImagePtr& img, double offset = 0.25, double view_offset = 0.05);
	void writeLine(const TPointPtr &start, const TPointPtr &end);
	void writeVertex(const TVertexPtr &vertex, double view_offset = 0.05);
	
private:
	TSplinePtr _spline;
};
DECLARE_ASSISTANCES(GnuplotWriter, GptWtr);



#ifdef use_namespace
}// namespace TSPLINE
#endif


#endif
