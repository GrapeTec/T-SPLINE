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
2016/03/31: Wenlei Xiao
- Doxygen comments added.
-------------------------------------------------------------------------------
*/

/**  @file  [finder]  
*  @brief  Finder classes.
  *  @author  <Wenlei Xiao>
  *  @date  <2016.03.31>  
  *  @version  <v1.0>  
  *  @note  
  *  The finder classes can facilitate the finding processes for STL containers.   
*/

#ifndef FINDER_H
#define FINDER_H

#include <tspline.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif
	
/**  
  *  @class  <IdFinder> 
  *  @brief  Find a T-object according its ID.
  *  @note  
  * IdFinder requires a ID of type int.
  * Example: std::find_if(container.begin(), container.end(), IdFinder(id)).
*/
struct IdFinder
{
	IdFinder(const unsigned int id);
	bool operator() (TObjectPtr object);
private:
	unsigned int _id;
};

/**  
  *  @class  <NameFinder> 
  *  @brief  Find a T-object according its name.
  *  @note  
  * IdFinder requires a name of type std::string.
  * Example: std::find_if(container.begin(), container.end(), NameFinder(name)).
*/
struct NameFinder
{
	NameFinder(const string &name);
	bool operator() (TObjectPtr object);
private:
	std::string _name;
};

/**  
  *  @class  <TypeFinder> 
  *  @brief  Find a T-object according its type.
  *  @note  
  * IdFinder requires a type of type enum TObjType.
  * Example: std::find_if(container.begin(), container.end(), TypeFinder(type)).
*/
struct TypeFinder
{
	TypeFinder(const TObjType type);
	bool operator() (TObjectPtr object);
private:
	TObjType _type;
};

/**  
  *  @class  <TObjectTraits> 
  *  @brief  T-object traits.
  *  @note  
  * TObjectTraits can help to find all T-objects using a single template function.
*/
template <typename ObjType>
struct TObjectTraits
{
	typedef typename ObjType::TCategory TCategory;
};

