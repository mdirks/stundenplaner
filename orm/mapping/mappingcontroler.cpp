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

        /* don't do this every time !? MappingControler should be valid without an active DB
        if(Database::getInstance()->isOpen()){
			createAdministrativTables();
		} else {
            qDebug() << "MappingControler(): Database is closed()";
		}	
        */
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
        //list_listener = new list<MappingEventListener*>();
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
    mapper->addMappingEventListener(this);
    if(Database::getInstance()->isOpen()){		
	    registerPersistentClassWithDatabase(mapper);
    } else {
        report(QString("MappingControler::registerPersistentClass : database closed, failed for %1").arg(mapper->getClassName().c_str()).toStdString());
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

    if( isVersion.isEmpty()){
        bool docreate = ask(QString("Could not find version for %1 - probably new!?\n Create table? ").arg(qClassName).toStdString());
        if(docreate){
            if(mapper->createTable()){
                db->registerPersistentClass(mapper, mapper->getVersion());

            } else {
                bool dodrop = ask(QString("Could not find version for %1 - probably new!?\n Create table? ").arg(qClassName).toStdString());
                if(dodrop){
                    mapper->dropMainTable();
                    mapper->createTable();
                }
            }
            db->registerVersion(mapper, mapper->getVersion());





        }
    } else if( version != isVersion){
        /*
        bool doversionchange=true;
        for(list<MappingEventListener*>::iterator it = list_listener->begin(); it!= list_listener->end(); it++){
            doversionchange = doversionchange & (*it)->versionChangeRequested(className);
        }
        */
       bool doversionchange=requestVersionChange(className);
        if(doversionchange){
            if(mapper->doVersionChange()){
                db->registerPersistentClass(mapper, mapper->getVersion());
                db->registerVersion(mapper, mapper->getVersion());
            } else {
                report(QString("Version changed failed for %1").arg(className.c_str()).toStdString());
            }
         } else {
                report(QString("Version change denied for %1").arg(className.c_str()).toStdString());
         }
    } else {
		db->registerPersistentClass(mapper,mapper->getVersion());
    }

    
    
    
    
    
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
    } else { // new class or older database layout
		return QString();
		//return mapVersions[className];
	}
}

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

bool MappingControler::checkAdministrativTables()
{
    bool res=true;

    QSqlQuery q1("select * from versions");
    res = res & q1.isActive();

    QSqlQuery q2("select * from admin");
    res = res & q2.isActive();

    QSqlQuery q3("select * from idtoname");
    res = res & q3.isActive();

    return res;
}

void MappingControler::checkForOldstyleDb()
{
    QSqlQuery q("select * from idtoname where name LIKE 'PlatzCanvasItem'");
    if(q.isActive() && q.isValid()) qDebug() << "Found old style DB -- correcting";
    {
        QSqlQuery q1("update idtoname set name='PlatzGraphicsItem' where name LIKE 'PlatzCanvasItem'");
        if(!q1.isActive()) qDebug() << "WARNING: Failed to correct PlatzCanvasItem";

        QSqlQuery q2("update idtoname set name='PObjectGraphicsItem' where name LIKE 'PObjectCanvasItem'");
        if(!q2.isActive()) qDebug() << "WARNING: Failed to correct PObjectCanvasItem";

        QSqlQuery q3("rename table pobjectcanvasitem to pobjectgraphicsitem");
        if(!q3.isActive()) qDebug() << "WARNING: Failed to rename table pobjectcanvasitem";

        QSqlQuery q4("rename table platzcanvasitem to platzgraphicsitem");
        if(!q4.isActive()) qDebug() << "WARNING: Failed to rename table platzcanvasitem";

        QSqlQuery q5("rename table PObjectCanvasItem_PObject to PObjectGraphicsItem_PObject");
        if(!q5.isActive()) qDebug() << "WARNING: Failed to rename table platzcanvasitem";

        QSqlQuery q6("rename table PlatzCanvasItem_platz to PlatGraphicsItem_platz");
        if(!q6.isActive()) qDebug() << "WARNING: Failed to rename table platzcanvasitem";

        QSqlQuery q7("rename table schultagcanvasitem to schultaggraphicsitem");
        if(!q7.isActive()) qDebug() << "WARNING: Failed to rename table platzcanvasitem";

        QSqlQuery q8("ALTER TABLE PObjectGraphicsItem_PObject CHANGE PObjectCanvasItem_id PObjectGraphicsItem_id int(11)");
        if(!q8.isActive()) qDebug() << "WARNING: Failed to rename table platzcanvasitem";

    }

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

PObject* MappingControler::loadById(int id)
{
    return Database::getInstance()->loadObjectById(id);
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
void MappingControler::setActiveDatabase(QString databaseName)
{
    Database::setDatabaseName(databaseName);
    if(checkDatabase()){
        //createAdministrativTables(); Should not be necessary - lets assume database is valid
        qDebug() << "MappingControler(): check OK";
    } else {
        if(ask("Database invalid - init new ?")){
            initNewDatabase(databaseName.toStdString());
            if(checkDatabase()){
                qDebug() << "MappingControler(): init new ok";
            } else {
                qDebug() << "MappingControler(): init new FAILED";
            }
        } else {
            qDebug() << "MappingControler(): Database is closed()";
        }
    }
}

bool MappingControler::checkDatabase()
{
    bool res=true;
    res=res & Database::getInstance()->isOpen();

    res = res & checkAdministrativTables();

    return res;
}

