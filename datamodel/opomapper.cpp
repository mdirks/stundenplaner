// 
 // C++ Implementation: opomapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "opomapper.h"
 #include "services/utils/utils.h"
 #include "opo.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 opomapper* opomapper::instance=0;
 
 opomapper* opomapper::getInstance()
 {
 	if(!instance){
 		instance=new opomapper();
 	}
 	return instance;
 }


 opomapper::opomapper()
  {
 	version = "0.2";
	columns = new string[1];
 	columnTypes = new string[1];
 	columns[0] = "title";
 	columnTypes[0] = "varchar(30)";
	mapProperties["title"] = new Property("title");
asc_Materialien = new Association<opo, material>("opo_material","opo_id","material_id","material", &opo::addToMaterialien, &opo::deleteFromMaterialien);
mapAssociations["Materialien"] = asc_Materialien;
registerAssociation( asc_Materialien);
}


opomapper::~opomapper(){}


 PObject* opomapper::createNewObject()
 {
     return new opo();
 }


 opo* opomapper::create()
 {
     return  (opo*) AbstractMapper::create( opomapper::getInstance() );
 }


 string opomapper::getTableName()
 {
     return string("opo");
 }
 
 string opomapper::getClassName()
 {
 	return string("opo");
 }
 
 string* opomapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* opomapper::getColumns()
 {
 	return columns;
 }
 
 int opomapper::getColumnCount()
 {
     return 1;
 }


 string* opomapper::getValues(PObject *realSubject)
 {
 	string *values = new string[1];  
 	opo *o = (opo*) realSubject;
	values[0] = to_string(o->getTitle());
return values;
 }


 void opomapper::save(){
qWarning("opo: save() not implemented");
}

void opomapper::save(PObject *realSubject)
{
 	opo *o = (opo*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Materialien -> save(realSubject, o->getMaterialien() );

}


void opomapper::init(PObject* inito, Variant *res)
 {
 	opo *o = (opo*) inito;
	o->setTitle( res[0].asstring());
 	inito->init();
}


 list<opo *>*opomapper::find() 
 {
 	return (list <opo*>*) Database::getInstance()->getAll(this); 
}


list<material*> * opomapper::findMaterialien(int pri_id) 
 { 
 	return asc_Materialien ->  findAssociates( pri_id );
     }


list<material*> * opomapper::findMaterialien(int pri_id,string prop,string value) 
         { 
             return asc_Materialien ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* opomapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "opo" ); 
	entry->addProperty( new StringProperty<opo>("Name", "string", &opo::getName, &opo::setName, false) );
	entry->addProperty( new StringProperty< opo >( "title" , "string", &opo::getTitle, &opo::setTitle, false ) );
	entry->addProperty( new CollectionPropertyImpl<material,opo>( "Materialien" , "material", &opo::getMaterialien, &opo::addToMaterialien, &opo::deleteFromMaterialien  ) ); 
	return entry;
 }
