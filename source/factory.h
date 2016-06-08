/*
T-SPLINE -- A T-spline object oriented library in C++
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
2016/03/31: Wenlei Xiao
- Doxygen comments added.
-------------------------------------------------------------------------------
*/

/**  @file  [factory]  
*  @brief  This file contains the classes of different crosses.
  *  @author  <Wenlei Xiao>  
  *  @date  <2015.04.08>  
  *  @version  <v1.0>  
  *  @note  
  *  The cross classes include the T-mapper cross, the T-vertex cross, the T-link cross, and the T-node cross.   
*/

#ifndef FACTORY_H
#define FACTORY_H

#include <utils.h>
#include <tspline.h>
#include <finder.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif
	
/**  
  *  @class  <TFactory> 
  *  @brief  Create T-objects using the factory patten.
  *  @note  
  * The TFactory class is used to create diverse T-objects.
  * The create functions are used to pre-allocate the memory for the wanted T-objects.
  * The patch functions are used to patch the parameters in the created T-objects.
  * The prepare functions are used to derive the missed optional attributes.
*/

DECLARE_SMARTPTR(TFactory);
class TFactory
{
public:
	TFactory();
	~TFactory();
public:
	/** Create a T-spline object*/
	TSplinePtr createTSpline(const std::string &name);
	/** Create a T-image object*/
	TImagePtr createTImage(const std::string &name);
	/** Create a T-connect object*/
	TConnectPtr createTConnect(const std::string &name);
	/** Create a T-pointset object*/
	TPointsetPtr createTPointset(const std::string &name);
	/** Create a T-vertex object with a coordinate (s, t)*/
	TVertexPtr createTVertex(const std::string &name, Real s, Real t);
	/** Create a T-edge object*/
	TEdgePtr createTEdge(const std::string &name);
	/** Create a T-link object*/
	TLinkPtr createTLink(const std::string &name);
	/** Create a T-edgecondition object*/
	TEdgeConditionPtr createTEdgeCondition(const std::string &name);
	/** Create a T-face object*/
	TFacePtr createTFace(const std::string &name);
	/** Create a T-node object*/
	TNodePtr createTNode(const std::string &name);
	/** Create a T-node valence 4 object*/
	TNodeV4Ptr createTNodeV4(const std::string &name);
	/** Create a T-point object with a coordinate (x, y, z, w)*/
	TPointPtr createTPoint(const std::string &name, Real x = 0.0, Real y = 0.0, Real z = 0.0, Real w = 1.0);

	/** Patch the T-spline with needed attributes*/
	void patchTSpline(const TSplinePtr &spline, const std::string &tmesh, const std::string &nodes, const std::string &points, int degree = 3);
	/** Patch the named T-spline with needed attributes*/
	void patchTSpline(const std::string &spline, const std::string &tmesh, const std::string &nodes, const std::string &points, int degree = 3);

	/** Patch the T-image with needed attributes*/
	void patchTImage(const TImagePtr &tmesh, const std::vector<std::string> &faces, const std::vector<std::string> &links, 
		const std::vector<std::string> &edges, const std::vector<std::string> &vertices);
	/** Patch the named T-image with needed attributes*/
	void patchTImage(const std::string &tmesh, const std::vector<std::string> &faces, const std::vector<std::string> &links, 
		const std::vector<std::string> &edges, const std::vector<std::string> &vertices);

	/** Patch the T-connect with needed attributes*/
	void patchTConnect(const TConnectPtr &tnode_grid, const std::vector<std::string> &nodes);
	/** Patch the named T-connect with needed attributes*/
	void patchTConnect(const std::string &tnode_grid, const std::vector<std::string> &nodes);

	/** Patch the T-pointset with needed attributes*/
	void patchTPointset(const TPointsetPtr &tpoint_grid, const std::vector<std::string> &points);
	/** Patch the named T-pointset with needed attributes*/
	void patchTPointset(const std::string &tpoint_grid, const std::vector<std::string> &points);

	/** Patch the T-vertex with needed attributes*/
	void patchTVertex(const TVertexPtr &vertex, const std::string &north, const std::string &west, const std::string &south, const std::string &east);
	/** Patch the named T-vertex with needed attributes*/
	void patchTVertex(const std::string &vertex, const std::string &north, const std::string &west, const std::string &south, const std::string &east);

