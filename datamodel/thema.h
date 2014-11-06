//
// C++ Interface: %{MODULE}
//
// Description: 
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef THEMA_H
#define THEMA_H

#include <list>
#include <string>

#include "orm/transactions/transactionobject.h"
#include "notizholder.h"
//#include "stunde.h"
//#include "reihe.h"


using namespace std;
/**
@author Marcus Dirks
*/

class stunde;
class reihe;
class lernkarte;
class lernkartensatz;

class thema : public /*TransactionObject*/ notizholder
{
public:
    thema();

    ~thema();
   
    list<thema*> *getRelated();
    list<thema*>  *getSub();
    
    void addToRelated(thema *th);
    void addToSub(thema *th);
    void deleteFromRelated(thema *th);
    void deleteFromSub(thema *th);

    string getTitle();
    void setTitle(string title);

    string getInhalt();
    void setInhalt(string ih);
    list<lernkarte*>* getLernkarten();
    void addToLernkarten(lernkarte *lk);
    void deleteFromLernkarten(lernkarte *lk);
    lernkartensatz* getLernkartensatz();
    void setLernkartensatz(lernkartensatz *ls);
    
private:
    
    list<thema*> *list_sub;
    list<thema*> *list_related;
    list<lernkarte*> *list_lernkarten;
    lernkartensatz *ls;
    string title,inhalt;

};

#endif
