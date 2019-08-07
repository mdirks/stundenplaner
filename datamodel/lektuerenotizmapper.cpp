// 
 // C++ Implementation: lektuerenotizmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "lektuerenotizmapper.h"
 #include "services/utils/utils.h"
 #include "lektuerenotiz.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 lektuerenotizmapper* lektuerenotizmapper::instance=0;
 
 lektuerenotizmapper* lektuerenotizmapper::getInstance()
 {
 	if(!instance){
 		instance=new lektuerenotizmapper();
 	}
 	return instance;
 }


 lektuerenotizmapper::lektuerenotizmapper()
  {
 	version = "0.3-0.4";
	columns = new string[3];
 	columnTypes = new string[3];
 	columns[0] = "notiz";
 	columnTypes[0] = "int";
	mapProperties["notiz"] = new Property("notiz");
	columns[1] = "title";
 	columnTypes[1] = "varchar(30)";
	mapProperties["title"] = new Property("title");
	columns[2] = "body";
 	columnTypes[2] = "text";
	mapProperties["body"] = new Property("body");
}


lektuerenotizmapper::~lektuerenotizmapper(){}


 PObject* lektuerenotizmapper::createNewObject()
 {
     return new lektuerenotiz();
 }


 lektuerenotiz* lektuerenotizmapper::create()
 {
     return  (lektuerenotiz*) AbstractMapper::create( lektuerenotizmapper::getInstance() );
 }


 string lektuerenotizmapper::getTableName()
 {
     return string("lektuerenotiz");
 }
 
 string lektuerenotizmapper::getClassName()
 {
 	return string("lektuerenotiz");
 }
 
 string* lektuerenotizmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* lektuerenotizmapper::getColumns()
 {
 	return columns;
 }
 
 int lektuerenotizmapper::getColumnCount()
 {
     return 3;
 }


 string* lektuerenotizmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[3];  
 	lektuerenotiz *o = (lektuerenotiz*) realSubject;
	values[0] = to_string(o->getSeite());
	values[1] = to_string(o->getTitle());
	values[2] = to_string(o->getBody());
return values;
 }


 void lektuerenotizmapper::save(){
qWarning("lektuerenotiz: save() not implemented");
}

void lektuerenotizmapper::save(PObject *realSubject)
{
 	lektuerenotiz *o = (lektuerenotiz*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	notizmapper::save(realSubject);
}


void lektuerenotizmapper::init(PObject* inito, Variant *res)
 {
 	lektuerenotiz *o = (lektuerenotiz*) inito;
	o->setSeite( res[0].asint());
 	o->setTitle( res[1].asstring());
 	o->setBody( res[2].asstring());
 	inito->init();
}


 list<lektuerenotiz *>*lektuerenotizmapper::find() 
 {
 	return (list <lektuerenotiz*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* lektuerenotizmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "lektuerenotiz" ); 
	entry->addProperty( new StringProperty<lektuerenotiz>("Name", "string", &lektuerenotiz::getName, &lektuerenotiz::setName, false) );
	entry->addProperty( new NumericProperty< int,lektuerenotiz> ( "Seite", "int" , &lektuerenotiz::getSeite,&lektuerenotiz::setSeite ) ); 
	entry->addProperty( new StringProperty< lektuerenotiz >( "Title" , "string", &lektuerenotiz::getTitle, &lektuerenotiz::setTitle, false ) );
	entry->addProperty( new StringProperty< lektuerenotiz >( "Body" , "string", &lektuerenotiz::getBody, &lektuerenotiz::setBody, true ) );
	entry->registerBase( "notiz" );
	return entry;
 }
