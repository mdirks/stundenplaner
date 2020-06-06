#ifndef SQLITE_H
#define SQLITE_H

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

class SQLite : public Database  {
public:
    SQLite();
    virtual ~SQLite();

    void save(PObject* object);
    void save(PCollection* collection);
    void save(PTree *tr);
    void deleteObject(PObject *object);

    PObject* create(string className);
    PObject* create(PersistenceClass *persObj);

    void createTable(QString tableName, QStringList columns);
    QStringList describeTable(QString tableName) override;
    bool addColumn(QString tableName, QString columnDescription) override;

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

#endif // SQLITE_H
