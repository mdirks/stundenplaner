//
// C++ Implementation: schultagGraphicsitem
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "schultagGraphicsitem.h"
#include "schultagGraphicsitemmapper.h"

SchultagGraphicsItem::SchultagGraphicsItem() : PObjectGraphicsItem()
{
	setMapper(SchultagGraphicsItemmapper::getInstance());
}
SchultagGraphicsItem::SchultagGraphicsItem(QGraphics *Graphics): PObjectGraphicsItem(Graphics)
{
	setMapper(SchultagGraphicsItemmapper::getInstance());
}

SchultagGraphicsItem::SchultagGraphicsItem(PObject *o, QGraphics *Graphics): PObjectGraphicsItem(o,Graphics)
{
	setMapper(SchultagGraphicsItemmapper::getInstance());
}

SchultagGraphicsItem::~SchultagGraphicsItem()
{
}


void SchultagGraphicsItem::resetSize()
{
	this->setSize(icon.width()+4+170,icon.height()+4+300);
}


QColor SchultagGraphicsItem::getFirstColor(){
	return getSecondColor();
}

QColor SchultagGraphicsItem::getSecondColor(){
	return QColor(230,203,175);
}