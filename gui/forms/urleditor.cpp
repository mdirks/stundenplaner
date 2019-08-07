#include "urleditor.h"

#include "gui/base/guiconfig.h"
#include "orm/transactions/transactions.h"

#include <QFile>
#include <QFileDialog>

UrlEditor::UrlEditor(PObject *o, RepositoryProperty *prop, QWidget *p)
    : QWidget(p),
        ui(new Ui::UrlEditor)
{
    po =o;
    this->prop=prop;
    ui->setupUi(this);

    QPixmap pmap=GuiConfig::getInstance()->getIcon( prop->getType().c_str() );
    pmap=pmap.scaledToHeight(20);
    ui->iconLabel->setPixmap(pmap);
    ui->valueLabel->setText(prop->asString(o).c_str());

    connect(ui->chooseButton,SIGNAL(clicked()),this,SLOT(chooseUrl()));
    connect(ui->editButton,SIGNAL(clicked()),this,SLOT(editUrl()));
}

UrlEditor::~UrlEditor()
{

}


void UrlEditor::chooseUrl()
{
    QString filename = QFileDialog::getSaveFileName();
    QFile file(filename);
    if(! file.exists()){
        file.open(QIODevice::ReadWrite);
        file.close();
    }

    ui->valueLabel->setText(filename);
    Transactions::getCurrentTransaction()->add(po);
    prop->fromString(filename.toStdString(),po);
}

void UrlEditor::editUrl()
{

}
