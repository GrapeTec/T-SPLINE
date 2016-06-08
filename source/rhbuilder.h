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

/**  @file  [rhbuilder]  
  *  @brief  Build the tspline structure from the Rhino T-Spline file.
  *  @author  <Wenlei Xiao>  
  *  @date  <2016.03.14>  
  *  @version  <v1.0>  
  *  @note  
  *  
*/ 

#ifndef RHBUILDER
#define RHBUILDER

#include <tspline.h>
#include <factory.h>
#include <rhparser.h>
#include <rhspreader.h>
#include <sstream>

#ifdef use_namespace
using namespace TSPLINE;
#endif

DECLARE_SMARTPTR(RhBuilder);

class RhBuilder
{
public:
	/** Build the tspline structure from the Rhino T-Spline file. */
	RhBuilder(const string &filename);
	~RhBuilder();

	/** Return the tspline pointer. */
	TSplinePtr findTSpline(){return _factory->findTSpline();};
	/** Return the tspline group. */
	TGroupPtr findTGroup(){return _factory->findTGroup();};
	/** Find the TFace from face name. */
	void findTFaceNames(std::vector<std::string> &faces){_factory->findTObjectNames(faces, TSPLINE::E_TFACE);};
protected:
	TSplinePtr buildTSpline(const RhTsplinePtr &rhtsp);

	/** Create tspline. */
	void createTSpline(const RhTsplinePtr &rhtsp);
	/** Create T-Image. */
	void createTImage(const RhTsplinePtr &rhtsp);
	/** Create T-Connect. */
	void createTConnect(const RhTsplinePtr &rhtsp);
	/** Create T-Pointset. */
	void createTPointset(const RhTsplinePtr &rhtsp);
	/** Create TVertices. */
	void createTVertices(const RhImageSpreaderPtr &imgsp);
	/** Create TEdges. */
	void createTEdges(const RhTsplinePtr &rhtsp);
	/** Create TLinks. */
	void createTLinks(const RhTsplinePtr &rhtsp);
	/** Create TEdgeConditions. */
	void createTEdgeConditions(const RhTsplinePtr &rhtsp);
	/** Create TFaces. */
	void createTFaces(const RhTsplinePtr &rhtsp);
	/** Create TNodes. */
	void createTNodes(const RhConnectSpreaderPtr &consp);
	/** Create TPoints. */
	void createTPoints(const RhTsplinePtr &rhtsp);

	/** Patch tspline. */
	void patchTSpline(const RhTsplinePtr &rhtsp);
	/** Patch T-Image. */
	void patchTImage(const RhTsplinePtr &rhtsp);
	/** Patch T-Connect. */
	void patchTConnect(const RhTsplinePtr &rhtsp);
	/** Patch T-Pointset. */
	void patchTPointset(const RhTsplinePtr &rhtsp);
	/** Patch TVertices. */
	void patchTVertices(const RhImageSpreaderPtr &imgsp);
	/** Patch TEdges. */
	void patchTEdges(const RhImageSpreaderPtr &imgsp);
	/** Patch TLinks. */
	void patchTLinks(const RhImageSpreaderPtr &imgsp);
	/** Patch TEdgeConditions. */
	void patchTEdgeConditions(const RhTsplinePtr &rhtsp);
	/** Patch TFaces. */
	void patchTFaces(const RhImageSpreaderPtr &imgsp);
	/** Patch TNodes. */
	void patchTNodesAndTPoints(const RhConnectSpreaderPtr &consp);

	/** Prepate TObjects. */
	void prepareTObjects();
private:
	/** Return the link orientation. */
	bool getLinkBinaryOrientation(const int linkid, const RhImageSpreaderPtr &imgsp);
	/** Return node name by id. */
	string getNodeName(int id);

	/** Create vertex name by id. */
	string vId(int id) { string s = "v" + to_string((long long)id); return s; }
	/** Create edge name by id. */
	string eId(int id) { string s = "e" + to_string((long long)id); return s; }
	/** Create link name by id. */
	string lId(int id) { string s = "l" + to_string((long long)id); return s; }
	/** Create edge condition name by id. */
	string ecId(int id) { string s = "ec" + to_string((long long)id); return s; }
	/** Create face name by id. */
	string fId(int id) { string s = "f" + to_string((long long)id); return s; }
	/** Create node name by id. */
	string nId(int id) { string s = "n" + to_string((long long)id); return s; }
	/** Create point name by id. */
	string pId(int id) { string s = "p" + to_string((long long)id); return s; }
private:
	RhParserPtr _parser;
	TFactoryPtr _factory;
};

#endif