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
	list_modified = new list<PObject*>();
}


Transaction::~Transaction()
{
}




/*!
    \fn Transaction::commit()
 */
void Transaction::commit()
{
    for(list<PObject*>::iterator it = list_modified -> begin(); it != list_modified->end(); it++)
    {
		if(*it){
            qDebug() << QString("Transaction::commit(): saving %1").arg(((*it)->getName()).c_str());
			(*it) -> save();
		} else {
            qDebug() << "Transaction::commit() :  Warning: Invalid object in list_modified";
		}
    }	
    list_modified -> clear();
    
}


/*!
    \fn Transaction::getModified()
 */
list<PObject*>  *Transaction::getModified()
{
    return list_modified;
}

void Transaction::add(PObject *o)
{
	list_modified->push_back(o);
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
