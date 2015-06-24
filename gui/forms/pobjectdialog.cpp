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

#include <QDragEnterEvent>

/*
PObjectView::PObjectView( list<PObject*> *listPObjects, QWidget *parent)
 : QListWidget(parent)
{
	for(list<PObject*>::iterator it = listPObjects->begin(); it != listPObjects->end(); it++)
	{
		new PObjectViewItem((*it),this);
	}
    setViewMode(QListView::IconMode);
}
*/

/*
PObjectViewx::~PObjectView()
{
}
*/

/*
void PObjectViewx::contentsDragEnterEvent(QDragEnterEvent *e)
{
    if(e->mimeData()->hasFormat("application/pobject")){
       e->acceptProposedAction();
    }

}
*/
/*
QDragObject* PObjectView::dragObject()
{
	PObjectDrag *drag=0;

	PObjectViewItem *item = static_cast<PObjectViewItem*>(currentItem());
	if(item){
		PObject *o = item->getPObject();
		if(o){
			drag = new PObjectDrag(o,this);
			
			if(item->pixmap()){
				drag->setPixmap(QPixmap(*item->pixmap()),QPoint(item->pixmapRect().width()/2, item->pixmapRect().height()/2) );
			}
												
		
			//drag->dragCopy();
		} else {
			qDebug("PObjectView::dragObject() : drag failed, could not get selected objecct");
		}
	} else {
		qDebug("No item selected");
		return 0;
	}
	

	return drag;
}
*/
	
/*
PObjectViewItem::PObjectViewItem(PObject *obj, PObjectView *parent) : QListWidgetItem(parent)
{
	this->obj = obj;
    setIcon(GuiConfig::getInstance()->getIcon(obj->getPersistenceObject()->getClassName().c_str()));
    setText(obj->getName().c_str());
};
*/
/*
PObject* PObjectViewItem::getPObject()
{
	return this->obj;
}
*/
PObjectDialog::PObjectDialog(PObjectListProvider *prov, QWidget *parent) : KDialog(parent)
{

    objectView = new PObjectIconView(prov,this);
    objectView->load();
    setMainWidget(objectView);

    resize(500,600);
    //this->mapper = mapper;

}



PObjectDialog::PObjectDialog(AbstractMapper *mapper, QWidget *parent) : KDialog(parent)
{
	
    objectView = new PObjectIconView(mapper->find_gen(),this);
    objectView->load();
	setMainWidget(objectView);

	resize(500,600);
	//this->mapper = mapper;
	
}

PObjectDialog::PObjectDialog(list<PObject*> *list_objects, QWidget *parent) : KDialog(parent)
{
    objectView = new PObjectIconView(list_objects,this);
    objectView->load();
	setMainWidget(objectView);
	
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
