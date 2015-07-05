// 
 // C++ Implementation: teilleistungmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "teilleistungmapper.h"
 #include "services/utils/utils.h"
 #include "teilleistung.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 teilleistungmapper* teilleistungmapper::instance=0;
 
 teilleistungmapper* teilleistungmapper::getInstance()
 {
 	if(!instance){
 		instance=new teilleistungmapper();
 	}
 	return instance;
 }


 teilleistungmapper::teilleistungmapper()
  {
 	version = "0.3";
	columns = new string[2];
 	columnTypes = new string[2];
 	columns[0] = "datum";
 	columnTypes[0] = "varchar(30)";
	mapProperties["datum"] = new Property("datum");
	columns[1] = "aufgabe";
 	columnTypes[1] = "varchar(80)";
	mapProperties["aufgabe"] = new Property("aufgabe");
asc_Noten = new Association<teilleistung, note>("teilleistung_note","leistung_id","note_id","note", &teilleistung::addToNoten, &teilleistung::deleteFromNoten);
mapAssociations["Noten"] = asc_Noten;
registerAssociation( asc_Noten);
mapReferences["Klasse"] = new Reference("teilleistung","datamodel/klasse");
}


teilleistungmapper::~teilleistungmapper(){}


 PObject* teilleistungmapper::createNewObject()
 {
     return new teilleistung();
 }


 teilleistung* teilleistungmapper::create()
 {
     return  (teilleistung*) AbstractMapper::create( teilleistungmapper::getInstance() );
 }


 string teilleistungmapper::getTableName()
 {
     return string("teilleistung");
 }
 
 string teilleistungmapper::getClassName()
 {
 	return string("teilleistung");
 }
 
 string* teilleistungmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* teilleistungmapper::getColumns()
 {
 	return columns;
 }
 
 int teilleistungmapper::getColumnCount()
 {
     return 2;
 }


 string* teilleistungmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[2];  
 	teilleistung *o = (teilleistung*) realSubject;
	values[0] = to_string(o->getDatum());
	values[1] = to_string(o->getAufgabe());
return values;
 }


 void teilleistungmapper::save(){
qWarning("teilleistung: save() not implemented");
}

void teilleistungmapper::save(PObject *realSubject)
{
 	teilleistung *o = (teilleistung*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Noten -> save(realSubject, o->getNoten() );

	mapReferences[ "Klasse" ] -> save(realSubject, (PObject*) o->getKlasse());
}


void teilleistungmapper::init(PObject* inito, Variant *res)
 {
 	teilleistung *o = (teilleistung*) inito;
	o->setDatum( res[0].asQDate());
 	o->setAufgabe( res[1].asMUrl());
 	inito->init();
}


 list<teilleistung *>*teilleistungmapper::find() 
 {
 	return (list <teilleistung*>*) Database::getInstance()->getAll(this); 
}


list<note*> * teilleistungmapper::findNoten(int pri_id) 
 { 
 	return asc_Noten ->  findAssociates( pri_id );
     }


list<note*> * teilleistungmapper::findNoten(int pri_id,string prop,string value) 
         { 
             return asc_Noten ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* teilleistungmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "teilleistung" ); 
	entry->addProperty( new StringProperty<teilleistung>("Name", "string", &teilleistung::getName, &teilleistung::setName, false) );
	entry->addProperty( new DateProperty< teilleistung> ( "Datum", "QDate" , &teilleistung::getDatum, &teilleistung::setDatum ) ); 
	entry->addProperty( new UrlProperty< teilleistung> ( "Aufgabe", "MUrl" , &teilleistung::getAufgabe, &teilleistung::setAufgabe ) ); 
	entry->addProperty( new CollectionPropertyImpl<note,teilleistung>( "Noten" , "note", &teilleistung::getNoten, &teilleistung::addToNoten, &teilleistung::deleteFromNoten  ) ); 
	entry->addProperty( new PObjectProperty<klasse,teilleistung>( "Klasse" , "klasse", &teilleistung::getKlasse,&teilleistung::setKlasse ) ); 
	return entry;
 }
