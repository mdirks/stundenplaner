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
#include "sitzplanmap.h"
#include "sitzplanmapmapper.h"
#include "platzgraphicsitem.h"
#include "platzgraphicsitemmapper.h"
//#include "bewertunggraphicsitem.h"

SitzplanMap::SitzplanMap() : GenericMap()
{
	setMapper(SitzplanMapmapper::getInstance());
	sp=0;
	atl=0;
	list_platzitems = new list<PlatzGraphicsItem*>();
    //list_bi = new list<BewertungGraphicsItem*>();
    listLeistungen = new list<teilleistung*>();


}


SitzplanMap::~SitzplanMap()
{
}




/*!
    \fn SitzplanMap::getSitzplan()
 */
sitzplan* SitzplanMap::getSitzplan()
{
    if(!sp){
	sp = (sitzplan*) SitzplanMapmapper::getInstance()->findReference("Sitzplan",getID());
    }
    return sp;
}


/*!
    \fn SitzplanMap::setSitzplan(sitzplan *sp)
 */
void SitzplanMap::setSitzplan(sitzplan *sp)
{
    	this->sp = sp;

	//loadSitzplan();
}


/*!
    \fn SitzplanMap::loadSitzplan()
 */
void  SitzplanMap::loadSitzplan()
{
    if(sp){
        list<platz*> *list_plaetze= sp->getPlaetze();

        list<platz*>::iterator it = list_plaetze->begin();
        int row=0;
        int col=0;
        while( it != list_plaetze->end()){

            PlatzGraphicsItem *item = PlatzGraphicsItemmapper::getInstance()->create();
            item->setPlatz(*it);
            QPoint pos;
            if(col < 4){
                pos =QPoint(105*col+10,105*row+10);
            } else {
                pos = QPoint(105*col+60,105*row+10);
            }
            addGraphicsItem(item,pos);
            if(col==8){ row++; col=-1;}
            col++;
            it++;
        }
    } else {
	qDebug("SitzplanMap : no sitzplan set -- cannot load");
    }
}


void SitzplanMap::readInfoForPlatz(platz *pl)
{
    QStringList info;
    QString noten;
    for(list<teilleistung*>::iterator it = listLeistungen->begin(); it != listLeistungen->end(); it++){
        teilleistung *tl = (*it);
        schueler *s = pl->getSchueler();
        noten=noten.append(QString("%1 ").arg(tl->getNote(s)->getPunkte()));
    }
    info << noten;
    mapInfo[pl]=info;
}



QStringList SitzplanMap::getInfoForPlatz(platz *pl)
{
    QStringList info = mapInfo[pl];
    if(info.isEmpty()){
        readInfoForPlatz(pl);
        info=mapInfo[pl];
    }
    return info;
}



void SitzplanMap::setDisplay(list<teilleistung*> *listDisplay)
{
    listLeistungen = listDisplay;
    mapInfo.clear();
}

void SitzplanMap::addPlatzItem(platz* pl, QPoint pos)
{
	PlatzGraphicsItem *item = PlatzGraphicsItemmapper::getInstance()->create();
	item->setPlatz(pl);
	list_platzitems->push_back(item);
	addGraphicsItem(item,pos);
	qDebug("SitzplanMap: Added item for platz");
}

PlatzGraphicsItem *SitzplanMap::findItem(platz *pl)
{
	PlatzGraphicsItem *result = 0;
	list<PlatzGraphicsItem*>::iterator it = list_platzitems->begin();
	while(result == 0){
		PlatzGraphicsItem *i = *it;
		if(i->getPlatz() == pl){
			result = i;
		}
	}
	return result;
}

/*!
    \fn SitzplanMap::addBewertungsItem(platz *p, note *n)
 */
void SitzplanMap::addBewertungsItem(platz *p, note *n)
{
    /*
    PlatzGraphicsItem *pitem = findItem(p);
    if(pitem){
	QPoint pos = (pitem->rect()).topLeft();
	BewertungGraphicsItem *bitem = new BewertungGraphicsItem(n, this, pos);
	list_bi->push_back(bitem);
	displayItem(bitem);
    } else {
	qDebug("SitzplanMap::addBewertungsItem: Could not find item for Platz");
    }
    */
    qDebug() << "SitzplanMap::addBewertungsItem not yet implemented";
}


/*!
    \fn SitzplanMap::addFehlzeitItem(platz *p, fehlzeit *f)
 */
void SitzplanMap::addFehlzeitItem(platz *p, fehlzeit *f)
{
    /// @todo implement me
}


/*!
    \fn SitzplanMap::setActiveTeilleistung(teilleistung *tl)
 */
void SitzplanMap::setActiveTeilleistung(teilleistung *tl)
{
    this->atl = tl;
}


/*!
    \fn SitzplanMap::getActiveTeilleistung()
 */
teilleistung* SitzplanMap::getActiveTeilleistung()
{
    if(!atl){
	atl = (teilleistung*) SitzplanMapmapper::getInstance()->findReference("ActiveTeilleistung",getID());
    }
    return atl;
}
