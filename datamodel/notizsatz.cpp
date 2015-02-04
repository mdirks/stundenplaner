#include "notizsatz.h"

#include "notizsatzmapper.h"

notizsatz::notizsatz()
{
    setMapper(notizsatzmapper::getInstance());
    list_notizen=0;
}

list<notiz*> *notizsatz::getNotizen()
{
    if(list_notizen==0){
        list_notizen=notizsatzmapper::getInstance()->findNotizen(getID());
    }
    return list_notizen;
}

void notizsatz::addToNotizen(notiz *n)
{
    getNotizen()->push_back(n);
}

void notizsatz::deleteFromNotizen(notiz *n)
{
    getNotizen()->remove(n);
}
