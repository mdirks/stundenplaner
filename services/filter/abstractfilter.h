//
// C++ Interface: abstractfilter
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef ABSTRACTFILTER_H
#define ABSTRACTFILTER_H

#include "filter.h"

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class AbstractFilter : public Filter{
public:
    AbstractFilter();
    ~AbstractFilter();
    void addAnd(Filter *f);
    void apply(list<PObject*> *input);
    bool apply(PObject *o);
    void addOr(Filter *f);

     bool operator()(PObject *o){return apply(o);}
     bool operator()(list<PObject*> *input){apply(input); return true;}
private:
	list<Filter*> *list_and, *list_or;


};

#endif
