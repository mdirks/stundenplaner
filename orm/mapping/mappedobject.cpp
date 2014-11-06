//
// C++ Implementation: %{MODULE}
//
// Description:
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "mappedobject.h"

MappedObject::MappedObject()
 : PObject()
{
}


MappedObject::~MappedObject()
{
}




/*!
    \fn MappedObject::setMapper(AbstractMapper *mapper)
 */
void MappedObject::setMapper(AbstractMapper* mapper)
{
    setPersistenceObject((PersistenceClass*)mapper);
}


/*!
    \fn MappedObject::*getMapper()
 */
AbstractMapper* MappedObject::getMapper()
{
    return 0;
}
