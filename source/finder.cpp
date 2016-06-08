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

#include <finder.h>
#include <visitor.h>
#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

IdFinder::IdFinder( const unsigned int id ) : _id(id)
{

}

bool IdFinder::operator()( TObjectPtr object )
{
	if (object)
	{
		return object->getId() == _id;
	}
	else
	{
		return false;
	}
}

NameFinder::NameFinder( const string &name ) : _name(name)
{

}

bool NameFinder::operator()( TObjectPtr object )
{
	if (object)
	{
		return object->getName() == _name;
	}
	else
	{
		return false;
	}
}

TypeFinder::TypeFinder( const TObjType type ) : _type(type)
{

}

bool TypeFinder::operator()( TObjectPtr object )
{
	if (object)
	{
		switch (_type)
		{
		case TSPLINE::E_TOBJECT:
			return castBool(object->asTObject());
			break;
		case TSPLINE::E_TGROUP:
			return castBool(object->asTGroup());
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

TFinder::TFinder( const TGroupPtr &group ) :
	_group(group)
{

}

TFinder::~TFinder()
{

}

void TFinder::findObjectNamesByType( std::vector<std::string> &names, TObjType type )
{
	TObjVIterator biter = _group->iteratorBegin();
	TObjVIterator eiter = _group->iteratorEnd();
	while (biter != eiter)
	{
		TObjVIterator iter = std::find_if(biter, eiter, TypeFinder(type));
		if (iter != eiter)
		{
			names.push_back((*iter)->getName());
			biter = ++iter;
		}
		else
		{
			biter = iter;
		}
	}
}

// void TFinder::findObjectsByType( TObjVector &objects, TObjType type )
// {
// 	TObjVIterator biter = _group->iteratorBegin();
// 	TObjVIterator eiter = _group->iteratorEnd();
// 
// 	while (biter != eiter)
// 	{
// 		TObjVIterator iter = std::find_if(biter, eiter, TypeFinder(type));
// 		if (iter != eiter)
// 		{
// 			objects.push_back(*iter);
// 			biter = ++iter;
// 		}
// 		else
// 		{
// 			biter = iter;
// 		}
// 	}
// }

TObjectPtr TFinder::findObjectById( unsigned int id )
{
	TObjVIterator biter = _group->iteratorBegin();
	TObjVIterator eiter = _group->iteratorEnd();
	TObjVIterator iter = find_if(biter, eiter, IdFinder(id));
	if (iter != eiter)
	{
		return *iter;
	}
	return 0;
}

TObjectPtr TFinder::findObjectByName( const string &name )
{
	TObjVIterator biter = _group->iteratorBegin();
	TObjVIterator eiter = _group->iteratorEnd();
	TObjVIterator iter = std::find_if(biter, eiter, NameFinder(name));
	if (iter != eiter)
	{
		return *iter;
	}
	return 0;
}

TObjectPtr TFinder::findObjectByType( TObjType type )
{
	TObjVIterator biter = _group->iteratorBegin();
	TObjVIterator eiter = _group->iteratorEnd();
	TObjVIterator iter = std::find_if(biter, eiter, TypeFinder(type));
	return (*iter);
}

TFacePtr TFinder::findTFaceByParameter( const Parameter &parameter, const std::string &mesh_name /* = "" */ )
{
	TImagePtr image;
	if (!mesh_name.empty())
	{
		image = castPtr<TImage>(findObjectByName(mesh_name));
	}
	if (!image)
	{
		image = castPtr<TImage>(findObjectByType(E_TIMAGE));
	}
	if (!image) return 0;
	
	TFacVIterator fbiter = image->faceIteratorBegin();
	TFacVIterator feiter = image->faceIteratorEnd();
	TFacVIterator fiter = std::find_if(fbiter, feiter, TFaceVisitorCheckParameterInside(parameter));

	if (fiter != feiter)
	{
		return *fiter;
	}
	else
	{
		return 0;
	}
}

TLinkPtr TFinder::findTLinkByStartEndVertices( const TVertexPtr &start, const TVertexPtr &end )
{
	TLnkVector links;
	findObjects<TLink>(links);

	TLnkVIterator link_iter = std::find_if(links.begin(), links.end(), 
		TLinkVisitorCheckStartEndVertices(start, end));

	if (link_iter != links.end())
	{
		return *link_iter;
	}
	else
	{
		return 0;
	}

}

TSplinePtr TFinder::findTSpline()
{
	TObjectPtr object = findObjectByType(TSPLINE::E_TSPLINE);
	return castPtr<TSpline>(object);
}


#ifdef use_namespace
}
#endif