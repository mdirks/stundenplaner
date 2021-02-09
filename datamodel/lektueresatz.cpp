#include "lektueresatz.h"
#include "lektueresatzmapper.h"

lektueresatz::lektueresatz()
{
   setMapper(lektueresatzmapper::getInstance());
   list_lektueren=0;
   list_children=0;
}


list<lektuere*> *lektueresatz::getLektueren()
{
    if(list_lektueren==0){
        list_lektueren=lektueresatzmapper::getInstance()->findLektueren(getID());
    }
    return list_lektueren;
}

void lektueresatz::addToLektueren(lektuere *l)
{
    getLektueren()->push_back(l);
}

void lektueresatz::deleteFromLektueren(lektuere *l)
{
    getLektueren()->remove(l);
}

list<lektueresatz*> *lektueresatz::getChildren()
{
    if(list_children==0){
        list_children=lektueresatzmapper::getInstance()->findChildren(getID());
    }
    return list_children;
}

void lektueresatz::addToChildren(lektueresatz *ls)
{
    getChildren()->push_back(ls);
}

void lektueresatz::deleteFromChildren(lektueresatz *ls)
{
    getChildren()->remove(ls);
}
