//
// C++ Interface: stringpropertyfilter
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef STRINGPROPERTYFILTER_H
#define STRINGPROPERTYFILTER_H

#include "orm/repository/repositoryproperty.h"
#include "propertyfilter.h"

#include <string>

using namespace std;

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class StringPropertyFilter : PropertyFilter {
public:
    StringPropertyFilter(RepositoryProperty *rp, string testItem);
    ~StringPropertyFilter();

    bool apply(PObject *o);
    string getValueString();

protected:
	//RepositoryProperty *rp;
	string testItem;
};

#endif
