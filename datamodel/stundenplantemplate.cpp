//
// C++ Implementation: stundenplantemplate
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "stundenplantemplate.h"
#include "stundenplantemplatemapper.h"

stundenplantemplate::stundenplantemplate()
{
	setMapper(stundenplantemplatemapper::getInstance());
}

stundenplantemplate::~stundenplantemplate()
{

}
/*!
    \fn stundenplantemplate::addToEintraege(stundenplantemplateeintrag *e)
 */
void stundenplantemplate::addToEintraege(stundenplantemplateeintrag *e)
{
    getEintraege()->push_back(e);
}


/*!
    \fn stundenplantemplate::deleteFromEintraege(stundenplantemplateeintrag *e)
 */
void stundenplantemplate::deleteFromEintraege(stundenplantemplateeintrag *e)
{
    getEintraege()->remove(e);
}


/*!
    \fn stundenplantemplate::getEintraege()
 */
list<stundenplantemplateeintrag*>*  stundenplantemplate::getEintraege()
{
    if(list_eintraege ==0){
	list_eintraege = stundenplantemplatemapper::getInstance()->findEintraege(getID());
    }
    return list_eintraege;
}
