//
// C++ Interface: platz
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef PLATZ_H
#define PLATZ_H

#include "schueler.h"
#include "note.h"
#include "orm/transactions/transactionobject.h"

#include <list>
#include <string>

using namespace std;

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class platz : public TransactionObject {
public:
    platz();

    ~platz();
    int getReihe();
    int  getSpalte();
    schueler* getSchueler();
    void setSpalte(int s);
    void setReihe(int r);
    void setSchueler(schueler *s);
    list<note*> *getNoten();
    void addToNoten(note* n);
    void deleteFromNoten(note *n);
    string getName();

private:
	int reihe, spalte;
	schueler *s;
	bool loaded_schueler;
	list<note*> *list_noten;
};

#endif
