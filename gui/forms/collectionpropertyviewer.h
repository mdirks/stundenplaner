#ifndef COLLECTIONPROPERTYVIEWER_H
#define COLLECTIONPROPERTYVIEWER_H

#include "orm/persistence/pobject.h"
#include "orm/repository/repositoryproperty.h"

class CollectionPropertyViewer
{
public:
    CollectionPropertyViewer();


    virtual void setParentObject(PObject *o);
    virtual void setProperty(RepositoryProperty *p);

private:
    PObject *parent;
    RepositoryProperty *prop;
};

#endif // COLLECTIONPROPERTYVIEWER_H
