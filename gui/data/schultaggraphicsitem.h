//
// C++ Interface: schultagGraphicsitem
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef SCHULTAGGraphicsITEM_H
#define SCHULTAGGraphicsITEM_H

#include "pobjectgraphicsitem.h"

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class SchultagGraphicsItem : public PObjectGraphicsItem {

public:
    SchultagGraphicsItem();
    SchultagGraphicsItem(QGraphicsScene *sc);
    SchultagGraphicsItem(PObject *o, QGraphicsScene *sc);
    ~SchultagGraphicsItem();

protected:
	void resetSize();
	QColor getFirstColor();
	 QColor getSecondColor();
};

#endif
