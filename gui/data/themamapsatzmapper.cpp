// 
 // C++ Implementation: ThemaMapSatzmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "themamapsatzmapper.h"
 #include "services/utils/utils.h"
 #include "themamapsatz.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 ThemaMapSatzmapper* ThemaMapSatzmapper::instance=0;
 
 ThemaMapSatzmapper* ThemaMapSatzmapper::getInstance()
 {
 	if(!instance){
 		instance=new ThemaMapSatzmapper();
 	}
 	return instance;
 }


 ThemaMapSatzmapper::ThemaMapSatzmapper()
  {
 	version = "0.1";
	columns = new string[0];
 	columnTypes = new string[0];
 asc_ThemaMaps = new Association<ThemaMapSatz, ThemaMap>("themamapsatz_themamap","satz_id","themamap_id","ThemaMap", &ThemaMapSatz::addToThemaMaps, &ThemaMapSatz::deleteFromThemaMaps);
mapAssociations["ThemaMaps"] = asc_ThemaMaps;
registerAssociation( asc_ThemaMaps);
asc_Children = new Association<ThemaMapSatz, ThemaMapSatz>("themamapsatz_children","satz_id","child_id","ThemaMapSatz", &ThemaMapSatz::addToChildren, &ThemaMapSatz::deleteFromChildren);
mapAssociations["Children"] = asc_Children;
registerAssociation( asc_Children);
}


ThemaMapSatzmapper::~ThemaMapSatzmapper(){}


 PObject* ThemaMapSatzmapper::createNewObject()
 {
     return new ThemaMapSatz();
 }


 ThemaMapSatz* ThemaMapSatzmapper::create()
 {
     return  (ThemaMapSatz*) AbstractMapper::create( ThemaMapSatzmapper::getInstance() );
 }


 string ThemaMapSatzmapper::getTableName()
 {
     return string("themamapsatz");
 }
 
 string ThemaMapSatzmapper::getClassName()
 {
 	return string("ThemaMapSatz");
 }
 
 string* ThemaMapSatzmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* ThemaMapSatzmapper::getColumns()
 {
 	return columns;
 }
 
 int ThemaMapSatzmapper::getColumnCount()
 {
     return 0;
 }


 string* ThemaMapSatzmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	ThemaMapSatz *o = (ThemaMapSatz*) realSubject;
return values;
 }


 void ThemaMapSatzmapper::save(){
qWarning("ThemaMapSatz: save() not implemented");
}

void ThemaMapSatzmapper::save(PObject *realSubject)
{
 	ThemaMapSatz *o = (ThemaMapSatz*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_ThemaMaps -> save(realSubject, o->getThemaMaps() );

	asc_Children -> save(realSubject, o->getChildren() );

}


void ThemaMapSatzmapper::init(PObject* inito, Variant *res)
 {
 	ThemaMapSatz *o = (ThemaMapSatz*) inito;
	inito->init();
}


 list<ThemaMapSatz *>*ThemaMapSatzmapper::find() 
 {
 	return (list <ThemaMapSatz*>*) Database::getInstance()->getAll(this); 
}


list<ThemaMap*> * ThemaMapSatzmapper::findThemaMaps(int pri_id) 
 { 
 	return asc_ThemaMaps ->  findAssociates( pri_id );
     }


list<ThemaMap*> * ThemaMapSatzmapper::findThemaMaps(int pri_id,string prop,string value) 
         { 
             return asc_ThemaMaps ->  findAssociates( pri_id,prop,value);
             }


list<ThemaMapSatz*> * ThemaMapSatzmapper::findChildren(int pri_id) 
 { 
 	return asc_Children ->  findAssociates( pri_id );
     }


list<ThemaMapSatz*> * ThemaMapSatzmapper::findChildren(int pri_id,string prop,string value) 
         { 
             return asc_Children ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* ThemaMapSatzmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "ThemaMapSatz" ); 
	entry->addProperty( new StringProperty<ThemaMapSatz>("Name", "string", &ThemaMapSatz::getName, &ThemaMapSatz::setName, false) );
	entry->addProperty( new CollectionPropertyImpl<ThemaMap,ThemaMapSatz>( "ThemaMaps" , "ThemaMap", &ThemaMapSatz::getThemaMaps, &ThemaMapSatz::addToThemaMaps, &ThemaMapSatz::deleteFromThemaMaps  ) ); 
	entry->addProperty( new CollectionPropertyImpl<ThemaMapSatz,ThemaMapSatz>( "Children" , "ThemaMapSatz", &ThemaMapSatz::getChildren, &ThemaMapSatz::addToChildren, &ThemaMapSatz::deleteFromChildren  ) ); 
	return entry;
 }
