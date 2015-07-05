// 
 // C++ Implementation: notizsatzmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "notizsatzmapper.h"
 #include "services/utils/utils.h"
 #include "notizsatz.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 notizsatzmapper* notizsatzmapper::instance=0;
 
 notizsatzmapper* notizsatzmapper::getInstance()
 {
 	if(!instance){
 		instance=new notizsatzmapper();
 	}
 	return instance;
 }


 notizsatzmapper::notizsatzmapper()
  {
 	version = "0.1";
	columns = new string[0];
 	columnTypes = new string[0];
 asc_Notizen = new Association<notizsatz, notiz>("notizsatz_notiz","satz_id","notiz_id","notiz", &notizsatz::addToNotizen, &notizsatz::deleteFromNotizen);
mapAssociations["Notizen"] = asc_Notizen;
registerAssociation( asc_Notizen);
}


notizsatzmapper::~notizsatzmapper(){}


 PObject* notizsatzmapper::createNewObject()
 {
     return new notizsatz();
 }


 notizsatz* notizsatzmapper::create()
 {
     return  (notizsatz*) AbstractMapper::create( notizsatzmapper::getInstance() );
 }


 string notizsatzmapper::getTableName()
 {
     return string("notizsatz");
 }
 
 string notizsatzmapper::getClassName()
 {
 	return string("notizsatz");
 }
 
 string* notizsatzmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* notizsatzmapper::getColumns()
 {
 	return columns;
 }
 
 int notizsatzmapper::getColumnCount()
 {
     return 0;
 }


 string* notizsatzmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	notizsatz *o = (notizsatz*) realSubject;
return values;
 }


 void notizsatzmapper::save(){
qWarning("notizsatz: save() not implemented");
}

void notizsatzmapper::save(PObject *realSubject)
{
 	notizsatz *o = (notizsatz*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Notizen -> save(realSubject, o->getNotizen() );

}


void notizsatzmapper::init(PObject* inito, Variant *res)
 {
 	notizsatz *o = (notizsatz*) inito;
	inito->init();
}


 list<notizsatz *>*notizsatzmapper::find() 
 {
 	return (list <notizsatz*>*) Database::getInstance()->getAll(this); 
}


list<notiz*> * notizsatzmapper::findNotizen(int pri_id) 
 { 
 	return asc_Notizen ->  findAssociates( pri_id );
     }


list<notiz*> * notizsatzmapper::findNotizen(int pri_id,string prop,string value) 
         { 
             return asc_Notizen ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* notizsatzmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "notizsatz" ); 
	entry->addProperty( new StringProperty<notizsatz>("Name", "string", &notizsatz::getName, &notizsatz::setName, false) );
	entry->addProperty( new CollectionPropertyImpl<notiz,notizsatz>( "Notizen" , "notiz", &notizsatz::getNotizen, &notizsatz::addToNotizen, &notizsatz::deleteFromNotizen  ) ); 
	return entry;
 }
