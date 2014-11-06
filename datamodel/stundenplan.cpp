//
// C++ Implementation: stundenplan
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "stundenplan.h"
#include "stundenplanmapper.h"



stundenplan::stundenplan()
{
	setMapper(stundenplanmapper::getInstance());
	list_templates=0;
}


stundenplan::~stundenplan()
{
}




/*!
    \fn stundenplan::addToEintraege(stundenplaneintrag *e)
 */
void stundenplan::addToTemplateEintraege(stundenplantemplateeintrag *e)
{
    getTemplateEintraege()->push_back(e);
}


/*!
    \fn stundenplan::deleteFromEintraege(stundenplaneintrag *e)
 */
void stundenplan::deleteFromTemplateEintraege(stundenplantemplateeintrag *e)
{
    getTemplateEintraege()->remove(e);
}


/*!
    \fn stundenplan::getEintraege()
 */
list<stundenplantemplateeintrag*> * stundenplan::getTemplateEintraege()
{
    if(list_templates == 0){
	list_templates = stundenplanmapper::getInstance()->findTemplateEintraege(getID());
    }
    return list_templates;
}

//  void stundenplan::getEintraege(list<stundenplaneintrag*> *result, QDate date)
// {
// 	list<stundenplaneintrag*> *all = getEintraege();
// 	for(list<stundenplaneintrag*>::iterator it = all->begin(); it != all->end(); it++){
// 		if(((*it)->getDatum()) == date){
// 			result->push_back(*it);
// 		}
// 	}
// }