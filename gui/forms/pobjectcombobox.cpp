#include "pobjectcombobox.h"

#include "orm/transactions/transactions.h"
#include "gui/base/guiconfig.h"
#include "gui/actions/guicreateaction.h"
#include "orm/repository/collectionproperty.h"

#define HEIGHT 17

PObjectComboBox::PObjectComboBox(list<PObject*> *ol,QWidget *parent) :
    QComboBox(parent)
{
    currentObject=0;

    this->olist=ol;
    this->prop=0;


    QString String = "border: 0px solid black;";
    setStyleSheet(String );
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    setEditable(true);
    setInsertPolicy(QComboBox::InsertAtCurrent);
    setFixedHeight(HEIGHT);
    if(olist){
        load(olist);
    }

    connect(this,SIGNAL(editTextChanged(QString)),this,SLOT(nameChanged(QString)));

}

PObjectComboBox::PObjectComboBox(RepositoryProperty *rp, PObject *parent, QWidget *pw)
    : QComboBox(pw)
{
    this->prop=rp;
    this->parent=parent;
    this->olist=0;


    QString String = "border: 0px solid black;";
    setStyleSheet(String );
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    setEditable(true);
    setInsertPolicy(QComboBox::InsertAtCurrent);
    setFixedHeight(HEIGHT);

    load();
    connect(this,SIGNAL(editTextChanged(QString)),this,SLOT(nameChanged(QString)));
    connect(this,SIGNAL(currentIndexChanged(QString)),this,SLOT(indexChanged(QString)));
}

void PObjectComboBox::load()
{
    if(prop && parent)
    {
        olist=prop->asCollection(parent);
    }
    if(olist){
        load(olist);
    }

}

void PObjectComboBox::setObjectList(list<PObject*> *olist)
{
    this->olist=olist;
    load();
    setCurrentIndex(0);
}

void PObjectComboBox::setParentObject(PObject *o)
{
    this->parent=o;
    if(prop) load();
}

void PObjectComboBox::indexChanged(QString text)
{
    if(text=="Create new item"){
        addNewObject();
    }
}

void PObjectComboBox::load(list<PObject*> *ol)
{
    this->olist=ol;

    if(olist){
        if(olist->size()>0){
            icon=GuiConfig::getInstance()->getIcon(olist->front());
        }

        clear();
        for(list<PObject*>::iterator it=olist->begin(); it!=olist->end(); it++)
        {
            addItem(icon,(*it)->getName().c_str());
        }

        if(olist->size()==0){
            addItem("..");
        }
    }

    if(prop && parent){
        addItem("Create new item");
    }
}


PObject* PObjectComboBox::addNewObject()
{
    PObject *o=0;
    if(prop && parent){
        Transaction *t=Transactions::getCurrentTransaction();
        t->add(parent);
        //string className = prop->getType();
        o = GuiCreateAction::getInstance()->create(prop->getType());
        t->add(o);
        if(CollectionProperty *cp = dynamic_cast<CollectionProperty*>(prop)){
            cp->add(o,parent);
        }
        load();
    }

}

PObject* PObjectComboBox::getObject(int i)
{
    PObject *o=0;
    if(olist && i<olist->size() && i>-1){
        std::list<PObject*>::iterator it = olist->begin();
        std::advance(it,i);
        o=*it;
    }
    return o;
}


void PObjectComboBox::nameChanged(QString newName)
{
    PObject *o=getObject(currentIndex());
    if(o){
        Transactions::getCurrentTransaction()->add(o);
        o->setName(newName.toStdString());
    }
}
