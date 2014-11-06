// 
 // C++ Implementation: unterrichtsthemamapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "unterrichtsthemamapper.h"
 #include "services/utils/utils.h"
 #include "datamodel/unterrichtsthema.h"
#include "orm/persistence/database.h"
 #include "orm/mapping/property.h"

 unterrichtsthemamapper* unterrichtsthemamapper::instance=0;
 
 unterrichtsthemamapper* unterrichtsthemamapper::getInstance()
 {
 	if(!instance){
 		instance=new unterrichtsthemamapper();
 	}
 	return instance;
 }


 unterrichtsthemamapper::unterrichtsthemamapper()
  {
 	version = "0.1";
	columns = new string[0];
 	columnTypes = new string[0];
 asc_Stunden = new Association<unterrichtsthema, stunde>("thema_stunde","thema_id","stunde_id","stunde", &unterrichtsthema::addToStunden, &unterrichtsthema::deleteFromStunden);
mapAssociations["Stunden"] = asc_Stunden;
registerAssociation( asc_Stunden);
asc_Reihen = new Association<unterrichtsthema, reihe>("thema_reihe","thema_id","reihe_id","reihe", &unterrichtsthema::addToReihen, &unterrichtsthema::deleteFromReihen);
mapAssociations["Reihen"] = asc_Reihen;
registerAssociation( asc_Reihen);
}


unterrichtsthemamapper::~unterrichtsthemamapper(){}


 PObject* unterrichtsthemamapper::createNewObject()
 {
     return new unterrichtsthema();
 }


 unterrichtsthema* unterrichtsthemamapper::create()
 {
     return  (unterrichtsthema*) AbstractMapper::create();
 }


 string unterrichtsthemamapper::getTableName()
 {
     return string("unterrichtsthema");
 }
 
 string unterrichtsthemamapper::getClassName()
 {
 	return string("unterrichtsthema");
 }
 
 string* unterrichtsthemamapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* unterrichtsthemamapper::getColumns()
 {
 	return columns;
 }
 
 int unterrichtsthemamapper::getColumnCount()
 {
     return 0;
 }


 string* unterrichtsthemamapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	unterrichtsthema *o = (unterrichtsthema*) realSubject;
return values;
 }


 void unterrichtsthemamapper::save(){
qWarning("unterrichtsthema: save() not implemented");
}

void unterrichtsthemamapper::save(PObject *realSubject)
{
 	unterrichtsthema *o = (unterrichtsthema*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Stunden -> save(realSubject, o->getStunden() );

	asc_Reihen -> save(realSubject, o->getReihen() );

	notizholdermapper::save(realSubject);
}


void unterrichtsthemamapper::init(PObject* inito, Variant *res)
 {
 	unterrichtsthema *o = (unterrichtsthema*) inito;
	inito->init();
}


 list<unterrichtsthema *>*unterrichtsthemamapper::find() 
 {
 	return (list <unterrichtsthema*>*) Database::getInstance()->getAll(this); 
}


list<stunde*> * unterrichtsthemamapper::findStunden(int pri_id) 
 { 
 	return asc_Stunden ->  findAssociates( pri_id );
 	}


list<reihe*> * unterrichtsthemamapper::findReihen(int pri_id) 
 { 
 	return asc_Reihen ->  findAssociates( pri_id );
 	}


RepositoryEntry* unterrichtsthemamapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "unterrichtsthema" ); 
	entry->addProperty( new StringProperty<unterrichtsthema>("Name", "string", &unterrichtsthema::getName, &unterrichtsthema::setName, false) );
	entry->addProperty( new CollectionPropertyImpl<stunde,unterrichtsthema>( "Stunden" , "stunde", &unterrichtsthema::getStunden, &unterrichtsthema::addToStunden, &unterrichtsthema::deleteFromStunden  ) ); 
	entry->addProperty( new CollectionPropertyImpl<reihe,unterrichtsthema>( "Reihen" , "reihe", &unterrichtsthema::getReihen, &unterrichtsthema::addToReihen, &unterrichtsthema::deleteFromReihen  ) ); 
	entry->registerBase( "notizholder" );
	return entry;
 }
