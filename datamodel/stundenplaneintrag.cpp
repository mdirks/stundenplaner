//
// C++ Implementation: stundenplaneintrag
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "stundenplaneintrag.h"
#include "stundenplaneintragmapper.h"
#include "krusbucheintragmapper.h"
#include "kursbuch.h"
#include "orm/transactions/transactions.h"
#include "fehlzeitmapper.h"


 stundenplaneintrag::stundenplaneintrag()
{
	setMapper(stundenplaneintragmapper::getInstance());
	st=0;
	kl=0;
	ke=0;
	te=0;

	list_bew=0;
	list_fz=0;
}


stundenplaneintrag::~stundenplaneintrag()
{
}




/*!
    \fn stundenplaneintrag::getStunde()
 */
stunde* stundenplaneintrag::getStunde()
{
    	if(st==0){
		st= (stunde*) stundenplaneintragmapper::getInstance()->findReference("Stunde",getID());
	}
	return this->st;
}

klasse* stundenplaneintrag::getKlasse()
{
	if(kl==0){
		kl= (klasse*) stundenplaneintragmapper::getInstance()->findReference("Klasse",getID());
	}
	if(kl==0 && getTemplate()){
		kl = getTemplate()->getKlasse();
	}
	return this->kl;
}
/*!
    \fn stundenplaneintrag::getKursbuchEintrag()
 */
krusbucheintrag* stundenplaneintrag::getKursbuchEintrag()
{
	/*
	if(ke==0){
		ke= (krusbucheintrag*) stundenplaneintragmapper::getInstance()->findReference("KursbuchEintrag",getID());
	}
	if(ke==0){
	*/
		if(klasse* kl=getKlasse()){
			kursbuch *kb = getKlasse()->getKursbuch();
			if(kb){
				krusbucheintrag *kee = kb->getEintrag(this);
				if(kee==0){
					kee =krusbucheintragmapper::getInstance()->create();
					kee->setDatum(this->getDatum());
					kee->setStundenplanEintrag(this);
					Transactions::getCurrentTransaction()->add(kb);
					kb->addToEintraege(kee);
					Transactions::getCurrentTransaction()->add(this);
				}
				return kee;
			} else {
				qDebug("stundenplaneintrag::getKursbuchEintrag: STRANGE : invalid kursbuch in klasse");
			}
	
		} else {
			qDebug("stundenplaneintrag::getKursbuchEintrag: Klasse nicht gesetzt");
		}
	//}
        return ke;
}


/*!
    \fn stundenplaneintrag::getDatum()
 */
QDate stundenplaneintrag::getDatum()
{
    return this->date;
}


/*!
    \fn stundenplaneintrag::setDatum(QDate date)
 */
void stundenplaneintrag::setDatum(QDate date)
{
    this->date = date;
}


/*!
    \fn stundenplaneintrag::setKursbuchEintrag(kursbucheintrag *e)
 */
void stundenplaneintrag::setKursbuchEintrag(krusbucheintrag *e)
{
    this->ke = e;
}


/*!
    \fn stundenplaneintrag::setStunde(stunde* st)
 */
void stundenplaneintrag::setStunde(stunde* st)
{
    this->st =st;
    qDebug("stundenplaneintrag: setStunde()");
}

void stundenplaneintrag::setKlasse(klasse* kl)
{
    this->kl = kl;
}

/*!
    \fn stundenplaneintrag::isActive()
 */
bool stundenplaneintrag::getActive()
{
	return true;
    //return is_active;
}

bool stundenplaneintrag::operator<(stundenplaneintrag &eintrag)
{
	return (this->getDatum() < eintrag.getDatum());
}
/*!
    \fn stundenplaneintrag::setActive(bool is_active)
 */
void stundenplaneintrag::setActive(bool is_active)
{
    this->is_active = is_active;
}


/*!
    \fn stundenplaneintrag::getVerlauf()
 */
string stundenplaneintrag::getVerlauf()
{
	return this->verlauf;
}


/*!
    \fn stundenplaneintrag::setVerlauf(string s)
 */
void stundenplaneintrag::setVerlauf(string s)
{
    this->verlauf = s;
}





/*!
    \fn stundenplaneintrag::getName()
 */
string stundenplaneintrag::getName()
{
    if(getKlasse()){
	return getKlasse()->getName(); //+ getDatum().toString();// + " / " + getNrStunde();
    } else {
	return PObject::getName();
    }
}


/*!
    \fn stundenplaneintrag::getBewertungen()
 */
list<stundenbewertung*>* stundenplaneintrag::getBewertungen()
{
    if(list_bew==0){
	list_bew = stundenplaneintragmapper::getInstance()->findBewertungen(getID());
	for(list<stundenbewertung*>::iterator it = list_bew->begin(); it != list_bew->end(); it++){
		if((*it)->getSchueler()){
			map_bew[(*it)->getSchueler()]=(*it);
		}else {
			qDebug("stundenplaneintrag::getBewertungen(): list contains bewertung without schueler: dropping");
		}
	}
    }
    return list_bew;
}


