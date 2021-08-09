#ifndef POBJECTACTION_H
#define POBJECTACTION_H

#include "orm/persistence/pobject.h"

#include <QAction>

class PObjectAction : public QAction
{
    Q_OBJECT
public:
    PObjectAction(const QString &text);
    virtual ~PObjectAction(){};
    void setPObject(PObject *o);

protected:
    PObject* getPObject();


private:
    PObject *po;
};


class AddToThemaAction : public PObjectAction
{
    Q_OBJECT
public:
    AddToThemaAction(const QString &text);

public slots:
    void addToThema();
};

class VocImportAction : public PObjectAction
{
    Q_OBJECT
public:
    VocImportAction(const QString &text);

public slots:
    void importFromFile();
};

class ImportToDocStoreAction : public PObjectAction
{
Q_OBJECT

public:
    ImportToDocStoreAction();


public slots:
    void importToDocStore();



};

class AddToRemarkableAction : public PObjectAction
{
    Q_OBJECT

public:
    AddToRemarkableAction();

public slots:
    void addToRm();
};

class WriteBookmarksToRmAction : public PObjectAction
{
    Q_OBJECT

public:
    WriteBookmarksToRmAction();

public slots:
    void writeToRm();
};

class FindRmObjectAction : public PObjectAction
{
    Q_OBJECT

public:
    FindRmObjectAction();

public slots:
    void findRmObject();
};


#endif // POBJECTACTION_H
