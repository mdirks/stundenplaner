// 
 // C++ Implementation: lernkartensatzmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "lernkartensatzmapper.h"
 #include "services/utils/utils.h"
 #include "lernkartensatz.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 lernkartensatzmapper* lernkartensatzmapper::instance=0;
 
 lernkartensatzmapper* lernkartensatzmapper::getInstance()
 {
 	if(!instance){
 		instance=new lernkartensatzmapper();
 	}
 	return instance;
 }


 lernkartensatzmapper::lernkartensatzmapper()
  {
 	version = "0.1";
	columns = new string[0];
 	columnTypes = new string[0];
 asc_Lernkarten = new Association<lernkartensatz, lernkarte>("lernkartensatz_lernkarte","satz_id","karte_id","lernkarte", &lernkartensatz::addToLernkarten, &lernkartensatz::deleteFromLernkarten);
mapAssociations["Lernkarten"] = asc_Lernkarten;
registerAssociation( asc_Lernkarten);
}


lernkartensatzmapper::~lernkartensatzmapper(){}


 PObject* lernkartensatzmapper::createNewObject()
 {
     return new lernkartensatz();
 }


 lernkartensatz* lernkartensatzmapper::create()
 {
     return  (lernkartensatz*) AbstractMapper::create( lernkartensatzmapper::getInstance() );
 }


 string lernkartensatzmapper::getTableName()
 {
     return string("lernkartensatz");
 }
 
 string lernkartensatzmapper::getClassName()
 {
 	return string("lernkartensatz");
 }
 
 string* lernkartensatzmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* lernkartensatzmapper::getColumns()
 {
 	return columns;
 }
 
 int lernkartensatzmapper::getColumnCount()
 {
     return 0;
 }


 string* lernkartensatzmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	lernkartensatz *o = (lernkartensatz*) realSubject;
return values;
 }


 void lernkartensatzmapper::save(){
qWarning("lernkartensatz: save() not implemented");
}

void lernkartensatzmapper::save(PObject *realSubject)
{
 	lernkartensatz *o = (lernkartensatz*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Lernkarten -> save(realSubject, o->getLernkarten() );

}


void lernkartensatzmapper::init(PObject* inito, Variant *res)
 {
 	lernkartensatz *o = (lernkartensatz*) inito;
	inito->init();
}


 list<lernkartensatz *>*lernkartensatzmapper::find() 
 {
 	return (list <lernkartensatz*>*) Database::getInstance()->getAll(this); 
}


list<lernkarte*> * lernkartensatzmapper::findLernkarten(int pri_id) 
 { 
 	return asc_Lernkarten ->  findAssociates( pri_id );
     }


list<lernkarte*> * lernkartensatzmapper::findLernkarten(int pri_id,string prop,string value) 
         { 
             return asc_Lernkarten ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* lernkartensatzmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "lernkartensatz" ); 
	entry->addProperty( new StringProperty<lernkartensatz>("Name", "string", &lernkartensatz::getName, &lernkartensatz::setName, false) );
	entry->addProperty( new CollectionPropertyImpl<lernkarte,lernkartensatz>( "Lernkarten" , "lernkarte", &lernkartensatz::getLernkarten, &lernkartensatz::addToLernkarten, &lernkartensatz::deleteFromLernkarten  ) ); 
	return entry;
 }
