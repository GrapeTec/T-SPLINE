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
#include <rhspreader.h>


void RhLinkLoop::addLinkId(const int linkid)
{
	_link_ids.push_back(linkid);
}

void RhLinkLoop::addFace(const RhFacePtr &face)
{
	_face = face;
}

VIntIterator RhLinkLoop::linkIdIteratorBegin()
{
	return _link_ids.begin();
}

VIntIterator RhLinkLoop::linkIdIteratorEnd()
{
	return _link_ids.end();
}

int RhLinkLoop::link(const int index)
{
	return _link_ids.at(index);
}


RhImageSpreader::RhImageSpreader( const RhTsplinePtr &rhtsp, const TDirection seed)
	:_faces(rhtsp->faces),_links(rhtsp->links),_vertices(rhtsp->vertices),_edges(rhtsp->edges)
{
	deriveLinkLoops();
	_link_orientations.resize(_links.size());
	_link_orientations = 0;
	
	//set start linkid
	int linkid = *getLinkLoop(_faces[0])->linkIdIteratorBegin();
	int linkseed;
	switch(seed)
	{
	case E_NORTH:
		linkseed = 1;
		break;
	case E_WEST:
		linkseed = 2;
		break;
	case E_SOUTH:
		linkseed = -1;
		break;
	case E_EAST:
		linkseed = -2;
		break;
	default:
		linkseed = 1;
		break;
	}
	_link_orientations(linkid) = linkseed;
	deriveLinkOrientations(linkid);
	
	deriveEdges();

	//set start vertexid
	int vertexid = 1;//index by 1
	_vertex_paramter.resize(_vertices.size(),2);
	_vertex_flag.resize(_vertices.size());
	_vertex_paramter = 0;
	_vertex_flag = 0;
	deriveVertexParameters(vertexid);
	normalizeParameters();
	organizeVertexIndices();
	generateTMesh();

	deriveVertexLinkages();
}

void RhImageSpreader::deriveLinkLoops()
{
	for (RhFacVIterator iter=_faces.begin();iter!=_faces.end();iter++)
	{
		RhFacePtr face = *iter;
		_link_loops.push_back(getLinkLoop(face));
	}
}

void RhImageSpreader::deriveLinkOrientations(const int linkid)
{
	int face_id = _links[linkid-1]->face;
	if(face_id < 0)
	{
		return;
	}
	RhLinkLoopPtr link_loop = findRhLinkLoop(_links[linkid-1]);
	int j=0;
	int theposition = 0;
	int theorientation = 0;
	VInt orientationindices;
	for (VIntIterator it = link_loop->linkIdIteratorBegin();it!=link_loop->linkIdIteratorEnd();it++)
	{
		RhLinkPtr link = _links[*it-1];
		int link_flag = link->flag;
		int link_orientation = _link_orientations(*it);
		if(link_flag == 0)
			j = j + 1;
		if(*it == linkid)
		{
			theposition = j;
			theorientation = link_orientation;
		}
		orientationindices.push_back(j);
	}
	int orientations[4];
	for (int i = theposition-1; i<=theposition+2; i++)
	{
		int orientation_index = i%4;
		orientations[orientation_index] = theorientation;
		theorientation = getNextOrientation(theorientation);
	}
	for (int i=0;i<orientationindices.size();i++)
	{
		int orientation_index = orientationindices[i];
		_link_orientations(link_loop->link(i)) = orientations[orientation_index-1];
		int opplinkid = _links[link_loop->link(i)-1]->opp_link+1;
		if(_link_orientations(opplinkid) == 0)
		{
			_link_orientations(opplinkid) = 0-orientations[orientation_index-1];
			deriveLinkOrientations(opplinkid);
		}
	}
}

void RhImageSpreader::deriveEdges()
{
	//_edge_nbr.resize(_edges.size());
	RhEdgVIterator iter;
	for (iter = _edges.begin();iter!=_edges.end();iter++)
	{
		RhEdgeNeighbourPtr edgenbr = makePtr<RhEdgeNeighbour>();
		if(*iter)
		{
			int vs,ve;
			getEdgeStartEnd(*iter,vs,ve);
			edgenbr->setVertexStartEnd(vs+1,ve+1);
			int fl,fr;
			getAdjacentFace(*iter,fl,fr);
			edgenbr->setAdjacentFace(fl+1,fr+1);
		}
		else
			edgenbr = 0;
		_edge_nbr.push_back(edgenbr);
	}
}

