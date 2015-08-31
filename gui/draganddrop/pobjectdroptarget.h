#ifndef POBJECTDROPTARGET_H
#define POBJECTDROPTARGET_H

#include "orm/persistence/pobject.h"

#include <QDropEvent>
#include <QMimeData>


class PObjectDropTarget
{
public:
    PObjectDropTarget();

    PObject* handlePObjectDrop(QDropEvent *e);
    PObject* recoverPObject(const QMimeData *md);
    QMimeData* createMimeData(PObject *o);
    //void startDrag ( Qt::DropActions supportedActions );

    //virtual PObject* getObject()=0;
};

#endif // POBJECTDROPTARGET_H
