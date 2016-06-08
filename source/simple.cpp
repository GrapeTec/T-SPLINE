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
  @file simple.cpp
  @brief A demo file.

  Demos for T-spline, etc.
*/

#include "simple.h"

#ifdef use_namespace
using namespace TSPLINE;
#endif

std::vector<std::string>& operator<<(std::vector<std::string> &container, const std::string &value);

SimpleDemo::SimpleDemo()
{
	_factory = makePtr<TFactory>();
	createSimple();
}

SimpleDemo::~SimpleDemo()
{

}

void SimpleDemo::createSimple()
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

void SimpleDemo::createTSpline()
{
	_factory->createTSpline("simple");
}

void SimpleDemo::createTImage()
{
	_factory->createTImage("image");
}

void SimpleDemo::createTConnect()
{
	_factory->createTConnect("nodes");
}

void SimpleDemo::createTPointset()
{
	_factory->createTPointset("points");
}

void SimpleDemo::createTVertices()
{
	_factory->createTVertex("v0", 0.0, 0.0); // v
	_factory->createTVertex("v1", 0.5, 0.0); // v
	_factory->createTVertex("v2", 1.0, 0.0); // v
	_factory->createTVertex("v3", 0.0, 0.5); // v
	_factory->createTVertex("v4", 0.5, 0.5); // v
	_factory->createTVertex("v5", 1.0, 0.5); // v
	_factory->createTVertex("v6", 0.0, 1.0); // v
	_factory->createTVertex("v7", 1.0, 1.0); // v
}

void SimpleDemo::createTEdges() // v
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
}

void SimpleDemo::createTLinks() // v
{
	_factory->createTLink("l0");
	_factory->createTLink("l1");
	_factory->createTLink("l2");
	_factory->createTLink("l3");
	_factory->createTLink("l4");
	_factory->createTLink("l5");
	_factory->createTLink("l6");
	_factory->createTLink("l7");
	_factory->createTLink("l8");
	_factory->createTLink("l9");
	_factory->createTLink("l10");
	_factory->createTLink("l11");
	_factory->createTLink("l12");
	_factory->createTLink("l13");
	_factory->createTLink("l14");
	_factory->createTLink("l15");
	_factory->createTLink("l16");
	_factory->createTLink("l17");
	_factory->createTLink("l18");
	_factory->createTLink("l19");
}

void SimpleDemo::createTEdgeConditions() // v
{
	_factory->createTEdgeCondition("ec0");
	_factory->createTEdgeCondition("ec1");
	_factory->createTEdgeCondition("ec2");
	_factory->createTEdgeCondition("ec3");
	_factory->createTEdgeCondition("ec4");
	_factory->createTEdgeCondition("ec5");
	_factory->createTEdgeCondition("ec6");
}

void SimpleDemo::createTFaces() // v
{
	_factory->createTFace("f0");
	_factory->createTFace("f1");
	_factory->createTFace("f2");
}

void SimpleDemo::createTNodes() // v
{
	_factory->createTNodeV4("n0-0"); // v0
	_factory->createTNodeV4("n0-1");
	_factory->createTNodeV4("n0-2");
	_factory->createTNodeV4("n0-3");
	_factory->createTNodeV4("n1-0"); // v1
	_factory->createTNodeV4("n1-1");
	_factory->createTNodeV4("n2-0"); // v2
	_factory->createTNodeV4("n2-1"); 
	_factory->createTNodeV4("n2-2"); 
	_factory->createTNodeV4("n2-3"); 
	_factory->createTNodeV4("n3-0"); // v3
	_factory->createTNodeV4("n3-1");
	_factory->createTNodeV4("n4-0"); // v4
	_factory->createTNodeV4("n5-0"); // v5
	_factory->createTNodeV4("n5-1");
	_factory->createTNodeV4("n6-0"); // v6
	_factory->createTNodeV4("n6-1");
	_factory->createTNodeV4("n6-2");
	_factory->createTNodeV4("n6-3");
	_factory->createTNodeV4("n7-0"); // v7
	_factory->createTNodeV4("n7-1");
	_factory->createTNodeV4("n7-2");
	_factory->createTNodeV4("n7-3");
}

