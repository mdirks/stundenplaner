// 
 // C++ Implementation: materialmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "materialmapper.h"
 #include "services/utils/utils.h"
 #include "material.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 materialmapper* materialmapper::instance=0;
 
 materialmapper* materialmapper::getInstance()
 {
 	if(!instance){
 		instance=new materialmapper();
 	}
 	return instance;
 }


 materialmapper::materialmapper()
  {
 	version = "0.6";
	columns = new string[2];
 	columnTypes = new string[2];
 	columns[0] = "title";
 	columnTypes[0] = "varchar(50)";
	mapProperties["title"] = new Property("title");
	columns[1] = "filename";
 	columnTypes[1] = "varchar(80)";
	mapProperties["filename"] = new Property("filename");
}


materialmapper::~materialmapper(){}


 PObject* materialmapper::createNewObject()
 {
     return new material();
 }


 material* materialmapper::create()
 {
     return  (material*) AbstractMapper::create( materialmapper::getInstance() );
 }


 string materialmapper::getTableName()
 {
     return string("material");
 }
 
 string materialmapper::getClassName()
 {
 	return string("material");
 }
 
 string* materialmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* materialmapper::getColumns()
 {
 	return columns;
 }
 
 int materialmapper::getColumnCount()
 {
     return 2;
 }


 string* materialmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[2];  
 	material *o = (material*) realSubject;
	values[0] = to_string(o->getTitle());
	values[1] = to_string(o->getFileName());
return values;
 }


 void materialmapper::save(){
qWarning("material: save() not implemented");
}

void materialmapper::save(PObject *realSubject)
{
 	material *o = (material*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
}


void materialmapper::init(PObject* inito, Variant *res)
 {
 	material *o = (material*) inito;
	o->setTitle( res[0].asstring());
 	o->setFileName( res[1].asstring());
 	inito->init();
}


 list<material *>*materialmapper::find() 
 {
 	return (list <material*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* materialmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "material" ); 
	entry->addProperty( new StringProperty<material>("Name", "string", &material::getName, &material::setName, false) );
	entry->addProperty( new StringProperty< material >( "title" , "string", &material::getTitle, &material::setTitle, false ) );
	entry->addProperty( new StringProperty< material >( "FileName" , "string", &material::getFileName, &material::setFileName, false ) );
	return entry;
 }
