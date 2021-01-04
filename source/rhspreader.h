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

/**  @file  [rhspreader]  
  *  @brief  Prepare to construct the three layers T-spline structure.
  *  @author  <Wenlei Xiao>  
  *  @date  <2016.03.15>  
  *  @version  <v1.0>  
  *  @note  
  *  
*/

#ifndef RHSPREADER
#define RHSPREADER

#include <tspline.h>
#include <rhparser.h>

#ifdef use_namespace
using namespace TSPLINE;
#endif

DECLARE_SMARTPTR(RhImageSpreader);
DECLARE_SMARTPTR(RhKnotConstruct);
DECLARE_SMARTPTR(RhConnectSpreader);
DECLARE_SMARTPTR(RhKnotMatrix);
DECLARE_SMARTPTR(RhKnotIdMatrix);
DECLARE_ASSISTANCES(RhLinkLoop, RhLnkLup);
DECLARE_ASSISTANCES(RhEdgeNeighbour, RhEdgNbr);
DECLARE_ASSISTANCES(RhVertexNeighbour, RhVtxNbr);
DECLARE_ASSISTANCES(RhKnot, RhKnt);
DECLARE_ASSISTANCES(RhMKnot, RhMKnt);
DECLARE_ASSISTANCES(RhSimpleKnot, RhSmpKnt);
DECLARE_ASSISTANCES(RhComplexKnot, RhCpxKnt);

typedef vector<int> VInt;
typedef VInt::iterator VIntIterator;

/**  
  *  @class  <RhLinkLoop> 
  *  @brief  Linkloop class.  
  *  @note  
  *  RhLinkLoop contains a closed loop of Rhino links.  
*/
class RhLinkLoop
{
public:
	RhLinkLoop(){};
	~RhLinkLoop(){};
public:
	/** Add link to the linkloop. */
	void addLinkId(const int linkid);
	/** Add face to the linkloop. */
	void addFace(const RhFacePtr &face);
	/** Return the begin iterator of the linkloop. */
	VIntIterator linkIdIteratorBegin();
	/** Return the end iterator of the linkloop. */
	VIntIterator linkIdIteratorEnd();
	/** Return the link id by index. */
	int link(const int index);;
private:
	RhFacePtr _face;	
	VInt _link_ids;		
};

/**  
  *  @class  <RhEdgeNeighbour> 
  *  @brief  Edge neighbour class.  
  *  @note  
  *  RhEdgeNeighbour contains start id and end id of Rhino vertices, left id and right id Rhino faces.  
*/
class RhEdgeNeighbour
{
public:
	RhEdgeNeighbour()
		:_vertex_start(-1),_vertex_end(-1),_face_left(-1),_face_right(-1){};
	~RhEdgeNeighbour(){};

	/** Set the start vertex and end vertex of the edge. */
	void setVertexStartEnd(const int vertexstart, const int vertexend){_vertex_start = vertexstart;_vertex_end = vertexend;};
	/** Set the left face and right face of the edge. */
	void setAdjacentFace(const int faceleft, const int faceright){_face_left = faceleft;_face_right = faceright;};

	/** Return the start vertex of the edge. */
	int getVertexStart(){return _vertex_start;};
	/** Return the end vertex of the edge. */
	int getVertexEnd(){return _vertex_end;};
	/** Return the left face of the edge. */
	int getFaceLeft(){return _face_left;};
	/** Return the right face of the edge. */
	int getFaceRight(){return _face_right;};
private:
	int _vertex_start;		
	int _vertex_end;		
	int _face_left;			
	int _face_right;		
};

/**  
  *  @class  <RhVertexNeighbour> 
  *  @brief  Vertex neighbour class.  
  *  @note  
  *  RhVertexNeighbour contains the north vertex id, west vertex id, south vertex id and east vertex id, 
  *  also contains the location of the vertex in the tmesh.
*/
class RhVertexNeighbour
{
public:
	RhVertexNeighbour()
		:_north_vertex(-1),_west_vertex(-1),_south_vertex(-1),_east_vertex(-1){};
	~RhVertexNeighbour(){};

