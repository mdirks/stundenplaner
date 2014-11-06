//
// C++ Interface: pcollection
//
// Description: 
//
//
// Author: Marcus Dirks <mopp@suse>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef PCOLLECTION_H
#define PCOLLECTION_H

#include <list>

#include "pobject.h"

using namespace std;

/**
@author Marcus Dirks
*/

//template<class ObjectType>
class PCollection : public PObject, public list<PObject* >
{
public:
    typedef list<PObject*>::iterator iterator;

    PCollection();
    ~PCollection();
    
    virtual void save();

};


#endif
