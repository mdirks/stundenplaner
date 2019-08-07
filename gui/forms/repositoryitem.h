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
#ifndef REPOSITORYITEM_H
#define REPOSITORYITEM_H

#include "orm/repository/repositoryproperty.h"

/**
@author Marcus Dirks
*/
class RepositoryItem{
public:
    RepositoryItem();
    ~RepositoryItem();
    
    virtual RepositoryProperty* getRepositoryProperty() = 0;
    virtual PObject* getParent() = 0;

};

#endif
