//
// C++ Interface: datamodelrepository
//
// Description: 
//
//
// Author: Marcus Dirks <mopp@suse>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef DATAMODELREPOSITORY_H
#define DATAMODELREPOSITORY_H

#include <list>
#include "../orm/mapping/abstractmapper.h"
#include "../orm/persistence/persistenceclass.h"
#include "../orm/persistence/pobject.h"

using namespace std;

/**
\brief Global information (Persistent classes, mappers etc.) on the Datamodel

Central repository providing acces to global information on the datamodel

\todo Make code a bit nicer

@author Marcus Dirks
*/
class DataModelRepository{
public:
    static DataModelRepository* getInstance();
    ~DataModelRepository();

   /**
	Returns a list of all persistent classes in the Datamodel
   */	
    list<AbstractMapper*>* getPersistentClasses();
    //list<PObject*>* getAll(string className);
    void registerTypesWithDatabase();
   
   /** \brief
	Given a class name find the corresponding mapper
   */
    AbstractMapper* getMapperByName(string className);
    
        
private: 
     DataModelRepository();
    

private:
    static DataModelRepository* instance;
    list<AbstractMapper*>* listMappers;

};

#endif
