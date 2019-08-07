// 
 // C++ Implementation: materialsatzmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "materialsatzmapper.h"
 #include "services/utils/utils.h"
 #include "materialsatz.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 materialsatzmapper* materialsatzmapper::instance=0;
 
 materialsatzmapper* materialsatzmapper::getInstance()
 {
 	if(!instance){
 		instance=new materialsatzmapper();
 	}
 	return instance;
 }


 materialsatzmapper::materialsatzmapper()
  {
 	version = "0.1";
	columns = new string[0];
 	columnTypes = new string[0];
 asc_Materialien = new Association<materialsatz, material>("materialsatz_material","satz_id","material_id","material", &materialsatz::addToMaterialien, &materialsatz::deleteFromMaterialien);
mapAssociations["Materialien"] = asc_Materialien;
registerAssociation( asc_Materialien);
}


materialsatzmapper::~materialsatzmapper(){}


 PObject* materialsatzmapper::createNewObject()
 {
     return new materialsatz();
 }


 materialsatz* materialsatzmapper::create()
 {
     return  (materialsatz*) AbstractMapper::create( materialsatzmapper::getInstance() );
 }


 string materialsatzmapper::getTableName()
 {
     return string("materialsatz");
 }
 
 string materialsatzmapper::getClassName()
 {
 	return string("materialsatz");
 }
 
 string* materialsatzmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* materialsatzmapper::getColumns()
 {
 	return columns;
 }
 
 int materialsatzmapper::getColumnCount()
 {
     return 0;
 }


 string* materialsatzmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	materialsatz *o = (materialsatz*) realSubject;
return values;
 }


 void materialsatzmapper::save(){
qWarning("materialsatz: save() not implemented");
}

void materialsatzmapper::save(PObject *realSubject)
{
 	materialsatz *o = (materialsatz*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Materialien -> save(realSubject, o->getMaterialien() );

}


void materialsatzmapper::init(PObject* inito, Variant *res)
 {
 	materialsatz *o = (materialsatz*) inito;
	inito->init();
}


 list<materialsatz *>*materialsatzmapper::find() 
 {
 	return (list <materialsatz*>*) Database::getInstance()->getAll(this); 
}


list<material*> * materialsatzmapper::findMaterialien(int pri_id) 
 { 
 	return asc_Materialien ->  findAssociates( pri_id );
     }


list<material*> * materialsatzmapper::findMaterialien(int pri_id,string prop,string value) 
         { 
             return asc_Materialien ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* materialsatzmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "materialsatz" ); 
	entry->addProperty( new StringProperty<materialsatz>("Name", "string", &materialsatz::getName, &materialsatz::setName, false) );
	entry->addProperty( new CollectionPropertyImpl<material,materialsatz>( "Materialien" , "material", &materialsatz::getMaterialien, &materialsatz::addToMaterialien, &materialsatz::deleteFromMaterialien  ) ); 
	return entry;
 }
