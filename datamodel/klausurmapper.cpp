// 
 // C++ Implementation: klausurmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "klausurmapper.h"
 #include "services/utils/utils.h"
 #include "klausur.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 klausurmapper* klausurmapper::instance=0;
 
 klausurmapper* klausurmapper::getInstance()
 {
 	if(!instance){
 		instance=new klausurmapper();
 	}
 	return instance;
 }


 klausurmapper::klausurmapper()
  {
 	version = "0.3";
	columns = new string[0];
 	columnTypes = new string[0];
 asc_Materialien = new Association<klausur, material>("klausur_material","klausur_id","material_id","material", &klausur::addToMaterialien, &klausur::deleteFromMaterialien);
mapAssociations["Materialien"] = asc_Materialien;
registerAssociation( asc_Materialien);
}


klausurmapper::~klausurmapper(){}


 PObject* klausurmapper::createNewObject()
 {
     return new klausur();
 }


 klausur* klausurmapper::create()
 {
     return  (klausur*) AbstractMapper::create( klausurmapper::getInstance() );
 }


 string klausurmapper::getTableName()
 {
     return string("klausur");
 }
 
 string klausurmapper::getClassName()
 {
 	return string("klausur");
 }
 
 string* klausurmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* klausurmapper::getColumns()
 {
 	return columns;
 }
 
 int klausurmapper::getColumnCount()
 {
     return 0;
 }


 string* klausurmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	klausur *o = (klausur*) realSubject;
return values;
 }


 void klausurmapper::save(){
qWarning("klausur: save() not implemented");
}

void klausurmapper::save(PObject *realSubject)
{
 	klausur *o = (klausur*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Materialien -> save(realSubject, o->getMaterialien() );

	teilleistungmapper::save(realSubject);
}


void klausurmapper::init(PObject* inito, Variant *res)
 {
 	klausur *o = (klausur*) inito;
	inito->init();
}


 list<klausur *>*klausurmapper::find() 
 {
 	return (list <klausur*>*) Database::getInstance()->getAll(this); 
}


list<material*> * klausurmapper::findMaterialien(int pri_id) 
 { 
 	return asc_Materialien ->  findAssociates( pri_id );
 	}


RepositoryEntry* klausurmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "klausur" ); 
	entry->addProperty( new StringProperty<klausur>("Name", "string", &klausur::getName, &klausur::setName, false) );
	entry->addProperty( new CollectionPropertyImpl<material,klausur>( "Materialien" , "material", &klausur::getMaterialien, &klausur::addToMaterialien, &klausur::deleteFromMaterialien  ) ); 
	entry->registerBase( "teilleistung" );
	return entry;
 }
