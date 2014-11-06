//
// C++ Interface: stundenplantemplate
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef STUNDENPLANTEMPLATE_H
#define STUNDENPLANTEMPLATE_H

#include "orm/transactions/transactionobject.h"
#include "datamodel/stundenplantemplateeintrag.h"

#include <list>

using namespace std;

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class stundenplantemplate : public TransactionObject {
public:
    stundenplantemplate();
    ~stundenplantemplate();
    void addToEintraege(stundenplantemplateeintrag *e);
    void deleteFromEintraege(stundenplantemplateeintrag *e);
    list<stundenplantemplateeintrag*> * getEintraege();

private:
    list<stundenplantemplateeintrag*> *list_eintraege;
    

};

#endif
