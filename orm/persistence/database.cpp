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



 
Database* Database::instance=0;
QString Database::databasename=QString("");

Database* Database::getInstance(){
 	if(!instance)
	{
		instance = new DatabaseImpl_Q();
	}
	return instance;
}

void Database::setDatabaseName(QString name){
	databasename=name;
}

QString Database::getDatabaseName(){
	return databasename;
}





/*!
    \fn Database::loadCollection(PCollection *col)
 */
void Database::loadCollection(PCollection *col)
{
    /// @todo implement me
}






