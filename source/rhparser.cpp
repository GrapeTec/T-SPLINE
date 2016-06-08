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
#include <rhparser.h>
#include <sstream>

RhParser::RhParser( const string& filename )
{
	readFile(filename);
}

RhTsplinePtr RhParser::readFile( const string& filename )
{
	std::ifstream fin;
	fin.open(filename);
	string cmd;

	fin >> cmd;
	if (cmd.compare("#TS0200") != 0) return 0;
	_rh_tspline = makePtr<RhTspline>();
	_rh_tspline->filename = filename;
	skipLine(fin);

	fin >> cmd;
	if (cmd.compare("degree") == 0)
	{
		fin >> _rh_tspline->degree;
	}
	skipLine(fin);
	fin >> cmd;
	if (cmd.compare("cap-type") == 0)
	{
		fin >> _rh_tspline->cap_type;
	}
	skipLine(fin);
	fin >> cmd;
	if (cmd.compare("star-smoothness") == 0)
	{
		fin >> _rh_tspline->star_smoothness;
	}
	skipLine(fin);
	fin >> cmd;
	if (cmd.compare("units") == 0)
	{
		fin >> _rh_tspline->unit_value >> _rh_tspline->unit_name;
	}
	skipLine(fin);
	fin >> cmd;
	if (cmd.compare("force-bezier-end-conditions") == 0)
	{
		fin >> _rh_tspline->force_bezier_end_conditions;
	}
	skipLine(fin);
	while (!fin.eof())
	{
		fin >> cmd;
		if (cmd.compare("f") == 0)
		{
			extractFace(fin);
		}
		else if (cmd.compare("e") == 0)
		{
			extractEdge(fin);
		}
		else if (cmd.compare("ec") == 0)
		{
			extractEdgeCondition(fin);
		}
		else if (cmd.compare("v") == 0)
		{
			extractVertex(fin);
		}
		else if (cmd.compare("l") == 0)
		{
			extractLink(fin);
		}
		else if (cmd.compare("ver") == 0)
		{
			extractVersion(fin);
		}
		else if (cmd.compare("0m") == 0)
		{
			extractMeta(fin);
		}
		else if (cmd.compare("0g") == 0)
		{
			extractGrip(fin);
		}
		else if (cmd.compare("tol") == 0)
		{
			extractTolerance(fin);
		}
		else
		{
			skipLine(fin);
		}
	}
	return _rh_tspline;
}

bool RhParser::extractFace( ifstream &s )
{
	if (!detectLine(s))
	{
		_rh_tspline->faces.push_back(0);
		skipLine(s);
		return false;
	}
	RhFacePtr face = makePtr<RhFace>();
	s >> face->link >> face->flag;
	skipLine(s);
	_rh_tspline->faces.push_back(face);
	return castBool(face);
}

bool RhParser::extractEdge( ifstream &s )
{
	if (!detectLine(s))
	{
		_rh_tspline->edges.push_back(0);
		skipLine(s);
		return false;
	}
	RhEdgePtr edge = makePtr<RhEdge>();
	s >> edge->link >> edge->interval;
	skipLine(s);
	_rh_tspline->edges.push_back(edge);
	return castBool(edge);
}

bool RhParser::extractVertex( ifstream &s )
{
	if (!detectLine(s))
	{
		_rh_tspline->vertices.push_back(0);
		skipLine(s);
		return false;
	}
	RhVertexPtr vertex = makePtr<RhVertex>();
	s >> vertex->link >> vertex->direction;
	skipLine(s);
	_rh_tspline->vertices.push_back(vertex);
	return castBool(vertex);
}

bool RhParser::extractLink( ifstream &s )
{
	if (!detectLine(s))
	{
		_rh_tspline->links.push_back(0);
		skipLine(s);
		return false;
	}
	RhLinkPtr link = makePtr<RhLink>();
	s >> link->previous_link >> link->next_link >> link->opp_link 
		>> link->vertex >> link->face >> link->edge >> link->flag;
	skipLine(s);
	_rh_tspline->links.push_back(link);
	return castBool(link);
}

bool RhParser::extractEdgeCondition( ifstream &s )
{
	if (!detectLine(s))
	{
		_rh_tspline->edge_conditions.push_back(0);
		skipLine(s);
		return false;
	}
	RhEdgeConditionPtr edge_condition = makePtr<RhEdgeCondition>();
	s >> edge_condition->edge >> edge_condition->boundary_condition;
	skipLine(s);
	_rh_tspline->edge_conditions.push_back(edge_condition);
	return castBool(edge_condition);
}

bool RhParser::extractMeta( ifstream &s )
{
	if (!detectLine(s))
	{
		_rh_tspline->vertices.push_back(0);
		skipLine(s);
		return false;
	}
	string p1; s >> p1;
	if (p1.compare("odd-grip-map") == 0)
	{
		_rh_tspline->odd_grip_map = true;
	}
	else if (p1.compare("gvp") == 0)
	{
		RhGripPtr grip = makePtr<RhGrip>();
		s >> grip->index;
		grip->with_p = true;
		_rh_tspline->grips.push_back(grip);
	}
	else if (p1.compare("gv") == 0)
	{
		RhGripPtr grip = makePtr<RhGrip>();
		s >> grip->index;
		grip->with_p = false;
		_rh_tspline->grips.push_back(grip);
	}
	else if (p1.compare("cg") == 0)
	{
		RhCompoundGripTagPtr cgt = makePtr<RhCompoundGripTag>();
		s >> cgt->vertex >> cgt->valence;
		for (int i=0;i<cgt->valence;i++)
		{
			int dim = 0; s >> dim;
			cgt->dims.push_back(dim);
		}
		while (detectLine(s))
		{
			int grip = 0; s >> grip;
			cgt->grips.push_back(grip);
			skipBlank(s);
		}
		_rh_tspline->compound_grip_tags.push_back(cgt);
	}
	skipLine(s);
	return false;
}

bool RhParser::extractGrip( ifstream &s )
{
	if (!detectLine(s))
	{
		_rh_tspline->control_points.push_back(0);
		skipLine(s);
		return false;
	}
	RhPointPtr point = makePtr<RhPoint>();
	s >> point->x >> point->y >> point->z >> point->w;
	skipLine(s);
	_rh_tspline->control_points.push_back(point);
	return true;
}

bool RhParser::extractTolerance( ifstream &s )
{
	if (!detectLine(s))
	{
		_rh_tspline->tolerance = 0.0;
		skipLine(s);
		return false;
	}
	s >> _rh_tspline->tolerance;
	skipLine(s);
	return true;
}

bool RhParser::extractVersion( ifstream &s )
{
	if (!detectLine(s))
	{
		_rh_tspline->version = 0;
		skipLine(s);
		return false;
	}
	s >> _rh_tspline->version;
	skipLine(s);
	return true;
}

void RhParser::skipLine( ifstream &s )
{
	char c = s.peek();
	if (c != '\n')
	{
		char tmp[128];
		s.get(tmp, 128);
	}
	else
	{
		char c = s.get();
	}
}

void RhParser::skipBlank( ifstream &s )
{
	char t = s.peek();
	while (t == ' ' || t == '\t')
	{
		t = s.get();
		t = s.peek();
	}
}

bool RhParser::detectLine( ifstream &s )
{
	char t = s.peek();
	if (t == ' ' || t == '\t')
	{
		skipBlank(s);
		t = s.peek();
	}
	if (t == '\r' || t == '\n' || t == '#')
	{
		return false;
	}
	else
	{
		return true;
	}
}