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
#ifndef TRANSACTION_H
#define TRANSACTION_H

//#include <list>
#include <set>

#include "transactionobject.h"
#include "../persistence/pobject.h"
using namespace std;


/**
@author Marcus Dirks
*/
class Transaction{

friend class Transactions;

public:
    Transaction();
    ~Transaction();
    
    void commit();
    void add(PObject* o);
    PObject* create(string className);


private:
    set<PObject*> * getModified();

    
private: 
    set<PObject*> *set_modified;
};

#endif
