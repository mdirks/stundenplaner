//
// C++ Implementation: iconGraphicsitem
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "icongraphicsitem.h"
#include "gui/base/guiconfig.h"

#include <QPainter>

IconGraphicsItem::IconGraphicsItem(qreal x, qreal y, qreal dx, qreal dy, QString t, QString in, QGraphicsScene *sc)
 : QGraphicsRectItem(0,0,dx,dy), text(t), iconName(in)
{
    moveBy(x,y);
	icon = GuiConfig::getInstance()->loadIcon(iconName);
}


IconGraphicsItem::~IconGraphicsItem()
{
}


void IconGraphicsItem::paint ( QPainter  *painter,
                               const QStyleOptionGraphicsItem * option,
                               QWidget *w )
{
    QGraphicsRectItem::paint(painter,option,w);
	
    painter->setPen( Qt::black );

    painter->drawPixmap(2,2,icon);
    painter->drawText(2+icon.width(),5+icon.height()/2,text);

}

/*
void IconGraphicsItem::paintEvent(QPaintEvent *e)
{

    QGraphicsRectItem::paintEvent(e);
    QPainter *painter = new QPainter(this);
    painter->setPen( Qt::black );

    painter->drawPixmap(x()+2,y()+2,icon);
    painter->drawText(x()+2+icon.width(),y()+5+icon.height()/2,text);
}
*/