RhLinkLoopPtr RhImageSpreader::getLinkLoop(const RhFacePtr &face)
{
	if(face)
	{
		RhLinkLoopPtr link_loop = makePtr<RhLinkLoop>();
		int startid = face->link + 1;
		link_loop->addLinkId(startid);
		int id = startid; int nextid = _links[id-1]->next_link + 1;
		while (nextid != startid)
		{
			id = nextid;
			link_loop->addLinkId(id);
			link_loop->addFace(face);
			nextid = _links[id-1]->next_link + 1;
		}
		return link_loop;
	}
	else
	{
		return NULL;
	}
}

RhLinkPtr RhImageSpreader::findRhLink(const int linkid)
{
	if (linkid <= 0 || linkid > _links.size())
	{
		return NULL;
	}
	else
	{
		return _links[linkid-1];
	}
}

RhLinkLoopPtr RhImageSpreader::findRhLinkLoop(const RhLinkPtr &link)
{
	RhLinkLoopPtr link_loop = makePtr<RhLinkLoop>();
	if(link->face<0)
		return 0;
	else
	{
		link_loop = _link_loops[link->face];
		return link_loop;
	}
}

int RhImageSpreader::getNextOrientation(const int orientation)
{
	if(orientation == 1)
		return 2;
	else if(orientation == 2)
		return -1;
	else if(orientation == -1)
		return -2;
	else if(orientation == -2)
		return 1;
	else
		return 0;
}

void RhImageSpreader::deriveVertexParameters(const int vertexid)
{
	RhVertexPtr start_vertex = _vertices[vertexid-1];
	double start_s = _vertex_paramter(vertexid,1);
	double start_t = _vertex_paramter(vertexid,2);

	int linkid1 = start_vertex->link;
	RhLinkPtr link1 = _links[linkid1];
	int opplinkid = link1->opp_link;
	RhLinkPtr opplink = _links[opplinkid];
	int linkid2 = opplink->next_link;
	int prelinkid = link1->previous_link;
	RhLinkPtr prelink = _links[prelinkid];
	int linkid3 = prelink->opp_link;

	int edgeid1 = link1->edge;
	int orientation1 = _link_orientations(linkid1+1);
	RhEdgePtr edge1 = _edges[edgeid1];
	double edgelength1 = edge1->interval;
	double vertex_s,vertex_t;
	getIncParameters(orientation1,edgelength1,vertex_s,vertex_t);
	int nextvertexid1;
	if(vertexid == _edge_nbr[edgeid1]->getVertexStart())
	{
		nextvertexid1 = _edge_nbr[edgeid1]->getVertexEnd();
	}
	else
	{
		nextvertexid1 = _edge_nbr[edgeid1]->getVertexStart();
	}
	if(_vertex_flag(nextvertexid1) == 0)
	{
		_vertex_paramter(nextvertexid1,1) = start_s + vertex_s;
		_vertex_paramter(nextvertexid1,2) = start_t + vertex_t;
		_vertex_flag(nextvertexid1) = 1;
		deriveVertexParameters(nextvertexid1);
	}

	RhLinkPtr link2 = _links[linkid2];
	int edgeid2 = link2->edge;
	int orientation2 = _link_orientations(linkid2+1);
	RhEdgePtr edge2 = _edges[edgeid2];
	double edgelength2 = edge2->interval;
	getIncParameters(orientation2,edgelength2,vertex_s,vertex_t);
	int nextvertexid2;
	if(vertexid == _edge_nbr[edgeid2]->getVertexStart())
	{
		nextvertexid2 = _edge_nbr[edgeid2]->getVertexEnd();
	}
	else
	{
		nextvertexid2 = _edge_nbr[edgeid2]->getVertexStart();
	}
	if(_vertex_flag(nextvertexid2) == 0)
	{
		_vertex_paramter(nextvertexid2,1) = start_s + vertex_s;
		_vertex_paramter(nextvertexid2,2) = start_t + vertex_t;
		_vertex_flag(nextvertexid2) = 1;
		deriveVertexParameters(nextvertexid2);
	}

	RhLinkPtr link3 = _links[linkid3];
	int edgeid3 = link3->edge;
	int orientation3 = _link_orientations(linkid3+1);
	RhEdgePtr edge3 = _edges[edgeid3];
	double edgelength3 = edge3->interval;
	getIncParameters(orientation3,edgelength3,vertex_s,vertex_t);
	int nextvertexid3;
	if(vertexid == _edge_nbr[edgeid3]->getVertexStart())
	{
		nextvertexid3 = _edge_nbr[edgeid3]->getVertexEnd();
	}
	else
	{
		nextvertexid3 = _edge_nbr[edgeid3]->getVertexStart();
	}
	if(_vertex_flag(nextvertexid3) == 0)
	{
		_vertex_paramter(nextvertexid3,1) = start_s + vertex_s;
		_vertex_paramter(nextvertexid3,2) = start_t + vertex_t;
		_vertex_flag(nextvertexid3) = 1;
		deriveVertexParameters(nextvertexid3);
	}
}

