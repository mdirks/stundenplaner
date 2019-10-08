#ifndef MYACTIONLIST_H
#define MYACTIONLIST_H

#include <QList>
#include <QAction>

class MyActionList : public QObject
{
    Q_OBJECT
public:
    MyActionList();
    QAction *addAction(QString text, QObject *receiver);

private:
    QList<QAction*> *actionlist;
};

#endif // MYACTIONLIST_H