	/** Return the vertex column location in the tmesh. */
	int getTmeshCol(){return _tmesh_col;};
	/** Return the vertex row location in the tmesh. */
	int getTmeshRow(){return _tmesh_row;};
	/** Return the north vertex of the current vertex. */
	int getNorthVertex(){return _north_vertex;};
	/** Return the west vertex of the current vertex. */
	int getWestVertex(){return _west_vertex;};
	/** Return the south vertex of the current vertex. */
	int getSouthVertex(){return _south_vertex;};
	/** Return the east vertex of the current vertex. */
	int getEastVertex(){return _east_vertex;};

	/** Set the vertex column location in the tmesh. */
	void setTmeshCol(const int tmesh_col){_tmesh_col = tmesh_col;};
	/** Set the vertex row location in the tmesh. */
	void setTmeshRow(const int tmesh_row){_tmesh_row = tmesh_row;};
	/** Set the north vertex of the current vertex. */
	void setNorthVertex(const int north_vertex){_north_vertex = north_vertex;};
	/** Set the west vertex of the current vertex. */
	void setWestVertex(const int west_vertex){_west_vertex = west_vertex;};
	/** Set the south vertex of the current vertex. */
	void setSouthVertex(const int south_vertex){_south_vertex = south_vertex;};
	/** Set the east vertex of the current vertex. */
	void setEastVertex(const int east_vertex){_east_vertex = east_vertex;};

private:
	int _tmesh_col;			
	int _tmesh_row;			
	int _north_vertex;		
	int _west_vertex;		
	int _south_vertex;		
	int _east_vertex;		
};

/**  
  *  @class  <RhImageSpreader> 
  *  @brief  Image spreader class.  
  *  @note  
  *  RhImageSpreader is uesd to prepare the T-Image structure.
  */
class RhImageSpreader
{
public:
	RhImageSpreader(const RhTsplinePtr &rhtsp, const TDirection seed);
	~RhImageSpreader(){};
public:
	/** Derive all the linkloops of the faces. */
	void deriveLinkLoops();
	/** Derive orientation of links. */
	void deriveLinkOrientations(const int linkid);
	/** Derive start vertex, end vertex, left face, right face of edges. */
	void deriveEdges();
	/** Derive parameters of vertices. */
	void deriveVertexParameters(const int vertexid);
	/** Normalize parameters of vertices. */
	void normalizeParameters();
	/** Organize the indices of vertices. */
	void organizeVertexIndices();
	/** Normalize parameters of vertices. */
	void generateTMesh();
	/** Derive neighbours of vertices. */
	void deriveVertexLinkages();
	
	/** Find the linkloop by link pointer. */
	RhLinkLoopPtr findRhLinkLoop(const RhLinkPtr &link);
	/** Return the orientation of the link. */
	int getLinkOrientation(const int linkid){return _link_orientations(linkid);};

