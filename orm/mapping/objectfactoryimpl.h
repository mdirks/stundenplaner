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
#ifndef OBJECTFACTORYIMPL_H
#define OBJECTFACTORYIMPL_H

#include <set>

#include "objectfactory.h"

using namespace std;

/**
@author Marcus Dirks
*/
class ObjectFactoryImpl : public ObjectFactory {

	friend class ObjectFactory;

public:
    
    
    
    void deleteObject(PObject *o);
    void registerAssociation(AbstractAssociation *asc);
    
    
private:
	
	ObjectFactoryImpl();
    ~ObjectFactoryImpl();
    
private:
        set<AbstractAssociation*>* findAssociations(string ascClassName);
	
private:
        map<string,set<AbstractAssociation*>*>  associationsMap;
};

#endif
