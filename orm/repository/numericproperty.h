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
#ifndef NUMERICPROPERTY_H
#define NUMERICPROPERTY_H

#include <string>
#include "repositorypropertyimpl.h"
#include "../persistence/pobject.h"

using namespace std;

/**
@author Marcus Dirks
*/
template<typename PropertyType, class ObjectType> class NumericProperty : public  RepositoryPropertyImpl {

typedef PropertyType (ObjectType::*pnumericmf)();
typedef void (ObjectType::*pnumericsf)(PropertyType prop);

public:
    NumericProperty(string name, string type, pnumericmf f, pnumericsf s) : RepositoryPropertyImpl(name,type){mf =f; sf=s;};
    ~NumericProperty();
    
    string asString(PObject *o);
    void fromString(string text, PObject *o);
    PropertyType asFullObject(PObject *o);
    
    bool isNumeric(){return true;}
   
private:
    pnumericmf mf; 
    pnumericsf sf;
};


template<typename PropertyType, class ObjectType>
string NumericProperty<PropertyType, ObjectType>::asString(PObject *o)
{
	ObjectType *ot = 0;
    	ot = dynamic_cast<ObjectType*>(o);
    	if(ot){
		QString st("%1");
            return st.arg((ot->*mf)()).toStdString();
   	 } else {
    		return string("Conversion failed due to wrong object type");
    	}
}


template<typename PropertyType, class ObjectType>
PropertyType NumericProperty<PropertyType, ObjectType>::asFullObject(PObject *o)
{
	ObjectType *ot = dynamic_cast<ObjectType*>(o);
	if(ot){
		return (ot->*mf)();
	} else {
		return -1;
	}
}


template<typename PropertyType, class ObjectType>
void NumericProperty<PropertyType, ObjectType>::fromString(string text, PObject *o)
{
	ObjectType *ot = dynamic_cast<ObjectType*>(o);
	if(ot){
		if(sf){
            QString str(text.c_str());
			(ot->*sf)(str.toInt());
		} else {
			qDebug("Failed to set property: setter not provided");
		}
	} else {
    		qDebug("Conversion failed due to wrong object type");
   	 }
}



#endif
