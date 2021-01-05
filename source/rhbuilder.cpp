/*This library is distributed in the hope that it will be useful,
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

2015/04/08: Wenlei Xiao, Yazui Liu
- Created.
2016/04/02: Yazui Liu
- Doxygen comments added.
-------------------------------------------------------------------------------
*/
#include <rhbuilder.h>

RhBuilder::RhBuilder( const string &filename )
{
	_parser = makePtr<RhParser>(filename);
	_factory = makePtr<TFactory>();

	RhTsplinePtr rhtsp = _parser->getRhTspline();
	RhImageSpreaderPtr image_spreader = makePtr<RhImageSpreader>(rhtsp, E_NORTH);
	RhConnectSpreaderPtr connect_spreader = makePtr<RhConnectSpreader>(rhtsp, image_spreader);

	createTSpline(rhtsp);
	createTImage(rhtsp);
	createTConnect(rhtsp);
	createTPointset(rhtsp);
	createTVertices(image_spreader);
	createTEdges(rhtsp);
	createTLinks(rhtsp);
	createTEdgeConditions(rhtsp);
	createTFaces(rhtsp);
	createTNodes(connect_spreader);
	createTPoints(rhtsp);
	
	patchTSpline(rhtsp);
	patchTImage(rhtsp);
	patchTConnect(rhtsp);
	patchTPointset(rhtsp);
	patchTEdges(image_spreader);
	patchTLinks(image_spreader);
	patchTEdgeConditions(rhtsp);
	patchTFaces(image_spreader);
	patchTVertices(image_spreader);
	patchTNodesAndTPoints(connect_spreader);

	prepareTObjects();
}

RhBuilder::~RhBuilder()
{

}

TSplinePtr RhBuilder::buildTSpline(const RhTsplinePtr &rhtsp)
{
	return 0;
}

void RhBuilder::createTSpline(const RhTsplinePtr &rhtsp)
{
	_factory->createTSpline(rhtsp->filename);
}

void RhBuilder::createTImage(const RhTsplinePtr &rhtsp)
{
	_factory->createTImage("image");
}

void RhBuilder::createTConnect(const RhTsplinePtr &rhtsp)
{
	_factory->createTConnect("connect");
}

void RhBuilder::createTPointset(const RhTsplinePtr &rhtsp)
{
	_factory->createTPointset("pointset");
}

void RhBuilder::createTVertices(const RhImageSpreaderPtr &imgsp)
{
	RhVtxVIterator it = imgsp->getVerticesBegin();
	int i = 1;
	for(;it!=imgsp->getVerticesEnd();it++,i++)
	{
		if(*it)
		{
			string name = vId(i);
			_factory->createTVertex(name, imgsp->getVertexSParameter(i), imgsp->getVertexTParameter(i));
		}
	}
}

void RhBuilder::createTEdges( const RhTsplinePtr &rhtsp )
{
	RhEdgVector &edges = rhtsp->edges;
	for (int i=1;i<=edges.size();i++)
	{
		RhEdgePtr edge = edges[i-1];
		if (edge)
		{
			string name = eId(i);
			_factory->createTEdge(name);
		}
	}
}

void RhBuilder::createTLinks( const RhTsplinePtr &rhtsp )
{
	RhLnkVector &links = rhtsp->links;
	for (int i=1;i<=links.size();i++)
	{
		RhLinkPtr link = links[i-1];
		if (link)
		{
			string name = lId(i);
			_factory->createTLink(name);
		}
	}
}

void RhBuilder::createTEdgeConditions( const RhTsplinePtr &rhtsp )
{
	RhEdgConVector &edge_conditions = rhtsp->edge_conditions;
	for (int i=1;i<=edge_conditions.size();i++)
	{
		RhEdgeConditionPtr edge_condition = edge_conditions[i-1];
		if (edge_condition)
		{
			string name = ecId(i);
			_factory->createTEdgeCondition(name);
		}
	}
}

void RhBuilder::createTFaces( const RhTsplinePtr &rhtsp )
{
	RhFacVector &faces = rhtsp->faces;
	for (int i=1;i<=faces.size();i++)
	{
		RhFacePtr face = faces[i-1];
		if (face)
		{
			string name = fId(i);
			_factory->createTFace(name);
		}
	}
}

void RhBuilder::createTNodes( const RhConnectSpreaderPtr &consp )
{
	RhSmpKntVIterator it = consp->getSimpleKnotsBegin();
	int i = 1;
	for (;it!=consp->getSimpleKnotsEnd();it++,i++)
	{
		if(*it)
		{
			string name = nId(i);
			_factory->createTNodeV4(name);
		}
	}
}

