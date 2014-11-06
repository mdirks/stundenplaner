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
#include "weekmapviewcontroler.h"
#include "gui/data/weekmap.h"
#include "services/sstundenplan.h"
#include "gui/forms/pobjecttable.h"
#include "services/reports/latexoutput.h"

#include <kfiledialog.h>
#include <QDebug>

WeekMapViewControler::WeekMapViewControler(WeekMapView *mapView)
	: GenericMapViewControler(mapView)
{
	this->mapView = mapView;
	
}


WeekMapViewControler::~WeekMapViewControler()
{
}

void WeekMapViewControler::readStundenplan()
{
	WeekMap *wm = dynamic_cast<WeekMap*>(mapView->getMap());
	if(wm){
		wm->readStundenplan();
		mapView->update();
	}
}

list<fehlzeit*>* WeekMapViewControler::collectFehlzeiten()
{
	

	stundenplaneintrag *selected_eintrag=0;
 	if(PObjectGraphicsItemNP *selectedItem= mapView->getSelected()){
		if(PObject *o = selectedItem->getObject()){
			selected_eintrag = dynamic_cast<stundenplaneintrag*>(o);
		}
	}

	list<fehlzeit*> *list_fehlzeiten=0;
	if(selected_eintrag){
		list_fehlzeiten = selected_eintrag->getFehlzeiten();
	} else {
		WeekMap *wm = dynamic_cast<WeekMap*>(mapView->getMap());
		if(wm){
			list_fehlzeiten = new list<fehlzeit*>();
			list<stundenplaneintrag*> *list_e = SStundenplan::getInstance()->getEintraegeForWeek(wm->getStartDate());
            qDebug() << QString("WeekMapViewControler::showFehlzeiten : got %1 eintraege").arg(list_e->size());
			for(list<stundenplaneintrag*>::iterator it = list_e->begin(); it != list_e->end(); it++){
				list<fehlzeit*> *list_f = (*it)->getFehlzeiten();
                qDebug() << QString("WeekMapViewControler::showFehlzeiten : got %1 fehlzeiten").arg(list_f->size());
				for(list<fehlzeit*>::iterator itt= list_f->begin(); itt != list_f->end(); itt++){
					list_fehlzeiten->push_back(*itt);
				}
			}
		} else {
            qDebug() << "WeekMapViewControler::showFehlzeiten : Could not get weekmap";
		}
	}
	return list_fehlzeiten;
}


void WeekMapViewControler::showFehlzeiten()
{
	PObjectTableDialog::edit((list<PObject*>*) collectFehlzeiten(),"fehlzeit");

	
}

void WeekMapViewControler::writeFehlzeiten()
{
	list<fehlzeit*> *l_f = collectFehlzeiten();
	QString fileName = KFileDialog::getSaveFileName();

	LatexOutput *lout = new LatexOutput(QString("Testoutput"),fileName);
	if(lout){
		lout -> write(l_f);
		lout -> close();
		lout -> edit();
	}	

	delete lout;
}
/*!
    \fn WeekMapViewControler::getPopupMenu()
 */
QMenu* WeekMapViewControler::getPopupMenu()
{
    QMenu *pmenu = GenericMapViewControler::getPopupMenu();

    pmenu->addAction("Stundenplan", this,SLOT(readStundenplan()));
    pmenu->addAction("Fehlzeiten", this,SLOT(showFehlzeiten()));
    pmenu->addAction("Fehlzeiten (Latex)", this,SLOT(writeFehlzeiten()));

	return pmenu;
}