void SimpleDemo::createTPoints()
{
	_factory->createTPoint("p0-0", 0.0, 1.0, 0.25, 1.0); // v0
	_factory->createTPoint("p0-1", 1.0, 1.0, 0.5, 1.0); // v
	_factory->createTPoint("p0-2", 0.0, 0.0, 0.0, 1.0); // v
	_factory->createTPoint("p0-3", 1.0, 0.0, 0.25, 1.0); // v
	_factory->createTPoint("p1-0", 2.0, 1.0, 0.75, 1.0); // v1
	_factory->createTPoint("p1-1", 2.0, 0.0, 0.5, 1.0); // v
	_factory->createTPoint("p2-0", 3.0, 1.0, 0.5, 1.0); // v2
	_factory->createTPoint("p2-1", 4.0, 1.0, 0.25, 1.0); // v
	_factory->createTPoint("p2-2", 3.0, 0.0, 0.25, 1.0); // v
	_factory->createTPoint("p2-3", 4.0, 0.0, 0.0, 1.0); // v
	_factory->createTPoint("p3-0", 0.0, 2.0, 0.5, 1.0); // v3
	_factory->createTPoint("p3-1", 1.0, 2.0, 0.75, 1.0); // v
	_factory->createTPoint("p4-0", 2.0, 2.0, -1.0, 1.0); // v4
	_factory->createTPoint("p5-0", 3.0, 2.0, 0.75, 1.0); // v5
	_factory->createTPoint("p5-1", 4.0, 2.0, 0.5, 1.0); // v
	_factory->createTPoint("p6-0", 0.0, 4.0, 0.0, 1.0); // v6
	_factory->createTPoint("p6-1", 1.0, 4.0, 0.25, 1.0); // v
	_factory->createTPoint("p6-2", 0.0, 3.0, 0.25, 1.0); // v
	_factory->createTPoint("p6-3", 1.0, 3.0, 0.5, 1.0); // v
	_factory->createTPoint("p7-0", 3.0, 4.0, 0.25, 1.0); // v7
	_factory->createTPoint("p7-1", 4.0, 4.0, 0.0, 1.0); // v
	_factory->createTPoint("p7-2", 3.0, 3.0, 0.5, 1.0); // v
	_factory->createTPoint("p7-3", 4.0, 3.0, 0.25, 1.0); // v
}

void SimpleDemo::patchTVertices()
{
	_factory->patchTVertexByVertices("v0", "v3", "", "", "v1"); // v
	_factory->patchTVertexByVertices("v1", "v4", "v0", "", "v2"); // v
	_factory->patchTVertexByVertices("v2", "v5", "v1", "", ""); // v
	_factory->patchTVertexByVertices("v3", "v6", "", "v0", "v4"); // v
	_factory->patchTVertexByVertices("v4", "", "v3", "v1", "v5"); // v
	_factory->patchTVertexByVertices("v5", "v7", "v4", "v2", ""); // v
	_factory->patchTVertexByVertices("v6", "", "", "v3", "v7"); // v
	_factory->patchTVertexByVertices("v7", "", "v6", "v5", ""); // v
}

void SimpleDemo::patchTEdges()
{
	_factory->patchTEdge("e0", "v0", "v1", "f0", ""); // v
	_factory->patchTEdge("e1", "v1", "v2", "f1", ""); // v
	_factory->patchTEdge("e2", "v0", "v3", "", "f0"); // v
	_factory->patchTEdge("e3", "v1", "v4", "f0", "f1"); // v
	_factory->patchTEdge("e4", "v2", "v5", "f1", ""); // v
	_factory->patchTEdge("e5", "v3", "v4", "f2", "f0"); // v
	_factory->patchTEdge("e6", "v4", "v5", "f2", "f1"); // v
	_factory->patchTEdge("e7", "v3", "v6", "", "f2"); // v
	_factory->patchTEdge("e8", "v5", "v7", "f2", ""); // v
	_factory->patchTEdge("e9", "v6", "v7", "", "f2"); // v
}