void RhBuilder::createTPoints( const RhTsplinePtr &rhtsp )
{
	RhPntVector &points = rhtsp->control_points;
	for (int i=1;i<=points.size();i++)
	{
		RhPointPtr point = points[i-1];
		if (point)
		{
			string name = pId(i);
			_factory->createTPoint(name, point->x, point->y, point->z, point->w);
		}
	}
}

void RhBuilder::patchTSpline( const RhTsplinePtr &rhtsp )
{
	TSplinePtr spline = _factory->findTSpline();
	_factory->patchTSpline(spline, "image", "connect", "pointset");
}

void RhBuilder::patchTImage( const RhTsplinePtr &rhtsp )
{
	std::vector<std::string> faces, links, edges, vertices;
	_factory->findTObjectNames(faces, TSPLINE::E_TFACE);
	_factory->findTObjectNames(links, TSPLINE::E_TLINK);
	_factory->findTObjectNames(edges, TSPLINE::E_TEDGE);
	_factory->findTObjectNames(vertices, TSPLINE::E_TVERTEX);
	TSplinePtr spline = _factory->findTSpline();
	TImagePtr image = spline->getTImage();
	if (image) _factory->patchTImage(image, faces, links, edges, vertices);
}

void RhBuilder::patchTConnect( const RhTsplinePtr &rhtsp )
{
	std::vector<std::string> nodes;
	_factory->findTObjectNames(nodes, TSPLINE::E_TNODE);
	TSplinePtr spline = _factory->findTSpline();
	TConnectPtr connect = spline->getTConnect();
	if (connect) _factory->patchTConnect(connect, nodes);
}

void RhBuilder::patchTPointset( const RhTsplinePtr &rhtsp )
{
	std::vector<std::string> points;
	_factory->findTObjectNames(points, TSPLINE::E_TPOINT);
	TSplinePtr spline = _factory->findTSpline();
	TPointsetPtr pointset = spline->getTPointset();
	if (pointset) _factory->patchTPointset(pointset, points);
}

void RhBuilder::patchTVertices( const RhImageSpreaderPtr &imgsp )
{
	RhVtxVIterator it = imgsp->getVerticesBegin();
	int i = 1;
	//Matrix vertex_parameter = imgsp->getVertexParameter();
	for (;it!=imgsp->getVerticesEnd();it++,i++)
	{
		if(*it)
		{
			string name = vId(i);
			string nortvertexname, westvertexname, southvertexname, eastvertexname;
			int nid, wid, sid, eid;
			nid = imgsp->getVertexNeighbour(i-1)->getNorthVertex();
			wid = imgsp->getVertexNeighbour(i-1)->getWestVertex();
			sid = imgsp->getVertexNeighbour(i-1)->getSouthVertex();
			eid = imgsp->getVertexNeighbour(i-1)->getEastVertex();
			if(nid>0)
				nortvertexname = vId(nid);
			if(wid>0)
				westvertexname = vId(wid);
			if(sid>0)
				southvertexname = vId(sid);
			if(eid>0)
				eastvertexname = vId(eid);

			_factory->patchTVertexByVertices(name, nortvertexname, westvertexname, southvertexname, eastvertexname);
		}
	}
}

void RhBuilder::patchTEdges( const RhImageSpreaderPtr &imgsp )
{
	RhEdgVIterator it = imgsp->getEdgesBegin();
	int i = 1;
	for (;it!=imgsp->getEdgesEnd();it++,i++)
	{
		if(*it)
		{
			string name = eId(i);
			string vstart, vend, fleft, fright;
			vstart = vId(imgsp->getEdgeNeighbour(i-1)->getVertexStart());
			vend = vId(imgsp->getEdgeNeighbour(i-1)->getVertexEnd());

			int fl = imgsp->getEdgeNeighbour(i-1)->getFaceLeft();
			int fr = imgsp->getEdgeNeighbour(i-1)->getFaceRight();
			if(fl>0)
				fleft = fId(fl);
			else
				fleft = "";
			if(fr>0)
				fright = fId(fr);
			else
				fright = "";

			_factory->patchTEdge(name, vstart, vend, fleft, fright);
		}
	}
}

void RhBuilder::patchTLinks( const RhImageSpreaderPtr &imgsp )
{
	RhLnkVIterator it = imgsp->getLinksBegin();
	int i = 1;
	for (;it!=imgsp->getLinksEnd();it++,i++)
	{
		if(*it)
		{
			string name = lId(i);
			bool orientation = getLinkBinaryOrientation(i-1,imgsp);
			string edgename = eId((*it)->edge + 1);
			_factory->patchTLink(name, edgename, orientation);
		}
	}
}

