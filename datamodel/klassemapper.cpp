// 
 // C++ Implementation: klassemapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "klassemapper.h"
 #include "services/utils/utils.h"
 #include "klasse.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 klassemapper* klassemapper::instance=0;
 
 klassemapper* klassemapper::getInstance()
 {
 	if(!instance){
 		instance=new klassemapper();
 	}
 	return instance;
 }


 klassemapper::klassemapper()
  {
 	version = "0.11-0.5-0.5";
	columns = new string[3];
 	columnTypes = new string[3];
 	columns[0] = "jhrg";
 	columnTypes[0] = "int";
	mapProperties["jhrg"] = new Property("jhrg");
	columns[1] = "kursnr";
 	columnTypes[1] = "varchar(15)";
	mapProperties["kursnr"] = new Property("kursnr");
	columns[2] = "fach";
 	columnTypes[2] = "varchar(15)";
	mapProperties["fach"] = new Property("fach");
asc_Stunden = new Association<klasse, stunde>("klasse_stunde","klasse_id","stunde_id","stunde", &klasse::addToStunden, &klasse::deleteFromStunden);
mapAssociations["Stunden"] = asc_Stunden;
registerAssociation( asc_Stunden);
asc_Schueler = new Association<klasse, schueler>("klasse_schueler","klasse_id","schueler_id","schueler", &klasse::addToSchueler, &klasse::deleteFromSchueler);
mapAssociations["Schueler"] = asc_Schueler;
registerAssociation( asc_Schueler);
asc_Teilleistungen = new Association<klasse, teilleistung>("klasse_leistung","klasse_id","teilleistung_id","teilleistung", &klasse::addToTeilleistungen, &klasse::deleteFromTeilleistungen);
mapAssociations["Teilleistungen"] = asc_Teilleistungen;
registerAssociation( asc_Teilleistungen);
asc_StundenplanTemplates = new Association<klasse, stundenplantemplateeintrag>("klasse_templates","klasse_id","template_id","stundenplantemplateeintrag", &klasse::addToStundenplanTemplates, &klasse::deleteFromStundenplanTemplates);
mapAssociations["StundenplanTemplates"] = asc_StundenplanTemplates;
registerAssociation( asc_StundenplanTemplates);
asc_Reihen = new Association<klasse, reihe>("klasse_reihe","klasse_id","reihe_id","reihe", &klasse::addToReihen, &klasse::deleteFromReihen);
mapAssociations["Reihen"] = asc_Reihen;
registerAssociation( asc_Reihen);
mapReferences["Sitzplan"] = new Reference("klasse","datamodel/sitzplan");
mapReferences["Kursbuch"] = new Reference("klasse","datamodel/kursbuch");
mapReferences["Schuljahr"] = new Reference("klasse","datamodel/schuljahr");
}


klassemapper::~klassemapper(){}


 PObject* klassemapper::createNewObject()
 {
     return new klasse();
 }


 klasse* klassemapper::create()
 {
     return  (klasse*) AbstractMapper::create( klassemapper::getInstance() );
 }


 string klassemapper::getTableName()
 {
     return string("klasse");
 }
 
 string klassemapper::getClassName()
 {
 	return string("klasse");
 }
 
 string* klassemapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* klassemapper::getColumns()
 {
 	return columns;
 }
 
 int klassemapper::getColumnCount()
 {
     return 3;
 }


 string* klassemapper::getValues(PObject *realSubject)
 {
 	string *values = new string[3];  
 	klasse *o = (klasse*) realSubject;
	values[0] = to_string(o->getJahrgangsstufe());
	values[1] = to_string(o->getKursnummer());
	values[2] = to_string(o->getFach());
return values;
 }


 void klassemapper::save(){
qWarning("klasse: save() not implemented");
}

