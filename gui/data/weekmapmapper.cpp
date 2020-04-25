// 
 // C++ Implementation: WeekMapmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "weekmapmapper.h"
 #include "services/utils/utils.h"
 #include "weekmap.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 WeekMapmapper* WeekMapmapper::instance=0;
 
 WeekMapmapper* WeekMapmapper::getInstance()
 {
 	if(!instance){
 		instance=new WeekMapmapper();
 	}
 	return instance;
 }


 WeekMapmapper::WeekMapmapper()
  {
 	version = "0.4";
	columns = new string[1];
 	columnTypes = new string[1];
 	columns[0] = "datum";
 	columnTypes[0] = "varchar(30)";
	mapProperties["datum"] = new Property("datum");
asc_GraphicsItems = new Association<WeekMap, PObjectGraphicsItem>("map_item","map_id","item_id","PObjectGraphicsItem", &WeekMap::addToGraphicsItems, &WeekMap::deleteFromGraphicsItems);
mapAssociations["GraphicsItems"] = asc_GraphicsItems;
registerAssociation( asc_GraphicsItems);
mapReferences["Stundenplan"] = new Reference("WeekMap","datamodel/stundenplan");
}


WeekMapmapper::~WeekMapmapper(){}


 PObject* WeekMapmapper::createNewObject()
 {
     return new WeekMap();
 }


 WeekMap* WeekMapmapper::create()
 {
     return  (WeekMap*) AbstractMapper::create( WeekMapmapper::getInstance() );
 }


 string WeekMapmapper::getTableName()
 {
     return string("weekmap");
 }
 
 string WeekMapmapper::getClassName()
 {
 	return string("WeekMap");
 }
 
 string* WeekMapmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* WeekMapmapper::getColumns()
 {
 	return columns;
 }
 
 int WeekMapmapper::getColumnCount()
 {
     return 1;
 }


 string* WeekMapmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[1];  
 	WeekMap *o = (WeekMap*) realSubject;
	values[0] = to_string(o->getStartDate());
return values;
 }


 void WeekMapmapper::save(){
qWarning("WeekMap: save() not implemented");
}

void WeekMapmapper::save(PObject *realSubject)
{
 	WeekMap *o = (WeekMap*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_GraphicsItems -> save(realSubject, o->getGraphicsItems() );

	mapReferences[ "Stundenplan" ] -> save(realSubject, (PObject*) o->getStundenplan());
}


void WeekMapmapper::init(PObject* inito, Variant *res)
 {
 	WeekMap *o = (WeekMap*) inito;
	o->setStartDate( res[0].asQDate());
 	inito->init();
}


 list<WeekMap *>*WeekMapmapper::find() 
 {
 	return (list <WeekMap*>*) Database::getInstance()->getAll(this); 
}


list<PObjectGraphicsItem*> * WeekMapmapper::findGraphicsItems(int pri_id) 
 { 
 	return asc_GraphicsItems ->  findAssociates( pri_id );
     }


list<PObjectGraphicsItem*> * WeekMapmapper::findGraphicsItems(int pri_id,string prop,string value) 
         { 
             return asc_GraphicsItems ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* WeekMapmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "WeekMap" ); 
	entry->addProperty( new StringProperty<WeekMap>("Name", "string", &WeekMap::getName, &WeekMap::setName, false) );
	entry->addProperty( new DateProperty< WeekMap> ( "StartDate", "QDate" , &WeekMap::getStartDate, &WeekMap::setStartDate ) ); 
	entry->addProperty( new CollectionPropertyImpl<PObjectGraphicsItem,WeekMap>( "GraphicsItems" , "PObjectGraphicsItem", &WeekMap::getGraphicsItems, &WeekMap::addToGraphicsItems, &WeekMap::deleteFromGraphicsItems  ) ); 
	entry->addProperty( new PObjectProperty<stundenplan,WeekMap>( "Stundenplan" , "stundenplan", &WeekMap::getStundenplan,&WeekMap::setStundenplan ) ); 
	return entry;
 }
