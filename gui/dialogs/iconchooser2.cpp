#include "iconchooser2.h"
#include "ui_iconchooser2.h"

#include "base/guiconfig.h"
#include <QHBoxLayout>
#include <QDirIterator>
#include <QDebug>

IconChooser2::IconChooser2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IconChooser2)
{
    ui->setupUi(this);
    QStringList all=GuiConfig::getInstance()->getRegisteredIconObjects();
    for(QStringList::iterator it=all.begin(); it!=all.end(); it++)
    {
        QString objectName=(*it);
        QIcon icon = GuiConfig::getInstance()->getIcon(objectName);
        QListWidgetItem *item =new IconChooserItem2(icon,objectName,ui->listChosen);
    }
    //ui->listChosen->setAcceptDrops(true);


    ui->listCollection->setViewMode(QListWidget::IconMode);
    ui->listCollection->setIconSize(QSize(32,32));


    QDirIterator it(":/icons", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString in=it.next();
        QListWidgetItem *item = new QListWidgetItem(QIcon(QString("%1").arg(in))/*,QString("%1").arg(in)*/,"");
        item->setData(Qt::ToolTipRole,in);
        ui->listCollection->addItem(item);
        //qDebug() << it.next();
    }


}

void IconChooser2::slotSelectIcon(QListWidgetItem *item)
{
    QString iconName=item->data(Qt::ToolTipRole).toString();
    QListWidgetItem *it=ui->listChosen->selectedItems().first();
    IconChooserItem2 *icit=dynamic_cast<IconChooserItem2*>(it);
    if(icit){
        icit->selectIcon(iconName);
    }
}

IconChooser2::~IconChooser2()
{
    delete ui;
}



IconChooserItem2::IconChooserItem2(QIcon icon,QString objectName,QListWidget *parent)
    : QListWidgetItem(icon,objectName,parent)
{

}

void IconChooserItem2::selectIcon(QString iconName)
{
    QString className=text();
    qDebug() << "Registering icon for " << className << ": " << iconName;
    GuiConfig::getInstance()->registerIcon(className,iconName);

    QIcon icon = GuiConfig::getInstance()->getIcon(iconName);
    setIcon(icon);
}

IconChooserDialog2::IconChooserDialog2(QWidget *parent)
    : QDialog(parent)
{
    QHBoxLayout *layout=new QHBoxLayout();
    chooser = new IconChooser2(this);
    layout->addWidget(chooser);
    this->setLayout(layout);

}
