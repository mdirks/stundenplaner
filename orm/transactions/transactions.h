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
#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include "transaction.h"

/**
@author Marcus Dirks
*/
class Transactions{
public:
    Transactions();

    ~Transactions();
    static Transaction* getCurrentTransaction();
    static void commit(Transaction *t);
    
private:
	static Transaction *current;
};

#endif
