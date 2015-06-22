// 
 // C++ Implementation: themamapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "themamapper.h"
 #include "services/utils/utils.h"
 #include "thema.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 themamapper* themamapper::instance=0;
 
 themamapper* themamapper::getInstance()
 {
 	if(!instance){
 		instance=new themamapper();
 	}
 	return instance;
 }


 themamapper::themamapper()
  {
 	version = "0.7";
	columns = new string[2];
 	columnTypes = new string[2];
 	columns[0] = "title";
 	columnTypes[0] = "varchar(30)";
	mapProperties["title"] = new Property("title");
	columns[1] = "inhalt";
 	columnTypes[1] = "text";
	mapProperties["inhalt"] = new Property("inhalt");
asc_Related = new Association<thema, thema>("thema_related","thema_id","related_id","thema", &thema::addToRelated, &thema::deleteFromRelated);
mapAssociations["Related"] = asc_Related;
registerAssociation( asc_Related);
asc_Sub = new Association<thema, thema>("thema_sub","thema_id","sub_id","thema", &thema::addToSub, &thema::deleteFromSub);
mapAssociations["Sub"] = asc_Sub;
registerAssociation( asc_Sub);
asc_Lernkarten = new Association<thema, lernkarte>("thema_karte","thema_id","karte_id","lernkarte", &thema::addToLernkarten, &thema::deleteFromLernkarten);
mapAssociations["Lernkarten"] = asc_Lernkarten;
registerAssociation( asc_Lernkarten);
mapReferences["Lernkartensatz"] = new Reference("thema","datamodel/lernkartensatz");
}


themamapper::~themamapper(){}


 PObject* themamapper::createNewObject()
 {
     return new thema();
 }


 thema* themamapper::create()
 {
     return  (thema*) AbstractMapper::create( themamapper::getInstance() );
 }


 string themamapper::getTableName()
 {
     return string("thema");
 }
 
 string themamapper::getClassName()
 {
 	return string("thema");
 }
 
 string* themamapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* themamapper::getColumns()
 {
 	return columns;
 }
 
 int themamapper::getColumnCount()
 {
     return 2;
 }


 string* themamapper::getValues(PObject *realSubject)
 {
 	string *values = new string[2];  
 	thema *o = (thema*) realSubject;
	values[0] = to_string(o->getTitle());
	values[1] = to_string(o->getInhalt());
return values;
 }


 void themamapper::save(){
qWarning("thema: save() not implemented");
}

void themamapper::save(PObject *realSubject)
{
 	thema *o = (thema*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Related -> save(realSubject, o->getRelated() );

	asc_Sub -> save(realSubject, o->getSub() );

	asc_Lernkarten -> save(realSubject, o->getLernkarten() );

	mapReferences[ "Lernkartensatz" ] -> save(realSubject, (PObject*) o->getLernkartensatz());
	notizholdermapper::save(realSubject);
}


void themamapper::init(PObject* inito, Variant *res)
 {
 	thema *o = (thema*) inito;
	o->setTitle( res[0].asstring());
 	o->setInhalt( res[1].asstring());
 	inito->init();
}


 list<thema *>*themamapper::find() 
 {
 	return (list <thema*>*) Database::getInstance()->getAll(this); 
}


list<thema*> * themamapper::findRelated(int pri_id) 
 { 
 	return asc_Related ->  findAssociates( pri_id );
     }


list<thema*> * themamapper::findRelated(int pri_id,string prop,string value) 
         { 
             return asc_Related ->  findAssociates( pri_id,prop,value);
             }


list<thema*> * themamapper::findSub(int pri_id) 
 { 
 	return asc_Sub ->  findAssociates( pri_id );
     }


list<thema*> * themamapper::findSub(int pri_id,string prop,string value) 
         { 
             return asc_Sub ->  findAssociates( pri_id,prop,value);
             }


list<lernkarte*> * themamapper::findLernkarten(int pri_id) 
 { 
 	return asc_Lernkarten ->  findAssociates( pri_id );
     }


list<lernkarte*> * themamapper::findLernkarten(int pri_id,string prop,string value) 
         { 
             return asc_Lernkarten ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* themamapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "thema" ); 
	entry->addProperty( new StringProperty<thema>("Name", "string", &thema::getName, &thema::setName, false) );
	entry->addProperty( new StringProperty< thema >( "title" , "string", &thema::getTitle, &thema::setTitle, false ) );
	entry->addProperty( new StringProperty< thema >( "Inhalt" , "string", &thema::getInhalt, &thema::setInhalt, true ) );
	entry->addProperty( new CollectionPropertyImpl<thema,thema>( "Related" , "thema", &thema::getRelated, &thema::addToRelated, &thema::deleteFromRelated  ) ); 
	entry->addProperty( new CollectionPropertyImpl<thema,thema>( "Sub" , "thema", &thema::getSub, &thema::addToSub, &thema::deleteFromSub  ) ); 
	entry->addProperty( new CollectionPropertyImpl<lernkarte,thema>( "Lernkarten" , "lernkarte", &thema::getLernkarten, &thema::addToLernkarten, &thema::deleteFromLernkarten  ) ); 
	entry->addProperty( new PObjectProperty<lernkartensatz,thema>( "Lernkartensatz" , "lernkartensatz", &thema::getLernkartensatz,&thema::setLernkartensatz ) ); 
	entry->registerBase( "notizholder" );
	return entry;
 }
