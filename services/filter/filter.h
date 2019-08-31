//
// C++ Interface: filter
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef FILTER_H
#define FILTER_H

#include "orm/persistence/pobject.h"

#include <list>
#include <string>
using namespace std;

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class Filter{
public:
    
    virtual void apply(list<PObject*> *input) = 0;
    virtual bool apply(PObject *o) = 0;
    virtual void addAnd(Filter *f) = 0;
    virtual void addOr(Filter *f) = 0;
    virtual string getDisplayString() = 0;
    virtual int type();
};

#endif
