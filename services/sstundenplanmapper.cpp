// 
 // C++ Implementation: SStundenplanmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "sstundenplanmapper.h"
 #include "services/utils/utils.h"
 #include "sstundenplan.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 SStundenplanmapper* SStundenplanmapper::instance=0;
 
 SStundenplanmapper* SStundenplanmapper::getInstance()
 {
 	if(!instance){
 		instance=new SStundenplanmapper();
 	}
 	return instance;
 }


 SStundenplanmapper::SStundenplanmapper()
  {
 	version = "0.2";
	columns = new string[0];
 	columnTypes = new string[0];
 asc_TemplateEintraege = new Association<SStundenplan, stundenplantemplateeintrag>("sstundenplan_teintraege","sstundenplan_id","template_id","stundenplantemplateeintrag", &SStundenplan::addToTemplateEintraege, &SStundenplan::deleteFromTemplateEintraege);
mapAssociations["TemplateEintraege"] = asc_TemplateEintraege;
registerAssociation( asc_TemplateEintraege);
}


SStundenplanmapper::~SStundenplanmapper(){}


 PObject* SStundenplanmapper::createNewObject()
 {
     return new SStundenplan();
 }


 SStundenplan* SStundenplanmapper::create()
 {
     return  (SStundenplan*) AbstractMapper::create( SStundenplanmapper::getInstance() );
 }


 string SStundenplanmapper::getTableName()
 {
     return string("sstundenplan");
 }
 
 string SStundenplanmapper::getClassName()
 {
 	return string("SStundenplan");
 }
 
 string* SStundenplanmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* SStundenplanmapper::getColumns()
 {
 	return columns;
 }
 
 int SStundenplanmapper::getColumnCount()
 {
     return 0;
 }


 string* SStundenplanmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	SStundenplan *o = (SStundenplan*) realSubject;
return values;
 }


 void SStundenplanmapper::save(){
qWarning("SStundenplan: save() not implemented");
}

void SStundenplanmapper::save(PObject *realSubject)
{
 	SStundenplan *o = (SStundenplan*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_TemplateEintraege -> save(realSubject, o->getTemplateEintraege() );

}


void SStundenplanmapper::init(PObject* inito, Variant *res)
 {
 	SStundenplan *o = (SStundenplan*) inito;
	inito->init();
}


 list<SStundenplan *>*SStundenplanmapper::find() 
 {
 	return (list <SStundenplan*>*) Database::getInstance()->getAll(this); 
}


list<stundenplantemplateeintrag*> * SStundenplanmapper::findTemplateEintraege(int pri_id) 
 { 
 	return asc_TemplateEintraege ->  findAssociates( pri_id );
 	}


RepositoryEntry* SStundenplanmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "SStundenplan" ); 
	entry->addProperty( new StringProperty<SStundenplan>("Name", "string", &SStundenplan::getName, &SStundenplan::setName, false) );
	entry->addProperty( new CollectionPropertyImpl<stundenplantemplateeintrag,SStundenplan>( "TemplateEintraege" , "stundenplantemplateeintrag", &SStundenplan::getTemplateEintraege, &SStundenplan::addToTemplateEintraege, &SStundenplan::deleteFromTemplateEintraege  ) ); 
	return entry;
 }
