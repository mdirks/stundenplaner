// 
 // C++ Implementation: ThemaItemmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "themaitemmapper.h"
 #include "utils/utils.h"
 #include "themaitem.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 ThemaItemmapper* ThemaItemmapper::instance=0;
 
 ThemaItemmapper* ThemaItemmapper::getInstance()
 {
 	if(!instance){
 		instance=new ThemaItemmapper();
 	}
 	return instance;
 }


 ThemaItemmapper::ThemaItemmapper()
  {
 	version = "0.2";
	columns = new string[0];
 	columnTypes = new string[0];
 mapReferences["Thema"] = new Reference("ThemaItem","datamodel/thema");
}


ThemaItemmapper::~ThemaItemmapper(){}


 PObject* ThemaItemmapper::createNewObject()
 {
     return new ThemaItem();
 }


 ThemaItem* ThemaItemmapper::create()
 {
     return  (ThemaItem*) AbstractMapper::create( ThemaItemmapper::getInstance() );
 }


 string ThemaItemmapper::getTableName()
 {
     return string("themaitem");
 }
 
 string ThemaItemmapper::getClassName()
 {
 	return string("ThemaItem");
 }
 
 string* ThemaItemmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* ThemaItemmapper::getColumns()
 {
 	return columns;
 }
 
 int ThemaItemmapper::getColumnCount()
 {
     return 0;
 }


 string* ThemaItemmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	ThemaItem *o = (ThemaItem*) realSubject;
return values;
 }


 void ThemaItemmapper::save(){
qWarning("ThemaItem: save() not implemented");
}

void ThemaItemmapper::save(PObject *realSubject)
{
 	ThemaItem *o = (ThemaItem*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	mapReferences[ "Thema" ] -> save(realSubject, (PObject*) o->getThema());
}


void ThemaItemmapper::init(PObject* inito, Variant *res)
 {
 	ThemaItem *o = (ThemaItem*) inito;
	inito->init();
}


 list<ThemaItem *>*ThemaItemmapper::find() 
 {
 	return (list <ThemaItem*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* ThemaItemmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "ThemaItem" ); 
	entry->addProperty( new StringProperty<ThemaItem>("Name", "string", &ThemaItem::getName, &ThemaItem::setName, false) );
	entry->addProperty( new PObjectProperty<thema,ThemaItem>( "Thema" , "thema", &ThemaItem::getThema,&ThemaItem::setThema ) ); 
	return entry;
 }
