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
#include "platzgraphicsitem.h"
#include "platzgraphicsitemmapper.h"
#include "gui/base/guiconfig.h"

#include <qpainter.h>

#define WIDTH 80
#define HEIGHT 80

PlatzGraphicsItem::PlatzGraphicsItem() : PObjectGraphicsItem()
{
	setMapper(PlatzGraphicsItemmapper::getInstance());
	pl = 0;
}

PlatzGraphicsItem::PlatzGraphicsItem(QGraphicsScene *c) : PObjectGraphicsItem(c)
{
	setMapper(PlatzGraphicsItemmapper::getInstance());
	pl = 0;
}

PlatzGraphicsItem::PlatzGraphicsItem(platz *pl, QGraphicsScene *sc) : PObjectGraphicsItem(pl,sc)
{
	setMapper(PlatzGraphicsItemmapper::getInstance());
	this->pl = pl;
	if(pl){
		if(schueler *s = pl->getSchueler()){
			this->icon = GuiConfig::getInstance()->getIcon( s);
		}
	}
	qDebug("Creation with PlatzGraphicsItem consturctor");
}

void PlatzGraphicsItem::resetSize()
{
    prepareGeometryChange();
    this->setRect(0,0,WIDTH,HEIGHT);
}


void PlatzGraphicsItem::setPlatz(platz *pl)
{
	setObject(pl);
}

void PlatzGraphicsItem::setObject(PObject *o)
{
	this->pl = dynamic_cast<platz*>(o);
	this->o = o;
	update();	
}

platz* PlatzGraphicsItem::getPlatz()
{
	return dynamic_cast<platz*>(getObject());
}

void PlatzGraphicsItem::paint ( QPainter  *painter,
                                const QStyleOptionGraphicsItem * option,
                                QWidget *w )
{
    QGraphicsRectItem::paint(painter,option,w);

    if(isSelected()){
		setBrush(getFirstColor());
	} else {
		setBrush(getSecondColor());
	}
    //drawShape(painter);
    //QGraphicsRectangle::draw(painter);
	
    painter->setPen( Qt::black );

    painter->drawPixmap(2,2,icon.scaled(20,20));
	schueler *s=0;
    if(getPlatz() &&  (s= getPlatz()->getSchueler())){
        painter->drawText(22,20,s->getVorname().c_str());
    }  else {
        painter->drawText(22,20,"Empty");
	}
	

}

/*!
    \fn PlatzGraphicsItem::update()
 */
void PlatzGraphicsItem::update()
{
    if(pl){
		if(schueler *s = pl->getSchueler()){
			this->icon = GuiConfig::getInstance()->getIcon( s);
		}
	}
	this->resetSize();/// @todo implement me
    QGraphicsRectItem::update(rect());
}
