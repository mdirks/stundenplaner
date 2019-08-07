#ifndef COLLECTIONSELECTIONDIALOG_H
#define COLLECTIONSELECTIONDIALOG_H

#include "orm/persistence/pobject.h"
#include "orm/repository/repositoryproperty.h"
#include "gui/forms/pobjecticonview.h"

#include <QWidget>
#include <QLabel>

#include <list>


class CollectionSelectionDialog : public QWidget
{
Q_OBJECT

public:
    CollectionSelectionDialog(PObject *po, RepositoryProperty *rp, QWidget *parent);
    ~CollectionSelectionDialog();

    list<PObject*>* getSelection();

private:
    PObjectIconView *listAll,*listDisplay;
    QLabel *labelDisplay,*labelAll;
};

#endif // COLLECTIONSELECTIONDIALOG_H
