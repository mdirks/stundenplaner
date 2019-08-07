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
#include "typeitem.h"

#include <list>
#include <qpixmap.h>

#include "newobjectitem.h"
#include "objectitem.h"
#include "orm/persistence/pobject.h"
#include "gui/base/guiconfig.h"

TypeItem::TypeItem(AbstractMapper *mapper, QListView *parent)
 : QListViewItem(parent)
{
	this->mapper = mapper;
	setText(0,mapper->getClassName());
	setPixmap(0, GuiConfig::getInstance()->getIcon(mapper->getClassName()));
}


TypeItem::~TypeItem()
{
}

void TypeItem::activate()
{
	if(!isOpen()){
		new NewObjectItem(mapper, this);
	
		list<PObject*> *list_objects = mapper->find_gen();
		for(list<PObject*>::iterator it = list_objects->begin(); it!=list_objects->end(); it++){
			new ObjectItem(*it, this);
		}
	
	}
}


