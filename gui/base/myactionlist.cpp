#include "myactionlist.h"


MyActionList::MyActionList()
{
    actionlist = new QList<QAction*>();
}


QAction *MyActionList::addAction(QString text, QObject *reciever, const char* slot_name)
{
    QAction *a = new QAction(text,reciever);
    connect(a, SIGNAL("triggered()"), reciever, SLOT(slot_name));
    actionlist->append(a);
    return a;
}
