#ifndef POBJECTCOMBOBOX_H
#define POBJECTCOMBOBOX_H

#include "orm/persistence/pobject.h"
#include "orm/repository/repositoryproperty.h"

#include <list>

#include <QComboBox>
#include <QPixmap>

class PObjectComboBox : public QComboBox
{
    Q_OBJECT
public:
    PObjectComboBox(list<PObject*> *olist, QWidget *parent = 0);
    PObjectComboBox(RepositoryProperty *rp, PObject *parent, QWidget *pw = 0);
    
    void load(list<PObject*> *ol);
    void load();

    void setParentObject(PObject *o);
    void setObjectList(list<PObject*> *olist);


    PObject* getCurrentObject();
    PObject* addNewObject();

    PObject* getObject(int i);



signals:
    
public slots:
    void nameChanged(QString newName);
    void indexChanged(QString text);

private:
    PObject *currentObject;
    list<PObject*> *olist;
    QPixmap icon;
    RepositoryProperty *prop;
    PObject *parent;
};

#endif // POBJECTCOMBOBOX_H
