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
#ifndef SITZPLANMAP_H
#define SITZPLANMAP_H

#include "genericmap.h"
#include "pobjectgraphicsitem.h"
#include "platzgraphicsitem.h"
//#include "bewertunggraphicsitem.h"
#include "datamodel/sitzplan.h"
#include "datamodel/platz.h"

#include <list>

/**
	@author Marcus Dirks <m-dirks@web.de>
*/
class SitzplanMap : public GenericMap {
public:
    SitzplanMap();
     	~SitzplanMap();
    	sitzplan* getSitzplan();
    	void setSitzplan(sitzplan *sp);
	void  loadSitzplan();

	void addPlatzItem(platz* pl, QPoint pos);
    void addFehlzeitItem(platz *p, fehlzeit *f);
    void addBewertungsItem(platz *p, note *n);
    teilleistung* getActiveTeilleistung();
    void setActiveTeilleistung(teilleistung *tl);
	 
private:
	PlatzGraphicsItem *findItem(platz *pl);


private:
    
    sitzplan *sp;
    teilleistung *atl;
    list<PlatzGraphicsItem*> *list_platzitems;
//    list<BewertungGraphicsItem*> *list_bi;

};



#endif
