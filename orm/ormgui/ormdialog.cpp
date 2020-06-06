#include "ormdialog.h"
#include "ui_ormdialog.h"


OrmDialog::OrmDialog(QPixmap &pm, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrmDialog)
{
    ui->setupUi(this);
    ui->labelSplash->setPixmap(pm);
    ui->listEvents->hide();
}

OrmDialog::~OrmDialog()
{
    delete ui;
}

bool OrmDialog::consider(MappingEvent *me)
{
    ui->listEvents->addItem(new EventListWidgetItem(me));
    ui->listEvents->show();
    return true;
}


EventListWidgetItem::EventListWidgetItem(MappingEvent *me)
    : QListWidgetItem(me->getMessage())
{

}
