#include "pobjectlistprovider.h"
#include "orm/transactions/transactions.h"
#include "orm/repository/collectionproperty.h"
#include "orm/mapping/mappingcontroler.h"
#include "gui/actions/guicreateaction.h"

PObject* PObjectListProvider::addNewObject()
{
    PObject *o = GuiCreateAction::getInstance()->create(getClassName().toStdString());
    if(o) addObject(o);
    return o;
}

PoLListProvider::PoLListProvider(list<PObject*> *olist, QString className)
{
    this->olist=olist;
    this->className=className;
}


list<PObject*> *PoLListProvider::objectList()
{
    return olist;
}

void PoLListProvider::addObject(PObject *o)
{
    //Transactions::getCurrentTransaction()->add(olist);
    olist->push_back(o);
}

QString PoLListProvider::getClassName()
{
    if(className.isEmpty() && !olist->empty()){
        PObject *o = olist->front();
        if(o){
            className = QString::fromStdString(o->getClassName());
        }
    }
    return className;
}

void PoLListProvider::deleteObject(PObject *o)
{
    olist->remove(o);
}

RpListProvider::RpListProvider(RepositoryProperty *rp, PObject *parentObject)
{
    this->rp=rp;
    this->parentObject = parentObject;

}

list<PObject*> *RpListProvider::objectList()
{
    list<PObject*> *olist=0;
    if (rp && rp->isCollection() && parentObject){
        olist=rp->asCollection( parentObject ) ;
    }
    return olist;
}

void RpListProvider::addObject(PObject *o)
{
    if(rp && parentObject)
    {
        Transaction *t=Transactions::getCurrentTransaction();
        t->add(parentObject);
        if(CollectionProperty *cp = dynamic_cast<CollectionProperty*>(rp)){
            //startEdit();
            cp->add(o,parentObject);
        }
    }


}

QString RpListProvider::getClassName()
{
    return rp->getType().c_str();
}

void RpListProvider::setParentObject(PObject *po)
{
    this->parentObject=po;
}

void RpListProvider::deleteObject(PObject *o)
{
    CollectionProperty *colProp = dynamic_cast<CollectionProperty*>(rp);
    if(colProp){
        colProp->remove( o,parentObject);
    }
}


MapperListProvider::MapperListProvider(QString className)
{
    this->mapper=MappingControler::getInstance()->getMapperByName(className.toStdString());
}

MapperListProvider::MapperListProvider(AbstractMapper *mapper)
{
    this->mapper=mapper;

}

list<PObject*> *MapperListProvider::objectList()
{
   return mapper->find_gen();
}

void MapperListProvider::addObject(PObject *o)
{
    mapper->reset();
}

QString MapperListProvider::getClassName()
{
    return mapper->getClassName().c_str();
}

void MapperListProvider::deleteObject(PObject *o)
{
    mapper->remove(o);
    Transactions::getCurrentTransaction()->add(o);
}
