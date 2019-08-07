#include "lektuere.h"

#include "lektueremapper.h"

lektuere::lektuere()
    : material()
{
    setMapper(lektueremapper::getInstance());
    list_notizen=0;
    lks=0;
}


list<lektuerenotiz*>* lektuere::getNotizen()
{
    if(list_notizen==0)
    {
        list_notizen=lektueremapper::getInstance()->findNotizen(getID());
    }
    return list_notizen;
}

void lektuere::addToNotizen(lektuerenotiz *n)
{
    getNotizen()->push_back(n);
}

void lektuere::deleteFromNotizen(lektuerenotiz *n)
{
    getNotizen()->remove(n);
}

void lektuere::setLernkartensatz(lernkartensatz *ls)
{
        this->lks=ls;
}

lernkartensatz* lektuere::getLernkartensatz()
{
    if(lks==0){
        lks= (lernkartensatz*) lektueremapper::getInstance()->findReference("Lernkartensatz",getID());
    }
    return lks;
}
