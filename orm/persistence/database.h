/***************************************************************************
                          database.h  -  description
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

#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <map>
#include <vector>
#include <list>

#include "pobject.h"
#include "pcollection.h"
#include "ptree.h"
#include "persistenceclass.h"
#include "qstring.h"

#include <QDebug>
/**
  *@author Marcus Dirks
  */


  

class Database {
public: 

    virtual ~Database(){qDebug() << "~Database: Should not be called";}
	static Database* getInstance();
	static void setDatabaseName(QString name);
	static QString getDatabaseName();
    static void close();
    static bool changeTo(string db_name);

  	virtual void save(PObject* object) = 0;
	virtual void save(PCollection* collection) = 0;
    virtual void save(PTree* tr)=0;

    virtual PObject* create(string className) = 0;
	virtual PObject* create(PersistenceClass *persObj)=0;

    virtual void createTable(QString tableName, QStringList columns) = 0;
    //virtual PCollection* createCollection() = 0;

  	//virtual list<PObject*>* getAll(string className) = 0;
	virtual list<PObject*>* getAll(PersistenceClass *persObj) = 0;
	virtual PObject* load(string className, int id) = 0;
	
  	virtual void registerPersistentClass(PersistenceClass *po, string version=string())=0;
	virtual void registerVersion(PersistenceClass *po, string version)=0;

	virtual PObject* loadObjectById(int id)=0;

    virtual void loadCollection(PCollection* col)=0;


    virtual bool isOpen()=0;
    virtual void deleteObject(PObject *o) = 0;
    virtual void executeSql(string sql) = 0;



    virtual string getCurrentVersion(string clName) = 0;

private:
    void registerBasicTypes();

	
private:
	static Database* instance;

protected:
	static QString databasename;
	

};




#endif
