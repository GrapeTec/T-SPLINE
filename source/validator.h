/*
T-SPLINE -- A T-spline object oriented library in C++
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
2016/04/02: Wenlei Xiao
- Doxygen comments added.
-------------------------------------------------------------------------------
*/


/**  @file  [validtor]  
  *  @brief  Validating classes 
  *  @author  <Wenlei Xiao>  
  *  @date  <2015.04.08>
  *  @version  <v1.0>  
  *  @note  
  *  This file contains the classes to validate the T-spline objects. (under development)
*/

#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <tspline.h>

#ifdef use_namespace
namespace TSPLINE {
	using namespace NEWMAT;
#endif

DECLARE_ASSISTANCES(TCheck, TChk)
DECLARE_ASSISTANCES(TMessage, TMsg)
DECLARE_ASSISTANCES(TWarning, TWrn)
DECLARE_ASSISTANCES(TError, TErr)

/**  
  *  @class  <TCheck> 
  *  @brief  T-check classes  
  *  @note  
  *  ...
*/
class TCheck : public std::enable_shared_from_this<TCheck>
{
public:
	TCheck(const TObjectPtr &object);
	virtual ~TCheck();
public:
	/// Return the pure pointer as a TCheck.
	virtual TCheckPtr asTCheck();
	/// Return the pure pointer as a TMessage.
	virtual TMessagePtr asTMessage() {return 0;}
	/// Return the pure pointer as a TWarning.
	virtual TWarningPtr asTWarning() {return 0;}
	/// Return the pure pointer as a TError.
	virtual TErrorPtr asTError() {return 0;}

public:
	void setDescription(const std::string& description) {_description = description;}
	const std::string getDescription() {return _description;}
	TCheck& operator<<(const std::string& str);
private:
	TObjectPtr _object;
	int _major_code;
	int _minor_code;
	std::string _description;
};

/**  
  *  @class  <TMessage> 
  *  @brief  T-message class
  *  @note  
  *  ...
*/
class TMessage : public TCheck
{
public:
	TMessage(const TObjectPtr &object);
	virtual ~TMessage();
public:
	/// return the pure pointer as a TMessage.
	virtual TMessagePtr asTMessage();

};

/**  
  *  @class  <TWarning> 
  *  @brief  T-warning class
  *  @note  
  *  ...
*/
class TWarning : public TCheck
{
public:
	TWarning(const TObjectPtr &object);
	virtual ~TWarning();
public:
	/// return the pure pointer as a TWarning.
	virtual TWarningPtr asTWarning();
};

/**  
  *  @class  <TError> 
  *  @brief  T-error class
  *  @note  
  *  ...
*/
class TError : public TCheck
{
public:
	TError(const TObjectPtr &object);
	virtual ~TError();
public:
	/// return the pure pointer as a TError.
	virtual TErrorPtr asTError();
};

/**  
  *  @class  <TValidator> 
  *  @brief  T-validator class
  *  @note  
  *  ...
*/
class TValidator
{
public:
	TValidator(const TSplinePtr &spline);
	~TValidator();

public:
	void checkSpline();
	void checkImage();
	void checkConnect();
	void checkPointset();

	void repairSpline();
	void repairImage();
	void repairConnect();
	void repairPointset();

	unsigned int sizeMessages();
	unsigned int sizeWarnings();
	unsigned int sizeErrors();

	TMsgVIterator messageIteratorBegin();
	TMsgVIterator messageIteratorEnd();
	TWrnVIterator warningIteratorBegin();
	TWrnVIterator warningIteratorEnd();
	TErrVIterator errorIteratorBegin();
	TErrVIterator errorIteratorEnd();
protected:
	void checkVertices();
	void checkPoints();
	TCheckPtr checkVertex(const TVertexPtr &vertex);
private:
	TSplinePtr _spline;
	TMsgVector _messages;
	TWrnVector _warnings;
	TErrVector _errors;	
};
DECLARE_ASSISTANCES(TValidator, TVld)

#ifdef use_namespace
}
#endif

#endif