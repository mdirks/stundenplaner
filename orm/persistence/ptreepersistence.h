#ifndef PTREEPERSISTENCE_H
#define PTREEPERSISTENCE_H

#include "persistenceclass.h"
#include "ptree.h"
#include <string>

using namespace std;

class PObject;

class PTreePersistence : public PersistenceClass
{
public:
    PTreePersistence();

    static PTreePersistence* getInstance();

    ~PTreePersistence();

    string getTableName();
    string getClassName();
    string* getColumnTypes();
    string* getColumns();
    string* getValues(PObject* realSubject);
    int getColumnCount();
    //void save();
    void save(PTree *realSubject);
    PObject* createNewObject();
    void init(PObject* o, Variant* res);

private:
    static PTreePersistence *instance;
    string *columns, *columnTypes;

};

#endif // PTREEPERSISTENCE_H
