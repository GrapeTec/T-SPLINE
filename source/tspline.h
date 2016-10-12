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
2016/04/02: Wenlei Xiao
- Doxygen comments added.
-------------------------------------------------------------------------------
*/

/**  @file  [tspline]  
  *  @brief  T-objects definitions (The core)
  *  @author  <Wenlei Xiao>  
  *  @date  <2015.04.08>  
  *  @version  <v1.0>  
  *  @note  
  *  This file contains the most basic definitions of T-objects.
*/

#ifndef __cplusplus
#error Must use C++ for the spline
#endif
#ifndef TSPLINE_H
#define TSPLINE_H

#include <basis.h>

#ifdef use_namespace
namespace TSPLINE {
  using namespace NEWMAT;
#endif

DECLARE_ASSISTANCES(TObject, TObj)
DECLARE_ASSISTANCES(TGroup, TGrp) 
DECLARE_ASSISTANCES(TMappableObject, TMapObj)
DECLARE_ASSISTANCES(TVertex, TVtx) 
DECLARE_ASSISTANCES(TEdge, TEdg) 
DECLARE_ASSISTANCES(TLink, TLnk)
DECLARE_ASSISTANCES(TEdgeCondition, TEdgCon)
DECLARE_ASSISTANCES(TFace, TFac)
DECLARE_ASSISTANCES(TImage, TImg)
DECLARE_ASSISTANCES(TNode, TNod)
DECLARE_ASSISTANCES(TNodeV4, TNodV4) 
DECLARE_ASSISTANCES(TPoint, TPnt)
DECLARE_ASSISTANCES(TSpline, TSpl) 
DECLARE_ASSISTANCES(TConnect, TCnt)
DECLARE_ASSISTANCES(TPointset, TPts) 

DECLARE_ASSISTANCES(TLinkLoop, TLnkLup) 

enum TObjType {E_TOBJECT, E_TGROUP, E_MAPPABLEOBJECT, E_TVERTEX, E_TEDGE, E_TLINK, 
	E_TEDGECONDITION, E_TFACE, E_TIMAGE, E_TNODE, E_TNODEV4, E_TCONNECT,
	E_TPOINT, E_TPOINTSET, E_TSPLINE};

enum TDirection {E_CENTER, E_NORTH, E_WEST, E_SOUTH, E_EAST};

/**  
  *  @class  <TObject> 
  *  @brief  Base class for all T-objects  
  *  @note  
  *  Any T-objects can be pointed by a TObject pointer. 
*/
class TObject : public std::enable_shared_from_this<TObject>
{
	friend class TGroup;

public:
	TObject(const std::string & name = "");
	virtual ~TObject();
	TObject & operator=(const TObject & x);
	typedef TObjectTag TCategory;
public:
	/** Check if this object is a TObject */
	virtual TObjectPtr asTObject();
	/** Check if this object is a TGroup */
	virtual TGroupPtr asTGroup() { return 0; }
	/** Check if this object is a TMappableObject */
	virtual TMappableObjectPtr asTMappableObject() { return 0; }
	/** Check if this object is a TVertex */
	virtual TVertexPtr asTVertex() { return 0; }
	/** Check if this object is a TEdge */
	virtual TEdgePtr asTEdge() { return 0; }
	/** Check if this object is a TLink */
	virtual TLinkPtr asTLink() { return 0; }
	/** Check if this object is a TEdgeCondition */
	virtual TEdgeConditionPtr asTEdgeCondition() { return 0; }
	/** Check if this object is a TFace */
	virtual TFacePtr asTFace() { return 0; }
	/** Check if this object is a TImage */
	virtual TImagePtr asTImage() { return 0; }
	/** Check if this object is a TNode */
	virtual TNodePtr asTNode() { return 0; }
	// fixed has no member named "asTConnect"
	virtual TConnectPtr asTConnect() { return 0; }
	/** Check if this object is a TPoint */
	virtual TPointPtr asTPoint() { return 0; }
	// fixed has no member named "asTPointSet"
	virtual TPointsetPtr asTPointset() { return 0; }
	/** Check if this object is a TSpline */
	virtual TSplinePtr asTSpline() { return 0; }
	/** Check if this object is virtual */
	virtual bool isVirtual() { return false; }

