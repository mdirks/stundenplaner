//
// C++ Interface: collectionproperty
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef COLLECTIONPROPERTY_H
#define COLLECTIONPROPERTY_H


#include "../persistence/pobject.h"

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class CollectionProperty 
{
public:
    
    virtual void add(PObject *o, PObject *po) = 0;
    virtual void remove(PObject *o, PObject *po) = 0;

};

#endif
