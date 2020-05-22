#include "docstoredialog.h"
#include "ui_docstoredialog.h"


#include <QFileDialog>

#include "services/docstore/docstore.h"

DocStoreDialog::DocStoreDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DocStoreDialog)
{
    ui->setupUi(this);
    ui->labelLocation->setText(locationDirName);
}

DocStoreDialog::~DocStoreDialog()
{
    delete ui;
}


void DocStoreDialog::chooseLocation()
{
    locationDirName=QFileDialog::getExistingDirectory();
    ui->labelLocation->setText(locationDirName);

    DocStore::getInstance()->setLocation(locationDirName);
}
