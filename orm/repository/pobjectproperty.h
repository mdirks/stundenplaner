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
#ifndef POBJECTPROPERTY_H
#define POBJECTPROPERTY_H

#include <string>
#include <QDebug>

#include "../persistence/pobject.h"
#include "repositorypropertyimpl.h"

using namespace std;


/**
@author Marcus Dirks
*/
template<class PropertyType, class ObjectType> class PObjectProperty : public RepositoryPropertyImpl {

typedef PropertyType* (ObjectType::*ppobjectmf)();
typedef void (ObjectType::*ppobjectsf)(PropertyType* value);

public:
    PObjectProperty(string name, string type, ppobjectmf f, ppobjectsf s=0) : RepositoryPropertyImpl(name, type) {mf=f; sf=s;};
    ~PObjectProperty(){};
    string asString(PObject *o);
    PObject* asPObject(PObject *o);
    PropertyType* asFullObject(PObject *o);
   void set(PObject *o, PObject *parent);

    bool isPObject(){return true;}

private:
     ppobjectmf mf;
     ppobjectsf sf;

};


/*!
    \fn PObjectProperty::asString()
 */
 template<class PropertyType, class ObjectType>
string PObjectProperty<PropertyType,ObjectType>::asString(PObject *o)
{
    return o->getName();
}


template<class PropertyType, class ObjectType> 
PObject* PObjectProperty<PropertyType,ObjectType>::asPObject(PObject *o)
{
   return asFullObject(o);   

   /*
   ObjectType *ot = dynamic_cast<ObjectType*>(o);
   if(ot == 0) return 0;
  
   return (ot->*mf)();
   */
}

/*!
    \fn PObjectProperty::asPObject()
 */
template<class PropertyType, class ObjectType> 
PropertyType* PObjectProperty<PropertyType,ObjectType>::asFullObject(PObject *o)
{
   ObjectType *ot = dynamic_cast<ObjectType*>(o);
   if(ot == 0){
	qDebug("PObjectProperty: wrong object type");
	return 0;
   }  
   return (ot->*mf)();
}

template<class PropertyType, class ObjectType> 
void PObjectProperty<PropertyType,ObjectType>::set(PObject *o, PObject *parent)
{
	if(sf){
		PropertyType *po = dynamic_cast<PropertyType*>(o);
        ObjectType *ot=dynamic_cast<ObjectType*>(parent);
        if(ot){
            (ot->*sf)(po);
        }
    } else { qDebug() << "PObjectProperty: Could not set value - setter missing";}
}


#endif
