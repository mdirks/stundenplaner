#include "pobjectcombobox.h"

#include "orm/transactions/transactions.h"
#include "gui/base/guiconfig.h"
#include "gui/actions/guicreateaction.h"
#include "pobjectlistprovider.h"
#include "orm/repository/collectionproperty.h"

#define HEIGHT 17

PObjectComboBox::PObjectComboBox(QWidget *parent) :
    QComboBox(parent)
{
    provider =0;

    doCommonSetup();
}

PObjectComboBox::PObjectComboBox(RepositoryProperty *rp, PObject *parent, QWidget *pw)
    : QComboBox(pw)
{
    provider = new RpListProvider(rp,parent);

    doCommonSetup();

}

PObjectComboBox::PObjectComboBox(PObjectListProvider *prov, QWidget *pw)
    : QComboBox(pw)
{
    provider=prov;

    doCommonSetup();
}

PObjectComboBox::PObjectComboBox(QString className, QWidget *pw)
    : QComboBox(pw)
{
    provider=new MapperListProvider(className);

    doCommonSetup();
}

void PObjectComboBox::doCommonSetup()
{
    currentObject=0;

    QString String = "border: 0px solid black;";
    setStyleSheet(String );
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    setEditable(true);
    setInsertPolicy(QComboBox::InsertAtCurrent);
    setFixedHeight(HEIGHT);

    if(provider){
        icon=GuiConfig::getInstance()->getIcon(provider->getClassName());
    }

    load();

    connect(this,SIGNAL(editTextChanged(QString)),this,SLOT(nameChanged(QString)));
    connect(this,SIGNAL(currentIndexChanged(QString)),this,SLOT(indexChanged(QString)));

}

void PObjectComboBox::load()
{
    if(provider){
        load(provider->objectList());
        //isLoaded=true;
        addItem("Create new item");
    }
}

void PObjectComboBox::reload()
{
    disconnect(this);
    clear();
    load();
    connect(this,SIGNAL(editTextChanged(QString)),this,SLOT(nameChanged(QString)));
    connect(this,SIGNAL(currentIndexChanged(QString)),this,SLOT(indexChanged(QString)));
}




void PObjectComboBox::load(list<PObject*> *olist)
{
    if(olist){
        for(list<PObject*>::iterator it=olist->begin(); it!=olist->end(); it++)
        {
            addItem(icon,(*it)->getName().c_str());
        }



    }
    if(!olist || olist->size()==0){
        addItem("..");
    }
}

/*
void PObjectComboBox::setObjectList(list<PObject*> *olist)
{
    this->olist=olist;
    load();
    setCurrentIndex(0);
}
*/


void PObjectComboBox::setParentObject(PObject *o)
{
    if(provider){
        disconnect(this);
        provider->setParentObject(o);
        reload();
    }
}


void PObjectComboBox::setProvider(PObjectListProvider *prov)
{
    this->provider=prov;
    if(provider) reload();
}

void PObjectComboBox::indexChanged(QString text)
{
    if(text=="Create new item"){
        addNewObject();
    }
}




PObject* PObjectComboBox::addNewObject()
{
    if(provider){
        PObject *o = provider->addNewObject();
        if(o){
            reload();
            setCurrentIndex(getIndex(o));
        }
    }

    /*
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
    */

}

PObject* PObjectComboBox::getObject(int i)
{
    PObject *o=0;
    if(provider){
        list<PObject*> *olist=provider->objectList();
        if(olist && i<olist->size() && i>-1){
            std::list<PObject*>::iterator it = olist->begin();
            std::advance(it,i);
            o=*it;
        }
    }
    return o;
}

int PObjectComboBox::getIndex(PObject *o)
{
    int i=-1;
    if(provider){
        list<PObject*> *olist=provider->objectList();
        if(olist){
            std::list<PObject*>::iterator it = olist->begin();
            int count=0;
            while(i<0 && it != olist->end()){
                if(o==*it){
                    i=count;
                }
                count++;
                it++;
            }
        }
    }
    return i;
}


void PObjectComboBox::nameChanged(QString newName)
{
    PObject *o=getObject(currentIndex());
    if(o){
        Transactions::getCurrentTransaction()->add(o);
        o->setName(newName.toStdString());
    }
}

PObject *PObjectComboBox::getCurrentObject()
{
    return getObject(currentIndex());
}
