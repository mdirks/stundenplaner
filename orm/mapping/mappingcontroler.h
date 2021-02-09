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
#include "mappingeventsource.h"

using namespace std;

/**
@author Marcus Dirks
*/
class MappingControler : public MappingEventSource, public MappingEventListener {
public:
    static MappingControler* getInstance();
    void registerPersistentClass(AbstractMapper *mapper);
    AbstractMapper* getMapperByName(string className);
    PObject* create(string className);
    bool initNewDatabase(string dbName);
    list<AbstractMapper*> *getRegisteredClasses();
    bool isOpen();
    void setActiveDatabase(QString databaseName);

    //Events are just relayed
    bool versionChangeRequested(string className){return requestVersionChange(className);};
    virtual bool confirm(string req){return ask(req);};
    virtual void message(string mes){report(mes);};

private:
    MappingControler();
    ~MappingControler();
    
    QString getCurrentVersion(QString className);
    //void writeVersions();
    void createAdministrativTables();
    bool checkAdministrativTables();
    void checkForOldstyleDb();
    void registerPersistentClassWithDatabase(AbstractMapper *mapper);
    bool checkDatabase();

 private:
     static MappingControler *instance;
     //map<QString,QString> mapVersions;
     list<AbstractMapper*> *listRegisteredMappers;
     //list<MappingEventListener*> *list_listener;
};

#endif
