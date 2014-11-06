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
#include "teilleistung.h"
#include "teilleistungmapper.h"

teilleistung::teilleistung()
{
	list_noten=0;
	kl =0;
	setMapper(teilleistungmapper::getInstance());
}


teilleistung::~teilleistung()
{
}


/*!
    \fn teilleistung::getNoten()
 */
list<note*>* teilleistung::getNoten()
{
    if(list_noten == 0){
	list_noten = teilleistungmapper::getInstance()->findNoten(getID());
    }
    return list_noten;
}


/*!
    \fn teilleistung::addToNoten(note *)
 */
void teilleistung::addToNoten(note *n)
{
    getNoten()->push_back(n);
}


/*!
    \fn teilleistung::deleteFromNoten(note *n)
 */
void teilleistung::deleteFromNoten(note *n)
{
    getNoten()->remove(n);
}


/*!
    \fn teilleistung::getKlasse()
 */
klasse* teilleistung::getKlasse()
{
	if(kl==0){
		kl = (klasse*) teilleistungmapper::getInstance()->findReference("Klasse",getID());
	}
	return kl;
}


/*!
    \fn teilleistung::setKlasse(klasse *kl)
 */
void teilleistung::setKlasse(klasse *kl)
{
    this->kl = kl;
}



/*!
    \fn teilleistung::getNote(schueler *s)
 */
note* teilleistung::getNote(schueler *s)
{
	note* result = 0;
	list<note*>::iterator it = getNoten()->begin();
	while(!result && it!= getNoten()->end())
	{
		if((*it)->getSchueler() == s) result = (*it);
		it++;
	}
	if(!result) qDebug("Could not find note for schueler");
	return result;
}


/*!
    \fn teilleistung::getDurchschnitt()
 */
double teilleistung::getDurchschnitt()
{
	double sum=0.0;
	for(list<note*>::iterator it = getNoten()->begin(); it!=getNoten()->end();it++)
	{
		sum += (*it)->getPunkte();
	}
	return sum/getNoten()->size();
}

int teilleistung::getAnzahl(int punkte)
{
	int anzahl=0;
	for(list<note*>::iterator it = getNoten()->begin(); it!=getNoten()->end();it++)
	{
		if((*it)->getPunkte()==punkte) anzahl+=1;
	}
	return anzahl;
}

int teilleistung::getAnzahlNote(int note)
{
	int anzahl=0;
	if(note == 6){
		anzahl = getAnzahl(0);
	} else {
		int punkte=15-(note-1)*3;
		anzahl=anzahl+getAnzahl(punkte)+getAnzahl(punkte-1)+getAnzahl(punkte-2);
	}
	return anzahl;
}


