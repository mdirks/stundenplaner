// 
 // C++ Implementation: lektueremapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "lektueremapper.h"
 #include "services/utils/utils.h"
 #include "lektuere.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 lektueremapper* lektueremapper::instance=0;
 
 lektueremapper* lektueremapper::getInstance()
 {
 	if(!instance){
 		instance=new lektueremapper();
 	}
 	return instance;
 }


 lektueremapper::lektueremapper()
  {
 	version = "0.5-0.6";
	columns = new string[2];
 	columnTypes = new string[2];
 	columns[0] = "title";
 	columnTypes[0] = "varchar(50)";
	mapProperties["title"] = new Property("title");
	columns[1] = "filename";
 	columnTypes[1] = "varchar(80)";
	mapProperties["filename"] = new Property("filename");
asc_Notizen = new Association<lektuere, lektuerenotiz>("lektuere_notizen","lektuere_id","notiz_id","lektuerenotiz", &lektuere::addToNotizen, &lektuere::deleteFromNotizen);
mapAssociations["Notizen"] = asc_Notizen;
registerAssociation( asc_Notizen);
mapReferences["Lernkartensatz"] = new Reference("lektuere","datamodel/lernkartensatz");
mapReferences["Kopien"] = new Reference("lektuere","datamodel/materialsatz");
}


lektueremapper::~lektueremapper(){}


 PObject* lektueremapper::createNewObject()
 {
     return new lektuere();
 }


 lektuere* lektueremapper::create()
 {
     return  (lektuere*) AbstractMapper::create( lektueremapper::getInstance() );
 }


 string lektueremapper::getTableName()
 {
     return string("lektuere");
 }
 
 string lektueremapper::getClassName()
 {
 	return string("lektuere");
 }
 
 string* lektueremapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* lektueremapper::getColumns()
 {
 	return columns;
 }
 
 int lektueremapper::getColumnCount()
 {
     return 2;
 }


 string* lektueremapper::getValues(PObject *realSubject)
 {
 	string *values = new string[2];  
 	lektuere *o = (lektuere*) realSubject;
	values[0] = to_string(o->getTitle());
	values[1] = to_string(o->getFileName());
return values;
 }


 void lektueremapper::save(){
qWarning("lektuere: save() not implemented");
}

void lektueremapper::save(PObject *realSubject)
{
 	lektuere *o = (lektuere*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Notizen -> save(realSubject, o->getNotizen() );

	mapReferences[ "Lernkartensatz" ] -> save(realSubject, (PObject*) o->getLernkartensatz());
	mapReferences[ "Kopien" ] -> save(realSubject, (PObject*) o->getKopien());
	materialmapper::save(realSubject);
}


void lektueremapper::init(PObject* inito, Variant *res)
 {
 	lektuere *o = (lektuere*) inito;
	o->setTitle( res[0].asstring());
 	o->setFileName( res[1].asstring());
 	inito->init();
}


 list<lektuere *>*lektueremapper::find() 
 {
 	return (list <lektuere*>*) Database::getInstance()->getAll(this); 
}


list<lektuerenotiz*> * lektueremapper::findNotizen(int pri_id) 
 { 
 	return asc_Notizen ->  findAssociates( pri_id );
     }


list<lektuerenotiz*> * lektueremapper::findNotizen(int pri_id,string prop,string value) 
         { 
             return asc_Notizen ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* lektueremapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "lektuere" ); 
	entry->addProperty( new StringProperty<lektuere>("Name", "string", &lektuere::getName, &lektuere::setName, false) );
	entry->addProperty( new StringProperty< lektuere >( "title" , "string", &lektuere::getTitle, &lektuere::setTitle, false ) );
	entry->addProperty( new StringProperty< lektuere >( "FileName" , "string", &lektuere::getFileName, &lektuere::setFileName, false ) );
	entry->addProperty( new CollectionPropertyImpl<lektuerenotiz,lektuere>( "Notizen" , "lektuerenotiz", &lektuere::getNotizen, &lektuere::addToNotizen, &lektuere::deleteFromNotizen  ) ); 
	entry->addProperty( new PObjectProperty<lernkartensatz,lektuere>( "Lernkartensatz" , "lernkartensatz", &lektuere::getLernkartensatz,&lektuere::setLernkartensatz ) ); 
	entry->addProperty( new PObjectProperty<materialsatz,lektuere>( "Kopien" , "materialsatz", &lektuere::getKopien,&lektuere::setKopien ) ); 
	entry->registerBase( "material" );
	return entry;
 }
