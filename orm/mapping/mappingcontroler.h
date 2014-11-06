//
// C++ Interface: %{MODULE}
//
// Description: 
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef MAPPINGCONTROLER_H
#define MAPPINGCONTROLER_H

#include "../persistence/pobject.h"

#include <map>
#include <list>

#include <qstring.h>

#include "abstractmapper.h"
#include "mappingeventlistener.h"

using namespace std;

/**
@author Marcus Dirks
*/
class MappingControler{
public:
    static MappingControler* getInstance();
    void registerPersistentClass(AbstractMapper *mapper);
    AbstractMapper* getMapperByName(string className);
    PObject* create(string className);
    bool initNewDatabase(string dbName);
    list<AbstractMapper*> *getRegisteredClasses();
    bool isOpen();
    static void setDatabaseName(QString databaseName);
    void addMappingEventListener(MappingEventListener *listener);
    
    
private:
    MappingControler();
    ~MappingControler();
    
    QString getCurrentVersion(QString className);
    //void writeVersions();
    void createAdministrativTables();
    void registerPersistentClassWithDatabase(AbstractMapper *mapper);

 private:
     static MappingControler *instance;
     //map<QString,QString> mapVersions;
     list<AbstractMapper*> *listRegisteredMappers;
     list<MappingEventListener*> *list_listener;
};

#endif
