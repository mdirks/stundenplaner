// 
 // C++ Implementation: GuiObjectmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "guiobjectmapper.h"
 #include "services/utils/utils.h"
 #include "guiobject.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 GuiObjectmapper* GuiObjectmapper::instance=0;
 
 GuiObjectmapper* GuiObjectmapper::getInstance()
 {
 	if(!instance){
 		instance=new GuiObjectmapper();
 	}
 	return instance;
 }


 GuiObjectmapper::GuiObjectmapper()
  {
 	version = "0.1";
	columns = new string[0];
 	columnTypes = new string[0];
 mapReferences["DashBoard"] = new Reference("GuiObject","ThemaMap");
}


GuiObjectmapper::~GuiObjectmapper(){}


 PObject* GuiObjectmapper::createNewObject()
 {
     return new GuiObject();
 }


 GuiObject* GuiObjectmapper::create()
 {
     return  (GuiObject*) AbstractMapper::create( GuiObjectmapper::getInstance() );
 }


 string GuiObjectmapper::getTableName()
 {
     return string("guiobject");
 }
 
 string GuiObjectmapper::getClassName()
 {
 	return string("GuiObject");
 }
 
 string* GuiObjectmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* GuiObjectmapper::getColumns()
 {
 	return columns;
 }
 
 int GuiObjectmapper::getColumnCount()
 {
     return 0;
 }


 string* GuiObjectmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	GuiObject *o = (GuiObject*) realSubject;
return values;
 }


 void GuiObjectmapper::save(){
qWarning("GuiObject: save() not implemented");
}

void GuiObjectmapper::save(PObject *realSubject)
{
 	GuiObject *o = (GuiObject*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	mapReferences[ "DashBoard" ] -> save(realSubject, (PObject*) o->getDashBoard());
}


void GuiObjectmapper::init(PObject* inito, Variant *res)
 {
 	GuiObject *o = (GuiObject*) inito;
	inito->init();
}


 list<GuiObject *>*GuiObjectmapper::find() 
 {
 	return (list <GuiObject*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* GuiObjectmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "GuiObject" ); 
	entry->addProperty( new StringProperty<GuiObject>("Name", "string", &GuiObject::getName, &GuiObject::setName, false) );
	entry->addProperty( new PObjectProperty<ThemaMap,GuiObject>( "DashBoard" , "ThemaMap", &GuiObject::getDashBoard,&GuiObject::setDashBoard ) ); 
	return entry;
 }
