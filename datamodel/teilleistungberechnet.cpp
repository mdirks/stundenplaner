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
#include "teilleistungberechnet.h"
#include "teilleistungberechnetmapper.h"
#include "schueler.h"
#include "note.h"
#include "orm/transactions/transactions.h"

teilleistungberechnet::teilleistungberechnet()
 : teilleistung()
{
	setMapper(teilleistungberechnetmapper::getInstance());
	list_teilleistungen=0;
	is_init=false;
}


teilleistungberechnet::~teilleistungberechnet()
{
}




/*!
    \fn teilleistungberechnet::getTeilleistungen()
 */
list<teilleistung*>* teilleistungberechnet::getTeilleistungen()
{
    if(!list_teilleistungen){
	list_teilleistungen = teilleistungberechnetmapper::getInstance()->findTeilleistungen(getID());
    }
    return list_teilleistungen;
}


/*!
    \fn teilleistungberechnet::addToTeilleistungen(teilleistung *tl)
 */
void teilleistungberechnet::addToTeilleistungen(teilleistung *tl)
{
    getTeilleistungen()->push_back(tl);
    berechne();
}


/*!
    \fn teilleistungberechnet::removeFromTeilleistungen(teilleistungen *tl)
 */
void teilleistungberechnet::deleteFromTeilleistungen(teilleistung *tl)
{
    getTeilleistungen()->remove(tl);
}

void teilleistungberechnet::berechne()
{
	int num = getTeilleistungen()->size();
	if(num != 0){
		for(list<note*>::iterator it=getNoten()->begin(); it != getNoten()->end(); it++){
			double punkte=0.0;
			note *n = (*it);
			schueler *s= n->getSchueler();
			for(list<teilleistung*>::iterator itt=getTeilleistungen()->begin(); itt != getTeilleistungen()->end(); itt++){
				teilleistung *tl = (*itt);
				note *nn = tl->getNote(s);
				if(nn){
					punkte += nn->getPunkte();
				}
			}
			punkte=punkte/num;
			n->setPunkte(punkte);
			if((punkte-n->getPunkte()) >= .5){
				n->setPunkte(n->getPunkte()+1);
			} else if((punkte-n->getPunkte()) < -.5){
				n->setPunkte(n->getPunkte()-1);
			}
			Transactions::getCurrentTransaction()->add(n);
		}
	} else {
		qDebug("WARNING: Berechnung failed: keine Teilleistungen");
	}
}
