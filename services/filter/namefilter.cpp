//
// C++ Implementation: namefilter
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "namefilter.h"

NameFilter::NameFilter(string name)
{
	this->name = name;
}


NameFilter::~NameFilter()
{
}

bool NameFilter::apply(PObject *o)
{
	if(o->getName() == name){
		return true;
	}
	return false;
}
