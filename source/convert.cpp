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
   - xxxxx.
-------------------------------------------------------------------------------
*/

/*! 
  @file demo.cpp
  @brief A demo file.

  Demos for T-spline, etc.
*/


#include <tspline.h>
#include <factory.h>
#include <editor.h>
#include <tessellator.h>
#include <writer.h>
#include <rhbuilder.h>
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

#ifdef use_namespace
using namespace TSPLINE;
#endif

std::vector<std::string>& operator<<(std::vector<std::string> &container, const std::string &value);
void writeObj(std::vector<TriMeshPtr> trimesh, std::string filename);
void writeObj(TriMeshPtr trimesh, std::string filename);
void writeSTLAscii(std::vector<TriMeshPtr> trimesh, std::string filename);
void writeSTLAscii(TriMeshPtr trimesh, std::string filename);
void writeSTLBinary(std::vector<TriMeshPtr> trimesh, std::string filename);
void writeSTLBinary(TriMeshPtr trimesh, std::string filename);
void writeTImage(RhBuilderPtr reader, std::string filename);
void writeTPointSet(RhBuilderPtr reader, std::string filename);
void writeSTEP(RhBuilderPtr reader, std::string filename);

int main(int argc, char **argv)
{
   cout << "=====================================================\n";
   cout << " TSPLINE -- A T-spline object oriented package in C++ \n";
   cout << " DEMO program \n";
   cout << "=====================================================\n";
   cout << "usage: convert.exe [*.tsm] [option] [flag]\n";
   cout << "-[option]: obj, stla, stlb, timage, tpointset, step\n";
   cout << "-[flag]: the flag is useful only for obj, stla and stlb.\n-[1]write meshes to one file; [0](default),write meshes to multi files.\n";
   cout << "=====================================================\n";
   cout << "\n";
   
   
   std::string option;
   int flag = 0;
   if(argc<3)
   {
	   cout<<"Please read the usage."<<endl;
	   return 0;
   }
   option = argv[2];
   if(argc>3)
   {
	   flag = atoi(argv[3]);
   }
   std::transform(option.begin(),option.end(),option.begin(),::tolower);
   std::vector<std::string> optionlist;
   optionlist << "obj" << "stla" << "stlb" << "timage" << "tpointset" << "step" << "all";
   if(find(optionlist.begin(),optionlist.end(),option) == optionlist.end())
   {
	   cout<<"Please read the usage."<<endl;
	   return 0;
   }

   std::string slash;
#ifdef _WIN32
   slash = "\\";
#else
   slash = "/";
#endif
   std::string filename(argv[1]);
   int pos = filename.find_last_of(slash);
   std::string splinename(filename.substr(pos+1));
   int i = splinename.find('.');
   splinename = splinename.substr(0,i);
   std::string pathname(filename.substr(0,pos+1));
   std::string dirname = pathname + splinename;

   RhBuilderPtr reader = makePtr<RhBuilder>(filename);
   TSplinePtr spline = reader->findTSpline();
   
   TTessellator tessellator(spline);
   tessellator.setResolution(0.05);
   TriMeshPtr trimesh = tessellator.interpolateAll();
   std::vector<TriMeshPtr> trimesh2;
   std::vector<std::string> faces;
   reader->findTFaceNames(faces);
   for (int i=0;i<faces.size();i++)
   {
	   TriMeshPtr trimesh = tessellator.interpolateFace(faces[i]);
	   trimesh2.push_back(trimesh);
   }

#ifdef _WIN32
   _mkdir(dirname.c_str());
#else
   mkdir(dirname.c_str());
#endif
   
   if(option == "obj")
   {
	   if(flag == 1)
	   {
		   writeObj(trimesh,dirname + slash + splinename);
	   }
	   else
	   {
		   writeObj(trimesh2,dirname + slash + splinename);
	   }  
   }
   else if(option == "stla")
   {
	   if(flag == 1)
	   {
		   writeSTLAscii(trimesh,dirname + slash + splinename);
	   }
	   else
	   {
		   writeSTLAscii(trimesh2,dirname + slash + splinename);
	   }
   }
   else if(option == "stlb")
   {
	   if(flag == 1)
	   {
		   writeSTLBinary(trimesh,dirname + slash + splinename);
	   }
	   else
	   {
		   writeSTLBinary(trimesh2,dirname + slash + splinename);
	   }
   }
   else if(option == "timage")
   {
	   writeTImage(reader, dirname + slash + splinename);
   }
   else if(option == "tpointset")
   {
	   writeTPointSet(reader, dirname + slash + splinename);
   }
   else if(option == "step")
   {
	   writeSTEP(reader, dirname + slash + splinename);
   }
   else if(option == "all")
   {
	   writeObj(trimesh,dirname + slash + splinename);
	   writeSTLAscii(trimesh,dirname + slash + splinename);
	   writeSTLBinary(trimesh2,dirname + slash + splinename);
	   writeTImage(reader, dirname + slash + splinename);
	   writeTPointSet(reader, dirname + slash + splinename);
	   writeSTEP(reader, dirname + slash + splinename);
   }
   else
   {
	   cout<<"Please read the usage."<<endl;
   }
   return(0);
}

