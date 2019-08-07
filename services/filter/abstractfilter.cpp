//
// C++ Implementation: abstractfilter
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "abstractfilter.h"

AbstractFilter::AbstractFilter()
{
	list_and = new list<Filter*>();
	list_or = new list<Filter*>();
}


AbstractFilter::~AbstractFilter()
{
}




/*!
    \fn AbstractFilter::addAnd(Filter *f)
 */
void AbstractFilter::addAnd(Filter *f)
{
    list_and->push_back(f);
}


/*!
    \fn AbstractFilter::apply(list<PObject*> *input)
 */
void AbstractFilter::apply(list<PObject*> *input)
{
     list<PObject*> *remove_list = new list<PObject*>();
     for(list<PObject*>::iterator it = input->begin(); it != input->end(); it++){
	PObject *o = (*it);
	if(! apply(o)){
		remove_list->push_back(o);
        }
    }
    for(list<PObject*>::iterator it = remove_list->begin(); it != remove_list->end(); it++)
    {
	input->remove( (*it) );
    }
}

bool AbstractFilter::apply(PObject *o)
{
    bool result = true;	
    for(list<Filter*>::iterator it = list_and->begin(); it != list_and->end(); it++){
	Filter *f = (*it);
	result = result & f->apply(o);
    }
    
   for(list<Filter*>::iterator it = list_or->begin(); it != list_or->end(); it++){
	Filter *f = (*it);
	result = result & f->apply(o);
    }

    return result;
}
/*!
    \fn AbstractFilter::addOr(Filter *f)
 */
void AbstractFilter::addOr(Filter *f)
{
    list_or->push_back(f);
}
