//
// C++ Interface: %{MODULE}
//
// Description: 
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef GENERICMAP_H
#define GENERICMAP_H

#include <list>

#include <QGraphicsScene>
#include <QPoint>

#include "themaitem.h"
#include "pobjectgraphicsitem.h"
#include "datamodel/thema.h"
#include "pobjectgraphicsitemnp.h"
#include "orm/persistence/pobject.h"
#include "orm/transactions/transactionobject.h"

using namespace std;

/** This is a generic Map-Layout based on QGraphics

	PObject Items can be added  at given positions. The Collection of all contained items is persisted.

@author Marcus Dirks
*/
class GenericMap : public QGraphicsScene, public TransactionObject
{
public:
    GenericMap();
    GenericMap(int x, int y);
    ~GenericMap();

    
    static QGraphicsScene* getDummyScene();
    
    list<PObjectGraphicsItem*> *getGraphicsItems();
    void addGraphicsItem(PObjectGraphicsItem *item);


    
    /**
     *  Adds an item for the given object at the given position
     * @param o object to be added
     * @param pos where to add
     */
    void addItem(PObject *o,const QPointF &pos, int z=0);
    PObjectGraphicsItemNP* addItemNP(PObject *o,const QPointF &pos, int z=0);
    void addToGraphicsItems(PObjectGraphicsItem *item);
    void deleteFromGraphicsItems(PObjectGraphicsItem *item);
	void setName(string name);

    void displayMap();
    
    //void init();
   
    
protected:
    void addGraphicsItem(PObjectGraphicsItem *item, const QPointF &pos);
    void addGraphicsItemNP(PObjectGraphicsItemNP* item,const QPointF &pos, int z);
    
private:
   static  QGraphicsScene *dummy;
   list<PObjectGraphicsItem*> *list_items;
protected:
    void displayItem(QGraphicsItem *item);
    
    
    

};

#endif
