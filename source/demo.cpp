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
-------------------------------------------------------------------------------
*/

/*!
@file demo.cpp
@brief A demo file.

Demos for T-spline, etc.
*/

#include "mouse.h"
#include "simple.h"
#include <tspline.h>
#include <factory.h>
#include <tessellator.h>
#include <writer.h>

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#endif

#ifdef use_namespace
using namespace TSPLINE;
#endif

int main(void)
{
	cout << "=====================================================\n";
	cout << " TSPLINE -- A T-spline object oriented package in C++ \n";
	cout << " DEMO program \n";
	cout << "=====================================================\n";
	cout << "\n";

	//SimpleDemoPtr demo = makePtr<SimpleDemo>();
	MouseDemoPtr demo = makePtr<MouseDemo>();
	TSplinePtr spline = demo->findTSpline();
	std::string splinename = spline->getName();

	TTessellator tessellator(spline);
	tessellator.setChordalError(0.3);

	TriMeshPtr trimesh = tessellator.interpolateAll();

	std::string dirname = "../export/" + splinename;

#ifdef _WIN32
	_mkdir(dirname.c_str());
#elif __linux__
	dirname = "./export/" + splinename;
	const int dir_err = mkdir(dirname.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#elif defined __APPLE__
	dirname = "./export/" + splinename;
	mkdir(dirname.c_str(), 0744);
#endif 

	StlWriter stlwriter(dirname + "/" + splinename, trimesh);
	stlwriter.writeStlAcii();
	cout << "STL file: " << stlwriter.fileName() << " is written!" << endl;

	ObjWriter objwriter(dirname + "/" + splinename, 0);
	std::vector<std::string> faces;
	demo->findTFaceNames(faces);
	for (int i = 0; i<faces.size(); i++)
	{
		TriMeshPtr trimesh = tessellator.interpolateFace(faces[i]);
		objwriter.addMesh(trimesh);
		StlWriter stlwriter(dirname + "/" + splinename + "-" + faces[i], trimesh);
		stlwriter.writeStlBinary();
		cout << "STL file: " << stlwriter.fileName() << " is written!" << endl;
	}

	objwriter.writeObj();
	cout << "OBJ file: " << objwriter.fileName() << " is written!" << endl;

	DxfWriter dxfwriter(dirname + "/" + splinename, spline);
	dxfwriter.writeDxfTPointset();
	dxfwriter.writeDxfTConnect();
	dxfwriter.writeDxfTImage();
	cout << "DXF file: " << dxfwriter.fileName() << " is written!" << endl;

	StepWriter stepwriter(dirname + "/" + splinename, demo->findTGroup());
	stepwriter.writeStep();
	cout << "STEP file: " << stepwriter.fileName() << " is written!" << endl;

	GnuplotWriter gplwriter(dirname + "/" + splinename, trimesh, spline);
	gplwriter.writeGnuplMesh();
	gplwriter.writeGnuplTImage();
	gplwriter.writeGnuplTConnect();
	gplwriter.writeGnuplTPointset();
	cout << "GNUpl files: " << gplwriter.fileName() << " is written!" << endl;

	return(0);
}

std::vector<std::string>& operator<<(std::vector<std::string> &container, const std::string &value)
{
	container.push_back(value);
	return container;
}
