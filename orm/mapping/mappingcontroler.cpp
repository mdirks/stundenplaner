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


bool MappingControler::registerPersistentClass(AbstractMapper *mapper)
{
    if(Database::getInstance()->isOpen()){
        if(registerPersistentClassWithDatabase(mapper)){
            listRegisteredMappers->push_back(mapper);
            return true;
        }
    } else {
        qDebug() << QString("MappingControler::registerPersistentClass : database closed, failed for %1").arg(mapper->getClassName().c_str());
    }
    return false;

}

bool MappingControler::registerPersistentClassWithDatabase(AbstractMapper *mapper)
{
    Database *db = Database::getInstance();
    
    string className = mapper->getClassName();
    QString qClassName(className.c_str());
    
    //mapPersistentClasses[className]=po;
    QString version = mapper->getVersion().c_str();
    QString isVersion = getCurrentVersion(qClassName);

    
    if( version != isVersion){

        bool doversionchange=true;
        VersionChangeRequest *me=new VersionChangeRequest(qClassName);
        for(list<MappingEventListener*>::iterator it = list_listener->begin(); it!= list_listener->end(); it++){
            doversionchange = doversionchange & (*it)->consider(me);
        }
        if(doversionchange){
            qDebug() << QString("Going to adjust table for class : %1").arg(qClassName);
	
            if(mapper->checkAndAdjustTable()){
                db->registerPersistentClass(mapper, mapper->getVersion());
                db->registerVersion(mapper, mapper->getVersion());
            } else {
                qDebug() << QString("!!! --- Versionchange failed");
                return false;
            }
        } else {
            qDebug() << QString("!!! --- Versionchange denied");
            return false;
        }
    } else {
		db->registerPersistentClass(mapper,mapper->getVersion());
    }

    
    return true;
    
    
    
    //qDebug(QString("MappingControler::registerPersistentClassWithDatabase: Registered : ").append(mapper->getClassName()));
    
    
}

bool MappingControler::initNewDatabase(string dbName)
{
	//mapVersions.clear();

    if(Database::changeTo(dbName)){
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

/*!
    \fn MappingControler::createAdministrativTables()
 */
void MappingControler::createAdministrativTables()
{
    
    QString tableName("versions");
    QStringList columns;
    columns << "class char(50)" << "version char(10)";

    Database::getInstance()->createTable(tableName,columns);

    tableName="admin";
    columns.clear();
    columns << "current_id int";
    Database::getInstance()->createTable(tableName,columns);

    tableName="idtoname";
    columns.clear();
    columns << "id int, name char(30)";
    Database::getInstance()->createTable(tableName,columns);


    /*
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
    */

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
