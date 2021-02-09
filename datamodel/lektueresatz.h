#ifndef LEKTUERESATZ_H
#define LEKTUERESATZ_H
#include "lektuere.h"
#include <list>

using namespace std;

class lektueresatz : public TransactionObject
{
public:
    lektueresatz();

    list<lektuere*> *getLektueren();
    void addToLektueren(lektuere *l);
    void deleteFromLektueren(lektuere *l);

    list<lektueresatz*> *getChildren();
    void addToChildren(lektueresatz *ls);
    void deleteFromChildren(lektueresatz *ls);

private:
    list<lektuere*> *list_lektueren;
    list<lektueresatz*> *list_children;
};



#endif // LEKTUERESATZ_H
