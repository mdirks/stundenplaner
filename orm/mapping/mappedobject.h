//
// C++ Interface: %{MODULE}
//
// Description: 
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef MAPPEDOBJECT_H
#define MAPPEDOBJECT_H

#include "../persistence/pobject.h"
//#include "abstractmapper.h"

class AbstractMapper;

/**
@author Marcus Dirks
*/
class MappedObject : public PObject
{
public:
    MappedObject();

    ~MappedObject();
    virtual void setMapper(AbstractMapper* mapper);
    AbstractMapper* getMapper();

};

#endif
