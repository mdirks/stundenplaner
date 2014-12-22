// 
 // C++ Implementation: SchultagGraphicsItemmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "schultaggraphicsitemmapper.h"
 #include "services/utils/utils.h"
 #include "schultaggraphicsitem.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 SchultagGraphicsItemmapper* SchultagGraphicsItemmapper::instance=0;
 
 SchultagGraphicsItemmapper* SchultagGraphicsItemmapper::getInstance()
 {
 	if(!instance){
 		instance=new SchultagGraphicsItemmapper();
 	}
 	return instance;
 }


 SchultagGraphicsItemmapper::SchultagGraphicsItemmapper()
  {
 	version = "0.1";
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
}


SchultagGraphicsItemmapper::~SchultagGraphicsItemmapper(){}


 PObject* SchultagGraphicsItemmapper::createNewObject()
 {
     return new SchultagGraphicsItem();
 }


 SchultagGraphicsItem* SchultagGraphicsItemmapper::create()
 {
     return  (SchultagGraphicsItem*) AbstractMapper::create( SchultagGraphicsItemmapper::getInstance() );
 }


 string SchultagGraphicsItemmapper::getTableName()
 {
     return string("schultaggraphicsitem");
 }
 
 string SchultagGraphicsItemmapper::getClassName()
 {
 	return string("SchultagGraphicsItem");
 }
 
 string* SchultagGraphicsItemmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* SchultagGraphicsItemmapper::getColumns()
 {
 	return columns;
 }
 
 int SchultagGraphicsItemmapper::getColumnCount()
 {
     return 6;
 }


 string* SchultagGraphicsItemmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[6];  
 	SchultagGraphicsItem *o = (SchultagGraphicsItem*) realSubject;
	values[0] = to_string(o->x());
	values[1] = to_string(o->y());
	values[2] = to_string(o->z());
	values[3] = to_string(o->width());
	values[4] = to_string(o->height());
	values[5] = to_string(o->getColor());
return values;
 }


 void SchultagGraphicsItemmapper::save(){
qWarning("SchultagGraphicsItem: save() not implemented");
}

void SchultagGraphicsItemmapper::save(PObject *realSubject)
{
 	SchultagGraphicsItem *o = (SchultagGraphicsItem*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	PObjectGraphicsItemmapper::save(realSubject);
}


void SchultagGraphicsItemmapper::init(PObject* inito, Variant *res)
 {
 	SchultagGraphicsItem *o = (SchultagGraphicsItem*) inito;
	o->setX( res[0].asdouble());
 	o->setY( res[1].asdouble());
 	o->setZValue( res[2].asdouble());
 	o->setWidth( res[3].asint());
 	o->setHeight( res[4].asint());
 	o->setColor( res[5].asint());
 	inito->init();
}


 list<SchultagGraphicsItem *>*SchultagGraphicsItemmapper::find() 
 {
 	return (list <SchultagGraphicsItem*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* SchultagGraphicsItemmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "SchultagGraphicsItem" ); 
	entry->addProperty( new StringProperty<SchultagGraphicsItem>("Name", "string", &SchultagGraphicsItem::getName, &SchultagGraphicsItem::setName, false) );
	entry->addProperty( new NumericProperty< double,SchultagGraphicsItem> ( "x", "double" , &SchultagGraphicsItem::x,&SchultagGraphicsItem::setX ) ); 
	entry->addProperty( new NumericProperty< double,SchultagGraphicsItem> ( "y", "double" , &SchultagGraphicsItem::y,&SchultagGraphicsItem::setY ) ); 
	entry->addProperty( new NumericProperty< double,SchultagGraphicsItem> ( "z", "double" , &SchultagGraphicsItem::z,&SchultagGraphicsItem::setZValue ) ); 
	entry->addProperty( new NumericProperty< int,SchultagGraphicsItem> ( "width", "int" , &SchultagGraphicsItem::width,&SchultagGraphicsItem::setWidth ) ); 
	entry->addProperty( new NumericProperty< int,SchultagGraphicsItem> ( "height", "int" , &SchultagGraphicsItem::height,&SchultagGraphicsItem::setHeight ) ); 
	entry->addProperty( new NumericProperty< int,SchultagGraphicsItem> ( "Color", "int" , &SchultagGraphicsItem::getColor,&SchultagGraphicsItem::setColor ) ); 
	entry->registerBase( "PObjectGraphicsItem" );
	return entry;
 }
