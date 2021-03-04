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
#include "pobjectgraphicsitemnp.h"

#include "pobjectgraphicsitem.h"
#include "pobjectgraphicsitemmapper.h"
#include "themamap.h"
#include "gui/base/guiconfig.h"
#include "datamodel/kopie.h"

#include <qpainter.h>
#include <qbrush.h>

#define HEIGHT 30
#define WIDTH 140

PObjectGraphicsItemNP::PObjectGraphicsItemNP()
 : QGraphicsRectItem(), RTTI(1002), m_dispProp(0), m_dispItem(0)
{
	setObject(0);//o=0;
    //setColor(Qt::black);
    setFlag(QGraphicsItem::ItemIsSelectable,true);

}

PObjectGraphicsItemNP::PObjectGraphicsItemNP(QGraphicsScene *sc)
 : QGraphicsRectItem(), RTTI(1002), m_dispProp(0), m_dispItem(0)
{
	setObject(0);//o=0;
	//setColor(Qt::black);
    setFlag(QGraphicsItem::ItemIsSelectable,true);

}

PObjectGraphicsItemNP::PObjectGraphicsItemNP(PObject *o, QGraphicsScene *sc, RepositoryProperty *dispProp)
 : QGraphicsRectItem(), RTTI(1002), m_dispProp(dispProp), m_dispItem(0)
{
	setObject(o);
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    this->icon = GuiConfig::getInstance()->getIcon( o);
	resetSize();
}


PObjectGraphicsItemNP::~PObjectGraphicsItemNP(){}

void PObjectGraphicsItemNP::setObject(PObject *o)
{
    this->o=o;
    if(!o){
        qDebug("PObjectGraphicsItemNP::setObject : WARNING : setting null object");
        return;
    }

    string clName=o->getClassName();
    if(clName=="material"){ // why is kopie reported as material?
           material *k = dynamic_cast<material*>(o);
           string fn=k->getFileName();
           QPixmap pm = QPixmap(fn.c_str());
           if(!pm.isNull()){
               QGraphicsPixmapItem *pitem= new QGraphicsPixmapItem(pm,this);
               m_dispItem = pitem;
           }
    } else {
        if(!m_dispProp){
            string clName = o->getClassName();

            RepositoryEntry *re=Repository::getInstance()->getRepositoryEntry(clName);
            m_dispProp=re->getMainProperty();
        }
        if(m_dispProp && !m_dispItem){
                string dispString = m_dispProp->asString(o);
                QGraphicsTextItem *titem =  new QGraphicsTextItem(dispString.c_str(),this);
                titem->setTextWidth(WIDTH >200 ? WIDTH : 200);
                m_dispItem = titem;
        }
    }


	update();
	//this->setSize(icon.width()+4+150,icon.height()+4);
}





PObject* PObjectGraphicsItemNP::getObject()
{
	return o;
}

void PObjectGraphicsItemNP::resetSize()
{
    //qDebug() << "WARNIGN: PObjectGraphicsItemNP::resetSize() : NOT IMPLEMENTED";
    prepareGeometryChange();
    //this->setRect(x(),y(),icon.width()+4+250,icon.height()+50);


    if(m_dispItem){
        m_dispItem->setX(0);
        m_dispItem->setY(0+HEIGHT);
        this->setRect(0,0,m_dispItem->boundingRect().width(),HEIGHT+m_dispItem->boundingRect().height());
    } else {
        this->setRect(0,0,WIDTH,HEIGHT);
    }
}


/*!
    \fn PObjectGraphicsItemNP::rtti() const
 */
int PObjectGraphicsItemNP::rtti() const
{
    return RTTI;
 }


/*!
    \fn PObjectGraphicsItemNP::init()
 */
void PObjectGraphicsItemNP::init()
{
    /*
	PObject *o = getObject();
    if(o != 0)
    {
	    setText(getObject()->getName());
    } else {
    	setText("Empty");
  }
	*/
    
}


/*!
    \fn PObjectGraphicsItemNP::x()
 */
double PObjectGraphicsItemNP::x()
{
    return QGraphicsItem::x();
}


/*!
    \fn PObjectGraphicsItemNP::y()
 */
double PObjectGraphicsItemNP::y()
{
    return QGraphicsItem::y();
}

int  PObjectGraphicsItemNP::width()
{
    return QGraphicsRectItem::rect().width();
}

int  PObjectGraphicsItemNP::getColor()
{
    return n_color;
}

void PObjectGraphicsItemNP::setColor(int c)
{
    n_color = c;
}


int  PObjectGraphicsItemNP::height()
{
    return QGraphicsRectItem::rect().height();
}

void  PObjectGraphicsItemNP::setX(qreal xx)
{
    prepareGeometryChange();
    QGraphicsRectItem::setX(xx);
    resetSize();
    //QGraphicsRectItem::setRect(x(),y(),width(), height());
}

void  PObjectGraphicsItemNP::setY(qreal yy)
{
    prepareGeometryChange();
    QGraphicsRectItem::setY(yy);
    resetSize();
    //QGraphicsRectItem::setRect(x(),y(),width(), height());
}


void  PObjectGraphicsItemNP::setWidth(int w)
{
    qDebug() << "WARNING PObjectGraphicsItemNP::setWidth: TO NOTHING implementation";
    //prepareGeometryChange();
    //QGraphicsRectItem::setRect(x(),y(),w, height());
    //QGraphicsRectItem::setRect(0,0,w, height());
}

void PObjectGraphicsItemNP::setHeight(int h)
{
    qDebug() << "WARNING PObjectGraphicsItemNP::setWidth: TO NOTHING implementation";
    //prepareGeometryChange();
    //QGraphicsRectItem::setRect(x(),y(),width(),h);
    //QGraphicsRectItem::setRect(0,0,width(),h);
}


void PObjectGraphicsItemNP::paint ( QPainter  *painter,
                                    const QStyleOptionGraphicsItem * option,
                                    QWidget *w )
{
	if(isSelected()){
		setBrush(getFirstColor());
	} else {
		setBrush(getSecondColor());
	}

    QGraphicsRectItem::paint(painter,option,w);
	
    painter->setPen( Qt::black );

    painter->drawPixmap(2,2,icon.scaled(HEIGHT*0.9,HEIGHT*0.9));
	if(PObject *o = getObject()){
        QString name(o->getName().c_str());
        painter->drawText(2+HEIGHT*0.9,5+(HEIGHT*0.9)/2,name);
        //painter->drawRect(rect());
	} else {
        painter->drawText(2+icon.width(),2,"Empty");
	}
	

}

QColor PObjectGraphicsItemNP::getFirstColor(){
    return QColor(100,130,160);
}

QColor PObjectGraphicsItemNP::getSecondColor(){
	return QColor(200,200,200);
}




/*!
    \fn PObjectGraphicsItemNP::z()
 */
double PObjectGraphicsItemNP::z()
{
    return QGraphicsItem::zValue();
}


/*!
    \fn PObjectGraphicsItemNP::update()
 */
void PObjectGraphicsItemNP::update()
{
    this->icon = GuiConfig::getInstance()->getIcon( o);
    this->resetSize();

}
