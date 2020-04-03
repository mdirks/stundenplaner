#include "importtodocstoreaction.h"

#include "services/docstore/docstore.h"
#include "datamodel/material.h"
#include "orm/transactions/transactions.h"
#include <QDebug>

ImportToDocStoreAction::ImportToDocStoreAction()
    : PObjectAction("Import to Objectstore")
{

    connect(this,SIGNAL(triggered()),this,SLOT(importToDocStore()));
}

void ImportToDocStoreAction::importToDocStore()
{
    if(PObject *po = getPObject()){
        if(material *m=dynamic_cast<material*>(po)){
            Transactions::getCurrentTransaction()->add(m);

            DocStore *ds = DocStore::getInstance();
            ds->addDocument(m);
        }
    } else {
        qDebug() << "ImportToObjectStoreAction ERROR: object was not set";
    }
}