void RhImageSpreader::getIncParameters(const int orientation, const double edgelength, double &vertex_s, double &vertex_t)
{
	vertex_s = vertex_t = 0;
	switch(orientation)
	{
	case 1:
		vertex_s = edgelength;
		break;
	case 2:
		vertex_t = edgelength;
		break;
	case -1:
		vertex_s = 0 - edgelength;
		break;
	case -2:
		vertex_t = 0 - edgelength;
		break;
	default:
		break;
	}
}

void RhImageSpreader::getEdgeStartEnd(const RhEdgePtr &edge, int &vertexstart, int &vertexend)
{
	int linkid = edge->link;
	
	vertexstart = _links[linkid]->vertex;
	vertexend = _links[_links[linkid]->next_link]->vertex;

}

void RhImageSpreader::getAdjacentFace(const RhEdgePtr &edge, int &faceleft, int &faceright)
{
	int linkid = edge->link;
	faceleft = _links[linkid]->face;
	faceright = _links[_links[linkid]->opp_link]->face;
}

void RhImageSpreader::normalizeParameters()
{
	double smax,smin,tmax,tmin;
	smax = smin = _vertex_paramter(1,1);
	tmax = tmin = _vertex_paramter(1,2);
	for (int i = 0; i<_vertices.size();i++)
	{
		if(_vertices[i])
		{
			if(_vertex_paramter(i+1,1) > smax)
				smax = _vertex_paramter(i+1,1);
			if(_vertex_paramter(i+1,1) < smin)
				smin = _vertex_paramter(i+1,1);
			if(_vertex_paramter(i+1,2) > tmax)
				tmax = _vertex_paramter(i+1,2);
			if(_vertex_paramter(i+1,2) < tmin)
				tmin = _vertex_paramter(i+1,2);
		}
	}
	_vertex_paramter.column(1) = _vertex_paramter.column(1) - smin;
	_vertex_paramter.column(2) = _vertex_paramter.column(2) - tmin;
}

void RhImageSpreader::organizeVertexIndices()
{
	vector<double> vertex_s,vertex_t;
	for (int i=0;i<_vertices.size();i++)
	{
		if(_vertices[i])
		{
			vertex_s.push_back(_vertex_paramter(i+1,1));
			vertex_t.push_back(_vertex_paramter(i+1,2));
		}
	}

	sort(vertex_s.begin(),vertex_s.end());
	std::vector<double>::iterator it_vertex_s = unique(vertex_s.begin(),vertex_s.end());
	vertex_s.erase(it_vertex_s,vertex_s.end());

	sort(vertex_t.begin(),vertex_t.end());
	std::vector<double>::iterator it_vertex_t = unique(vertex_t.begin(),vertex_t.end());
	vertex_t.erase(it_vertex_t,vertex_t.end());
	reverse(vertex_t.begin(),vertex_t.end());

	for (int i=0;i<_vertices.size();i++)
	{
		RhVertexNeighbourPtr vertex_nbr = makePtr<RhVertexNeighbour>();
		if(_vertices[i])
		{
			for (int k=0;k<vertex_s.size();k++)
			{
				if(_vertex_paramter(i+1,1) == vertex_s[k])
					vertex_nbr->setTmeshCol(k);
			}
			for (int k=0;k<vertex_t.size();k++)
			{
				if(_vertex_paramter(i+1,2) == vertex_t[k])
					vertex_nbr->setTmeshRow(k);
			}
		}
		else
		{
			vertex_nbr = 0;
		}
		_vertex_nbr.push_back(vertex_nbr);
	}

	_tmesh.resize(vertex_t.size(), vertex_s.size());
	_tmesh = -1;
}

void RhImageSpreader::generateTMesh()
{
	for (int i=0;i<_vertices.size();i++)
	{
		if(_vertices[i])
		{
			_tmesh(_vertex_nbr[i]->getTmeshRow()+1, _vertex_nbr[i]->getTmeshCol()+1) = i;
		}
	}
}

void RhImageSpreader::deriveVertexLinkages()
{
	for (int i=0;i<_links.size();i++)
	{
		if(_links[i])
		{
			int vertexid = _links[i]->vertex;
			int edgeid = _links[i]->edge;
			int othervertexid = getOtherVertex(edgeid,vertexid);
			int orientation = _link_orientations(i+1);
			setLinkage(vertexid, othervertexid, orientation);
		}
	}
}

int RhImageSpreader::getOtherVertex(const int edgeid, const int vertexid)
{
	if(_edge_nbr[edgeid]->getVertexStart() == vertexid+1)
		return _edge_nbr[edgeid]->getVertexEnd();
	else if(_edge_nbr[edgeid]->getVertexEnd() == vertexid+1)
		return _edge_nbr[edgeid]->getVertexStart();
	else
		return -1;
}

