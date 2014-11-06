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
#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include "persistence/pobject.h"
#include "abstractassociation.h"

/**
@author Marcus Dirks
*/
class ObjectFactory{
public:
    
    static ObjectFactory* getInstance();
    
    virtual void deleteObject(PObject *o)=0;
    virtual void registerAssociation(AbstractAssociation *asc) = 0;
  
 private:
 	static ObjectFactory *instance;

};

#endif
