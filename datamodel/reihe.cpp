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
#include "reihe.h"
#include "reihemapper.h"

reihe::reihe()
 : notizholder()
{
	list_stunden=0;
	
	setMapper(reihemapper::getInstance());
}


reihe::~reihe()
{
}




/*!
    \fn reihe::getStunden()
 */
std::list<stunde*> * reihe::getStunden()
{
    if(list_stunden==0){
    	list_stunden = reihemapper::getInstance()->findStunden(getID());
    }
    return list_stunden;
}


/*!
    \fn reihe::getThema()
 */
string reihe::getThema()
{
    return thema;
}


/*!
    \fn reihe::setThema(string thema)
 */
void reihe::setThema(string thema)
{
    this->thema=thema;
}


/*!
    \fn reihe::addToStunden(stunde *st)
 */
void reihe::addToStunden(stunde *st)
{
    getStunden()->push_back(st);
}


/*!
    \fn reihe::deleteFromStunden(stunde *st)
 */
void reihe::deleteFromStunden(stunde *st)
{
    getStunden()->remove(st);
}




string reihe::getVerlauf()
{
    return verlauf;
}


/*!
    \fn stunde::setVerlauf(const string &verlauf)
 */
void reihe::setVerlauf(string verlauf)
{
    this->verlauf = verlauf;
}
