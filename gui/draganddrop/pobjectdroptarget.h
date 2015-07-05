#ifndef POBJECTDROPTARGET_H
#define POBJECTDROPTARGET_H

#include "orm/persistence/pobject.h"

#include <QDropEvent>

class PObjectDropTarget
{
public:
    PObjectDropTarget();

    PObject* handlePObjectDrop(QDropEvent *e);
    PObject* recoverPObject(const QMimeData *md);
    QMimeData* createMimeData(PObject *o);
};

#endif // POBJECTDROPTARGET_H
