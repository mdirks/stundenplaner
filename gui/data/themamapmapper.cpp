// 
 // C++ Implementation: ThemaMapmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "themamapmapper.h"
 #include "services/utils/utils.h"
 #include "themamap.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 ThemaMapmapper* ThemaMapmapper::instance=0;
 
 ThemaMapmapper* ThemaMapmapper::getInstance()
 {
 	if(!instance){
 		instance=new ThemaMapmapper();
 	}
 	return instance;
 }


 ThemaMapmapper::ThemaMapmapper()
  {
 	version = "0.5-0.3";
	columns = new string[0];
 	columnTypes = new string[0];
 asc_GraphicsItems = new Association<ThemaMap, PObjectGraphicsItem>("map_item","map_id","item_id","PObjectGraphicsItem", &ThemaMap::addToGraphicsItems, &ThemaMap::deleteFromGraphicsItems);
mapAssociations["GraphicsItems"] = asc_GraphicsItems;
registerAssociation( asc_GraphicsItems);
mapReferences["Thema"] = new Reference("ThemaMap","datamodel/thema");
}


ThemaMapmapper::~ThemaMapmapper(){}


 PObject* ThemaMapmapper::createNewObject()
 {
     return new ThemaMap();
 }


 ThemaMap* ThemaMapmapper::create()
 {
     return  (ThemaMap*) AbstractMapper::create( ThemaMapmapper::getInstance() );
 }


 string ThemaMapmapper::getTableName()
 {
     return string("themamap");
 }
 
 string ThemaMapmapper::getClassName()
 {
 	return string("ThemaMap");
 }
 
 string* ThemaMapmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* ThemaMapmapper::getColumns()
 {
 	return columns;
 }
 
 int ThemaMapmapper::getColumnCount()
 {
     return 0;
 }


 string* ThemaMapmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	ThemaMap *o = (ThemaMap*) realSubject;
return values;
 }


 void ThemaMapmapper::save(){
qWarning("ThemaMap: save() not implemented");
}

void ThemaMapmapper::save(PObject *realSubject)
{
 	ThemaMap *o = (ThemaMap*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_GraphicsItems -> save(realSubject, o->getGraphicsItems() );

	mapReferences[ "Thema" ] -> save(realSubject, (PObject*) o->getThema());
	GenericMapmapper::save(realSubject);
}


void ThemaMapmapper::init(PObject* inito, Variant *res)
 {
 	ThemaMap *o = (ThemaMap*) inito;
	inito->init();
}


 list<ThemaMap *>*ThemaMapmapper::find() 
 {
 	return (list <ThemaMap*>*) Database::getInstance()->getAll(this); 
}


list<PObjectGraphicsItem*> * ThemaMapmapper::findGraphicsItems(int pri_id) 
 { 
 	return asc_GraphicsItems ->  findAssociates( pri_id );
     }


list<PObjectGraphicsItem*> * ThemaMapmapper::findGraphicsItems(int pri_id,string prop,string value) 
         { 
             return asc_GraphicsItems ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* ThemaMapmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "ThemaMap" ); 
	entry->addProperty( new StringProperty<ThemaMap>("Name", "string", &ThemaMap::getName, &ThemaMap::setName, false) );
	entry->addProperty( new CollectionPropertyImpl<PObjectGraphicsItem,ThemaMap>( "GraphicsItems" , "PObjectGraphicsItem", &ThemaMap::getGraphicsItems, &ThemaMap::addToGraphicsItems, &ThemaMap::deleteFromGraphicsItems  ) ); 
	entry->addProperty( new PObjectProperty<thema,ThemaMap>( "Thema" , "thema", &ThemaMap::getThema,&ThemaMap::setThema ) ); 
	entry->registerBase( "GenericMap" );
	return entry;
 }