	/** Return the face by index. */
	RhFacePtr getFace(int index){return _faces[index];};
	/** Return the begin iterator of the faces. */
	RhFacVIterator getFacesBegin(){return _faces.begin();};
	/** Return the end iterator of the faces. */
	RhFacVIterator getFacesEnd(){return _faces.end();};
	/** Return the link by index. */
	RhLinkPtr getLink(int index){return _links[index];};
	/** Return the begin iterator of the links. */
	RhLnkVIterator getLinksBegin(){return _links.begin();};
	/** Return the end iterator of the links. */
	RhLnkVIterator getLinksEnd(){return _links.end();};
	/** Return the vertex by index. */
	RhVertexPtr getVertex(int index){return _vertices[index];};
	/** Return the begin iterator of the vertices. */
	RhVtxVIterator getVerticesBegin(){return _vertices.begin();};
	/** Return the end iterator of the vertices. */
	RhVtxVIterator getVerticesEnd(){return _vertices.end();};
	/** Return the edge by index. */
	RhEdgePtr getEdge(int index){return _edges[index];};
	/** Return the begin iterator of the edges. */
	RhEdgVIterator getEdgesBegin(){return _edges.begin();};
	/** Return the end iterator of the edges. */
	RhEdgVIterator getEdgesEnd(){return _edges.end();};
	/** Return the linkloop by index. */
	RhLinkLoopPtr getLinkNeighbour(int index){return _link_loops[index];};
	/** Return the begin iterator of the linkneighbours. */
	RhLnkLupVIterator getLinkNeighboursBegin(){return _link_loops.begin();};
	/** Return the end iterator of the linkneighbours. */
	RhLnkLupVIterator getLinkNeighboursEnd(){return _link_loops.end();};
	/** Return the edge neighbour by index. */
	RhEdgeNeighbourPtr getEdgeNeighbour(int index){return _edge_nbr[index];};
	/** Return the begin iterator of the edgeneighbours. */
	RhEdgNbrVIterator getEdgeNeighboursBegin(){return _edge_nbr.begin();};
	/** Return the end iterator of the edgeneighbours. */
	RhEdgNbrVIterator getEdgeNeighboursEnd(){return _edge_nbr.end();};
	/** Return all the vertex neighbours. */
	RhVtxNbrVector& getVertexNeighbours(){return _vertex_nbr;};
	/** Return the vertex neighbour by index. */
	RhVertexNeighbourPtr getVertexNeighbour(int index){return _vertex_nbr[index];};
	/** Return the begin iterator of the vertexneighbours. */
	RhVtxNbrVIterator getVertexNeighboursBegin(){return _vertex_nbr.begin();};
	/** Return the end iterator of the vertexneighbours. */
	RhVtxNbrVIterator getVertexNeighboursEnd(){return _vertex_nbr.end();};
	/** Return the orientation of all the links. */
	ColumnVector getAllLinkOrientation(){return _link_orientations;};
	/** Return s parameter of vertex by index. */
	Real getVertexSParameter(int index){return _vertex_paramter(index,1);};
	/** Return t parameter of vertex by index. */
	Real getVertexTParameter(int index){return _vertex_paramter(index,2);};
	/** Return the tmesh. */
	Matrix getTmesh(){return _tmesh;};
protected:
	/** Return the linkloop of the face. */
	RhLinkLoopPtr getLinkLoop(const RhFacePtr &face);
	/** Find the link by id. */
	RhLinkPtr findRhLink(const int linkid);	
	/** Get the next orientation of the link. */
	int getNextOrientation(const int orientation);
	/** Get the start vertex and end vertex of the edge. */
	void getEdgeStartEnd(const RhEdgePtr &edge, int &vertexstart, int &vertexend);
	/** Get the left face and right face of the edge. */
	void getAdjacentFace(const RhEdgePtr &edge, int &faceleft, int &faceright);
	/** Derive parameter of all the vertices. */
	void spreadParameter(const int linkid, const int vertexid);
	/** Get the parameter using the orientation and length of the edge. */
	void getIncParameters(const int orientation, const double edgelength, double &vertex_s, double &vertex_t);
	/** Get the other vertex of the edge. */
	int getOtherVertex(const int edgeid, const int vertexid);
	/** Set the neighbour vertex of the vertex by orientation. */
	void setLinkage(const int vertexid, const int linkedvertex, const int orientation);
private:
	RhFacVector _faces;					
	RhLnkVector _links;					
	RhVtxVector _vertices;				
	RhEdgVector _edges;					
	RhLnkLupVector _link_loops;			
	RhEdgNbrVector _edge_nbr;			
	RhVtxNbrVector _vertex_nbr;			
	ColumnVector _link_orientations;	
	Matrix _vertex_paramter;			
	ColumnVector _vertex_flag;			
	Matrix _tmesh;						
};

/**  
  *  @class  <RotMatrix> 
  *  @brief  Rotate the newmat matrix.  
  *  @note  
  *  Rotate the newmat matrix in counter clockwise.  
*/
class RotMatrix
{
public:
	static RotMatrix* Instance();
	/** Rotate the matrix in counter clockwise by num times. */
	Matrix rot90(Matrix &mt, int num =1);
private:
	static RotMatrix* _instance;
	Matrix rot90base(const Matrix &mt);
	RotMatrix(){};
	~RotMatrix(){};
};

