//
// C++ Interface: kursbuch
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef KURSBUCH_H
#define KURSBUCH_H

#include "krusbucheintrag.h"
#include "klasse.h"
#include "stundenplaneintrag.h"
#include "teilleistung.h"
#include "orm/transactions/transactionobject.h"

#include <list>

using namespace std;

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class kursbuch : public TransactionObject {
public:
    kursbuch();
    ~kursbuch();

    klasse* getKlasse();
    void setKlasse(klasse *kl);

    list<krusbucheintrag*>* getEintraege();
    void addToEintraege(krusbucheintrag *e);
    void deleteFromEintraege(krusbucheintrag *e);
    krusbucheintrag* getEintrag(QDate date);
	krusbucheintrag* getEintrag(stundenplaneintrag *se);
    string getName();

    teilleistung* getKlausur1a();
    void setKlausur1a(teilleistung *kl);
    teilleistung* getKlausur1b();
    void setKlausur1b(teilleistung *kl);
    teilleistung* getKlausur2a();
    void setKlausur2a(teilleistung *kl);
    teilleistung* getKlausur2b();
    void setKlausur2b(teilleistung *kl);
    teilleistung* getAt1();
    void setAt1(teilleistung *kl);
    teilleistung* getAt2();
    void setAt2(teilleistung *kl);
    teilleistung* getG1();
    void setG1(teilleistung *kl);
    teilleistung* getG2();
    void setG2(teilleistung *kl);
    	

private:
	list<krusbucheintrag*> *list_eintraege;
	klasse *kl;

	teilleistung *kl1a, *kl1b, *kl2a, *kl2b, *at1, *at2, *g1, *g2;
};

#endif
