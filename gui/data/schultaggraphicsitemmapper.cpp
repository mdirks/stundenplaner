// 
 // C++ Implementation: SchultagGraphicsItemmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "schultaggraphicsitemmapper.h"
 #include "services/utils/utils.h"
 #include "schultaggraphicsitem.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 SchultagGraphicsItemmapper* SchultagGraphicsItemmapper::instance=0;
 
 SchultagGraphicsItemmapper* SchultagGraphicsItemmapper::getInstance()
 {
 	if(!instance){
 		instance=new SchultagGraphicsItemmapper();
 	}
 	return instance;
 }


 SchultagGraphicsItemmapper::SchultagGraphicsItemmapper()
  {
 	version = "0.1";
	columns = new string[0];
 	columnTypes = new string[0];
 }


SchultagGraphicsItemmapper::~SchultagGraphicsItemmapper(){}


 PObject* SchultagGraphicsItemmapper::createNewObject()
 {
     return new SchultagGraphicsItem();
 }


 SchultagGraphicsItem* SchultagGraphicsItemmapper::create()
 {
     return  (SchultagGraphicsItem*) AbstractMapper::create( SchultagGraphicsItemmapper::getInstance() );
 }


 string SchultagGraphicsItemmapper::getTableName()
 {
     return string("schultaggraphicsitem");
 }
 
 string SchultagGraphicsItemmapper::getClassName()
 {
 	return string("SchultagGraphicsItem");
 }
 
 string* SchultagGraphicsItemmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* SchultagGraphicsItemmapper::getColumns()
 {
 	return columns;
 }
 
 int SchultagGraphicsItemmapper::getColumnCount()
 {
     return 0;
 }


 string* SchultagGraphicsItemmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	SchultagGraphicsItem *o = (SchultagGraphicsItem*) realSubject;
return values;
 }


 void SchultagGraphicsItemmapper::save(){
qWarning("SchultagGraphicsItem: save() not implemented");
}

void SchultagGraphicsItemmapper::save(PObject *realSubject)
{
 	SchultagGraphicsItem *o = (SchultagGraphicsItem*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	PObjectGraphicsItemmapper::save(realSubject);
}


void SchultagGraphicsItemmapper::init(PObject* inito, Variant *res)
 {
 	SchultagGraphicsItem *o = (SchultagGraphicsItem*) inito;
	inito->init();
}


 list<SchultagGraphicsItem *>*SchultagGraphicsItemmapper::find() 
 {
 	return (list <SchultagGraphicsItem*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* SchultagGraphicsItemmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "SchultagGraphicsItem" ); 
	entry->addProperty( new StringProperty<SchultagGraphicsItem>("Name", "string", &SchultagGraphicsItem::getName, &SchultagGraphicsItem::setName, false) );
	entry->registerBase( "PObjectGraphicsItem" );
	return entry;
 }
