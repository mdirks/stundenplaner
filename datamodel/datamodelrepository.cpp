//
// C++ Implementation: datamodelrepository
//
// Description: 
//
//
// Author: Marcus Dirks <mopp@suse>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "datamodelrepository.h"
//#include "stundepersistence.h"
//#include "opopersistence.h"
#include "orm/mapping/mappingcontroler.h"
#include "orm/mapping/abstractmapper.h"
#include "stundemapper.h"
#include "opomapper.h"
#include "reihemapper.h"
#include "materialmapper.h"
#include "themamapper.h"
#include "notizmapper.h"
#include "klassemapper.h"
#include "tagmapper.h"
#include "kursbuchmapper.h"
#include "krusbucheintragmapper.h"
#include "stundenplanmapper.h"
#include "stundenplaneintragmapper.h"
#include "stundenplantemplateeintragmapper.h"
#include "schultagmapper.h"
#include "unterrichtsthemamapper.h" 
#include "schuelermapper.h"
#include "notemapper.h"
#include "sitzplanmapper.h"
#include "platzmapper.h"
#include "fehlzeitmapper.h"
#include "stundenbewertungmapper.h"
#include "lernkartemapper.h"
#include "lernkartensatzmapper.h"
#include "klausurmapper.h"
#include "teilleistungmapper.h"
#include "schuljahrmapper.h"
#include "ferientagmapper.h"
#include "ferienmapper.h"
#include "teilleistungberechnetmapper.h"
#include "fehlzeitmeldungmapper.h"
#include "tutoriummapper.h"
#include "krankmeldungmapper.h"
#include "meldungmapper.h"
#include "lektueremapper.h"
#include "lektuerenotizmapper.h"
#include "notizsatzmapper.h"
#include "materialsatzmapper.h"

#include "orm/persistence/database.h"
#include "orm/repository/repository.h"
#include "orm/repository/repositoryenabled.h"




DataModelRepository* DataModelRepository::instance=0;


DataModelRepository::DataModelRepository()
{
	listMappers = new list<AbstractMapper*>();
	listMappers->push_back(notizholdermapper::getInstance());
	listMappers->push_back(stundemapper::getInstance());
	listMappers->push_back(opomapper::getInstance());
	listMappers->push_back(reihemapper::getInstance());
	listMappers->push_back(materialmapper::getInstance());
	listMappers->push_back(themamapper::getInstance());
	listMappers->push_back(unterrichtsthemamapper::getInstance());
	listMappers->push_back(notizmapper::getInstance());
	listMappers->push_back(klassemapper::getInstance());
	listMappers->push_back(tagmapper::getInstance());
	listMappers->push_back(kursbuchmapper::getInstance());
	listMappers->push_back(krusbucheintragmapper::getInstance());
	listMappers->push_back(stundenplanmapper::getInstance());
	listMappers->push_back(stundenplaneintragmapper::getInstance());
	listMappers->push_back(stundenplantemplateeintragmapper::getInstance());
	listMappers->push_back(schultagmapper::getInstance());
	listMappers->push_back(schuelermapper::getInstance());
 	listMappers->push_back(notemapper::getInstance());
	listMappers->push_back(sitzplanmapper::getInstance());
	listMappers->push_back(platzmapper::getInstance());
	listMappers->push_back(fehlzeitmapper::getInstance());
	listMappers->push_back(stundenbewertungmapper::getInstance());
	listMappers->push_back(lernkartemapper::getInstance());
	listMappers->push_back(lernkartensatzmapper::getInstance());
	listMappers->push_back(klausurmapper::getInstance());
	listMappers->push_back(teilleistungmapper::getInstance());
	listMappers->push_back(schuljahrmapper::getInstance());
	listMappers->push_back(ferientagmapper::getInstance());
	listMappers->push_back(ferienmapper::getInstance());
	listMappers->push_back(teilleistungberechnetmapper::getInstance());
	listMappers->push_back(fehlzeitmeldungmapper::getInstance());
	listMappers->push_back(krankmeldungmapper::getInstance());
	listMappers->push_back(meldungmapper::getInstance());
	
	listMappers->push_back(tutoriummapper::getInstance());
    listMappers->push_back(lektueremapper::getInstance());
    listMappers->push_back(lektuerenotizmapper::getInstance());
    listMappers->push_back(notizsatzmapper::getInstance());
    listMappers->push_back(materialsatzmapper::getInstance());

	
	
	for(list<AbstractMapper*>::iterator it = listMappers->begin();
		it!=listMappers->end(); ++it)
	{
		MappingControler::getInstance()->registerPersistentClass(*it);
		RepositoryEnabled *re = dynamic_cast<RepositoryEnabled*>(*it);
		if(re){
			Repository::getInstance()->addRepositoryEntry(re->getRepositoryEntry());
		}
	}
}


DataModelRepository::~DataModelRepository()
{

}




/*!
    \fn DataModelRepository::getInstance()
 */
DataModelRepository* DataModelRepository::getInstance()
{
    	if(!instance)
	{
		instance= new DataModelRepository();
	}
	return instance;
}


/*!
    \fn DataModelRepository::getPersistentClasses();
 */
list<AbstractMapper*>* DataModelRepository::getPersistentClasses()
{
    return listMappers;
}




/*!
    \fn DataModelRepository::getAll(string className)
 */
/*
list<PObject*>* DataModelRepository::getAll(string className)
{
    Database *db = Database::getInstance();
    return db->getAll(PersistenceClass);
}
*/


/*!
    \fn DataModelRepository::getMapperByName(string className)
 */
AbstractMapper* DataModelRepository::getMapperByName(string className)
{
    	return MappingControler::getInstance()->getMapperByName(className);
	/*
	for(list<AbstractMapper*>::iterator it = listMappers->begin(); it != listMappers->end(); it++){
		AbstractMapper* mapper = (*it);
		if(mapper->getClassName() == className){
			return mapper;
		}
	}
	return 0;
	*/
}


