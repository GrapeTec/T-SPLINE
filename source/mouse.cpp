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
Beihang University (Beijing University of Aeronautics and Astronautics)
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

#include "mouse.h"

#ifdef use_namespace
using namespace TSPLINE;
#endif

extern std::vector<std::string>& operator<<(std::vector<std::string> &container, const std::string &value);

MouseDemo::MouseDemo()
{
	_factory = makePtr<TFactory>();
	createMouse();
}

void MouseDemo::createMouse()
{
	createTSpline();
	createTImage();
	createTConnect();
	createTPointset();
	createTVertices();
	createTEdges();
 	createTLinks();
	createTEdgeConditions();
	createTFaces();
	createTNodes();
	createTPoints();

	patchTSpline();
	patchTImage();
	patchTConnect();
	patchTPointset();
	patchTEdges();
	patchTLinks();
	patchTEdgeConditions();
	patchTFaces();
	patchTVertices();
	patchTNodes();
	patchTPoints();

	prepareTObjects();
}

void MouseDemo::createTSpline()
{
	_factory->createTSpline("mouse");
}

void MouseDemo::createTImage()
{
	_factory->createTImage("image");
}

void MouseDemo::createTConnect()
{
	_factory->createTConnect("nodes");
}

void MouseDemo::createTPointset()
{
	_factory->createTPointset("points");
}

void MouseDemo::createTVertices()
{
	_factory->createTVertex("v0", 3.0, 0.0); // v
	_factory->createTVertex("v1", 4.0, 0.0); // v
	_factory->createTVertex("v2", 4.0, 1.0); // v
	_factory->createTVertex("v3", 3.0, 1.0); // v
	_factory->createTVertex("v4", 2.0, 2.0); // v
	_factory->createTVertex("v5", 2.0, 1.0); // v
	_factory->createTVertex("v6", 3.0, 2.0); // v
	_factory->createTVertex("v7", 4.0, 2.0); // v
	_factory->createTVertex("v8", 4.0, 1.5); // v
	_factory->createTVertex("v9", 3.0, 1.5); // v
	_factory->createTVertex("v10", 2.0, 1.5); // v
	_factory->createTVertex("v12", 3.5, 0.0); // v
	_factory->createTVertex("v13", 1.0, 0.0); // v
	_factory->createTVertex("v14", 0.0, 0.0); // v
	_factory->createTVertex("v15", 0.0, 1.0); // v
	_factory->createTVertex("v16", 1.0, 1.0); // v
	_factory->createTVertex("v17", 3.0, 0.5); // v
	_factory->createTVertex("v18", 1.0, 0.5); // v
	_factory->createTVertex("v19", 1.0, 2.0); // v
	_factory->createTVertex("v20", 0.0, 2.0); // v
	_factory->createTVertex("v21", 0.0, 1.5); // v
	_factory->createTVertex("v22", 1.0, 1.5); // v
	_factory->createTVertex("v23", 3.5, 0.5); // v
	_factory->createTVertex("v25", 0.5, 0.0); // v
	_factory->createTVertex("v26", 0.5, 0.5); // v
	_factory->createTVertex("v27", 4.0, 0.5); // v
	_factory->createTVertex("v28", 0.0, 0.5); // v
}

void MouseDemo::createTEdges() // v
{
	_factory->createTEdge("e0");
	_factory->createTEdge("e1"); 
	_factory->createTEdge("e2");
	_factory->createTEdge("e3");
	_factory->createTEdge("e4");
	_factory->createTEdge("e5");
	_factory->createTEdge("e6");
	_factory->createTEdge("e7");
	_factory->createTEdge("e8");
	_factory->createTEdge("e9");
	_factory->createTEdge("e10");
	_factory->createTEdge("e12");
	_factory->createTEdge("e13");
	_factory->createTEdge("e14");
	_factory->createTEdge("e15");
	_factory->createTEdge("e17");
	_factory->createTEdge("e18");
	_factory->createTEdge("e19");
	_factory->createTEdge("e20");
	_factory->createTEdge("e21");
	_factory->createTEdge("e22");
	_factory->createTEdge("e23");
	_factory->createTEdge("e24");
	_factory->createTEdge("e25");
	_factory->createTEdge("e26");
	_factory->createTEdge("e27");
	_factory->createTEdge("e29");
	_factory->createTEdge("e30");
	_factory->createTEdge("e31");
	_factory->createTEdge("e32");
	_factory->createTEdge("e33");
	_factory->createTEdge("e34");
	_factory->createTEdge("e36");
	_factory->createTEdge("e37");
	_factory->createTEdge("e38");
	_factory->createTEdge("e39");
	_factory->createTEdge("e40");
	_factory->createTEdge("e41");
}

void MouseDemo::createTLinks() // v
{
	_factory->createTLink("l0");
	_factory->createTLink("l2");
	_factory->createTLink("l3");
	_factory->createTLink("l1");
	_factory->createTLink("l4");
	_factory->createTLink("l5");
	_factory->createTLink("l6");
	_factory->createTLink("l7");
	_factory->createTLink("l8");
	_factory->createTLink("l9");
	_factory->createTLink("l11");
	_factory->createTLink("l12");
	_factory->createTLink("l13");
	_factory->createTLink("l14");
	_factory->createTLink("l15");
	_factory->createTLink("l16");
	_factory->createTLink("l17");
	_factory->createTLink("l18");
	_factory->createTLink("l19");
	_factory->createTLink("l20");
	_factory->createTLink("l21");
	_factory->createTLink("l23");
	_factory->createTLink("l24");
	_factory->createTLink("l25");
	_factory->createTLink("l26");
	_factory->createTLink("l27");
	_factory->createTLink("l28");
	_factory->createTLink("l29");
	_factory->createTLink("l30");
	_factory->createTLink("l31");
	_factory->createTLink("l34");
	_factory->createTLink("l35");
	_factory->createTLink("l36");
	_factory->createTLink("l37");
	_factory->createTLink("l38");
	_factory->createTLink("l39");
	_factory->createTLink("l40");
	_factory->createTLink("l41");
	_factory->createTLink("l42");
	_factory->createTLink("l43");
	_factory->createTLink("l45");
	_factory->createTLink("l46");
	_factory->createTLink("l47");
	_factory->createTLink("l48");
	_factory->createTLink("l49");
	_factory->createTLink("l50");
	_factory->createTLink("l51");
	_factory->createTLink("l52");
	_factory->createTLink("l53");
	_factory->createTLink("l54");
	_factory->createTLink("l55");
	_factory->createTLink("l56");
	_factory->createTLink("l57");
	_factory->createTLink("l58");
	_factory->createTLink("l59");
	_factory->createTLink("l60");
	_factory->createTLink("l61");
	_factory->createTLink("l62");
	_factory->createTLink("l63");
	_factory->createTLink("l64");
	_factory->createTLink("l65");
	_factory->createTLink("l66");
	_factory->createTLink("l68");
	_factory->createTLink("l69");
	_factory->createTLink("l72");
	_factory->createTLink("l73");
	_factory->createTLink("l74");
	_factory->createTLink("l75");
	_factory->createTLink("l76");
	_factory->createTLink("l77");
	_factory->createTLink("l78");
	_factory->createTLink("l79");
	_factory->createTLink("l80");
	_factory->createTLink("l81");
	_factory->createTLink("l82");
	_factory->createTLink("l83");
}

