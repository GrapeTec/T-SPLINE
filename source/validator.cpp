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

#include <validator.h>
#include <sstream>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

TCheck::TCheck(const TObjectPtr &object) :
	_object(object)
{

}

TCheck::~TCheck()
{

}

TCheckPtr TCheck::asTCheck()
{
	return castPtr<TCheck>(shared_from_this());
}

TCheck& TCheck::operator<<( const std::string& str )
{
	_description += str;
	return *this;
}

TMessage::TMessage(const TObjectPtr &object) :
	TCheck(object)
{

}

TMessage::~TMessage()
{

}

TMessagePtr TMessage::asTMessage()
{
	return castPtr<TMessage>(shared_from_this());
}

TWarning::TWarning(const TObjectPtr &object) :
	TCheck(object)
{

}

TWarning::~TWarning()
{

}

TWarningPtr TWarning::asTWarning()
{
	return castPtr<TWarning>(shared_from_this());
}

TError::TError(const TObjectPtr &object) :
	TCheck(object)
{

}

TError::~TError()
{

}

TErrorPtr TError::asTError()
{
	return castPtr<TError>(shared_from_this());
}

TValidator::TValidator( const TSplinePtr &spline ) : 
	_spline(spline)
{

}

TValidator::~TValidator()
{

}

void TValidator::checkSpline()
{

}

void TValidator::repairSpline()
{

}

void TValidator::checkVertices()
{
	TImagePtr image = _spline->getTImage();
	TVtxVIterator iter = image->vertexIteratorBegin();
	for (;iter!=image->vertexIteratorEnd();iter++)
	{
		TCheckPtr check = checkVertex(*iter);
		if (!check) continue;

		if (TMessagePtr message = check->asTMessage())
		{
			_messages.push_back(message);
		}
		else if (TWarningPtr warning = check->asTWarning())
		{
			_warnings.push_back(warning);
		}
		else if (TErrorPtr error = check->asTError())
		{
			_errors.push_back(error);
		}
	}
}

TCheckPtr TValidator::checkVertex( const TVertexPtr &vertex )
{
	TCheckPtr check = 0;
	bool redundant_north = (vertex == vertex->getNorthTVertex());
	bool redundant_west = (vertex == vertex->getWestTVertex());
	bool redundant_south = (vertex == vertex->getSouthTVertex());
	bool redundant_east = (vertex == vertex->getEastTVertex());

	if (redundant_north || redundant_west || redundant_south || redundant_east)
	{
		check = makePtr<TWarning>(vertex);
	}
	
	return check;
}

#ifdef use_namespace
}
#endif