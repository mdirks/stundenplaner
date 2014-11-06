// 
 // C++ Implementation: fehlzeitmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "fehlzeitmapper.h"
 #include "services/utils/utils.h"
 #include "fehlzeit.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 fehlzeitmapper* fehlzeitmapper::instance=0;
 
 fehlzeitmapper* fehlzeitmapper::getInstance()
 {
 	if(!instance){
 		instance=new fehlzeitmapper();
 	}
 	return instance;
 }


 fehlzeitmapper::fehlzeitmapper()
  {
 	version = "0.3";
	columns = new string[4];
 	columnTypes = new string[4];
 	columns[0] = "von";
 	columnTypes[0] = "varchar(30)";
	mapProperties["von"] = new Property("von");
	columns[1] = "bis";
 	columnTypes[1] = "varchar(30)";
	mapProperties["bis"] = new Property("bis");
	columns[2] = "bemerkung";
 	columnTypes[2] = "text";
	mapProperties["bemerkung"] = new Property("bemerkung");
	columns[3] = "entschuldigt";
 	columnTypes[3] = "bool";
	mapProperties["entschuldigt"] = new Property("entschuldigt");
mapReferences["Schueler"] = new Reference("fehlzeit","datamodel/schueler");
mapReferences["Stundenplaneintrag"] = new Reference("fehlzeit","datamodel/stundenplaneintrag");
}


fehlzeitmapper::~fehlzeitmapper(){}


 PObject* fehlzeitmapper::createNewObject()
 {
     return new fehlzeit();
 }


 fehlzeit* fehlzeitmapper::create()
 {
     return  (fehlzeit*) AbstractMapper::create( fehlzeitmapper::getInstance() );
 }


 string fehlzeitmapper::getTableName()
 {
     return string("fehlzeit");
 }
 
 string fehlzeitmapper::getClassName()
 {
 	return string("fehlzeit");
 }
 
 string* fehlzeitmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* fehlzeitmapper::getColumns()
 {
 	return columns;
 }
 
 int fehlzeitmapper::getColumnCount()
 {
     return 4;
 }


 string* fehlzeitmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[4];  
 	fehlzeit *o = (fehlzeit*) realSubject;
	values[0] = to_string(o->getVon());
	values[1] = to_string(o->getBis());
	values[2] = to_string(o->getBemerkung());
	values[3] = to_string(o->getEntschuldigt());
return values;
 }


 void fehlzeitmapper::save(){
qWarning("fehlzeit: save() not implemented");
}

void fehlzeitmapper::save(PObject *realSubject)
{
 	fehlzeit *o = (fehlzeit*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	mapReferences[ "Schueler" ] -> save(realSubject, (PObject*) o->getSchueler());
	mapReferences[ "Stundenplaneintrag" ] -> save(realSubject, (PObject*) o->getStundenplaneintrag());
	notizholdermapper::save(realSubject);
}


void fehlzeitmapper::init(PObject* inito, Variant *res)
 {
 	fehlzeit *o = (fehlzeit*) inito;
	o->setVon( res[0].asQDateTime());
 	o->setBis( res[1].asQDateTime());
 	o->setBemerkung( res[2].asstring());
 	o->setEntschuldigt( res[3].asbool());
 	inito->init();
}


 list<fehlzeit *>*fehlzeitmapper::find() 
 {
 	return (list <fehlzeit*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* fehlzeitmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "fehlzeit" ); 
	entry->addProperty( new StringProperty<fehlzeit>("Name", "string", &fehlzeit::getName, &fehlzeit::setName, false) );
	entry->addProperty( new DateTimeProperty< fehlzeit> ( "Datum", "QDateTime" , &fehlzeit::getVon, &fehlzeit::setVon ) ); 
	entry->addProperty( new DateTimeProperty< fehlzeit> ( "Datum", "QDateTime" , &fehlzeit::getBis, &fehlzeit::setBis ) ); 
	entry->addProperty( new StringProperty< fehlzeit >( "Bemerkung" , "string", &fehlzeit::getBemerkung, &fehlzeit::setBemerkung, true ) );
	entry->addProperty( new BooleanProperty< fehlzeit> ( "Entschuldigt", "bool" , &fehlzeit::getEntschuldigt,&fehlzeit::setEntschuldigt ) ); 
	entry->addProperty( new PObjectProperty<schueler,fehlzeit>( "Schueler" , "schueler", &fehlzeit::getSchueler,&fehlzeit::setSchueler ) ); 
	entry->addProperty( new PObjectProperty<stundenplaneintrag,fehlzeit>( "Stundenplaneintrag" , "stundenplaneintrag", &fehlzeit::getStundenplaneintrag,&fehlzeit::setStundenplaneintrag ) ); 
	entry->registerBase( "notizholder" );
	return entry;
 }
