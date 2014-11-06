//
// C++ Implementation: %{MODULE}
//
// Description:
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "klasse.h"

#include "klassemapper.h"
#include "sitzplanmapper.h"
#include "kursbuchmapper.h"
#include "notemapper.h"

klasse::klasse()
{
	list_stunden = 0;
	list_schueler = 0;
	list_templates = 0;
	list_teilleistungen = 0;
	sp = 0;
	kb = 0;
	sj = 0;
	setMapper(klassemapper::getInstance());
}


klasse::~klasse()
{
}




/*!
    \fn klasse::getStunden()
 */
list<stunde*>* klasse::getStunden()
{
       if(list_stunden == 0){
		list_stunden = klassemapper::getInstance()->findStunden(getID());
	}
	
	return list_stunden;
}


/*!
    \fn klasse::addStunde(stunde *st)
 */
void klasse::addToStunden(stunde *st)
{
    getStunden()->push_back(st);
}


/*!
    \fn klasse::deleteFromStunden(stunde *st)
 */
void klasse::deleteFromStunden(stunde *st)
{
    getStunden()->remove(st);
}


/*!
    \fn klasse::getSchueler()
 */
list<schueler*> * klasse::getSchueler()
{
    if(list_schueler == 0){
	list_schueler = klassemapper::getInstance()->findSchueler(getID());
    }
    return list_schueler;
}



/*!
    \fn klasse::addToSchueler(schueler *s)
 */
void klasse::addToSchueler(schueler *s)
{
    getSchueler()->push_back(s);
}


/*!
    \fn klasse::deleteFromSchueler(schueler *s)
 */
void klasse::deleteFromSchueler(schueler *s)
{
    getSchueler()->remove(s);
}
/*!
    \fn klasse::getSchueler()
 */
list<teilleistung*> * klasse::getTeilleistungen()
{
    if(list_teilleistungen == 0){
	list_teilleistungen = klassemapper::getInstance()->findTeilleistungen(getID());
    }
    return list_teilleistungen;
}



/*!
    \fn klasse::addToSchueler(schueler *s)
 */
void klasse::addToTeilleistungen(teilleistung *tl)
{
    getTeilleistungen()->push_back(tl);
    tl->setKlasse(this);
//     for(list<schueler*>::iterator it=getSchueler()->begin(); it!=getSchueler()->end();it++){
// 	note *n = (note*) notemapper::getInstance()->create();
// 	n->setSchueler(*it);
// 	tl->addToNoten(n);
//     }
}


/*!
    \fn klasse::deleteFromSchueler(schueler *s)
 */
void klasse::deleteFromTeilleistungen(teilleistung *tl)
{
    getTeilleistungen()->remove(tl);
}


void klasse::setSitzplan(sitzplan* sp)
{
	this->sp = sp;
	sp->setKlasse(this);
}

sitzplan* klasse::getSitzplan()
{
	if(sp==0){
		sp= (sitzplan*) klassemapper::getInstance()->findReference("Sitzplan",getID());
	} 
	if(sp==0){ // create if not yet defined 
		sp = (sitzplan*) sitzplanmapper::getInstance()->create();
		sp->setKlasse(this);
	}
	return sp;
}


/*!
    \fn klasse::getStundenplanTemplates()
 */
list<stundenplantemplateeintrag*> * klasse::getStundenplanTemplates()
{
    if(list_templates == 0){
	list_templates = klassemapper::getInstance()->findStundenplanTemplates(getID());
    }
    return list_templates;/// @todo implement me
}


/*!
    \fn klasse::addToStundenplanTemplates(stundenplantemplateeintrag *e)
 */
void klasse::addToStundenplanTemplates(stundenplantemplateeintrag *e)
{
    	e->setKlasse(this);
	getStundenplanTemplates()->push_back(e);
}


/*!
    \fn klasse::deleteFromStundenplanTemplates(stundenplantemplateeintrag *e)
 */
void klasse::deleteFromStundenplanTemplates(stundenplantemplateeintrag *e)
{
    getStundenplanTemplates()->remove(e);
}


/*!
    \fn klasse::getKursbuch()
 */
kursbuch* klasse::getKursbuch()
{
    	if(kb==0){
		kb= (kursbuch*) klassemapper::getInstance()->findReference("Kursbuch",getID());
	} 
	if(kb==0){ // create if not yet defined 
		kb = (kursbuch*) kursbuchmapper::getInstance()->create();
		kb->setKlasse(this);
	}
	return kb;/// @todo implement me
}


/*!
    \fn klasse::setKursbuch(kursbuch *kb)
 */
void klasse::setKursbuch(kursbuch *kb)
{
    this->kb = kb;
}


/*!
    \fn klasse::getSchuljahr()
 */
schuljahr* klasse::getSchuljahr()
{
    if(sj==0){
	sj=(schuljahr*) klassemapper::getInstance()->findReference("Schuljahr", getID());
    }
    return sj;
}


/*!
    \fn klasse::setSchuljahr(schuljahr *sj)
 */
void klasse::setSchuljahr(schuljahr *sj)
{
    this->sj = sj;
}
