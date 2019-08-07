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
#include <QSqlQuery>
#include <QDebug>

#include "mappingcontroler.h"
#include "../persistence/database.h"



MappingControler *MappingControler::instance = 0;

MappingControler::MappingControler(){
		if(Database::getInstance()->isOpen()){
			createAdministrativTables();
		} else {
            qDebug() << "MappingControler(): Database is closed()";
		}	
		/*
		QString qs2("select * from versions");
		QSqlQuery q2(qs2);
		if(q2.isActive()){
			while(q2.next()){
				mapVersions[q2.value(0).toString()] = q2.value(1).toString();
			}
		} else {
			qWarning("Critical ! : Failed to read Version information from database !");
		}
		*/

		listRegisteredMappers = new list<AbstractMapper*>();
		list_listener = new list<MappingEventListener*>();
}
MappingControler::~MappingControler(){qDebug() << "Mapping Controler destroyed";}

/*!
    \fn MappingControler::getInstance()
 */
MappingControler* MappingControler::getInstance()
{
   if(instance == 0){
   	instance = new MappingControler();
   }
    return instance;
}


void MappingControler::registerPersistentClass(AbstractMapper *mapper)
{
    listRegisteredMappers->push_back(mapper);
    if(Database::getInstance()->isOpen()){		
	    registerPersistentClassWithDatabase(mapper);
    } else {
        qDebug() << QString("MappingControler::registerPersistentClass : database closed, failed for %1").arg(mapper->getClassName().c_str());
    }

}

void MappingControler::registerPersistentClassWithDatabase(AbstractMapper *mapper)
{
    Database *db = Database::getInstance();
    
    string className = mapper->getClassName();
    QString qClassName(className.c_str());
    
    //mapPersistentClasses[className]=po;
    QString version = mapper->getVersion().c_str();
    QString isVersion = getCurrentVersion(qClassName);

    
    if( version != isVersion){
	bool doversionchange=true;    
	for(list<MappingEventListener*>::iterator it = list_listener->begin(); it!= list_listener->end(); it++){
		doversionchange = doversionchange & (*it)->versionChangeRequested(className);
	}
        if(doversionchange){
        qDebug() << QString("Going to (re)create table for class : %1").arg(qClassName);
	
	    	mapper->createTable();
		db->registerPersistentClass(mapper, mapper->getVersion());
		db->registerVersion(mapper, mapper->getVersion());
	} else {
        qDebug() << QString("!!! --- Versionchange denied");
	}
    } else {
		db->registerPersistentClass(mapper,mapper->getVersion());
    }

    
    
    
    
    
    //qDebug(QString("MappingControler::registerPersistentClassWithDatabase: Registered : ").append(mapper->getClassName()));
    
    
}

bool MappingControler::initNewDatabase(string dbName)
{
	//mapVersions.clear();

	if(Database::getInstance()->changeTo(dbName)){
		createAdministrativTables();
		for(list<AbstractMapper*>::iterator it=listRegisteredMappers->begin(); it!=listRegisteredMappers->end();it++){
			(*it)->reset();
			registerPersistentClassWithDatabase((*it));
		}
		return true;
	} else {
		return false;
	} 
}

QString MappingControler::getCurrentVersion(QString className)
{
    string version = Database::getInstance()->getCurrentVersion(className.toStdString());
	if(version != string()){
        return QString::fromStdString(version);
	} else { // older database layout
        qDebug() << "MappingControler::getCurrentVersion : WARNING : database cannot provide version";
		return QString();
		//return mapVersions[className];
	}
}

/*
void MappingControler::writeVersions()
{
	QString qs("delete from versions;");
	QSqlQuery q(qs);
	if(!q.isActive()){qDebug("Criticla","Could not delete from versions");}

	QString qs2("insert into versions values (\"%1\",\"%2\");");
	map<QString,QString>::iterator it;
	for(it = mapVersions.begin(); it != mapVersions.end(); it++){
		QString qs2p = qs2.arg(it->first).arg(it->second);
		QSqlQuery q2(qs2p);
		if(!q2.isActive()){qDebug(QString("Critical: Could not insert into versions : %1").arg(qs2p));}
	}

}
*/

/*!
    \fn MappingControler::createAdministrativTables()
 */
void MappingControler::createAdministrativTables()
{
    
	QString qs1("create table versions (class char(50), version char(10));");
    QSqlQuery q1(qs1);
    if(!q1.isActive()) qDebug() << "appingControler::createAdministrativTables : Could not create table versions";
    
    QString qs2("create table admin (current_id int);");
    QSqlQuery q2(qs2);
    if(q2.isActive()) {
    	QString qs2a("insert into admin values (1);");
	QSqlQuery q2a(qs2a);
    if(!q2a.isActive()) qDebug() << "Failed to insert initial id";
    } else {
        qDebug() << "Could not create table admin";
    }
    
    QString qs3("create table idtoname (id int, name char(30));");
    QSqlQuery q3(qs3);
    if(!q3.isActive()) qDebug() << "Could not create table idtoname";

}


/*!
    \fn MappingControler::getMapperByName(string className)
 */
AbstractMapper* MappingControler::getMapperByName(string className)
{
   	 for(list<AbstractMapper*>::iterator it = listRegisteredMappers->begin(); it != listRegisteredMappers->end(); it++){
		AbstractMapper* mapper = (*it);
		if(mapper->getClassName() == className){
			return mapper;
		}
	}
	return 0;
}


/*!
    \fn MappingControler::create(string className)
 */
PObject* MappingControler::create(string className)
{
    PObject *o=0;

	AbstractMapper *mapper = MappingControler::getInstance()->getMapperByName(className);
	if(mapper){
		o = mapper->create();
	} else {
        qDebug() << QString("Could not get mapper for %1").arg(className.c_str());
	}

	return o;
}


/*!
    \fn MappingControler::getRegisteredClasses();
 */
list<AbstractMapper*> *MappingControler::getRegisteredClasses()
{
    return listRegisteredMappers;
}


/*!
    \fn MappingControler::isOpen()
 */
bool MappingControler::isOpen()
{
    return Database::getInstance()->isOpen();
}


/*!
    \fn MappingControler::setDatabaseName(QString databaseName)
 */
void MappingControler::setDatabaseName(QString databaseName)
{
    Database::setDatabaseName(databaseName);
}


/*!
    \fn MappingControler::addMappingEventListener(MappingEventListener *listener)
 */
void MappingControler::addMappingEventListener(MappingEventListener *listener)
{
    list_listener->push_back(listener);
}