void RhImageSpreader::setLinkage(const int vertexid, const int linkedvertex, const int orientation)
{
	switch(orientation)
	{
	case 1:
		_vertex_nbr[vertexid]->setEastVertex(linkedvertex);
		break;
	case 2:
		_vertex_nbr[vertexid]->setNorthVertex(linkedvertex);
		break;
	case -1:
		_vertex_nbr[vertexid]->setWestVertex(linkedvertex);
		break;
	case -2:
		_vertex_nbr[vertexid]->setSouthVertex(linkedvertex);
		break;
	}
}

RotMatrix* RotMatrix::_instance = 0;
RotMatrix* RotMatrix::Instance()
{
	if(_instance == 0)
	{
		_instance = new RotMatrix;
	}
	return _instance;
}

Matrix RotMatrix::rot90(Matrix &mt, int num /*=1*/)
{
	for (int i=0;i<num;i++)
	{
		mt = rot90base(mt);
	}
	return mt;
}

Matrix RotMatrix::rot90base(const Matrix &mt)
{
	Matrix m(mt.ncols(),mt.nrows());
	for (int i=1;i<=mt.nrows();i++)
	{
		m.Column(i) = mt.Row(i).as_column();
		m.Column(i) = m.Column(i).reverse();
	}
	return m;
}

RhComplexKnot::RhComplexKnot(const int nrows, const int ncols)
{
	_matrix.resize(nrows,ncols);
	_matrix = -1;
	_id = 0;
}


void RhComplexKnot::addSimpleKnot(const RhSimpleKnotPtr &knot, const int row, const int col)
{
	if(row > _matrix.nrows() || row<1 || col > _matrix.ncols() || col<1)
		return ;
	_knot.push_back(knot);
	_matrix(row,col) = _id++;
}

RhSimpleKnotPtr RhComplexKnot::operator()(const int nrows, const int ncols)
{
	if(nrows > _matrix.nrows() || nrows<1 || ncols > _matrix.ncols() || ncols<1)
		cout<<"out of the range."<<endl;
	else 
	{
		int index = _matrix(nrows,ncols);
		if(index>-1)
			return _knot[_matrix(nrows,ncols)];
	}
	return NULL;
}

RhComplexKnotPtr RhComplexKnot::asComplex()
{
	return castPtr<RhComplexKnot>(shared_from_this());
}

void RhComplexKnot::rotate(int num)
{
	if(num<0)
		num += 4;
	RotMatrix::Instance()->rot90(_matrix,num);
}

RhKnotMatrix::RhKnotMatrix(const int nrows, const int ncols)
{
	_matrix.resize(nrows,ncols);
	_matrix = -1;
	_id = 0;
}

RhSimpleKnotPtr RhKnotMatrix::operator()(const int nrows, const int ncols)
{
	if(nrows > _matrix.nrows() || nrows<1 || ncols > _matrix.ncols() || ncols<1)
		cout<<"out of the range."<<endl;
	else 
	{
		int index = _matrix(nrows,ncols);
		if(index>-1)
			return _knots[_matrix(nrows,ncols)];
	}
	return NULL;
}

void RhKnotMatrix::addKnot(const RhSimpleKnotPtr &knot, const int nrows, const int ncols)
{
	if(nrows > _matrix.nrows() || nrows<1 || ncols > _matrix.ncols() || ncols<1)
		return;
	_knots.push_back(knot);
	_matrix(nrows,ncols) = _id++;
}

RhKnotIdMatrix::RhKnotIdMatrix(const int nrows, const int ncols)
{
	_matrix.resize(nrows,ncols);
	_matrix = -1;
	_id = 0;
}

Matrix RhKnotIdMatrix::operator()(const int nrows, const int ncols)
{
	if(nrows > _matrix.nrows() || nrows<1 || ncols > _matrix.ncols() || ncols<1)
		cout<<"out of the range."<<endl;
	else 
	{
		int index = _matrix(nrows,ncols);
		if(index>-1)
			return _complexid[_matrix(nrows,ncols)];
	}
	/*an error has occurd, return a null-matrix*/
	Matrix m(0,0);
	return m;
}

void RhKnotIdMatrix::addKnotid(const Matrix &id, int row, int col)
{
	if(row > _matrix.nrows() || row<1 || col > _matrix.ncols() || col<1)
		return;
	_complexid.push_back(id);
	_matrix(row,col) = _id++;
}

