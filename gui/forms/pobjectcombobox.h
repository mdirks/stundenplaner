#ifndef POBJECTCOMBOBOX_H
#define POBJECTCOMBOBOX_H

#include "orm/persistence/pobject.h"
#include "orm/repository/repositoryproperty.h"
#include "pobjectlistprovider.h"

#include <list>

#include <QComboBox>
#include <QPixmap>

class PObjectComboBox : public QComboBox
{
    Q_OBJECT
public:

    PObjectComboBox(QWidget *parent = 0);
    PObjectComboBox(PObjectListProvider *prov, QWidget *parent = 0);
    PObjectComboBox(RepositoryProperty *rp, PObject *parent, QWidget *pw = 0);
    PObjectComboBox(QString className, QWidget *pw);

    void load();
    void setProvider(PObjectListProvider *prov);
    void setParentObject(PObject *po);
    PObject* getCurrentObject();
    PObject* getObject(int i);
    PObject* addNewObject();
    void setActiveObject(PObject *o);


private:
    void doCommonSetup();
    int getIndex(PObject *o);


    void reload();
    void load(list<PObject*> *ol);

signals:
    
public slots:
    void nameChanged(QString newName);
    void indexChanged(QString text);

private:
    PObject *currentObject;
    //list<PObject*> *olist;
    QPixmap icon;
    //RepositoryProperty *prop;
    PObject *parent;
    PObjectListProvider *provider;
};

#endif // POBJECTCOMBOBOX_H
