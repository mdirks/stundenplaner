// 
 // C++ Implementation: stundenbewertungenmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "stundenbewertungenmapper.h"
 #include "services/utils/utils.h"
 #include "stundenbewertungen.h"
#include "orm/persistence/database.h"
 #include "orm/mapping/property.h"

 stundenbewertungenmapper* stundenbewertungenmapper::instance=0;
 
 stundenbewertungenmapper* stundenbewertungenmapper::getInstance()
 {
 	if(!instance){
 		instance=new stundenbewertungenmapper();
 	}
 	return instance;
 }


 stundenbewertungenmapper::stundenbewertungenmapper()
  {
 	version = "0.1";
	columns = new string[0];
 	columnTypes = new string[0];
 asc_Stundenbewertungen = new Association<stundenbewertungen, stundenbewertung>("stundenbewertungen_stundenbewertung","stundenbewertungen_id","stundenbewertung_id","stundenbewertung", &stundenbewertungen::addToStundenbewertungen, &stundenbewertungen::deleteFromStundenbewertungen);
mapAssociations["Stundenbewertungen"] = asc_Stundenbewertungen;
registerAssociation( asc_Stundenbewertungen);
}


stundenbewertungenmapper::~stundenbewertungenmapper(){}


 PObject* stundenbewertungenmapper::createNewObject()
 {
     return new stundenbewertungen();
 }


 stundenbewertungen* stundenbewertungenmapper::create()
 {
     return  (stundenbewertungen*) AbstractMapper::create( stundenbewertungenmapper::getInstance() );
 }


 string stundenbewertungenmapper::getTableName()
 {
     return string("stundenbewertungen");
 }
 
 string stundenbewertungenmapper::getClassName()
 {
 	return string("stundenbewertungen");
 }
 
 string* stundenbewertungenmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* stundenbewertungenmapper::getColumns()
 {
 	return columns;
 }
 
 int stundenbewertungenmapper::getColumnCount()
 {
     return 0;
 }


 string* stundenbewertungenmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	stundenbewertungen *o = (stundenbewertungen*) realSubject;
return values;
 }


 void stundenbewertungenmapper::save(){
qWarning("stundenbewertungen: save() not implemented");
}

void stundenbewertungenmapper::save(PObject *realSubject)
{
 	stundenbewertungen *o = (stundenbewertungen*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Stundenbewertungen -> save(realSubject, o->getStundenbewertungen() );

}


void stundenbewertungenmapper::init(PObject* inito, Variant *res)
 {
 	stundenbewertungen *o = (stundenbewertungen*) inito;
	inito->init();
}


 list<stundenbewertungen *>*stundenbewertungenmapper::find() 
 {
 	return (list <stundenbewertungen*>*) Database::getInstance()->getAll(this); 
}


list<stundenbewertung*> * stundenbewertungenmapper::findStundenbewertungen(int pri_id) 
 { 
 	return asc_Stundenbewertungen ->  findAssociates( pri_id );
 	}


RepositoryEntry* stundenbewertungenmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "stundenbewertungen" ); 
	entry->addProperty( new StringProperty<stundenbewertungen>("Name", "string", &stundenbewertungen::getName, &stundenbewertungen::setName, false) );
	entry->addProperty( new CollectionPropertyImpl<stundenbewertung,stundenbewertungen>( "Stundenbewertungen" , "stundenbewertung", &stundenbewertungen::getStundenbewertungen, &stundenbewertungen::addToStundenbewertungen, &stundenbewertungen::deleteFromStundenbewertungen  ) ); 
	return entry;
 }
