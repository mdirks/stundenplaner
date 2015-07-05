#ifndef URLEDITOR_H
#define URLEDITOR_H

#include "ui_urleditor.h"
#include "orm/persistence/pobject.h"
#include "orm/repository/repositoryproperty.h"

#include <QWidget>

class UrlEditor : public QWidget
{
Q_OBJECT

public:
    UrlEditor(PObject *o, RepositoryProperty *prop, QWidget *p);
    ~UrlEditor();

public slots:
    void chooseUrl();
    void editUrl();

private:
    PObject *po;
    RepositoryProperty *prop;
    Ui::UrlEditor *ui;
};

#endif // URLEDITOR_H