	/** Set the name of this object */
	void setName (const std::string & name) { _name = name; }
	/** Get the name of this object */
	const std::string getName() const { return _name; }
	/** Set the logical ID number of this object */
	void setId(int id) { _logical_id = id; }
	/** Get the logical ID number of this object */
	const unsigned int getId() const { return _logical_id; }

	/** Set the collector which contains this object */
	void setCollector(const TGroupPtr &collector) { _collector = collector; }
	/** Get the collector which contains this object */
	TGroupPtr getCollector() { return _collector; }
//private:
	/** Get the physical ID number */
	const unsigned int getPhysicalId() const { return _physical_id; }

private:
	std::string _name;
	unsigned int _physical_id;
	unsigned int _logical_id;
	static int _obj_count;
	TGroupPtr _collector;
};

/**  
  *  @class  <TGroup> 
  *  @brief  T-group class
  *  @note  
  *  TGroup can be used to hold a set of T-objects using the composition pattern.
*/
class TGroup : public TObject
{
public:
	TGroup(const std::string & name = "");
	virtual ~TGroup();
	typedef TGroupTag TCategory;
public:
	/** Return a smart pointer TGroupPtr to this object.*/
	virtual TGroupPtr asTGroup();
	/** Check if the object is a TConnect.*/
	virtual TConnectPtr asTConnect() { return 0; }
	/** Check if the object is a TPointset.*/
	virtual TPointsetPtr asTPointset() { return 0; }

