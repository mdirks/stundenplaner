/***************************************************************************
                          persistenceclass.h  -  description
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

#ifndef PERSISTENCECLASS_H
#define PERSISTENCECLASS_H

#include <string>

#include "variant.h"

//#include "pobject.h"
//#include "database.h"


using namespace std;
/**
  *@author Marcus Dirks
  */

class PObject;

class PersistenceClass {
public: 
	PersistenceClass();
	virtual ~PersistenceClass();

	virtual string* getColumns() = 0;
    virtual string*  getColumnTypes()=0;
	virtual string* getValues(PObject *realSubject) =0;
	virtual string  getTableName()=0;
	virtual int getColumnCount() =0;
	virtual string getClassName()=0;
	virtual void init(PObject* o, Variant *res) = 0;
  
  	virtual void save(){qWarning("PersistenceClass: save() not yet implemented");}
  	virtual void save(PObject *realSubject);
  	virtual PObject* createNewObject() = 0;
    	virtual string getVersion();
    virtual void deleteObject(PObject *o);
	
protected: 
	string version;
};

#endif

