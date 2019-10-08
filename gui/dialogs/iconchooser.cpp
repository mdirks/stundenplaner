#include "iconchooser.h"
#include <QHBoxLayout>

#include "base/guiconfig.h"

IconChooser::IconChooser(QWidget *parent)
    : QListWidget(parent)
{
    QStringList all=GuiConfig::getInstance()->getRegisteredIconObjects();
    for(QStringList::iterator it=all.begin(); it!=all.end(); it++)
    {
        QString objectName=(*it);
        QIcon icon = GuiConfig::getInstance()->getIcon(objectName);
        QListWidgetItem *item =new IconChooserItem(icon,objectName,this);
    }
    connect(this,&QListWidget::itemDoubleClicked,this,&IconChooser::activateItem);
}


void IconChooser::activateItem(QListWidgetItem *item)
{
    IconChooserItem *ii = dynamic_cast<IconChooserItem*>(item);
    if(ii){
        GuiConfig *config=GuiConfig::getInstance();
        QString className=item->text();
        config->selectIcon(className);
        ii->setIcon(config->getIcon(className));
    }
}


IconChooserItem::IconChooserItem(QIcon icon,QString objectName,QListWidget *parent)
    : QListWidgetItem(icon,objectName,parent)
{

}


IconChooserDialog::IconChooserDialog(QWidget *parent)
    : QDialog(parent)
{
    QHBoxLayout *layout=new QHBoxLayout();
    chooser = new IconChooser(this);
    layout->addWidget(chooser);
    this->setLayout(layout);

}
