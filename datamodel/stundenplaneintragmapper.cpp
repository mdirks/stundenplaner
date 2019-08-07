// 
 // C++ Implementation: stundenplaneintragmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "stundenplaneintragmapper.h"
 #include "services/utils/utils.h"
 #include "stundenplaneintrag.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 stundenplaneintragmapper* stundenplaneintragmapper::instance=0;
 
 stundenplaneintragmapper* stundenplaneintragmapper::getInstance()
 {
 	if(!instance){
 		instance=new stundenplaneintragmapper();
 	}
 	return instance;
 }


 stundenplaneintragmapper::stundenplaneintragmapper()
  {
 	version = "0.11-0.4";
	columns = new string[5];
 	columnTypes = new string[5];
 	columns[0] = "datum";
 	columnTypes[0] = "varchar(30)";
	mapProperties["datum"] = new Property("datum");
	columns[1] = "verlauf";
 	columnTypes[1] = "text";
	mapProperties["verlauf"] = new Property("verlauf");
	columns[2] = "doppelstunde";
 	columnTypes[2] = "bool";
	mapProperties["doppelstunde"] = new Property("doppelstunde");
	columns[3] = "tag";
 	columnTypes[3] = "int";
	mapProperties["tag"] = new Property("tag");
	columns[4] = "stunde";
 	columnTypes[4] = "int";
	mapProperties["stunde"] = new Property("stunde");
asc_Bewertungen = new Association<stundenplaneintrag, stundenbewertung>("stundenplaneintrag_bewertung","stundenplaneintrag_id","bewertung_id","stundenbewertung", &stundenplaneintrag::addToBewertungen, &stundenplaneintrag::deleteFromBewertungen);
mapAssociations["Bewertungen"] = asc_Bewertungen;
registerAssociation( asc_Bewertungen);
asc_Fehlzeiten = new Association<stundenplaneintrag, fehlzeit>("stundenplaneintrag_fehlzeit","stundenplaneintrag_id","fehlzeit_id","fehlzeit", &stundenplaneintrag::addToFehlzeiten, &stundenplaneintrag::deleteFromFehlzeiten);
mapAssociations["Fehlzeiten"] = asc_Fehlzeiten;
registerAssociation( asc_Fehlzeiten);
mapReferences["Klasse"] = new Reference("stundenplaneintrag","datamodel/klasse");
mapReferences["Stunde"] = new Reference("stundenplaneintrag","datamodel/stunde");
mapReferences["Template"] = new Reference("stundenplaneintrag","datamodel/stundenplantemplateeintrag");
mapReferences["KursbuchEintrag"] = new Reference("stundenplaneintrag","datamodel/krusbucheintrag");
}


stundenplaneintragmapper::~stundenplaneintragmapper(){}


 PObject* stundenplaneintragmapper::createNewObject()
 {
     return new stundenplaneintrag();
 }


 stundenplaneintrag* stundenplaneintragmapper::create()
 {
     return  (stundenplaneintrag*) AbstractMapper::create( stundenplaneintragmapper::getInstance() );
 }


 string stundenplaneintragmapper::getTableName()
 {
     return string("stundenplaneintrag");
 }
 
 string stundenplaneintragmapper::getClassName()
 {
 	return string("stundenplaneintrag");
 }
 
 string* stundenplaneintragmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* stundenplaneintragmapper::getColumns()
 {
 	return columns;
 }
 
 int stundenplaneintragmapper::getColumnCount()
 {
     return 5;
 }


 string* stundenplaneintragmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[5];  
 	stundenplaneintrag *o = (stundenplaneintrag*) realSubject;
	values[0] = to_string(o->getDatum());
	values[1] = to_string(o->getVerlauf());
	values[2] = to_string(o->getDoppelstunde());
	values[3] = to_string(o->getTag());
	values[4] = to_string(o->getNrStunde());
return values;
 }


 void stundenplaneintragmapper::save(){
qWarning("stundenplaneintrag: save() not implemented");
}

