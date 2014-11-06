//
// C++ Implementation: typefilter
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "typefilter.h"

TypeFilter::TypeFilter(string className)
{
	this->className = className;
}


TypeFilter::~TypeFilter()
{
}


bool TypeFilter::apply( PObject *o )
{
	if(o->getPersistenceObject()->getClassName() == className){
		return true;
        }
	return false;
}