// 
 // C++ Implementation: lernkartemapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "lernkartemapper.h"
 #include "services/utils/utils.h"
 #include "lernkarte.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 lernkartemapper* lernkartemapper::instance=0;
 
 lernkartemapper* lernkartemapper::getInstance()
 {
 	if(!instance){
 		instance=new lernkartemapper();
 	}
 	return instance;
 }


 lernkartemapper::lernkartemapper()
  {
 	version = "0.5";
	columns = new string[5];
 	columnTypes = new string[5];
 	columns[0] = "vorn";
 	columnTypes[0] = "varchar(30)";
	mapProperties["vorn"] = new Property("vorn");
	columns[1] = "hinten";
 	columnTypes[1] = "varchar(30)";
	mapProperties["hinten"] = new Property("hinten");
	columns[2] = "sourcevorn";
 	columnTypes[2] = "text";
	mapProperties["sourcevorn"] = new Property("sourcevorn");
	columns[3] = "sourcehinten";
 	columnTypes[3] = "text";
	mapProperties["sourcehinten"] = new Property("sourcehinten");
	columns[4] = "compiled";
 	columnTypes[4] = "bool";
	mapProperties["compiled"] = new Property("compiled");
}


lernkartemapper::~lernkartemapper(){}


 PObject* lernkartemapper::createNewObject()
 {
     return new lernkarte();
 }


 lernkarte* lernkartemapper::create()
 {
     return  (lernkarte*) AbstractMapper::create( lernkartemapper::getInstance() );
 }


 string lernkartemapper::getTableName()
 {
     return string("lernkarte");
 }
 
 string lernkartemapper::getClassName()
 {
 	return string("lernkarte");
 }
 
 string* lernkartemapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* lernkartemapper::getColumns()
 {
 	return columns;
 }
 
 int lernkartemapper::getColumnCount()
 {
     return 5;
 }


 string* lernkartemapper::getValues(PObject *realSubject)
 {
 	string *values = new string[5];  
 	lernkarte *o = (lernkarte*) realSubject;
	values[0] = to_string(o->getVorn());
	values[1] = to_string(o->getHinten());
	values[2] = to_string(o->getSourceVorn());
	values[3] = to_string(o->getSourceHinten());
	values[4] = to_string(o->getCompiled());
return values;
 }


 void lernkartemapper::save(){
qWarning("lernkarte: save() not implemented");
}

void lernkartemapper::save(PObject *realSubject)
{
 	lernkarte *o = (lernkarte*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
}


void lernkartemapper::init(PObject* inito, Variant *res)
 {
 	lernkarte *o = (lernkarte*) inito;
	o->setVorn( res[0].asQUrl());
 	o->setHinten( res[1].asQUrl());
 	o->setSourceVorn( res[2].asstring());
 	o->setSourceHinten( res[3].asstring());
 	o->setCompiled( res[4].asbool());
 	inito->init();
}


 list<lernkarte *>*lernkartemapper::find() 
 {
 	return (list <lernkarte*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* lernkartemapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "lernkarte" ); 
	entry->addProperty( new StringProperty<lernkarte>("Name", "string", &lernkarte::getName, &lernkarte::setName, false) );
	entry->addProperty( new StringProperty< lernkarte >( "SourceVorn" , "string", &lernkarte::getSourceVorn, &lernkarte::setSourceVorn, true ) );
	entry->addProperty( new StringProperty< lernkarte >( "SourceHinten" , "string", &lernkarte::getSourceHinten, &lernkarte::setSourceHinten, true ) );
	entry->addProperty( new BooleanProperty< lernkarte> ( "Compiled", "bool" , &lernkarte::getCompiled,&lernkarte::setCompiled ) ); 
	return entry;
 }
