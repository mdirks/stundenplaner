#include "lektuere.h"

#include "lektueremapper.h"

lektuere::lektuere()
    : material()
{
    setMapper(lektueremapper::getInstance());
    list_notizen=0;
    list_bookmarks=0;
    list_toc=0;
    lks=0;
    kop=0;
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

list<bookmark*>* lektuere::getBookmarks()
{
    if(list_bookmarks==0){
        list_bookmarks=lektueremapper::getInstance()->findBookmarks(getID());
    }
    return list_bookmarks;
}
void lektuere::addToBookmarks(bookmark *bm)
{
    getBookmarks()->push_back(bm);
}

void lektuere::deleteFromBookmarks(bookmark *bm)
{
    getBookmarks()->remove(bm);
}

list<bookmark*>* lektuere::getToc()
{
    if(list_toc==0){
        list_toc=lektueremapper::getInstance()->findToc(getID());
    }
    return list_toc;
}
void lektuere::addToToc(bookmark *bm)
{
    getToc()->push_back(bm);
    getToc()->sort(lektuere::toc_compare);
}

bool lektuere::toc_compare(bookmark *bm1, bookmark *bm2)
{
    return bm1->getPosition() < bm2->getPosition();
}


void lektuere::deleteFromToc(bookmark *bm)
{
    getToc()->remove(bm);
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

void lektuere::setKopien(materialsatz *ms)
{
    this->kop=ms;
}

materialsatz* lektuere::getKopien()
{
    if(kop==0){
        kop = (materialsatz*) lektueremapper::getInstance()->findReference("Kopien",getID());
    }
    return kop;
}
