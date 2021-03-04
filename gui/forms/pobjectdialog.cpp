// C++ Implementation: mapperview
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "pobjectdialog.h"

#include "gui/base/guiconfig.h"
#include "datamodel/datamodelrepository.h"
//#include "gui/draganddrop/pobjectdrag.h"
#include "orm/mapping/mappingcontroler.h"

#include <QDragEnterEvent>


PObjectDialog::PObjectDialog(PObjectListProvider *prov, QWidget *parent) : QDialog(parent)
{

    objectView = new PObjectIconView(prov,this);
    objectView->load();
    //ToDo: does chooser show up, add to layout ?
    //setMainWidget(objectView);

    resize(500,600);
    //this->mapper = mapper;

}



PObjectDialog::PObjectDialog(AbstractMapper *mapper, QWidget *parent) : QDialog(parent)
{
	
    objectView = new PObjectIconView(mapper->find_gen(),this);
    objectView->load();
    //ToDo: does chooser show up, add to layout ?
    //setMainWidget(objectView);

	resize(500,600);
	//this->mapper = mapper;
	
}

PObjectDialog::PObjectDialog(list<PObject*> *list_objects, QWidget *parent) : QDialog(parent)
{
    objectView = new PObjectIconView(list_objects,this);
    objectView->load();
    //ToDo: does chooser show up, add to layout ?
    //setMainWidget(objectView);
	
	resize(500,600);
}

PObject* PObjectDialog::getSelectedPObject()
{
    return objectView->getSelected();
}

void PObjectDialog::setDisplayProperty(RepositoryProperty *rp)
{
    objectView->setDisplayProperty(rp);
}

void PObjectDialog::showPObjects(PObjectListProvider *prov, RepositoryProperty *displayProp)
{
    PObjectDialog *instance = new PObjectDialog(prov);
    if(displayProp){
        instance->setDisplayProperty(displayProp);
    }
    instance->exec();
}


PObject* PObjectDialog::choosePObject(string className)
{
    AbstractMapper *m = MappingControler::getInstance()->getMapperByName(className);
    PObjectDialog *instance = new PObjectDialog(m);
    instance->exec();
    return instance->getSelectedPObject();
}


PObject* PObjectDialog::choosePObject(AbstractMapper *mapper)
{
	PObjectDialog *instance = new PObjectDialog(mapper);
	instance->exec();
	return instance->getSelectedPObject();
}

PObject* PObjectDialog::choosePObject(list<PObject*> *list_objects)
{
	PObjectDialog *instance = new PObjectDialog(list_objects);
	instance->exec();
	return instance->getSelectedPObject();
}