RhKnotConstruct::RhKnotConstruct(const RhGrpVector &grips, const RhCgtVector &cgs, const int vsize)
{
	_knot_num = 0;
	_knots.resize(vsize);
	_mknots.resize(vsize);
	for (RhGrpVector::const_iterator iter = grips.begin();iter!=grips.end();iter++)
	{
		if(*iter)
		{
			int vertexid = (*iter)->index;
			if(vertexid>-1)
			{
				if(!_knots[vertexid])
				{
					RhKnotPtr knot = makePtr<RhKnot>();
					_knots[vertexid] = knot;
				}
				_knots[vertexid]->setVertex(vertexid);
				_knots[vertexid]->multiplicity();
				_knots[vertexid]->addControlPointId(_knot_num);
				if((*iter)->with_p)
				{
					_knots[vertexid]->setPrime(_knot_num);
				}
			}	
			_knot_num++;
		}	
	}
	for (RhCgtVector::const_iterator iter = cgs.begin();iter!=cgs.end();iter++)
	{
		if(*iter)
		{
			int vertexid = (*iter)->vertex;
			RhMKnotPtr mknot = makePtr<RhMKnot>();
			mknot->setDims((*iter)->dims);
			mknot->setGrips((*iter)->grips);
			_mknots[vertexid] = mknot;
		}
	}

}

RhConnectSpreader::RhConnectSpreader(const RhTsplinePtr &rhtsp, const RhImageSpreaderPtr &imgspr)
{
	_vertices = rhtsp->vertices;
	_vertex_nbr = imgspr->getVertexNeighbours();
	_link_orientations = imgspr->getAllLinkOrientation();
	_knot_construct = makePtr<RhKnotConstruct>(rhtsp->grips, rhtsp->compound_grip_tags, rhtsp->vertices.size());

	constructKnotMatrix(imgspr->getTmesh());
	deriveKnotLinkages(imgspr->getTmesh());
}

void RhConnectSpreader::constructKnotMatrix(const Matrix &tmesh)
{
	int nrows = tmesh.nrows();
	int ncols = tmesh.ncols();
	_knot_matrix = makePtr<RhKnotMatrix>(nrows, ncols);
	for (int i=1;i<=nrows;i++)
	{
		for (int j=1;j<=ncols;j++)
		{
			int vertexid = tmesh(i,j);
			if(vertexid>=0)
			{
				RhSimpleKnotPtr knots = constructKnots(vertexid);
				_knot_matrix->addKnot(knots,i,j);
			}
		}
	}
}

void RhConnectSpreader::deriveKnotLinkages(const Matrix &tmesh)
{
	int nrows = tmesh.nrows();
	int ncols = tmesh.ncols();
	_knotid_matrix = makePtr<RhKnotIdMatrix>(nrows,ncols);
	
	int k = 0;
	for (int i=1;i<=nrows;i++)
	{
		for (int j=1;j<=ncols;j++)
		{
			RhSimpleKnotPtr smpcpx_knot = (*_knot_matrix.get())(i,j);
			if(smpcpx_knot)
			{
				Matrix complexid;
				if(!smpcpx_knot->asComplex())
				{
					smpcpx_knot->setId(k);
					complexid.resize(1,1);
					complexid = k;
					k++;
					_simple_knots.push_back(smpcpx_knot);		
				}
				else
				{
					RhComplexKnotPtr knotgrp = smpcpx_knot->asComplex();
					int row = knotgrp->nrows();
					int col = knotgrp->ncols();
					complexid.resize(row,col);
					complexid = -1;
					for (int m=1;m<=row;m++)
					{
						for (int n=1;n<=col;n++)
						{
							RhSimpleKnotPtr simpleknot = (*knotgrp.get())(m,n);
							if(simpleknot)
							{
								simpleknot->setId(k);
								complexid(m,n) = k;
								//k++;
							}
							k++;
							_simple_knots.push_back(simpleknot);
						}
					}	
				}
				_knotid_matrix->addKnotid(complexid,i,j);
			}
		}
	}

	for (int i=1;i<=nrows;i++)
	{
		for (int j=1;j<=ncols;j++)
		{
			Matrix complexid = (*_knotid_matrix.get())(i,j);
			if(complexid.size()>0)
			{
				organizeInnerLinkage(complexid);

				if(i>1)
				{
					Matrix northcomplexid = getNorthComplexKnotId(complexid);
					if(northcomplexid.size()>0)
					{
						organizeNorthLinkage(complexid,northcomplexid);
					}
				}

				if(i<nrows)
				{
					Matrix southcomplexid = getSouthComplexKnotId(complexid);
					if(southcomplexid.size()>0)
					{
						organizeSouthLinkage(complexid,southcomplexid);
					}
				}

				if(j>1)
				{
					Matrix westcomplexid = getWestComplexKnotId(complexid);
					if(westcomplexid.size()>0)
					{
						organizeWestLinkage(complexid,westcomplexid);
					}
				}

				if(j<ncols)
				{
					Matrix eastcomplexid = getEastComplexKnotId(complexid);
					if(eastcomplexid.size()>0)
					{
						organizeEastLinkage(complexid,eastcomplexid);
					}
				}
			}
		}
	}
}

