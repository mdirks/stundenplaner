// 
 // C++ Implementation: ferientagmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "ferientagmapper.h"
 #include "services/utils/utils.h"
 #include "ferientag.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 ferientagmapper* ferientagmapper::instance=0;
 
 ferientagmapper* ferientagmapper::getInstance()
 {
 	if(!instance){
 		instance=new ferientagmapper();
 	}
 	return instance;
 }


 ferientagmapper::ferientagmapper()
  {
 	version = "0.1";
	columns = new string[2];
 	columnTypes = new string[2];
 	columns[0] = "datum";
 	columnTypes[0] = "varchar(30)";
	mapProperties["datum"] = new Property("datum");
	columns[1] = "title";
 	columnTypes[1] = "varchar(30)";
	mapProperties["title"] = new Property("title");
}


ferientagmapper::~ferientagmapper(){}


 PObject* ferientagmapper::createNewObject()
 {
     return new ferientag();
 }


 ferientag* ferientagmapper::create()
 {
     return  (ferientag*) AbstractMapper::create( ferientagmapper::getInstance() );
 }


 string ferientagmapper::getTableName()
 {
     return string("ferientag");
 }
 
 string ferientagmapper::getClassName()
 {
 	return string("ferientag");
 }
 
 string* ferientagmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* ferientagmapper::getColumns()
 {
 	return columns;
 }
 
 int ferientagmapper::getColumnCount()
 {
     return 2;
 }


 string* ferientagmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[2];  
 	ferientag *o = (ferientag*) realSubject;
	values[0] = to_string(o->getDatum());
	values[1] = to_string(o->getTitle());
return values;
 }


 void ferientagmapper::save(){
qWarning("ferientag: save() not implemented");
}

void ferientagmapper::save(PObject *realSubject)
{
 	ferientag *o = (ferientag*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
}


void ferientagmapper::init(PObject* inito, Variant *res)
 {
 	ferientag *o = (ferientag*) inito;
	o->setDatum( res[0].asQDate());
 	o->setTitle( res[1].asstring());
 	inito->init();
}


 list<ferientag *>*ferientagmapper::find() 
 {
 	return (list <ferientag*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* ferientagmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "ferientag" ); 
	entry->addProperty( new StringProperty<ferientag>("Name", "string", &ferientag::getName, &ferientag::setName, false) );
	entry->addProperty( new DateProperty< ferientag> ( "Datum", "QDate" , &ferientag::getDatum, &ferientag::setDatum ) ); 
	entry->addProperty( new StringProperty< ferientag >( "Title" , "string", &ferientag::getTitle, &ferientag::setTitle, false ) );
	return entry;
 }
