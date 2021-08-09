#ifndef LEKTUEREACTION_H
#define LEKTUEREACTION_H

#include "pobjectaction.h"
#include "datamodel/lektuere.h"

class LektuereAction : PObjectAction
{
public:
    LektuereAction(lektuere *l);
};

#endif // LEKTUEREACTION_H
