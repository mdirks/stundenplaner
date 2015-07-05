#include "pobjectdroptarget.h"
#include "pobjectdata.h"
#include "orm/persistence/database.h"
#include <QDebug>
PObjectDropTarget::PObjectDropTarget()
{
}





PObject* PObjectDropTarget::handlePObjectDrop(QDropEvent *e)
{
    qDebug() << "PObjectDropTarget::handleDrop";

    PObject *o=0;

    const QMimeData *md = e->mimeData();
    o=recoverPObject(md);
    if(o){
        e->accept();
    }else{
        e->ignore();
        qDebug() << "PObjectDropTarget::handleDrop: Strange, how to decode this data?";
    }
    return o;

}


PObject* PObjectDropTarget::recoverPObject(const QMimeData *md)
{
    PObject *o=0;
    if(md->hasFormat("application/pobject") ){ // recieved a valid object
        QByteArray data=md->data("application/pobject");
        QDataStream stream(&data,QIODevice::ReadOnly);
        QString className;
        int id;
        stream >> className >> id;
        o = Database::getInstance()->load(className.toStdString(), id);

    }else{
        qDebug() << "PobjectDropTarget: Cannot handle object";
    }
    return o;
}

QMimeData* PObjectDropTarget::createMimeData(PObject *o)
{
    QMimeData *mimeData = new QMimeData();
    QByteArray data;
    QDataStream stream(&data,QIODevice::WriteOnly);
    stream <<  QString(o->getPersistenceObject()->getClassName().c_str()) << o->getID();
    mimeData->setData("application/pobject",data);
    return mimeData;
}