	/** Add an T-object.*/
	bool addObject(const TObjectPtr & object);
	/** Insert an T-object into the indexed position.*/
	bool insertObject(unsigned int index, const TObjectPtr & object);
	/** Remove an T-object.*/
	bool removeObject(const TObjectPtr & object );
	/** Remove [num] T-objects from the position [pos].*/
	bool removeObject(unsigned int pos, unsigned int num = 1);
	/** Replace an T-object with a new one.*/
	bool replaceObject(const TObjectPtr & old_object, \
		const TObjectPtr & new_object);
	/** Return the number of T-objects.*/
	unsigned int size() const;
	/** Return the begin iterator of T-objects.*/
	TObjVIterator iteratorBegin();
	/** Return the end iterator of T-objects.*/
	TObjVIterator iteratorEnd();
		
private:
	struct IdFinder
	{
		IdFinder(const unsigned int id) : _id(id) {}
		bool operator() (TObjectPtr object)
		{
			if (object)
			{
				return object->_physical_id == _id;
			}
			else
			{
				return false;
			}
		}
		unsigned int _id;
	};
	struct NameFinder
	{
		NameFinder(const string &name) : _name(name) {}
		bool operator() (TObjectPtr object)
		{
			if (object)
			{
				return object->_name == _name;
			}
			else
			{
				return false;
			}
		}
		std::string _name;
	};
	struct TypeFinder
	{
		TypeFinder(const TObjType type) : _type(type) {}
		bool operator() (TObjectPtr object)
		{
			if (object)
			{
				switch (_type)
				{
				case TSPLINE::E_TOBJECT:
					return true;
					break;
				case TSPLINE::E_TGROUP:
					return castBool(object->asTGroup());
					break;
				case TSPLINE::E_MAPPABLEOBJECT:
					return castBool(object->asTMappableObject());
					break;
				case TSPLINE::E_TVERTEX:
					return castBool(object->asTVertex());
					break;
				case TSPLINE::E_TEDGE:
					return castBool(object->asTEdge());
					break;
				case TSPLINE::E_TLINK:
					return castBool(object->asTLink());
					break;
				case TSPLINE::E_TEDGECONDITION:
					return castBool(object->asTEdgeCondition());
					break;
				case TSPLINE::E_TFACE:
					return castBool(object->asTFace());
					break;
				case TSPLINE::E_TIMAGE:
					return castBool(object->asTImage());
					break;
				case TSPLINE::E_TNODE:
					return castBool(object->asTNode());
					break;
				case TSPLINE::E_TNODEV4:
					return castBool(object->asTNode());
					break;
				case TSPLINE::E_TPOINT:
					return castBool(object->asTPoint());
					break;
				case TSPLINE::E_TSPLINE:
					return castBool(object->asTSpline());
					break;
				default:
					return false;
					break;
				}
			}
			else
			{
				return false;
			}			
		}
		TObjType _type;
	};
private:
	TObjVector _objects;
};

/**  
  *  @class  <TMappableObject> 
  *  @brief  The mappable T-object (T-mapper)  
  *  @note  
  *  TMappableObject is the supertype of TVertex, TEdge, and TFace.
*/
class TMappableObject : public TObject
{
public:
	TMappableObject(const std::string & name = "");
	virtual ~TMappableObject();
	typedef TMappableObjectTag TCategory;
public:
	virtual TMappableObjectPtr asTMappableObject();
public:
	/** Add a T-node */
	void addNode(const TNodePtr &node);
	/** Remove a T-node */
	void removeNode(const TNodePtr &node);
	/** Return the begin iterator of the T-nodes */
	TNodVIterator nodeIteratorBegin();
	/** Return the end iterator of the T-nodes */
	TNodVIterator nodeIteratorEnd();
	/** Return the number of the T-nodes */
	long sizeNodes();
	
public:
	/** Width of the T-mapper. */
	virtual Real width() = 0;
	/** Height of the T-mapper. */
	virtual Real height() = 0;
	/** Area of the T-mapper. */
	virtual Real area() = 0;
	/** Northwest parameter of the T-mapper. */
	virtual Parameter northWest() = 0;
	/** Southeast parameter of the T-mapper. */
	virtual Parameter southEast() = 0;
private:
	TNodVector _nodes;
};

/**  
  *  @class  <TVertex> 
  *  @brief  T-vertex class 
  *  @note  
  *  TVertex contains a parametric coordinate (s, t).
*/
class TVertex : public TMappableObject
{
    friend class TEdge;
    friend class TLink;
    friend class TFace;
	friend class TImage;

public:
   TVertex(const std::string & name = "", 
	   Real s = 0.0, 
	   Real t = 0.0);
   virtual ~TVertex(){}
   typedef TVertexTag TCategory;
public:
	virtual TVertexPtr asTVertex();

	/** Return the s parameter. */
	Real getS(void) const {return _s; }
	/** Return the t parameter. */
	Real getT(void) const { return _t; }
	/** Set the s and t parameters. */
	void setST(Real s, Real t) { _s = s; _t = t; }
	/** Return the north link. */
	TLinkPtr getNorth(void) const { return _north; }
	/** Return the west link. */
	TLinkPtr getWest(void) const { return _west; }
	/** Return the south link. */
	TLinkPtr getSouth(void) const { return _south; }
	/** Return the east link. */
	TLinkPtr getEast(void) const { return _east; }
	/** Set the north link. */
	void setNorth(const TLinkPtr &north);
	/** Set the west link. */
	void setWest(const TLinkPtr &west);
	/** Set the south link. */
	void setSouth(const TLinkPtr &south);
	/** Set the east link. */
	void setEast(const TLinkPtr &east);
	/** Set the neighbour links of the vertex. */
	void setNeighbours(const TLinkPtr &north, 
		const TLinkPtr &west,
		const TLinkPtr &south,
		const TLinkPtr &east);
	/** Check if the vertex is the neighborhood of the current vertex. Return the location of the vertex. */
	TLinkPtr checkNeighborhood(const TVertexPtr &vertex);
	/** Return the numbers of the neighbors. */
	int numberOfNeighbors();

