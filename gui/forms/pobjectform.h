#ifndef POBJECTFORM_H
#define POBJECTFORM_H

#include "orm/persistence/pobject.h"

class PObjectForm
{
public:
    virtual void setParentObject(PObject *o)=0;
};

#endif // POBJECTFORM_H
