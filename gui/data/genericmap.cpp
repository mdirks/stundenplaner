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
#include "genericmap.h"
#include "pobjectgraphicsitem.h"
#include "pobjectgraphicsitemmapper.h"
#include "stundenplaneintraggraphicsitem.h"
#include "datamodel/stundenplaneintrag.h"
#include "genericmapmapper.h"

QGraphicsScene* GenericMap::dummy = 0;


GenericMap::GenericMap() : QGraphicsScene()
{
	list_items=0;
	setMapper(GenericMapmapper::getInstance());
}

GenericMap::GenericMap(int x, int y)
 : QGraphicsScene(0,0,x,y)
{
	list_items=0;
	setMapper(GenericMapmapper::getInstance());
}


GenericMap::~GenericMap()
{
}


QGraphicsScene* GenericMap::getDummyScene()
{
   if(dummy==0){
    dummy = new QGraphicsScene();
    }
    return dummy;
}


/*!  Property GraphicsItems (association)
    \fn GenericMap::getThemaItems()
 */
list<PObjectGraphicsItem*>* GenericMap::getGraphicsItems()
{
    if(list_items==0){
    	//list_items = (list<PObjectGraphicsItem*>*) GenericMapmapper::getInstance()->findAssociates("GraphicsItems", getID());
    	list_items = GenericMapmapper::getInstance()->findGraphicsItems( getID() );
    }
    return list_items;
}



/*! Adder for the property GraphicsItems
    \fn GenericMap::addToGraphicsItems(PObjectGraphicsItem *item)
 */
void GenericMap::addToGraphicsItems(PObjectGraphicsItem *item)
{
   getGraphicsItems()->push_back(item);
}


/*! Deleter for the property GraphicsItems 
    \fn GenericMap::deleteFromGraphicsItems(PObjectGraphicsItems *item)
 */
void GenericMap::deleteFromGraphicsItems(PObjectGraphicsItem *item)
{
     getGraphicsItems()->remove(item);
    qDebug("GenericMap::deleteFromGraphicsItems() : removed item");
}












void GenericMap::addGraphicsItem(PObjectGraphicsItem *item){
	addGraphicsItem(item,QPoint(item->x(),item->y()));
}




/*!
    \fn GenericMap::addItem(PObject *o,const QPoint &pos)
 */
void GenericMap::addItem(PObject *o,const QPointF &pos, int z)
{
    if(!o){
    qDebug() << "Warning: GenericMap adding null object";
    } else {
    qDebug() << "GenerciMap adding item";
	}
    PObjectGraphicsItem *item = (PObjectGraphicsItem*) PObjectGraphicsItemmapper::getInstance()->create();
    item->setObject(o);
    item->setZValue(z);

    addGraphicsItem(item,pos);
    
    item->save();
}

PObjectGraphicsItemNP* GenericMap::addItemNP(PObject *o,const QPointF &pos, int z)
{
	PObjectGraphicsItemNP *item=0;
        if(stundenplaneintrag *se = dynamic_cast<stundenplaneintrag*>(o)){
		item = new StundenplaneintragGraphicsItem(se,0);
	} else {
		item = new PObjectGraphicsItemNP();
	}
	item->setObject(o);
	addGraphicsItemNP(item,pos,z);
	return item;
}

void GenericMap::addGraphicsItemNP(PObjectGraphicsItemNP* item,const QPointF &pos, int z)
{
    //item->setObject(o);
    item->setZValue(z);
    item->setPos(QPointF(0,0));
    item->moveBy(pos.x(),pos.y());

    //item->setGraphics(this);
    QGraphicsScene::addItem(item);
    item->show();
    update();
    
    
}

void GenericMap::addGraphicsItem(PObjectGraphicsItem *item, const QPointF &pos)
{
    
    item->setPos(QPointF(0,0));
    item->moveBy(pos.x(),pos.y());
    
	addToGraphicsItems(item);
    displayItem(item);
}


/*!
    \fn GenericMap::displayItem(PObjectItem *item)
 */
void GenericMap::displayItem(QGraphicsItem *item)
{
    //item->setGraphics(this);
    
   QGraphicsScene::addItem(item);
    
    item->show();
    update();
    qDebug() << "GenericMap::displayItem";
}


/*!
    \fn GenericMap::displayMap()
 */
void GenericMap::displayMap()
{
      list<PObjectGraphicsItem*> *items = getGraphicsItems();
      qDebug() << QString(">>>>GenericMap: displaying %1 items").arg(items->size());
      for(list<PObjectGraphicsItem*>::iterator it=items->begin(); it!=items->end(); it++)
      {
	   displayItem(*it);
	}
	update();
}




/*!
    \fn GenericMap::setName(string name)
 */
void GenericMap::setName(string name)
{
    PObject::setName(name);
    //QObject::setName(name);
}



