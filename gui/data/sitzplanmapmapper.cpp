// 
 // C++ Implementation: SitzplanMapmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "sitzplanmapmapper.h"
 #include "services/utils/utils.h"
 #include "sitzplanmap.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 SitzplanMapmapper* SitzplanMapmapper::instance=0;
 
 SitzplanMapmapper* SitzplanMapmapper::getInstance()
 {
 	if(!instance){
 		instance=new SitzplanMapmapper();
 	}
 	return instance;
 }


 SitzplanMapmapper::SitzplanMapmapper()
  {
 	version = "0.5-0.3";
	columns = new string[0];
 	columnTypes = new string[0];
 asc_GraphicsItems = new Association<SitzplanMap, PObjectGraphicsItem>("map_item","map_id","item_id","PObjectGraphicsItem", &SitzplanMap::addToGraphicsItems, &SitzplanMap::deleteFromGraphicsItems);
mapAssociations["GraphicsItems"] = asc_GraphicsItems;
registerAssociation( asc_GraphicsItems);
mapReferences["Sitzplan"] = new Reference("SitzplanMap","datamodel/sitzplan");
mapReferences["ActiveTeilleistung"] = new Reference("SitzplanMap","datamodel/teilleistung");
}


SitzplanMapmapper::~SitzplanMapmapper(){}


 PObject* SitzplanMapmapper::createNewObject()
 {
     return new SitzplanMap();
 }


 SitzplanMap* SitzplanMapmapper::create()
 {
     return  (SitzplanMap*) AbstractMapper::create( SitzplanMapmapper::getInstance() );
 }


 string SitzplanMapmapper::getTableName()
 {
     return string("sitzplanmap");
 }
 
 string SitzplanMapmapper::getClassName()
 {
 	return string("SitzplanMap");
 }
 
 string* SitzplanMapmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* SitzplanMapmapper::getColumns()
 {
 	return columns;
 }
 
 int SitzplanMapmapper::getColumnCount()
 {
     return 0;
 }


 string* SitzplanMapmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	SitzplanMap *o = (SitzplanMap*) realSubject;
return values;
 }


 void SitzplanMapmapper::save(){
qWarning("SitzplanMap: save() not implemented");
}

void SitzplanMapmapper::save(PObject *realSubject)
{
 	SitzplanMap *o = (SitzplanMap*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_GraphicsItems -> save(realSubject, o->getGraphicsItems() );

	mapReferences[ "Sitzplan" ] -> save(realSubject, (PObject*) o->getSitzplan());
	mapReferences[ "ActiveTeilleistung" ] -> save(realSubject, (PObject*) o->getActiveTeilleistung());
	GenericMapmapper::save(realSubject);
}


void SitzplanMapmapper::init(PObject* inito, Variant *res)
 {
 	SitzplanMap *o = (SitzplanMap*) inito;
	inito->init();
}


 list<SitzplanMap *>*SitzplanMapmapper::find() 
 {
 	return (list <SitzplanMap*>*) Database::getInstance()->getAll(this); 
}


list<PObjectGraphicsItem*> * SitzplanMapmapper::findGraphicsItems(int pri_id) 
 { 
 	return asc_GraphicsItems ->  findAssociates( pri_id );
     }


list<PObjectGraphicsItem*> * SitzplanMapmapper::findGraphicsItems(int pri_id,string prop,string value) 
         { 
             return asc_GraphicsItems ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* SitzplanMapmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "SitzplanMap" ); 
	entry->addProperty( new StringProperty<SitzplanMap>("Name", "string", &SitzplanMap::getName, &SitzplanMap::setName, false) );
	entry->addProperty( new CollectionPropertyImpl<PObjectGraphicsItem,SitzplanMap>( "GraphicsItems" , "PObjectGraphicsItem", &SitzplanMap::getGraphicsItems, &SitzplanMap::addToGraphicsItems, &SitzplanMap::deleteFromGraphicsItems  ) ); 
	entry->addProperty( new PObjectProperty<sitzplan,SitzplanMap>( "Sitzplan" , "sitzplan", &SitzplanMap::getSitzplan,&SitzplanMap::setSitzplan ) ); 
	entry->addProperty( new PObjectProperty<teilleistung,SitzplanMap>( "ActiveTeilleistung" , "teilleistung", &SitzplanMap::getActiveTeilleistung,&SitzplanMap::setActiveTeilleistung ) ); 
	entry->registerBase( "GenericMap" );
	return entry;
 }
