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
#include "newobjectitem.h"
#include "objectitem.h"

NewObjectItem::NewObjectItem(AbstractMapper *mapper, TypeItem *parent)
 : ActionItem(parent)
{
	this->mapper = mapper;
	this->parent = parent;
    setText(QString("Neu: ").append(mapper->getClassName().c_str()));
}


NewObjectItem::~NewObjectItem()
{
}

void NewObjectItem::actionPerformed()
{
	PObject *o = mapper->create();
	new ObjectItem(o,parent,this);
}