RhSimpleKnotPtr RhConnectSpreader::constructKnots(const int vertexid)
{
	RhKnotPtr knot = _knot_construct->getKnot(vertexid);
	RhMKnotPtr mknot = _knot_construct->getMKnot(vertexid);

	int anrows=0, ancols=0;
	int bnrows=0, bncols=0;
	int cnrows=0, cncols=0;
	int dnrows=0, dncols=0;
	int nrows=0, ncols=0;

	if(mknot)
	{
		anrows = mknot->dim(0); ancols = mknot->dim(1)+1;
		bnrows = mknot->dim(1); bncols = mknot->dim(2)+1;
		cnrows = mknot->dim(2); cncols = mknot->dim(3)+1;
		dnrows = mknot->dim(3); dncols = mknot->dim(0)+1;
		nrows = 1 + mknot->dim(0) + mknot->dim(2);
		ncols = 1 + mknot->dim(1) + mknot->dim(3);

		anrows = mknot->dim(0);
	}

	RhSimpleKnotPtr knotsGrp;
	if((nrows == 0) && (ncols == 0))
	{
		knotsGrp = makePtr<RhSimpleKnot>();
		knotsGrp->setVertex(vertexid+1);
		knotsGrp->setPoint(knot->getPrime()+1);
		knotsGrp->setMiddle(1);
		if(knotsGrp->getPoint()!=0)//newmat index
			return knotsGrp;
	}
	else
		knotsGrp = makePtr<RhComplexKnot>(nrows,ncols);

	//A wedge
	Matrix aindices(anrows,ancols);
	int gripoffset = 0;
	for (int i=1;i<=anrows*ancols;i++)
	{
		aindices(floor((i-1)/(float)ancols)+1,(i-1)%ancols+1) = i;
	}
	aindices = RotMatrix::Instance()->rot90(aindices,2);
	int actualnrows = aindices.nrows();
	int actualncols = aindices.ncols();
	for (int i=1;i<=actualnrows;i++)
	{
		for (int j=1;j<=actualncols;j++)
		{
			int gripindex = aindices(i,j) + gripoffset;
			RhSimpleKnotPtr knots = makePtr<RhSimpleKnot>();
			knots->setVertex(vertexid+1);
			knots->setPoint(mknot->grip(gripindex-1)+1);
			if(knots->getPoint()!=0)//newmat index
				knotsGrp->addSimpleKnot(knots,i,j);
		}
	}

	//B wedge
	Matrix bindices(bnrows,bncols);
	gripoffset+= anrows*ancols;
	for (int i=1;i<=bnrows*bncols;i++)
	{
		bindices(floor((i-1)/(float)bncols)+1,(i-1)%bncols+1) = i;
	}
    Matrix tempb = RotMatrix::Instance()->rot90(bindices,2);
	bindices = RotMatrix::Instance()->rot90(tempb);
	actualnrows = bindices.nrows();
	actualncols = bindices.ncols();
	for (int i=1;i<=actualnrows;i++)
	{
		for (int j=1;j<=actualncols;j++)
		{
			int gripindex = bindices(i,j) + gripoffset;
			RhSimpleKnotPtr knots = makePtr<RhSimpleKnot>();
			knots->setVertex(vertexid+1);
			knots->setPoint(mknot->grip(gripindex-1)+1);
			if(knots->getPoint()!=0)//newmat index
				knotsGrp->addSimpleKnot(knots,i+anrows,j);
		}
	}

	//C wedge
	Matrix cindices(cnrows,cncols);
	gripoffset+= bnrows*bncols;
	for (int i=1;i<=cnrows*cncols;i++)
	{
		cindices(floor((i-1)/(float)cncols)+1,(i-1)%cncols+1) = i;
	}
    Matrix tempc1,tempc2;
    tempc1 = RotMatrix::Instance()->rot90(cindices,2);
    tempc2 = RotMatrix::Instance()->rot90(tempc1);
	cindices = RotMatrix::Instance()->rot90(tempc2);
	actualnrows = cindices.nrows();
	actualncols = cindices.ncols();
	for (int i=1;i<=actualnrows;i++)
	{
		for (int j=1;j<=actualncols;j++)
		{
			int gripindex = cindices(i,j) + gripoffset;
			RhSimpleKnotPtr knots = makePtr<RhSimpleKnot>();
			knots->setVertex(vertexid+1);
			knots->setPoint(mknot->grip(gripindex-1)+1);
			if(knots->getPoint()!=0)//newmat index
				knotsGrp->addSimpleKnot(knots,i+anrows+1,j+bnrows);
		}
	}

	//D wedge
	Matrix dindices(dnrows,dncols);
	gripoffset+= cnrows*cncols;
	for (int i = 1;i<=dnrows*dncols;i++)
	{
		dindices(floor((i-1)/(float)dncols)+1,(i-1)%dncols+1) = i;
	}
    Matrix tempd1, tempd2, tempd3;
    tempd1 = RotMatrix::Instance()->rot90(dindices,2);
    tempd2 = RotMatrix::Instance()->rot90(tempd1);
    tempd3 = RotMatrix::Instance()->rot90(tempd2);
	dindices = RotMatrix::Instance()->rot90(tempd3);
	actualnrows = dindices.nrows();
	actualncols = dindices.ncols();
	for (int i=1;i<=actualnrows;i++)
	{
		for (int j=1;j<=actualncols;j++)
		{
			int gripindex = dindices(i,j) + gripoffset;
			RhSimpleKnotPtr knots = makePtr<RhSimpleKnot>();
			knots->setVertex(vertexid+1);
			knots->setPoint(mknot->grip(gripindex-1)+1);
			if(knots->getPoint()!=0)//newmat index
				knotsGrp->addSimpleKnot(knots,i,j+bnrows+1);
		}
	}

	//middle
	RhSimpleKnotPtr knots = makePtr<RhSimpleKnot>();
	knots->setVertex(vertexid+1);
	knots->setPoint(knot->getPrime()+1);
	knots->setMiddle(1);
	if(knots->getPoint()!=0)//newmat index
		knotsGrp->addSimpleKnot(knots,anrows+1,bnrows+1);

	//orientation
	RhVertexPtr vertex = _vertices[vertexid];
	int linkref = vertex->link;
	int linkorientation = _link_orientations(linkref+1);
	int vertexorientation = direction2Orientation(vertex->direction);
	int linkangle = orientation2Rotation(linkorientation);
	int vertexangle = orientation2Rotation(vertexorientation);
	int rotcount = floor((linkangle-vertexangle)/(float)90);

	knotsGrp->asComplex()->rotate(rotcount);

	return knotsGrp;
}