void MouseDemo::createTEdgeConditions() // v
{
	_factory->createTEdgeCondition("ec0");
	_factory->createTEdgeCondition("ec1");
	_factory->createTEdgeCondition("ec2");
	_factory->createTEdgeCondition("ec3");
	_factory->createTEdgeCondition("ec4");
	_factory->createTEdgeCondition("ec5");
	_factory->createTEdgeCondition("ec6");
	_factory->createTEdgeCondition("ec7");
	_factory->createTEdgeCondition("ec8");
	_factory->createTEdgeCondition("ec9");
	_factory->createTEdgeCondition("ec10");
	_factory->createTEdgeCondition("ec11");
	_factory->createTEdgeCondition("ec12");
	_factory->createTEdgeCondition("ec13");
	_factory->createTEdgeCondition("ec14");
	_factory->createTEdgeCondition("ec15");
	_factory->createTEdgeCondition("ec16");
	_factory->createTEdgeCondition("ec17");
	_factory->createTEdgeCondition("ec18");
	_factory->createTEdgeCondition("ec19");
	_factory->createTEdgeCondition("ec20");
	_factory->createTEdgeCondition("ec21");
}

void MouseDemo::createTFaces() // v
{
	_factory->createTFace("f0");
	_factory->createTFace("f1");
	_factory->createTFace("f2");
	_factory->createTFace("f3");
	_factory->createTFace("f4");
	_factory->createTFace("f5");
	_factory->createTFace("f6");
	_factory->createTFace("f7");
	_factory->createTFace("f8");
	_factory->createTFace("f9");
	_factory->createTFace("f10");
	_factory->createTFace("f11");
}

void MouseDemo::createTNodes() // v
{
	_factory->createTNodeV4("n0-0"); // v
	_factory->createTNodeV4("n0-1");
	_factory->createTNodeV4("n0-2");
	_factory->createTNodeV4("n0-3");
	_factory->createTNodeV4("n1-0"); // v
	_factory->createTNodeV4("n1-1");
	_factory->createTNodeV4("n1-2");
	_factory->createTNodeV4("n1-3");
	_factory->createTNodeV4("n2-0"); // v
	_factory->createTNodeV4("n2-1"); 
	_factory->createTNodeV4("n3-0"); // v
	_factory->createTNodeV4("n3-1");
	_factory->createTNodeV4("n3-2");
	_factory->createTNodeV4("n3-3");
	_factory->createTNodeV4("n3-4");
	_factory->createTNodeV4("n3-5");
	_factory->createTNodeV4("n3-6");
	_factory->createTNodeV4("n3-7"); 
	_factory->createTNodeV4("n4-0"); // v
	_factory->createTNodeV4("n4-1");
	_factory->createTNodeV4("n5-0"); // v
	_factory->createTNodeV4("n5-1");
	_factory->createTNodeV4("n6-0"); // v
	_factory->createTNodeV4("n6-1");
	_factory->createTNodeV4("n7-0"); // v
	_factory->createTNodeV4("n7-1");
	_factory->createTNodeV4("n7-2");
	_factory->createTNodeV4("n7-3");
	_factory->createTNodeV4("n8-0"); // v
	_factory->createTNodeV4("n8-1");
	_factory->createTNodeV4("n9-0"); // v
	_factory->createTNodeV4("n10-0"); // v
	_factory->createTNodeV4("n12-0"); // v
	_factory->createTNodeV4("n12-1");
	_factory->createTNodeV4("n13-0"); // v
	_factory->createTNodeV4("n13-1");
	_factory->createTNodeV4("n13-2");
	_factory->createTNodeV4("n13-3");
	_factory->createTNodeV4("n14-0"); // v
	_factory->createTNodeV4("n14-1");
	_factory->createTNodeV4("n14-2");
	_factory->createTNodeV4("n14-3");
	_factory->createTNodeV4("n15-0"); // v
	_factory->createTNodeV4("n15-1");
	_factory->createTNodeV4("n16-0"); // v
	_factory->createTNodeV4("n16-1");
	_factory->createTNodeV4("n16-2");
	_factory->createTNodeV4("n16-3");
	_factory->createTNodeV4("n16-4");
	_factory->createTNodeV4("n16-5");
	_factory->createTNodeV4("n16-6");
	_factory->createTNodeV4("n16-7");
	_factory->createTNodeV4("n17-0"); // v
	_factory->createTNodeV4("n17-1");
	_factory->createTNodeV4("n18-0"); // v
	_factory->createTNodeV4("n18-1");
	_factory->createTNodeV4("n19-0"); // v
	_factory->createTNodeV4("n19-1");
	_factory->createTNodeV4("n20-0"); // v
	_factory->createTNodeV4("n20-1");
	_factory->createTNodeV4("n20-2");
	_factory->createTNodeV4("n20-3");
	_factory->createTNodeV4("n21-0"); // v
	_factory->createTNodeV4("n21-1");
	_factory->createTNodeV4("n22-0"); // v
	_factory->createTNodeV4("n23-0"); // v
	_factory->createTNodeV4("n25-0"); // v
	_factory->createTNodeV4("n25-1");
	_factory->createTNodeV4("n26-0"); // v
	_factory->createTNodeV4("n27-0"); // v
	_factory->createTNodeV4("n27-1");
	_factory->createTNodeV4("n28-0"); // v
	_factory->createTNodeV4("n28-1");
}