/**  
  *  @class  <TFinder> 
  *  @brief  The global finder class.
  *  @note  
  * TFinder can be used to find various properties in the T-spline data structures.
*/
class TFinder
{
public:
	TFinder(const TGroupPtr &group);
	~TFinder();
public:
	/** Find T-objects' names according to a specified type*/
	void findObjectNamesByType(std::vector<std::string> &names, TObjType type);
	/** Find a T-object according to its ID*/
	TObjectPtr findObjectById(unsigned int id);
	/** Find a T-object according to its name*/
	TObjectPtr findObjectByName(const string &name);
	/** Find a T-object according to its type*/
	TObjectPtr findObjectByType(TObjType type);
	/** Find a T-face according to a parameter inside*/
	TFacePtr findTFaceByParameter(const Parameter &parameter, const std::string &mesh_name = "");
	/** Find a T-link according to its start and end T-vertices*/
	TLinkPtr findTLinkByStartEndVertices(const TVertexPtr &start, const TVertexPtr &end);

public:
	/** Find the T-spline root*/
	TSplinePtr findTSpline();

public:
	/** Template function to find a T-object by its name*/
	template<class T>
	std::shared_ptr<T> findByName(const std::string &name)
	{
		return castPtr<T>(findObjectByName(name));
	}
	/** Template function to find a vector of T-objects by its type*/
	template<class T>
	void findObjects(std::vector<std::shared_ptr<T>> &objects)
	{	// fixed added typename
		doFindObjects(objects, typename TObjectTraits<T>::TCategory());
	}
protected:
	template<class T>
	void doFindObjects(std::vector<std::shared_ptr<T>> &objects, TObjectTag)
	{
		TObjVIterator biter = _group->iteratorBegin();
		TObjVIterator eiter = _group->iteratorEnd();

		for (TObjVIterator iter=biter;iter!=eiter;iter++)
		{
			TObjectPtr object = *iter;
			objects.push_back(object);
		}
	}
	template<class T>
	void doFindObjects(std::vector<std::shared_ptr<T>> &objects, TGroupTag)
	{
		TObjVIterator biter = _group->iteratorBegin();
		TObjVIterator eiter = _group->iteratorEnd();

		for (TObjVIterator iter=biter;iter!=eiter;iter++)
		{
			TObjectPtr object = *iter;
			TGroupPtr group = object->asTGroup();
			if (group) objects.push_back(group);
		}
	}
	template<class T>
	void doFindObjects(std::vector<std::shared_ptr<T>> &objects, TMappableObjectTag)
	{
		TObjVIterator biter = _group->iteratorBegin();
		TObjVIterator eiter = _group->iteratorEnd();

		for (TObjVIterator iter=biter;iter!=eiter;iter++)
		{
			TObjectPtr object = *iter;
			TMappableObjectPtr mapper = object->asTMappableObject();
			if (mapper) objects.push_back(mapper);
		}
	}
	template<class T>
	void doFindObjects(std::vector<std::shared_ptr<T>> &objects, TVertexTag)
	{
		TObjVIterator biter = _group->iteratorBegin();
		TObjVIterator eiter = _group->iteratorEnd();

		for (TObjVIterator iter=biter;iter!=eiter;iter++)
		{
			TObjectPtr object = *iter;
			TVertexPtr vertex = object->asTVertex();
			if (vertex) objects.push_back(vertex);
		}
	}
	template<class T>
	void doFindObjects(std::vector<std::shared_ptr<T>> &objects, TEdgeTag)
	{
		TObjVIterator biter = _group->iteratorBegin();
		TObjVIterator eiter = _group->iteratorEnd();

		for (TObjVIterator iter=biter;iter!=eiter;iter++)
		{
			TObjectPtr object = *iter;
			TEdgePtr edge = object->asTEdge();
			if (edge) objects.push_back(edge);
		}
	}
	template<class T>
	void doFindObjects(std::vector<std::shared_ptr<T>> &objects, TLinkTag)
	{
		TObjVIterator biter = _group->iteratorBegin();
		TObjVIterator eiter = _group->iteratorEnd();

		for (TObjVIterator iter=biter;iter!=eiter;iter++)
		{
			TObjectPtr object = *iter;
			TLinkPtr link = object->asTLink();
			if (link) objects.push_back(link);
		}
	}
	template<class T>
	void doFindObjects(std::vector<std::shared_ptr<T>> &objects, TFaceTag)
	{
		TObjVIterator biter = _group->iteratorBegin();
		TObjVIterator eiter = _group->iteratorEnd();

		for (TObjVIterator iter=biter;iter!=eiter;iter++)
		{
			TObjectPtr object = *iter;
			TFacePtr face = object->asTFace();
			if (face) objects.push_back(face);
		}
	}
	template<class T>
	void doFindObjects(std::vector<std::shared_ptr<T>> &objects, TImageTag)
	{
		TObjVIterator biter = _group->iteratorBegin();
		TObjVIterator eiter = _group->iteratorEnd();

		for (TObjVIterator iter=biter;iter!=eiter;iter++)
		{
			TObjectPtr object = *iter;
			TImagePtr image = object->asTImage();
			if (image) objects.push_back(image);
		}
	}
	template<class T>
	void doFindObjects(std::vector<std::shared_ptr<T>> &objects, TNodeTag)
	{
		TObjVIterator biter = _group->iteratorBegin();
		TObjVIterator eiter = _group->iteratorEnd();

		for (TObjVIterator iter=biter;iter!=eiter;iter++)
		{
			TObjectPtr object = *iter;
			TNodePtr node = object->asTNode();
			if (node) objects.push_back(node);
		}
	}
	template<class T>
	void doFindObjects(std::vector<std::shared_ptr<T>> &objects, TNodeV4Tag)
	{
		TObjVIterator biter = _group->iteratorBegin();
		TObjVIterator eiter = _group->iteratorEnd();

		for (TObjVIterator iter=biter;iter!=eiter;iter++)
		{
			TObjectPtr object = *iter;
			TNodePtr node = object->asTNode();
			if (node)
			{	TVertex t; TNodeV4 v;
				TNodeV4Ptr nodev4 = node->asTNodeV4();
				if (nodev4) objects.push_back(nodev4);
			}
		}
	}
	template<class T>
	void doFindObjects(std::vector<std::shared_ptr<T>> &objects, TConnectTag)
	{
		TObjVIterator biter = _group->iteratorBegin();
		TObjVIterator eiter = _group->iteratorEnd();

		for (TObjVIterator iter=biter;iter!=eiter;iter++)
		{
			TGroup g;
			TObjectPtr object = *iter;
			TConnectPtr connect = object->asTConnect();
			if (connect) objects.push_back(connect);
		}
	}
	template<class T>
	void doFindObjects(std::vector<std::shared_ptr<T>> &objects, TPointTag)
	{
		TObjVIterator biter = _group->iteratorBegin();
		TObjVIterator eiter = _group->iteratorEnd();

		for (TObjVIterator iter=biter;iter!=eiter;iter++)
		{
			TObjectPtr object = *iter;
			TPointPtr point = object->asTPoint();
			if (point) objects.push_back(point);
		}
	}
	template<class T>
	void doFindObjects(std::vector<std::shared_ptr<T>> &objects, TPointsetTag)
	{
		TObjVIterator biter = _group->iteratorBegin();
		TObjVIterator eiter = _group->iteratorEnd();

		for (TObjVIterator iter=biter;iter!=eiter;iter++)
		{
			TObjectPtr object = *iter;
			TPointsetPtr points = object->asTPointset();
			if (points) objects.push_back(points);
		}
	}
	template<class T>
	void doFindObjects(std::vector<std::shared_ptr<T>> &objects, TSplineTag)
	{
		TObjVIterator biter = _group->iteratorBegin();
		TObjVIterator eiter = _group->iteratorEnd();

		for (TObjVIterator iter=biter;iter!=eiter;iter++)
		{
			TObjectPtr object = *iter;
			TSplinePtr spline = object->asTSpline();
			if (spline) objects.push_back(spline);
		}
	}
	template<class T>
	void doFindObjects(std::vector<std::shared_ptr<T>> &objects, TVertex2Tag)
	{
		TObjVIterator biter = _group->iteratorBegin();
		TObjVIterator eiter = _group->iteratorEnd();

		for (TObjVIterator iter=biter;iter!=eiter;iter++)
		{
			TObjectPtr object = *iter;
			TVertex2Ptr vertex = object->asTVertex2();
			if (vertex) objects.push_back(vertex);
		}
	}
private:
	TGroupPtr _group;
};

