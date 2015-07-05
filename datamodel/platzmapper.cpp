// 
 // C++ Implementation: platzmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "platzmapper.h"
 #include "services/utils/utils.h"
 #include "platz.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 platzmapper* platzmapper::instance=0;
 
 platzmapper* platzmapper::getInstance()
 {
 	if(!instance){
 		instance=new platzmapper();
 	}
 	return instance;
 }


 platzmapper::platzmapper()
  {
 	version = "0.5";
	columns = new string[2];
 	columnTypes = new string[2];
 	columns[0] = "reihe";
 	columnTypes[0] = "int";
	mapProperties["reihe"] = new Property("reihe");
	columns[1] = "spalte";
 	columnTypes[1] = "int";
	mapProperties["spalte"] = new Property("spalte");
asc_Noten = new Association<platz, note>("platz_note","platz_id","note_id","note", &platz::addToNoten, &platz::deleteFromNoten);
mapAssociations["Noten"] = asc_Noten;
registerAssociation( asc_Noten);
mapReferences["Schueler"] = new Reference("platz","datamodel/schueler");
}


platzmapper::~platzmapper(){}


 PObject* platzmapper::createNewObject()
 {
     return new platz();
 }


 platz* platzmapper::create()
 {
     return  (platz*) AbstractMapper::create( platzmapper::getInstance() );
 }


 string platzmapper::getTableName()
 {
     return string("platz");
 }
 
 string platzmapper::getClassName()
 {
 	return string("platz");
 }
 
 string* platzmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* platzmapper::getColumns()
 {
 	return columns;
 }
 
 int platzmapper::getColumnCount()
 {
     return 2;
 }


 string* platzmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[2];  
 	platz *o = (platz*) realSubject;
	values[0] = to_string(o->getReihe());
	values[1] = to_string(o->getSpalte());
return values;
 }


 void platzmapper::save(){
qWarning("platz: save() not implemented");
}

void platzmapper::save(PObject *realSubject)
{
 	platz *o = (platz*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Noten -> save(realSubject, o->getNoten() );

	mapReferences[ "Schueler" ] -> save(realSubject, (PObject*) o->getSchueler());
}


void platzmapper::init(PObject* inito, Variant *res)
 {
 	platz *o = (platz*) inito;
	o->setReihe( res[0].asint());
 	o->setSpalte( res[1].asint());
 	inito->init();
}


 list<platz *>*platzmapper::find() 
 {
 	return (list <platz*>*) Database::getInstance()->getAll(this); 
}


list<note*> * platzmapper::findNoten(int pri_id) 
 { 
 	return asc_Noten ->  findAssociates( pri_id );
     }


list<note*> * platzmapper::findNoten(int pri_id,string prop,string value) 
         { 
             return asc_Noten ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* platzmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "platz" ); 
	entry->addProperty( new StringProperty<platz>("Name", "string", &platz::getName, &platz::setName, false) );
	entry->addProperty( new NumericProperty< int,platz> ( "Reihe", "int" , &platz::getReihe,&platz::setReihe ) ); 
	entry->addProperty( new NumericProperty< int,platz> ( "Spalte", "int" , &platz::getSpalte,&platz::setSpalte ) ); 
	entry->addProperty( new CollectionPropertyImpl<note,platz>( "Noten" , "note", &platz::getNoten, &platz::addToNoten, &platz::deleteFromNoten  ) ); 
	entry->addProperty( new PObjectProperty<schueler,platz>( "Schueler" , "schueler", &platz::getSchueler,&platz::setSchueler ) ); 
	return entry;
 }
