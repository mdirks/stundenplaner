// 
 // C++ Implementation: SchultagCanvasItemmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "schultagcanvasitemmapper.h"
 #include "utils/utils.h"
 #include "schultagcanvasitem.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 SchultagCanvasItemmapper* SchultagCanvasItemmapper::instance=0;
 
 SchultagCanvasItemmapper* SchultagCanvasItemmapper::getInstance()
 {
 	if(!instance){
 		instance=new SchultagCanvasItemmapper();
 	}
 	return instance;
 }


 SchultagCanvasItemmapper::SchultagCanvasItemmapper()
  {
 	version = "0.1";
	columns = new string[0];
 	columnTypes = new string[0];
 }


SchultagCanvasItemmapper::~SchultagCanvasItemmapper(){}


 PObject* SchultagCanvasItemmapper::createNewObject()
 {
     return new SchultagCanvasItem();
 }


 SchultagCanvasItem* SchultagCanvasItemmapper::create()
 {
     return  (SchultagCanvasItem*) AbstractMapper::create( SchultagCanvasItemmapper::getInstance() );
 }


 string SchultagCanvasItemmapper::getTableName()
 {
     return string("schultagcanvasitem");
 }
 
 string SchultagCanvasItemmapper::getClassName()
 {
 	return string("SchultagCanvasItem");
 }
 
 string* SchultagCanvasItemmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* SchultagCanvasItemmapper::getColumns()
 {
 	return columns;
 }
 
 int SchultagCanvasItemmapper::getColumnCount()
 {
     return 0;
 }


 string* SchultagCanvasItemmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	SchultagCanvasItem *o = (SchultagCanvasItem*) realSubject;
return values;
 }


 void SchultagCanvasItemmapper::save(){
qWarning("SchultagCanvasItem: save() not implemented");
}

void SchultagCanvasItemmapper::save(PObject *realSubject)
{
 	SchultagCanvasItem *o = (SchultagCanvasItem*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	PObjectCanvasItemmapper::save(realSubject);
}


void SchultagCanvasItemmapper::init(PObject* inito, Variant *res)
 {
 	SchultagCanvasItem *o = (SchultagCanvasItem*) inito;
	inito->init();
}


 list<SchultagCanvasItem *>*SchultagCanvasItemmapper::find() 
 {
 	return (list <SchultagCanvasItem*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* SchultagCanvasItemmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "SchultagCanvasItem" ); 
	entry->addProperty( new StringProperty<SchultagCanvasItem>("Name", "string", &SchultagCanvasItem::getName, &SchultagCanvasItem::setName, false) );
	entry->registerBase( "PObjectCanvasItem" );
	return entry;
 }
