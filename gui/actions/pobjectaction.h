#ifndef POBJECTACTION_H
#define POBJECTACTION_H

#include "orm/persistence/pobject.h"

#include <QAction>

class PObjectAction : public QAction
{
public:
    PObjectAction(const QString &text);
    void setPObject(PObject *o);
    PObject* getPObject();


private:
    PObject *po;
};

#endif // POBJECTACTION_H