/**  
  *  @class  <RhKnot> 
  *  @brief  Knot class.  
  *  @note  
  *  RhKnot contains the vertex id shared by multiple knot, the multiplicity, 
  *  a set of control point id corresponding to the multiple knot and the primary knot id.
*/
class RhKnot
{
public:
	RhKnot():
	  _vertex(-1),_multiplicity(0),_prime_id(-1){};
	~RhKnot(){};

	/** Set the vertex belong to the knot. */
	void setVertex(const int id){_vertex = id;};
	/** Calculate the multiplicity of the vertex belong to the knot. */
	void multiplicity(){_multiplicity++;};
	/** Set the prime knot id. */
	void setPrime(const int id){_prime_id = id;};
	/** Add the control point id. */
	void addControlPointId(const int id){_control_point_ids.push_back(id);};

	/** Return the prime knot id. */
	int getPrime(){return _prime_id;};
private:
	int _vertex;				
	int _multiplicity;			
	VInt _control_point_ids;	
	int _prime_id;				
};

/**  
  *  @class  <RhMKnot> 
  *  @brief  Multi knot class.  
  *  @note  
  *  RhMKnot contains a set of dimensions and grips.
*/
class RhMKnot
{
public:
	RhMKnot(){};
	~RhMKnot(){};

	/** Set the dimension of the knot. */
	void setDims(const VInt &dims){_dims = dims;};
	/** Set the grips of the knot. */
	void setGrips(const VInt &grips){_grips = grips;};

	/** Return the dimension of the knot. */
	int dim(const int index){return _dims[index];};
	/** Return the grips of the knot. */
	int grip(const int index){return _grips[index];};

private:
	VInt _dims;		
	VInt _grips;	
};

/**  
  *  @class  <RhSimpleKnot> 
  *  @brief  Simple knot class.  
  *  @note  
  *  RhSimpleKnot contains the the vertex id, control point id, middle flag,
  *  north knot id, west knot id, south knot id and east knot id.
*/
class RhSimpleKnot: public std::enable_shared_from_this<RhSimpleKnot>
{
public:
	RhSimpleKnot()
		:_vertex(-1),_control_point(-1),_is_middle(0),_id(-1)
		,_north_knot(-1),_west_knot(-1),_south_knot(-1),_east_knot(-1)
	{};
	~RhSimpleKnot(){};
	/** Check if the RhSimpleKnot is a RhComplexKnot. */
	virtual RhComplexKnotPtr asComplex(){return 0;};

	/** Add RhSimpleKnot to the RhComplexKnot. */
	virtual void addSimpleKnot(const RhSimpleKnotPtr &knot, const int nrows, const int ncols){};

	/** Set the vertex of the RhSimpleKnot. */
	void setVertex(const int vertex){_vertex = vertex;};
	/** Set the control point of the RhSimpleKnot. */
	void setPoint(const int point){_control_point = point;};
	/** Set the middle flag of the RhSimpleKnot. */
	void setMiddle(const int ismiddle){_is_middle = ismiddle;};
	/** Set the id of the RhSimpleKnot. */
	void setId(const int id){_id = id;};
	/** Set the north knot of the RhSimpleKnot. */
	void setNorthKnot(const int knot){_north_knot = knot;};
	/** Set the west knot of the RhSimpleKnot. */
	void setWestKnot(const int knot){_west_knot = knot;};
	/** Set the south knot of the RhSimpleKnot. */
	void setSouthKnot(const int knot){_south_knot = knot;};
	/** Set the east knot of the RhSimpleKnot. */
	void setEastKnot(const int knot){_east_knot = knot;};

