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
class MappingControler : public MappingEventSource
{
public:
    static MappingControler* getInstance();
    bool registerPersistentClass(AbstractMapper *mapper);
    AbstractMapper* getMapperByName(string className);
    PObject* create(string className);
    bool initNewDatabase(string dbName);
    list<AbstractMapper*> *getRegisteredClasses();
    bool isOpen();
    static void setDatabaseName(QString databaseName);
    void addMappingEventListener(MappingEventListener *listener);
    
    void close();

private:
    MappingControler();
    ~MappingControler();
    
    QString getCurrentVersion(QString className);
    //void writeVersions();
    void createAdministrativTables();
    bool registerPersistentClassWithDatabase(AbstractMapper *mapper);

 private:
     static MappingControler *instance;
     //map<QString,QString> mapVersions;
     list<AbstractMapper*> *listRegisteredMappers;
     list<MappingEventListener*> *list_listener;
};

#endif
