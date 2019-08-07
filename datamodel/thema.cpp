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
#include "thema.h"
#include "themamapper.h"
#include "lernkartensatzmapper.h"

thema::thema()
 : notizholder(),title("EmptyTitle")
{
	
	list_related=0;
	list_sub=0;
	list_lernkarten=0;
	ls = 0;

	setMapper(themamapper::getInstance());
}


thema::~thema()
{
}




string thema::getInhalt()
{
	return this->inhalt;
}

void thema::setInhalt(string inhalt)
{
	this->inhalt = inhalt;
}




/*!
    \fn thema::*getRelated()
 */
list<thema*> *thema::getRelated()
{
    if(list_related==0){
    	list_related = themamapper::getInstance()->findRelated(getID());
    }
    return list_related;
}


/*!
    \fn thema::*getSub()
 */
list<thema*>  *thema::getSub()
{
    if(list_sub==0){
    	list_sub =  themamapper::getInstance()->findSub(getID());
    }
    return list_sub;
}




/*!
    \fn thema::addRelated(thema *th)
 */
void thema::addToRelated(thema *th)
{
    getRelated()->push_back(th);
}




/*!
    \fn thema::addSub(thema *th)
 */
void thema::addToSub(thema *th)
{
    getSub()->push_back(th);
}


/*!
    \fn thema::getTitle()
 */
string thema::getTitle()
{
    return title;
}

void thema::setTitle(string title)
{
	this->title=title;
}



/*!
    \fn thema::deleteFromRelated(thema *th)
 */
void thema::deleteFromRelated(thema *th)
{
    /// @todo implement me
}





/*!
    \fn thema::deleteFromSub(thema *th)
 */
void thema::deleteFromSub(thema *th)
{
    /// @todo implement me
}




/*!
    \fn thema::getLernkarten()
 */
list<lernkarte*>* thema::getLernkarten()
{
	if(list_lernkarten==0){
		list_lernkarten = themamapper::getInstance()->findLernkarten(getID());
	}
	return list_lernkarten;
}


/*!
    \fn thema::addToLernkarten(lernkarte *lk)
 */
void thema::addToLernkarten(lernkarte *lk)
{
	getLernkarten()->push_back(lk);
}


/*!
    \fn thema::delteFromLernkarten(lernkarte *lk)
 */
void thema::deleteFromLernkarten(lernkarte *lk)
{
	getLernkarten()->remove(lk);
}


/*!
    \fn thema::getLernkartensatz()
 */
lernkartensatz* thema::getLernkartensatz()
{
	if(!ls){
		ls= (lernkartensatz*) themamapper::getInstance()->findReference("Lernkartensatz",getID());
	}
	if(!ls){
		ls = (lernkartensatz*) lernkartensatzmapper::getInstance()->create();
	}
	return ls;
}


/*!
    \fn thema::setLernkartensatz(lernkartensatz *ls)
 */
void thema::setLernkartensatz(lernkartensatz *ls)
{
	this->ls = ls;
}
