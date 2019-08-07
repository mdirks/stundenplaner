//
// C++ Implementation: schueler
//
// Description: 
//
//
	// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "schueler.h"
#include "schuelermapper.h"

schueler::schueler()
{
	list_noten=0;
	list_fehlzeiten=0;
	list_bewertungen=0;
	kl=0;
	setMapper(schuelermapper::getInstance());
}


schueler::~schueler()
{
}




/*!
    \fn schueler::getKlasse()
 */
klasse* schueler::getKlasse()
{
    	return this->kl;
}


/*!
    \fn schueler::setKlasse(klasse* kl)
 */
void schueler::setKlasse(klasse* kl)
{
    this->kl = kl;
}


/*!
    \fn schueler::getNoten()
 */
list<note*> * schueler::getNoten()
{
        if(list_noten == 0){
		list_noten = schuelermapper::getInstance()->findNoten(getID());
	}
	
	return list_noten;
}


/*!
    \fn schueler::addNote(note *n)
 */
void schueler::addToNoten(note *n)
{
    getNoten()->push_back(n);
    saved=false;
}


/*!
    \fn schueler::deleteNote(note *n)
 */
void schueler::deleteFromNoten(note *n)
{
    getNoten()->remove(n);
}


/*!
    \fn schueler::getVorname()
 */
string schueler::getVorname()
{
   return vorname;
}


/*!
    \fn schueler::getNachnahme()
 */
string schueler::getNachname()
{
    return this->nachname;
}


/*!
    \fn schueler::setNachName(string nname)
 */
void schueler::setNachname(string nname)
{
    this->nachname=nname;
}


/*!
    \fn schueler::setVorname(string vname)
 */
void schueler::setVorname(string vname)
{
    this->vorname =vname;
}


/*!
    \fn schueler::method_2()
 */
string schueler::getTutor()
{
    return this->tutor;
}


/*!
    \fn schueler::setTutor(string tutor)
 */
void schueler::setTutor(string tutor)
{
    this->tutor = tutor;
}



/*!
    \fn schueler::getFehlzeiten()
 */
list<fehlzeit*> * schueler::getFehlzeiten()
{
        if(list_fehlzeiten == 0){
		list_fehlzeiten = schuelermapper::getInstance()->findFehlzeiten(getID());
	}
	
	return list_fehlzeiten;
}


/*!
    \fn schueler::addToFehlzeiten(fehlzeit *f)
 */
void schueler::addToFehlzeiten(fehlzeit *f)
{
    getFehlzeiten()->push_back(f);
    f->setSchueler(this);
}


/*!
    \fn schueler::deleteFromFehlzeiten(fehlzeit *)
 */
void schueler::deleteFromFehlzeiten(fehlzeit *f)
{
    getFehlzeiten()->remove(f);
}


/*!
    \fn schueler::getName()
 */
string schueler::getName()
{
    if(getNachname()!=""){
	return getNachname() + "," + getVorname();
    } else {
	return PObject::getName();
    }
}


/*!
    \fn schueler::getStundenBewertungen()
 */
list<stundenbewertung*>* schueler::getStundenbewertungen()
{
    if(list_bewertungen == 0){
		list_bewertungen = schuelermapper::getInstance()->findStundenbewertungen(getID());
    }
    return list_bewertungen;
}


/*!
    \fn schueler::addToStundenbewertungen(stundenbewertung *bew)
 */
void schueler::addToStundenbewertungen(stundenbewertung *bew)
{
    getStundenbewertungen()->push_back(bew);
	bew->setSchueler(this);
}


/*!
    \fn schueler::deleteFromStundenBewertungen(stundenbewertung *bew)
 */
void schueler::deleteFromStundenbewertungen(stundenbewertung *bew)
{
    getStundenbewertungen()->remove(bew);
}
