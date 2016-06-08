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

2015/04/08: Wenlei Xiao
- Created.
2016/04/02: Yazui Liu
- Doxygen comments added.
-------------------------------------------------------------------------------
*/

/**  @file  [rhparser]  
  *  @brief  Parser the Rhino T-Spline file.
  *  @author  <Wenlei Xiao>  
  *  @date  <2016.03.14>  
  *  @version  <v1.0>  
  *  @note  
  *  
*/ 
#ifndef RHPARSER
#define RHPARSER

#include <utils.h>

#ifdef use_namespace
using namespace TSPLINE;
#endif

DECLARE_ASSISTANCES(RhObject, RhObj)
DECLARE_ASSISTANCES(RhFace, RhFac)
DECLARE_ASSISTANCES(RhEdge, RhEdg)
DECLARE_ASSISTANCES(RhVertex, RhVtx)
DECLARE_ASSISTANCES(RhLink, RhLnk)
DECLARE_ASSISTANCES(RhEdgeCondition, RhEdgCon)
DECLARE_ASSISTANCES(RhGrip, RhGrp)
DECLARE_ASSISTANCES(RhCompoundGripTag, RhCgt)
DECLARE_ASSISTANCES(RhPoint, RhPnt)
DECLARE_ASSISTANCES(RhTspline, RhTsp)

enum E_RDIRECTION {NORTH, WEST, SOUTH, EAST};

/**  
  *  @class  <RhObject> 
  *  @brief  The base class for all Rh objects.  
  *  @note  
  *  detailed  description  
*/ 
struct RhObject {};

/**  
  *  @class  <RhFace> 
  *  @brief  The definition of RhFace class.  
  *  @note  
  *  RhFace contains the link id and flag.
*/ 
struct RhFace : public RhObject
{
	int link;
	int flag;
};

/**  
  *  @class  <RhEdge> 
  *  @brief  The definition of RhEdge class.  
  *  @note  
  *  RhEdge contains the link id and interval.
*/
struct RhEdge : public RhObject
{
	int link;
	Real interval;
};

/**  
  *  @class  <RhVertex> 
  *  @brief  The definition of RhVertex class.  
  *  @note  
  *  RhVertex contains the link id and the direction,
*/
struct RhVertex : public RhObject
{
	int link;
	std::string direction;
};

/**  
  *  @class  <RhLink> 
  *  @brief  The definition of RhLink class.  
  *  @note  
  *  RhLink the previous link id, next link id, opposite link id, vertex id, face id, edge id and flag.
*/
struct RhLink : public RhObject
{
	int previous_link;
	int next_link;
	int opp_link;
	int vertex;
	int face;
	int edge;
	int flag;
};

/**  
  *  @class  <RhEdgeCondition> 
  *  @brief  The definition of RhEdgeCondition class.  
  *  @note  
  *  RhEdgeCondition contains the edge and the boundary condition.
*/
struct RhEdgeCondition : public RhObject
{
	int edge;
	int boundary_condition;
};

/**  
  *  @class  <RhGrip> 
  *  @brief  The definition of RhGrip class.  
  *  @note  
  *  RhGrip contains the vertex id and the primary flag.
*/
struct RhGrip
{
	int index;
	bool with_p;
};

/**  
  *  @class  <RhCompoundGripTag> 
  *  @brief  The definition of RhCompoundGripTag class.  
  *  @note  
  *  RhCompoundGripTag contains the vertex id and its valence, 
  *  a set of dimensions and control point ids.
*/
struct RhCompoundGripTag
{
	int vertex;
	int valence;
	vector<int> dims;
	vector<int> grips;
};

/**  
  *  @class  <RhPoint> 
  *  @brief  The definition of RhPoint class.  
  *  @note  
  *  RhPoint contains the homogeneous coordinates of the control point.
*/
struct RhPoint : public RhObject
{
	Real x, y, z, w;
};

/**  
  *  @class  <RhTspline> 
  *  @brief  The definition of RhTspline class.  
  *  @note  
  *  Store all the rhino T-spline elements.   
*/
struct RhTspline : public RhObject
{
	RhTspline() :
		degree(0), 
		cap_type(0), 
		star_smoothness(0), 
		force_bezier_end_conditions(0),
		odd_grip_map(false),
		tolerance(0.0),
		version(0) {}
	string filename;
	int degree;
	int cap_type;
	int star_smoothness;
	int force_bezier_end_conditions;
	Real unit_value;
	string unit_name;
	RhFacVector faces;
	RhEdgVector edges;
	RhVtxVector vertices;
	RhLnkVector links;
	RhEdgConVector edge_conditions;
	bool odd_grip_map;
	RhGrpVector grips;
	RhCgtVector compound_grip_tags;
	RhPntVector control_points;
	Real tolerance;
	int version;
};

/**  
  *  @class  <RhParser> 
  *  @brief  The definition of RhParser class.  
  *  @note  
  *  Parse the rhino T-spline format file.  
*/
class RhParser
{
public:
	RhParser(const string& filename);
	~RhParser(){};

protected:
	/** Read file. */
	RhTsplinePtr readFile(const string& filename);
public:
	/** Return the RhTspline pointer. */
	RhTsplinePtr getRhTspline() const { return _rh_tspline; }

protected:
	/** Extract all faces from file. */
	bool extractFace(ifstream &s);
	/** Extract all edges from file. */
	bool extractEdge(ifstream &s);
	/** Extract all vertices from file. */
	bool extractVertex(ifstream &s);
	/** Extract all links from file. */
	bool extractLink(ifstream &s);
	/** Extract all edgeconditions from file. */
	bool extractEdgeCondition(ifstream &s);
	/** Extract all meta0 from file. */
	bool extractMeta(ifstream &s);
	/** Extract all grips from file. */
	bool extractGrip(ifstream &s);
	/** Extract tolerance from file. */
	bool extractTolerance(ifstream &s);
	/** Extract version from file. */
	bool extractVersion(ifstream &s);

	/** Skip one line. */
	void skipLine(ifstream &s);
	/** Skip blank. */
	void skipBlank(ifstream &s);
	/** Check if the line has a T-spline element. */
	bool detectLine(ifstream &s);
private:

	RhTsplinePtr _rh_tspline;	
};

DECLARE_SMARTPTR(RhParser);


#endif