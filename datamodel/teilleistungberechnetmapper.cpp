// 
 // C++ Implementation: teilleistungberechnetmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "teilleistungberechnetmapper.h"
 #include "services/utils/utils.h"
 #include "teilleistungberechnet.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 teilleistungberechnetmapper* teilleistungberechnetmapper::instance=0;
 
 teilleistungberechnetmapper* teilleistungberechnetmapper::getInstance()
 {
 	if(!instance){
 		instance=new teilleistungberechnetmapper();
 	}
 	return instance;
 }


 teilleistungberechnetmapper::teilleistungberechnetmapper()
  {
 	version = "0.1";
	columns = new string[0];
 	columnTypes = new string[0];
 asc_Teilleistungen = new Association<teilleistungberechnet, teilleistung>("teilleistungberechnet_teilleistungen","teilleistungb_id","teilleistung_id","teilleistung", &teilleistungberechnet::addToTeilleistungen, &teilleistungberechnet::deleteFromTeilleistungen);
mapAssociations["Teilleistungen"] = asc_Teilleistungen;
registerAssociation( asc_Teilleistungen);
mapReferences["Klasse"] = new Reference("teilleistungberechnet","datamodel/klasse");
}


teilleistungberechnetmapper::~teilleistungberechnetmapper(){}


 PObject* teilleistungberechnetmapper::createNewObject()
 {
     return new teilleistungberechnet();
 }


 teilleistungberechnet* teilleistungberechnetmapper::create()
 {
     return  (teilleistungberechnet*) AbstractMapper::create( teilleistungberechnetmapper::getInstance() );
 }


 string teilleistungberechnetmapper::getTableName()
 {
     return string("teilleistungberechnet");
 }
 
 string teilleistungberechnetmapper::getClassName()
 {
 	return string("teilleistungberechnet");
 }
 
 string* teilleistungberechnetmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* teilleistungberechnetmapper::getColumns()
 {
 	return columns;
 }
 
 int teilleistungberechnetmapper::getColumnCount()
 {
     return 0;
 }


 string* teilleistungberechnetmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	teilleistungberechnet *o = (teilleistungberechnet*) realSubject;
return values;
 }


 void teilleistungberechnetmapper::save(){
qWarning("teilleistungberechnet: save() not implemented");
}

void teilleistungberechnetmapper::save(PObject *realSubject)
{
 	teilleistungberechnet *o = (teilleistungberechnet*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Teilleistungen -> save(realSubject, o->getTeilleistungen() );

	mapReferences[ "Klasse" ] -> save(realSubject, (PObject*) o->getKlasse());
	teilleistungmapper::save(realSubject);
}


void teilleistungberechnetmapper::init(PObject* inito, Variant *res)
 {
 	teilleistungberechnet *o = (teilleistungberechnet*) inito;
	inito->init();
}


 list<teilleistungberechnet *>*teilleistungberechnetmapper::find() 
 {
 	return (list <teilleistungberechnet*>*) Database::getInstance()->getAll(this); 
}


list<teilleistung*> * teilleistungberechnetmapper::findTeilleistungen(int pri_id) 
 { 
 	return asc_Teilleistungen ->  findAssociates( pri_id );
     }


list<teilleistung*> * teilleistungberechnetmapper::findTeilleistungen(int pri_id,string prop,string value) 
         { 
             return asc_Teilleistungen ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* teilleistungberechnetmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "teilleistungberechnet" ); 
	entry->addProperty( new StringProperty<teilleistungberechnet>("Name", "string", &teilleistungberechnet::getName, &teilleistungberechnet::setName, false) );
	entry->addProperty( new CollectionPropertyImpl<teilleistung,teilleistungberechnet>( "Teilleistungen" , "teilleistung", &teilleistungberechnet::getTeilleistungen, &teilleistungberechnet::addToTeilleistungen, &teilleistungberechnet::deleteFromTeilleistungen  ) ); 
	entry->addProperty( new PObjectProperty<klasse,teilleistungberechnet>( "Klasse" , "klasse", &teilleistungberechnet::getKlasse,&teilleistungberechnet::setKlasse ) ); 
	entry->registerBase( "teilleistung" );
	return entry;
 }
