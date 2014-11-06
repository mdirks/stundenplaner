/***************************************************************************
                          abstractpersistenceclass.cpp  -  description
                             -------------------
    begin                : Son Jul 20 2003
    copyright            : (C) 2003 by Marcus Dirks
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

#include "abstractpersistenceclass.h"
#include "database.h"

AbstractPersistenceClass::AbstractPersistenceClass(){
	qDebug("AbstractPersistenceClass()");
}


AbstractPersistenceClass::AbstractPersistenceClass(PObject *rs){
	this->realSubject = rs;
}
AbstractPersistenceClass::~AbstractPersistenceClass(){
}

/** No descriptions */
void AbstractPersistenceClass::save(){
	  Database::getInstance()->save(realSubject);
}