	/** Return the vertex of the RhSimpleKnot. */
	int getVertex(){return _vertex;};
	/** Return the control point of the RhSimpleKnot. */
	int getPoint(){return _control_point;};
	/** Return the middle flag of the RhSimpleKnot. */
	int isMiddle(){return _is_middle;};
	/** Return the north knot of the RhSimpleKnot. */
	int getNorth(){return _north_knot;};
	/** Return the west knot of the RhSimpleKnot. */
	int getWest(){return _west_knot;};
	/** Return the south knot of the RhSimpleKnot. */
	int getSouth(){return _south_knot;};
	/** Return the east knot of the RhSimpleKnot. */
	int getEast(){return _east_knot;};
private:
	int _vertex;			 
	int _control_point;		 
	int _is_middle;			 
	int _id;				 
	int _north_knot;		 
	int _west_knot;			 
	int _south_knot;		 
	int _east_knot;			 
};

/**  
  *  @class  <RhComplexKnot> 
  *  @brief  Complex knot class.  
  *  @note  
  *  RhComplexKnot contains a set of RhSimpleKnot shared the same vertex.
*/
class RhComplexKnot : public RhSimpleKnot
{
public:
	RhComplexKnot(const int nrows, const int ncols);
	~RhComplexKnot(){};
	/** Check if the RhSimpleKnot is a RhComplexKnot. */
	virtual RhComplexKnotPtr asComplex();

	/** Return the RhSimpleKnot by (nrows, ncols). */
	RhSimpleKnotPtr operator()(const int nrows, const int ncols);
	
	/** Add RhSimpleKnot to the RhComplexKnot. */
	void addSimpleKnot(const RhSimpleKnotPtr &knot, const int nrows, const int ncols);
	/** Rotate the RhComplexKnot in counter clockwise. */
	void rotate(int num);

	/** Return the row dimension of the RhComplexKnot. */
	int nrows(){return _matrix.nrows();};
	/** Return the column dimension of the RhComplexKnot. */
	int ncols(){return _matrix.ncols();};
private:
	RhSmpKntVector _knot;	
	Matrix _matrix;
	int _id;
};

/**  
  *  @class  <RhKnotMatrix> 
  *  @brief  Knot matrix class.  
  *  @note  
  *  RhKnotMatrix contains all the RhSimpleKnot.
*/
class RhKnotMatrix
{
public:
	RhKnotMatrix(const int nrows, const int ncols);
	~RhKnotMatrix(){};

	/** Return RhSimpleKnot by (nrows, ncols). */
	RhSimpleKnotPtr operator()(const int nrows, const int ncols);

	/** Add RhSimpleKnot to the RhKnotMatrix. */
	void addKnot(const RhSimpleKnotPtr &knot, const int nrows, const int ncols);
private:
	RhSmpKntVector _knots;
	Matrix _matrix;
	int _id;
};

/**  
  *  @class  <RhKnotIdMatrix> 
  *  @brief  KnotId matrix class.  
  *  @note  
  *  RhKnotIdMatrix is used to assign the index for the RhSimpleKnot.
*/
class RhKnotIdMatrix
{
public:
	RhKnotIdMatrix(int row, int col);
	~RhKnotIdMatrix(){};

	/** Return RhKnotIdMatrix by (nrows, ncols). */
	Matrix operator()(const int nrows, const int ncols);

	/** Add KnotId Matrix to the RhKnotIdMatrix. */
	void addKnotid(const Matrix &id, const int nrows, const int ncols);
private:
	vector<Matrix> _complexid;
	Matrix _matrix;
	int _id;
};

/**  
  *  @class  <RhKnotConstruct> 
  *  @brief  Knot construct class.  
  *  @note  
  *  RhKnotConstruct is used to prepare the knot and multi knot structures.
*/
class RhKnotConstruct
{
public:
	/** Construct the RhKnot and RhMKnot by using the grips and compound grips. */
	RhKnotConstruct(const RhGrpVector &grips, const RhCgtVector &cgs, const int vsize);
	~RhKnotConstruct(){};
	
