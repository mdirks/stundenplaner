/***************************************************************************
                          database.cpp  -  description
                             -------------------
    begin                : Fri Oct 4 2002
    copyright            : (C) 2002 by Marcus Dirks
    email                : marcus.dirks@t-online.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "database.h"
#include "databaseimpl_q.h"
#include "sqlite.h"

#include "pcollectionpersistence.h"
#include "ptreepersistence.h"

#include <QStringList>

 
Database* Database::instance=0;
QString Database::databasename=QString("");

Database* Database::getInstance(){
 	if(!instance)
	{
        //instance = new DatabaseImpl_Q();
        instance = new SQLite();
        instance->registerBasicTypes();
	}
	return instance;
}

void Database::registerBasicTypes()
{
    registerPersistentClass(PCollectionPersistence::getInstance(),"1.0");
    registerPersistentClass(PTreePersistence::getInstance(), "1.0");
}

void Database::setDatabaseName(QString name){
    databasename=name;
}

QString Database::getDatabaseName(){
	return databasename;
}

void Database::close(){
    if(instance){
        delete instance;
        instance=0;
    }
}


/*!
    \fn DatabaseImpl_Q::changeTo(string db_name)
 */
bool Database::changeTo(string db_name)
{
    Database::close();

    Database::setDatabaseName(QString::fromStdString(db_name));

    if(Database::getInstance()->isOpen()){
    return true;
    } else {
    return false;
    }

}


/*!
    \fn Database::loadCollection(PCollection *col)
 */
void Database::loadCollection(PCollection *col)
{
    /// @todo implement me
}






