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
#include "rootitem.h"

#include "orm/repository/repository.h"
#include "gui/base/guiconfig.h"
#include "pobjectlistviewitem.h"
#include "propertyitem.h"

RootItem::RootItem(QListWidget *parent, PObject *mo)
 : QListWidgetItem()
{
	this->mo = mo;
	this->entry = Repository::getInstance()->getRepositoryEntry(mo);
    // todo : setPixmap(0,GuiConfig::getInstance()->getIcon(mo));
}


QString RootItem::text( int column ) const
{
    return QString(entry->getClassName().c_str()).append(": ").append(mo->getName().c_str());
}

RootItem::~RootItem()
{
}


void RootItem::activate()
{
    //if(!isOpen()){
		if(entry){
			list<RepositoryProperty*> *properties = entry->getAllProperties();
			if(properties){
				for(list<RepositoryProperty*>::iterator it=properties->begin(); it != properties->end(); it++){
					RepositoryProperty *prop = (*it);
					if(prop->asPObject( mo )){
							new PObjectListViewItem(this,prop, mo);
					} else 
							new PropertyItem(this, prop, mo);
				}
				
			}
		}
	
    //}
}
