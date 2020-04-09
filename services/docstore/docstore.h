#ifndef DOCSTORE_H
#define DOCSTORE_H

#include <QString>
#include <QFile>

#include "datamodel/material.h"

class DocStore
{
protected:
    DocStore();

public:
    static DocStore *getInstance();
    static QString getDirectory();


    //virtual DocStore *createStore()=0;
    virtual void addRemote()=0;

    virtual bool addDocument(material *m)=0;
    virtual void removeDocument(QFile *file)=0;

    virtual void getDocument()=0;
    virtual void dropDocument()=0;
    virtual void moveDocument()=0;


private:
    static DocStore *instance;
};

#endif // DOCSTORE_H
