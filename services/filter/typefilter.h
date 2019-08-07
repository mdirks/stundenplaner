//
// C++ Interface: typefilter
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef TYPEFILTER_H
#define TYPEFILTER_H

#include "abstractfilter.h"

#include <string>

using namespace std;

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class TypeFilter : public AbstractFilter {
public:
    TypeFilter(string className);
    ~TypeFilter();
   
     bool apply(PObject *o);

private:
	string className;

};

#endif
