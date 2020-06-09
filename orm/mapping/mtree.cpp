#include "mtree.h"
#include "mtreemapper.h"

MTree::MTree()
{
    list_children=0;
    parent=0;
    setMapper(MTreemapper::getInstance());
}



MTree* MTree::getParent()
{
    if(parent==0){
        parent= (MTree*) MTreemapper::getInstance()->findReference("Parent",getID());
    }
    return parent;
}

void MTree::setParent(MTree *tr)
{
    parent=tr;
}
list<MTree*>* MTree::getChildren()
{
    if(list_children == 0){
        list_children = MTreemapper::getInstance()->findChildren(getID());
    }

    return list_children;
}

void MTree::addToChildren(MTree *tr)
{

}

void MTree::deleteFromChildren(MTree *tr)
{

}

