#include "actionpopup.h"

ActionPopup::ActionPopup()
    : QMenu("Aktionen")
{
    list_oa=new list<PObjectAction*>();
}

void ActionPopup::setPObject(PObject *po)
{
    for(list<PObjectAction*>::iterator it=list_oa->begin(); it!=list_oa->end(); it++){
        PObjectAction *oa = *it;
        oa->setPObject(po);
    }

}

void ActionPopup::addAction(PObjectAction *a)
{
    list_oa->push_back(a);
    QMenu::addAction(a);
}
