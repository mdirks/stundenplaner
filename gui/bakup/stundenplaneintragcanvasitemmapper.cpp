// 
 // C++ Implementation: StundenplaneintragCanvasItemmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "stundenplaneintragcanvasitemmapper.h"
 #include "utils/utils.h"
 #include "stundenplaneintragcanvasitem.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 StundenplaneintragCanvasItemmapper* StundenplaneintragCanvasItemmapper::instance=0;
 
 StundenplaneintragCanvasItemmapper* StundenplaneintragCanvasItemmapper::getInstance()
 {
 	if(!instance){
 		instance=new StundenplaneintragCanvasItemmapper();
 	}
 	return instance;
 }


 StundenplaneintragCanvasItemmapper::StundenplaneintragCanvasItemmapper()
  {
 	version = "0.1";
	columns = new string[0];
 	columnTypes = new string[0];
 }


StundenplaneintragCanvasItemmapper::~StundenplaneintragCanvasItemmapper(){}


 PObject* StundenplaneintragCanvasItemmapper::createNewObject()
 {
     return new StundenplaneintragCanvasItem();
 }


 StundenplaneintragCanvasItem* StundenplaneintragCanvasItemmapper::create()
 {
     return  (StundenplaneintragCanvasItem*) AbstractMapper::create( StundenplaneintragCanvasItemmapper::getInstance() );
 }


 string StundenplaneintragCanvasItemmapper::getTableName()
 {
     return string("stundenplaneintragcanvasitem");
 }
 
 string StundenplaneintragCanvasItemmapper::getClassName()
 {
 	return string("StundenplaneintragCanvasItem");
 }
 
 string* StundenplaneintragCanvasItemmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* StundenplaneintragCanvasItemmapper::getColumns()
 {
 	return columns;
 }
 
 int StundenplaneintragCanvasItemmapper::getColumnCount()
 {
     return 0;
 }


 string* StundenplaneintragCanvasItemmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	StundenplaneintragCanvasItem *o = (StundenplaneintragCanvasItem*) realSubject;
return values;
 }


 void StundenplaneintragCanvasItemmapper::save(){
qWarning("StundenplaneintragCanvasItem: save() not implemented");
}

void StundenplaneintragCanvasItemmapper::save(PObject *realSubject)
{
 	StundenplaneintragCanvasItem *o = (StundenplaneintragCanvasItem*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	PObjectCanvasItemmapper::save(realSubject);
}


void StundenplaneintragCanvasItemmapper::init(PObject* inito, Variant *res)
 {
 	StundenplaneintragCanvasItem *o = (StundenplaneintragCanvasItem*) inito;
	inito->init();
}


 list<StundenplaneintragCanvasItem *>*StundenplaneintragCanvasItemmapper::find() 
 {
 	return (list <StundenplaneintragCanvasItem*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* StundenplaneintragCanvasItemmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "StundenplaneintragCanvasItem" ); 
	entry->addProperty( new StringProperty<StundenplaneintragCanvasItem>("Name", "string", &StundenplaneintragCanvasItem::getName, &StundenplaneintragCanvasItem::setName, false) );
	entry->registerBase( "PObjectCanvasItem" );
	return entry;
 }