	/** Return the north vertex. */
	TVertexPtr getNorthTVertex() const;
	/** Return the west vertex. */
	TVertexPtr getWestTVertex() const;
	/** Return the south vertex. */
	TVertexPtr getSouthTVertex() const;
	/** Return the east vertex. */
	TVertexPtr getEastTVertex() const;
	
public:
	/** Width of the T-vertex. */
	virtual Real width();
	/** Height of the T-vertex. */
	virtual Real height();
	/** Area of the T-vertex. */
	virtual Real area();
	/** Northwest parameter of the T-vertex. */
	virtual Parameter northWest();
	/** Southeast parameter of the T-vertex. */
	virtual Parameter southEast();

protected:
	TVertexPtr getEndVertex(const TLinkPtr &link);
private:
   Real _s,			
        _t;			
   TLinkPtr _north;	
   TLinkPtr _west;	
   TLinkPtr _south;	
   TLinkPtr _east;	
};

/**  
  *  @class  <TEdge> 
  *  @brief  T-edge class
  *  @note  
  *  TEdge contains its start and end T-vertices and left and right T-faces.
*/ 
class TEdge : public TMappableObject
{
   friend class TLink;
   friend class TVertex;
   friend class TFace;
   friend class TImage;
public:
   TEdge(const std::string & name = "");
   ~TEdge(){}
   typedef TEdgeTag TCategory;
public:
	virtual TEdgePtr asTEdge();
	/** Return the start T-vertex of the T-edge. */
    TVertexPtr getStartVertex() const { return _start; } 
	/** Return the end T-vertex of the T-edge. */
    TVertexPtr getEndVertex() const { return _end; } 
	/** Return the left T-face of the T-edge. */
    TFacePtr getLeftFace() const { return _left; } 
	/** Return the right T-face of the T-edge. */
    TFacePtr getRightFace() const { return _right; } 
	/** Return the T-vertex by the orientation. */
	TVertexPtr getNextVertex(bool orientation) const;

	/** Set the start T-vertex of the T-edge. */
	void setStartVertex(const TVertexPtr &start) { _start = start; }
	/** Set the end T-vertex of the T-edge. */
	void setEndVertex(const TVertexPtr &end) { _end = end; }
	/** Set the left T-face of the T-edge. */
	void setLeftFace(const TFacePtr &left) { _left = left; }
	/** Set the right T-face of the T-edge. */
	void setRightFace(const TFacePtr &right) { _right = right; }

	/** Set the boundary flag of the T-edge. */
	void setBoundary(bool condition) { _boundary = condition; }
	/** Check if the T-edge is boundary. */
	bool isBoundary() const {return _boundary;}

	/** Return the length of the T-edge. */
	Real length();
	/** Check if the orientation of T-edge is north. */
	bool toNorth();
	/** Check if the orientation of T-edge is west. */
	bool toWest();
	/** Check if the orientation of T-edge is south. */
	bool toSouth();
	/** Check if the orientation of T-edge is east. */
	bool toEast();
public:
	/** Width of the T-vertex. */
	virtual Real width();
	/** Height of the T-vertex. */
	virtual Real height();
	/** Area of the T-vertex. */
	virtual Real area();
	/** Northwest parameter of the T-vertex. */
	virtual Parameter northWest();
	/** Southeast parameter of the T-vertex. */
	virtual Parameter southEast();
private:
	TVertexPtr _start;	
	TVertexPtr _end;	
	TFacePtr _left;		
	TFacePtr _right;	
	bool _boundary;		
};

/**  
  *  @class  <TLink> 
  *  @brief  definition of TLink  
  *  @note  
  *  TLink contains a pointer to a T-edge and defines the orientation. 
*/
class TLink : public TObject
{
public:
   TLink( const std::string & name = "");
   ~TLink(){}   //!< Destructor.
   typedef TLinkTag TCategory;
public:
	virtual TLinkPtr asTLink();

