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
#include "schultaggraphicsitem.h"
#include "schultaggraphicsitemmapper.h"

SchultagGraphicsItem::SchultagGraphicsItem() : PObjectGraphicsItem()
{
	setMapper(SchultagGraphicsItemmapper::getInstance());
}
SchultagGraphicsItem::SchultagGraphicsItem(QGraphicsScene *sc): PObjectGraphicsItem(sc)
{
	setMapper(SchultagGraphicsItemmapper::getInstance());
}

SchultagGraphicsItem::SchultagGraphicsItem(PObject *o, QGraphicsScene *sc): PObjectGraphicsItem(o,sc)
{
	setMapper(SchultagGraphicsItemmapper::getInstance());
}

SchultagGraphicsItem::~SchultagGraphicsItem()
{
}


void SchultagGraphicsItem::resetSize()
{
    this->setRect(x(),y(),icon.width()+4+170,icon.height()+4+300);
}


QColor SchultagGraphicsItem::getFirstColor(){
	return getSecondColor();
}

QColor SchultagGraphicsItem::getSecondColor(){
	return QColor(230,203,175);
}
