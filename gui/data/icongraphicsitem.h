//
// C++ Interface: iconGraphicsitem
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef ICONGraphicsITEM_H
#define ICONGraphicsITEM_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QString>
#include <QPaintEvent>
/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class IconGraphicsItem : public QGraphicsRectItem
{
public:
    IconGraphicsItem(qreal x, qreal y, qreal dx, qreal dy, QString t, QString in, QGraphicsScene *sc);
    ~IconGraphicsItem();

private:
	QString text, iconName;
	QPixmap icon;
public:
    virtual void paint ( QPainter * painter ,
                         const QStyleOptionGraphicsItem * option,
                         QWidget * widget = 0 );

protected:
  //  virtual void paintEvent(QPaintEvent *e);
};

#endif
