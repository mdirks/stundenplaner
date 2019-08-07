//
// C++ Interface: pobjectpropertyfilter
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef POBJECTPROPERTYFILTER_H
#define POBJECTPROPERTYFILTER_H

#include "orm/repository/repositoryproperty.h"
#include "orm/persistence/pobject.h"
#include "propertyfilter.h"

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class PObjectPropertyFilter : public PropertyFilter {
public:
    PObjectPropertyFilter(RepositoryProperty *rp, PObject *testObject);
    ~PObjectPropertyFilter();
    bool  apply(PObject *o);
    string getValueString();

private:
	//RepositoryProperty *rp;
	PObject *testObject;

};

#endif
