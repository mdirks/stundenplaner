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
#include "pobjectlistviewitem.h"

#include "orm/repository/repository.h"
#include "gui/guirepository.h"
#include "gui/base/guiconfig.h"
#include "propertyitem.h"


PObjectListViewItem::PObjectListViewItem(QListWidget *parent, RepositoryProperty *rp, PObject *parent_object)
 : QListWidgetItem(parent)
{
	this->rp = rp;
	this->parent = parent_object;
	this->property = rp->asPObject(parent_object);
	
    //setPixmap(0,GuiConfig::getInstance()->getIcon(property));
	entry = Repository::getInstance()->getRepositoryEntry( property );
}

PObjectListViewItem::PObjectListViewItem(QListWidgetItem *parent, RepositoryProperty *rp, PObject *parent_object)
 : QListWidgetItem()
{
	this->rp = rp;
	this->parent = parent_object;
	this->property = rp->asPObject(parent_object);
    //setPixmap(0,GuiConfig::getInstance()->getIcon(property));
	entry = Repository::getInstance()->getRepositoryEntry( property );
}

PObjectListViewItem::~PObjectListViewItem()
{
}


void PObjectListViewItem::activate()
{
	if(entry){
        //if(!isOpen()){
			list<RepositoryProperty*> *properties = entry->getAllProperties();
			if(properties){
				for(list<RepositoryProperty*>::iterator it=properties->begin(); it != properties->end(); it++){
					RepositoryProperty *repp = (*it);
					if(repp->asPObject(parent)){
						new PObjectListViewItem(this,repp,property);
					} else {
						new PropertyItem(this,repp,property);
					}
				}
			}
        //}
	
	}
}


QString PObjectListViewItem::text( int column ) const
{
    return QString(rp->getName().c_str()).append(": ").append(rp->asString( parent ).c_str());
}

RepositoryProperty* PObjectListViewItem::getRepositoryProperty()
{
	return rp;
}



/*!
    \fn PObjectListViewItem::getParent()
 */
PObject* PObjectListViewItem::getParent()
{
    return parent;
}
