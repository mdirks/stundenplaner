#include "pobjectaction.h"
#include "gui/forms/pobjectdialog.h"
#include "datamodel/thema.h"
#include "datamodel/lektuerenotiz.h"
#include "datamodel/kopie.h"
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
        thema *t= (thema*) PObjectDialog::choosePObject("thema");
        string ocl = o->getClassName();
        if(ocl == "notiz"){
            t->addToNotizen((notiz*) o);
        } else if (ocl == "lektuerenotiz"){
            t->addToNotizen((lektuerenotiz*) o);
        } else if (ocl == "material"){
            t->addToMaterialien((material*) o);
        } else if (ocl == "kopie"){
            t->addToMaterialien((kopie*) o);
        }
        qDebug() << QString("AddToThemaAction: added %1 (%2) to %3").arg(o->getName().c_str()).arg(ocl.c_str()).arg(t->getName().c_str());
    }
}
