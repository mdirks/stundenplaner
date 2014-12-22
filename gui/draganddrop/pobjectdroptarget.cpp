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


    if(e->mimeData()->hasFormat("application/pobject") ){ // recieved a valid object
        QByteArray data=e->mimeData()->data("application/pobject");
        QDataStream stream(&data,QIODevice::ReadOnly);
        QString className;
        int id;
        stream >> className >> id;
        o = Database::getInstance()->load(className.toStdString(), id);
        if(o){
            e->accept();
        }else{
            e->ignore();
            qDebug() << "PObjectDropTarget::handleDrop: Strange, how to decode this data?";
        }
    }else{
        qDebug() << "PobjectDropTarget: Cannot handle object";
    }

    return o;


}
