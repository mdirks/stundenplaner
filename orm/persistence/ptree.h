#ifndef PTREE_H
#define PTREE_H

#include "pobject.h"
#include "pcollection.h"

class PTree : public PObject
{
public:
    PTree();

    void setParent(PTree *tr);

    void addToChildren(PTree *tr);
    void deleteFromChildren(PTree *tr);
    PCollection* getChildren();

private:
    PTree *parent;
    PCollection *children;

};

#endif // PTREE_H
