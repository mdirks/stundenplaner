//
// C++ Implementation: sitzplan
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "sitzplan.h"
#include "sitzplanmapper.h"
#include "platzmapper.h"

#include "orm/transactions/transactions.h"

sitzplan::sitzplan()
{
	setMapper(sitzplanmapper::getInstance());
	list_plaetze = 0;
	kl=0;
	reihen=4;
	spalten=8;
}


sitzplan::~sitzplan()
{
}




/*!
    \fn sitzplan::getPlaetze()
 */
list<platz*> * sitzplan::getPlaetze()
{
	if(list_plaetze == 0){
		list_plaetze = sitzplanmapper::getInstance()->findPlaetze(getID());
	} 
	/*
	if(list_plaetze == 0){ // create if not there
		list_plaetze = new list<platz*>();
	}
	*/
	/*
	if(list_plaetze->empty()){
		int cols = getReihen();
		int rows = getSpalten();
		for(int i = 1 ; i<=rows; i++){
			for(int j=1; j<=cols; j++){
				platz *p = (platz*)platzmapper::getInstance()->create();
				p->setReihe(i);
				p->setSpalte(j);
				list_plaetze->push_back(p);
			}
		}
	}
	*/
	return list_plaetze;
}


/*!
    \fn sitzplan::addToPlaetze(platz *pl)
 */
void sitzplan::addToPlaetze(platz *pl)
{
    getPlaetze()->push_back(pl);
}


/*!
    \fn sitzplan::deleteFromPlaetze(platz *pl)
 */
void sitzplan::deleteFromPlaetze(platz *pl)
{
    getPlaetze()->remove(pl);
}


/*!
    \fn sitzplan::getKlasse()
 */
klasse* sitzplan::getKlasse()
{
    if(kl==0){
	kl = (klasse*) sitzplanmapper::getInstance()->findReference("Klasse",getID());
    }
    return kl;
}


/*!
    \fn sitzplan::setKlasse(klasse *k)
 */
void sitzplan::setKlasse(klasse *k)
{
    this->kl = k;
}

int sitzplan::getReihen()
{
	return this->reihen;
}

void sitzplan::setReihen(int reihen)
{
	this->reihen = reihen;
}

int sitzplan::getSpalten()
{
	return this->spalten;
}

void sitzplan::setSpalten(int spalten)
{
	this->spalten=spalten;
}



/*!
    \fn sitzplan::getPlatz(int row, int col)
 */
platz* sitzplan::getPlatz(int row, int col)
{
    platz* result = 0;
    list<platz*>::iterator it = getPlaetze()->begin();
    while(it != getPlaetze()->end() && result == 0){
	int r = (*it)->getReihe(); 
	int s = (*it) -> getSpalte();
	if(r == row && s == col) result = *it;
	++it;
    }

   /*
   while(it != getPlaetze()->end() && result == 0){
	int r = (*it)->getReihe(); 
	int s = (*it) -> getSpalte();
	if(r == 0 && s == 0){ 
		result = *it;
		Transactions::getCurrentTransaction()->add(result);
		result->setReihe(r);
		result->setSpalte(s);
	}
	it++;
    }
  */

    if(result == 0){
    qDebug() << QString("sitzplan::getPlatz: Could not find platz (%1,%2) -- creating new one").arg(row).arg(col);
	result = (platz*) platzmapper::getInstance()->create();
	result->setReihe(row);
	result->setSpalte(col);
	addToPlaetze(result);
	Transactions::getCurrentTransaction()->add(this);
    }
    return result;

}
