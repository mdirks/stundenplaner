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
#include "objectitem.h"

int ObjectItem::Rtti = 1002;


ObjectItem::ObjectItem(PObject *o, QListWidgetItem *parent)
 : QListWidgetItem()
{
    setText(o->getName().c_str());
	this->o = o;
}

ObjectItem::ObjectItem(PObject *o, QListWidgetItem *parent, QListWidgetItem *after)
 : QListWidgetItem()
{
	this->o = o;
    setText(o->getName().c_str());
}

ObjectItem::~ObjectItem()
{
}

PObject* ObjectItem::getObject()
{
	return this->o;
}

int ObjectItem::rtti() const
{
	return ObjectItem::Rtti;
}


