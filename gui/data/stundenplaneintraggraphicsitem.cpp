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
#include "stundenplaneintraggraphicsitem.h"
#include "stundenplaneintraggraphicsitemmapper.h"

#include <QPainter>


StundenplaneintragGraphicsItem::StundenplaneintragGraphicsItem(stundenplaneintrag *se, QGraphicsScene *sc)
    : PObjectGraphicsItem(se,sc)
{
	setMapper(StundenplaneintragGraphicsItemmapper::getInstance());
	this->se = se;
}


StundenplaneintragGraphicsItem::~StundenplaneintragGraphicsItem()
{
}

void StundenplaneintragGraphicsItem::paint ( QPainter  *painter,
                                             const QStyleOptionGraphicsItem * option,
                                             QWidget *w )
{
    PObjectGraphicsItemNP::paint(painter,option,w);
	if(se){
        if(se->getKursbuchEintrag() == 0 || se->getKursbuchEintrag()->getEintrag() == ""){
            painter->setBrush( Qt::red );
            painter->drawRoundRect(width()-height()*.2,0,height()*.2,height()*.2);
		} 
	} else {
            painter->setBrush( Qt::red );
            painter->drawRoundRect(0,0,height()*.2,height()*.2);
	}
}


/*!
    \fn StundenplaneintragGraphicsItem::setStundenplaneintrag(stundenplaneintrag *se)
 */
void StundenplaneintragGraphicsItem::setStundenplaneintrag(stundenplaneintrag *se)
{
    this->se =se;
    PObjectGraphicsItem::setObject(se);
}
