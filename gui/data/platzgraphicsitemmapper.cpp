// 
 // C++ Implementation: PlatzGraphicsItemmapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "platzgraphicsitemmapper.h"
 #include "services/utils/utils.h"
 #include "platzgraphicsitem.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 PlatzGraphicsItemmapper* PlatzGraphicsItemmapper::instance=0;
 
 PlatzGraphicsItemmapper* PlatzGraphicsItemmapper::getInstance()
 {
 	if(!instance){
 		instance=new PlatzGraphicsItemmapper();
 	}
 	return instance;
 }


 PlatzGraphicsItemmapper::PlatzGraphicsItemmapper()
  {
 	version = "0.4";
	columns = new string[12];
 	columnTypes = new string[12];
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
	columns[6] = "xpos";
 	columnTypes[6] = "real";
	mapProperties["xpos"] = new Property("xpos");
	columns[7] = "ypos";
 	columnTypes[7] = "real";
	mapProperties["ypos"] = new Property("ypos");
	columns[8] = "zpos";
 	columnTypes[8] = "real";
	mapProperties["zpos"] = new Property("zpos");
	columns[9] = "width";
 	columnTypes[9] = "integer";
	mapProperties["width"] = new Property("width");
	columns[10] = "height";
 	columnTypes[10] = "integer";
	mapProperties["height"] = new Property("height");
	columns[11] = "color";
 	columnTypes[11] = "integer";
	mapProperties["color"] = new Property("color");
mapReferences["Platz"] = new Reference("PlatzGraphicsItem","datamodel/platz");
}


PlatzGraphicsItemmapper::~PlatzGraphicsItemmapper(){}


 PObject* PlatzGraphicsItemmapper::createNewObject()
 {
     return new PlatzGraphicsItem();
 }


 PlatzGraphicsItem* PlatzGraphicsItemmapper::create()
 {
     return  (PlatzGraphicsItem*) AbstractMapper::create( PlatzGraphicsItemmapper::getInstance() );
 }


 string PlatzGraphicsItemmapper::getTableName()
 {
     return string("platzgraphicsitem");
 }
 
 string PlatzGraphicsItemmapper::getClassName()
 {
 	return string("PlatzGraphicsItem");
 }
 
 string* PlatzGraphicsItemmapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* PlatzGraphicsItemmapper::getColumns()
 {
 	return columns;
 }
 
 int PlatzGraphicsItemmapper::getColumnCount()
 {
     return 12;
 }


 string* PlatzGraphicsItemmapper::getValues(PObject *realSubject)
 {
 	string *values = new string[12];  
 	PlatzGraphicsItem *o = (PlatzGraphicsItem*) realSubject;
	values[0] = to_string(o->x());
	values[1] = to_string(o->y());
	values[2] = to_string(o->z());
	values[3] = to_string(o->width());
	values[4] = to_string(o->height());
	values[5] = to_string(o->getColor());
	values[6] = to_string(o->x());
	values[7] = to_string(o->y());
	values[8] = to_string(o->z());
	values[9] = to_string(o->width());
	values[10] = to_string(o->height());
	values[11] = to_string(o->getColor());
return values;
 }


 void PlatzGraphicsItemmapper::save(){
qWarning("PlatzGraphicsItem: save() not implemented");
}

void PlatzGraphicsItemmapper::save(PObject *realSubject)
{
 	PlatzGraphicsItem *o = (PlatzGraphicsItem*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	mapReferences[ "Platz" ] -> save(realSubject, (PObject*) o->getPlatz());
	PObjectGraphicsItemmapper::save(realSubject);
}


void PlatzGraphicsItemmapper::init(PObject* inito, Variant *res)
 {
 	PlatzGraphicsItem *o = (PlatzGraphicsItem*) inito;
	o->setX( res[0].asdouble());
 	o->setY( res[1].asdouble());
 	o->setZValue( res[2].asdouble());
 	o->setWidth( res[3].asint());
 	o->setHeight( res[4].asint());
 	o->setColor( res[5].asint());
 	o->setX( res[6].asdouble());
 	o->setY( res[7].asdouble());
 	o->setZValue( res[8].asdouble());
 	o->setWidth( res[9].asint());
 	o->setHeight( res[10].asint());
 	o->setColor( res[11].asint());
 	inito->init();
}


 list<PlatzGraphicsItem *>*PlatzGraphicsItemmapper::find() 
 {
 	return (list <PlatzGraphicsItem*>*) Database::getInstance()->getAll(this); 
}


RepositoryEntry* PlatzGraphicsItemmapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "PlatzGraphicsItem" ); 
	entry->addProperty( new StringProperty<PlatzGraphicsItem>("Name", "string", &PlatzGraphicsItem::getName, &PlatzGraphicsItem::setName, false) );
	entry->addProperty( new NumericProperty< double,PlatzGraphicsItem> ( "x", "double" , &PlatzGraphicsItem::x,&PlatzGraphicsItem::setX ) ); 
	entry->addProperty( new NumericProperty< double,PlatzGraphicsItem> ( "y", "double" , &PlatzGraphicsItem::y,&PlatzGraphicsItem::setY ) ); 
	entry->addProperty( new NumericProperty< double,PlatzGraphicsItem> ( "z", "double" , &PlatzGraphicsItem::z,&PlatzGraphicsItem::setZValue ) ); 
	entry->addProperty( new NumericProperty< int,PlatzGraphicsItem> ( "width", "int" , &PlatzGraphicsItem::width,&PlatzGraphicsItem::setWidth ) ); 
	entry->addProperty( new NumericProperty< int,PlatzGraphicsItem> ( "height", "int" , &PlatzGraphicsItem::height,&PlatzGraphicsItem::setHeight ) ); 
	entry->addProperty( new NumericProperty< int,PlatzGraphicsItem> ( "Color", "int" , &PlatzGraphicsItem::getColor,&PlatzGraphicsItem::setColor ) ); 
	entry->addProperty( new NumericProperty< double,PlatzGraphicsItem> ( "x", "double" , &PlatzGraphicsItem::x,&PlatzGraphicsItem::setX ) ); 
	entry->addProperty( new NumericProperty< double,PlatzGraphicsItem> ( "y", "double" , &PlatzGraphicsItem::y,&PlatzGraphicsItem::setY ) ); 
	entry->addProperty( new NumericProperty< double,PlatzGraphicsItem> ( "z", "double" , &PlatzGraphicsItem::z,&PlatzGraphicsItem::setZValue ) ); 
	entry->addProperty( new NumericProperty< int,PlatzGraphicsItem> ( "width", "int" , &PlatzGraphicsItem::width,&PlatzGraphicsItem::setWidth ) ); 
	entry->addProperty( new NumericProperty< int,PlatzGraphicsItem> ( "height", "int" , &PlatzGraphicsItem::height,&PlatzGraphicsItem::setHeight ) ); 
	entry->addProperty( new NumericProperty< int,PlatzGraphicsItem> ( "Color", "int" , &PlatzGraphicsItem::getColor,&PlatzGraphicsItem::setColor ) ); 
	entry->addProperty( new PObjectProperty<platz,PlatzGraphicsItem>( "Platz" , "platz", &PlatzGraphicsItem::getPlatz,&PlatzGraphicsItem::setPlatz ) ); 
	entry->registerBase( "PObjectGraphicsItem" );
	return entry;
 }
