// 
 // C++ Implementation: stundenplantemplateeintragmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "stundenplantemplateeintragmapper.h"
 #include "services/utils/utils.h"
 #include "stundenplantemplateeintrag.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 stundenplantemplateeintragmapper* stundenplantemplateeintragmapper::instance=0;
 
 stundenplantemplateeintragmapper* stundenplantemplateeintragmapper::getInstance()
 {
 	if(!instance){
 		instance=new stundenplantemplateeintragmapper();
 	}
 	return instance;
 }


 stundenplantemplateeintragmapper::stundenplantemplateeintragmapper()
  {
 	version = "0.8";
	columns = new string[5];
 	columnTypes = new string[5];
 	columns[0] = "datumbegin";
 	columnTypes[0] = "varchar(30)";
	mapProperties["datumbegin"] = new Property("datumbegin");
	columns[1] = "datumende";
 	columnTypes[1] = "varchar(30)";
	mapProperties["datumende"] = new Property("datumende");
	columns[2] = "tag";
 	columnTypes[2] = "int";
	mapProperties["tag"] = new Property("tag");
	columns[3] = "stunde";
 	columnTypes[3] = "int";
	mapProperties["stunde"] = new Property("stunde");
	columns[4] = "doppelstunde";
 	columnTypes[4] = "bool";
	mapProperties["doppelstunde"] = new Property("doppelstunde");
asc_Eintraege = new Association<stundenplantemplateeintrag, stundenplaneintrag>("stundenplantemplateeintrag_eintrag","template_id","eintrag_id","stundenplaneintrag", &stundenplantemplateeintrag::addToEintraege, &stundenplantemplateeintrag::deleteFromEintraege);
mapAssociations["Eintraege"] = asc_Eintraege;
registerAssociation( asc_Eintraege);
asc_Reihen = new Association<stundenplantemplateeintrag, reihe>("stundenplantemplateeintrag_reihe","template_id","reihe_id","reihe", &stundenplantemplateeintrag::addToReihen, &stundenplantemplateeintrag::deleteFromReihen);
mapAssociations["Reihen"] = asc_Reihen;
registerAssociation( asc_Reihen);
mapReferences["Klasse"] = new Reference("stundenplantemplateeintrag","datamodel/klasse");
}


stundenplantemplateeintragmapper::~stundenplantemplateeintragmapper(){}


 PObject* stundenplantemplateeintragmapper::createNewObject()
 {
     return new stundenplantemplateeintrag();
 }


 stundenplantemplateeintrag* stundenplantemplateeintragmapper::create()
 {
     return  (stundenplantemplateeintrag*) AbstractMapper::create( stundenplantemplateeintragmapper::getInstance() );
 }


 string stundenplantemplateeintragmapper::getTableName()
 {
     return string("stundenplantemplateeintrag");
 }
 
 string stundenplantemplateeintragmapper::getClassName()
 {
 	return string("stundenplantemplateeintrag");
 }
 
 string* stundenplantemplateeintragmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* stundenplantemplateeintragmapper::getColumns()
 {
 	return columns;
 }
 
 int stundenplantemplateeintragmapper::getColumnCount()
 {
     return 5;
 }


 string* stundenplantemplateeintragmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[5];  
 	stundenplantemplateeintrag *o = (stundenplantemplateeintrag*) realSubject;
	values[0] = to_string(o->getDatumBegin());
	values[1] = to_string(o->getDatumEnde());
	values[2] = to_string(o->getTag());
	values[3] = to_string(o->getNrStunde());
	values[4] = to_string(o->getDoppelstunde());
return values;
 }


 void stundenplantemplateeintragmapper::save(){
qWarning("stundenplantemplateeintrag: save() not implemented");
}

