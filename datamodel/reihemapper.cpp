// 
 // C++ Implementation: reihemapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "reihemapper.h"
 #include "services/utils/utils.h"
 #include "reihe.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 reihemapper* reihemapper::instance=0;
 
 reihemapper* reihemapper::getInstance()
 {
 	if(!instance){
 		instance=new reihemapper();
 	}
 	return instance;
 }


 reihemapper::reihemapper()
  {
 	version = "0.4-0.5-0.5";
	columns = new string[2];
 	columnTypes = new string[2];
 	columns[0] = "thema";
 	columnTypes[0] = "varchar(30)";
	mapProperties["thema"] = new Property("thema");
	columns[1] = "verlauf";
 	columnTypes[1] = "text";
	mapProperties["verlauf"] = new Property("verlauf");
asc_Stunden = new Association<reihe, stunde>("reihe_stunde","reihe_id","stunde_id","stunde", &reihe::addToStunden, &reihe::deleteFromStunden);
mapAssociations["Stunden"] = asc_Stunden;
registerAssociation( asc_Stunden);
}


reihemapper::~reihemapper(){}


 PObject* reihemapper::createNewObject()
 {
     return new reihe();
 }


 reihe* reihemapper::create()
 {
     return  (reihe*) AbstractMapper::create( reihemapper::getInstance() );
 }


 string reihemapper::getTableName()
 {
     return string("reihe");
 }
 
 string reihemapper::getClassName()
 {
 	return string("reihe");
 }
 
 string* reihemapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* reihemapper::getColumns()
 {
 	return columns;
 }
 
 int reihemapper::getColumnCount()
 {
     return 2;
 }


 string* reihemapper::getValues(PObject *realSubject)
 {
 	string *values = new string[2];  
 	reihe *o = (reihe*) realSubject;
	values[0] = to_string(o->getThema());
	values[1] = to_string(o->getVerlauf());
return values;
 }


 void reihemapper::save(){
qWarning("reihe: save() not implemented");
}

void reihemapper::save(PObject *realSubject)
{
 	reihe *o = (reihe*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Stunden -> save(realSubject, o->getStunden() );

	notizholdermapper::save(realSubject);
}


void reihemapper::init(PObject* inito, Variant *res)
 {
 	reihe *o = (reihe*) inito;
	o->setThema( res[0].asstring());
 	o->setVerlauf( res[1].asstring());
 	inito->init();
}


 list<reihe *>*reihemapper::find() 
 {
 	return (list <reihe*>*) Database::getInstance()->getAll(this); 
}


list<stunde*> * reihemapper::findStunden(int pri_id) 
 { 
 	return asc_Stunden ->  findAssociates( pri_id );
     }


list<stunde*> * reihemapper::findStunden(int pri_id,string prop,string value) 
         { 
             return asc_Stunden ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* reihemapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "reihe" ); 
	entry->addProperty( new StringProperty<reihe>("Name", "string", &reihe::getName, &reihe::setName, false) );
	entry->addProperty( new StringProperty< reihe >( "thema" , "string", &reihe::getThema, &reihe::setThema, false ) );
	entry->addProperty( new StringProperty< reihe >( "Verlauf" , "string", &reihe::getVerlauf, &reihe::setVerlauf, true ) );
	entry->addProperty( new CollectionPropertyImpl<stunde,reihe>( "Stunden" , "stunde", &reihe::getStunden, &reihe::addToStunden, &reihe::deleteFromStunden  ) ); 
	entry->registerBase( "notizholder" );
	return entry;
 }