void stundenplaneintragmapper::save(PObject *realSubject)
{
 	stundenplaneintrag *o = (stundenplaneintrag*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Bewertungen -> save(realSubject, o->getBewertungen() );

	asc_Fehlzeiten -> save(realSubject, o->getFehlzeiten() );

	mapReferences[ "Klasse" ] -> save(realSubject, (PObject*) o->getKlasse());
	mapReferences[ "Stunde" ] -> save(realSubject, (PObject*) o->getStunde());
	mapReferences[ "Template" ] -> save(realSubject, (PObject*) o->getTemplate());
	mapReferences[ "KursbuchEintrag" ] -> save(realSubject, (PObject*) o->getKursbuchEintrag());
	notizholdermapper::save(realSubject);
}


void stundenplaneintragmapper::init(PObject* inito, Variant *res)
 {
 	stundenplaneintrag *o = (stundenplaneintrag*) inito;
	o->setDatum( res[0].asQDate());
 	o->setVerlauf( res[1].asstring());
 	o->setDoppelstunde( res[2].asbool());
 	o->setTag( res[3].asint());
 	o->setNrStunde( res[4].asint());
 	inito->init();
}


 list<stundenplaneintrag *>*stundenplaneintragmapper::find() 
 {
 	return (list <stundenplaneintrag*>*) Database::getInstance()->getAll(this); 
}


list<stundenbewertung*> * stundenplaneintragmapper::findBewertungen(int pri_id) 
 { 
 	return asc_Bewertungen ->  findAssociates( pri_id );
     }


list<stundenbewertung*> * stundenplaneintragmapper::findBewertungen(int pri_id,string prop,string value) 
         { 
             return asc_Bewertungen ->  findAssociates( pri_id,prop,value);
             }


list<fehlzeit*> * stundenplaneintragmapper::findFehlzeiten(int pri_id) 
 { 
 	return asc_Fehlzeiten ->  findAssociates( pri_id );
     }


list<fehlzeit*> * stundenplaneintragmapper::findFehlzeiten(int pri_id,string prop,string value) 
         { 
             return asc_Fehlzeiten ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* stundenplaneintragmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "stundenplaneintrag" ); 
	entry->addProperty( new StringProperty<stundenplaneintrag>("Name", "string", &stundenplaneintrag::getName, &stundenplaneintrag::setName, false) );
	entry->addProperty( new DateProperty< stundenplaneintrag> ( "Datum", "QDate" , &stundenplaneintrag::getDatum, &stundenplaneintrag::setDatum ) ); 
	entry->addProperty( new StringProperty< stundenplaneintrag >( "Verlauf" , "string", &stundenplaneintrag::getVerlauf, &stundenplaneintrag::setVerlauf, true ) );
	entry->addProperty( new BooleanProperty< stundenplaneintrag> ( "Doppelstunde", "bool" , &stundenplaneintrag::getDoppelstunde,&stundenplaneintrag::setDoppelstunde ) ); 
	entry->addProperty( new NumericProperty< int,stundenplaneintrag> ( "Tag", "int" , &stundenplaneintrag::getTag,&stundenplaneintrag::setTag ) ); 
	entry->addProperty( new NumericProperty< int,stundenplaneintrag> ( "NrStunde", "int" , &stundenplaneintrag::getNrStunde,&stundenplaneintrag::setNrStunde ) ); 
	entry->addProperty( new CollectionPropertyImpl<stundenbewertung,stundenplaneintrag>( "Bewertungen" , "stundenbewertung", &stundenplaneintrag::getBewertungen, &stundenplaneintrag::addToBewertungen, &stundenplaneintrag::deleteFromBewertungen  ) ); 
	entry->addProperty( new CollectionPropertyImpl<fehlzeit,stundenplaneintrag>( "Fehlzeiten" , "fehlzeit", &stundenplaneintrag::getFehlzeiten, &stundenplaneintrag::addToFehlzeiten, &stundenplaneintrag::deleteFromFehlzeiten  ) ); 
	entry->addProperty( new PObjectProperty<klasse,stundenplaneintrag>( "Klasse" , "klasse", &stundenplaneintrag::getKlasse,&stundenplaneintrag::setKlasse ) ); 
	entry->addProperty( new PObjectProperty<stunde,stundenplaneintrag>( "Stunde" , "stunde", &stundenplaneintrag::getStunde,&stundenplaneintrag::setStunde ) ); 
	entry->addProperty( new PObjectProperty<stundenplantemplateeintrag,stundenplaneintrag>( "Template" , "stundenplantemplateeintrag", &stundenplaneintrag::getTemplate,&stundenplaneintrag::setTemplate ) ); 
	entry->addProperty( new PObjectProperty<krusbucheintrag,stundenplaneintrag>( "KursbuchEintrag" , "krusbucheintrag", &stundenplaneintrag::getKursbuchEintrag,&stundenplaneintrag::setKursbuchEintrag ) ); 
	entry->registerBase( "notizholder" );
	return entry;
 }
