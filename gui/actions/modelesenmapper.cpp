// 
 // C++ Implementation: ModeLesenmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "modelesenmapper.h"
 #include "services/utils/utils.h"
 #include "modelesen.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 ModeLesenmapper* ModeLesenmapper::instance=0;
 
 ModeLesenmapper* ModeLesenmapper::getInstance()
 {
 	if(!instance){
 		instance=new ModeLesenmapper();
 	}
 	return instance;
 }


 ModeLesenmapper::ModeLesenmapper()
  {
 	version = "0.3";
	columns = new string[0];
 	columnTypes = new string[0];
 asc_Texte = new Association<ModeLesen, lektuere>("modelesen_texte","modelesen_id","text_id","lektuere", &ModeLesen::addToTexte, &ModeLesen::deleteFromTexte);
mapAssociations["Texte"] = asc_Texte;
registerAssociation( asc_Texte);
}


ModeLesenmapper::~ModeLesenmapper(){}


 PObject* ModeLesenmapper::createNewObject()
 {
     return new ModeLesen();
 }


 ModeLesen* ModeLesenmapper::create()
 {
     return  (ModeLesen*) AbstractMapper::create( ModeLesenmapper::getInstance() );
 }


 string ModeLesenmapper::getTableName()
 {
     return string("modelesen");
 }
 
 string ModeLesenmapper::getClassName()
 {
 	return string("ModeLesen");
 }
 
 string* ModeLesenmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* ModeLesenmapper::getColumns()
 {
 	return columns;
 }
 
 int ModeLesenmapper::getColumnCount()
 {
     return 0;
 }


 string* ModeLesenmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	ModeLesen *o = (ModeLesen*) realSubject;
return values;
 }


 void ModeLesenmapper::save(){
qWarning("ModeLesen: save() not implemented");
}

void ModeLesenmapper::save(PObject *realSubject)
{
 	ModeLesen *o = (ModeLesen*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Texte -> save(realSubject, o->getTexte() );

	notizholdermapper::save(realSubject);
}


void ModeLesenmapper::init(PObject* inito, Variant *res)
 {
 	ModeLesen *o = (ModeLesen*) inito;
	inito->init();
}


 list<ModeLesen *>*ModeLesenmapper::find() 
 {
 	return (list <ModeLesen*>*) Database::getInstance()->getAll(this); 
}


list<lektuere*> * ModeLesenmapper::findTexte(int pri_id) 
 { 
 	return asc_Texte ->  findAssociates( pri_id );
 	}


RepositoryEntry* ModeLesenmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "ModeLesen" ); 
	entry->addProperty( new StringProperty<ModeLesen>("Name", "string", &ModeLesen::getName, &ModeLesen::setName, false) );
	entry->addProperty( new CollectionPropertyImpl<lektuere,ModeLesen>( "Texte" , "lektuere", &ModeLesen::getTexte, &ModeLesen::addToTexte, &ModeLesen::deleteFromTexte  ) ); 
	entry->registerBase( "notizholder" );
	return entry;
 }
