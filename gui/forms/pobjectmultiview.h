#ifndef POBJECTMULTIVIEW_H
#define POBJECTMULTIVIEW_H

#include "pobjecticonview.h"
#include "pobjecttable.h"

#include <QStackedWidget>
#include <QMenu>
#include <QMouseEvent>

class PObjectMultiView : public QStackedWidget
{
    Q_OBJECT
public:
    PObjectMultiView(RepositoryProperty *prop, PObject *parentObject, QWidget *parent = 0);


    /*
    PObjectTable(list<PObject*> *olist, QString type, QWidget *parent=0, bool addable=false);
    PObjectTable(string className, QWidget *parent=0, bool addable=false);
    PObjectTable(AbstractMapper *mapper,QWidget *parent=0, bool addable=true);
    PObjectTable(RepositoryProperty *prop, PObject *parentObject, QWidget *parent=0, bool addable=true);

    PObjectIconView(QWidget *parent=0);
    PObjectIconView(list<PObject*> *olist, QWidget *parent=0);
    PObjectIconView(AbstractMapper *mapper, QWidget *parent=0);
        PObjectIconView(RepositoryProperty *prop, PObject *parentObject, QWidget *parent=0);
    */

    void load();
    bool isIconView();

    PObjectTable* getTable();
    PObjectIconView* getIconView();
    QMenu* getPopupMenu();

public slots:
    void switchView();

protected:
    virtual void mousePressEvent(QMouseEvent *e);

private:
    PObjectTable *table;
    PObjectIconView *iconView;
    
};

#endif // POBJECTMULTIVIEW_H
