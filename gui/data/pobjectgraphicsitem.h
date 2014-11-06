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
#ifndef POBJECTGraphicsITEM_H
#define POBJECTGraphicsITEM_H

#include <QGraphicsScene>
#include <qpixmap.h>
#include <qcolor.h>

#include "orm/persistence/pobject.h"
#include "pobjectgraphicsitemnp.h"
#include "orm/transactions/transactionobject.h"

/**
@author Marcus Dirks
*/
class PObjectGraphicsItem : public PObjectGraphicsItemNP, public TransactionObject
{
public:
    PObjectGraphicsItem();
    PObjectGraphicsItem(QGraphicsScene *scene);
    PObjectGraphicsItem(PObject *o, QGraphicsScene *scene);
    ~PObjectGraphicsItem();
    
    virtual void setObject(PObject *o){PObjectGraphicsItemNP::setObject(o);};
    virtual PObject* getObject();
    virtual void update();
    /*
    int rtti() const;
    void init();
    double x();
    double y();
    int width();
    int height();
    int getColor();
    void setColor(int i);
    void  setWidth(int w);
    void setHeight(int h);
    
    const int RTTI;
    */
    virtual void paint ( QPainter  *painter,
                        const QStyleOptionGraphicsItem * option,
                        QWidget *w )
    {PObjectGraphicsItemNP::paint(painter,option,w);}

protected:

	/*
	void draw ( QPainter & painter );
	virtual void resetSize();
	virtual QColor getFirstColor();
	virtual QColor getSecondColor();
	*/

protected:
    //PObject *o;
    //QPixmap icon;
    //int n_color;

public:
    virtual void resetSize();
};

#endif
