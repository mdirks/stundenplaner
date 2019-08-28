//
// C++ Interface: %{MODULE}
//
// Description: 
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef STRINGPROPERTY_H
#define STRINGPROPERTY_H

#include <string>
#include "../persistence/pobject.h"
#include "repositorypropertyimpl.h"
#include "../services/filter/stringpropertyfilter.h"

using namespace std;



/**
@author Marcus Dirks
*/

template<class ObjectType> class StringProperty : public RepositoryPropertyImpl {

typedef string (ObjectType::*pstringgetter)();
typedef void (ObjectType::*pstringsetter)(string text);

public:
    
    
    StringProperty(string name, string type, pstringgetter g, pstringsetter s=0, bool isText=false) 
	: RepositoryPropertyImpl(name, type){getter = g; setter = s; is_text = isText;};
    
    ~StringProperty(){};
    
    string asString(PObject *o);
    void fromString(string text, PObject *parent);
    bool isString(){return !is_text;}
    bool isText(){return is_text;}
    Filter *getFilter();
    
private:

    pstringgetter getter;
    pstringsetter setter;

    bool is_text;
};


/*!
    \fn StringProperty::asString()
 */
 template<class ObjectType>
string StringProperty<ObjectType>::asString(PObject *o)
{
    ObjectType *ot = 0;
    ot = dynamic_cast<ObjectType*>(o);
    if(ot){
	    return (ot->*getter)();
    } else {
    	return string("Conversion failed due to wrong object type");
    }
}

template<class ObjectType>
void StringProperty<ObjectType>::fromString(string text, PObject *o)
{
	ObjectType *ot = dynamic_cast<ObjectType*>(o);
	if(ot){
		if(setter){
			(ot->*setter)(text);
		} else {
			qDebug("Failed to set property: setter not provided");
		}
	} else {
    		qDebug("Conversion failed due to wrong object type");
   	 }
}

template<class ObjectType>
Filter *StringProperty<ObjectType>::getFilter()
{
    Filter *f=new StringPropertyFilter(this);
    return f;
}
#endif
