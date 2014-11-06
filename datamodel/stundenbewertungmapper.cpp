// 
 // C++ Implementation: stundenbewertungmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "stundenbewertungmapper.h"
 #include "services/utils/utils.h"
 #include "stundenbewertung.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 stundenbewertungmapper* stundenbewertungmapper::instance=0;
 
 stundenbewertungmapper* stundenbewertungmapper::getInstance()
 {
 	if(!instance){
 		instance=new stundenbewertungmapper();
 	}
 	return instance;
 }


 stundenbewertungmapper::stundenbewertungmapper()
  {
 	version = "0.4";
	columns = new string[3];
 	columnTypes = new string[3];
 	columns[0] = "bewertung";
 	columnTypes[0] = "varchar(30)";
	mapProperties["bewertung"] = new Property("bewertung");
	columns[1] = "bemerkung";
 	columnTypes[1] = "text";
	mapProperties["bemerkung"] = new Property("bemerkung");
	columns[2] = "fehlzeit";
 	columnTypes[2] = "bool";
	mapProperties["fehlzeit"] = new Property("fehlzeit");
mapReferences["Stundenplaneintrag"] = new Reference("stundenbewertung","datamodel/stundenplaneintrag");
mapReferences["Schueler"] = new Reference("stundenbewertung","datamodel/schueler");
}


stundenbewertungmapper::~stundenbewertungmapper(){}


 PObject* stundenbewertungmapper::createNewObject()
 {
     return new stundenbewertung();
 }


 stundenbewertung* stundenbewertungmapper::create()
 {
     return  (stundenbewertung*) AbstractMapper::create( stundenbewertungmapper::getInstance() );
 }


 string stundenbewertungmapper::getTableName()
 {
     return string("stundenbewertung");
 }
 
 string stundenbewertungmapper::getClassName()
 {
 	return string("stundenbewertung");
 }
 
 string* stundenbewertungmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* stundenbewertungmapper::getColumns()
 {
 	return columns;
 }
 
 int stundenbewertungmapper::getColumnCount()
 {
     return 3;
 }


 string* stundenbewertungmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[3];  
 	stundenbewertung *o = (stundenbewertung*) realSubject;
	values[0] = to_string(o->getBewertung());
	values[1] = to_string(o->getBemerkung());
	values[2] = to_string(o->getGefehlt());
return values;
 }


 void stundenbewertungmapper::save(){
qWarning("stundenbewertung: save() not implemented");
}

void stundenbewertungmapper::save(PObject *realSubject)
{
 	stundenbewertung *o = (stundenbewertung*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	mapReferences[ "Stundenplaneintrag" ] -> save(realSubject, (PObject*) o->getStundenplaneintrag());
	mapReferences[ "Schueler" ] -> save(realSubject, (PObject*) o->getSchueler());
}


void stundenbewertungmapper::init(PObject* inito, Variant *res)
 {
 	stundenbewertung *o = (stundenbewertung*) inito;
	o->setBewertung( res[0].asstring());
 	o->setBemerkung( res[1].asstring());
 	o->setGefehlt( res[2].asbool());
 	inito->init();
}


 list<stundenbewertung *>*stundenbewertungmapper::find() 
 {
 	return (list <stundenbewertung*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* stundenbewertungmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "stundenbewertung" ); 
	entry->addProperty( new StringProperty<stundenbewertung>("Name", "string", &stundenbewertung::getName, &stundenbewertung::setName, false) );
	entry->addProperty( new StringProperty< stundenbewertung >( "Bewertung" , "string", &stundenbewertung::getBewertung, &stundenbewertung::setBewertung, false ) );
	entry->addProperty( new StringProperty< stundenbewertung >( "Bemerkung" , "string", &stundenbewertung::getBemerkung, &stundenbewertung::setBemerkung, true ) );
	entry->addProperty( new BooleanProperty< stundenbewertung> ( "Gefehlt", "bool" , &stundenbewertung::getGefehlt,&stundenbewertung::setGefehlt ) ); 
	entry->addProperty( new PObjectProperty<stundenplaneintrag,stundenbewertung>( "Stundenplaneintrag" , "stundenplaneintrag", &stundenbewertung::getStundenplaneintrag,&stundenbewertung::setStundenplaneintrag ) ); 
	entry->addProperty( new PObjectProperty<schueler,stundenbewertung>( "Schueler" , "schueler", &stundenbewertung::getSchueler,&stundenbewertung::setSchueler ) ); 
	return entry;
 }
