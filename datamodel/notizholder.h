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
#include "bookmark.h"
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

    list<bookmark*>* getBookmarks();
    void addToBookmarks(bookmark *b);
    void deleteFromBookmarks(bookmark *b);

private:
    list<notiz*> *list_notizen;
    list<material*> *list_materialien;
    list<bookmark*> *list_bookmarks;
};

#endif
