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
#ifndef PROPERTYEDITOR_H
#define PROPERTYEDITOR_H

#include "orm/repository/repositoryproperty.h"
#include "orm/persistence/pobject.h"

/**
@author Marcus Dirks
*/
class PropertyEditor{
public:
    
    virtual void stopEdit() = 0;
    virtual void startEdit(RepositoryProperty *rp, PObject *parent) = 0;
    virtual void startEdit() = 0;
};

#endif
