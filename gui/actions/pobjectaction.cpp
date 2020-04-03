#include "pobjectaction.h"

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
