 //
 // C++ Implementation: taskmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "taskmapper.h"
 #include "services/utils/utils.h"
 #include "task.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 taskmapper* taskmapper::instance=0;
 
 taskmapper* taskmapper::getInstance()
 {
 	if(!instance){
 		instance=new taskmapper();
 	}
 	return instance;
 }


 taskmapper::taskmapper()
  {
 	version = "0.2";
	columns = new string[1];
 	columnTypes = new string[1];
 	columns[0] = "datum";
 	columnTypes[0] = "varchar(30)";
	mapProperties["datum"] = new Property("datum");
mapReferences["Bezugsobjekt"] = new Reference("task","orm/persistence/PObject");
}


taskmapper::~taskmapper(){}


 PObject* taskmapper::createNewObject()
 {
     return new task();
 }


 task* taskmapper::create()
 {
     return  (task*) AbstractMapper::create( taskmapper::getInstance() );
 }


 string taskmapper::getTableName()
 {
     return string("task");
 }
 
 string taskmapper::getClassName()
 {
 	return string("task");
 }
 
 string* taskmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* taskmapper::getColumns()
 {
 	return columns;
 }
 
 int taskmapper::getColumnCount()
 {
     return 1;
 }


 string* taskmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[1];  
 	task *o = (task*) realSubject;
	values[0] = to_string(o->getDatum());
return values;
 }


 void taskmapper::save(){
qWarning("task: save() not implemented");
}

void taskmapper::save(PObject *realSubject)
{
 	task *o = (task*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	mapReferences[ "Bezugsobjekt" ] -> save(realSubject, (PObject*) o->getBezugsobjekt());
}


void taskmapper::init(PObject* inito, Variant *res)
 {
 	task *o = (task*) inito;
	o->setDatum( res[0].asQDate());
 	inito->init();
}


 list<task *>*taskmapper::find() 
 {
 	return (list <task*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* taskmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "task" ); 
	entry->addProperty( new StringProperty<task>("Name", "string", &task::getName, &task::setName, false) );
	entry->addProperty( new DateProperty< task> ( "Datum", "QDate" , &task::getDatum, &task::setDatum ) ); 
	entry->addProperty( new PObjectProperty<PObject,task>( "Bezugsobjekt" , "PObject", &task::getBezugsobjekt,&task::setBezugsobjekt ) ); 
	return entry;
 }
