// 
 // C++ Implementation: tutoriummapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "tutoriummapper.h"
 #include "services/utils/utils.h"
 #include "tutorium.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 tutoriummapper* tutoriummapper::instance=0;
 
 tutoriummapper* tutoriummapper::getInstance()
 {
 	if(!instance){
 		instance=new tutoriummapper();
 	}
 	return instance;
 }


 tutoriummapper::tutoriummapper()
  {
 	version = "0.1";
	columns = new string[0];
 	columnTypes = new string[0];
 asc_Fehlzeitmeldungen = new Association<tutorium, fehlzeitmeldung>("tutorium_fehlzeitmeldung","tutorium_id","fehlzeitmeldung_id","fehlzeitmeldung", &tutorium::addToFehlzeitmeldungen, &tutorium::deleteFromFehlzeitmeldungen);
mapAssociations["Fehlzeitmeldungen"] = asc_Fehlzeitmeldungen;
registerAssociation( asc_Fehlzeitmeldungen);
mapReferences["Klasse"] = new Reference("tutorium","datamodel/klasse");
}


tutoriummapper::~tutoriummapper(){}


 PObject* tutoriummapper::createNewObject()
 {
     return new tutorium();
 }


 tutorium* tutoriummapper::create()
 {
     return  (tutorium*) AbstractMapper::create( tutoriummapper::getInstance() );
 }


 string tutoriummapper::getTableName()
 {
     return string("tutorium");
 }
 
 string tutoriummapper::getClassName()
 {
 	return string("tutorium");
 }
 
 string* tutoriummapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* tutoriummapper::getColumns()
 {
 	return columns;
 }
 
 int tutoriummapper::getColumnCount()
 {
     return 0;
 }


 string* tutoriummapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	tutorium *o = (tutorium*) realSubject;
return values;
 }


 void tutoriummapper::save(){
qWarning("tutorium: save() not implemented");
}

void tutoriummapper::save(PObject *realSubject)
{
 	tutorium *o = (tutorium*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Fehlzeitmeldungen -> save(realSubject, o->getFehlzeitmeldungen() );

	mapReferences[ "Klasse" ] -> save(realSubject, (PObject*) o->getKlasse());
}


void tutoriummapper::init(PObject* inito, Variant *res)
 {
 	tutorium *o = (tutorium*) inito;
	inito->init();
}


 list<tutorium *>*tutoriummapper::find() 
 {
 	return (list <tutorium*>*) Database::getInstance()->getAll(this); 
}


list<fehlzeitmeldung*> * tutoriummapper::findFehlzeitmeldungen(int pri_id) 
 { 
 	return asc_Fehlzeitmeldungen ->  findAssociates( pri_id );
     }


list<fehlzeitmeldung*> * tutoriummapper::findFehlzeitmeldungen(int pri_id,string prop,string value) 
         { 
             return asc_Fehlzeitmeldungen ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* tutoriummapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "tutorium" ); 
	entry->addProperty( new StringProperty<tutorium>("Name", "string", &tutorium::getName, &tutorium::setName, false) );
	entry->addProperty( new CollectionPropertyImpl<fehlzeitmeldung,tutorium>( "Fehlzeitmeldungen" , "fehlzeitmeldung", &tutorium::getFehlzeitmeldungen, &tutorium::addToFehlzeitmeldungen, &tutorium::deleteFromFehlzeitmeldungen  ) ); 
	entry->addProperty( new PObjectProperty<klasse,tutorium>( "Klasse" , "klasse", &tutorium::getKlasse,&tutorium::setKlasse ) ); 
	return entry;
 }