void MouseDemo::createTPoints()
{
	_factory->createTPoint("p0-0", 4.0, -93.0, -5.0, 1.0); // v
	_factory->createTPoint("p0-1", 8.0, -93.0, -6.0, 1.0); // v
	_factory->createTPoint("p0-2", 3.0, -98.0, -5.0, 1.0); // v
	_factory->createTPoint("p0-3", 7.0, -98.0, -7.0, 1.0); // v
	_factory->createTPoint("p1-0", 24.0, -90.0, -6.0, 1.0); // v
	_factory->createTPoint("p1-1", 28.0, -88.0, -5.0, 1.0); // v
	_factory->createTPoint("p1-2", 22.0, -94.0, -8.0, 1.0); // v
	_factory->createTPoint("p1-3", 25.0, -93.0, -8.0, 1.0); // v
	_factory->createTPoint("p2-0", 25.0, -62.0, 0.0, 1.0); // v
	_factory->createTPoint("p2-1", 35.0, -58.0, 0.0, 1.0); // v
	_factory->createTPoint("p3-0", 4.973, -61.0, 2.0, 1.0); // v
	_factory->createTPoint("p3-1", 8.453, -63.0, 3.0, 1.0); // v
	_factory->createTPoint("p3-2", 15.0, -61.0, 2.0, 1.0); // v
	_factory->createTPoint("p3-3", 5.006, -66.0, 1.896, 1.0); // v
	_factory->createTPoint("p3-4", 5.0, -70.0, 0.0, 1.0); // v
	_factory->createTPoint("p3-5", 15.0, -66.0, 0.0, 1.0); // v
	_factory->createTPoint("p3-6", 6.0, -74.0, -2.0, 1.0); // v
	_factory->createTPoint("p3-7", 16.0, -71.0, -1.0, 1.0); // v
	_factory->createTPoint("p4-0", 0.0, 0.0, 0.0, 1.0); // v
	_factory->createTPoint("p4-1", 0.0, -18.0, 3.0, 1.0); // v
	_factory->createTPoint("p5-0", 0.0, -57.0, 0.0, 1.0); // v
	_factory->createTPoint("p5-1", 0.0, -58.0, -1.044, 1.0); // v
	_factory->createTPoint("p6-0", 10.0, -3.0, -3.0, 1.0); // v
	_factory->createTPoint("p6-1", 12.0, -18.0, 2.0, 1.0); // v
	_factory->createTPoint("p7-0", 22.0, -11.0, -6.0, 1.0); // v
	_factory->createTPoint("p7-1", 28.0, -15.0, -8.0, 1.0); // v
	_factory->createTPoint("p7-2", 23.0, -23.0, -3.0, 1.0); // v
	_factory->createTPoint("p7-3", 29.0, -25.0, -5.0, 1.0); // v
	_factory->createTPoint("p8-0", 27.0, -47.0, 3.0, 1.0); // v
	_factory->createTPoint("p8-1", 33.0, -45.0, 0.0, 1.0); // v
	_factory->createTPoint("p9-0", 15.0, -50.0, 10.0, 1.0); // v
	_factory->createTPoint("p10-0", 0.0, -55.0, 10.0, 1.0); // v
	_factory->createTPoint("p12-0", 16.0, -93.0, -8.0, 1.0); // v
	_factory->createTPoint("p12-1", 15.0, -98.0, -10.0, 1.0); // v
	_factory->createTPoint("p13-0", -8.0, -93.0, -6.0, 1.0); // v
	_factory->createTPoint("p13-1", -4.0, -93.0, -5.0, 1.0); // v
	_factory->createTPoint("p13-2", -7.0, -98.0, -7.0, 1.0); // v
	_factory->createTPoint("p13-3", -3.0, -98.0, -5.0, 1.0); // v
	_factory->createTPoint("p14-0", -28.0, -88.0, -5.0, 1.0); // v
	_factory->createTPoint("p14-1", -24.0, -90.0, -6.0, 1.0); // v
	_factory->createTPoint("p14-2", -25.0, -93.0, -8.0, 1.0); // v
	_factory->createTPoint("p14-3", -22.0, -94.0, -8.0, 1.0); // v
	_factory->createTPoint("p15-0", -35.0, -58.0, 0.0, 1.0); // v
	_factory->createTPoint("p15-1", -25.0, -62.0, 0.0, 1.0); // v
	_factory->createTPoint("p16-0", -11.0, -61.0, 2.0, 1.0); // v
	_factory->createTPoint("p16-1", -8.453, -63.0, 3.0, 1.0); // v
	_factory->createTPoint("p16-2", -4.973, -61.0, 2.0, 1.0); // v
	_factory->createTPoint("p16-3", -15.0, -66.0, 0.0, 1.0); // v
	_factory->createTPoint("p16-4", -5.0, -70.0, 0.0, 1.0); // v
	_factory->createTPoint("p16-5", -5.006, -66.0, 1.896, 1.0); // v
	_factory->createTPoint("p16-6", -16.0, -71.0, -1.0, 1.0); // v
	_factory->createTPoint("p16-7", -6.0, -74.0, -2.0, 1.0); // v
	_factory->createTPoint("p17-0", 8.0, -83.0, -5.0, 1.0); // v
	_factory->createTPoint("p17-1", 11.0, -83.0, -5.0, 1.0); // v
	_factory->createTPoint("p18-0", -11.0, -83.0, -5.0, 1.0); // v
	_factory->createTPoint("p18-1", -8.0, -83.0, -5.0, 1.0); // v
	_factory->createTPoint("p19-0", -10.0, -3.0, -3.0, 1.0); // v
	_factory->createTPoint("p19-1", -12.0, -18.0, 2.0, 1.0); // v
	_factory->createTPoint("p20-0", -28.0, -15.0, -8.0, 1.0); // v
	_factory->createTPoint("p20-1", -22.0, -11.0, -6.0, 1.0); // v
	_factory->createTPoint("p20-2", -29.0, -25.0, -5.0, 1.0); // v
	_factory->createTPoint("p20-3", -23.0, -23.0, -3.0, 1.0); // v
	_factory->createTPoint("p21-0", -33.0, -45.0, 0.0, 1.0); // v
	_factory->createTPoint("p21-1", -27.0, -47.0, 3.0, 1.0); // v
	_factory->createTPoint("p22-0", -15.0, -50.0, 10.0, 1.0); // v
	_factory->createTPoint("p23-0", 18.0, -83.0, -5.0, 1.0); // v
	_factory->createTPoint("p25-0", -16.0, -93.0, -8.0, 1.0); // v
	_factory->createTPoint("p25-1", -15.0, -98.0, -10.0, 1.0); // v
	_factory->createTPoint("p26-0", -18.0, -83.0, -5.0, 1.0); // v
	_factory->createTPoint("p27-0", 29.0, -81.0, -2.0, 1.0); // v
	_factory->createTPoint("p27-1", 35.0, -80.0, 0.0, 1.0); // v
	_factory->createTPoint("p28-0", -35.0, -80.0, 0.0, 1.0); // v
	_factory->createTPoint("p28-1", -29.0, -81.0, -2.0, 1.0); // v
}

void MouseDemo::patchTVertices()
{
	_factory->patchTVertexByVertices("v20", "", "", "v21", "v19"); // v
	_factory->patchTVertexByVertices("v19", "", "v20", "v22", "v4"); // v
	_factory->patchTVertexByVertices("v4", "", "v19", "v10", "v6"); // v
	_factory->patchTVertexByVertices("v6", "", "v4", "v9", "v7"); // v
	_factory->patchTVertexByVertices("v7", "", "v6", "v8", ""); // v
	_factory->patchTVertexByVertices("v21", "v20", "", "v15", "v22"); // v
	_factory->patchTVertexByVertices("v22", "v19", "v21", "", "v10"); // v
	_factory->patchTVertexByVertices("v10", "v4", "v22", "v5", "v9"); // v
	_factory->patchTVertexByVertices("v9", "v6", "v10", "", "v8"); // v
	_factory->patchTVertexByVertices("v8", "v7", "v9", "v2", ""); // v
	_factory->patchTVertexByVertices("v15", "v21", "", "v28", "v16"); // v
	_factory->patchTVertexByVertices("v16", "", "v15", "v18", "v5"); // v
	_factory->patchTVertexByVertices("v5", "v10", "v16", "", "v3"); // v
	_factory->patchTVertexByVertices("v3", "", "v5", "v17", "v2"); // v
	_factory->patchTVertexByVertices("v2", "v8", "v3", "v27", ""); // v
	_factory->patchTVertexByVertices("v28", "v15", "", "v14", "v26"); // v
	_factory->patchTVertexByVertices("v26", "", "v28", "v25", "v18"); // v 
	_factory->patchTVertexByVertices("v18", "v16", "v26", "v13", ""); // v
	_factory->patchTVertexByVertices("v17", "v3", "", "v0", "v23"); // v
	_factory->patchTVertexByVertices("v23", "", "v17", "v12", "v27"); // v
	_factory->patchTVertexByVertices("v27", "v2", "v23", "v1", ""); // v
	_factory->patchTVertexByVertices("v14", "v28", "", "", "v25"); // v
	_factory->patchTVertexByVertices("v25", "v26", "v14", "", "v13"); // v
	_factory->patchTVertexByVertices("v13", "v18", "v25", "", ""); // v
	_factory->patchTVertexByVertices("v0", "v17", "", "", "v12"); // v
	_factory->patchTVertexByVertices("v12", "v23", "v0", "", "v1"); // v
	_factory->patchTVertexByVertices("v1", "v27", "v12", "", ""); // v
}

