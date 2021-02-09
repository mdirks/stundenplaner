#include "collectionpropertyviewer.h"

CollectionPropertyViewer::CollectionPropertyViewer()
{

}


void CollectionPropertyViewer::setParentObject(PObject *o)
{
   this->parent = o;
}

void CollectionPropertyViewer::setProperty(RepositoryProperty *p)
{
    this->prop = p;
}