int RhConnectSpreader::direction2Orientation(const std::string &direction)
{
	if(direction == "EAST")
		return 1;
	else if(direction == "NORTH")
		return 2;
	else if(direction == "WEST")
		return -1;
	else//SOUTH
		return -2;
}

int RhConnectSpreader::orientation2Rotation(const int &orientation)
{
	switch(orientation)
	{
	case 1:
		return -90;
		break;
	case 2:
		return 0;
		break;
	case -1:
		return 90;
		break;
	case -2:
		return 180;
		break;
	default:
		/*non-valid orientation, return 0 rotation*/
		return 0;
		break;
	}
}

void RhConnectSpreader::organizeInnerLinkage(const Matrix &complexid)
{
	int row = complexid.nrows();
	int col = complexid.ncols();
	for (int i=1;i<=row;i++)
	{
		for (int j=1;j<=col;j++)
		{
			int knotid = complexid(i,j);
			if(knotid<0)
				continue;
			RhSimpleKnotPtr knot = _simple_knots[knotid];
			if(i>1)
				knot->setNorthKnot(complexid(i-1,j) + 1);//newmat index
			if(j>1)
				knot->setWestKnot(complexid(i,j-1) + 1);
			if(i<row)
				knot->setSouthKnot(complexid(i+1,j) + 1);
			if(j<col)
				knot->setEastKnot(complexid(i,j+1) + 1);
		}
	}
}

Matrix RhConnectSpreader::getNorthComplexKnotId(const Matrix &complexid)
{
	int vertexid = getVertexFromComplexId(complexid);
	int northvertexid = _vertex_nbr[vertexid-1]->getNorthVertex();
	if(northvertexid>0)
	{
		int row = _vertex_nbr[northvertexid-1]->getTmeshRow();
		int col = _vertex_nbr[northvertexid-1]->getTmeshCol();
		return (*_knotid_matrix.get())(row+1,col+1);
	}
	else
	{
		Matrix m(0,0);
		return m;
	}
}

Matrix RhConnectSpreader::getSouthComplexKnotId(const Matrix &complexid)
{
	int vertexid = getVertexFromComplexId(complexid);
	int southvertexid = _vertex_nbr[vertexid-1]->getSouthVertex();
	if(southvertexid>0)
	{
		int row = _vertex_nbr[southvertexid-1]->getTmeshRow();
		int col = _vertex_nbr[southvertexid-1]->getTmeshCol();
		return (*_knotid_matrix.get())(row+1,col+1);
	}
	else
	{
		Matrix m(0,0);
		return m;
	}
}