void MouseDemo::patchTEdges()
{
	_factory->patchTEdge("e23", "v20", "v19", "", "f8"); // v
	_factory->patchTEdge("e21", "v19", "v4", "", "f7"); // v
	_factory->patchTEdge("e4", "v4", "v6", "", "f2"); // v
	_factory->patchTEdge("e6", "v6", "v7", "", "f3"); // v
	_factory->patchTEdge("e27", "v20", "v21", "f8", ""); // v
	_factory->patchTEdge("e22", "v19", "v22", "f7", "f8"); // v
	_factory->patchTEdge("e8", "v4", "v10", "f2", "f7"); // v
	_factory->patchTEdge("e5", "v6", "v9", "f3", "f2"); // v
	_factory->patchTEdge("e10", "v7", "v8", "", "f3"); // v
	_factory->patchTEdge("e29", "v21", "v22", "f8", "f6"); // v
	_factory->patchTEdge("e31", "v22", "v10", "f7", "f6"); // v
	_factory->patchTEdge("e14", "v10", "v9", "f2", "f1"); // v
	_factory->patchTEdge("e12", "v9", "v8", "f3", "f1"); // v
	_factory->patchTEdge("e24", "v21", "v15", "f6", ""); // v
	_factory->patchTEdge("e13", "v10", "v5", "f1", "f6"); // v
	_factory->patchTEdge("e7", "v8", "v2", "", "f1"); // v
	_factory->patchTEdge("e19", "v15", "v16", "f6", "f11"); // v
	_factory->patchTEdge("e26", "v16", "v5", "f6", ""); // v
	_factory->patchTEdge("e9", "v5", "v3", "f1", ""); // v
	_factory->patchTEdge("e2", "v3", "v2", "f1", "f10"); // v
	_factory->patchTEdge("e18", "v15", "v28", "f11", ""); // v 
	_factory->patchTEdge("e30", "v16", "v18", "", "f11"); // v
	_factory->patchTEdge("e3", "v3", "v17", "f10", ""); // v
	_factory->patchTEdge("e38", "v2", "v27", "", "f10"); // v
	_factory->patchTEdge("e41", "v28", "v26", "f11", "f9"); // v
	_factory->patchTEdge("e37", "v26", "v18", "f11", "f5"); // v
	_factory->patchTEdge("e36", "v17", "v23", "f10", "f0"); // v
	_factory->patchTEdge("e40", "v23", "v27", "f10", "f4"); // v
	_factory->patchTEdge("e39", "v28", "v14", "f9", ""); // v
	_factory->patchTEdge("e33", "v26", "v25", "f5", "f9"); // v
	_factory->patchTEdge("e20", "v18", "v13", "", "f5"); // v
	_factory->patchTEdge("e25", "v17", "v0", "f0", ""); // v
	_factory->patchTEdge("e34", "v23", "v12", "f4", "f0"); // v
	_factory->patchTEdge("e1", "v27", "v1", "", "f4"); // v
	_factory->patchTEdge("e32", "v14", "v25", "f9", ""); // v
	_factory->patchTEdge("e17", "v25", "v13", "f5", ""); // v
	_factory->patchTEdge("e0", "v0", "v12", "f0", ""); // v
	_factory->patchTEdge("e15", "v12", "v1", "f4", ""); // v
}

void MouseDemo::patchTLinks()
{
	_factory->patchTLink("l55", "e23", true); // v
	_factory->patchTLink("l46", "e23", false); // v
	_factory->patchTLink("l45", "e21", true); // v
	_factory->patchTLink("l50", "e21", false); // v
	_factory->patchTLink("l15", "e4", true); // v
	_factory->patchTLink("l5", "e4", false); // v
	_factory->patchTLink("l11", "e6", true); // v
	_factory->patchTLink("l14", "e6", false); // v
	_factory->patchTLink("l48", "e27", true); // v
	_factory->patchTLink("l47", "e27", false); // v
	_factory->patchTLink("l39", "e22", true); // v
	_factory->patchTLink("l59", "e22", false); // v
	_factory->patchTLink("l16", "e8", true); // v
	_factory->patchTLink("l62", "e8", false); // v
	_factory->patchTLink("l12", "e5", true); // v
	_factory->patchTLink("l20", "e5", false); // v
	_factory->patchTLink("l21", "e10", true); // v
	_factory->patchTLink("l9", "e10", false); // v
	_factory->patchTLink("l43", "e29", true); // v
	_factory->patchTLink("l63", "e29", false); // v
	_factory->patchTLink("l54", "e31", true); // v
	_factory->patchTLink("l60", "e31", false); // v
	_factory->patchTLink("l28", "e14", true); // v
	_factory->patchTLink("l29", "e14", false); // v
	_factory->patchTLink("l25", "e12", true); // v
	_factory->patchTLink("l24", "e12", false); // v
	_factory->patchTLink("l58", "e24", true); // v
	_factory->patchTLink("l37", "e24", false); // v
	_factory->patchTLink("l26", "e13", true); // v
	_factory->patchTLink("l52", "e13", false); // v
	_factory->patchTLink("l13", "e7", true); // v
	_factory->patchTLink("l8", "e7", false); // v
	_factory->patchTLink("l42", "e19", true); // v
	_factory->patchTLink("l40", "e19", false); // v
	_factory->patchTLink("l57", "e26", true); // v
	_factory->patchTLink("l61", "e26", false); // v
	_factory->patchTLink("l18", "e9", true); // v
	_factory->patchTLink("l19", "e9", false); // v
	_factory->patchTLink("l23", "e2", true); // v
	_factory->patchTLink("l4", "e2", false); // v
	_factory->patchTLink("l38", "e18", true); // v
	_factory->patchTLink("l65", "e18", false); // v
	_factory->patchTLink("l51", "e30", true); // v
	_factory->patchTLink("l49", "e30", false); // v
	_factory->patchTLink("l6", "e3", true); // v
	_factory->patchTLink("l7", "e3", false); // v
	_factory->patchTLink("l77", "e38", true); // v
	_factory->patchTLink("l76", "e38", false); // v
	_factory->patchTLink("l83", "e41", true); // v
	_factory->patchTLink("l82", "e41", false); // v
	_factory->patchTLink("l75", "e37", true); // v
	_factory->patchTLink("l74", "e37", false); // v
	_factory->patchTLink("l73", "e36", true); // v
	_factory->patchTLink("l72", "e36", false); // v
	_factory->patchTLink("l81", "e40", true); // v
	_factory->patchTLink("l80", "e40", false); // v
	_factory->patchTLink("l78", "e39", true); // v
	_factory->patchTLink("l79", "e39", false); // v
	_factory->patchTLink("l56", "e33", true); // v
	_factory->patchTLink("l64", "e33", false); // v
	_factory->patchTLink("l53", "e20", true); // v
	_factory->patchTLink("l34", "e20", false); // v
	_factory->patchTLink("l17", "e25", true); // v
	_factory->patchTLink("l27", "e25", false); // v
	_factory->patchTLink("l68", "e34", true); // v
	_factory->patchTLink("l69", "e34", false); // v
	_factory->patchTLink("l3", "e1", true); // v
	_factory->patchTLink("l2", "e1", false); // v
	_factory->patchTLink("l36", "e32", true); // v
	_factory->patchTLink("l35", "e32", false); // v
	_factory->patchTLink("l66", "e17", true); // v
	_factory->patchTLink("l41", "e17", false); // v
	_factory->patchTLink("l0", "e0", true); // v
	_factory->patchTLink("l1", "e0", false); // v
	_factory->patchTLink("l30", "e15", true); // v
	_factory->patchTLink("l31", "e15", false); // v
}

