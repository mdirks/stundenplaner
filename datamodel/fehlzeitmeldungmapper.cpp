// 
 // C++ Implementation: fehlzeitmeldungmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "fehlzeitmeldungmapper.h"
 #include "services/utils/utils.h"
 #include "fehlzeitmeldung.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 fehlzeitmeldungmapper* fehlzeitmeldungmapper::instance=0;
 
 fehlzeitmeldungmapper* fehlzeitmeldungmapper::getInstance()
 {
 	if(!instance){
 		instance=new fehlzeitmeldungmapper();
 	}
 	return instance;
 }


 fehlzeitmeldungmapper::fehlzeitmeldungmapper()
  {
 	version = "0.3";
	columns = new string[2];
 	columnTypes = new string[2];
 	columns[0] = "datum";
 	columnTypes[0] = "varchar(30)";
	mapProperties["datum"] = new Property("datum");
	columns[1] = "bemerkung";
 	columnTypes[1] = "text";
	mapProperties["bemerkung"] = new Property("bemerkung");
}


fehlzeitmeldungmapper::~fehlzeitmeldungmapper(){}


 PObject* fehlzeitmeldungmapper::createNewObject()
 {
     return new fehlzeitmeldung();
 }


 fehlzeitmeldung* fehlzeitmeldungmapper::create()
 {
     return  (fehlzeitmeldung*) AbstractMapper::create( fehlzeitmeldungmapper::getInstance() );
 }


 string fehlzeitmeldungmapper::getTableName()
 {
     return string("fehlzeitmeldung");
 }
 
 string fehlzeitmeldungmapper::getClassName()
 {
 	return string("fehlzeitmeldung");
 }
 
 string* fehlzeitmeldungmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* fehlzeitmeldungmapper::getColumns()
 {
 	return columns;
 }
 
 int fehlzeitmeldungmapper::getColumnCount()
 {
     return 2;
 }


 string* fehlzeitmeldungmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[2];  
 	fehlzeitmeldung *o = (fehlzeitmeldung*) realSubject;
	values[0] = to_string(o->getDatum());
	values[1] = to_string(o->getBemerkung());
return values;
 }


 void fehlzeitmeldungmapper::save(){
qWarning("fehlzeitmeldung: save() not implemented");
}

void fehlzeitmeldungmapper::save(PObject *realSubject)
{
 	fehlzeitmeldung *o = (fehlzeitmeldung*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	meldungmapper::save(realSubject);
}


void fehlzeitmeldungmapper::init(PObject* inito, Variant *res)
 {
 	fehlzeitmeldung *o = (fehlzeitmeldung*) inito;
	o->setDatum( res[0].asQDate());
 	o->setBemerkung( res[1].asstring());
 	inito->init();
}


 list<fehlzeitmeldung *>*fehlzeitmeldungmapper::find() 
 {
 	return (list <fehlzeitmeldung*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* fehlzeitmeldungmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "fehlzeitmeldung" ); 
	entry->addProperty( new StringProperty<fehlzeitmeldung>("Name", "string", &fehlzeitmeldung::getName, &fehlzeitmeldung::setName, false) );
	entry->addProperty( new DateProperty< fehlzeitmeldung> ( "Datum", "QDate" , &fehlzeitmeldung::getDatum, &fehlzeitmeldung::setDatum ) ); 
	entry->addProperty( new StringProperty< fehlzeitmeldung >( "Bemerkung" , "string", &fehlzeitmeldung::getBemerkung, &fehlzeitmeldung::setBemerkung, true ) );
	entry->registerBase( "meldung" );
	return entry;
 }
