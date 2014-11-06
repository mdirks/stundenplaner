// 
 // C++ Implementation: tagmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "tagmapper.h"
 #include "services/utils/utils.h"
 #include "tag.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 tagmapper* tagmapper::instance=0;
 
 tagmapper* tagmapper::getInstance()
 {
 	if(!instance){
 		instance=new tagmapper();
 	}
 	return instance;
 }


 tagmapper::tagmapper()
  {
 	version = "0.2";
	columns = new string[1];
 	columnTypes = new string[1];
 	columns[0] = "datum";
 	columnTypes[0] = "varchar(30)";
	mapProperties["datum"] = new Property("datum");
}


tagmapper::~tagmapper(){}


 PObject* tagmapper::createNewObject()
 {
     return new tag();
 }


 tag* tagmapper::create()
 {
     return  (tag*) AbstractMapper::create( tagmapper::getInstance() );
 }


 string tagmapper::getTableName()
 {
     return string("tag");
 }
 
 string tagmapper::getClassName()
 {
 	return string("tag");
 }
 
 string* tagmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* tagmapper::getColumns()
 {
 	return columns;
 }
 
 int tagmapper::getColumnCount()
 {
     return 1;
 }


 string* tagmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[1];  
 	tag *o = (tag*) realSubject;
	values[0] = to_string(o->getDatum());
return values;
 }


 void tagmapper::save(){
qWarning("tag: save() not implemented");
}

void tagmapper::save(PObject *realSubject)
{
 	tag *o = (tag*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
}


void tagmapper::init(PObject* inito, Variant *res)
 {
 	tag *o = (tag*) inito;
	o->setDatum( res[0].asQDate());
 	inito->init();
}


 list<tag *>*tagmapper::find() 
 {
 	return (list <tag*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* tagmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "tag" ); 
	entry->addProperty( new StringProperty<tag>("Name", "string", &tag::getName, &tag::setName, false) );
	entry->addProperty( new DateProperty< tag> ( "Datum", "QDate" , &tag::getDatum, &tag::setDatum ) ); 
	return entry;
 }