	/** Return the RhKnot by vertex id . */
	RhKnotPtr getKnot(int vertexid)
	{
		if(vertexid>=0 && vertexid<_knots.size())
			return _knots[vertexid];
		else
			cout<<"Knots: out of range."<<endl;
		return NULL;
	};
	/** Return the RhMKnot by vertex id . */
	RhMKnotPtr getMKnot(int vertexid)
	{
		if(vertexid>=0 && vertexid<_mknots.size())
			return _mknots[vertexid];
		else
			cout<<"MultiKnots: out of range."<<endl;
		return NULL;
	}
private:
	RhKntVector _knots;
	RhMKntVector _mknots;
	int _knot_num;
};

/**  
  *  @class  <RhConnectSpreader> 
  *  @brief  Connect spreader class.  
  *  @note  
  *  RhConnectSpreader is used to prepare the T-Connect structure.
*/
class RhConnectSpreader
{
public:
	RhConnectSpreader(const RhTsplinePtr &rhtsp, const RhImageSpreaderPtr &imgspr);
	~RhConnectSpreader(){};

	/** Construct knot matrix . */
	void constructKnotMatrix(const Matrix &tmesh);
	/** Derive the neighbours of all knots . */
	void deriveKnotLinkages(const Matrix &tmesh);
	/** Return RhSimpleKnot by index . */
	RhSimpleKnotPtr getSimpleKnot(int index){return _simple_knots[index];};
	/** Return the begin iterator of RhSimpleKnots. */
	RhSmpKntVIterator getSimpleKnotsBegin(){return _simple_knots.begin();};
	/** Return the end iterator of RhSimpleKnots. */
	RhSmpKntVIterator getSimpleKnotsEnd(){return _simple_knots.end();};
protected:
	/** Construct RhSimpleKnot by vertex id . */
	RhSimpleKnotPtr constructKnots(const int vertexid);
	/** Convert direction to orientation . */
	int direction2Orientation(const std::string &direction);
	/** Return the rotation angle by orientation . */
	int orientation2Rotation(const int &orientation);
	/** Organize the inner linkage of the RhComplexKnot . */
	void organizeInnerLinkage(const Matrix &complexid);
	/** Return the north knotid matrix of the vertex. */
	Matrix getNorthComplexKnotId(const Matrix &complexid);
	/** Return the south knotid matrix of the vertex. */
	Matrix getSouthComplexKnotId(const Matrix &complexid);
	/** Return the west knotid matrix of the vertex. */
	Matrix getWestComplexKnotId(const Matrix &complexid);
	/** Return the east knotid matrix of the vertex. */
	Matrix getEastComplexKnotId(const Matrix &complexid);
	/** Return the vertex id shared by the RhComplexKnot. */
	int getVertexFromComplexId(const Matrix &complexid);
	/** Organize the north linkage of the RhComplexKnot . */
	void organizeNorthLinkage(const Matrix &complexid, const Matrix &northcomplexid);
	/** Organize the south linkage of the RhComplexKnot . */
	void organizeSouthLinkage(const Matrix &complexid, const Matrix &southcomplexid);
	/** Organize the west linkage of the RhComplexKnot . */
	void organizeWestLinkage(const Matrix &complexid, const Matrix &westcomplexid);
	/** Organize the east linkage of the RhComplexKnot . */
	void organizeEastLinkage(const Matrix &complexid, const Matrix &eastcomplexid);
	/** Return the north tip of the knot id matrix. */
	int getNorthTipFromComplexId(const Matrix &complexid);
	/** Return the south tip of the knot id matrix. */
	int getSouthTipFromComplexId(const Matrix &complexid);
	/** Return the west tip of the knot id matrix. */
	int getWestTipFromComplexId(const Matrix &complexid);
	/** Return the east tip of the knot id matrix. */
	int getEastTipFromComplexId(const Matrix &complexid);
	/** Get the center knot location of the knot id matrix. */
	void getCenterOfComplexKnotId(const Matrix &complexid, int &midrow, int &midcol);
private:
	RhKnotConstructPtr _knot_construct;
	RhKnotMatrixPtr _knot_matrix;
	RhKnotIdMatrixPtr _knotid_matrix;
	RhSmpKntVector _simple_knots;
	RhVtxVector _vertices;
	RhVtxNbrVector _vertex_nbr;
	ColumnVector _link_orientations;
};

#endif
