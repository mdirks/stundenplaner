#include "myactionlist.h"

#include <QObject>

MyActionList::MyActionList()
{
    actionlist = new QList<QAction*>();
}


QAction *MyActionList::addAction(QString text, QObject *reciever)
{
    QAction *a = new QAction(text,reciever);
    actionlist->append(a);
    return a;
}
