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

#include <list>

#include "transactionobject.h"
#include "../persistence/pobject.h"
using namespace std;

/**
@author Marcus Dirks
*/
class Transaction{
public:
    Transaction();
    ~Transaction();
    
    void commit();
    void add(PObject* o);
    list<PObject*> * getModified();
    PObject* create(string className);

    
private: 
    list<PObject*> *list_modified;
};

#endif
