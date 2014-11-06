//
// C++ Implementation: doctree_stunden
//
// Description: 
//
//
// Author: Marcus Dirks <mopp@suse>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include <qlayout.h>

#include "doctree_stunden.h"
#include "stundelistboxitem.h"
#include "../datamodel/stunde.h"
#include "../datamodel/stundemapper.h"
#include "guirepository.h"

doctree_stunden::doctree_stunden(QWidget *parent)
 : QWidget(parent)
{	
	QBoxLayout * l = new QHBoxLayout( this );
	//setResizeEnabled(true);
	listBox = new PObjectListBox(this);
	l->addWidget(listBox);
	
	

	//setWidget(listBox);
	//listBox->show();
	//readStunden();
	
	connect(listBox,SIGNAL(doubleClicked(QListBoxItem*)),this,SLOT(activateItem(QListBoxItem*)));

}


doctree_stunden::~doctree_stunden()
{
}




/*!
    \fn doctree_stunden::readStunden()
 */
void doctree_stunden::readStunden()
{
    Database *db = Database::getInstance();
    list<stunde*> *v = stundemapper::getInstance()->find();
    listBox->addObjects((list<PObject*>*)v);
    /*
    stunde *st;
    StundeListBoxItem *item;
    for(vector<PObject*>::iterator it=v->begin(); it!=v->end(); ++it){
	st=(stunde*) *it;

	item = new StundeListBoxItem(st,listBox);
	//listBox->insertItem(item);
	qDebug(QString("Insert stunde into list: %1").arg(st->getID()) );
    }
    qDebug("done: insertion");
    */	

}


/*!
    \fn doctree_stunden::mouseDoubleClickEvent(QMouseEvent *e)
 */
void doctree_stunden::contentsMouseDoubleClickEvent(QMouseEvent *e)
{
    qDebug(QString("double click"));

    StundeListBoxItem *item = (StundeListBoxItem*) listBox->itemAt(e->pos());
    if(item){
    	stunde *st = item->getStunde();
	qDebug(QString("Got item for stunde %1").arg(st->getID()));
    }
}


/*!
    \fn doctree_stunden::contentsMousePressEvent(QMouseEvent *e)
 */
void doctree_stunden::contentsMousePressEvent(QMouseEvent *e)
{
    qDebug(QString("Mouse pressed"));
}


/*!
    \fn doctree_stunden::activateItem(QListBoxItem *item)
 */
void doctree_stunden::activateItem(QListBoxItem *item)
{
    StundeListBoxItem *it = (StundeListBoxItem*) item;
    if(item){
    	stunde *st = it->getStunde();
	qDebug(QString("Got item for stunde %1").arg(st->getID()));
	GuiRepository::getInstance()->showFormForObject(st);
    }
}