void MouseDemo::patchTEdgeConditions() // v
{
	/*
	_factory->patchTEdgeCondition("ec0", "e0", true);
	_factory->patchTEdgeCondition("ec1", "e15", true);
	_factory->patchTEdgeCondition("ec2", "e1", true);
	_factory->patchTEdgeCondition("ec3", "e38", true);
	_factory->patchTEdgeCondition("ec4", "e7", true);
	_factory->patchTEdgeCondition("ec5", "e10", true);
	_factory->patchTEdgeCondition("ec6", "e6", true);
	_factory->patchTEdgeCondition("ec7", "e4", true);
	_factory->patchTEdgeCondition("ec8", "e21", true);
	_factory->patchTEdgeCondition("ec9", "e23", true);
	_factory->patchTEdgeCondition("ec10", "e27", true);
	_factory->patchTEdgeCondition("ec11", "e24", true);
	_factory->patchTEdgeCondition("ec12", "e18", true);
	_factory->patchTEdgeCondition("ec13", "e39", true);
	_factory->patchTEdgeCondition("ec14", "e32", true);
	_factory->patchTEdgeCondition("ec15", "e17", true);
	_factory->patchTEdgeCondition("ec16", "e20", true);
	_factory->patchTEdgeCondition("ec17", "e30", true);
	_factory->patchTEdgeCondition("ec18", "e26", true);
	_factory->patchTEdgeCondition("ec19", "e9", true);
	_factory->patchTEdgeCondition("ec20", "e3", true);
	_factory->patchTEdgeCondition("ec21", "e25", true);*/
	_factory->patchTEdgeCondition("ec2", "e0", true);
	_factory->patchTEdgeCondition("ec1", "e15", true);
	_factory->patchTEdgeCondition("ec2", "e1", true);
	_factory->patchTEdgeCondition("ec3", "e38", true);
	_factory->patchTEdgeCondition("ec4", "e7", true);
	_factory->patchTEdgeCondition("ec5", "e4", true);
	_factory->patchTEdgeCondition("ec6", "e6", true);
	_factory->patchTEdgeCondition("ec7", "e10", true);
	_factory->patchTEdgeCondition("ec8", "e21", true);
	_factory->patchTEdgeCondition("ec9", "e23", true);
	_factory->patchTEdgeCondition("ec10", "e27", true);
	_factory->patchTEdgeCondition("ec11", "e24", true);
	_factory->patchTEdgeCondition("ec12", "e18", true);
	_factory->patchTEdgeCondition("ec13", "e39", true);
	_factory->patchTEdgeCondition("ec14", "e32", true);
	_factory->patchTEdgeCondition("ec15", "e17", true);
	_factory->patchTEdgeCondition("ec16", "e20", true);
	_factory->patchTEdgeCondition("ec17", "e30", true);
	_factory->patchTEdgeCondition("ec18", "e26", true);
	_factory->patchTEdgeCondition("ec19", "e9", true);
	_factory->patchTEdgeCondition("ec20", "e3", true);
	_factory->patchTEdgeCondition("ec21", "e25", true);
}

void MouseDemo::patchTFaces()
{
	std::vector<std::string> link_loop;
	std::vector<std::string> nodes;

	link_loop << "l0" << "l69" << "l72" << "l17";
	_factory->patchTFace("f0", link_loop, nodes); // v
	link_loop.clear();

	link_loop << "l18" << "l23" << "l8" << "l24" << "l29" << "l26";
	_factory->patchTFace("f1", link_loop, nodes); // v
	link_loop.clear();

	link_loop << "l28" << "l20" << "l5" << "l16";
	_factory->patchTFace("f2", link_loop, nodes); // v
	link_loop.clear();

	link_loop << "l25" << "l9" << "l14" << "l12";
	_factory->patchTFace("f3", link_loop, nodes); // v
	link_loop.clear();

	link_loop << "l30" << "l2" << "l80" << "l68";
	_factory->patchTFace("f4", link_loop, nodes); // v
	link_loop.clear();

	link_loop << "l66" << "l34" << "l74" << "l56";
	_factory->patchTFace("f5", link_loop, nodes); // v
	link_loop.clear();

	link_loop << "l42" << "l57" << "l52" << "l60" << "l63" << "l58";
	_factory->patchTFace("f6", link_loop, nodes); // v
	link_loop.clear();

	link_loop << "l54" << "l62" << "l50" << "l39";
	_factory->patchTFace("f7", link_loop, nodes); // v
	link_loop.clear();

	link_loop << "l43" << "l59" << "l46" << "l48";
	_factory->patchTFace("f8", link_loop, nodes); // v
	link_loop.clear();

	link_loop << "l36" << "l64" << "l82" << "l78";
	_factory->patchTFace("f9", link_loop, nodes); // v
	link_loop.clear();

	link_loop << "l73" << "l81" << "l76" << "l4" << "l6";
	_factory->patchTFace("f10", link_loop, nodes); // v
	link_loop.clear();

	link_loop << "l83" << "l75" << "l49" << "l40" << "l38";
	_factory->patchTFace("f11", link_loop, nodes); // v
	link_loop.clear();

	nodes.clear();
}

