/***************************************************************************
                          persistenceclass.cpp  -  description
                             -------------------
    begin                : Sam Jun 21 2003
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

#include "persistenceclass.h"
#include "database.h"

PersistenceClass::PersistenceClass()
{
	version="0.0";
}

PersistenceClass::~PersistenceClass(){}

 void PersistenceClass::save(PObject *o){
        qDebug("PersistenceClass::save(PObject *)");
	Database::getInstance()->save(o);
}


/*!
    \fn PersistenceClass::getVersion()
 */
string PersistenceClass::getVersion()
{
    return version;
}


/*!
    \fn PersistenceClass::deleteObject(PObject *o)
 */
void PersistenceClass::deleteObject(PObject *o)
{
    qDebug("PersistenceClass::deleteObject(PObject *)");
    Database::getInstance()->deleteObject(o);
}
