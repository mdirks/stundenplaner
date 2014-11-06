// 
 // C++ Implementation: krankmeldungmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "krankmeldungmapper.h"
 #include "services/utils/utils.h"
 #include "krankmeldung.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 krankmeldungmapper* krankmeldungmapper::instance=0;
 
 krankmeldungmapper* krankmeldungmapper::getInstance()
 {
 	if(!instance){
 		instance=new krankmeldungmapper();
 	}
 	return instance;
 }


 krankmeldungmapper::krankmeldungmapper()
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


krankmeldungmapper::~krankmeldungmapper(){}


 PObject* krankmeldungmapper::createNewObject()
 {
     return new krankmeldung();
 }


 krankmeldung* krankmeldungmapper::create()
 {
     return  (krankmeldung*) AbstractMapper::create( krankmeldungmapper::getInstance() );
 }


 string krankmeldungmapper::getTableName()
 {
     return string("krankmeldung");
 }
 
 string krankmeldungmapper::getClassName()
 {
 	return string("krankmeldung");
 }
 
 string* krankmeldungmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* krankmeldungmapper::getColumns()
 {
 	return columns;
 }
 
 int krankmeldungmapper::getColumnCount()
 {
     return 2;
 }


 string* krankmeldungmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[2];  
 	krankmeldung *o = (krankmeldung*) realSubject;
	values[0] = to_string(o->getDatum());
	values[1] = to_string(o->getBemerkung());
return values;
 }


 void krankmeldungmapper::save(){
qWarning("krankmeldung: save() not implemented");
}

void krankmeldungmapper::save(PObject *realSubject)
{
 	krankmeldung *o = (krankmeldung*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	meldungmapper::save(realSubject);
}


void krankmeldungmapper::init(PObject* inito, Variant *res)
 {
 	krankmeldung *o = (krankmeldung*) inito;
	o->setDatum( res[0].asQDate());
 	o->setBemerkung( res[1].asstring());
 	inito->init();
}


 list<krankmeldung *>*krankmeldungmapper::find() 
 {
 	return (list <krankmeldung*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* krankmeldungmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "krankmeldung" ); 
	entry->addProperty( new StringProperty<krankmeldung>("Name", "string", &krankmeldung::getName, &krankmeldung::setName, false) );
	entry->addProperty( new DateProperty< krankmeldung> ( "Datum", "QDate" , &krankmeldung::getDatum, &krankmeldung::setDatum ) ); 
	entry->addProperty( new StringProperty< krankmeldung >( "Bemerkung" , "string", &krankmeldung::getBemerkung, &krankmeldung::setBemerkung, true ) );
	entry->registerBase( "meldung" );
	return entry;
 }
