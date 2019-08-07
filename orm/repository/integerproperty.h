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
#ifndef INTEGERPROPERTY_H
#define INTEGERPROPERTY_H

#include "../persistence/pobject.h"
#include "repositorypropertyimpl.h"

typedef int (PObject::*pintmf)();

/**
@author Marcus Dirks
*/
class  IntegerProperty : public RepositoryPropertyImpl {
public:
 

    IntegerProperty(string name, string type, pintmf f);
    ~IntegerProperty();

};

#endif
