//
// C++ Implementation: %{MODULE}
//
// Description:
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "transactions.h"

Transaction* Transactions::current = 0;

Transactions::Transactions()
{
}


Transactions::~Transactions()
{
}




/*!
    \fn Transactions::getTransaction()
 */
Transaction* Transactions::getCurrentTransaction()
{
    if(current==0){
     	current= new Transaction();
    }
    return current;
}


/*!
    \fn Transactions::commit(Transaction *t)
 */
void Transactions::commit(Transaction *t)
{
    if(t != current){
    	qWarning("Transactions::commit : Got invalid  transaction");
    }
    
    set<PObject *>  *set_modified = t->getModified();
    for(set<PObject*>::iterator it = set_modified->begin(); it != set_modified->end(); it++){
    	PObject *o = *it;
	o->save();
    }
    
    delete(current);
    current = 0;
}