void MouseDemo::patchTNodes()
{
	//////////////////////////////////////////////////////////////////////////
	// ???
	_factory->patchTNodeV4("n0-0", "v0", "p0-0",  "n17-0", "", "n0-2", "n0-1"); // v
	_factory->patchTNodeV4("n0-1", "v0", "p0-1", "n17-0", "n0-0", "n0-3", "n12-1"); // v
	_factory->patchTNodeV4("n0-2", "v0", "p0-2", "n0-0", "", "", "n0-3"); // v
	_factory->patchTNodeV4("n0-3", "v0", "p0-3", "n0-1", "n0-2", "", "n12-1"); // v
	_factory->patchTNodeV4("n1-0", "v1", "p1-0", "n27-1", "n12-1", "n1-2", "n1-1"); // v
	_factory->patchTNodeV4("n1-1", "v1", "p1-1", "n27-1", "n1-0", "n1-3", ""); // v
	_factory->patchTNodeV4("n1-2", "v1", "p1-2", "n1-0", "n12-1", "", "n1-3"); // v
	_factory->patchTNodeV4("n1-3", "v1", "p1-3", "n1-1", "n1-2", "", ""); // v
	_factory->patchTNodeV4("n2-0", "v2", "p2-0", "n8-1", "n3-5", "n27-1", "n2-1"); // v
	_factory->patchTNodeV4("n2-1", "v2", "p2-1", "n8-1", "n2-0", "n27-1", ""); // v
	_factory->patchTNodeV4("n3-0", "v3", "p3-0", "", "n5-1", "n3-3", "n3-1"); // v
	_factory->patchTNodeV4("n3-1", "v3", "p3-1", "", "n3-0", "n3-4", "n3-2"); // v 
	_factory->patchTNodeV4("n3-2", "v3", "p3-2", "", "n3-1", "n3-5", "n2-0"); // v
	_factory->patchTNodeV4("n3-3", "v3", "p3-3", "n3-0", "n5-1", "", "n3-4"); // v
	_factory->patchTNodeV4("n3-4", "v3", "p3-4", "n3-1", "n3-3", "n3-6", "n3-5"); // v
	_factory->patchTNodeV4("n3-5", "v3", "p3-5", "n3-2", "n3-4", "n3-7", "n2-0"); // v
	_factory->patchTNodeV4("n3-6", "v3", "p3-6", "n3-4", "", "n17-0", "n3-7"); // v
	_factory->patchTNodeV4("n3-7", "v3", "p3-7", "n3-5", "n3-6", "n17-0", "n2-0"); // v
	_factory->patchTNodeV4("n4-0", "v4", "p4-0", "", "n19-0", "n4-1", "n6-0"); // v
	_factory->patchTNodeV4("n4-1", "v4", "p4-1", "n4-0", "n19-0", "n10-0", "n6-0"); // v
	_factory->patchTNodeV4("n5-0", "v5", "p5-0", "n10-0", "n16-5", "n5-1", "n3-3"); // v
	_factory->patchTNodeV4("n5-1", "v5", "p5-1", "n5-0", "n16-5", "", "n3-3"); // v
	_factory->patchTNodeV4("n6-0", "v6", "p6-0", "", "n4-0", "n6-1", "n7-0"); // v
	_factory->patchTNodeV4("n6-1", "v6", "p6-1", "n6-0", "n4-0", "n9-0", "n7-0"); // v
	_factory->patchTNodeV4("n7-0", "v7", "p7-0", "", "n6-0", "n7-2", "n7-1"); // v
	_factory->patchTNodeV4("n7-1", "v7", "p7-1", "", "n7-0", "n7-3", ""); // v
	_factory->patchTNodeV4("n7-2", "v7", "p7-2", "n7-0", "n6-0", "n8-1", "n7-3"); // v
	_factory->patchTNodeV4("n7-3", "v7", "p7-3", "n7-1", "n7-2", "n8-1", ""); // v
	_factory->patchTNodeV4("n8-0", "v8", "p8-0", "n7-3", "n9-0", "n2-1", "n8-1"); // v
	_factory->patchTNodeV4("n8-1", "v8", "p8-1", "n7-3", "n8-0", "n2-1", ""); // v
	_factory->patchTNodeV4("n9-0", "v9", "p9-0", "n6-1", "n10-0", "", "n8-0"); // v
	_factory->patchTNodeV4("n10-0", "v10", "p10-0", "n4-1", "n22-0", "n5-0", "n9-0"); // v
	_factory->patchTNodeV4("n12-0", "v12", "p12-0", "n23-0", "n0-3", "n12-1", "n1-2"); // v 
	_factory->patchTNodeV4("n12-1", "v12", "p12-1", "n12-0", "n0-3", "", "n1-2"); // v
	_factory->patchTNodeV4("n13-0", "v13", "p13-0", "n18-1", "n25-1", "n13-2", "n13-1"); // v
	_factory->patchTNodeV4("n13-1", "v13", "p13-1", "n18-1", "n13-0", "n13-3", ""); // v
	_factory->patchTNodeV4("n13-2", "v13", "p13-2", "n13-0", "n25-1", "", "n13-3"); // v
	_factory->patchTNodeV4("n13-3", "v13", "p13-3", "n13-1", "n13-2", "", ""); // v
	_factory->patchTNodeV4("n14-0", "v14", "p14-0", "n28-0", "", "n14-2", "n14-1"); // v
	_factory->patchTNodeV4("n14-1", "v14", "p14-1", "n28-0", "n14-0", "n14-3", "n25-1"); // v 
	_factory->patchTNodeV4("n14-2", "v14", "p14-2", "n14-0", "", "", "n14-3"); // v
	_factory->patchTNodeV4("n14-3", "v14", "p14-3", "n14-1", "n14-2", "", "n25-1"); // v 
	_factory->patchTNodeV4("n15-0", "v15", "p15-0", "n21-0", "", "n28-0", "n15-1"); // v 
	_factory->patchTNodeV4("n15-1", "v15", "p15-1", "n21-0", "n15-0", "n28-0", "n16-3"); // v
	_factory->patchTNodeV4("n16-0", "v16", "p16-0", "", "n15-1", "n16-3", "n16-1"); // v
	_factory->patchTNodeV4("n16-1", "v16", "p16-1", "", "n16-0", "n16-4", "n16-2"); // v
	_factory->patchTNodeV4("n16-2", "v16", "p16-2", "", "n16-1", "n16-5", "n5-1"); // v
	_factory->patchTNodeV4("n16-3", "v16", "p16-3", "n16-0", "n15-1", "n16-6", "n16-4"); // v
	_factory->patchTNodeV4("n16-4", "v16", "p16-4", "n16-1", "n16-3", "n16-7", "n16-5"); // v
	_factory->patchTNodeV4("n16-5", "v16", "p16-5", "n16-2", "n16-4", "", "n5-1"); // v
	_factory->patchTNodeV4("n16-6", "v16", "p16-6", "n16-3", "n15-1", "n18-1", "n16-7"); // v
	_factory->patchTNodeV4("n16-7", "v16", "p16-7", "n16-4", "n16-6", "n18-1", ""); // v
	_factory->patchTNodeV4("n17-0", "v17", "p17-0", "n3-6", "", "n0-0", "n17-1"); // v
	_factory->patchTNodeV4("n17-1", "v17", "p17-1", "n3-6", "n17-0", "n0-0", "n23-0"); // v
	_factory->patchTNodeV4("n18-0", "v18", "p18-0", "n16-7", "n26-0", "n13-1", "n18-1"); // v
	_factory->patchTNodeV4("n18-1", "v18", "p18-1", "n16-7", "n18-0", "n13-1", ""); // v
	_factory->patchTNodeV4("n19-0", "v19", "p19-0", "", "n20-1", "n19-1", "n4-0"); // v
	_factory->patchTNodeV4("n19-1", "v19", "p19-1", "n19-0", "n20-1", "n22-0", "n4-0"); // v
	_factory->patchTNodeV4("n20-0", "v20", "p20-0", "", "", "n20-2", "n20-1"); // v
	_factory->patchTNodeV4("n20-1", "v20", "p20-1", "", "n20-0", "n20-3", "n19-0"); // v
	_factory->patchTNodeV4("n20-2", "v20", "p20-2", "n20-0", "", "n21-0", "n20-3"); // v
	_factory->patchTNodeV4("n20-3", "v20", "p20-3", "n20-1", "n20-2", "n21-0", "n19-0"); // v
	_factory->patchTNodeV4("n21-0", "v21", "p21-0", "n20-2", "", "n15-0", "n21-1"); // v
	_factory->patchTNodeV4("n21-1", "v21", "p21-1", "n20-2", "n21-0", "n15-0", "n22-0"); // v
	_factory->patchTNodeV4("n22-0", "v22", "p22-0", "n19-1", "n21-1", "", "n10-0"); // v
	_factory->patchTNodeV4("n23-0", "v23", "p23-0", "", "n17-1", "n12-0", "n27-0"); // v
	_factory->patchTNodeV4("n25-0", "v25", "p25-0", "n26-0", "n14-3", "n25-1", "n13-2"); // v
	_factory->patchTNodeV4("n25-1", "v25", "p25-1", "n25-0", "n14-3", "", "n13-2"); // v
	_factory->patchTNodeV4("n26-0", "v26", "p26-0", "", "n28-1", "n25-0", "n18-0"); // v
	_factory->patchTNodeV4("n27-0", "v27", "p27-0", "n2-1", "n23-0", "n1-1", "n27-1"); // v
	_factory->patchTNodeV4("n27-1", "v27", "p27-1", "n2-1", "n27-0", "n1-1", ""); // v
	_factory->patchTNodeV4("n28-0", "v28", "p28-0", "n15-0", "", "n14-0", "n28-1"); // v
	_factory->patchTNodeV4("n28-1", "v28", "p28-1", "n15-0", "n28-0", "n14-0", "n26-0"); // v


	//////////////////////////////////////////////////////////////////////////
	// ???
// 	_factory->patchTNodeV4("k0-0", "v0", "p0-0",  "k17-0", "", "k0-2", "k0-1"); // v
// 	_factory->patchTNodeV4("k0-1", "v0", "p0-1", "k17-0", "k0-0", "k0-3", "k12-1"); // v
// 	_factory->patchTNodeV4("k0-2", "v0", "p0-2", "k0-0", "", "", "k0-3"); // v
// 	_factory->patchTNodeV4("k0-3", "v0", "p0-3", "k0-1", "k0-2", "", "k12-1"); // v
// 	_factory->patchTNodeV4("k1-0", "v1", "p1-0", "k27-1", "k12-1", "k1-2", "k1-1"); // v
// 	_factory->patchTNodeV4("k1-1", "v1", "p1-1", "k27-1", "k1-0", "k1-3", ""); // v
// 	_factory->patchTNodeV4("k1-2", "v1", "p1-2", "k1-0", "k12-1", "", "k1-3"); // v
// 	_factory->patchTNodeV4("k1-3", "v1", "p1-3", "k1-1", "k1-2", "", ""); // v
// 	_factory->patchTNodeV4("k2-0", "v2", "p2-0", "k8-1", "k3-5", "k27-1", "k2-1"); // v
// 	_factory->patchTNodeV4("k2-1", "v2", "p2-1", "k8-1", "k2-0", "k27-1", ""); // v
// 	_factory->patchTNodeV4("k3-0", "v3", "p3-0", "k9-0", "k5-1", "k3-3", "k3-1"); // v
// 	_factory->patchTNodeV4("k3-1", "v3", "p3-1", "k9-0", "k3-0", "k3-4", "k3-2"); // v 
// 	_factory->patchTNodeV4("k3-2", "v3", "p3-2", "k9-0", "k3-1", "k3-5", "k2-0"); // v
// 	_factory->patchTNodeV4("k3-3", "v3", "p3-3", "k3-0", "k5-1", "", "k3-4"); // v
// 	_factory->patchTNodeV4("k3-4", "v3", "p3-4", "k3-1", "k3-3", "k3-6", "k3-5"); // v
// 	_factory->patchTNodeV4("k3-5", "v3", "p3-5", "k3-2", "k3-4", "k3-7", "k2-0"); // v
// 	_factory->patchTNodeV4("k3-6", "v3", "p3-6", "k3-4", "", "k17-0", "k3-7"); // v
// 	_factory->patchTNodeV4("k3-7", "v3", "p3-7", "k3-5", "k3-6", "k17-0", "k2-0"); // v
// 	_factory->patchTNodeV4("k4-0", "v4", "p4-0", "", "k19-0", "k4-1", "k6-0"); // v
// 	_factory->patchTNodeV4("k4-1", "v4", "p4-1", "k4-0", "k19-0", "k10-0", "k6-0"); // v
// 	_factory->patchTNodeV4("k5-0", "v5", "p5-0", "k10-0", "k16-5", "k5-1", "k3-3"); // v
// 	_factory->patchTNodeV4("k5-1", "v5", "p5-1", "k5-0", "k16-5", "", "k3-3"); // v
// 	_factory->patchTNodeV4("k6-0", "v6", "p6-0", "", "k4-0", "k6-1", "k7-0"); // v
// 	_factory->patchTNodeV4("k6-1", "v6", "p6-1", "k6-0", "k4-0", "k9-0", "k7-0"); // v
// 	_factory->patchTNodeV4("k7-0", "v7", "p7-0", "", "k6-0", "k7-2", "k7-1"); // v
// 	_factory->patchTNodeV4("k7-1", "v7", "p7-1", "", "k7-0", "k7-3", ""); // v
// 	_factory->patchTNodeV4("k7-2", "v7", "p7-2", "k7-0", "k6-0", "k8-1", "k7-3"); // v
// 	_factory->patchTNodeV4("k7-3", "v7", "p7-3", "k7-1", "k7-2", "k8-1", ""); // v
// 	_factory->patchTNodeV4("k8-0", "v8", "p8-0", "k7-3", "k9-0", "k2-1", "k8-1"); // v
// 	_factory->patchTNodeV4("k8-1", "v8", "p8-1", "k7-3", "k8-0", "k2-1", ""); // v
// 	_factory->patchTNodeV4("k9-0", "v9", "p9-0", "k6-1", "k10-0", "k3-1", "k8-0"); // v
// 	_factory->patchTNodeV4("k10-0", "v10", "p10-0", "k4-1", "k22-0", "k5-0", "k9-0"); // v
// 	_factory->patchTNodeV4("k12-0", "v12", "p12-0", "k23-0", "k0-3", "k12-1", "k1-2"); // v 
// 	_factory->patchTNodeV4("k12-1", "v12", "p12-1", "k12-0", "k0-3", "", "k1-2"); // v
// 	_factory->patchTNodeV4("k13-0", "v13", "p13-0", "k18-1", "k25-1", "k13-2", "k13-1"); // v
// 	_factory->patchTNodeV4("k13-1", "v13", "p13-1", "k18-1", "k13-0", "k13-3", ""); // v
// 	_factory->patchTNodeV4("k13-2", "v13", "p13-2", "k13-0", "k25-1", "", "k13-3"); // v
// 	_factory->patchTNodeV4("k13-3", "v13", "p13-3", "k13-1", "k13-2", "", ""); // v
// 	_factory->patchTNodeV4("k14-0", "v14", "p14-0", "k28-0", "", "k14-2", "k14-1"); // v
// 	_factory->patchTNodeV4("k14-1", "v14", "p14-1", "k28-0", "k14-0", "k14-3", "k25-1"); // v 
// 	_factory->patchTNodeV4("k14-2", "v14", "p14-2", "k14-0", "", "", "k14-3"); // v
// 	_factory->patchTNodeV4("k14-3", "v14", "p14-3", "k14-1", "k14-2", "", "k25-1"); // v 
// 	_factory->patchTNodeV4("k15-0", "v15", "p15-0", "k21-0", "", "k28-0", "k15-1"); // v 
// 	_factory->patchTNodeV4("k15-1", "v15", "p15-1", "k21-0", "k15-0", "k28-0", "k16-3"); // v
// 	_factory->patchTNodeV4("k16-0", "v16", "p16-0", "k22-0", "k15-1", "k16-3", "k16-1"); // v
// 	_factory->patchTNodeV4("k16-1", "v16", "p16-1", "k22-0", "k16-0", "k16-4", "k16-2"); // v
// 	_factory->patchTNodeV4("k16-2", "v16", "p16-2", "k22-0", "k16-1", "k16-5", "k5-1"); // v
// 	_factory->patchTNodeV4("k16-3", "v16", "p16-3", "k16-0", "k15-1", "k16-6", "k16-4"); // v
// 	_factory->patchTNodeV4("k16-4", "v16", "p16-4", "k16-1", "k16-3", "k16-7", "k16-5"); // v
// 	_factory->patchTNodeV4("k16-5", "v16", "p16-5", "k16-2", "k16-4", "", "k5-1"); // v
// 	_factory->patchTNodeV4("k16-6", "v16", "p16-6", "k16-3", "k15-1", "k18-1", "k16-7"); // v
// 	_factory->patchTNodeV4("k16-7", "v16", "p16-7", "k16-4", "k16-6", "k18-1", ""); // v
// 	_factory->patchTNodeV4("k17-0", "v17", "p17-0", "k3-6", "", "k0-0", "k17-1"); // v
// 	_factory->patchTNodeV4("k17-1", "v17", "p17-1", "k3-6", "k17-0", "k0-0", "k23-0"); // v
// 	_factory->patchTNodeV4("k18-0", "v18", "p18-0", "k16-7", "k26-0", "k13-1", "k18-1"); // v
// 	_factory->patchTNodeV4("k18-1", "v18", "p18-1", "k16-7", "k18-0", "k13-1", ""); // v
// 	_factory->patchTNodeV4("k19-0", "v19", "p19-0", "", "k20-1", "k19-1", "k4-0"); // v
// 	_factory->patchTNodeV4("k19-1", "v19", "p19-1", "k19-0", "k20-1", "k22-0", "k4-0"); // v
// 	_factory->patchTNodeV4("k20-0", "v20", "p20-0", "", "", "k20-2", "k20-1"); // v
// 	_factory->patchTNodeV4("k20-1", "v20", "p20-1", "", "k20-0", "k20-3", "k19-0"); // v
// 	_factory->patchTNodeV4("k20-2", "v20", "p20-2", "k20-0", "", "k21-0", "k20-3"); // v
// 	_factory->patchTNodeV4("k20-3", "v20", "p20-3", "k20-1", "k20-2", "k21-0", "k19-0"); // v
// 	_factory->patchTNodeV4("k21-0", "v21", "p21-0", "k20-2", "", "k15-0", "k21-1"); // v
// 	_factory->patchTNodeV4("k21-1", "v21", "p21-1", "k20-2", "k21-0", "k15-0", "k22-0"); // v
// 	_factory->patchTNodeV4("k22-0", "v22", "p22-0", "k19-1", "k21-1", "k16-1", "k10-0"); // v
// 	_factory->patchTNodeV4("k23-0", "v23", "p23-0", "", "k17-1", "k12-0", "k27-0"); // v
// 	_factory->patchTNodeV4("k25-0", "v25", "p25-0", "k26-0", "k14-3", "k25-1", "k13-2"); // v
// 	_factory->patchTNodeV4("k25-1", "v25", "p25-1", "k25-0", "k14-3", "", "k13-2"); // v
// 	_factory->patchTNodeV4("k26-0", "v26", "p26-0", "", "k28-1", "k25-0", "k18-0"); // v
// 	_factory->patchTNodeV4("k27-0", "v27", "p27-0", "k2-1", "k23-0", "k1-1", "k27-1"); // v
// 	_factory->patchTNodeV4("k27-1", "v27", "p27-1", "k2-1", "k27-0", "k1-1", ""); // v
// 	_factory->patchTNodeV4("k28-0", "v28", "p28-0", "k15-0", "", "k14-0", "k28-1"); // v
// 	_factory->patchTNodeV4("k28-1", "v28", "p28-1", "k15-0", "k28-0", "k14-0", "k26-0"); // v
}

