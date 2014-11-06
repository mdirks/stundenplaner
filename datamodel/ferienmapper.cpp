// 
 // C++ Implementation: ferienmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "ferienmapper.h"
 #include "services/utils/utils.h"
 #include "ferien.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 ferienmapper* ferienmapper::instance=0;
 
 ferienmapper* ferienmapper::getInstance()
 {
 	if(!instance){
 		instance=new ferienmapper();
 	}
 	return instance;
 }


 ferienmapper::ferienmapper()
  {
 	version = "0.1";
	columns = new string[3];
 	columnTypes = new string[3];
 	columns[0] = "von";
 	columnTypes[0] = "varchar(30)";
	mapProperties["von"] = new Property("von");
	columns[1] = "bis";
 	columnTypes[1] = "varchar(30)";
	mapProperties["bis"] = new Property("bis");
	columns[2] = "title";
 	columnTypes[2] = "varchar(30)";
	mapProperties["title"] = new Property("title");
}


ferienmapper::~ferienmapper(){}


 PObject* ferienmapper::createNewObject()
 {
     return new ferien();
 }


 ferien* ferienmapper::create()
 {
     return  (ferien*) AbstractMapper::create( ferienmapper::getInstance() );
 }


 string ferienmapper::getTableName()
 {
     return string("ferien");
 }
 
 string ferienmapper::getClassName()
 {
 	return string("ferien");
 }
 
 string* ferienmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* ferienmapper::getColumns()
 {
 	return columns;
 }
 
 int ferienmapper::getColumnCount()
 {
     return 3;
 }


 string* ferienmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[3];  
 	ferien *o = (ferien*) realSubject;
	values[0] = to_string(o->getVon());
	values[1] = to_string(o->getBis());
	values[2] = to_string(o->getTitle());
return values;
 }


 void ferienmapper::save(){
qWarning("ferien: save() not implemented");
}

void ferienmapper::save(PObject *realSubject)
{
 	ferien *o = (ferien*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
}


void ferienmapper::init(PObject* inito, Variant *res)
 {
 	ferien *o = (ferien*) inito;
	o->setVon( res[0].asQDate());
 	o->setBis( res[1].asQDate());
 	o->setTitle( res[2].asstring());
 	inito->init();
}


 list<ferien *>*ferienmapper::find() 
 {
 	return (list <ferien*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* ferienmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "ferien" ); 
	entry->addProperty( new StringProperty<ferien>("Name", "string", &ferien::getName, &ferien::setName, false) );
	entry->addProperty( new DateProperty< ferien> ( "Von", "QDate" , &ferien::getVon, &ferien::setVon ) ); 
	entry->addProperty( new DateProperty< ferien> ( "Bis", "QDate" , &ferien::getBis, &ferien::setBis ) ); 
	entry->addProperty( new StringProperty< ferien >( "Title" , "string", &ferien::getTitle, &ferien::setTitle, false ) );
	return entry;
 }
