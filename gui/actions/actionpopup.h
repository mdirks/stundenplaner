#ifndef ACTIONPOPUP_H
#define ACTIONPOPUP_H

#include <QMenu>
#include "orm/persistence/pobject.h"
#include "pobjectaction.h"

class ActionPopup : public QMenu
{
Q_OBJECT

public:
    ActionPopup();
    void setPObject(PObject *po);
    void addAction(PObjectAction *a);

private:
    list<PObjectAction*> *list_oa;
};

#endif // ACTIONPOPUP_H
