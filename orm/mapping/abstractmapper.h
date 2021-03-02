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
#ifndef ABSTRACTMAPPER_H
#define ABSTRACTMAPPER_H

#include <string>
#include <list>
#include <map>

#include "../persistence/pobject.h"
#include "../persistence/persistenceclass.h"
#include "mappedobject.h"
#include "abstractassociation.h"
#include "reference.h"
#include "property.h"
#include "abstractassociation.h"
#include "mappingeventsource.h"

using namespace std;


/**
@author Marcus Dirks
*/
class AbstractMapper : public PersistenceClass, public MappingEventSource {

friend class MappingControler;

public:
    AbstractMapper();

    ~AbstractMapper();
    //string getVersion();


    
    static MappedObject*  create(AbstractMapper *mapper);
    MappedObject* create();
    MappedObject* getSingletonInstance();

    //list<PObject*> *findAssociates(string asc_name, int pri_id);
    PObject* findReference(string ref_name, int pri_id);
    void deleteReference(string ref_name, int pri_id);
    list<PObject*>* find_gen();
    string getName();
    void remove(PObject *mo);
    void reset();
    list<AbstractAssociation*>* getAssociations();
    
    
    //void save(MappedObject *realSubject);
    
protected:
	
	//list<PObject*> *findAssociation(int pri_id, string table,  string pri_col, string asc_col, string asc_class);
	void saveAssociation(int pri_id, string table,  string pri_col, string asc_col, list<PObject*> *list_asc);
        void saveReference(int pri_id, string table,  string pri_col, string asc_col, PObject *obj_asc);
      //list<Association*> getAssociations();
    list<Reference*> getReferences();
    list<Property*> getProperties();
	//list<Association*> *getAssociations();


private:
    bool createTable();
    bool createMainTable();
    bool adjustMainTable(); //will read columns in db and attempt to create non-existing columns
    void dropMainTable();

    bool doVersionChange(); //will adjustMainTable + handle Ass and Ref
    bool checkForExistingColumns(map<string,string> *column_map);
	
protected:
	map<string,AbstractAssociation*> mapAssociations;
	map<string,Reference*> mapReferences;
	map<string,Property*> mapProperties;
	//string version;
protected:
    void registerAssociation(AbstractAssociation *asc);

private:
	list<PObject*> *list_all;
};


// template<class Keytype, class Valuetype> list<Valuetype*>* getValueList(map<Keytype, Valuetype>* m){
// 	list<Valuetype*>* result = new list<Valuetype*>();
// 	for(map<Keytype,Valuetype>::iterator it = m->begin(); it!=m->end(); it++)
// 	{
// 		result->push_back((*it)->second);
// 	}
// 	return result;
// }
#endif
