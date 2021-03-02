// 
 // C++ Implementation: tweetmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "tweetmapper.h"
 #include "services/utils/utils.h"
 #include "tweet.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 tweetmapper* tweetmapper::instance=0;
 
 tweetmapper* tweetmapper::getInstance()
 {
 	if(!instance){
 		instance=new tweetmapper();
 	}
 	return instance;
 }


 tweetmapper::tweetmapper()
  {
 	version = "0.2";
	columns = new string[0];
 	columnTypes = new string[0];
 }


tweetmapper::~tweetmapper(){}


 PObject* tweetmapper::createNewObject()
 {
     return new tweet();
 }


 tweet* tweetmapper::create()
 {
     return  (tweet*) AbstractMapper::create( tweetmapper::getInstance() );
 }


 string tweetmapper::getTableName()
 {
     return string("tweet");
 }
 
 string tweetmapper::getClassName()
 {
 	return string("tweet");
 }
 
 string* tweetmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* tweetmapper::getColumns()
 {
 	return columns;
 }
 
 int tweetmapper::getColumnCount()
 {
     return 0;
 }


 string* tweetmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	tweet *o = (tweet*) realSubject;
return values;
 }


 void tweetmapper::save(){
qWarning("tweet: save() not implemented");
}

void tweetmapper::save(PObject *realSubject)
{
 	tweet *o = (tweet*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	notizmapper::save(realSubject);
}


void tweetmapper::init(PObject* inito, Variant *res)
 {
 	tweet *o = (tweet*) inito;
	inito->init();
}


 list<tweet *>*tweetmapper::find() 
 {
 	return (list <tweet*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* tweetmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "tweet" ); 
	entry->addProperty( new StringProperty<tweet>("Name", "string", &tweet::getName, &tweet::setName, false) );
	entry->registerBase( "notiz" );
	return entry;
 }
