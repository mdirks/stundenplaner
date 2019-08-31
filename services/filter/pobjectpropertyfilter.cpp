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

string PObjectPropertyFilter::getDisplayString()
{
    return PropertyFilter::getDisplayString() + " (PObject) \n" + getValueString();
}


/*!
    \fn PObjectPropertyFilter::apply(PObject *o)
 */
bool  PObjectPropertyFilter::apply(PObject *o)
{
    PObject *po = rp->asPObject(o);
    if(po){
        if(po->getID() == testObject->getID()){
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

string PObjectPropertyFilter::getPropertyType() const
{
    return rp->getType();
}

int PObjectPropertyFilter::type()
{
    return 1;
}

void PObjectPropertyFilter::setValue(PObject *po)
{
    testObject=po;
}
