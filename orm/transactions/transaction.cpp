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
#include "transaction.h"
#include "../mapping/mappingcontroler.h"
#include <QDebug>

Transaction::Transaction()
{
    set_modified = new set<PObject*>();
}


Transaction::~Transaction()
{
}




/*!
    \fn Transaction::commit()
 */
void Transaction::commit()
{
    for(set<PObject*>::iterator it = set_modified -> begin(); it != set_modified->end(); it++)
    {
		if(*it){
            qDebug() << QString("Transaction::commit(): saving %1").arg(((*it)->getName()).c_str());
			(*it) -> save();
		} else {
            qDebug() << "Transaction::commit() :  Warning: Invalid object in list_modified";
		}
    }	
    set_modified -> clear();
    
}


/*!
    \fn Transaction::getModified()
 */
set<PObject*>  *Transaction::getModified()
{
    return set_modified;
}

void Transaction::add(PObject *o)
{
    set_modified->insert(o);
	/*
	qDebug("In transaction now:\n");
	for(list<PObject*>::iterator it = list_modified->begin(); it != list_modified->end(); it++){
		qDebug(QString("%1, %2").arg((*it)->getPersistenceObject()->getClassName()).arg((*it)->getID()));
	}
	*/
}




/*!
    \fn Transaction::create(string className)
 */
PObject* Transaction::create(string className)
{
    PObject *o =  MappingControler::getInstance()->create(className);
    add(o);
    return o;
}
