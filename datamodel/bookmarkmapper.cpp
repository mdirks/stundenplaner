// 
 // C++ Implementation: bookmarkmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "bookmarkmapper.h"
 #include "services/utils/utils.h"
 #include "bookmark.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 bookmarkmapper* bookmarkmapper::instance=0;
 
 bookmarkmapper* bookmarkmapper::getInstance()
 {
 	if(!instance){
 		instance=new bookmarkmapper();
 	}
 	return instance;
 }


 bookmarkmapper::bookmarkmapper()
  {
 	version = "0.1";
	columns = new string[2];
 	columnTypes = new string[2];
 	columns[0] = "beschreibung";
 	columnTypes[0] = "text";
	mapProperties["beschreibung"] = new Property("beschreibung");
	columns[1] = "position";
 	columnTypes[1] = "int";
	mapProperties["position"] = new Property("position");
mapReferences["Ziel"] = new Reference("bookmark","orm/transactions/TransactionObject");
mapReferences["Verweis"] = new Reference("bookmark","orm/transactions/TransactionObject");
}


bookmarkmapper::~bookmarkmapper(){}


 PObject* bookmarkmapper::createNewObject()
 {
     return new bookmark();
 }


 bookmark* bookmarkmapper::create()
 {
     return  (bookmark*) AbstractMapper::create( bookmarkmapper::getInstance() );
 }


 string bookmarkmapper::getTableName()
 {
     return string("bookmark");
 }
 
 string bookmarkmapper::getClassName()
 {
 	return string("bookmark");
 }
 
 string* bookmarkmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* bookmarkmapper::getColumns()
 {
 	return columns;
 }
 
 int bookmarkmapper::getColumnCount()
 {
     return 2;
 }


 string* bookmarkmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[2];  
 	bookmark *o = (bookmark*) realSubject;
	values[0] = to_string(o->getBeschreibung());
	values[1] = to_string(o->getPosition());
return values;
 }


 void bookmarkmapper::save(){
qWarning("bookmark: save() not implemented");
}

void bookmarkmapper::save(PObject *realSubject)
{
 	bookmark *o = (bookmark*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	mapReferences[ "Ziel" ] -> save(realSubject, (PObject*) o->getZiel());
	mapReferences[ "Verweis" ] -> save(realSubject, (PObject*) o->getVerweis());
}


void bookmarkmapper::init(PObject* inito, Variant *res)
 {
 	bookmark *o = (bookmark*) inito;
	o->setBeschreibung( res[0].asstring());
 	o->setPosition( res[1].asint());
 	inito->init();
}


 list<bookmark *>*bookmarkmapper::find() 
 {
 	return (list <bookmark*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* bookmarkmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "bookmark" ); 
	entry->addProperty( new StringProperty<bookmark>("Name", "string", &bookmark::getName, &bookmark::setName, false) );
	entry->addProperty( new StringProperty< bookmark >( "Beschreibung" , "string", &bookmark::getBeschreibung, &bookmark::setBeschreibung, true ) );
	entry->addProperty( new NumericProperty< int,bookmark> ( "Position", "int" , &bookmark::getPosition,&bookmark::setPosition ) ); 
	entry->addProperty( new PObjectProperty<TransactionObject,bookmark>( "Ziel" , "TransactionObject", &bookmark::getZiel,&bookmark::setZiel ) ); 
	entry->addProperty( new PObjectProperty<TransactionObject,bookmark>( "Verweis" , "TransactionObject", &bookmark::getVerweis,&bookmark::setVerweis ) ); 
	return entry;
 }
