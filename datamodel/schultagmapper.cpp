// 
 // C++ Implementation: schultagmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "schultagmapper.h"
 #include "services/utils/utils.h"
 #include "schultag.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 schultagmapper* schultagmapper::instance=0;
 
 schultagmapper* schultagmapper::getInstance()
 {
 	if(!instance){
 		instance=new schultagmapper();
 	}
 	return instance;
 }


 schultagmapper::schultagmapper()
  {
 	version = "0.2-0.4";
	columns = new string[1];
 	columnTypes = new string[1];
 	columns[0] = "datum";
 	columnTypes[0] = "varchar(30)";
	mapProperties["datum"] = new Property("datum");
asc_Eintraege = new Association<schultag, stundenplaneintrag>("schultag_eintrag","schultag_id","eintrag_id","stundenplaneintrag", &schultag::addToEintraege, &schultag::deleteFromEintraege);
mapAssociations["Eintraege"] = asc_Eintraege;
registerAssociation( asc_Eintraege);
}


schultagmapper::~schultagmapper(){}


 PObject* schultagmapper::createNewObject()
 {
     return new schultag();
 }


 schultag* schultagmapper::create()
 {
     return  (schultag*) AbstractMapper::create( schultagmapper::getInstance() );
 }


 string schultagmapper::getTableName()
 {
     return string("schultag");
 }
 
 string schultagmapper::getClassName()
 {
 	return string("schultag");
 }
 
 string* schultagmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* schultagmapper::getColumns()
 {
 	return columns;
 }
 
 int schultagmapper::getColumnCount()
 {
     return 1;
 }


 string* schultagmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[1];  
 	schultag *o = (schultag*) realSubject;
	values[0] = to_string(o->getDatum());
return values;
 }


 void schultagmapper::save(){
qWarning("schultag: save() not implemented");
}

void schultagmapper::save(PObject *realSubject)
{
 	schultag *o = (schultag*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Eintraege -> save(realSubject, o->getEintraege() );

	notizholdermapper::save(realSubject);
}


void schultagmapper::init(PObject* inito, Variant *res)
 {
 	schultag *o = (schultag*) inito;
	o->setDatum( res[0].asQDateTime());
 	inito->init();
}


 list<schultag *>*schultagmapper::find() 
 {
 	return (list <schultag*>*) Database::getInstance()->getAll(this); 
}


list<stundenplaneintrag*> * schultagmapper::findEintraege(int pri_id) 
 { 
 	return asc_Eintraege ->  findAssociates( pri_id );
     }


list<stundenplaneintrag*> * schultagmapper::findEintraege(int pri_id,string prop,string value) 
         { 
             return asc_Eintraege ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* schultagmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "schultag" ); 
	entry->addProperty( new StringProperty<schultag>("Name", "string", &schultag::getName, &schultag::setName, false) );
	entry->addProperty( new DateTimeProperty< schultag> ( "Datum", "QDateTime" , &schultag::getDatum, &schultag::setDatum ) ); 
	entry->addProperty( new CollectionPropertyImpl<stundenplaneintrag,schultag>( "Eintraege" , "stundenplaneintrag", &schultag::getEintraege, &schultag::addToEintraege, &schultag::deleteFromEintraege  ) ); 
	entry->registerBase( "notizholder" );
	return entry;
 }
