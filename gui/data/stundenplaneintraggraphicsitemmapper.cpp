// 
 // C++ Implementation: StundenplaneintragGraphicsItemmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "stundenplaneintraggraphicsitemmapper.h"
 #include "services/utils/utils.h"
 #include "stundenplaneintraggraphicsitem.h"
#include "orm/persistence/database.h"
 #include "orm/repository/urlproperty.h"
 //#include "orm/mappingproperty.h"

 StundenplaneintragGraphicsItemmapper* StundenplaneintragGraphicsItemmapper::instance=0;
 
 StundenplaneintragGraphicsItemmapper* StundenplaneintragGraphicsItemmapper::getInstance()
 {
 	if(!instance){
 		instance=new StundenplaneintragGraphicsItemmapper();
 	}
 	return instance;
 }


 StundenplaneintragGraphicsItemmapper::StundenplaneintragGraphicsItemmapper()
  {
 	version = "0.1-0.6";
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


StundenplaneintragGraphicsItemmapper::~StundenplaneintragGraphicsItemmapper(){}


 PObject* StundenplaneintragGraphicsItemmapper::createNewObject()
 {
     return new StundenplaneintragGraphicsItem();
 }


 StundenplaneintragGraphicsItem* StundenplaneintragGraphicsItemmapper::create()
 {
     return  (StundenplaneintragGraphicsItem*) AbstractMapper::create( StundenplaneintragGraphicsItemmapper::getInstance() );
 }


 string StundenplaneintragGraphicsItemmapper::getTableName()
 {
     return string("stundenplaneintraggraphicsitem");
 }
 
 string StundenplaneintragGraphicsItemmapper::getClassName()
 {
 	return string("StundenplaneintragGraphicsItem");
 }
 
 string* StundenplaneintragGraphicsItemmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* StundenplaneintragGraphicsItemmapper::getColumns()
 {
 	return columns;
 }
 
 int StundenplaneintragGraphicsItemmapper::getColumnCount()
 {
     return 6;
 }


 string* StundenplaneintragGraphicsItemmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[6];  
 	StundenplaneintragGraphicsItem *o = (StundenplaneintragGraphicsItem*) realSubject;
	values[0] = to_string(o->x());
	values[1] = to_string(o->y());
	values[2] = to_string(o->z());
	values[3] = to_string(o->width());
	values[4] = to_string(o->height());
	values[5] = to_string(o->getColor());
return values;
 }


 void StundenplaneintragGraphicsItemmapper::save(){
qWarning("StundenplaneintragGraphicsItem: save() not implemented");
}

void StundenplaneintragGraphicsItemmapper::save(PObject *realSubject)
{
 	StundenplaneintragGraphicsItem *o = (StundenplaneintragGraphicsItem*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	PObjectGraphicsItemmapper::save(realSubject);
}


void StundenplaneintragGraphicsItemmapper::init(PObject* inito, Variant *res)
 {
 	StundenplaneintragGraphicsItem *o = (StundenplaneintragGraphicsItem*) inito;
	o->setX( res[0].asdouble());
 	o->setY( res[1].asdouble());
 	o->setZValue( res[2].asdouble());
 	o->setWidth( res[3].asint());
 	o->setHeight( res[4].asint());
 	o->setColor( res[5].asint());
 	inito->init();
}


 list<StundenplaneintragGraphicsItem *>*StundenplaneintragGraphicsItemmapper::find() 
 {
 	return (list <StundenplaneintragGraphicsItem*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* StundenplaneintragGraphicsItemmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "StundenplaneintragGraphicsItem" ); 
	entry->addProperty( new StringProperty<StundenplaneintragGraphicsItem>("Name", "string", &StundenplaneintragGraphicsItem::getName, &StundenplaneintragGraphicsItem::setName, false) );
	entry->addProperty( new NumericProperty< double,StundenplaneintragGraphicsItem> ( "x", "double" , &StundenplaneintragGraphicsItem::x,&StundenplaneintragGraphicsItem::setX ) ); 
	entry->addProperty( new NumericProperty< double,StundenplaneintragGraphicsItem> ( "y", "double" , &StundenplaneintragGraphicsItem::y,&StundenplaneintragGraphicsItem::setY ) ); 
	entry->addProperty( new NumericProperty< double,StundenplaneintragGraphicsItem> ( "z", "double" , &StundenplaneintragGraphicsItem::z,&StundenplaneintragGraphicsItem::setZValue ) ); 
	entry->addProperty( new NumericProperty< int,StundenplaneintragGraphicsItem> ( "width", "int" , &StundenplaneintragGraphicsItem::width,&StundenplaneintragGraphicsItem::setWidth ) ); 
	entry->addProperty( new NumericProperty< int,StundenplaneintragGraphicsItem> ( "height", "int" , &StundenplaneintragGraphicsItem::height,&StundenplaneintragGraphicsItem::setHeight ) ); 
	entry->addProperty( new NumericProperty< int,StundenplaneintragGraphicsItem> ( "Color", "int" , &StundenplaneintragGraphicsItem::getColor,&StundenplaneintragGraphicsItem::setColor ) ); 
	entry->registerBase( "PObjectGraphicsItem" );
	return entry;
 }
