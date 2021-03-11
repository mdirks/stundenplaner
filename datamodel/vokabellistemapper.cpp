// 
 // C++ Implementation: vokabellistemapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "vokabellistemapper.h"
 #include "services/utils/utils.h"
 #include "vokabelliste.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 vokabellistemapper* vokabellistemapper::instance=0;
 
 vokabellistemapper* vokabellistemapper::getInstance()
 {
 	if(!instance){
 		instance=new vokabellistemapper();
 	}
 	return instance;
 }


 vokabellistemapper::vokabellistemapper()
  {
 	version = "0.1";
	columns = new string[0];
 	columnTypes = new string[0];
 asc_Vokabeln = new Association<vokabelliste, vokabel>("vokabelliste_vokabel","list_id","vok_id","vokabel", &vokabelliste::addToVokabeln, &vokabelliste::deleteFromVokabeln);
mapAssociations["Vokabeln"] = asc_Vokabeln;
registerAssociation( asc_Vokabeln);
}


vokabellistemapper::~vokabellistemapper(){}


 PObject* vokabellistemapper::createNewObject()
 {
     return new vokabelliste();
 }


 vokabelliste* vokabellistemapper::create()
 {
     return  (vokabelliste*) AbstractMapper::create( vokabellistemapper::getInstance() );
 }


 string vokabellistemapper::getTableName()
 {
     return string("vokabelliste");
 }
 
 string vokabellistemapper::getClassName()
 {
 	return string("vokabelliste");
 }
 
 string* vokabellistemapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* vokabellistemapper::getColumns()
 {
 	return columns;
 }
 
 int vokabellistemapper::getColumnCount()
 {
     return 0;
 }


 string* vokabellistemapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	vokabelliste *o = (vokabelliste*) realSubject;
return values;
 }


 void vokabellistemapper::save(){
qWarning("vokabelliste: save() not implemented");
}

void vokabellistemapper::save(PObject *realSubject)
{
 	vokabelliste *o = (vokabelliste*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Vokabeln -> save(realSubject, o->getVokabeln() );

}


void vokabellistemapper::init(PObject* inito, Variant *res)
 {
 	vokabelliste *o = (vokabelliste*) inito;
	inito->init();
}


 list<vokabelliste *>*vokabellistemapper::find() 
 {
 	return (list <vokabelliste*>*) Database::getInstance()->getAll(this); 
}


list<vokabel*> * vokabellistemapper::findVokabeln(int pri_id) 
 { 
 	return asc_Vokabeln ->  findAssociates( pri_id );
     }


list<vokabel*> * vokabellistemapper::findVokabeln(int pri_id,string prop,string value) 
         { 
             return asc_Vokabeln ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* vokabellistemapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "vokabelliste" ); 
	entry->addProperty( new StringProperty<vokabelliste>("Name", "string", &vokabelliste::getName, &vokabelliste::setName, false) );
	entry->addProperty( new CollectionPropertyImpl<vokabel,vokabelliste>( "Vokabeln" , "vokabel", &vokabelliste::getVokabeln, &vokabelliste::addToVokabeln, &vokabelliste::deleteFromVokabeln  ) ); 
	return entry;
 }
