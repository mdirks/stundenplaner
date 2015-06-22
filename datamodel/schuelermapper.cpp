// 
 // C++ Implementation: schuelermapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "schuelermapper.h"
 #include "services/utils/utils.h"
 #include "schueler.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 schuelermapper* schuelermapper::instance=0;
 
 schuelermapper* schuelermapper::getInstance()
 {
 	if(!instance){
 		instance=new schuelermapper();
 	}
 	return instance;
 }


 schuelermapper::schuelermapper()
  {
 	version = "0.6";
	columns = new string[3];
 	columnTypes = new string[3];
 	columns[0] = "vorname";
 	columnTypes[0] = "varchar(30)";
	mapProperties["vorname"] = new Property("vorname");
	columns[1] = "nachname";
 	columnTypes[1] = "varchar(30)";
	mapProperties["nachname"] = new Property("nachname");
	columns[2] = "tutor";
 	columnTypes[2] = "varchar(30)";
	mapProperties["tutor"] = new Property("tutor");
asc_Noten = new Association<schueler, note>("schueler_note","schueler_id","note_id","note", &schueler::addToNoten, &schueler::deleteFromNoten);
mapAssociations["Noten"] = asc_Noten;
registerAssociation( asc_Noten);
asc_Fehlzeiten = new Association<schueler, fehlzeit>("schueler_fehlzeit","schueler_id","fehlzeit_id","fehlzeit", &schueler::addToFehlzeiten, &schueler::deleteFromFehlzeiten);
mapAssociations["Fehlzeiten"] = asc_Fehlzeiten;
registerAssociation( asc_Fehlzeiten);
asc_Stundenbewertungen = new Association<schueler, stundenbewertung>("schueler_bewertung","schueler_id","bewertung_id","stundenbewertung", &schueler::addToStundenbewertungen, &schueler::deleteFromStundenbewertungen);
mapAssociations["Stundenbewertungen"] = asc_Stundenbewertungen;
registerAssociation( asc_Stundenbewertungen);
mapReferences["Klasse"] = new Reference("schueler","datamodel/klasse");
}


schuelermapper::~schuelermapper(){}


 PObject* schuelermapper::createNewObject()
 {
     return new schueler();
 }


 schueler* schuelermapper::create()
 {
     return  (schueler*) AbstractMapper::create( schuelermapper::getInstance() );
 }


 string schuelermapper::getTableName()
 {
     return string("schueler");
 }
 
 string schuelermapper::getClassName()
 {
 	return string("schueler");
 }
 
 string* schuelermapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* schuelermapper::getColumns()
 {
 	return columns;
 }
 
 int schuelermapper::getColumnCount()
 {
     return 3;
 }


 string* schuelermapper::getValues(PObject *realSubject)
 {
 	string *values = new string[3];  
 	schueler *o = (schueler*) realSubject;
	values[0] = to_string(o->getVorname());
	values[1] = to_string(o->getNachname());
	values[2] = to_string(o->getTutor());
return values;
 }


 void schuelermapper::save(){
qWarning("schueler: save() not implemented");
}

void schuelermapper::save(PObject *realSubject)
{
 	schueler *o = (schueler*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Noten -> save(realSubject, o->getNoten() );

	asc_Fehlzeiten -> save(realSubject, o->getFehlzeiten() );

	asc_Stundenbewertungen -> save(realSubject, o->getStundenbewertungen() );

	mapReferences[ "Klasse" ] -> save(realSubject, (PObject*) o->getKlasse());
	notizholdermapper::save(realSubject);
}


void schuelermapper::init(PObject* inito, Variant *res)
 {
 	schueler *o = (schueler*) inito;
	o->setVorname( res[0].asstring());
 	o->setNachname( res[1].asstring());
 	o->setTutor( res[2].asstring());
 	inito->init();
}


 list<schueler *>*schuelermapper::find() 
 {
 	return (list <schueler*>*) Database::getInstance()->getAll(this); 
}


list<note*> * schuelermapper::findNoten(int pri_id) 
 { 
 	return asc_Noten ->  findAssociates( pri_id );
     }


list<note*> * schuelermapper::findNoten(int pri_id,string prop,string value) 
         { 
             return asc_Noten ->  findAssociates( pri_id,prop,value);
             }


list<fehlzeit*> * schuelermapper::findFehlzeiten(int pri_id) 
 { 
 	return asc_Fehlzeiten ->  findAssociates( pri_id );
     }


list<fehlzeit*> * schuelermapper::findFehlzeiten(int pri_id,string prop,string value) 
         { 
             return asc_Fehlzeiten ->  findAssociates( pri_id,prop,value);
             }


list<stundenbewertung*> * schuelermapper::findStundenbewertungen(int pri_id) 
 { 
 	return asc_Stundenbewertungen ->  findAssociates( pri_id );
     }


list<stundenbewertung*> * schuelermapper::findStundenbewertungen(int pri_id,string prop,string value) 
         { 
             return asc_Stundenbewertungen ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* schuelermapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "schueler" ); 
	entry->addProperty( new StringProperty<schueler>("Name", "string", &schueler::getName, &schueler::setName, false) );
	entry->addProperty( new StringProperty< schueler >( "Vorname" , "string", &schueler::getVorname, &schueler::setVorname, false ) );
	entry->addProperty( new StringProperty< schueler >( "Nachname" , "string", &schueler::getNachname, &schueler::setNachname, false ) );
	entry->addProperty( new StringProperty< schueler >( "Tutor" , "string", &schueler::getTutor, &schueler::setTutor, false ) );
	entry->addProperty( new CollectionPropertyImpl<note,schueler>( "Noten" , "note", &schueler::getNoten, &schueler::addToNoten, &schueler::deleteFromNoten  ) ); 
	entry->addProperty( new CollectionPropertyImpl<fehlzeit,schueler>( "Fehlzeiten" , "fehlzeit", &schueler::getFehlzeiten, &schueler::addToFehlzeiten, &schueler::deleteFromFehlzeiten  ) ); 
	entry->addProperty( new CollectionPropertyImpl<stundenbewertung,schueler>( "Stundenbewertungen" , "stundenbewertung", &schueler::getStundenbewertungen, &schueler::addToStundenbewertungen, &schueler::deleteFromStundenbewertungen  ) ); 
	entry->addProperty( new PObjectProperty<klasse,schueler>( "Klasse" , "klasse", &schueler::getKlasse,&schueler::setKlasse ) ); 
	entry->registerBase( "notizholder" );
	return entry;
 }
