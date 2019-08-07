// 
 // C++ Implementation: notemapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "notemapper.h"
 #include "services/utils/utils.h"
 #include "note.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 notemapper* notemapper::instance=0;
 
 notemapper* notemapper::getInstance()
 {
 	if(!instance){
 		instance=new notemapper();
 	}
 	return instance;
 }


 notemapper::notemapper()
  {
 	version = "0.6";
	columns = new string[5];
 	columnTypes = new string[5];
 	columns[0] = "punkte";
 	columnTypes[0] = "int";
	mapProperties["punkte"] = new Property("punkte");
	columns[1] = "bemerkung";
 	columnTypes[1] = "text";
	mapProperties["bemerkung"] = new Property("bemerkung");
	columns[2] = "datum";
 	columnTypes[2] = "varchar(30)";
	mapProperties["datum"] = new Property("datum");
	columns[3] = "at";
 	columnTypes[3] = "bool";
	mapProperties["at"] = new Property("at");
	columns[4] = "klausur";
 	columnTypes[4] = "bool";
	mapProperties["klausur"] = new Property("klausur");
mapReferences["Schueler"] = new Reference("note","datamodel/schueler");
}


notemapper::~notemapper(){}


 PObject* notemapper::createNewObject()
 {
     return new note();
 }


 note* notemapper::create()
 {
     return  (note*) AbstractMapper::create( notemapper::getInstance() );
 }


 string notemapper::getTableName()
 {
     return string("note");
 }
 
 string notemapper::getClassName()
 {
 	return string("note");
 }
 
 string* notemapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* notemapper::getColumns()
 {
 	return columns;
 }
 
 int notemapper::getColumnCount()
 {
     return 5;
 }


 string* notemapper::getValues(PObject *realSubject)
 {
 	string *values = new string[5];  
 	note *o = (note*) realSubject;
	values[0] = to_string(o->getPunkte());
	values[1] = to_string(o->getBemerkung());
	values[2] = to_string(o->getDatum());
	values[3] = to_string(o->getIsAt());
	values[4] = to_string(o->getIsKlausur());
return values;
 }


 void notemapper::save(){
qWarning("note: save() not implemented");
}

void notemapper::save(PObject *realSubject)
{
 	note *o = (note*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	mapReferences[ "Schueler" ] -> save(realSubject, (PObject*) o->getSchueler());
}


void notemapper::init(PObject* inito, Variant *res)
 {
 	note *o = (note*) inito;
	o->setPunkte( res[0].asint());
 	o->setBemerkung( res[1].asstring());
 	o->setDatum( res[2].asQDateTime());
 	o->setIsAt( res[3].asbool());
 	o->setIsKlausur( res[4].asbool());
 	inito->init();
}


 list<note *>*notemapper::find() 
 {
 	return (list <note*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* notemapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "note" ); 
	entry->addProperty( new StringProperty<note>("Name", "string", &note::getName, &note::setName, false) );
	entry->addProperty( new NumericProperty< int,note> ( "Punkte", "int" , &note::getPunkte,&note::setPunkte ) ); 
	entry->addProperty( new StringProperty< note >( "Bemerkung" , "string", &note::getBemerkung, &note::setBemerkung, true ) );
	entry->addProperty( new DateTimeProperty< note> ( "Datum", "QDateTime" , &note::getDatum, &note::setDatum ) ); 
	entry->addProperty( new BooleanProperty< note> ( "IsAt", "bool" , &note::getIsAt,&note::setIsAt ) ); 
	entry->addProperty( new BooleanProperty< note> ( "IsKl", "bool" , &note::getIsKlausur,&note::setIsKlausur ) ); 
	entry->addProperty( new PObjectProperty<schueler,note>( "Schueler" , "schueler", &note::getSchueler,&note::setSchueler ) ); 
	return entry;
 }
