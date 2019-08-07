//
// C++ Implementation: %{MODULE}
//
// Description:
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "typelistview.h"

#include <qpoint.h>

#include "typeitem.h"
#include "actionitem.h"
#include "objectitem.h"
#include "draganddrop/pobjectdrag.h"
#include "../persistence/pobject.h"
#include "guirepository.h"


TypeListView::TypeListView(QWidget *parent, const char *name)
 : QListWidget(parent, name)
{
	selection = 0;

    connect(this,SIGNAL(doubleClicked(QListWidgetItem *,const QPoint &, int)), this, SLOT(checkForObjectItem(QListWidgetItem *)));
    connect(this,SIGNAL(pressed(QListWidgetItem *)), this, SLOT(checkForDrag(QListWidgetItem *)));
    connect(this,SIGNAL(clicked(QListWidgetItem *)), this, SLOT(checkForActionItem(QListWidgetItem *)));
    connect(this,SIGNAL(returnPressed(QListWidgetItem *)), this, SLOT(checkForActionItem(QListWidgetItem *)));
}


TypeListView::~TypeListView()
{
}


void TypeListView::addTypeNodes(list<AbstractMapper*> *list_mappers)
{
	for(list<AbstractMapper*>::iterator it=list_mappers->begin(); it != list_mappers->end(); it++){
		addTypeNode(*it);
	}
}


/*!
    \fn TypeListView::addTypeNode(AbstractMapper *mapper)
 */
void TypeListView::addTypeNode(AbstractMapper *mapper)
{
     new TypeItem(mapper,this);
}

void TypeListView::checkForActionItem(QListWidgetItem *item)
{
	if(item && item->rtti() == ActionItem::Rtti){
		((ActionItem*) item)->actionPerformed();
	} 
	selection = 0;
}

void TypeListView::checkForObjectItem(QListWidgetItem *item)
{
	if(item->rtti() == ObjectItem::Rtti) {
		PObject *o = ((ObjectItem*) item)->getObject();
		GuiRepository::getInstance()->showFormForObject(o);
	}
	
	selection=0;
}


/*!
    \fn TypeListView::dragStart()
 */
void TypeListView::checkForDrag(QListViewItem *item)
{
	selection = item;    
}


void TypeListView::contentsMouseMoveEvent ( QMouseEvent * e )
{
	if(selection){
		 if(selection->rtti() == ObjectItem::Rtti){
			qDebug("TypeListView::checkForDrag : starting drag");
			PObject *o = ((ObjectItem*) selection)->getObject();
			PObjectDrag *dragObject = new PObjectDrag(o,this);
			dragObject->dragCopy();
		}
		selection=0;
	}
	QListView::contentsMouseMoveEvent(e);
}