DECLARE_SMARTPTR(TFinder)

/**  
  *  @class  <TLocalFinder> 
  *  @brief  The local finder class.
  *  @note  
  * TLocalFinder can be used to narrow the search range, and require begin and end iterators .
*/
template<typename Iter>
class TLocalFinder
{
public:
	TLocalFinder(const Iter &begin, const Iter &end);
	~TLocalFinder();

public:
	/** Find a T-object according to its name*/
	Iter findObjectByName(const std::string& name);
	/** Check if the T-object is in the range*/
	bool has(const TObjectPtr &object);
private:
	Iter _begin;
	Iter _end;
};


template<typename Iter>
TLocalFinder<Iter>::TLocalFinder( const Iter &begin, const Iter &end ) :
	_begin(begin), _end(end)
{

}

template<typename Iter>
TLocalFinder<Iter>::~TLocalFinder()
{

}

template<typename Iter>
Iter TLocalFinder<Iter>::findObjectByName( const std::string& name )
{
	return std::find_if(_begin, _end, NameFinder(name));
}

template<typename Iter>
bool TLocalFinder<Iter>::has( const TObjectPtr &object )
{
	Iter iter = std::find(_begin, _end, object);
	if (iter != _end)
	{
		return true;
	}
	else
	{
		return false;
	}
}
#ifdef use_namespace
}
#endif


#endif
