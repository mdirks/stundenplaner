#ifndef ORMDIALOG_H
#define ORMDIALOG_H

#include <QWidget>
#include <QListWidgetItem>
#include "../mapping/mappingeventlistener.h"


namespace Ui {
class OrmDialog;
}

class OrmDialog : public QWidget, public MappingEventListener
{
    Q_OBJECT

public:
    explicit OrmDialog(QPixmap &pm, QWidget *parent = nullptr);
    bool consider(MappingEvent *me) override;

    ~OrmDialog();

private:
    Ui::OrmDialog *ui;
};


class EventListWidgetItem : public QListWidgetItem
{

public:
    EventListWidgetItem(MappingEvent *me);
};

#endif // ORMDIALOG_H
