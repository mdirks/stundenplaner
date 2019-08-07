//
// C++ Interface: stundenplantemplateeintrag
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef STUNDENPLANTEMPLATEEINTRAG_H
#define STUNDENPLANTEMPLATEEINTRAG_H

#include "datamodel/klasse.h"
#include "orm/transactions/transactionobject.h"
#include "datamodel/stundenplaneintrag.h"
#include "datamodel/reihe.h"
#include <list>

using namespace std;
/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class stundenplantemplateeintrag : public TransactionObject  {
public:
    stundenplantemplateeintrag();

    ~stundenplantemplateeintrag();
    int getNrStunde();
    int getTag();
    klasse* getKlasse();
    void setNrStunde(int st);
    void setKlasse(klasse *kl);
    void setTag(int tag);
    bool getActive();
    void setActive(bool is_active);
    string getName();
    void setName(string n);
    bool getDoppelstunde();
    void setDoppelstunde(bool d);
    void addToEintraege(stundenplaneintrag *se);
    void deleteFromEintraege(stundenplaneintrag *se);
    list<stundenplaneintrag*>* getEintraege();
    void addToReihen(reihe *r);
    void deleteFromReihen(reihe *r);
    list<reihe*>* getReihen();

    stundenplaneintrag* getEintrag(QDate date);
    QDate getDatumBegin();
    QDate getDatumEnde();
    void setDatumEnde(QDate date);
    void setDatumBegin(QDate date);
    /*
    stundenplaneintrag* getNaechsten(stundenplaneintrag *se);
    stundenplaneintrag* getVorherigen(stundenplaneintrag *se);
    */

private:
	int st,tag;
	klasse *kl;
	bool is_doppel;
	list<stundenplaneintrag*> *list_eintraege;
    //map<QDate,stundenplaneintrag*> map_eintraege;
    list<reihe*> *list_reihen;
	QDate dateEnde, dateBegin;

};

#endif
