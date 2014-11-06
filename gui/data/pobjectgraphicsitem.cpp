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
#include "pobjectgraphicsitem.h"
#include "pobjectgraphicsitemmapper.h"
#include "themamap.h"
#include "gui/base/guiconfig.h"

#include <qpainter.h>
#include <qbrush.h>

PObjectGraphicsItem::PObjectGraphicsItem()
 : PObjectGraphicsItemNP(), TransactionObject()
{
	setMapper(PObjectGraphicsItemmapper::getInstance());
}

PObjectGraphicsItem::PObjectGraphicsItem(QGraphicsScene *sc)
 : PObjectGraphicsItemNP(sc), TransactionObject()
{
	setMapper(PObjectGraphicsItemmapper::getInstance());
        
}

PObjectGraphicsItem::PObjectGraphicsItem(PObject *o, QGraphicsScene *sc)
 : PObjectGraphicsItemNP(o,sc), TransactionObject()
{
	setMapper(PObjectGraphicsItemmapper::getInstance());
}


PObjectGraphicsItem::~PObjectGraphicsItem(){}

/*
void PObjectGraphicsItem::setObject(PObject *o)
{
	if(!o) qDebug("PObjectGraphicsItem::setObject : WARNING : setting null object");
	this->o = o;
	this->icon = GuiConfig::getInstance()->getIcon( o);
	resetSize();
	//this->setSize(icon.width()+4+150,icon.height()+4);
}
*/

PObject* PObjectGraphicsItem::getObject()
{
	PObject *o = PObjectGraphicsItemNP::getObject();
	if(o==0){
		o= (PObject*) PObjectGraphicsItemmapper::getInstance()->findReference("Object",getID());
		this->icon = GuiConfig::getInstance()->getIcon( o);
		resetSize();
		setObject(o);
	} 

	return o;
}

/*
void PObjectGraphicsItem::resetSize()
{
	this->setSize(icon.width()+4+150,icon.height()+4);
}
*/


/*!
    \fn PObjectGraphicsItem::rtti() const
 */
/*
int PObjectGraphicsItem::rtti() const
{
    return RTTI;
 }
*/

/*!
    \fn PObjectGraphicsItem::init()
 */
/*
void PObjectGraphicsItem::init()
{
   
    
}
*/


/*!
    \fn PObjectGraphicsItem::x()
 */
/*
double PObjectGraphicsItem::x()
{
    return QGraphicsItem::x();
}
*/

/*!
    \fn PObjectGraphicsItem::y()
 */
/*
double PObjectGraphicsItem::y()
{
    return QGraphicsItem::y();
}

int  PObjectGraphicsItem::width()
{
    return QGraphicsRectangle::width();
}

int  PObjectGraphicsItem::getColor()
{
    return n_color;
}

void PObjectGraphicsItem::setColor(int c)
{
    n_color = c;
}


int  PObjectGraphicsItem::height()
{
    return QGraphicsRectangle::height();
}

void  PObjectGraphicsItem::setWidth(int w)
{
    return QGraphicsRectangle::setSize(w, height());
}

void PObjectGraphicsItem::setHeight(int h)
{
    return QGraphicsRectangle::setSize(width(),h);
}


void PObjectGraphicsItem::draw ( QPainter & painter )
{
	if(isSelected()){
		setBrush(getFirstColor());
	} else {
		setBrush(getSecondColor());
	}
	drawShape(painter);
	QGraphicsRectangle::draw(painter);
	
	painter.setPen( Qt::black );

	painter.drawPixmap(x()+2,y()+2,icon);
	if(PObject *o = getObject()){
		QString name(o->getName());
		painter.drawText(x()+2+icon.width(),y()+5+icon.height()/2,name);
	} else {
		painter.drawText(x()+2+icon.width(),y()+2,"Empty");
	}
	

}

QColor PObjectGraphicsItem::getFirstColor(){
	return QColor(130,130,130);
}

QColor PObjectGraphicsItem::getSecondColor(){
	return QColor(200,200,200);
}
*/

/*!
    \fn PObjectGraphicsItem::resetSize()
 */
void PObjectGraphicsItem::resetSize()
{
    PObjectGraphicsItemNP::resetSize();
}


/*!
    \fn PObjectGraphicsItem::update()
 */
void PObjectGraphicsItem::update()
{
    PObjectGraphicsItemNP::update();
}
