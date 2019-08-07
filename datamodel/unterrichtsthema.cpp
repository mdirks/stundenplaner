//
// C++ Implementation: unterrichtsthema
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "unterrichtsthema.h"
#include "unterrichtsthemamapper.h"

unterrichtsthema::unterrichtsthema()
 : thema()
{
	list_stunden=0;
	list_reihen=0;

	setMapper(unterrichtsthemamapper::getInstance());
}


unterrichtsthema::~unterrichtsthema()
{
}


/*!
    \fn thema::getStunden()
 */
list<stunde*> *unterrichtsthema::getStunden()
{
    if(list_stunden==0){
    	list_stunden = unterrichtsthemamapper::getInstance()->findStunden(getID());
    }
    return list_stunden;
}


/*!
    \fn thema::getReihen()
 */
list<reihe*> *unterrichtsthema::getReihen()
{
   if(list_reihen==0){
   	list_reihen = unterrichtsthemamapper::getInstance()->findReihen(getID());
   }
   return list_reihen;
}


/*!
    \fn thema::addReihe(reihe *r)
 */
void unterrichtsthema::addToReihen(reihe *r)
{
    getReihen()->push_back(r);
}

/*!
    \fn thema::addStunde(stunde* st)
 */
void unterrichtsthema::addToStunden(stunde* st)
{
    getStunden()->push_back(st);
}

/*!
    \fn thema::deleteFromReihen(reihe * r)
 */
void unterrichtsthema::deleteFromReihen(reihe * r)
{
    /// @todo implement me
}

/*!
    \fn thema::deleteFromStunden(stunde *st)
 */
void unterrichtsthema::deleteFromStunden(stunde *st)
{
    /// @todo implement me
}