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
#ifndef REIHE_H
#define REIHE_H

#include <list>
#include <string>

#include "../orm/transactions/transactionobject.h"
#include "stunde.h"
#include "notizholder.h"
//#include "../persistence/pobject.h"
//#include "../persistence/pcollection.h"

/**
@author Marcus Dirks
*/
class reihe : public /*TransactionObject*/ notizholder
{
public:
    reihe();

    ~reihe();
    list<stunde*> * getStunden();
    string getThema();
    void setThema(string thema);
    void addToStunden(stunde *st);
    void deleteFromStunden(stunde *st);

    string getVerlauf();
    void setVerlauf(string verlauf);

private:
    string thema, verlauf;
    list<stunde*> *list_stunden;
};

#endif
