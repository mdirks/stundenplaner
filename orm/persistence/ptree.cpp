#include "ptree.h"
#include "ptreepersistence.h"

PTree::PTree()
{
    setPersistenceObject(PTreePersistence::getInstance());
}

PTree* PTree::getParent()
{
    return parent;
}

void PTree::setParent(PTree *tr)
{
    parent=tr;
}
PCollection* PTree::getChildren()
{
    return children;
}

void PTree::setChildren(PCollection *cc)
{
    children =cc;
}