Matrix RhConnectSpreader::getWestComplexKnotId(const Matrix &complexid)
{
	int vertexid = getVertexFromComplexId(complexid);
	int westvertexid = _vertex_nbr[vertexid-1]->getWestVertex();
	if(westvertexid>0)
	{
		int row = _vertex_nbr[westvertexid-1]->getTmeshRow();
		int col = _vertex_nbr[westvertexid-1]->getTmeshCol();
		return (*_knotid_matrix.get())(row+1,col+1);
	}
	else
	{
		Matrix m(0,0);
		return m;
	}
}

Matrix RhConnectSpreader::getEastComplexKnotId(const Matrix &complexid)
{
	int vertexid = getVertexFromComplexId(complexid);
	int eastvertexid = _vertex_nbr[vertexid-1]->getEastVertex();
	if(eastvertexid>0)
	{
		int row = _vertex_nbr[eastvertexid-1]->getTmeshRow();
		int col = _vertex_nbr[eastvertexid-1]->getTmeshCol();
		return (*_knotid_matrix.get())(row+1,col+1);
	}
	else
	{
		Matrix m(0,0);
		return m;
	}
}

int RhConnectSpreader::getVertexFromComplexId(const Matrix &complexid)
{
	int i = 1;
	int knotid = complexid(1,i);
	while(knotid<0)
	{
		i = i+1;
		knotid = complexid(1,i);
	}
	return _simple_knots[knotid]->getVertex();
}

void RhConnectSpreader::organizeNorthLinkage(const Matrix &complexid, const Matrix &northcomplexid)
{
	int southtip = getSouthTipFromComplexId(northcomplexid);
	for (int i=1;i<=complexid.ncols();i++)
	{
		int knotid = complexid(1,i);
		if(knotid>0)
			_simple_knots[knotid]->setNorthKnot(southtip + 1);
	}
}

void RhConnectSpreader::organizeSouthLinkage(const Matrix &complexid, const Matrix &southcomplexid)
{
	int northtip = getNorthTipFromComplexId(southcomplexid);
	int nrow = complexid.nrows();
	for (int i=1;i<=complexid.ncols();i++)
	{
		int knotid = complexid(nrow,i);
		if(knotid>0)
			_simple_knots[knotid]->setSouthKnot(northtip + 1);
	}
}

void RhConnectSpreader::organizeWestLinkage(const Matrix &complexid, const Matrix &westcomplexid)
{
	int easttip = getEastTipFromComplexId(westcomplexid);
	for (int i=1;i<=complexid.nrows();i++)
	{
		int knotid = complexid(i,1);
		if(knotid>0)
			_simple_knots[knotid]->setWestKnot(easttip + 1);
	}
}

void RhConnectSpreader::organizeEastLinkage(const Matrix &complexid, const Matrix &eastcomplexid)
{
	int westtip = getWestTipFromComplexId(eastcomplexid);
	int ncol = complexid.ncols();
	for (int i=1;i<=complexid.nrows();i++)
	{
		int knotid = complexid(i,ncol);
		if(knotid>0)
			_simple_knots[knotid]->setEastKnot(westtip + 1);
	}
}

int RhConnectSpreader::getNorthTipFromComplexId(const Matrix &complexid)
{
	int midrow, midcol;
	getCenterOfComplexKnotId(complexid, midrow, midcol);
	return complexid(1,midcol);
}

int RhConnectSpreader::getSouthTipFromComplexId(const Matrix &complexid)
{
	int midrow, midcol;
	getCenterOfComplexKnotId(complexid, midrow, midcol);
	return complexid(complexid.nrows(),midcol);
}

int RhConnectSpreader::getWestTipFromComplexId(const Matrix &complexid)
{
	int midrow, midcol;
	getCenterOfComplexKnotId(complexid, midrow, midcol);
	return complexid(midrow,1);
}

int RhConnectSpreader::getEastTipFromComplexId(const Matrix &complexid)
{
	int midrow, midcol;
	getCenterOfComplexKnotId(complexid, midrow, midcol);
	return complexid(midrow,complexid.ncols());
}

void RhConnectSpreader::getCenterOfComplexKnotId(const Matrix &complexid, int &midrow, int &midcol)
{
	int nrows = complexid.nrows();
	int ncols = complexid.ncols();

	midrow = 0; midcol = 0;
	for (int i=1;i<=nrows;i++)
	{
		for (int j=1;j<=ncols;j++)
		{
			int knotid = complexid(i,j);
			if(knotid<0)
				continue;
			RhSimpleKnotPtr knot = _simple_knots[knotid];
			if(knot && (knot->isMiddle() == 1))
			{
				midrow = i;
				midcol = j;
				break;
			}
		}
	}
}
