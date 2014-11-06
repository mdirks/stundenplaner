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
#ifndef COLLECTIONPROPERTYIMPL_H
#define COLLECTIONPROPERTYIMPL_H

#include <string>
#include <list>

#include "repositorypropertyimpl.h"
#include "collectionproperty.h"

using namespace std;

/**
@author Marcus Dirks
*/
template<class EntryType, class ObjectType> class CollectionPropertyImpl : public RepositoryPropertyImpl, public CollectionProperty 
{

typedef list<EntryType*>*  (ObjectType::*pcollectionmf)();
typedef void  (ObjectType::*pcollectionadder)(EntryType*);
typedef void  (ObjectType::*pcollectionremover)(EntryType*);

public:
    typedef list<EntryType*> entry_list;

    CollectionPropertyImpl(string name, string type, pcollectionmf f, pcollectionadder a, pcollectionremover r) : RepositoryPropertyImpl(name, type, true) { mf=f; af=a; rf =r;};
    ~CollectionPropertyImpl(){};

    string asString(PObject *o);
    PObject* asPObject(PObject *o);
    list<PObject*>* asPObjectList(PObject *o);
    entry_list* asFullObject(PObject *o);
    list<PObject*>* asCollection(PObject *o);
    void add(PObject *o, PObject *po);
    void remove(PObject *o, PObject *po);
    
private:
     pcollectionmf mf;
     pcollectionadder af;
    pcollectionremover rf;
};


/*!
    \fn PObjectProperty::asString()
 */
 template<class EntryType, class ObjectType>
string CollectionPropertyImpl<EntryType,ObjectType>::asString(PObject *o)
{
    return string("Not implemented");
}


template<class EntryType, class ObjectType> 
PObject* CollectionPropertyImpl<EntryType,ObjectType>::asPObject(PObject *o)
{
   return 0;   

   /*
   ObjectType *ot = dynamic_cast<ObjectType*>(o);
   if(ot == 0) return 0;
  
   return (ot->*mf)();
   */
}


/*!
    \fn CollectionPropertyImpl::asCollection(PObject *o)
 */
template<class EntryType, class ObjectType> 
list<PObject*>* CollectionPropertyImpl<EntryType, ObjectType>::asCollection(PObject *o)
{
    return asPObjectList(o);
    
}



/*!
    \fn PObjectProperty::asPObject()
 */
template<class EntryType, class ObjectType> 
list<EntryType*>* CollectionPropertyImpl<EntryType,ObjectType>::asFullObject(PObject *o)
{
   ObjectType *ot = dynamic_cast<ObjectType*>(o);
   if(ot == 0) return 0;
  
   return (ot->*mf)();
}

template<class EntryType, class ObjectType> 
void CollectionPropertyImpl<EntryType,ObjectType>::add(PObject *o, PObject *po)
{
	ObjectType *ot = dynamic_cast<ObjectType*>(po);
	EntryType *et = dynamic_cast<EntryType*>(o);
	if(et)
	{
		(ot->*af)(et);
	}
}

/** Remove the given object from the parent object.
 * 
 * @param o object to be removed
 * @param po parent object
 */
template<class EntryType, class ObjectType> 
void CollectionPropertyImpl<EntryType,ObjectType>::remove(PObject *o, PObject *po)
{
	ObjectType *ot = dynamic_cast<ObjectType*>(po);
	EntryType *et = dynamic_cast<EntryType*>(o);
	if(ot && et)
	{
		(ot->*rf)(et);
	} else {
		qDebug("CollectionPropertyImpl::remove(): Failed to remove since either object or entry was null");
	}
}




template<class EntryType, class ObjectType> 
list<PObject*>* CollectionPropertyImpl<EntryType,ObjectType>::asPObjectList(PObject *o)
{
   ObjectType *ot = dynamic_cast<ObjectType*>(o);
   if(ot == 0) return 0;
  
   entry_list* el  = (ot->*mf)();
   list<PObject*> *ol = new list<PObject*>();

  if(el){ 
  	for( typename entry_list::iterator it = el->begin();it != el->end(); ++it)
   	{
   		if((*it)){
			ol->push_back( *it );
   		} else {
			qDebug("CollectionPropertyImpl::asPObjectList : Invalid object in list");
		}
	}
   }
   
   return ol;
}




#endif
