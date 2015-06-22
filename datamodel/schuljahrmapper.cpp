// 
 // C++ Implementation: schuljahrmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "schuljahrmapper.h"
 #include "services/utils/utils.h"
 #include "schuljahr.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 schuljahrmapper* schuljahrmapper::instance=0;
 
 schuljahrmapper* schuljahrmapper::getInstance()
 {
 	if(!instance){
 		instance=new schuljahrmapper();
 	}
 	return instance;
 }


 schuljahrmapper::schuljahrmapper()
  {
 	version = "0.4";
	columns = new string[2];
 	columnTypes = new string[2];
 	columns[0] = "von";
 	columnTypes[0] = "varchar(30)";
	mapProperties["von"] = new Property("von");
	columns[1] = "bis";
 	columnTypes[1] = "varchar(30)";
	mapProperties["bis"] = new Property("bis");
asc_Klassen = new Association<schuljahr, klasse>("schuljahr_klasse","schuljahr_id","klasse_id","klasse", &schuljahr::addToKlassen, &schuljahr::deleteFromKlassen);
mapAssociations["Klassen"] = asc_Klassen;
registerAssociation( asc_Klassen);
asc_Ferien = new Association<schuljahr, ferien>("schuljahr_ferien","schuljahr_id","ferien_id","ferien", &schuljahr::addToFerien, &schuljahr::deleteFromFerien);
mapAssociations["Ferien"] = asc_Ferien;
registerAssociation( asc_Ferien);
mapReferences["Stundenplana"] = new Reference("schuljahr","datamodel/stundenplan");
}


schuljahrmapper::~schuljahrmapper(){}


 PObject* schuljahrmapper::createNewObject()
 {
     return new schuljahr();
 }


 schuljahr* schuljahrmapper::create()
 {
     return  (schuljahr*) AbstractMapper::create( schuljahrmapper::getInstance() );
 }


 string schuljahrmapper::getTableName()
 {
     return string("schuljahr");
 }
 
 string schuljahrmapper::getClassName()
 {
 	return string("schuljahr");
 }
 
 string* schuljahrmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* schuljahrmapper::getColumns()
 {
 	return columns;
 }
 
 int schuljahrmapper::getColumnCount()
 {
     return 2;
 }


 string* schuljahrmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[2];  
 	schuljahr *o = (schuljahr*) realSubject;
	values[0] = to_string(o->getVon());
	values[1] = to_string(o->getBis());
return values;
 }


 void schuljahrmapper::save(){
qWarning("schuljahr: save() not implemented");
}

void schuljahrmapper::save(PObject *realSubject)
{
 	schuljahr *o = (schuljahr*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Klassen -> save(realSubject, o->getKlassen() );

	asc_Ferien -> save(realSubject, o->getFerien() );

	mapReferences[ "Stundenplana" ] -> save(realSubject, (PObject*) o->getStundenplana());
}


void schuljahrmapper::init(PObject* inito, Variant *res)
 {
 	schuljahr *o = (schuljahr*) inito;
	o->setVon( res[0].asQDate());
 	o->setBis( res[1].asQDate());
 	inito->init();
}


 list<schuljahr *>*schuljahrmapper::find() 
 {
 	return (list <schuljahr*>*) Database::getInstance()->getAll(this); 
}


list<klasse*> * schuljahrmapper::findKlassen(int pri_id) 
 { 
 	return asc_Klassen ->  findAssociates( pri_id );
     }


list<klasse*> * schuljahrmapper::findKlassen(int pri_id,string prop,string value) 
         { 
             return asc_Klassen ->  findAssociates( pri_id,prop,value);
             }


list<ferien*> * schuljahrmapper::findFerien(int pri_id) 
 { 
 	return asc_Ferien ->  findAssociates( pri_id );
     }


list<ferien*> * schuljahrmapper::findFerien(int pri_id,string prop,string value) 
         { 
             return asc_Ferien ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* schuljahrmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "schuljahr" ); 
	entry->addProperty( new StringProperty<schuljahr>("Name", "string", &schuljahr::getName, &schuljahr::setName, false) );
	entry->addProperty( new DateProperty< schuljahr> ( "Von", "QDate" , &schuljahr::getVon, &schuljahr::setVon ) ); 
	entry->addProperty( new DateProperty< schuljahr> ( "Bis", "QDate" , &schuljahr::getBis, &schuljahr::setBis ) ); 
	entry->addProperty( new CollectionPropertyImpl<klasse,schuljahr>( "Klassen" , "klasse", &schuljahr::getKlassen, &schuljahr::addToKlassen, &schuljahr::deleteFromKlassen  ) ); 
	entry->addProperty( new CollectionPropertyImpl<ferien,schuljahr>( "Ferien" , "ferien", &schuljahr::getFerien, &schuljahr::addToFerien, &schuljahr::deleteFromFerien  ) ); 
	entry->addProperty( new PObjectProperty<stundenplan,schuljahr>( "Stundenplana" , "stundenplan", &schuljahr::getStundenplana,&schuljahr::setStundenplana ) ); 
	return entry;
 }