void RhBuilder::patchTFaces( const RhImageSpreaderPtr &imgsp )
{
	RhFacVIterator it = imgsp->getFacesBegin();
	int i=1;
	for (;it!=imgsp->getFacesEnd();it++,i++)
	{
		if(*it)
		{
			string name = fId(i);
			vector<string> link_loop_name;
			RhLinkLoopPtr link_loop = imgsp->findRhLinkLoop(imgsp->getLink((*it)->link));
			for (VIntIterator itt = link_loop->linkIdIteratorBegin();itt!=link_loop->linkIdIteratorEnd();itt++)
			{
				link_loop_name.push_back(lId(*itt));
			}
			_factory->patchTFace(name, link_loop_name);
		}
	}
}

void RhBuilder::patchTNodesAndTPoints( const RhConnectSpreaderPtr &consp )
{
	RhSmpKntVIterator it = consp->getSimpleKnotsBegin();
	int i = 1;
	for (;it!=consp->getSimpleKnotsEnd();it++,i++)
	{
		if(*it)
		{
			string name, vertex_name, controlpoint_name, northknot_name, westknot_name, southknot_name, eastknot_name;
			name = nId(i);
			vertex_name = vId((*it)->getVertex());
			controlpoint_name = pId((*it)->getPoint());
			int nid, wid, sid, eid;
			nid = (*it)->getNorth();
			wid = (*it)->getWest();
			sid = (*it)->getSouth();
			eid = (*it)->getEast();
			northknot_name = getNodeName(nid);
			westknot_name = getNodeName(wid);
			southknot_name = getNodeName(sid);
			eastknot_name = getNodeName(eid);

			_factory->patchTNodeV4(name, vertex_name, controlpoint_name, northknot_name, westknot_name, southknot_name, eastknot_name);
			_factory->patchTPoint(controlpoint_name, name);
		}
	}
}


void RhBuilder::patchTEdgeConditions(const RhTsplinePtr &rhtsp)
{
	RhEdgConVector &edge_conditions = rhtsp->edge_conditions;
	for (int i=1;i<=edge_conditions.size();i++)
	{
		RhEdgeConditionPtr edge_condition = edge_conditions[i-1];
		if(edge_condition)
		{
			string name = ecId(i);
			string edge_name = eId(edge_condition->edge+1);//edge_condition->edge, inde by 0; but edge name index by 1
			if(!edge_condition->boundary_condition)
				_factory->patchTEdgeCondition(name,edge_name,true);
			else
				_factory->patchTEdgeCondition(name,edge_name,false);
		}
	}
}

bool RhBuilder::getLinkBinaryOrientation(const int linkid, const RhImageSpreaderPtr &imgsp)
{
	int edgeid = imgsp->getLink(linkid)->edge;
	RhEdgePtr edge = imgsp->getEdge(edgeid);
	if(edge)
	{
		int vertexstartid = imgsp->getEdgeNeighbour(edgeid)->getVertexStart();
		int vertexendid = imgsp->getEdgeNeighbour(edgeid)->getVertexEnd();
		Real vs_s,vs_t,ve_s,ve_t;
		vs_s = imgsp->getVertexSParameter(vertexstartid);
		vs_t = imgsp->getVertexTParameter(vertexstartid);
		ve_s = imgsp->getVertexSParameter(vertexendid);
		ve_t = imgsp->getVertexTParameter(vertexendid);

		int edgeorientation = 0;
		if( abs(vs_s - ve_s) < 1e-6)
		{
			if(ve_t > vs_t)
			{
				edgeorientation = 2;
			}
			else
			{
				edgeorientation = -2;
			}
		}
		else
		{
			if(ve_s > vs_s)
			{
				edgeorientation = 1;
			}
			else
			{
				edgeorientation = -1;
			}
		}
		if(edgeorientation == imgsp->getLinkOrientation(linkid+1))
			return true;
		else
			return false;
	}
	else
	{
		cout<<"edge: "<<edgeid<< " does not exist."<<endl;
	}
	return false;
}

std::string RhBuilder::getNodeName(int id)
{
	if(id>0)
		return nId(id);
	else
		return "";
}

void RhBuilder::prepareTObjects()
{
	_factory->prepareTNodeHalfLinkages();
	_factory->prepareTJunctions();
	_factory->prepareImageConnect();
}

