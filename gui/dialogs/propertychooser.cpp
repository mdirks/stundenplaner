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
#include "propertychooser.h"
#include "orm/repository/repository.h"
#include "orm/repository/repositoryentry.h"
#include "orm/repository/repositoryproperty.h"
#include "services/utils/namedobjectptrcomp.h"
#include "qlayout.h"
#include "qpushbutton.h"
#include <QDebug>

PropertyListChooser::PropertyListChooser(AbstractMapper *mapper, QWidget *parent)
	: QWidget(parent)
{
	QHBoxLayout *la = new QHBoxLayout(this);
	
	viewChooser = new PropertyChooser(mapper,this);
	//rootViewSelected = new QListViewItem(viewChooser,"Auswahl");
	la->addWidget(viewChooser);

	QWidget *buttonWidget = new QWidget(this);
	QVBoxLayout *laa = new QVBoxLayout(buttonWidget);
	QPushButton *buttonRemove = new QPushButton("Remove",buttonWidget);
	QPushButton *buttonAdd = new QPushButton("Add",buttonWidget);
	laa->addWidget(buttonAdd);
	laa->addWidget(buttonRemove);
	la->addWidget(buttonWidget);

    viewSelected = new QTreeWidget(this);
    viewSelected -> setHeaderItem(new QTreeWidgetItem(viewSelected, QStringList("Property")));
    //viewSelected -> setSorting(-1);
	la->addWidget(viewSelected);

	connect(buttonRemove,SIGNAL(clicked()),this,SLOT(removeSelected()));
	connect(buttonAdd,SIGNAL(clicked()),this,SLOT(addSelected()));


	re_root=Repository::getInstance()->getRepositoryEntry(mapper->getClassName());

}

list<RepositoryProperty*>* PropertyListChooser::selectedProperties()
{
	list<RepositoryProperty*> *result = new list<RepositoryProperty*>();


    for(int i=0; i<viewSelected->topLevelItemCount(); i++){
        QTreeWidgetItem *child = viewSelected->topLevelItem(i);
        PropertyChooserItem *pci = dynamic_cast<PropertyChooserItem*>(child);
        if(pci){
            result->push_back(pci->getProperty());
        }
	}

	return result;
}

void PropertyListChooser::addSelected()
{
	if(RepositoryProperty *rp=viewChooser->selectedProperty()){
		addProperty(re_root,rp);
	} else {
		qDebug("PropertyListChooser::addSelected : no property selected");
	}
}

void PropertyListChooser::removeSelected()
{
    //qDebug() << "Warning: PropertyListChooser::removeSelected() not implemented";

    PropertyChooserItem *selectedItem = dynamic_cast<PropertyChooserItem*>(
                viewChooser->takeTopLevelItem(viewChooser->currentColumn()));

}

void PropertyListChooser::addProperty(RepositoryEntry *re, RepositoryProperty* rp)
{
    //qDebug() << "Warning: PropertyListChooser::addProperty() not implemented";

    viewSelected->addTopLevelItem(new PropertyChooserItem(re, rp,viewSelected));
    //viewSelected->triggerUpdate();


}
PropertyChooser::PropertyChooser(AbstractMapper *mapper, QWidget *parent)
    : QTreeWidget(parent)
{
	if(mapper){
		this->mapper = mapper;
        //addColumn("Property");
        QTreeWidgetItem *root = new QTreeWidgetItem(this,QStringList(mapper->getClassName().c_str()));
		
		RepositoryEntry *re = Repository::getInstance()->getRepositoryEntry(mapper->getClassName());
	
		list<RepositoryProperty*> *list_prop = re->getAllProperties(true);
		list_prop->sort(NamedObjectPtrComp<RepositoryProperty>());
		for(list<RepositoryProperty*>::iterator it = list_prop->begin(); it != list_prop->end(); it++){
			new PropertyChooserItem(re, *it,root);
		}
	} else { qDebug("PropertyChooser : invalid mapper given"); }
}


PropertyChooser::~PropertyChooser()
{
}

RepositoryProperty* PropertyChooser::selectedProperty()
{
    //qDebug() << "Warning: PropertyChooser::selectedProperty() not implemented";
    //return 0;

    PropertyChooserItem *selectedItem = dynamic_cast<PropertyChooserItem*>(
                currentItem());
	if(selectedItem){
		return selectedItem->getProperty();
	} else {
		return 0;
	}

}



PropertyChooserItem::PropertyChooserItem(RepositoryEntry *re, RepositoryProperty *rp, QTreeWidgetItem *parent)
    : QTreeWidgetItem(parent,QStringList(rp->getName().c_str()))
{
	this->rp = rp;
	this->re_root = re;
	activated = false;
	
}
PropertyChooserItem::PropertyChooserItem(RepositoryEntry *re, RepositoryProperty *rp, QTreeWidget *parent)
    : QTreeWidgetItem(parent,QStringList(rp->getName().c_str()))
{
	this->rp = rp;
	this->re_root = re;
	activated = false;
	
}

void PropertyChooserItem::activate()
{
	if(!activated){
		RepositoryEntry *re = Repository::getInstance()->getRepositoryEntry(rp->getType());
		if(re){
			list<RepositoryProperty*> *list_prop = re->getAllProperties(true);
			list_prop->sort(NamedObjectPtrComp<RepositoryProperty>());
			for(list<RepositoryProperty*>::iterator it = list_prop->begin(); it != list_prop->end(); it++){
                QString propName = QString("%1/%2").arg(rp->getName().c_str()).arg(QString::fromStdString((*it)->getName()));
                RepositoryProperty *irp= re_root->getProperty(propName.toStdString());
				new PropertyChooserItem(re_root,irp,this);
			}
		}
	}
}


RepositoryProperty* PropertyChooserItem::getProperty()
{
	return this->rp;
}

PropertyChooserDialog::PropertyChooserDialog(AbstractMapper *mapper, QWidget *parent)
    : QDialog(parent)
{
	chooser = new PropertyChooser(mapper,this);
    //ToDo: does chooser show up, add to layout ?
    //setMainWidget(chooser);
}

RepositoryProperty* PropertyChooserDialog::selectedProperty()
{
	return chooser->selectedProperty();
}

RepositoryProperty* PropertyChooserDialog::chooseProperty(AbstractMapper *mapper)
{
	PropertyChooserDialog *instance = new PropertyChooserDialog(mapper);
	instance->exec();
	return instance->selectedProperty();
}

PropertylistChooserDialog::PropertylistChooserDialog(AbstractMapper *mapper, QWidget *parent)
    : QDialog(parent)
{
	chooser = new PropertyListChooser(mapper,this);
    //ToDo: does chooser show up, add to layout ?
    //setMainWidget(chooser);
}

list<RepositoryProperty*>* PropertylistChooserDialog::selectedProperties()
{
	return chooser->selectedProperties();
}

list<RepositoryProperty*>* PropertylistChooserDialog::chooseProperties(AbstractMapper *mapper)
{
	PropertylistChooserDialog *instance = new PropertylistChooserDialog(mapper);
	instance->exec();
	return instance->selectedProperties();
}
