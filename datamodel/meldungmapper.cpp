// 
 // C++ Implementation: meldungmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "meldungmapper.h"
 #include "services/utils/utils.h"
 #include "meldung.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 meldungmapper* meldungmapper::instance=0;
 
 meldungmapper* meldungmapper::getInstance()
 {
 	if(!instance){
 		instance=new meldungmapper();
 	}
 	return instance;
 }


 meldungmapper::meldungmapper()
  {
 	version = "0.1";
	columns = new string[2];
 	columnTypes = new string[2];
 	columns[0] = "datum";
 	columnTypes[0] = "varchar(30)";
	mapProperties["datum"] = new Property("datum");
	columns[1] = "bemerkung";
 	columnTypes[1] = "text";
	mapProperties["bemerkung"] = new Property("bemerkung");
mapReferences["Schueler"] = new Reference("meldung","datamodel/schueler");
}


meldungmapper::~meldungmapper(){}


 PObject* meldungmapper::createNewObject()
 {
     return new meldung();
 }


 meldung* meldungmapper::create()
 {
     return  (meldung*) AbstractMapper::create( meldungmapper::getInstance() );
 }


 string meldungmapper::getTableName()
 {
     return string("meldung");
 }
 
 string meldungmapper::getClassName()
 {
 	return string("meldung");
 }
 
 string* meldungmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* meldungmapper::getColumns()
 {
 	return columns;
 }
 
 int meldungmapper::getColumnCount()
 {
     return 2;
 }


 string* meldungmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[2];  
 	meldung *o = (meldung*) realSubject;
	values[0] = to_string(o->getDatum());
	values[1] = to_string(o->getBemerkung());
return values;
 }


 void meldungmapper::save(){
qWarning("meldung: save() not implemented");
}

void meldungmapper::save(PObject *realSubject)
{
 	meldung *o = (meldung*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	mapReferences[ "Schueler" ] -> save(realSubject, (PObject*) o->getSchueler());
}


void meldungmapper::init(PObject* inito, Variant *res)
 {
 	meldung *o = (meldung*) inito;
	o->setDatum( res[0].asQDate());
 	o->setBemerkung( res[1].asstring());
 	inito->init();
}


 list<meldung *>*meldungmapper::find() 
 {
 	return (list <meldung*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* meldungmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "meldung" ); 
	entry->addProperty( new StringProperty<meldung>("Name", "string", &meldung::getName, &meldung::setName, false) );
	entry->addProperty( new DateProperty< meldung> ( "Datum", "QDate" , &meldung::getDatum, &meldung::setDatum ) ); 
	entry->addProperty( new StringProperty< meldung >( "Bemerkung" , "string", &meldung::getBemerkung, &meldung::setBemerkung, true ) );
	entry->addProperty( new PObjectProperty<schueler,meldung>( "Schueler" , "schueler", &meldung::getSchueler,&meldung::setSchueler ) ); 
	return entry;
 }
