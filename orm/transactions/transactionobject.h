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
#ifndef TRANSACTIONOBJECT_H
#define TRANSACTIONOBJECT_H

#include "../orm/mapping/mappedobject.h"

/**
@author Marcus Dirks
*/
class TransactionObject : public MappedObject {
public:
    TransactionObject();

    ~TransactionObject();
    void markNew();
    void markModified();
    void markDeleted();
    void markSaved();
    bool isModified();
    bool isNew();
    bool isSaved();
    bool isDeleted();

private:
    bool is_saved;
    bool is_deleted;
    bool is_new;
    bool is_modified;
};

#endif