void MouseDemo::patchTPoints() // v
{
	_factory->patchTPoint("p0-0", "n0-0");
	_factory->patchTPoint("p0-1", "n0-1");
	_factory->patchTPoint("p0-2", "n0-2");
	_factory->patchTPoint("p0-3", "n0-3");
	_factory->patchTPoint("p1-0", "n1-0");
	_factory->patchTPoint("p1-1", "n1-1");
	_factory->patchTPoint("p1-2", "n1-2");
	_factory->patchTPoint("p1-3", "n1-3");
	_factory->patchTPoint("p2-0", "n2-0");
	_factory->patchTPoint("p2-1", "n2-1");
	_factory->patchTPoint("p3-0", "n3-0");
	_factory->patchTPoint("p3-1", "n3-1");
	_factory->patchTPoint("p3-2", "n3-2");
	_factory->patchTPoint("p3-3", "n3-3");
	_factory->patchTPoint("p3-4", "n3-4");
	_factory->patchTPoint("p3-5", "n3-5");
	_factory->patchTPoint("p3-6", "n3-6");
	_factory->patchTPoint("p3-7", "n3-7");
	_factory->patchTPoint("p4-0", "n4-0");
	_factory->patchTPoint("p4-1", "n4-1");
	_factory->patchTPoint("p5-0", "n5-0");
	_factory->patchTPoint("p5-1", "n5-1");
	_factory->patchTPoint("p6-0", "n6-0");
	_factory->patchTPoint("p6-1", "n6-1");
	_factory->patchTPoint("p7-0", "n7-0");
	_factory->patchTPoint("p7-1", "n7-1");
	_factory->patchTPoint("p7-2", "n7-2");
	_factory->patchTPoint("p7-3", "n7-3");
	_factory->patchTPoint("p8-0", "n8-0");
	_factory->patchTPoint("p8-1", "n8-1");
	_factory->patchTPoint("p9-0", "n9-0");
	_factory->patchTPoint("p10-0", "n10-0");
	_factory->patchTPoint("p12-0", "n12-0");
	_factory->patchTPoint("p12-1", "n12-1");
	_factory->patchTPoint("p13-0", "n13-0");
	_factory->patchTPoint("p13-1", "n13-1");
	_factory->patchTPoint("p13-2", "n13-2");
	_factory->patchTPoint("p13-3", "n13-3");
	_factory->patchTPoint("p14-0", "n14-0");
	_factory->patchTPoint("p14-1", "n14-1");
	_factory->patchTPoint("p14-2", "n14-2");
	_factory->patchTPoint("p14-3", "n14-3");
	_factory->patchTPoint("p15-0", "n15-0");
	_factory->patchTPoint("p15-1", "n15-1");
	_factory->patchTPoint("p16-0", "n16-0");
	_factory->patchTPoint("p16-1", "n16-1");
	_factory->patchTPoint("p16-2", "n16-2");
	_factory->patchTPoint("p16-3", "n16-3");
	_factory->patchTPoint("p16-4", "n16-4");
	_factory->patchTPoint("p16-5", "n16-5");
	_factory->patchTPoint("p16-6", "n16-6");
	_factory->patchTPoint("p16-7", "n16-7");
	_factory->patchTPoint("p17-0", "n17-0");
	_factory->patchTPoint("p17-1", "n17-1");
	_factory->patchTPoint("p18-0", "n18-0");
	_factory->patchTPoint("p18-1", "n18-1");
	_factory->patchTPoint("p19-0", "n19-0");
	_factory->patchTPoint("p19-1", "n19-1");
	_factory->patchTPoint("p20-0", "n20-0");
	_factory->patchTPoint("p20-1", "n20-1");
	_factory->patchTPoint("p20-2", "n20-2");
	_factory->patchTPoint("p20-3", "n20-3");
	_factory->patchTPoint("p21-0", "n21-0");
	_factory->patchTPoint("p21-1", "n21-1");
	_factory->patchTPoint("p22-0", "n22-0");
	_factory->patchTPoint("p23-0", "n23-0");
	_factory->patchTPoint("p25-0", "n25-0");
	_factory->patchTPoint("p25-1", "n25-1");
	_factory->patchTPoint("p26-0", "n26-0");
	_factory->patchTPoint("p27-0", "n27-0");
	_factory->patchTPoint("p27-1", "n27-1");
	_factory->patchTPoint("p28-0", "n28-0");
	_factory->patchTPoint("p28-1", "n28-1");
}

