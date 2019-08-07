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
#ifndef NOTIZHOLDER_H
#define NOTIZHOLDER_H

#include <list>
#include "notiz.h"
#include "material.h"
#include "orm/transactions/transactionobject.h"

using namespace std;


/**
@author Marcus Dirks
*/
class notizholder : public TransactionObject {
public:
    notizholder();
    ~notizholder();
    
    list<notiz*>* getNotizen();
    void addToNotizen(notiz *n);
    void deleteFromNotizen(notiz *n);

    list<material*>* getMaterialien();
    void addToMaterialien(material *n);
    void deleteFromMaterialien(material *n);

private:
    list<notiz*> *list_notizen;
    list<material*> *list_materialien;
};

#endif
