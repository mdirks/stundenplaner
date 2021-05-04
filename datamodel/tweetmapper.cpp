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
 	version = "0.3-0.4";
	columns = new string[2];
 	columnTypes = new string[2];
 	columns[0] = "title";
 	columnTypes[0] = "varchar(30)";
	mapProperties["title"] = new Property("title");
	columns[1] = "body";
 	columnTypes[1] = "text";
	mapProperties["body"] = new Property("body");
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
     return 2;
 }


 string* tweetmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[2];  
 	tweet *o = (tweet*) realSubject;
	values[0] = to_string(o->getTitle());
	values[1] = to_string(o->getBody());
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
	o->setTitle( res[0].asstring());
 	o->setBody( res[1].asstring());
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
	entry->addProperty( new StringProperty< tweet >( "Title" , "string", &tweet::getTitle, &tweet::setTitle, false ) );
	entry->addProperty( new StringProperty< tweet >( "Body" , "string", &tweet::getBody, &tweet::setBody, true ) );
	entry->registerBase( "notiz" );
	return entry;
 }