	/** Patch the T-edge with needed attributes*/
	void patchTEdge(const TEdgePtr &edge, const std::string &vstart_name, const std::string &vend_name, const std::string &lface_name, const std::string &rface_name);
	/** Patch the named T-edge with needed attributes*/
	void patchTEdge(const std::string &edge, const std::string &vstart_name, const std::string &vend_name, const std::string &lface_name, const std::string &rface_name);

	/** Patch the T-link with needed attributes*/
	void patchTLink(const TLinkPtr &link, const std::string &edge_name, bool orientation = true);
	/** Patch the named T-link with needed attributes*/
	void patchTLink(const std::string &link, const std::string &edge_name, bool orientation = true);

	/** Patch the T-edgecondition with needed attributes*/
	void patchTEdgeCondition(const TEdgeConditionPtr &edge_condition, const std::string &edge, bool boundary_condition);
	/** Patch the named T-edgecondition with needed attributes*/
	void patchTEdgeCondition(const std::string &edge_condition, const std::string &edge, bool boundary_condition);

	/** Patch the T-face with needed attributes*/
	void patchTFace(const TFacePtr &face, const std::vector<std::string> &link_loop, const std::vector<std::string> &nodes = _empty_nodes);
	/** Patch the named T-face with needed attributes*/
	void patchTFace(const std::string &face, const std::vector<std::string> &link_loop, const std::vector<std::string> &nodes = _empty_nodes);

	/** Patch the T-node with needed attributes*/
	void patchTNode(const TNodePtr &node, const std::string &mapper, const std::string &point);
	/** Patch the T-node valence 4 with needed attributes*/
	void patchTNodeV4(const TNodeV4Ptr &node_v4, const std::string &mapper, const std::string &point, const std::string &north, const std::string &west, const std::string &south, const std::string &east);
	/** Patch the named T-node valence 4 with needed attributes*/
	void patchTNodeV4(const std::string &node_v4, const std::string &mapper, const std::string &point, const std::string &north, const std::string &west, const std::string &south, const std::string &east);

	/** Patch the T-point with needed attributes*/
	void patchTPoint(const TPointPtr &point, const std::string &node);
	/** Patch the named T-point with needed attributes*/
	void patchTPoint(const std::string &point, const std::string &node);

	/** Patch the T-vertex with needed attributes by T-vertex neighbors*/
	void patchTVertexByVertices(const TVertexPtr &vertex, const std::string &north, const std::string &west, const std::string &south, const std::string &east);
	/** Patch the named T-vertex with needed attributes by T-vertex neighbors*/
	void patchTVertexByVertices(const std::string &vertex, const std::string &north, const std::string &west, const std::string &south, const std::string &east);

	/** Prepare all the T-nodes' half linkages*/
	void prepareTNodeHalfLinkages();
	/** Prepare all T-junctions*/
	void prepareTJunctions();
	/** Prepare all T-image connects*/
	void prepareImageConnect();

	/** Find the names of T-objects of the specified type*/
	void findTObjectNames(std::vector<std::string> &names, TObjType type);
	/** Find the T-spline*/
	TSplinePtr findTSpline();
	/** Find the T-group*/
	TGroupPtr findTGroup();
protected:
	template<class T>
	std::shared_ptr<T> createTObject(const std::string &name)
	{
		std::shared_ptr<T> obj = makePtr<T>(name);
		_objects->addObject(obj);
		obj->setCollector(_objects);
		return obj;
	}

public:
	template<class T>
	std::shared_ptr<T> findTObject(const std::string& name)
	{
		TObjectPtr object = _finder->findObjectByName(name);
		if (object)
		{
			return castPtr<T>(object);
		}
		return 0;
	}

	template<class T>
	std::shared_ptr<T> findTObjectById(int id)
	{
		TObjectPtr object = _finder->findObjectById(id);
		if (object)
		{
			return castPtr<T>(object);
		}
		return 0;
	}

	TLinkPtr findTLinkByStartEndVertices(const TVertexPtr &start, const TVertexPtr &end);
private:
	TGroupPtr _objects;
	TFinderPtr _finder;
	static std::vector<std::string> _empty_nodes;
};

#ifdef use_namespace
}
#endif


#endif