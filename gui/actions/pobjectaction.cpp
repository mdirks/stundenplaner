#include "pobjectaction.h"
#include <QDebug>


PObjectAction::PObjectAction(const QString &text)
    : QAction(text)
{
    this->po=0;
}

void PObjectAction::setPObject(PObject *o)
{
    this->po=o;
}

PObject* PObjectAction::getPObject()
{
    return this->po;
}


AddToThemaAction::AddToThemaAction(const QString &text)
    : PObjectAction(text)
{
    connect(this, &QAction::triggered, this, &AddToThemaAction::addToThema);
}

void AddToThemaAction::addToThema()
{
    if(PObject *o = getPObject()){
        qDebug() << QString("TODO: add to thema %1").arg(o->getName().c_str());
    }
}
