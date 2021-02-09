// 
 // C++ Implementation: GenericMapmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "genericmapmapper.h"
 #include "services/utils/utils.h"
 #include "genericmap.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 GenericMapmapper* GenericMapmapper::instance=0;
 
 GenericMapmapper* GenericMapmapper::getInstance()
 {
 	if(!instance){
 		instance=new GenericMapmapper();
 	}
 	return instance;
 }


 GenericMapmapper::GenericMapmapper()
  {
 	version = "0.3";
	columns = new string[0];
 	columnTypes = new string[0];
 asc_GraphicsItems = new Association<GenericMap, PObjectGraphicsItem>("map_item","map_id","item_id","PObjectGraphicsItem", &GenericMap::addToGraphicsItems, &GenericMap::deleteFromGraphicsItems);
mapAssociations["GraphicsItems"] = asc_GraphicsItems;
registerAssociation( asc_GraphicsItems);
}


GenericMapmapper::~GenericMapmapper(){}


 PObject* GenericMapmapper::createNewObject()
 {
     return new GenericMap();
 }


 GenericMap* GenericMapmapper::create()
 {
     return  (GenericMap*) AbstractMapper::create( GenericMapmapper::getInstance() );
 }


 string GenericMapmapper::getTableName()
 {
     return string("genericmap");
 }
 
 string GenericMapmapper::getClassName()
 {
 	return string("GenericMap");
 }
 
 string* GenericMapmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* GenericMapmapper::getColumns()
 {
 	return columns;
 }
 
 int GenericMapmapper::getColumnCount()
 {
     return 0;
 }


 string* GenericMapmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	GenericMap *o = (GenericMap*) realSubject;
return values;
 }


 void GenericMapmapper::save(){
qWarning("GenericMap: save() not implemented");
}

void GenericMapmapper::save(PObject *realSubject)
{
 	GenericMap *o = (GenericMap*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_GraphicsItems -> save(realSubject, o->getGraphicsItems() );

}


void GenericMapmapper::init(PObject* inito, Variant *res)
 {
 	GenericMap *o = (GenericMap*) inito;
	inito->init();
}


 list<GenericMap *>*GenericMapmapper::find() 
 {
 	return (list <GenericMap*>*) Database::getInstance()->getAll(this); 
}


list<PObjectGraphicsItem*> * GenericMapmapper::findGraphicsItems(int pri_id) 
 { 
 	return asc_GraphicsItems ->  findAssociates( pri_id );
     }


list<PObjectGraphicsItem*> * GenericMapmapper::findGraphicsItems(int pri_id,string prop,string value) 
         { 
             return asc_GraphicsItems ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* GenericMapmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "GenericMap" ); 
	entry->addProperty( new StringProperty<GenericMap>("Name", "string", &GenericMap::getName, &GenericMap::setName, false) );
	entry->addProperty( new CollectionPropertyImpl<PObjectGraphicsItem,GenericMap>( "GraphicsItems" , "PObjectGraphicsItem", &GenericMap::getGraphicsItems, &GenericMap::addToGraphicsItems, &GenericMap::deleteFromGraphicsItems  ) ); 
	return entry;
 }
