//
// C++ Interface: pcollectionpersistence
//
// Description: 
//
//
// Author: Marcus Dirks <mopp@suse>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef PCOLLECTIONPERSISTENCE_H
#define PCOLLECTIONPERSISTENCE_H

#include <string>

#include "persistenceclass.h"
#include "pcollection.h"
#include "variant.h"

using namespace std;

class PObject;

/**
@author Marcus Dirks
*/
class PCollectionPersistence : public PersistenceClass
{
public:
    static PCollectionPersistence* getInstance();
    ~PCollectionPersistence();
    
    string getTableName();
    string getClassName();
    string* getColumnTypes();
    string* getColumns();
    string* getValues(PObject* realSubject);
    int getColumnCount();
    //void save();
    void save(PCollection *realSubject);
    PObject* createNewObject();
    void init(PObject* o, Variant* res);
    
private:
	PCollectionPersistence();    
    void checkTable();


private:
	static PCollectionPersistence *instance;
	string *columns, *columnTypes;

};

#endif
