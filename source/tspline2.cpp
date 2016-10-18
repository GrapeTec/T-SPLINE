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

#include <tspline2.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

TVertex2::TVertex2( const std::string & name /*= ""*/, Real r /*= 0.0*/, Real s /*= 0.0*/, Real t /*= 0.0*/ ) :
	TVertex(name, s, t), _r(r)
{

}

void TVertex2::setNeighbours( const TLinkPtr &up, const TLinkPtr &down, const TLinkPtr &north, const TLinkPtr &west, const TLinkPtr &south, const TLinkPtr &east )
{
	setUp(up); setDown(down);
	TVertex::setNeighbours(north, west, south, east);
}

TLinkPtr TVertex2::checkNeighborhood( const TVertexPtr &vertex )
{
	if (!vertex) return 0;
	if (vertex == getEndVertex(getNorth())) return getNorth();
	if (vertex == getEndVertex(getWest())) return getWest();
	if (vertex == getEndVertex(getSouth())) return getSouth();
	if (vertex == getEndVertex(getEast())) return getEast();
	if (vertex == getEndVertex(getUp())) return getUp();
	if (vertex == getEndVertex(getDown())) return getDown();
}

int TVertex2::numberOfNeighbors() const
{
	int number = 0;
	if (getNorth()) number++;
	if (getWest()) number++;
	if (getSouth()) number++;
	if (getNorth()) number++;
	if (getUp()) number++;
	if (getDown()) number++;
	return number;
}

TVertexPtr TVertex2::getUpTVertex() const
{
	if (_up)
	{
		return _up->getEndVertex();
	}
	else
	{
		return 0;
	}
}

TVertexPtr TVertex2::getDownTVertex() const
{
	if (_down)
	{
		return _down->getEndVertex();
	}
	else
	{
		return 0;
	}
}

Real TVertex2::thickness()
{
	return 0.0;
}

Real TVertex2::volumn()
{
	return 0.0;
}

Parameter2 TVertex2::northWestUp()
{
	return Parameter2(getR(), getS(), getT());
}

Parameter2 TVertex2::southEastDown()
{
	return Parameter2(getR(), getS(), getT());
}

TEdge2::TEdge2( const std::string & name /*= ""*/ ) : TEdge(name)
{

}

bool TEdge2::toUp() const
{
	TVertex2Ptr vs = getStartVertex()->asTVertex2();
	TVertex2Ptr ve = getEndVertex()->asTVertex2();
	Real dr = ve->getR() - vs->getR();
	if (!isZero(dr))
	{
		return dr > 0.0;
	}
	else
	{
		return false;
	}
}

bool TEdge2::toDown() const
{
	TVertex2Ptr vs = getStartVertex()->asTVertex2();
	TVertex2Ptr ve = getEndVertex()->asTVertex2();
	Real dr = ve->getR() - vs->getR();
	if (!isZero(dr))
	{
		return dr < 0.0;
	}
	else
	{
		return false;
	}
}

TFacePtr TLink2::getAboveFace() const
{
	TEdge2Ptr edge = getTEdge()->asTEdge2();
	if (edge)
	{
		if (getOrientation())
		{
			return edge->getAboveFace();
		}
		else
		{
			return edge->getBelowFace();
		}
	}
	else
	{
		return 0;
	}
}

TFacePtr TLink2::getBelowFace() const
{
	TEdge2Ptr edge = getTEdge()->asTEdge2();
	if (edge)
	{
		if (getOrientation())
		{
			return edge->getBelowFace();
		}
		else
		{
			return edge->getAboveFace();
		}
	}
	else
	{
		return 0;
	}
}

bool TLink2::toUp() const
{
	TEdge2Ptr edge = getTEdge()->asTEdge2();
	if (edge)
	{
		if (getOrientation())
		{
			return edge->toUp();
		}
		else
		{
			return edge->toDown();
		}
	}
	return false;
}

bool TLink2::toDown() const
{
	TEdge2Ptr edge = getTEdge()->asTEdge2();
	if (edge)
	{
		if (getOrientation())
		{
			return edge->toDown();
		}
		else
		{
			return edge->toUp();
		}
	}
	return false;
}

bool TFace2::inXPlane() const
{
	return false;
}

bool TFace2::inYPlane() const
{
	return false;
}

bool TFace2::inZPlane() const
{
	return false;
}

TBox::TBox( const std::string & name /*= ""*/ ) :
	TMappableObject(name)
{

}

void TBox::addFace( const TFace2Ptr face )
{
	_faces.push_back(face);
}

void TBox::addBlendingNode( const TNodePtr node )
{
	_blending_nodes.push_back(node);
}

void TBox::findUpFaces( TFac2Vector &faces )
{

}

void TBox::findDownFaces( TFac2Vector &faces )
{

}

void TBox::findNorthFaces( TFac2Vector &faces )
{

}

void TBox::findWestFaces( TFac2Vector &faces )
{

}

void TBox::findSouthFaces( TFac2Vector &faces )
{

}

void TBox::findEastFaces( TFac2Vector &faces )
{

}

void TBox::findUpBoxes( TBoxVector &boxes )
{

}

void TBox::findDownBoxes( TBoxVector &boxes )
{

}

void TBox::findNorthBoxes( TBoxVector &boxes )
{

}

void TBox::findWestBoxes( TBoxVector &boxes )
{

}

void TBox::findSouthBoxes( TBoxVector &boxes )
{

}

void TBox::findEastBoxes( TBoxVector &boxes )
{

}

TImage2::TImage2( const std::string & name /*= ""*/ ) : TImage(name)
{

}

void TImage2::addBox( const TBoxPtr &box )
{
	_boxes.push_back(box);
}

TBoxVIterator TImage2::boxIteratorBegin()
{
	return _boxes.begin();
}

TBoxVIterator TImage2::boxIteratorEnd()
{
	return _boxes.end();
}

#ifdef use_namespace
}
#endif