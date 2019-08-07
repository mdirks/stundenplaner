//
// C++ Implementation: kursbuch
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "kursbuch.h"
#include "kursbuchmapper.h"


kursbuch::kursbuch()
{
	setMapper(kursbuchmapper::getInstance());
	this->kl = 0;
	this->list_eintraege = 0;
	this->kl1a = 0;
	this->kl1b = 0;
	this->kl2a = 0;
	this->kl2b = 0;
	this->at1=0;
	this->at2=0;
	this->g1=0;
	this->g2=0;
}


kursbuch::~kursbuch()
{
}




/*!
    \fn kursbuch::getEintraege()
 */
list<krusbucheintrag*>* kursbuch::getEintraege()
{
    if(list_eintraege==0){
	list_eintraege = kursbuchmapper::getInstance()->findEintraege(getID());
   }
   return list_eintraege;
}


/*!
    \fn kursbuch::addToEintraege()
 */
void kursbuch::addToEintraege(krusbucheintrag *e)
{
    getEintraege()->push_back(e);
    e->setKursbuch(this);
}


/*!
    \fn kursbuch::removeFromEintraege()
 */
void kursbuch::deleteFromEintraege(krusbucheintrag *e)
{
    getEintraege()->remove(e);
}


klasse* kursbuch::getKlasse()
{
	if(kl==0){
		kl = (klasse*) kursbuchmapper::getInstance()->findReference("Klasse",getID());
	}
	return kl;
}

void kursbuch::setKlasse(klasse *kl)
{
	this->kl = kl;
}

/*!
    \fn kursbuch::getEintrag(QDate date)
 */
krusbucheintrag* kursbuch::getEintrag(QDate date)
{
    list<krusbucheintrag*> *list_eintraege = getEintraege();
    for(list<krusbucheintrag*>::iterator it = list_eintraege->begin(); it != list_eintraege->end(); it++){
	if((*it)-> getDatum() == date) return *it;
    }	
    return 0;
}

krusbucheintrag* kursbuch::getEintrag(stundenplaneintrag *se)
{
    list<krusbucheintrag*> *list_eintraege = getEintraege();
    for(list<krusbucheintrag*>::iterator it = list_eintraege->begin(); it != list_eintraege->end(); it++){
	if((*it)-> getStundenplanEintrag() == se) return *it;
    }	
    return 0;
}
/*!
    \fn kursbuch::getName()
 */
string kursbuch::getName()
{
    if(klasse *kl=getKlasse()){
	return "Kursbuch " + kl->getName();
    } else {
	return PObject::getName();
   }
}


teilleistung* kursbuch::getKlausur1a()
{
	if(kl1a==0){
		kl1a = (teilleistung*) kursbuchmapper::getInstance()->findReference("Klausur1a",getID());
	}
	return kl1a;
}

void kursbuch::setKlausur1a(teilleistung *kl)
{
	this->kl1a = kl;
}

teilleistung* kursbuch::getKlausur1b()
{
	if(kl1b==0){
		kl1b = (teilleistung*) kursbuchmapper::getInstance()->findReference("Klausur1b",getID());
	}
	return kl1b;
}

void kursbuch::setKlausur1b(teilleistung *kl)
{
	this->kl1b = kl;
}

teilleistung* kursbuch::getKlausur2a()
{
	if(kl2a==0){
		kl2a = (teilleistung*) kursbuchmapper::getInstance()->findReference("Klausur2a",getID());
	}
	return kl2a;
}

void kursbuch::setKlausur2a(teilleistung *kl)
{
	this->kl2a = kl;
}


teilleistung* kursbuch::getKlausur2b()
{
	if(kl2b==0){
		kl2b = (teilleistung*) kursbuchmapper::getInstance()->findReference("Klausur2b",getID());
	}
	return kl2b;
}

void kursbuch::setKlausur2b(teilleistung *kl)
{
	this->kl2b = kl;
}


teilleistung* kursbuch::getAt1()
{
	if(at1==0){
		at1 = (teilleistung*) kursbuchmapper::getInstance()->findReference("At1",getID());
	}
	return at1;
}

void kursbuch::setAt1(teilleistung *kl)
{
	this->at1 = kl;
}

teilleistung* kursbuch::getAt2()
{
	if(at2==0){
		at2 = (teilleistung*) kursbuchmapper::getInstance()->findReference("At2",getID());
	}
	return at2;
}

void kursbuch::setAt2(teilleistung *kl)
{
	this->at2 = kl;
}

teilleistung* kursbuch::getG1()
{
	if(g1==0){
		g1 = (teilleistung*) kursbuchmapper::getInstance()->findReference("G1",getID());
	}
	return g1;
}

void kursbuch::setG1(teilleistung *kl)
{
	this->g1 = kl;
}

teilleistung* kursbuch::getG2()
{
	if(g2==0){
		g2 = (teilleistung*) kursbuchmapper::getInstance()->findReference("G2",getID());
	}
	return g2;
}

void kursbuch::setG2(teilleistung *kl)
{
	this->g2 = kl;
}

