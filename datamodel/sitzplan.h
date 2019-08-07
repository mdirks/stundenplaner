//
// C++ Interface: sitzplan
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef SITZPLAN_H
#define SITZPLAN_H

#include "platz.h"
#include "klasse.h"
#include "orm/transactions/transactionobject.h"

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class sitzplan : public TransactionObject {
public:
    sitzplan();

    ~sitzplan();
    list<platz*> * getPlaetze();
    void addToPlaetze(platz *pl);
    void deleteFromPlaetze(platz *pl);
    klasse* getKlasse();
    void setKlasse(klasse *k);

   void setReihen(int reihen);
   int getReihen();
  void setSpalten(int spalten);
  int getSpalten();
    platz* getPlatz(int row, int col);


private:
   list<platz*> *list_plaetze;
   klasse *kl;
   int reihen, spalten;
};

#endif
