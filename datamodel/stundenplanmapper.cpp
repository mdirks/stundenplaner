// 
 // C++ Implementation: stundenplanmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "stundenplanmapper.h"
 #include "services/utils/utils.h"
 #include "stundenplan.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 stundenplanmapper* stundenplanmapper::instance=0;
 
 stundenplanmapper* stundenplanmapper::getInstance()
 {
 	if(!instance){
 		instance=new stundenplanmapper();
 	}
 	return instance;
 }


 stundenplanmapper::stundenplanmapper()
  {
 	version = "0.3";
	columns = new string[0];
 	columnTypes = new string[0];
 asc_TemplateEintraege = new Association<stundenplan, stundenplantemplateeintrag>("stundenplan_template","stundenplan_id","template_id","stundenplantemplateeintrag", &stundenplan::addToTemplateEintraege, &stundenplan::deleteFromTemplateEintraege);
mapAssociations["TemplateEintraege"] = asc_TemplateEintraege;
registerAssociation( asc_TemplateEintraege);
}


stundenplanmapper::~stundenplanmapper(){}


 PObject* stundenplanmapper::createNewObject()
 {
     return new stundenplan();
 }


 stundenplan* stundenplanmapper::create()
 {
     return  (stundenplan*) AbstractMapper::create( stundenplanmapper::getInstance() );
 }


 string stundenplanmapper::getTableName()
 {
     return string("stundenplan");
 }
 
 string stundenplanmapper::getClassName()
 {
 	return string("stundenplan");
 }
 
 string* stundenplanmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* stundenplanmapper::getColumns()
 {
 	return columns;
 }
 
 int stundenplanmapper::getColumnCount()
 {
     return 0;
 }


 string* stundenplanmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	stundenplan *o = (stundenplan*) realSubject;
return values;
 }


 void stundenplanmapper::save(){
qWarning("stundenplan: save() not implemented");
}

void stundenplanmapper::save(PObject *realSubject)
{
 	stundenplan *o = (stundenplan*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_TemplateEintraege -> save(realSubject, o->getTemplateEintraege() );

	notizholdermapper::save(realSubject);
}


void stundenplanmapper::init(PObject* inito, Variant *res)
 {
 	stundenplan *o = (stundenplan*) inito;
	inito->init();
}


 list<stundenplan *>*stundenplanmapper::find() 
 {
 	return (list <stundenplan*>*) Database::getInstance()->getAll(this); 
}


list<stundenplantemplateeintrag*> * stundenplanmapper::findTemplateEintraege(int pri_id) 
 { 
 	return asc_TemplateEintraege ->  findAssociates( pri_id );
     }


list<stundenplantemplateeintrag*> * stundenplanmapper::findTemplateEintraege(int pri_id,string prop,string value) 
         { 
             return asc_TemplateEintraege ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* stundenplanmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "stundenplan" ); 
	entry->addProperty( new StringProperty<stundenplan>("Name", "string", &stundenplan::getName, &stundenplan::setName, false) );
	entry->addProperty( new CollectionPropertyImpl<stundenplantemplateeintrag,stundenplan>( "TemplateEintraege" , "stundenplantemplateeintrag", &stundenplan::getTemplateEintraege, &stundenplan::addToTemplateEintraege, &stundenplan::deleteFromTemplateEintraege  ) ); 
	entry->registerBase( "notizholder" );
	return entry;
 }
