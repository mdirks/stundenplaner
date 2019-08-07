//
// C++ Implementation: note
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "note.h"
#include "notemapper.h"

note::note()
{
	setMapper(notemapper::getInstance());
	s = 0;
	punkte=-1;

}


note::~note()
{
}




/*!
    \fn note::getPunkte()
 */
int note::getPunkte()
{
    return punkte;
}


/*!
    \fn note::getSchueler()
 */
schueler* note::getSchueler()
{
	if(s == 0){
		s = (schueler*) notemapper::getInstance()->findReference("Schueler",getID());
	}
	return s;
}


/*!
    \fn note::getBemerkung()
 */
string note::getBemerkung()
{
    return bem;
}


/*!
    \fn note::setBemerkung()
 */
void note::setBemerkung(string b)
{
    bem = b;
}


/*!
    \fn note::setPunkte(int p)
 */
void note::setPunkte(int p)
{
    punkte = p;
}


/*!
    \fn note::setSchueler(schueler *)
 */
void note::setSchueler(schueler *sch)
{
	this->s = sch;
	sch->addToNoten(this);
	
}


/*!
    \fn note::getDatum()
 */
QDateTime note::getDatum()
{
    return this->date;
}


/*!
    \fn note::setDatum(QDate d)
 */
void note::setDatum(QDateTime d)
{
    this->date = d;
}


/*!
    \fn note::setIsAt(bool at)
 */
void note::setIsAt(bool at)
{
    is_at = at;
}


/*!
    \fn note::getIsAt()
 */
bool  note::getIsAt()
{
    return is_at;
}


/*!
    \fn note::getIsKlausur()
 */
bool note::getIsKlausur()
{
    return is_kl;
}


/*!
    \fn note::setIsKlausur(bool kl)
 */
void note::setIsKlausur(bool kl)
{
    is_kl = kl;
}

string note::getName()
{
	if(getSchueler()){
		return string("note")+getSchueler()->getName();
	}
}