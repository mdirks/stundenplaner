// 
 // C++ Implementation: PObjectCanvasItemmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "pobjectcanvasitemmapper.h"
 #include "utils/utils.h"
 #include "pobjectcanvasitem.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 PObjectCanvasItemmapper* PObjectCanvasItemmapper::instance=0;
 
 PObjectCanvasItemmapper* PObjectCanvasItemmapper::getInstance()
 {
 	if(!instance){
 		instance=new PObjectCanvasItemmapper();
 	}
 	return instance;
 }


 PObjectCanvasItemmapper::PObjectCanvasItemmapper()
  {
 	version = "0.4";
	columns = new string[5];
 	columnTypes = new string[5];
 	columns[0] = "xpos";
 	columnTypes[0] = "real";
	mapProperties["xpos"] = new Property("xpos");
	columns[1] = "ypos";
 	columnTypes[1] = "real";
	mapProperties["ypos"] = new Property("ypos");
	columns[2] = "width";
 	columnTypes[2] = "integer";
	mapProperties["width"] = new Property("width");
	columns[3] = "height";
 	columnTypes[3] = "integer";
	mapProperties["height"] = new Property("height");
	columns[4] = "color";
 	columnTypes[4] = "integer";
	mapProperties["color"] = new Property("color");
mapReferences["Object"] = new Reference("PObjectCanvasItem","persistence/PObject");
}


PObjectCanvasItemmapper::~PObjectCanvasItemmapper(){}


 PObject* PObjectCanvasItemmapper::createNewObject()
 {
     return new PObjectCanvasItem();
 }


 PObjectCanvasItem* PObjectCanvasItemmapper::create()
 {
     return  (PObjectCanvasItem*) AbstractMapper::create( PObjectCanvasItemmapper::getInstance() );
 }


 string PObjectCanvasItemmapper::getTableName()
 {
     return string("pobjectcanvasitem");
 }
 
 string PObjectCanvasItemmapper::getClassName()
 {
 	return string("PObjectCanvasItem");
 }
 
 string* PObjectCanvasItemmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* PObjectCanvasItemmapper::getColumns()
 {
 	return columns;
 }
 
 int PObjectCanvasItemmapper::getColumnCount()
 {
     return 5;
 }


 string* PObjectCanvasItemmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[5];  
 	PObjectCanvasItem *o = (PObjectCanvasItem*) realSubject;
	values[0] = to_string(o->x());
	values[1] = to_string(o->y());
	values[2] = to_string(o->width());
	values[3] = to_string(o->height());
	values[4] = to_string(o->getColor());
return values;
 }


 void PObjectCanvasItemmapper::save(){
qWarning("PObjectCanvasItem: save() not implemented");
}

void PObjectCanvasItemmapper::save(PObject *realSubject)
{
 	PObjectCanvasItem *o = (PObjectCanvasItem*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	mapReferences[ "Object" ] -> save(realSubject, (PObject*) o->getObject());
}


void PObjectCanvasItemmapper::init(PObject* inito, Variant *res)
 {
 	PObjectCanvasItem *o = (PObjectCanvasItem*) inito;
	o->setX( res[0].asdouble());
 	o->setY( res[1].asdouble());
 	o->setWidth( res[2].asint());
 	o->setHeight( res[3].asint());
 	o->setColor( res[4].asint());
 	inito->init();
}


 list<PObjectCanvasItem *>*PObjectCanvasItemmapper::find() 
 {
 	return (list <PObjectCanvasItem*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* PObjectCanvasItemmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "PObjectCanvasItem" ); 
	entry->addProperty( new StringProperty<PObjectCanvasItem>("Name", "string", &PObjectCanvasItem::getName, &PObjectCanvasItem::setName, false) );
	entry->addProperty( new NumericProperty< double,PObjectCanvasItem> ( "x", "double" , &PObjectCanvasItem::x,&PObjectCanvasItem::setX ) ); 
	entry->addProperty( new NumericProperty< double,PObjectCanvasItem> ( "y", "double" , &PObjectCanvasItem::y,&PObjectCanvasItem::setY ) ); 
	entry->addProperty( new NumericProperty< int,PObjectCanvasItem> ( "width", "int" , &PObjectCanvasItem::width,&PObjectCanvasItem::setWidth ) ); 
	entry->addProperty( new NumericProperty< int,PObjectCanvasItem> ( "height", "int" , &PObjectCanvasItem::height,&PObjectCanvasItem::setHeight ) ); 
	entry->addProperty( new NumericProperty< int,PObjectCanvasItem> ( "Color", "int" , &PObjectCanvasItem::getColor,&PObjectCanvasItem::setColor ) ); 
	entry->addProperty( new PObjectProperty<PObject,PObjectCanvasItem>( "Object" , "PObject", &PObjectCanvasItem::getObject,&PObjectCanvasItem::setObject ) ); 
	return entry;
 }