std::vector<std::string>& operator<<(std::vector<std::string> &container, const std::string &value)
{
	container.push_back(value);
	return container;
}

void writeObj(std::vector<TriMeshPtr> trimesh, std::string filename)
{
	ObjWriter objwriter(filename, 0);
	for (std::vector<TriMeshPtr>::iterator it = trimesh.begin(); it!=trimesh.end();it++)
	{
		objwriter.addMesh(*it);
	}

	objwriter.writeObj();
	cout << "OBJ file: " << objwriter.fileName() << " is written!" <<  endl;
}

void writeObj(TriMeshPtr trimesh, std::string filename)
{
	ObjWriter objwriter(filename, trimesh);
	objwriter.writeObj();
	cout << "OBJ file: " << objwriter.fileName() << " is written!" <<  endl;
}

void writeSTLAscii(std::vector<TriMeshPtr> trimesh, std::string filename)
{
	int i=0;
	for (std::vector<TriMeshPtr>::iterator it = trimesh.begin(); it!=trimesh.end();i++,it++)
	{
		std::stringstream ss;
		std::string str;
		ss<<i;
		ss>>str;
		StlWriter stlwriter(filename + "-" + str, *it);
		stlwriter.writeStlAcii();
		cout << "STL file: " << stlwriter.fileName() << " is written!" <<  endl;
	}
}

void writeSTLAscii(TriMeshPtr trimesh, std::string filename)
{
	StlWriter stlwriter(filename, trimesh);
	stlwriter.writeStlAcii();
	cout << "STL file: " << stlwriter.fileName() << " is written!" <<  endl;
}

void writeSTLBinary(std::vector<TriMeshPtr> trimesh, std::string filename)
{
	int i=0;
	for (std::vector<TriMeshPtr>::iterator it = trimesh.begin(); it!=trimesh.end();i++,it++)
	{
		std::stringstream ss;
		std::string str;
		ss<<i;
		ss>>str;
		StlWriter stlwriter(filename + "-" + str, *it);
		stlwriter.writeStlBinary();
		cout << "STL file: " << stlwriter.fileName() << " is written!" <<  endl;
	}
}

void writeSTLBinary(TriMeshPtr trimesh, std::string filename)
{
	StlWriter stlwriter(filename, trimesh);
	stlwriter.writeStlBinary();
	cout << "STL file: " << stlwriter.fileName() << " is written!" <<  endl;
}

void writeTImage(RhBuilderPtr reader, std::string filename)
{
	DxfWriter dxfwriter(filename, reader->findTSpline());
	   dxfwriter.writeDxfTImage();
	   cout << "TImage file: " << dxfwriter.fileName() << " is written!" <<  endl;
}

void writeTPointSet(RhBuilderPtr reader, std::string filename)
{
	DxfWriter dxfwriter(filename, reader->findTSpline());
	   dxfwriter.writeDxfTPointset();
	   cout << "TPointSet file: " << dxfwriter.fileName() << " is written!" <<  endl;
}

void writeSTEP(RhBuilderPtr reader, std::string filename)
{
	StepWriter stepwriter(filename, reader->findTGroup());
	   stepwriter.writeStep();
	   cout << "STEP file: " << stepwriter.fileName() << " is written!" <<  endl;
}