void SimpleDemo::patchTLinks()
{
	_factory->patchTLink("l0", "e0", true); // v
	_factory->patchTLink("l1", "e0", false); // v
	_factory->patchTLink("l2", "e1", true); // v
	_factory->patchTLink("l3", "e1", false); // v
	_factory->patchTLink("l4", "e2", true); // v
	_factory->patchTLink("l5", "e2", false); // v
	_factory->patchTLink("l6", "e3", true); // v
	_factory->patchTLink("l7", "e3", false); // v
	_factory->patchTLink("l8", "e4", true); // v
	_factory->patchTLink("l9", "e4", false); // v
	_factory->patchTLink("l10", "e5", true); // v
	_factory->patchTLink("l11", "e5", false); // v
	_factory->patchTLink("l12", "e6", true); // v
	_factory->patchTLink("l13", "e6", false); // v
	_factory->patchTLink("l14", "e7", true); // v
	_factory->patchTLink("l15", "e7", false); // v
	_factory->patchTLink("l16", "e8", true); // v
	_factory->patchTLink("l17", "e8", false); // v
	_factory->patchTLink("l18", "e9", true); // v
	_factory->patchTLink("l19", "e9", false); // v
}

void SimpleDemo::patchTEdgeConditions() // v
{
	_factory->patchTEdgeCondition("ec0", "e0", true);
	_factory->patchTEdgeCondition("ec1", "e1", true);
	_factory->patchTEdgeCondition("ec2", "e2", true);
	_factory->patchTEdgeCondition("ec3", "e4", true);
	_factory->patchTEdgeCondition("ec4", "e7", true);
	_factory->patchTEdgeCondition("ec5", "e8", true);
	_factory->patchTEdgeCondition("ec6", "e9", true);
}

void SimpleDemo::patchTFaces()
{
	std::vector<std::string> link_loop;
	std::vector<std::string> nodes;

	link_loop << "l0" << "l6" << "l11" << "l5";
	_factory->patchTFace("f0", link_loop, nodes); // v
	link_loop.clear();

	link_loop << "l2" << "l8" << "l13" << "l7";
	_factory->patchTFace("f1", link_loop, nodes); // v
	link_loop.clear();

	link_loop << "l10" << "l12" << "l16" << "l19" << "l15";
	_factory->patchTFace("f2", link_loop, nodes); // v
	link_loop.clear();

	nodes.clear();
}

void SimpleDemo::patchTNodes()
{
	//////////////////////////////////////////////////////////////////////////
	// ???
	_factory->patchTNodeV4("n0-0", "v0", "p0-0",  "n3-0", "", "n0-2", "n0-1"); // v0
	_factory->patchTNodeV4("n0-1", "v0", "p0-1", "n3-0", "n0-0", "n0-3", "n1-1"); // v
	_factory->patchTNodeV4("n0-2", "v0", "p0-2", "n0-0", "", "", "n0-3"); // v
	_factory->patchTNodeV4("n0-3", "v0", "p0-3", "n0-1", "n0-2", "", "n1-1"); // v

	_factory->patchTNodeV4("n1-0", "v1", "p1-0", "n4-0", "n0-3", "n1-1", "n2-2"); // v1
	_factory->patchTNodeV4("n1-1", "v1", "p1-1", "n1-0", "n0-3", "", "n2-2"); // v

	_factory->patchTNodeV4("n2-0", "v2", "p2-0", "n5-1", "n1-1", "n2-2", "n2-1"); // v2
	_factory->patchTNodeV4("n2-1", "v2", "p2-1", "n5-1", "n2-0", "n2-3", ""); // v
	_factory->patchTNodeV4("n2-2", "v2", "p2-2", "n2-0", "n1-1", "", "n2-3"); // v
	_factory->patchTNodeV4("n2-3", "v2", "p2-3", "n2-1", "n2-2", "", ""); // v

	_factory->patchTNodeV4("n3-0", "v3", "p3-0", "n6-2", "", "n0-0", "n3-1"); // v3
	_factory->patchTNodeV4("n3-1", "v3", "p3-1", "n6-2", "n3-0", "n0-0", "n4-0"); // v 

	_factory->patchTNodeV4("n4-0", "v4", "p4-0", "", "n3-1", "n1-0", "n5-0"); // v4

	_factory->patchTNodeV4("n5-0", "v5", "p5-0", "n7-3", "n4-0", "n2-1", "n5-1"); // v5
	_factory->patchTNodeV4("n5-1", "v5", "p5-1", "n7-3", "n5-0", "n2-1", ""); // v

	_factory->patchTNodeV4("n6-0", "v6", "p6-0", "", "", "n6-2", "n6-1"); // v6
	_factory->patchTNodeV4("n6-1", "v6", "p6-1", "", "n6-0", "n6-3", "n7-0"); // v
	_factory->patchTNodeV4("n6-2", "v6", "p6-2", "n6-0", "", "n3-0", "n6-3"); // v
	_factory->patchTNodeV4("n6-3", "v6", "p6-3", "n6-1", "n6-2", "n3-0", "n7-0"); // v

	_factory->patchTNodeV4("n7-0", "v7", "p7-0", "", "n6-1", "n7-2", "n7-1"); // v
	_factory->patchTNodeV4("n7-1", "v7", "p7-1", "", "n7-0", "n7-3", ""); // v
	_factory->patchTNodeV4("n7-2", "v7", "p7-2", "n7-0", "n6-1", "n5-1", "n7-3"); // v
	_factory->patchTNodeV4("n7-3", "v7", "p7-3", "n7-1", "n7-2", "n5-1", ""); // v
}

