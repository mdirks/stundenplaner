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
    
    list<PObject *>  *list_modified = t->getModified();
    for(list<PObject*>::iterator it = list_modified->begin(); it != list_modified->end(); it++){
    	PObject *o = *it;
	o->save();
    }
    
    delete(current);
    current = 0;
}
