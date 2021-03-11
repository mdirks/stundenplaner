// 
 // C++ Implementation: vokabelmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "vokabelmapper.h"
 #include "services/utils/utils.h"
 #include "vokabel.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 vokabelmapper* vokabelmapper::instance=0;
 
 vokabelmapper* vokabelmapper::getInstance()
 {
 	if(!instance){
 		instance=new vokabelmapper();
 	}
 	return instance;
 }


 vokabelmapper::vokabelmapper()
  {
 	version = "0.2";
	columns = new string[3];
 	columnTypes = new string[3];
 	columns[0] = "kanji";
 	columnTypes[0] = "varchar(50)";
	mapProperties["kanji"] = new Property("kanji");
	columns[1] = "reading";
 	columnTypes[1] = "varchar(50)";
	mapProperties["reading"] = new Property("reading");
	columns[2] = "translation";
 	columnTypes[2] = "varchar(50)";
	mapProperties["translation"] = new Property("translation");
asc_Beispiele = new Association<vokabel, bspsatz>("vokabel_bsp","vok_id","bsp_id","bspsatz", &vokabel::addToBeispiele, &vokabel::deleteFromBeispiele);
mapAssociations["Beispiele"] = asc_Beispiele;
registerAssociation( asc_Beispiele);
}


vokabelmapper::~vokabelmapper(){}


 PObject* vokabelmapper::createNewObject()
 {
     return new vokabel();
 }


 vokabel* vokabelmapper::create()
 {
     return  (vokabel*) AbstractMapper::create( vokabelmapper::getInstance() );
 }


 string vokabelmapper::getTableName()
 {
     return string("vokabel");
 }
 
 string vokabelmapper::getClassName()
 {
 	return string("vokabel");
 }
 
 string* vokabelmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* vokabelmapper::getColumns()
 {
 	return columns;
 }
 
 int vokabelmapper::getColumnCount()
 {
     return 3;
 }


 string* vokabelmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[3];  
 	vokabel *o = (vokabel*) realSubject;
	values[0] = to_string(o->getKanji());
	values[1] = to_string(o->getReading());
	values[2] = to_string(o->getTranslation());
return values;
 }


 void vokabelmapper::save(){
qWarning("vokabel: save() not implemented");
}

void vokabelmapper::save(PObject *realSubject)
{
 	vokabel *o = (vokabel*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Beispiele -> save(realSubject, o->getBeispiele() );

}


void vokabelmapper::init(PObject* inito, Variant *res)
 {
 	vokabel *o = (vokabel*) inito;
	o->setKanji( res[0].asstring());
 	o->setReading( res[1].asstring());
 	o->setTranslation( res[2].asstring());
 	inito->init();
}


 list<vokabel *>*vokabelmapper::find() 
 {
 	return (list <vokabel*>*) Database::getInstance()->getAll(this); 
}


list<bspsatz*> * vokabelmapper::findBeispiele(int pri_id) 
 { 
 	return asc_Beispiele ->  findAssociates( pri_id );
     }


list<bspsatz*> * vokabelmapper::findBeispiele(int pri_id,string prop,string value) 
         { 
             return asc_Beispiele ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* vokabelmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "vokabel" ); 
	entry->addProperty( new StringProperty<vokabel>("Name", "string", &vokabel::getName, &vokabel::setName, false) );
	entry->addProperty( new StringProperty< vokabel >( "Kanji" , "string", &vokabel::getKanji, &vokabel::setKanji, false ) );
	entry->addProperty( new StringProperty< vokabel >( "Reading" , "string", &vokabel::getReading, &vokabel::setReading, false ) );
	entry->addProperty( new StringProperty< vokabel >( "Translation" , "string", &vokabel::getTranslation, &vokabel::setTranslation, false ) );
	entry->addProperty( new CollectionPropertyImpl<bspsatz,vokabel>( "Beispiele" , "bspsatz", &vokabel::getBeispiele, &vokabel::addToBeispiele, &vokabel::deleteFromBeispiele  ) ); 
	return entry;
 }
