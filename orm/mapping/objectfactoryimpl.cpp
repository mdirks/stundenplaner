//
// C++ Implementation: %{MODULE}
//
// Description:
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "objectfactoryimpl.h"

ObjectFactoryImpl::ObjectFactoryImpl()
{
}


ObjectFactoryImpl::~ObjectFactoryImpl()
{
}




/*!
    \fn ObjectFactoryImpl::delete(PObject *o)
 */
void ObjectFactoryImpl::deleteObject(PObject *o)
{
     string className = o->getPersistenceObject()->getClassName();
     set<AbstractAssociation*> *ascSet = findAssociations(className);
     if(ascSet){
	for(set<AbstractAssociation*>::iterator it = ascSet->begin(); it != ascSet->end(); it++)
	{
		(*it)->deleteObject(o);
        }
     } 
}


/*!
    \fn ObjectFactoryImpl::registerAssociation(Association *asc)
 */
void ObjectFactoryImpl::registerAssociation(AbstractAssociation *asc)
{
       string ascClassName = asc->getAscClassName();
       set<AbstractAssociation*> *ascSet;
       
       map<string,set<AbstractAssociation*>*>::iterator it = associationsMap.find(ascClassName);
       if( it != associationsMap.end() ){
       		ascSet = it->second;
       } else {
       		ascSet = new set<AbstractAssociation*>();
		associationsMap[ascClassName] = ascSet;
       }
       ascSet->insert(asc);
}

set<AbstractAssociation*>* ObjectFactoryImpl::findAssociations(string ascClassName)
{
	map<string,set<AbstractAssociation*>*>::iterator it = associationsMap.find(ascClassName);
	if( it != associationsMap.end() )
	{
		return it->second;
	} else {
		return 0;
	}
	
}