//
// C++ Implementation: krusbucheintrag
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "krusbucheintrag.h"
#include "krusbucheintragmapper.h"
#include "kursbuch.h"

krusbucheintrag::krusbucheintrag()
{
	setMapper(krusbucheintragmapper::getInstance());
	kb=0;
	se=0;
}


krusbucheintrag::~krusbucheintrag()
{
}




/*!
    \fn krusbucheintrag::getDatum()
 */
QDate krusbucheintrag::getDatum()
{
    return this->date;
}


/*!
    \fn krusbucheintrag::getStunde()
 */
string krusbucheintrag::getStunde()
{
    return this->st;
}


/*!
    \fn krusbucheintrag::setDatum(QDate date)
 */
void krusbucheintrag::setDatum(QDate date)
{
    this->date = date;
}


/*!
    \fn krusbucheintrag::getEintrag()
 */
string krusbucheintrag::getEintrag()
{
    return this->text;
}


/*!
    \fn krusbucheintrag::setEintrag(string text)
 */
void krusbucheintrag::setEintrag(string text)
{
    this->text = text;
}


/*!
    \fn krusbucheintrag::setStunde(string st)
 */
void krusbucheintrag::setStunde(string st)
{
    this->st = st;
}


/*!
    \fn krusbucheintrag::getKursbuch()
 */
kursbuch* krusbucheintrag::getKursbuch()
{
    	if(!kb){
		kb = (kursbuch*) krusbucheintragmapper::getInstance()->findReference("Kursbuch",getID());
	}
	return kb;
}


/*!
    \fn krusbucheintrag::setKursbuch(kursbuch *kb)
 */
void krusbucheintrag::setKursbuch(kursbuch *kb)
{
   	this->kb=kb;
}


/*!
    \fn krusbucheintrag::getStundenplanEintrag()
 */
stundenplaneintrag* krusbucheintrag::getStundenplanEintrag()
{
  	 if(!se){
		se = (stundenplaneintrag*) krusbucheintragmapper::getInstance()->findReference("StundenplanEintrag",getID());
	}
	return se;
}


/*!
    \fn krusbucheintrag::setStundenplanEintrag(stundenplaneintrag *se)
 */
void krusbucheintrag::setStundenplanEintrag(stundenplaneintrag *se)
{
    this->se = se;
}


/*!
    \fn krusbucheintrag::getName()
 */
string krusbucheintrag::getName()
{
    if(stundenplaneintrag *se = getStundenplanEintrag()){
	return "KE " + se->getName();
    } else {
	return PObject::getName();
    }
}


/*!
    \fn krusbucheintrag::getBemerkung()
 */
string krusbucheintrag::getBemerkung()
{
    return this->bem;
}


/*!
    \fn krusbucheintrag::getDetails()
 */
string krusbucheintrag::getDetails()
{
	return this->det;
}


/*!
    \fn krusbucheintrag::setBemerkung(string bem)
 */
void krusbucheintrag::setBemerkung(string bem)
{
    this->bem = bem;
}


/*!
    \fn krusbucheintrag::setDetails()
 */
void krusbucheintrag::setDetails(string det)
{
   this->det = det;
}