void klassemapper::save(PObject *realSubject)
{
 	klasse *o = (klasse*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Stunden -> save(realSubject, o->getStunden() );

	asc_Schueler -> save(realSubject, o->getSchueler() );

	asc_Teilleistungen -> save(realSubject, o->getTeilleistungen() );

	asc_StundenplanTemplates -> save(realSubject, o->getStundenplanTemplates() );

	asc_Reihen -> save(realSubject, o->getReihen() );

	mapReferences[ "Sitzplan" ] -> save(realSubject, (PObject*) o->getSitzplan());
	mapReferences[ "Kursbuch" ] -> save(realSubject, (PObject*) o->getKursbuch());
	mapReferences[ "Schuljahr" ] -> save(realSubject, (PObject*) o->getSchuljahr());
	notizholdermapper::save(realSubject);
}


void klassemapper::init(PObject* inito, Variant *res)
 {
 	klasse *o = (klasse*) inito;
	o->setJahrgangsstufe( res[0].asint());
 	o->setKursnummer( res[1].asstring());
 	o->setFach( res[2].asstring());
 	inito->init();
}


 list<klasse *>*klassemapper::find() 
 {
 	return (list <klasse*>*) Database::getInstance()->getAll(this); 
}


list<stunde*> * klassemapper::findStunden(int pri_id) 
 { 
 	return asc_Stunden ->  findAssociates( pri_id );
     }


list<stunde*> * klassemapper::findStunden(int pri_id,string prop,string value) 
         { 
             return asc_Stunden ->  findAssociates( pri_id,prop,value);
             }


list<schueler*> * klassemapper::findSchueler(int pri_id) 
 { 
 	return asc_Schueler ->  findAssociates( pri_id );
     }


list<schueler*> * klassemapper::findSchueler(int pri_id,string prop,string value) 
         { 
             return asc_Schueler ->  findAssociates( pri_id,prop,value);
             }


list<teilleistung*> * klassemapper::findTeilleistungen(int pri_id) 
 { 
 	return asc_Teilleistungen ->  findAssociates( pri_id );
     }


list<teilleistung*> * klassemapper::findTeilleistungen(int pri_id,string prop,string value) 
         { 
             return asc_Teilleistungen ->  findAssociates( pri_id,prop,value);
             }


list<stundenplantemplateeintrag*> * klassemapper::findStundenplanTemplates(int pri_id) 
 { 
 	return asc_StundenplanTemplates ->  findAssociates( pri_id );
     }


list<stundenplantemplateeintrag*> * klassemapper::findStundenplanTemplates(int pri_id,string prop,string value) 
         { 
             return asc_StundenplanTemplates ->  findAssociates( pri_id,prop,value);
             }


list<reihe*> * klassemapper::findReihen(int pri_id) 
 { 
 	return asc_Reihen ->  findAssociates( pri_id );
     }


list<reihe*> * klassemapper::findReihen(int pri_id,string prop,string value) 
         { 
             return asc_Reihen ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* klassemapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "klasse" ); 
	entry->addProperty( new StringProperty<klasse>("Name", "string", &klasse::getName, &klasse::setName, false) );
	entry->addProperty( new NumericProperty< int,klasse> ( "Jahrgangsstufe", "int" , &klasse::getJahrgangsstufe,&klasse::setJahrgangsstufe ) ); 
	entry->addProperty( new StringProperty< klasse >( "Kursnummer" , "string", &klasse::getKursnummer, &klasse::setKursnummer, false ) );
	entry->addProperty( new StringProperty< klasse >( "Fach" , "string", &klasse::getFach, &klasse::setFach, false ) );
	entry->addProperty( new CollectionPropertyImpl<stunde,klasse>( "Stunden" , "stunde", &klasse::getStunden, &klasse::addToStunden, &klasse::deleteFromStunden  ) ); 
	entry->addProperty( new CollectionPropertyImpl<schueler,klasse>( "Schueler" , "schueler", &klasse::getSchueler, &klasse::addToSchueler, &klasse::deleteFromSchueler  ) ); 
	entry->addProperty( new CollectionPropertyImpl<teilleistung,klasse>( "Teilleistungen" , "teilleistung", &klasse::getTeilleistungen, &klasse::addToTeilleistungen, &klasse::deleteFromTeilleistungen  ) ); 
	entry->addProperty( new CollectionPropertyImpl<stundenplantemplateeintrag,klasse>( "StundenplanTemplates" , "stundenplantemplateeintrag", &klasse::getStundenplanTemplates, &klasse::addToStundenplanTemplates, &klasse::deleteFromStundenplanTemplates  ) ); 
	entry->addProperty( new CollectionPropertyImpl<reihe,klasse>( "Reihen" , "reihe", &klasse::getReihen, &klasse::addToReihen, &klasse::deleteFromReihen  ) ); 
	entry->addProperty( new PObjectProperty<sitzplan,klasse>( "Sitzplan" , "sitzplan", &klasse::getSitzplan,&klasse::setSitzplan ) ); 
	entry->addProperty( new PObjectProperty<kursbuch,klasse>( "Kursbuch" , "kursbuch", &klasse::getKursbuch,&klasse::setKursbuch ) ); 
	entry->addProperty( new PObjectProperty<schuljahr,klasse>( "Schuljahr" , "schuljahr", &klasse::getSchuljahr,&klasse::setSchuljahr ) ); 
	entry->registerBase( "notizholder" );
	return entry;
 }
