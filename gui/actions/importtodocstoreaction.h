#ifndef IMPORTTOOBJECTSTOREACTION_H
#define IMPORTTOOBJECTSTOREACTION_H

#include "pobjectaction.h"
#include "orm/persistence/pobject.h"

class ImportToDocStoreAction : public PObjectAction
{
Q_OBJECT

public:
    ImportToDocStoreAction();


public slots:
    void importToDocStore();



};


#endif // IMPORTTOOBJECTSTOREACTION_H
