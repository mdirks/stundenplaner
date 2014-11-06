//
// C++ Implementation: platz
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "platz.h"
#include "platzmapper.h"

platz::platz()
{
	loaded_schueler=false;
	s=0;
	list_noten=0;
	setMapper(platzmapper::getInstance());
}


platz::~platz()
{
}

string platz::getName()
{
    return QString("r%1, s%2").arg(getReihe()).arg(getSpalte()).toStdString();
}


/*!
    \fn platz::getReihe()
 */
int platz::getReihe()
{
	return reihe;
}


/*!
    \fn platz::getSpalte()
 */
int  platz::getSpalte()
{
	return spalte;
}


/*!
    \fn platz::getSchueler()
 */
schueler* platz::getSchueler()
{
   	if(s==0 && ! loaded_schueler){
		s= (schueler*) platzmapper::getInstance()->findReference("Schueler",getID());
		loaded_schueler=true;
	}
	return this->s;
}


/*!
    \fn platz::setSpalte(int s)
 */
void platz::setSpalte(int s)
{
    this->spalte = s;
}


/*!
    \fn platz::setReihe(int r)
 */
void platz::setReihe(int r)
{
    this->reihe = r;
}


/*!
    \fn platz::setSchueler(schueler *s)
 */
void platz::setSchueler(schueler *s)
{
	
        this->s = s;
	//loaded_schueler=true;
}


list<note*> *platz::getNoten()
{
	if(list_noten == 0){
		list_noten = platzmapper::getInstance()->findNoten(getID());
	}
	
	return list_noten;
}


void platz::addToNoten(note *n)
{
	getNoten()->push_back(n);
	saved=false;
}

/*!
    \fn stunde::deleteOpo(opo *o)
 */
void platz::deleteFromNoten(note *n)
{
    getNoten()->remove(n);
}