void MouseDemo::patchTSpline() // v
{
	_factory->patchTSpline("mouse", "image", "nodes", "points");
}

void MouseDemo::patchTImage()
{
	std::vector<std::string> faces, links, edges, vertices;
	_factory->findTObjectNames(faces, TSPLINE::E_TFACE);
	_factory->findTObjectNames(links, TSPLINE::E_TLINK);
	_factory->findTObjectNames(edges, TSPLINE::E_TEDGE);
	_factory->findTObjectNames(vertices, TSPLINE::E_TVERTEX);
	_factory->patchTImage("image", faces, links, edges, vertices);
}

void MouseDemo::patchTConnect()
{
	std::vector<std::string> nodes;
	_factory->findTObjectNames(nodes, TSPLINE::E_TNODE);
	_factory->patchTConnect("nodes", nodes);
}

void MouseDemo::patchTPointset()
{
	std::vector<std::string> points;
	_factory->findTObjectNames(points, TSPLINE::E_TPOINT);
	_factory->patchTPointset("points", points);
}

void MouseDemo::prepareTObjects()
{
	_factory->prepareTNodeHalfLinkages();
	_factory->prepareTJunctions();
	_factory->prepareImageConnect();
}

TSplinePtr MouseDemo::findTSpline()
{
	return _factory->findTSpline();
}

TGroupPtr MouseDemo::findTGroup()
{
	return _factory->findTGroup();
}

void MouseDemo::findTFaceNames( std::vector<std::string> &faces )
{
	_factory->findTObjectNames(faces, TSPLINE::E_TFACE);
}
