// 
 // C++ Implementation: PObjectGraphicsItemmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "pobjectgraphicsitemmapper.h"
 #include "services/utils/utils.h"
 #include "pobjectgraphicsitem.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 PObjectGraphicsItemmapper* PObjectGraphicsItemmapper::instance=0;
 
 PObjectGraphicsItemmapper* PObjectGraphicsItemmapper::getInstance()
 {
 	if(!instance){
 		instance=new PObjectGraphicsItemmapper();
 	}
 	return instance;
 }


 PObjectGraphicsItemmapper::PObjectGraphicsItemmapper()
  {
 	version = "0.6";
	columns = new string[6];
 	columnTypes = new string[6];
 	columns[0] = "xpos";
 	columnTypes[0] = "real";
	mapProperties["xpos"] = new Property("xpos");
	columns[1] = "ypos";
 	columnTypes[1] = "real";
	mapProperties["ypos"] = new Property("ypos");
	columns[2] = "zpos";
 	columnTypes[2] = "real";
	mapProperties["zpos"] = new Property("zpos");
	columns[3] = "width";
 	columnTypes[3] = "integer";
	mapProperties["width"] = new Property("width");
	columns[4] = "height";
 	columnTypes[4] = "integer";
	mapProperties["height"] = new Property("height");
	columns[5] = "color";
 	columnTypes[5] = "integer";
	mapProperties["color"] = new Property("color");
mapReferences["Object"] = new Reference("PObjectGraphicsItem","orm/persistence/PObject");
}


PObjectGraphicsItemmapper::~PObjectGraphicsItemmapper(){}


 PObject* PObjectGraphicsItemmapper::createNewObject()
 {
     return new PObjectGraphicsItem();
 }


 PObjectGraphicsItem* PObjectGraphicsItemmapper::create()
 {
     return  (PObjectGraphicsItem*) AbstractMapper::create( PObjectGraphicsItemmapper::getInstance() );
 }


 string PObjectGraphicsItemmapper::getTableName()
 {
     return string("pobjectgraphicsitem");
 }
 
 string PObjectGraphicsItemmapper::getClassName()
 {
 	return string("PObjectGraphicsItem");
 }
 
 string* PObjectGraphicsItemmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* PObjectGraphicsItemmapper::getColumns()
 {
 	return columns;
 }
 
 int PObjectGraphicsItemmapper::getColumnCount()
 {
     return 6;
 }


 string* PObjectGraphicsItemmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[6];  
 	PObjectGraphicsItem *o = (PObjectGraphicsItem*) realSubject;
	values[0] = to_string(o->x());
	values[1] = to_string(o->y());
	values[2] = to_string(o->z());
	values[3] = to_string(o->width());
	values[4] = to_string(o->height());
	values[5] = to_string(o->getColor());
return values;
 }


 void PObjectGraphicsItemmapper::save(){
qWarning("PObjectGraphicsItem: save() not implemented");
}

void PObjectGraphicsItemmapper::save(PObject *realSubject)
{
 	PObjectGraphicsItem *o = (PObjectGraphicsItem*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	mapReferences[ "Object" ] -> save(realSubject, (PObject*) o->getObject());
}


void PObjectGraphicsItemmapper::init(PObject* inito, Variant *res)
 {
 	PObjectGraphicsItem *o = (PObjectGraphicsItem*) inito;
	o->setX( res[0].asdouble());
 	o->setY( res[1].asdouble());
 	o->setZValue( res[2].asdouble());
 	o->setWidth( res[3].asint());
 	o->setHeight( res[4].asint());
 	o->setColor( res[5].asint());
 	inito->init();
}


 list<PObjectGraphicsItem *>*PObjectGraphicsItemmapper::find() 
 {
 	return (list <PObjectGraphicsItem*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* PObjectGraphicsItemmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "PObjectGraphicsItem" ); 
	entry->addProperty( new StringProperty<PObjectGraphicsItem>("Name", "string", &PObjectGraphicsItem::getName, &PObjectGraphicsItem::setName, false) );
	entry->addProperty( new NumericProperty< double,PObjectGraphicsItem> ( "x", "double" , &PObjectGraphicsItem::x,&PObjectGraphicsItem::setX ) ); 
	entry->addProperty( new NumericProperty< double,PObjectGraphicsItem> ( "y", "double" , &PObjectGraphicsItem::y,&PObjectGraphicsItem::setY ) ); 
	entry->addProperty( new NumericProperty< double,PObjectGraphicsItem> ( "z", "double" , &PObjectGraphicsItem::z,&PObjectGraphicsItem::setZValue ) ); 
	entry->addProperty( new NumericProperty< int,PObjectGraphicsItem> ( "width", "int" , &PObjectGraphicsItem::width,&PObjectGraphicsItem::setWidth ) ); 
	entry->addProperty( new NumericProperty< int,PObjectGraphicsItem> ( "height", "int" , &PObjectGraphicsItem::height,&PObjectGraphicsItem::setHeight ) ); 
	entry->addProperty( new NumericProperty< int,PObjectGraphicsItem> ( "Color", "int" , &PObjectGraphicsItem::getColor,&PObjectGraphicsItem::setColor ) ); 
	entry->addProperty( new PObjectProperty<PObject,PObjectGraphicsItem>( "Object" , "PObject", &PObjectGraphicsItem::getObject,&PObjectGraphicsItem::setObject ) ); 
	return entry;
 }