	/** Return the T-edge attaching the T-link. */
	inline TEdgePtr getTEdge() { return _edge; }
	/** Return the orientation of the T-link. */
	inline bool getOrientation() { return _orientation; }
	/** Set the T-edge and orientation of the T-link. */
	void setOrientedEdge(const TEdgePtr &edge, bool orientation = true);

	/** Return the start T-vertex of the T-link. */
	TVertexPtr getStartVertex() const;
	/** Return the end T-vertex of the T-link. */
	TVertexPtr getEndVertex() const;
	/** Return the left T-face of the T-link. */
	TFacePtr getLeftFace() const;
	/** Return the right T-face of the T-link. */
	TFacePtr getRightFace() const;

	/** Check if the T-link is on boundary. */
	bool isBoundary() const;

	/** Get the length of the T-link. */
	Real length() const;
	/** Check if the T-link is to the north. */
	bool toNorth();
	/** Check if the T-link is to the west. */
	bool toWest();
	/** Check if the T-link is to the south. */
	bool toSouth();
	/** Check if the T-link is to the east. */
	bool toEast();
private:
	TEdgePtr _edge;		//!< Attached T-edge.
	bool _orientation;	//!< Orientation.
};

/**  
  *  @class  <TLinkLoop> 
  *  @brief  The T-link loop class  
  *  @note  
  *  TLinkLoop is used to manage a closed loop of T-links.
*/
class TLinkLoop
{
public:
	TLinkLoop();
	~TLinkLoop();
	typedef TLinkLoopTag TCategory;
public:
	/** Add a T-link to the T-link loop. */
	void addLink(const TLinkPtr &link);
	/** Find all the to north T-links in the T-link loop. */
	void findNorthLinks(TLnkVector &north_links);
	/** Find all the to west T-links in the T-link loop. */
	void findWestLinks(TLnkVector &west_links);
	/** Find all the to south T-links in the T-link loop. */
	void findSouthLinks(TLnkVector &south_links);
	/** Find all the to east T-links in the T-link loop. */
	void findEastLinks(TLnkVector &east_links);

	/** Return the number of the T-links. */
	long size();
	/** Return the begin iterator of the T-link loop. */
	TLnkLIterator linkIteratorBegin();
	/** Return the end iterator of the T-link loop. */
	TLnkLIterator linkIteratorEnd();
protected:
	void organize();
private:
	TLnkList _links;	
};

/**  
  *  @class  <TFace> 
  *  @brief  T-face class
  *  @note  
  *  TFace contains a T-link loop and related T-nodes used for the blending calculation. 
*/
class TFace : public TMappableObject
{
public:
	TFace(const std::string & name = "");
	TFace(TLinkPtr , ...);
	virtual ~TFace(){}
	typedef TFaceTag TCategory;
public:
	virtual TFacePtr asTFace();

	/** Add link to the T-face. */
	void addLink(const TLinkPtr link);
	/** Add blending T-node to the T-face. */
	void addBlendingNode(const TNodePtr node);

	/** Find all the to north T-links in the T-face. */
	void findNorthLinks(TLnkVector &links);
	/** Find all the to west T-links in the T-face. */
	void findWestLinks(TLnkVector &links);
	/** Find all the to south T-links in the T-face. */
	void findSouthLinks(TLnkVector &links);
	/** Find all the to east T-links in the T-face. */
	void findEastLinks(TLnkVector &links);

	/** Find all the north T-faces adjacent to the T-face. */
	virtual void findNorthFaces(TFacVector &faces);
	/** Find all the west T-faces adjacent to the T-face. */
	virtual void findWestFaces(TFacVector &faces);
	/** Find all the south T-faces adjacent to the T-face. */
	virtual void findSouthFaces(TFacVector &faces);
	/** Find all the east T-faces adjacent to the T-face. */
	virtual void findEastFaces(TFacVector &faces);

