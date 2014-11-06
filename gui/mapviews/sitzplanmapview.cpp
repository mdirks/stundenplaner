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
#include "sitzplanmapview.h"

#include <qwmatrix.h>

SitzplanMapView::SitzplanMapView(QWidget * parent, const char * name)
	: GenericMapView(parent,name)
{
    //QWMatrix wm = worldMatrix(); // set to convenient initial size
    //wm.scale(.7,.7);
    //setWorldMatrix(wm);
}


SitzplanMapView::~SitzplanMapView()
{
}




/*!
    \fn SitzplanMapView::setStundenplaneintrag(stundenplaneintrag *se)
 */
void SitzplanMapView::setStundenplaneintrag(stundenplaneintrag *se)
{
    this->se = se;
}


/*!
    \fn SitzplanMapView::getStundenplaneintrag()
 */
stundenplaneintrag* SitzplanMapView::getStundenplaneintrag()
{
    return this->se;
}

sitzplan* SitzplanMapView::getSitzplan()
{
	sitzplan *result=0;

    QGraphicsScene *c = scene();
	if(SitzplanMap *sm = dynamic_cast<SitzplanMap*>(c)){
		result = sm->getSitzplan();		
	}
	return result;
}


/*!
    \fn SitzplanMapView::getSitzplanMap()
 */
SitzplanMap* SitzplanMapView::getSitzplanMap()
{
    QGraphicsScene *c = scene();
    return dynamic_cast<SitzplanMap*>(c);
}
