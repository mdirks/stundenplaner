#include "themamapsatz.h"
#include "themamapsatzmapper.h"

ThemaMapSatz::ThemaMapSatz()
{
    setMapper(ThemaMapSatzmapper::getInstance());
    list_themamaps=0;
    list_children=0;
}


list<ThemaMap*> *ThemaMapSatz::getThemaMaps()
{
    if(list_themamaps==0){
        list_themamaps=ThemaMapSatzmapper::getInstance()->findThemaMaps(getID());
    }
    return list_themamaps;
}

void ThemaMapSatz::addToThemaMaps(ThemaMap *tm)
{
    getThemaMaps()->push_back(tm);
}
void ThemaMapSatz::deleteFromThemaMaps(ThemaMap *tm)
{
    getThemaMaps()->remove(tm);
}

list<ThemaMapSatz*> *ThemaMapSatz::getChildren()
{
    if(list_children==0){
        list_children=ThemaMapSatzmapper::getInstance()->findChildren(getID());
    }
    return list_children;
}

void ThemaMapSatz::addToChildren(ThemaMapSatz *tms)
{
    getChildren()->push_back(tms);
}

void ThemaMapSatz::deleteFromChildren(ThemaMapSatz *tms)
{
    getChildren()->remove(tms);
}
