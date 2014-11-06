//
// C++ Implementation: stundenplantemplateeintrag
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "stundenplantemplateeintrag.h"

#include "stundenplantemplateeintragmapper.h"

#include "qstring.h"
#include "services/utils/datecompare.h"

stundenplantemplateeintrag::stundenplantemplateeintrag()
{
	setMapper(stundenplantemplateeintragmapper::getInstance());
	st=0;
	tag=0;
	kl=0;
	is_doppel = false;
        list_eintraege=0;
}

 stundenplantemplateeintrag::~stundenplantemplateeintrag()
{

}


/*!
    \fn stundenplantemplateeintrag::getStunde()
 */
int stundenplantemplateeintrag::getNrStunde()
{
    return this->st;
}


/*!
    \fn stundenplantemplateeintrag::getTag()
 */
int stundenplantemplateeintrag::getTag()
{
    return this->tag;
}


/*!
    \fn stundenplantemplateeintrag::getKlasse()
 */
klasse* stundenplantemplateeintrag::getKlasse()
{
    	if(kl==0){
		kl= (klasse*) stundenplantemplateeintragmapper::getInstance()->findReference("Klasse",getID());
	}
	return this->kl;
}


/*!
    \fn stundenplantemplateeintrag::setStunde(int st)
 */
void stundenplantemplateeintrag::setNrStunde(int st)
{
    this->st = st;
}


/*!
    \fn stundenplantemplateeintrag::setKlasse(klasse *kl)
 */
void stundenplantemplateeintrag::setKlasse(klasse *kl)
{
    this->kl = kl;
}


/*!
    \fn stundenplantemplateeintrag::setTag(int tag)
 */
void stundenplantemplateeintrag::setTag(int tag)
{
    this->tag = tag;
}


/*!
    \fn stundenplantemplateeintrag::getActive()
 */
bool stundenplantemplateeintrag::getActive()
{
    return true;
}


/*!
    \fn stundenplantemplateeintrag::setActive(bool is_active)
 */
void stundenplantemplateeintrag::setActive(bool is_active)
{
    /// @todo implement me
}


/*!
    \fn stundenplantemplateeintrag::getName()
 */
string stundenplantemplateeintrag::getName()
{
    if(getKlasse()){
    return getKlasse()->getName() + QString(" / %1 / %2 ").arg( getTag()).arg( getNrStunde()).toStdString();
    } else {
	return PObject::getName();
   }
	
}


/*!
    \fn stundenplantemplateeintrag::setName(string n)
 */
void stundenplantemplateeintrag::setName(string n)
{
    qDebug("Warning stundenplantemplateeintrag::setName() to nothing implementation");
}


/*!
    \fn stundenplantemplateeintrag::isDoppelstunde()
 */
bool stundenplantemplateeintrag::getDoppelstunde()
{
    return is_doppel;
}


/*!
    \fn stundenplantemplateeintrag::setDoppelstunde(bool d)
 */
void stundenplantemplateeintrag::setDoppelstunde(bool d)
{
        qDebug() << QString("stundenplantemplateeintrag: setting doppel to %1").arg(d);
	is_doppel=d;
}


/*!
    \fn stundenplantemplateeintrag::addToEintraege(stundenplaneintrag *se)
 */
void stundenplantemplateeintrag::addToEintraege(stundenplaneintrag *se)
{
     getEintraege()->push_back(se);
     se->setNrStunde(getNrStunde());
     se->setTag(getTag());
     se->setKlasse(getKlasse());
     se->setTemplate(this);
     se->setName(getName());
     se->setDoppelstunde(getDoppelstunde());
}


/*!
    \fn stundenplantemplateeintrag::deleteFromEintraege(stundenplaneintrag *se)
 */
void stundenplantemplateeintrag::deleteFromEintraege(stundenplaneintrag *se)
{
    getEintraege()->remove(se);
}


/*!
    \fn stundenplantemplateeintrag::getEintraege()
 */
list<stundenplaneintrag*>* stundenplantemplateeintrag::getEintraege()
{
    if(!list_eintraege){
	list_eintraege = stundenplantemplateeintragmapper::getInstance()->findEintraege(getID());
	list_eintraege->sort(DateMemberCompare<stundenplaneintrag>());
    }
    return list_eintraege;
}


/*!
    \fn stundenplantemplateeintrag::getEintrag(QDate date)
 */
stundenplaneintrag* stundenplantemplateeintrag::getEintrag(QDate date)
{

    list<stundenplaneintrag*> *list_eintraege = getEintraege();
    for(list<stundenplaneintrag*>::iterator it = list_eintraege->begin(); it != list_eintraege->end(); it++){
	if(((*it)-> getDatum()) == date) return *it;
    }	
    return 0;

}


/*!
    \fn stundenplantemplateeintrag::getDatumBegin()
 */
QDate stundenplantemplateeintrag::getDatumBegin()
{
    return dateBegin;
}


/*!
    \fn stundenplantemplateeintrag::getDatumEnde()
 */
QDate stundenplantemplateeintrag::getDatumEnde()
{
    return dateEnde;
}


/*!
    \fn stundenplantemplateeintrag::setDatumEnde(QDate date)
 */
void stundenplantemplateeintrag::setDatumEnde(QDate date)
{
    this->dateEnde=date;
}


/*!
    \fn stundenplantemplateeintrag::setDatumBegin(QDate date)
 */
void stundenplantemplateeintrag::setDatumBegin(QDate date)
{
    this->dateBegin=date;
}


/*!
    \fn stundenplantemplateeintrag::getNaechsten(stundenplaneintrag *se)
 */
/*
stundenplaneintrag* stundenplantemplateeintrag::getNaechsten(stundenplaneintrag *se)
{
    stundenplaneintrag *result=0;
    
    list<stundenplaneintrag*>::iterator it = std::find(getEintraege()->begin(), getEintraege()->end(),se);
    if(it != getEintraege()->end()){
	it++;
	if(it != getEintraege()->end()) result = (*it);
    }
    return result;
}
*/


/*!
    \fn stundenplantemplateeintrag::getVorherigen(stundenplaneintrag *se)
 */
/*
stundenplaneintrag* stundenplantemplateeintrag::getVorherigen(stundenplaneintrag *se)
{
    stundenplaneintrag *result=0;
    list<stundenplaneintrag*>::iterator it = std::find(getEintraege()->begin(), getEintraege()->end(),se);
    if(it != getEintraege()->end() && it != getEintraege()->begin()){
	it--;
	result = (*it);
    }
    return result;
}
*/
