// 
 // C++ Implementation: notizmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "notizmapper.h"
 #include "services/utils/utils.h"
 #include "notiz.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 notizmapper* notizmapper::instance=0;
 
 notizmapper* notizmapper::getInstance()
 {
 	if(!instance){
 		instance=new notizmapper();
 	}
 	return instance;
 }


 notizmapper::notizmapper()
  {
 	version = "0.4";
	columns = new string[2];
 	columnTypes = new string[2];
 	columns[0] = "title";
 	columnTypes[0] = "varchar(30)";
	mapProperties["title"] = new Property("title");
	columns[1] = "body";
 	columnTypes[1] = "text";
	mapProperties["body"] = new Property("body");
}


notizmapper::~notizmapper(){}


 PObject* notizmapper::createNewObject()
 {
     return new notiz();
 }


 notiz* notizmapper::create()
 {
     return  (notiz*) AbstractMapper::create( notizmapper::getInstance() );
 }


 string notizmapper::getTableName()
 {
     return string("notiz");
 }
 
 string notizmapper::getClassName()
 {
 	return string("notiz");
 }
 
 string* notizmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* notizmapper::getColumns()
 {
 	return columns;
 }
 
 int notizmapper::getColumnCount()
 {
     return 2;
 }


 string* notizmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[2];  
 	notiz *o = (notiz*) realSubject;
	values[0] = to_string(o->getTitle());
	values[1] = to_string(o->getBody());
return values;
 }


 void notizmapper::save(){
qWarning("notiz: save() not implemented");
}

void notizmapper::save(PObject *realSubject)
{
 	notiz *o = (notiz*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
}


void notizmapper::init(PObject* inito, Variant *res)
 {
 	notiz *o = (notiz*) inito;
	o->setTitle( res[0].asstring());
 	o->setBody( res[1].asstring());
 	inito->init();
}


 list<notiz *>*notizmapper::find() 
 {
 	return (list <notiz*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* notizmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "notiz" ); 
	entry->addProperty( new StringProperty<notiz>("Name", "string", &notiz::getName, &notiz::setName, false) );
	entry->addProperty( new StringProperty< notiz >( "Title" , "string", &notiz::getTitle, &notiz::setTitle, false ) );
	entry->addProperty( new StringProperty< notiz >( "Body" , "string", &notiz::getBody, &notiz::setBody, true ) );
	return entry;
 }
