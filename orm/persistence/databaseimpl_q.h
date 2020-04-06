/***************************************************************************
                          databaseimpl_q.h  -  description
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

#ifndef DATABASEIMPL_Q_H
#define DATABASEIMPL_Q_H

#include "database.h"
#include <vector>
#include <list>

#include "pobject.h"	
#include <QSqlDatabase>



#define USER "root"
#define PASSWD "duodisc"

#include "pobject.h"
#include <string>

using namespace std;

/**
  *@author Marcus Dirks
  */

class DatabaseImpl_Q : public Database  {
public: 
	DatabaseImpl_Q();
	virtual ~DatabaseImpl_Q();

	void save(PObject* object);
	void save(PCollection* collection);
	void deleteObject(PObject *object);
	
  	 PObject* create(string className);
	 PObject* create(PersistenceClass *persObj);
	 virtual PCollection* createCollection();
   
   	//list<PObject*>* getAll(string className);
	list<PObject*>* getAll(PersistenceClass *persObj);
	PObject* load(string className, int id);
	bool isOpen();
	
	void registerVersion(PersistenceClass *po, string version);
    	void registerPersistentClass(PersistenceClass *po,string version=string());

    void loadCollection(PCollection *col);
    PObject* loadObjectById(int id);
    bool changeTo(string db_name);
    void executeSql(string sql);
    string getCurrentVersion(string clName);

private:
    QSqlDatabase getConnection();
	string getTableName(PersistenceClass *persObj);
	//void createTable(PersistenceClass *persObj);
	
	int getNewId();
	bool tableExists(string tname);
      	bool tableExists(PersistenceClass *persObj);
    	void close();
	QString mask(QString qs);
    QString unmask(QString qs);

    void checkForOldstyleDb();
     // void writeVersions();

private:
    QSqlDatabase connection;
	list<string> tables;
	map<int,PObject*> cache;
	map<string,PersistenceClass*> mapPersistentClasses;
	//map<string,string> mapVersions;
	//map<QString,QString> mapVersions;
};

#endif
