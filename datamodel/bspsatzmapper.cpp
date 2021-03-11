// 
 // C++ Implementation: bspsatzmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "bspsatzmapper.h"
 #include "services/utils/utils.h"
 #include "bspsatz.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 bspsatzmapper* bspsatzmapper::instance=0;
 
 bspsatzmapper* bspsatzmapper::getInstance()
 {
 	if(!instance){
 		instance=new bspsatzmapper();
 	}
 	return instance;
 }


 bspsatzmapper::bspsatzmapper()
  {
 	version = "0.1";
	columns = new string[0];
 	columnTypes = new string[0];
 }


bspsatzmapper::~bspsatzmapper(){}


 PObject* bspsatzmapper::createNewObject()
 {
     return new bspsatz();
 }


 bspsatz* bspsatzmapper::create()
 {
     return  (bspsatz*) AbstractMapper::create( bspsatzmapper::getInstance() );
 }


 string bspsatzmapper::getTableName()
 {
     return string("bspsatz");
 }
 
 string bspsatzmapper::getClassName()
 {
 	return string("bspsatz");
 }
 
 string* bspsatzmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* bspsatzmapper::getColumns()
 {
 	return columns;
 }
 
 int bspsatzmapper::getColumnCount()
 {
     return 0;
 }


 string* bspsatzmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	bspsatz *o = (bspsatz*) realSubject;
return values;
 }


 void bspsatzmapper::save(){
qWarning("bspsatz: save() not implemented");
}

void bspsatzmapper::save(PObject *realSubject)
{
 	bspsatz *o = (bspsatz*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	vokabelmapper::save(realSubject);
}


void bspsatzmapper::init(PObject* inito, Variant *res)
 {
 	bspsatz *o = (bspsatz*) inito;
	inito->init();
}


 list<bspsatz *>*bspsatzmapper::find() 
 {
 	return (list <bspsatz*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* bspsatzmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "bspsatz" ); 
	entry->addProperty( new StringProperty<bspsatz>("Name", "string", &bspsatz::getName, &bspsatz::setName, false) );
	entry->registerBase( "vokabel" );
	return entry;
 }
