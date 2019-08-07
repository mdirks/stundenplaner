// 
 // C++ Implementation: StundenplaneintragGraphicsItemmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "stundenplaneintraggraphicsitemmapper.h"
 #include "utils/utils.h"
 #include "stundenplaneintraggraphicsitem.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 StundenplaneintragGraphicsItemmapper* StundenplaneintragGraphicsItemmapper::instance=0;
 
 StundenplaneintragGraphicsItemmapper* StundenplaneintragGraphicsItemmapper::getInstance()
 {
 	if(!instance){
 		instance=new StundenplaneintragGraphicsItemmapper();
 	}
 	return instance;
 }


 StundenplaneintragGraphicsItemmapper::StundenplaneintragGraphicsItemmapper()
  {
 	version = "0.1";
	columns = new string[0];
 	columnTypes = new string[0];
 }


StundenplaneintragGraphicsItemmapper::~StundenplaneintragGraphicsItemmapper(){}


 PObject* StundenplaneintragGraphicsItemmapper::createNewObject()
 {
     return new StundenplaneintragGraphicsItem();
 }


 StundenplaneintragGraphicsItem* StundenplaneintragGraphicsItemmapper::create()
 {
     return  (StundenplaneintragGraphicsItem*) AbstractMapper::create( StundenplaneintragGraphicsItemmapper::getInstance() );
 }


 string StundenplaneintragGraphicsItemmapper::getTableName()
 {
     return string("stundenplaneintraggraphicsitem");
 }
 
 string StundenplaneintragGraphicsItemmapper::getClassName()
 {
 	return string("StundenplaneintragGraphicsItem");
 }
 
 string* StundenplaneintragGraphicsItemmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* StundenplaneintragGraphicsItemmapper::getColumns()
 {
 	return columns;
 }
 
 int StundenplaneintragGraphicsItemmapper::getColumnCount()
 {
     return 0;
 }


 string* StundenplaneintragGraphicsItemmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	StundenplaneintragGraphicsItem *o = (StundenplaneintragGraphicsItem*) realSubject;
return values;
 }


 void StundenplaneintragGraphicsItemmapper::save(){
qWarning("StundenplaneintragGraphicsItem: save() not implemented");
}

void StundenplaneintragGraphicsItemmapper::save(PObject *realSubject)
{
 	StundenplaneintragGraphicsItem *o = (StundenplaneintragGraphicsItem*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	PObjectGraphicsItemmapper::save(realSubject);
}


void StundenplaneintragGraphicsItemmapper::init(PObject* inito, Variant *res)
 {
 	StundenplaneintragGraphicsItem *o = (StundenplaneintragGraphicsItem*) inito;
	inito->init();
}


 list<StundenplaneintragGraphicsItem *>*StundenplaneintragGraphicsItemmapper::find() 
 {
 	return (list <StundenplaneintragGraphicsItem*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* StundenplaneintragGraphicsItemmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "StundenplaneintragGraphicsItem" ); 
	entry->addProperty( new StringProperty<StundenplaneintragGraphicsItem>("Name", "string", &StundenplaneintragGraphicsItem::getName, &StundenplaneintragGraphicsItem::setName, false) );
	entry->registerBase( "PObjectGraphicsItem" );
	return entry;
 }
