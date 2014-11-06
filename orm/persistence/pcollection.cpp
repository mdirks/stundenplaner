//
// C++ Implementation: pcollection
//
// Description: 
//
//
// Author: Marcus Dirks <mopp@suse>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "pcollection.h"
#include "pcollectionpersistence.h"

PCollection::PCollection()
 : PObject()
{
	setPersistenceObject(PCollectionPersistence::getInstance());
}


PCollection::~PCollection()
{
}

void PCollection::save()
{
 	
}


