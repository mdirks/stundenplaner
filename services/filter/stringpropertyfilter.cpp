//
// C++ Implementation: stringpropertyfilter
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "stringpropertyfilter.h"

StringPropertyFilter::StringPropertyFilter(RepositoryProperty *rp, string testItem)
	: PropertyFilter(rp), testItem (testItem)
{
	
}


StringPropertyFilter::~StringPropertyFilter()
{
}




/*!
    \fn StringPropertyFilter::apply(PObject *o)
 */
bool StringPropertyFilter::apply(PObject *o)
{
    if(rp->asString(o) == testItem){
	return true;
    }
    return false;
}

string StringPropertyFilter::getValueString()
{
	return testItem;
}