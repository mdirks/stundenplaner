//
// C++ Interface: stundenplan
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef STUNDENPLAN_H
#define STUNDENPLAN_H

#include "datamodel/notizholder.h"
#include "datamodel/stundenplantemplateeintrag.h"

#include <qdatetime.h>

#include <list>

using namespace std;

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class stundenplan : public notizholder {
public:
    stundenplan();

    ~stundenplan();
    void addToTemplateEintraege(stundenplantemplateeintrag *e);
    void deleteFromTemplateEintraege(stundenplantemplateeintrag *e);
    list<stundenplantemplateeintrag*> * getTemplateEintraege();
    //void getEintraege(list<stundenplaneintrag*> *result, QDate date);


private:
	list<stundenplantemplateeintrag*> *list_templates;
};

#endif