	/** Return the number of T-links in the T-link loop. */
	long sizeLinks();
	/** Return the size of the blending T-nodes belong to the T-face. */
	long sizeBlendingNodes();
	/** Get the T-link loop. */
	TLinkLoopPtr getLinkLoop() {return _link_loop;}
	/** Return the begin iterator of the T-link loop. */
	TLnkLIterator linkIteratorBegin();
	/** Return the end iterator of the T-link loop. */
	TLnkLIterator linkIteratorEnd();
	/** Return the begin iterator of the blending T-nodes. */
	TNodVIterator blendingNodeIteratorBegin();
	/** Return the end iterator of the blending T-nodes. */
	TNodVIterator blendingNodeIteratorEnd();

public:
	/** Get the width of the T-face. */
	virtual Real width();
	/** Get the height of the T-face. */
	virtual Real height();
	/** Get the area of the T-face. */
	virtual Real area();
	/** Get the northwest parameter of the T-face. */
	virtual Parameter northWest();
	/** Get the southeast parameter of the T-face. */
	virtual Parameter southEast();

protected:
	void findRightFaces(const TLnkVector &links, TFacVector &faces);
private:
	TLinkLoopPtr _link_loop;		
	TNodVector _blending_nodes;		
};

/**  
  *  @class  <TEdgeCondition> 
  *  @brief  T-edge condition class
  *  @note  
  *  TEdgeCondition is used to identify if a T-edge is on boundary.
*/
class TEdgeCondition : public TObject 
{
public:
   TEdgeCondition(const std::string & name = "");
   ~TEdgeCondition(){}
   typedef TEdgeConditionTag TCategory;
public:
	virtual TEdgeConditionPtr asTEdgeCondition();

	/** Set the boundary condition of the T-edge. */
	void setEdgeCondition(const TEdgePtr &edge, bool boundary_condition);
	/** Get the T-edge. */
	TEdgePtr getEdge();
	/** Get the boundary condition. */
	bool getBoundaryCondtion();

private:
	TEdgePtr _edge;				
	bool _boundary_condition;	
};


/**  
  *  @class  <TImage> 
  *  @brief  T-image class
  *  @note  
  *  TImage is the entry object to access T-objects on the parametric layer. 
*/
class TImage : public TObject 
{
public:
   TImage(const std::string & name = "");
   ~TImage(){}
   typedef TImageTag TCategory;
public:
	virtual TImagePtr asTImage();

	/** Add a T-face to the T-image. */
	void addFace(const TFacePtr &face);
	/** Add a T-edge to the T-image. */
	void addEdge(const TEdgePtr &edge);
	/** Add a T-link to the T-image. */
	void addLink(const TLinkPtr &link);
	/** Add a T-vertex to the T-image. */
	void addVertex(const TVertexPtr &vertex);
	
	/** Return the number of T-faces. */
	int sizeFaces();
	/** Return the number of T-edges. */
	int sizeEdges();
	/** Return the number of T-links. */
	int sizeLinks();
	/** Return the number of T-vertices. */
	int sizeVertices();

