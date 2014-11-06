// 
 // C++ Implementation: kursbuchmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "kursbuchmapper.h"
 #include "services/utils/utils.h"
 #include "kursbuch.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 kursbuchmapper* kursbuchmapper::instance=0;
 
 kursbuchmapper* kursbuchmapper::getInstance()
 {
 	if(!instance){
 		instance=new kursbuchmapper();
 	}
 	return instance;
 }


 kursbuchmapper::kursbuchmapper()
  {
 	version = "0.61";
	columns = new string[0];
 	columnTypes = new string[0];
 asc_Eintraege = new Association<kursbuch, krusbucheintrag>("kursbuch_eintraege","kursbuch_id","eintrag_id","krusbucheintrag", &kursbuch::addToEintraege, &kursbuch::deleteFromEintraege);
mapAssociations["Eintraege"] = asc_Eintraege;
registerAssociation( asc_Eintraege);
mapReferences["Klasse"] = new Reference("kursbuch","datamodel/klasse");
mapReferences["Klausur1a"] = new Reference("kursbuch","datamodel/teilleistung" , "kl1a");
mapReferences["Klausur1b"] = new Reference("kursbuch","datamodel/teilleistung" , "kl1b");
mapReferences["Klausur2a"] = new Reference("kursbuch","datamodel/teilleistung" , "kl2a");
mapReferences["Klausur2b"] = new Reference("kursbuch","datamodel/teilleistung" , "kl2b");
mapReferences["At1"] = new Reference("kursbuch","datamodel/teilleistung" , "at1");
mapReferences["At2"] = new Reference("kursbuch","datamodel/teilleistung" , "at2");
mapReferences["G1"] = new Reference("kursbuch","datamodel/teilleistung" , "g1");
mapReferences["G2"] = new Reference("kursbuch","datamodel/teilleistung" , "g2");
}


kursbuchmapper::~kursbuchmapper(){}


 PObject* kursbuchmapper::createNewObject()
 {
     return new kursbuch();
 }


 kursbuch* kursbuchmapper::create()
 {
     return  (kursbuch*) AbstractMapper::create( kursbuchmapper::getInstance() );
 }


 string kursbuchmapper::getTableName()
 {
     return string("kursbuch");
 }
 
 string kursbuchmapper::getClassName()
 {
 	return string("kursbuch");
 }
 
 string* kursbuchmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* kursbuchmapper::getColumns()
 {
 	return columns;
 }
 
 int kursbuchmapper::getColumnCount()
 {
     return 0;
 }


 string* kursbuchmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	kursbuch *o = (kursbuch*) realSubject;
return values;
 }


 void kursbuchmapper::save(){
qWarning("kursbuch: save() not implemented");
}

void kursbuchmapper::save(PObject *realSubject)
{
 	kursbuch *o = (kursbuch*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Eintraege -> save(realSubject, o->getEintraege() );

	mapReferences[ "Klasse" ] -> save(realSubject, (PObject*) o->getKlasse());
	mapReferences[ "Klausur1a" ] -> save(realSubject, (PObject*) o->getKlausur1a());
	mapReferences[ "Klausur1b" ] -> save(realSubject, (PObject*) o->getKlausur1b());
	mapReferences[ "Klausur2a" ] -> save(realSubject, (PObject*) o->getKlausur2a());
	mapReferences[ "Klausur2b" ] -> save(realSubject, (PObject*) o->getKlausur2b());
	mapReferences[ "At1" ] -> save(realSubject, (PObject*) o->getAt1());
	mapReferences[ "At2" ] -> save(realSubject, (PObject*) o->getAt2());
	mapReferences[ "G1" ] -> save(realSubject, (PObject*) o->getG1());
	mapReferences[ "G2" ] -> save(realSubject, (PObject*) o->getG2());
}


void kursbuchmapper::init(PObject* inito, Variant *res)
 {
 	kursbuch *o = (kursbuch*) inito;
	inito->init();
}


 list<kursbuch *>*kursbuchmapper::find() 
 {
 	return (list <kursbuch*>*) Database::getInstance()->getAll(this); 
}


list<krusbucheintrag*> * kursbuchmapper::findEintraege(int pri_id) 
 { 
 	return asc_Eintraege ->  findAssociates( pri_id );
 	}


RepositoryEntry* kursbuchmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "kursbuch" ); 
	entry->addProperty( new StringProperty<kursbuch>("Name", "string", &kursbuch::getName, &kursbuch::setName, false) );
	entry->addProperty( new CollectionPropertyImpl<krusbucheintrag,kursbuch>( "Eintraege" , "krusbucheintrag", &kursbuch::getEintraege, &kursbuch::addToEintraege, &kursbuch::deleteFromEintraege  ) ); 
	entry->addProperty( new PObjectProperty<klasse,kursbuch>( "Klasse" , "klasse", &kursbuch::getKlasse,&kursbuch::setKlasse ) ); 
	entry->addProperty( new PObjectProperty<teilleistung,kursbuch>( "Klausur1a" , "teilleistung", &kursbuch::getKlausur1a,&kursbuch::setKlausur1a ) ); 
	entry->addProperty( new PObjectProperty<teilleistung,kursbuch>( "Klausur1b" , "teilleistung", &kursbuch::getKlausur1b,&kursbuch::setKlausur1b ) ); 
	entry->addProperty( new PObjectProperty<teilleistung,kursbuch>( "Klausur2a" , "teilleistung", &kursbuch::getKlausur2a,&kursbuch::setKlausur2a ) ); 
	entry->addProperty( new PObjectProperty<teilleistung,kursbuch>( "Klausur2b" , "teilleistung", &kursbuch::getKlausur2b,&kursbuch::setKlausur2b ) ); 
	entry->addProperty( new PObjectProperty<teilleistung,kursbuch>( "At1" , "teilleistung", &kursbuch::getAt1,&kursbuch::setAt1 ) ); 
	entry->addProperty( new PObjectProperty<teilleistung,kursbuch>( "At2" , "teilleistung", &kursbuch::getAt2,&kursbuch::setAt2 ) ); 
	entry->addProperty( new PObjectProperty<teilleistung,kursbuch>( "G1" , "teilleistung", &kursbuch::getG1,&kursbuch::setG1 ) ); 
	entry->addProperty( new PObjectProperty<teilleistung,kursbuch>( "G2" , "teilleistung", &kursbuch::getG2,&kursbuch::setG2 ) ); 
	return entry;
 }
