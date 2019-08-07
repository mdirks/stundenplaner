#include "reihemap.h"
#define YSEP 100

#include <QPoint>

ReiheMap::ReiheMap()
    : GenericMap(0,0)
{
}

void ReiheMap::setReihe(reihe *r)
{
    this->m_r = r;
    list<stunde*> *lst = r->getStunden();
    QPoint p(0,0);
    for(list<stunde*>::iterator it=lst->begin(); it!=lst->end(); it++){
        stunde *st = (*it);
        GenericMap::addItem(st,p);
        p.setY(p.y()+YSEP);
    }
}