void SimpleDemo::patchTPoints() // v
{
	_factory->patchTPoint("p0-0", "n0-0");
	_factory->patchTPoint("p0-1", "n0-1");
	_factory->patchTPoint("p0-2", "n0-2");
	_factory->patchTPoint("p0-3", "n0-3");

	_factory->patchTPoint("p1-0", "n1-0");
	_factory->patchTPoint("p1-1", "n1-1");

	_factory->patchTPoint("p2-0", "n2-0");
	_factory->patchTPoint("p2-1", "n2-1");
	_factory->patchTPoint("p2-2", "n2-2");
	_factory->patchTPoint("p2-3", "n2-3");

	_factory->patchTPoint("p3-0", "n3-0");
	_factory->patchTPoint("p3-1", "n3-1");

	_factory->patchTPoint("p4-0", "n4-0");

	_factory->patchTPoint("p5-0", "n5-0");
	_factory->patchTPoint("p5-1", "n5-1");

	_factory->patchTPoint("p6-0", "n6-0");
	_factory->patchTPoint("p6-1", "n6-1");
	_factory->patchTPoint("p6-2", "n6-2");
	_factory->patchTPoint("p6-3", "n6-3");

	_factory->patchTPoint("p7-0", "n7-0");
	_factory->patchTPoint("p7-1", "n7-1");
	_factory->patchTPoint("p7-2", "n7-2");
	_factory->patchTPoint("p7-3", "n7-3");
}

void SimpleDemo::patchTSpline() // v
{
	_factory->patchTSpline("simple", "image", "nodes", "points");
}

void SimpleDemo::patchTImage()
{
	std::vector<std::string> faces, links, edges, vertices;
	_factory->findTObjectNames(faces, TSPLINE::E_TFACE);
	_factory->findTObjectNames(links, TSPLINE::E_TLINK);
	_factory->findTObjectNames(edges, TSPLINE::E_TEDGE);
	_factory->findTObjectNames(vertices, TSPLINE::E_TVERTEX);
	_factory->patchTImage("image", faces, links, edges, vertices);
}

void SimpleDemo::patchTConnect()
{
	std::vector<std::string> nodes;
	_factory->findTObjectNames(nodes, TSPLINE::E_TNODE);
	_factory->patchTConnect("nodes", nodes);
}

void SimpleDemo::patchTPointset()
{
	std::vector<std::string> points;
	_factory->findTObjectNames(points, TSPLINE::E_TPOINT);
	_factory->patchTPointset("points", points);
}

void SimpleDemo::prepareTObjects()
{
	_factory->prepareTNodeHalfLinkages();
	_factory->prepareTJunctions();
	_factory->prepareImageConnect();
}

TSplinePtr SimpleDemo::findTSpline()
{
	return _factory->findTSpline();
}

TGroupPtr SimpleDemo::findTGroup()
{
	return _factory->findTGroup();
}

void SimpleDemo::findTFaceNames( std::vector<std::string> &faces )
{
	_factory->findTObjectNames(faces, TSPLINE::E_TFACE);
}
