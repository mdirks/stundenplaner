#include "collectiondisplay.h"
#include "ui_collectiondisplay.h"
#include "orm/repository/repository.h"


CollectionDisplay::CollectionDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CollectionDisplay)
{
    ui->setupUi(this);
}


CollectionDisplay::CollectionDisplay(QString clName, QString propName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CollectionDisplay)
{
    ui->setupUi(this);

    setContents(clName,propName);
}


void CollectionDisplay::setContents(QString clName, QString propName)
{
    ui->viewCollections->setObjectListProvider(new MapperListProvider(clName));
    RepositoryProperty *rp= Repository::getInstance()->getRepositoryEntry(clName.toStdString().c_str())->getProperty(propName.toStdString().c_str());
    prov = new RpListProvider(rp);
}

CollectionDisplay::~CollectionDisplay()
{
    delete ui;
}


void CollectionDisplay::changeCollection()
{
    if(prov){
        PObject *o=ui->viewCollections->getCurrent();
        if(o){
            prov->setParentObject(o);
            ui->viewItems->setObjectListProvider(prov);
            ui->viewItems->setCurrentRow(0);
        }
    }
}

void CollectionDisplay::changeItem()
{
    emit itemChanged();
}

PObject* CollectionDisplay::getCurrentItem()
{
    return ui->viewItems->getCurrent();
}
