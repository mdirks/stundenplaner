//
// C++ Implementation: pobjectpropertyfilter
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "pobjectpropertyfilter.h"

PObjectPropertyFilter::PObjectPropertyFilter(RepositoryProperty *rp, PObject *testObject)
	: PropertyFilter(rp)
{
	this->testObject = testObject;
}


PObjectPropertyFilter::~PObjectPropertyFilter()
{
}

string PObjectPropertyFilter::getValueString()
{
	if(testObject){
		return testObject->getName();
	} else {
		return "Empty";
	}
}



/*!
    \fn PObjectPropertyFilter::apply(PObject *o)
 */
bool  PObjectPropertyFilter::apply(PObject *o)
{
    if(rp->asPObject(o) == testObject){
	return true;
    }
    return false;
}


