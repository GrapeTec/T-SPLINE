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

/**  @file  [tspline3d]  
  *  @brief  T-objects definitions (The core)
  *  @author  <Wenlei Xiao>  
  *  @date  <2016.10.15>  
  *  @version  <v1.0>  
  *  @note  
  *  This file contains the most basic definitions of T-objects.
*/

#ifndef __cplusplus
#error Must use C++ for the spline
#endif
#ifndef TSPLINE2_H
#define TSPLINE2_H

#include <basis2.h>
#include <tspline.h>

#ifdef use_namespace
namespace TSPLINE {
  using namespace NEWMAT;
#endif

class TVertex2 : public TVertex
{
	friend class TLink2;
public:
	TVertex2(const std::string & name = "", 
		Real r = 0.0,
		Real s = 0.0, 
		Real t = 0.0);
	virtual ~TVertex2() {}
public:
	virtual TVertex2Ptr asTVertex2() { return castPtr<TVertex2>(shared_from_this()); }

	/** Return the r parameter. */
	Real getR(void) const { return _r; }
	void SetRST(Real r, Real s, Real t) { _r = r; setST(s, t); }

	/** Return the up link. */
	TLinkPtr getUp(void) const { return _up; }
	/** Return the down link. */
	TLinkPtr getDown(void) const { return _down; }

	/** Set the north link. */
	void setUp(const TLinkPtr &up) { _up = up; }
	/** Set the west link. */
	void setDown(const TLinkPtr &down) { _down = down; }

	/** Set the neighbour links of the vertex. */
	void setNeighbours( const TLinkPtr &up,
		const TLinkPtr &down,
		const TLinkPtr &north, 
		const TLinkPtr &west,
		const TLinkPtr &south,
		const TLinkPtr &east);

	/** Check if the vertex is the neighborhood of the current vertex. Return the location of the vertex. */
	virtual TLinkPtr checkNeighborhood(const TVertexPtr &vertex);
	/** Return the numbers of the neighbors. */
	virtual int numberOfNeighbors() const;
	
	/** Return the up vertex. */
	TVertexPtr getUpTVertex() const;
	/** Return the west vertex. */
	TVertexPtr getDownTVertex() const;

public:
	/** Thickness of the T-vertex. */
	virtual Real thickness();
	virtual Real volumn();
	virtual Parameter2 northWestUp();
	virtual Parameter2 southEastDown();
private:
	Real _r;
	TLinkPtr _up;
	TLinkPtr _down;
};

class TEdge2 : public TEdge
{
public:
	TEdge2(const std::string & name = "");
	virtual ~TEdge2(){}
public:
	virtual TEdge2Ptr asTEdge2() { return castPtr<TEdge2>(shared_from_this()); }

	/** Return the above T-face of the T-edge. */
	TFacePtr getAboveFace() const { return _above; } 
	/** Return the below T-face of the T-edge. */
	TFacePtr getBelowFace() const { return _below; } 

	/** Set the above T-face of the T-edge. */
	void setAboveFace(const TFacePtr &above) { _above = above; }
	/** Set the below T-face of the T-edge. */
	void setBelowFace(const TFacePtr &below) { _below = below; }

	/** Check if the orientation of T-edge is up. */
	bool toUp() const;
	/** Check if the orientation of T-edge is down. */
	bool toDown() const;
private:
	TFacePtr _above;
	TFacePtr _below;
};

class TLink2 : public TLink
{
public:
	TLink2(const std::string & name = "");
	virtual ~TLink2() {}
public:
	virtual TLink2Ptr asTLink2() { return castPtr<TLink2>(shared_from_this()); }
	/** Return the above T-face of the T-link. */
	TFacePtr getAboveFace() const;
	/** Return the below T-face of the T-link. */
	TFacePtr getBelowFace() const;
	/** Check if the T-link is to the up. */
	bool toUp() const;
	/** Check if the T-link is to the down. */
	bool toDown() const;
};

class TFace2 : public TFace
{
public:
	TFace2(const std::string & name = "");
	virtual ~TFace2(){}
public:
	virtual TFace2Ptr asTFace2() { return castPtr<TFace2>(shared_from_this()); }

	/** Check if the T-face is in x-plane. */
	bool inXPlane() const;
	/** Check if the T-face is in y-plane. */
	bool inYPlane() const;
	/** Check if the T-face is in z-plane. */
	bool inZPlane() const;
private:

};

/**  
  *  @class  <TBox> 
  *  @brief  T-box class
  *  @note  
  *  TBox contains a set of T-faces. 
*/
class TBox : public TMappableObject
{
public:
	TBox(const std::string & name = "");
	virtual ~TBox(){}
	typedef TBoxTag TCategory;
public:
	virtual TBoxPtr asTBox() { return castPtr<TBox>(shared_from_this()); }

	void addFace(const TFace2Ptr face); 
	/** Add blending T-node to the T-box. */
	void addBlendingNode(const TNodePtr node);

	/** Find all the to up T-faces in the T-box. */
	void findUpFaces(TFac2Vector &faces);
	/** Find all the to down T-faces in the T-box. */
	void findDownFaces(TFac2Vector &faces);
	/** Find all the to north T-faces in the T-box. */
	void findNorthFaces(TFac2Vector &faces);
	/** Find all the to west T-faces in the T-box. */
	void findWestFaces(TFac2Vector &faces);
	/** Find all the to south T-faces in the T-box. */
	void findSouthFaces(TFac2Vector &faces);
	/** Find all the to east T-faces in the T-box. */
	void findEastFaces(TFac2Vector &faces);

	/** Find all the up T-boxes adjacent to the T-box. */
	virtual void findUpBoxes(TBoxVector &boxes);
	/** Find all the down T-boxes adjacent to the T-box. */
	virtual void findDownBoxes(TBoxVector &boxes);
	/** Find all the north T-boxes adjacent to the T-box. */
	virtual void findNorthBoxes(TBoxVector &boxes);
	/** Find all the west T-boxes adjacent to the T-box. */
	virtual void findWestBoxes(TBoxVector &boxes);
	/** Find all the south T-boxes adjacent to the T-box. */
	virtual void findSouthBoxes(TBoxVector &boxes);
	/** Find all the east T-boxes adjacent to the T-box. */
	virtual void findEastBoxes(TBoxVector &boxes);

	/** Return the number of T-faces in the T-face set. */
	long sizeFaces() const { return _faces.size(); }
	/** Return the size of the blending T-nodes belong to the T-face. */
	long sizeBlendingNodes() const { return _blending_nodes.size(); }
private:
	TFac2Vector _faces;
	TNodVector _blending_nodes;		
};

class TImage2 : public TImage
{
public:
	TImage2(const std::string & name = "");
	virtual ~TImage2() {}
public:
	virtual TImage2Ptr asTImage2() { return castPtr<TImage2>(shared_from_this()); }

	/** Add a T-box to the T-image. */
	void addBox(const TBoxPtr &box);
	/** Return the number of T-boxes. */
	int sizeBoxes() const { return _boxes.size(); }

	/** Return the begin iterator of T-boxes. */
	TBoxVIterator boxIteratorBegin();
	/** Return the end iterator of T-boxes. */
	TBoxVIterator boxIteratorEnd();

private:
	TBoxVector _boxes;
};

#ifdef use_namespace
}
#endif

#endif 

