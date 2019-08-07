//
// C++ Implementation: schultag
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "schultag.h"
#include "schultagmapper.h"

schultag::schultag()
{
	setMapper( schultagmapper::getInstance() );

	list_eintraege = 0;
}


schultag::~schultag()
{
}




/*!
    \fn schultag::getEintraege()
 */
list<stundenplaneintrag*>* schultag::getEintraege()
{
 	if(list_eintraege == 0){
		list_eintraege = schultagmapper::getInstance()->findEintraege(getID());
	}
	return list_eintraege;
}


/*!
    \fn schultag::addToEintraege(stundenplaneintrag *eintrag)
 */
void schultag::addToEintraege(stundenplaneintrag *eintrag)
{
    getEintraege()->push_back(eintrag);
}


/*!
    \fn schultag::deleteFromEintraege(stundenplaneintrag *eintrag)
 */
void schultag::deleteFromEintraege(stundenplaneintrag *eintrag)
{
    getEintraege()->remove(eintrag);
}


/*!
    \fn schultag::getDatum()
 */
QDateTime schultag::getDatum()
{
    return this->date;
}


/*!
    \fn schultag::setDatum(QDateTime date)
 */
void schultag::setDatum(QDateTime date)
{
    this->date = date;
}
