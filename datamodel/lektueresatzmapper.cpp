// 
 // C++ Implementation: lektueresatzmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "lektueresatzmapper.h"
 #include "services/utils/utils.h"
 #include "lektueresatz.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 lektueresatzmapper* lektueresatzmapper::instance=0;
 
 lektueresatzmapper* lektueresatzmapper::getInstance()
 {
 	if(!instance){
 		instance=new lektueresatzmapper();
 	}
 	return instance;
 }


 lektueresatzmapper::lektueresatzmapper()
  {
 	version = "0.1";
	columns = new string[0];
 	columnTypes = new string[0];
 asc_Lektueren = new Association<lektueresatz, lektuere>("lektueresatz_lektuere","satz_id","lektuere_id","lektuere", &lektueresatz::addToLektueren, &lektueresatz::deleteFromLektueren);
mapAssociations["Lektueren"] = asc_Lektueren;
registerAssociation( asc_Lektueren);
asc_Children = new Association<lektueresatz, lektueresatz>("lektueresatz_children","satz_id","child_id","lektueresatz", &lektueresatz::addToChildren, &lektueresatz::deleteFromChildren);
mapAssociations["Children"] = asc_Children;
registerAssociation( asc_Children);
}


lektueresatzmapper::~lektueresatzmapper(){}


 PObject* lektueresatzmapper::createNewObject()
 {
     return new lektueresatz();
 }


 lektueresatz* lektueresatzmapper::create()
 {
     return  (lektueresatz*) AbstractMapper::create( lektueresatzmapper::getInstance() );
 }


 string lektueresatzmapper::getTableName()
 {
     return string("lektueresatz");
 }
 
 string lektueresatzmapper::getClassName()
 {
 	return string("lektueresatz");
 }
 
 string* lektueresatzmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* lektueresatzmapper::getColumns()
 {
 	return columns;
 }
 
 int lektueresatzmapper::getColumnCount()
 {
     return 0;
 }


 string* lektueresatzmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	lektueresatz *o = (lektueresatz*) realSubject;
return values;
 }


 void lektueresatzmapper::save(){
qWarning("lektueresatz: save() not implemented");
}

void lektueresatzmapper::save(PObject *realSubject)
{
 	lektueresatz *o = (lektueresatz*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Lektueren -> save(realSubject, o->getLektueren() );

	asc_Children -> save(realSubject, o->getChildren() );

}


void lektueresatzmapper::init(PObject* inito, Variant *res)
 {
 	lektueresatz *o = (lektueresatz*) inito;
	inito->init();
}


 list<lektueresatz *>*lektueresatzmapper::find() 
 {
 	return (list <lektueresatz*>*) Database::getInstance()->getAll(this); 
}


list<lektuere*> * lektueresatzmapper::findLektueren(int pri_id) 
 { 
 	return asc_Lektueren ->  findAssociates( pri_id );
     }


list<lektuere*> * lektueresatzmapper::findLektueren(int pri_id,string prop,string value) 
         { 
             return asc_Lektueren ->  findAssociates( pri_id,prop,value);
             }


list<lektueresatz*> * lektueresatzmapper::findChildren(int pri_id) 
 { 
 	return asc_Children ->  findAssociates( pri_id );
     }


list<lektueresatz*> * lektueresatzmapper::findChildren(int pri_id,string prop,string value) 
         { 
             return asc_Children ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* lektueresatzmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "lektueresatz" ); 
	entry->addProperty( new StringProperty<lektueresatz>("Name", "string", &lektueresatz::getName, &lektueresatz::setName, false) );
	entry->addProperty( new CollectionPropertyImpl<lektuere,lektueresatz>( "Lektueren" , "lektuere", &lektueresatz::getLektueren, &lektueresatz::addToLektueren, &lektueresatz::deleteFromLektueren  ) ); 
	entry->addProperty( new CollectionPropertyImpl<lektueresatz,lektueresatz>( "Children" , "lektueresatz", &lektueresatz::getChildren, &lektueresatz::addToChildren, &lektueresatz::deleteFromChildren  ) ); 
	return entry;
 }