	/** Return the begin iterator of T-faces. */
	TFacVIterator faceIteratorBegin();
	/** Return the end iterator of T-faces. */
	TFacVIterator faceIteratorEnd();
	/** Return the begin iterator of T-edges. */
	TEdgVIterator edgeIteratorBegin();
	/** Return the end iterator of T-edges. */
	TEdgVIterator edgeIteratorEnd();
	/** Return the begin iterator of T-links. */
	TLnkVIterator linkIteratorBegin();
	/** Return the end iterator of T-links. */
	TLnkVIterator linkIteratorEnd();
	/** Return the begin iterator of T-vertices. */
	TVtxVIterator vertexIteratorBegin();
	/** Return the end iterator of T-vertices. */
	TVtxVIterator vertexIteratorEnd();

private:
	TFacVector _faces;		
	TEdgVector _edges;		
	TLnkVector _links;		
	TVtxVector _vertices;	
};

class TNodeV4;
/**  
  *  @class  <TNode> 
  *  @brief  T-node class
  *  @note  
  *  TNode is used to connect a T-mapper and a T-point.
*/
class TNode : public TObject 
{
	friend class TMapper;
	friend class TPoint;
public:
   TNode(const std::string & name = "");
   virtual ~TNode(){}
   typedef TNodeTag TCategory;
public:
	virtual TNodePtr asTNode();
	virtual TNodeV4Ptr asTNodeV4() { return 0; }

	/** Get the T-mapper. */
	TMappableObjectPtr getTMapper() {return _mapper;}

	/** Get the T-mapper as a T-vertex. */
	TVertexPtr getTVertex() {return _mapper->asTVertex();}
	/** Get the T-mapper as a T-edge. */
	TEdgePtr getTEdge() {return _mapper->asTEdge();}
	/** Get the T-mapper as a T-face. */
	TFacePtr getTFace() {return _mapper->asTFace();}
	/** Get the T-point. */
	TPointPtr getTPoint() {return _point;}

	/** Set the T-mapper. */
	void setTMappableObject(const TMappableObjectPtr &mapper);
	/** Set the T-mapper as a T-vertex. */
	void setTVertex(const TVertexPtr &vertex);
	/** Set the T-mapper as a T-edge. */
	void setTEdge(const TEdgePtr &edge);
	/** Set the T-mapper as a T-face. */
	void setTFace(const TFacePtr &face);
	/** Set the T-point. */
	void setTPoint(const TPointPtr &point);
private:
	TMappableObjectPtr _mapper;	
	TPointPtr _point;			
};

/**  
  *  @class  <TNodeV4> 
  *  @brief  T-node valence 4 class
  *  @note  
  *  TNodeV4 inherits from a TNode and contains four pointers to its adjacent T-nodes.
*/
class TNodeV4 : public TNode 
{
public:
   TNodeV4(const std::string & name = "");
   ~TNodeV4(){}    //!< Destructor.
   typedef TNodeV4Tag TCategory;
public:
	virtual TNodeV4Ptr asTNodeV4();

	/** Get the north T-node. */
	TNodeV4Ptr getNorth() { return _north; }
	/** Get the west T-node. */
	TNodeV4Ptr getWest() { return _west; }
	/** Get the south T-node. */
	TNodeV4Ptr getSouth() { return _south; }
	/** Get the east T-node. */
	TNodeV4Ptr getEast() { return _east; } 
	/** Set the north T-node. */
	void setNorth(const TNodeV4Ptr &node) { _north = node; }
	/** Set the west T-node. */
	void setWest(const TNodeV4Ptr &node) { _west = node; }
	/** Set the south T-node. */
	void setSouth(const TNodeV4Ptr &node) { _south = node; }
	/** Set the east T-node. */
	void setEast(const TNodeV4Ptr &node) { _east = node; }

	/** Set the neighbors. */
	void setNeighbours(const TNodeV4Ptr north,
		const TNodeV4Ptr west, const TNodeV4Ptr south,
		const TNodeV4Ptr east);
private:
	TNodeV4Ptr _north;	
	TNodeV4Ptr _west;	
	TNodeV4Ptr _south;	
	TNodeV4Ptr _east;	
};

/**  
  *  @class  <TConnect> 
  *  @brief  T-connect class
  *  @note  
  *  TConnect inherits from the TGroup and contains the T-objects on the topological layer.
*/
class TConnect : public TGroup 
{
	friend class TVertex;
	friend class TPoint;
public:
   TConnect(const std::string & name = "");
   ~TConnect(){}
   typedef TConnectTag TCategory;

public:
	virtual TConnectPtr asTConnect();
};

/**  
  *  @class  <TPoint> 
  *  @brief  T-point class
  *  @note  
  *  TPoint contains a coordinate (x, y, z) and a weight w. Additionally, it gives the pointer to its corresponding T-node.
*/
class TPoint : public TObject 
{
	friend class TNode;
	friend class TPointset;
public:
   TPoint(const std::string & name = "", Real x = 0.0, Real y = 0.0, Real z = 0.0, Real w = 1.0);
   ~TPoint(){}    //!< Destructor.
   typedef TPointTag TCategory;
public:
	virtual TPointPtr asTPoint();

