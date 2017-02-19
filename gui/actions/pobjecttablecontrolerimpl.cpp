/***************************************************************************
 *   Copyright (C) 2008 by Marcus Dirks   *
 *   m-dirks@web.de   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "pobjecttablecontrolerimpl.h"
#include "orm/persistence/pobject.h"
#include "orm/transactions/transactions.h"
#include "orm/repository/repositoryproperty.h"
#include "orm/repository/collectionproperty.h"
#include "orm/mapping/abstractmapper.h"
#include "gui/actions/guicreateaction.h"
#include "gui/dialogs/propertychooser.h"

#include <qmessagebox.h>
//#include <kstdaccel.h>
#include <QDebug>

PObjectTableControlerImpl::PObjectTableControlerImpl(PObjectTable *table)
{
	this->table = table;
    //configurePropertiesAction = new QAction("Properties festlegen", KStdAccel::shortcut(KStdAccel::New), this, SLOT(configureProperties()), table,"reload");
}


PObjectTableControlerImpl::~PObjectTableControlerImpl()
{
}


void PObjectTableControlerImpl::addElement(int row){
	PObject *o=0;
	Transaction *t=Transactions::getCurrentTransaction();
	RepositoryProperty *prop = table->getProperty();
	PObject *parentObject = table->getParentObject();
	if(prop && parentObject){
		t->add(parentObject);
		//string className = prop->getType();
		o = GuiCreateAction::getInstance()->create(prop->getType());
		if(CollectionProperty *cp = dynamic_cast<CollectionProperty*>(prop)){
			table->startEdit();
			cp->add(o,parentObject);
			
		}
		t->add(o);
	} else if(AbstractMapper *mapper=table->getMapper()) {
		 //o = mapper->create();
		o = GuiCreateAction::getInstance()->create(mapper->getClassName());
		t->add(o);
	}
	
	if(o){
		table->createRow(row,o);	
		table->update();
	} else {
		QMessageBox::warning(table,"Creation failed","Could not create object");
	}
}



QMenu* PObjectTableControlerImpl::getContextMenu(const QPoint &pos)
{
    QMenu *popup = new QMenu(table);
	

    popup->addAction("Properties festlegen",this,SLOT(configureProperties()));
	//}
    //( new QAction("Löschen", KStdAccel::shortcut(KStdAccel::New), this, SLOT(deleteSelected()), table, "activate") )->plug(popup);
        popup->addAction("Löschen",this,SLOT(deleteSelected()));
    return popup;
	
}

void PObjectTableControlerImpl::configureProperties()
{
	list<RepositoryProperty*>* list_prop = PropertylistChooserDialog::chooseProperties(table->getMapper());
	table->setDisplayProperties(list_prop);
}

/*!
    \fn PObjectTableControlerImpl::deleteSelected()
 */
void PObjectTableControlerImpl::deleteSelected()
{
    	table->deleteSelected();
	/*
	PObject *o=0;
	Transaction *t=Transactions::getCurrentTransaction();
	RepositoryProperty *prop = table->getProperty();
	PObject *parentObject = table->getParentObject();
	int row = table->currentRow();
	if(prop && parentObject){
		t->add(parentObject);
		if(CollectionProperty *cp = dynamic_cast<CollectionProperty*>(prop)){
			table->startEdit();
			o=table->getObject(row);
			qDebug(QString("PObjectTableControlerImpl::deleteSelected : deleting %1").arg(o->getName()));
			cp->remove(o,parentObject);
			
		}
	} else if(AbstractMapper *mapper=table->getMapper()) {
		 //o = mapper->create();
		o = GuiCreateAction::getInstance()->create(mapper->getClassName());
		t->add(o);
	}
	
	if(o){
		table->removeRow(row);	
		table->update();
	} else {
		QMessageBox::warning(table,"Creation failed","Could not create object");
	}
	*/
}