void stundenplantemplateeintragmapper::save(PObject *realSubject)
{
 	stundenplantemplateeintrag *o = (stundenplantemplateeintrag*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Eintraege -> save(realSubject, o->getEintraege() );

	asc_Reihen -> save(realSubject, o->getReihen() );

	mapReferences[ "Klasse" ] -> save(realSubject, (PObject*) o->getKlasse());
}


void stundenplantemplateeintragmapper::init(PObject* inito, Variant *res)
 {
 	stundenplantemplateeintrag *o = (stundenplantemplateeintrag*) inito;
	o->setDatumBegin( res[0].asQDate());
 	o->setDatumEnde( res[1].asQDate());
 	o->setTag( res[2].asint());
 	o->setNrStunde( res[3].asint());
 	o->setDoppelstunde( res[4].asbool());
 	inito->init();
}


 list<stundenplantemplateeintrag *>*stundenplantemplateeintragmapper::find() 
 {
 	return (list <stundenplantemplateeintrag*>*) Database::getInstance()->getAll(this); 
}


list<stundenplaneintrag*> * stundenplantemplateeintragmapper::findEintraege(int pri_id) 
 { 
 	return asc_Eintraege ->  findAssociates( pri_id );
     }


list<stundenplaneintrag*> * stundenplantemplateeintragmapper::findEintraege(int pri_id,string prop,string value) 
         { 
             return asc_Eintraege ->  findAssociates( pri_id,prop,value);
             }


list<reihe*> * stundenplantemplateeintragmapper::findReihen(int pri_id) 
 { 
 	return asc_Reihen ->  findAssociates( pri_id );
     }


list<reihe*> * stundenplantemplateeintragmapper::findReihen(int pri_id,string prop,string value) 
         { 
             return asc_Reihen ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* stundenplantemplateeintragmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "stundenplantemplateeintrag" ); 
	entry->addProperty( new StringProperty<stundenplantemplateeintrag>("Name", "string", &stundenplantemplateeintrag::getName, &stundenplantemplateeintrag::setName, false) );
	entry->addProperty( new DateProperty< stundenplantemplateeintrag> ( "DatumBegin", "QDate" , &stundenplantemplateeintrag::getDatumBegin, &stundenplantemplateeintrag::setDatumBegin ) ); 
	entry->addProperty( new DateProperty< stundenplantemplateeintrag> ( "DatumEnde", "QDate" , &stundenplantemplateeintrag::getDatumEnde, &stundenplantemplateeintrag::setDatumEnde ) ); 
	entry->addProperty( new NumericProperty< int,stundenplantemplateeintrag> ( "Tag", "int" , &stundenplantemplateeintrag::getTag,&stundenplantemplateeintrag::setTag ) ); 
	entry->addProperty( new NumericProperty< int,stundenplantemplateeintrag> ( "NrStunde", "int" , &stundenplantemplateeintrag::getNrStunde,&stundenplantemplateeintrag::setNrStunde ) ); 
	entry->addProperty( new BooleanProperty< stundenplantemplateeintrag> ( "Doppelstunde", "bool" , &stundenplantemplateeintrag::getDoppelstunde,&stundenplantemplateeintrag::setDoppelstunde ) ); 
	entry->addProperty( new CollectionPropertyImpl<stundenplaneintrag,stundenplantemplateeintrag>( "Eintraege" , "stundenplaneintrag", &stundenplantemplateeintrag::getEintraege, &stundenplantemplateeintrag::addToEintraege, &stundenplantemplateeintrag::deleteFromEintraege  ) ); 
	entry->addProperty( new CollectionPropertyImpl<reihe,stundenplantemplateeintrag>( "Reihen" , "reihe", &stundenplantemplateeintrag::getReihen, &stundenplantemplateeintrag::addToReihen, &stundenplantemplateeintrag::deleteFromReihen  ) ); 
	entry->addProperty( new PObjectProperty<klasse,stundenplantemplateeintrag>( "Klasse" , "klasse", &stundenplantemplateeintrag::getKlasse,&stundenplantemplateeintrag::setKlasse ) ); 
	return entry;
 }
