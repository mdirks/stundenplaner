// 
 // C++ Implementation: stundenplantemplatemapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "stundenplantemplatemapper.h"
 #include "services/utils/utils.h"
 #include "stundenplantemplate.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 stundenplantemplatemapper* stundenplantemplatemapper::instance=0;
 
 stundenplantemplatemapper* stundenplantemplatemapper::getInstance()
 {
 	if(!instance){
 		instance=new stundenplantemplatemapper();
 	}
 	return instance;
 }


 stundenplantemplatemapper::stundenplantemplatemapper()
  {
 	version = "0.3";
	columns = new string[0];
 	columnTypes = new string[0];
 asc_Eintraege = new Association<stundenplantemplate, stundenplantemplateeintrag>("stundenplan_eintrag","stundenplan_id","eintrag_id","stundenplantemplateeintrag", &stundenplantemplate::addToEintraege, &stundenplantemplate::deleteFromEintraege);
mapAssociations["Eintraege"] = asc_Eintraege;
registerAssociation( asc_Eintraege);
}


stundenplantemplatemapper::~stundenplantemplatemapper(){}


 PObject* stundenplantemplatemapper::createNewObject()
 {
     return new stundenplantemplate();
 }


 stundenplantemplate* stundenplantemplatemapper::create()
 {
     return  (stundenplantemplate*) AbstractMapper::create( stundenplantemplatemapper::getInstance() );
 }


 string stundenplantemplatemapper::getTableName()
 {
     return string("stundenplantemplate");
 }
 
 string stundenplantemplatemapper::getClassName()
 {
 	return string("stundenplantemplate");
 }
 
 string* stundenplantemplatemapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* stundenplantemplatemapper::getColumns()
 {
 	return columns;
 }
 
 int stundenplantemplatemapper::getColumnCount()
 {
     return 0;
 }


 string* stundenplantemplatemapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	stundenplantemplate *o = (stundenplantemplate*) realSubject;
return values;
 }


 void stundenplantemplatemapper::save(){
qWarning("stundenplantemplate: save() not implemented");
}

void stundenplantemplatemapper::save(PObject *realSubject)
{
 	stundenplantemplate *o = (stundenplantemplate*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Eintraege -> save(realSubject, o->getEintraege() );

}


void stundenplantemplatemapper::init(PObject* inito, Variant *res)
 {
 	stundenplantemplate *o = (stundenplantemplate*) inito;
	inito->init();
}


 list<stundenplantemplate *>*stundenplantemplatemapper::find() 
 {
 	return (list <stundenplantemplate*>*) Database::getInstance()->getAll(this); 
}


list<stundenplantemplateeintrag*> * stundenplantemplatemapper::findEintraege(int pri_id) 
 { 
 	return asc_Eintraege ->  findAssociates( pri_id );
     }


list<stundenplantemplateeintrag*> * stundenplantemplatemapper::findEintraege(int pri_id,string prop,string value) 
         { 
             return asc_Eintraege ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* stundenplantemplatemapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "stundenplantemplate" ); 
	entry->addProperty( new StringProperty<stundenplantemplate>("Name", "string", &stundenplantemplate::getName, &stundenplantemplate::setName, false) );
	entry->addProperty( new CollectionPropertyImpl<stundenplantemplateeintrag,stundenplantemplate>( "Eintraege" , "stundenplantemplateeintrag", &stundenplantemplate::getEintraege, &stundenplantemplate::addToEintraege, &stundenplantemplate::deleteFromEintraege  ) ); 
	return entry;
 }
