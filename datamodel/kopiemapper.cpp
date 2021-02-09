// 
 // C++ Implementation: kopiemapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "kopiemapper.h"
 #include "services/utils/utils.h"
 #include "kopie.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 kopiemapper* kopiemapper::instance=0;
 
 kopiemapper* kopiemapper::getInstance()
 {
 	if(!instance){
 		instance=new kopiemapper();
 	}
 	return instance;
 }


 kopiemapper::kopiemapper()
  {
 	version = "0.1-0.6";
	columns = new string[2];
 	columnTypes = new string[2];
 	columns[0] = "title";
 	columnTypes[0] = "varchar(50)";
	mapProperties["title"] = new Property("title");
	columns[1] = "filename";
 	columnTypes[1] = "varchar(80)";
	mapProperties["filename"] = new Property("filename");
mapReferences["Lektuere"] = new Reference("kopie","datamodel/lektuere");
}


kopiemapper::~kopiemapper(){}


 PObject* kopiemapper::createNewObject()
 {
     return new kopie();
 }


 kopie* kopiemapper::create()
 {
     return  (kopie*) AbstractMapper::create( kopiemapper::getInstance() );
 }


 string kopiemapper::getTableName()
 {
     return string("kopie");
 }
 
 string kopiemapper::getClassName()
 {
 	return string("kopie");
 }
 
 string* kopiemapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* kopiemapper::getColumns()
 {
 	return columns;
 }
 
 int kopiemapper::getColumnCount()
 {
     return 2;
 }


 string* kopiemapper::getValues(PObject *realSubject)
 {
 	string *values = new string[2];  
 	kopie *o = (kopie*) realSubject;
	values[0] = to_string(o->getTitle());
	values[1] = to_string(o->getFileName());
return values;
 }


 void kopiemapper::save(){
qWarning("kopie: save() not implemented");
}

void kopiemapper::save(PObject *realSubject)
{
 	kopie *o = (kopie*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	mapReferences[ "Lektuere" ] -> save(realSubject, (PObject*) o->getLektuere());
	materialmapper::save(realSubject);
}


void kopiemapper::init(PObject* inito, Variant *res)
 {
 	kopie *o = (kopie*) inito;
	o->setTitle( res[0].asstring());
 	o->setFileName( res[1].asstring());
 	inito->init();
}


 list<kopie *>*kopiemapper::find() 
 {
 	return (list <kopie*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* kopiemapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "kopie" ); 
	entry->addProperty( new StringProperty<kopie>("Name", "string", &kopie::getName, &kopie::setName, false) );
	entry->addProperty( new StringProperty< kopie >( "title" , "string", &kopie::getTitle, &kopie::setTitle, false ) );
	entry->addProperty( new StringProperty< kopie >( "FileName" , "string", &kopie::getFileName, &kopie::setFileName, false ) );
	entry->addProperty( new PObjectProperty<lektuere,kopie>( "Lektuere" , "lektuere", &kopie::getLektuere,&kopie::setLektuere ) ); 
	entry->registerBase( "material" );
	return entry;
 }
