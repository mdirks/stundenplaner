// 
 // C++ Implementation: DayMapmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "daymapmapper.h"
 #include "services/utils/utils.h"
 #include "daymap.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 DayMapmapper* DayMapmapper::instance=0;
 
 DayMapmapper* DayMapmapper::getInstance()
 {
 	if(!instance){
 		instance=new DayMapmapper();
 	}
 	return instance;
 }


 DayMapmapper::DayMapmapper()
  {
 	version = "0.2";
	columns = new string[1];
 	columnTypes = new string[1];
 	columns[0] = "datum";
 	columnTypes[0] = "varchar(30)";
	mapProperties["datum"] = new Property("datum");
asc_GraphicsItems = new Association<DayMap, PObjectGraphicsItem>("map_item","map_id","item_id","PObjectGraphicsItem", &DayMap::addToGraphicsItems, &DayMap::deleteFromGraphicsItems);
mapAssociations["GraphicsItems"] = asc_GraphicsItems;
registerAssociation( asc_GraphicsItems);
}


DayMapmapper::~DayMapmapper(){}


 PObject* DayMapmapper::createNewObject()
 {
     return new DayMap();
 }


 DayMap* DayMapmapper::create()
 {
     return  (DayMap*) AbstractMapper::create( DayMapmapper::getInstance() );
 }


 string DayMapmapper::getTableName()
 {
     return string("daymap");
 }
 
 string DayMapmapper::getClassName()
 {
 	return string("DayMap");
 }
 
 string* DayMapmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* DayMapmapper::getColumns()
 {
 	return columns;
 }
 
 int DayMapmapper::getColumnCount()
 {
     return 1;
 }


 string* DayMapmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[1];  
 	DayMap *o = (DayMap*) realSubject;
	values[0] = to_string(o->getDate());
return values;
 }


 void DayMapmapper::save(){
qWarning("DayMap: save() not implemented");
}

void DayMapmapper::save(PObject *realSubject)
{
 	DayMap *o = (DayMap*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_GraphicsItems -> save(realSubject, o->getGraphicsItems() );

}


void DayMapmapper::init(PObject* inito, Variant *res)
 {
 	DayMap *o = (DayMap*) inito;
	o->setDate( res[0].asQDate());
 	inito->init();
}


 list<DayMap *>*DayMapmapper::find() 
 {
 	return (list <DayMap*>*) Database::getInstance()->getAll(this); 
}


list<PObjectGraphicsItem*> * DayMapmapper::findGraphicsItems(int pri_id) 
 { 
 	return asc_GraphicsItems ->  findAssociates( pri_id );
     }


list<PObjectGraphicsItem*> * DayMapmapper::findGraphicsItems(int pri_id,string prop,string value) 
         { 
             return asc_GraphicsItems ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* DayMapmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "DayMap" ); 
	entry->addProperty( new StringProperty<DayMap>("Name", "string", &DayMap::getName, &DayMap::setName, false) );
	entry->addProperty( new DateProperty< DayMap> ( "Date", "QDate" , &DayMap::getDate, &DayMap::setDate ) ); 
	entry->addProperty( new CollectionPropertyImpl<PObjectGraphicsItem,DayMap>( "GraphicsItems" , "PObjectGraphicsItem", &DayMap::getGraphicsItems, &DayMap::addToGraphicsItems, &DayMap::deleteFromGraphicsItems  ) ); 
	return entry;
 }
