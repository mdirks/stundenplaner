// 
 // C++ Implementation: stundemapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "stundemapper.h"
 #include "services/utils/utils.h"
 #include "stunde.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 stundemapper* stundemapper::instance=0;
 
 stundemapper* stundemapper::getInstance()
 {
 	if(!instance){
 		instance=new stundemapper();
 	}
 	return instance;
 }


 stundemapper::stundemapper()
  {
 	version = "1.1";
	columns = new string[2];
 	columnTypes = new string[2];
 	columns[0] = "verlauf";
 	columnTypes[0] = "text";
	mapProperties["verlauf"] = new Property("verlauf");
	columns[1] = "title";
 	columnTypes[1] = "varchar(30)";
	mapProperties["title"] = new Property("title");
asc_Opos = new Association<stunde, opo>("stunde_opo","stunde_id","opo_id","opo", &stunde::addToOpos, &stunde::deleteFromOpos);
mapAssociations["Opos"] = asc_Opos;
registerAssociation( asc_Opos);
asc_Materialien = new Association<stunde, material>("stunde_material","stunde_id","material_id","material", &stunde::addToMaterialien, &stunde::deleteFromMaterialien);
mapAssociations["Materialien"] = asc_Materialien;
registerAssociation( asc_Materialien);
mapReferences["Thema"] = new Reference("stunde","datamodel/thema");
}


stundemapper::~stundemapper(){}


 PObject* stundemapper::createNewObject()
 {
     return new stunde();
 }


 stunde* stundemapper::create()
 {
     return  (stunde*) AbstractMapper::create( stundemapper::getInstance() );
 }


 string stundemapper::getTableName()
 {
     return string("stunde");
 }
 
 string stundemapper::getClassName()
 {
 	return string("stunde");
 }
 
 string* stundemapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* stundemapper::getColumns()
 {
 	return columns;
 }
 
 int stundemapper::getColumnCount()
 {
     return 2;
 }


 string* stundemapper::getValues(PObject *realSubject)
 {
 	string *values = new string[2];  
 	stunde *o = (stunde*) realSubject;
	values[0] = to_string(o->getVerlauf());
	values[1] = to_string(o->getTitle());
return values;
 }


 void stundemapper::save(){
qWarning("stunde: save() not implemented");
}

void stundemapper::save(PObject *realSubject)
{
 	stunde *o = (stunde*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Opos -> save(realSubject, o->getOpos() );

	asc_Materialien -> save(realSubject, o->getMaterialien() );

	mapReferences[ "Thema" ] -> save(realSubject, (PObject*) o->getThema());
	notizholdermapper::save(realSubject);
}


void stundemapper::init(PObject* inito, Variant *res)
 {
 	stunde *o = (stunde*) inito;
	o->setVerlauf( res[0].asstring());
 	o->setTitle( res[1].asstring());
 	inito->init();
}


 list<stunde *>*stundemapper::find() 
 {
 	return (list <stunde*>*) Database::getInstance()->getAll(this); 
}


list<opo*> * stundemapper::findOpos(int pri_id) 
 { 
 	return asc_Opos ->  findAssociates( pri_id );
     }


list<opo*> * stundemapper::findOpos(int pri_id,string prop,string value) 
         { 
             return asc_Opos ->  findAssociates( pri_id,prop,value);
             }


list<material*> * stundemapper::findMaterialien(int pri_id) 
 { 
 	return asc_Materialien ->  findAssociates( pri_id );
     }


list<material*> * stundemapper::findMaterialien(int pri_id,string prop,string value) 
         { 
             return asc_Materialien ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* stundemapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "stunde" ); 
	entry->addProperty( new StringProperty<stunde>("Name", "string", &stunde::getName, &stunde::setName, false) );
	entry->addProperty( new StringProperty< stunde >( "Verlauf" , "string", &stunde::getVerlauf, &stunde::setVerlauf, true ) );
	entry->addProperty( new StringProperty< stunde >( "Title" , "string", &stunde::getTitle, &stunde::setTitle, false ) );
	entry->addProperty( new CollectionPropertyImpl<opo,stunde>( "Opos" , "opo", &stunde::getOpos, &stunde::addToOpos, &stunde::deleteFromOpos  ) ); 
	entry->addProperty( new CollectionPropertyImpl<material,stunde>( "Materialien" , "material", &stunde::getMaterialien, &stunde::addToMaterialien, &stunde::deleteFromMaterialien  ) ); 
	entry->addProperty( new PObjectProperty<thema,stunde>( "Thema" , "thema", &stunde::getThema,&stunde::setThema ) ); 
	entry->registerBase( "notizholder" );
	return entry;
 }
