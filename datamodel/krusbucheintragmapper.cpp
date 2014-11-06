// 
 // C++ Implementation: krusbucheintragmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "krusbucheintragmapper.h"
 #include "services/utils/utils.h"
 #include "krusbucheintrag.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 krusbucheintragmapper* krusbucheintragmapper::instance=0;
 
 krusbucheintragmapper* krusbucheintragmapper::getInstance()
 {
 	if(!instance){
 		instance=new krusbucheintragmapper();
 	}
 	return instance;
 }


 krusbucheintragmapper::krusbucheintragmapper()
  {
 	version = "0.11";
	columns = new string[5];
 	columnTypes = new string[5];
 	columns[0] = "stunde";
 	columnTypes[0] = "varchar(30)";
	mapProperties["stunde"] = new Property("stunde");
	columns[1] = "eintrag";
 	columnTypes[1] = "text";
	mapProperties["eintrag"] = new Property("eintrag");
	columns[2] = "bemerkung";
 	columnTypes[2] = "text";
	mapProperties["bemerkung"] = new Property("bemerkung");
	columns[3] = "details";
 	columnTypes[3] = "text";
	mapProperties["details"] = new Property("details");
	columns[4] = "datum";
 	columnTypes[4] = "varchar(30)";
	mapProperties["datum"] = new Property("datum");
mapReferences["Kursbuch"] = new Reference("krusbucheintrag","datamodel/kursbuch");
mapReferences["StundenplanEintrag"] = new Reference("krusbucheintrag","datamodel/stundenplaneintrag");
}


krusbucheintragmapper::~krusbucheintragmapper(){}


 PObject* krusbucheintragmapper::createNewObject()
 {
     return new krusbucheintrag();
 }


 krusbucheintrag* krusbucheintragmapper::create()
 {
     return  (krusbucheintrag*) AbstractMapper::create( krusbucheintragmapper::getInstance() );
 }


 string krusbucheintragmapper::getTableName()
 {
     return string("krusbucheintrag");
 }
 
 string krusbucheintragmapper::getClassName()
 {
 	return string("krusbucheintrag");
 }
 
 string* krusbucheintragmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* krusbucheintragmapper::getColumns()
 {
 	return columns;
 }
 
 int krusbucheintragmapper::getColumnCount()
 {
     return 5;
 }


 string* krusbucheintragmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[5];  
 	krusbucheintrag *o = (krusbucheintrag*) realSubject;
	values[0] = to_string(o->getStunde());
	values[1] = to_string(o->getEintrag());
	values[2] = to_string(o->getBemerkung());
	values[3] = to_string(o->getDetails());
	values[4] = to_string(o->getDatum());
return values;
 }


 void krusbucheintragmapper::save(){
qWarning("krusbucheintrag: save() not implemented");
}

void krusbucheintragmapper::save(PObject *realSubject)
{
 	krusbucheintrag *o = (krusbucheintrag*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	mapReferences[ "Kursbuch" ] -> save(realSubject, (PObject*) o->getKursbuch());
	mapReferences[ "StundenplanEintrag" ] -> save(realSubject, (PObject*) o->getStundenplanEintrag());
}


void krusbucheintragmapper::init(PObject* inito, Variant *res)
 {
 	krusbucheintrag *o = (krusbucheintrag*) inito;
	o->setStunde( res[0].asstring());
 	o->setEintrag( res[1].asstring());
 	o->setBemerkung( res[2].asstring());
 	o->setDetails( res[3].asstring());
 	o->setDatum( res[4].asQDate());
 	inito->init();
}


 list<krusbucheintrag *>*krusbucheintragmapper::find() 
 {
 	return (list <krusbucheintrag*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* krusbucheintragmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "krusbucheintrag" ); 
	entry->addProperty( new StringProperty<krusbucheintrag>("Name", "string", &krusbucheintrag::getName, &krusbucheintrag::setName, false) );
	entry->addProperty( new StringProperty< krusbucheintrag >( "Stunde" , "string", &krusbucheintrag::getStunde, &krusbucheintrag::setStunde, false ) );
	entry->addProperty( new StringProperty< krusbucheintrag >( "Eintrag" , "string", &krusbucheintrag::getEintrag, &krusbucheintrag::setEintrag, true ) );
	entry->addProperty( new StringProperty< krusbucheintrag >( "Bemerkung" , "string", &krusbucheintrag::getBemerkung, &krusbucheintrag::setBemerkung, true ) );
	entry->addProperty( new StringProperty< krusbucheintrag >( "Details" , "string", &krusbucheintrag::getDetails, &krusbucheintrag::setDetails, true ) );
	entry->addProperty( new DateProperty< krusbucheintrag> ( "Datum", "QDate" , &krusbucheintrag::getDatum, &krusbucheintrag::setDatum ) ); 
	entry->addProperty( new PObjectProperty<kursbuch,krusbucheintrag>( "Kursbuch" , "kursbuch", &krusbucheintrag::getKursbuch,&krusbucheintrag::setKursbuch ) ); 
	entry->addProperty( new PObjectProperty<stundenplaneintrag,krusbucheintrag>( "StundenplanEintrag" , "stundenplaneintrag", &krusbucheintrag::getStundenplanEintrag,&krusbucheintrag::setStundenplanEintrag ) ); 
	return entry;
 }
