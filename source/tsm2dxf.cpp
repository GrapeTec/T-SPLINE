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
- Create.
2016/04/10: Yazui Liu
- Implemented.
-------------------------------------------------------------------------------
*/

/*! 
	@file tsm2dxf.cpp
	@brief Import tsm file and export T-image, T-connect and T-pointset file.
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
#include <sys/types.h>
#include <sys/stat.h>
#endif

#ifdef use_namespace
using namespace TSPLINE;
#endif

int main(int argc, char **argv)
{
	cout << "=====================================================\n";
	cout << " TSPLINE -- A T-spline object oriented package in C++ \n";
	cout << " Usage: tsm2dxf.exe [*.tsm] [-img/-cnt/-pst]\n";
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

   RhBuilderPtr reader = makePtr<RhBuilder>(filename);
   TSplinePtr spline = reader->findTSpline();

   if(option == "-img")
   {
	   DxfWriter dxfwriter(dirname + "/" + splinename, spline);
	   dxfwriter.writeDxfTImage();
	   cout << "DXF file, T-image: " << dxfwriter.fileName() << " is written!" <<  endl;
   }
   else if(option == "-cnt")
   {
	   DxfWriter dxfwriter(dirname + "/" + splinename, spline);
	   dxfwriter.writeDxfTConnect();
	   cout << "DXF file, T-image: " << dxfwriter.fileName() << " is written!" <<  endl;
   }
   else if(option == "-pst")
   {
	   DxfWriter dxfwriter(dirname + "/" + splinename, spline);
	   dxfwriter.writeDxfTPointset();
	   cout << "DXF file, T-pointset: " << dxfwriter.fileName() << " is written!" <<  endl;
   }
   else
   {
	   cout << "Do not support the option." << endl;
   }

   return(0);
}