	/** Get the coordinate x. */
	inline Real getX() const { return _x; }
	/** Get the coordinate y. */
	inline Real getY() const { return _y; }
	/** Get the coordinate z. */
	inline Real getZ() const { return _z; }
	/** Get the weight w. */
	inline Real getW() const { return _w; }
	/** Set the coordinate with weight. */
	inline void setXYZW(Real x, Real y, Real z, Real w) 
	{ _x = x; _y = y; _z = z; _w = w; }
	/** Get the T-node. */
	inline TNodePtr getTNode()
	{ return _node; }
	/** Set the T-node. */
	inline void setTNode(const TNodePtr node)
	{ _node = node; }
private:
	Real _x, _y, _z, _w;	
	TNodePtr _node;			
};

/**  
  *  @class  <TPointset> 
  *  @brief  T-pointset class  
  *  @note  
  *  TPointset inherits from the TGroup and contains the T-objects on the Cartesian layer.
*/
class TPointset : public TGroup 
{
	friend class TPoint;
	friend class TSpline;
public:
   TPointset(const std::string & name = "");
   ~TPointset(){}
   typedef TPointsetTag TCategory;
public:
	virtual TPointsetPtr asTPointset();
};


/**  
  *  @class  <TSpline> 
  *  @brief  T-spline class
  *  @note  
  *  TSpline contains all the properties and parameters related to a T-spline surface.
*/
class TSpline : public TObject 
{
public:
   TSpline(const std::string & name = "", int degree = 3,
	   bool force_bezier_end_condition = false);
   ~TSpline(){}
   typedef TSplineTag TCategory;
public:
	virtual TSplinePtr asTSpline();

	/** Get the s degree. */
	inline int getSDegree() {return _s_degree; }
	/** Set the s degree. */
	inline void setSDegree(int degree) { _s_degree = degree; }
	/** Get the t degree. */
	inline int getTDegree() {return _t_degree; }
	/** Set the s degree. */
	inline void setTDegree(int degree) { _t_degree = degree; }
	/** Get the Bezier end condition flag. */
	inline bool getForceBezierEndCondition() {return _force_bezier_end_condition; }
	/** Set the Bezier end condition flag. */
	inline void setForceBezierEndCondition(bool force_bezier_end_condition) {_force_bezier_end_condition = force_bezier_end_condition;}

	/** Get the T-image. */
	inline TImagePtr getTImage() { return _image; }
	/** Set the T-image. */
	inline void setTImage(const TImagePtr &image) { _image = image; }
	/** Get the T-connect. */
	inline TConnectPtr getTConnect() { return _connect; }
	/** Set the T-connect. */
	inline void setTConnect(const TConnectPtr &node_grid) { _connect = node_grid; } 
	/** Get the T-pointset. */
	inline TPointsetPtr getTPointset() { return _pointset; }
	/** Set the T-pointset. */
	inline void setTPointset(const TPointsetPtr &point_grid) { _pointset = point_grid; }

private:
	int _s_degree;						
	int _t_degree;						
	bool _force_bezier_end_condition;	
	TImagePtr _image;					
	TConnectPtr _connect;				
	TPointsetPtr _pointset;				
};

#ifdef use_namespace
}
#endif

#endif 

