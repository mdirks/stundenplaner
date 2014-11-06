#ifndef TEXTPROPERTYBROWSER_H
#define TEXTPROPERTYBROWSER_H

#include "textpropertyviewer.h"
#include "orm/persistence/pobject.h"
#include "orm/repository/repositoryproperty.h"
#include "orm/repository/collectionproperty.h"
#include "gui/forms/pobjectcombobox.h"

#include <QWidget>
#include <QToolBar>
#include <QComboBox>
#include <QSpinBox>
#include <QString>

#include <list>

class TextPropertyBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit TextPropertyBrowser(PObject *po, RepositoryProperty *colProp, RepositoryProperty *dispProp, QWidget *parent = 0);
    void setParentObject(PObject *po);

protected:
    //PObject* getObject(int i);
    //void load(list<PObject*> *ol);

signals:
    void pageRequested(int i);
    
public slots:
    void indexChanged(int i);
    void newObject();
    void numberChanged(int i);
    void nameChanged(QString newName);

private:
    TextPropertyViewer *viewer;
    QToolBar *toolBar;
    PObjectComboBox *combo;
    //list<PObject*> *olist;
    PObject *parentObject;
    RepositoryProperty *colProp;
    QSpinBox *spinBox;
};

#endif // TEXTPROPERTYBROWSER_H