/*!
    \fn stundenplaneintrag::addToBewertungen(stundenbewertungen *sb)
 */
void stundenplaneintrag::addToBewertungen(stundenbewertung *sb)
{
    if(sb->getSchueler()){
	    getBewertungen()->push_back(sb);
	    map_bew[sb->getSchueler()] = sb;
	    sb->setStundenplaneintrag(this);
    } else {
	qDebug("stundenplaneintrag::addToBewertung: Bewertung without schueler, could not add");
    }
    
    saved=false;	
}


/*!
    \fn stundenplaneintrag::deleteFromBewertungen(stundenbewertung *sb)
 */
void stundenplaneintrag::deleteFromBewertungen(stundenbewertung *sb)
{
    getBewertungen()->remove(sb);
}





/*!
    \fn stundenplaneintrag::getFehlzeiten()
 */
list<fehlzeit*>* stundenplaneintrag::getFehlzeiten()
{
    if(list_fz==0){
	list_fz = stundenplaneintragmapper::getInstance()->findFehlzeiten(getID());
	for(list<fehlzeit*>::iterator it = list_fz->begin(); it != list_fz->end() ; it++){
		if((*it)->getSchueler()){
			map_fehl[(*it)->getSchueler()] = (*it);
		} else {
			qDebug("stundenplaneintrag::getFehlzeiten(): list contains fehlzeit without schueler: dropping");
		}
	}
    }
    return list_fz;
}


/*!
    \fn stundenplaneintrag::addToFehlzeiten(fehlzeit *fz)
 */
void stundenplaneintrag::addToFehlzeiten(fehlzeit *fz)
{
    getFehlzeiten()->push_back(fz);
    if(fz->getSchueler()){
	map_fehl[fz->getSchueler()] = fz;
    } else {
	qDebug("stundenplaneintrag::addToFehlzeiten: WARNING fehlzeit without schueler, skipping");
    }
    fz->setStundenplaneintrag(this);
}

void stundenplaneintrag::addFehlzeit(schueler *s)
{
	fehlzeit* fz = (fehlzeit*) fehlzeitmapper::getInstance()->create();
	fz->setSchueler(s);
	Transactions::getCurrentTransaction()->add(s);
	s->addToFehlzeiten(fz);
	addToFehlzeiten(fz);
}

/*!
    \fn stundenplaneintrag::deleteFromFehlzeiten(fehlzeit *fz)
 */
void stundenplaneintrag::deleteFromFehlzeiten(fehlzeit *fz)
{
    getFehlzeiten()->remove(fz);
    map<schueler*,fehlzeit*>::iterator it = map_fehl.find(fz->getSchueler());
    if(it != map_fehl.end()){
	map_fehl.erase(it);
    }
}


/*!
    \fn stundenplaneintrag::getDoppelstunde()
 */
bool stundenplaneintrag::getDoppelstunde()
{
    return is_doppel;
}


/*!
    \fn stundenplaneintrag::setDoppelstunde(bool d)
 */
void stundenplaneintrag::setDoppelstunde(bool d)
{
    is_doppel=d;
}


/*!
    \fn stundenplaneintrag::getBewertung(schueler *s)
 */
stundenbewertung* stundenplaneintrag::getBewertung(schueler *s)
{
    getBewertungen();

    map<schueler*, stundenbewertung*>::iterator it = map_bew.find(s);
    if( it != map_bew.end()){
	 return it->second;
    } else {
	return 0;
    }
}
/*!
    \fn stundenplaneintrag::getFehlzeit(schueler *s)
 */
fehlzeit* stundenplaneintrag::getFehlzeit(schueler *s)
{
    getFehlzeiten();

    map<schueler*, fehlzeit*>::iterator it = map_fehl.find(s);
    if( it != map_fehl.end()){
	return it->second;
    } else {
	return 0;
    }
}


/*!
    \fn stundenplaneintrag::getTemplate()
 */
stundenplantemplateeintrag* stundenplaneintrag::getTemplate()
{
    if(!te){
	te = (stundenplantemplateeintrag*) stundenplaneintragmapper::getInstance()->findReference("Template",getID());
    }
     return te;
}


/*!
    \fn stundenplaneintrag::setTemplate(StundenplanEintragTemplate *et)
 */
void stundenplaneintrag::setTemplate(stundenplantemplateeintrag *te)
{
    this->te=te;
}


/*!
    \fn stundenplaneintrag::getNrStunde()
 */
int stundenplaneintrag::getNrStunde()
{
    if(getTemplate()){
	return getTemplate()->getNrStunde();
    }
    return n_st;
}


/*!
    \fn stundenplaneintrag::getTag()
 */
int stundenplaneintrag::getTag()
{
     if(getTemplate()){
	return getTemplate()->getTag();
    }
    return n_t;
}


/*!
    \fn stundenplaneintrag::setTag(int nt)
 */
void stundenplaneintrag::setTag(int nt)
{
    this->n_t = nt;
}


/*!
    \fn stundenplaneintrag::setNrStunde(int nrs)
 */
void stundenplaneintrag::setNrStunde(int nrs)
{
    this->n_st =nrs;
}


