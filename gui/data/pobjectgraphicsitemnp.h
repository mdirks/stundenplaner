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
#ifndef POBJECTGraphicsITEMNP_H
#define POBJECTGraphicsITEMNP_H


#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QPixmap>
#include <QColor>

#include "orm/repository/repositoryproperty.h"
#include "orm/persistence/pobject.h"
#include "orm/transactions/transactionobject.h"

/**
@author Marcus Dirks
*/
class PObjectGraphicsItemNP : public QGraphicsRectItem /*public QGraphicsText*/
{
public:
    PObjectGraphicsItemNP();
    PObjectGraphicsItemNP(QGraphicsScene *scene);
    PObjectGraphicsItemNP(PObject *o, QGraphicsScene *scene, RepositoryProperty *dispProp=0);
    ~PObjectGraphicsItemNP();
    
    virtual void setObject(PObject *o);
    virtual PObject* getObject();
    int rtti() const;
    void init();
    double x();
    double y();
    int width();
    int height();
    int getColor();
    void setColor(int i);
    void  setX(qreal x);
    void  setY(qreal y);

    void  setWidth(int w);
    void setHeight(int h);
    double z();
    virtual void update();
    
    const int RTTI;
    
    virtual void paint ( QPainter  *painter,
                         const QStyleOptionGraphicsItem * option,
                         QWidget *w );
protected:
    virtual void resetSize();
	virtual QColor getFirstColor();
	virtual QColor getSecondColor();

protected:
    PObject *o;
    QPixmap icon;
    int n_color;
    RepositoryProperty *m_dispProp;
    QGraphicsItem *m_dispItem;
};



#endif
