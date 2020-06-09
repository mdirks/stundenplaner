#ifndef MTREE_H
#define MTREE_H

#include "../persistence/pobject.h"
#include "../transactions/transactionobject.h"


class MTree : public TransactionObject
{
public:
    MTree();

    void setParent(MTree *tr);
    MTree* getParent();

    void setContents(TransactionObject *o);
    TransactionObject* getContents();

    void addToChildren(MTree *tr);
    void deleteFromChildren(MTree *tr);
    list<MTree*>* getChildren();
    //void setChildren(list<MTree*>* *cc);

private:
    MTree *parent;
    TransactionObject* contents;
    list<MTree*> *list_children;

};

#endif // MTREE_H
