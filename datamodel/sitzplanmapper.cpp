// 
 // C++ Implementation: sitzplanmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "sitzplanmapper.h"
 #include "services/utils/utils.h"
 #include "sitzplan.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 sitzplanmapper* sitzplanmapper::instance=0;
 
 sitzplanmapper* sitzplanmapper::getInstance()
 {
 	if(!instance){
 		instance=new sitzplanmapper();
 	}
 	return instance;
 }


 sitzplanmapper::sitzplanmapper()
  {
 	version = "0.2";
	columns = new string[2];
 	columnTypes = new string[2];
 	columns[0] = "reihen";
 	columnTypes[0] = "int";
	mapProperties["reihen"] = new Property("reihen");
	columns[1] = "spalten";
 	columnTypes[1] = "int";
	mapProperties["spalten"] = new Property("spalten");
asc_Plaetze = new Association<sitzplan, platz>("sitzplan_plaetze","sitzplan_id","platz_id","platz", &sitzplan::addToPlaetze, &sitzplan::deleteFromPlaetze);
mapAssociations["Plaetze"] = asc_Plaetze;
registerAssociation( asc_Plaetze);
mapReferences["Klasse"] = new Reference("sitzplan","datamodel/klasse");
}


sitzplanmapper::~sitzplanmapper(){}


 PObject* sitzplanmapper::createNewObject()
 {
     return new sitzplan();
 }


 sitzplan* sitzplanmapper::create()
 {
     return  (sitzplan*) AbstractMapper::create( sitzplanmapper::getInstance() );
 }


 string sitzplanmapper::getTableName()
 {
     return string("sitzplan");
 }
 
 string sitzplanmapper::getClassName()
 {
 	return string("sitzplan");
 }
 
 string* sitzplanmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* sitzplanmapper::getColumns()
 {
 	return columns;
 }
 
 int sitzplanmapper::getColumnCount()
 {
     return 2;
 }


 string* sitzplanmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[2];  
 	sitzplan *o = (sitzplan*) realSubject;
	values[0] = to_string(o->getReihen());
	values[1] = to_string(o->getSpalten());
return values;
 }


 void sitzplanmapper::save(){
qWarning("sitzplan: save() not implemented");
}

void sitzplanmapper::save(PObject *realSubject)
{
 	sitzplan *o = (sitzplan*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Plaetze -> save(realSubject, o->getPlaetze() );

	mapReferences[ "Klasse" ] -> save(realSubject, (PObject*) o->getKlasse());
}


void sitzplanmapper::init(PObject* inito, Variant *res)
 {
 	sitzplan *o = (sitzplan*) inito;
	o->setReihen( res[0].asint());
 	o->setSpalten( res[1].asint());
 	inito->init();
}


 list<sitzplan *>*sitzplanmapper::find() 
 {
 	return (list <sitzplan*>*) Database::getInstance()->getAll(this); 
}


list<platz*> * sitzplanmapper::findPlaetze(int pri_id) 
 { 
 	return asc_Plaetze ->  findAssociates( pri_id );
 	}


RepositoryEntry* sitzplanmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "sitzplan" ); 
	entry->addProperty( new StringProperty<sitzplan>("Name", "string", &sitzplan::getName, &sitzplan::setName, false) );
	entry->addProperty( new NumericProperty< int,sitzplan> ( "Reihen", "int" , &sitzplan::getReihen,&sitzplan::setReihen ) ); 
	entry->addProperty( new NumericProperty< int,sitzplan> ( "Spalten", "int" , &sitzplan::getSpalten,&sitzplan::setSpalten ) ); 
	entry->addProperty( new CollectionPropertyImpl<platz,sitzplan>( "Plaetze" , "platz", &sitzplan::getPlaetze, &sitzplan::addToPlaetze, &sitzplan::deleteFromPlaetze  ) ); 
	entry->addProperty( new PObjectProperty<klasse,sitzplan>( "Klasse" , "klasse", &sitzplan::getKlasse,&sitzplan::setKlasse ) ); 
	return entry;
 }
