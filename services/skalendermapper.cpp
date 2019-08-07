// 
 // C++ Implementation: SKalendermapper
 //
 // Description: 
 //
 //
 // Author: Marcus Dirks <mopp@suse>, (C) 2005
 //
 // Copyright: See COPYING file that comes with this distribution
 //
 //
 #include "skalendermapper.h"
 #include "services/utils/utils.h"
 #include "skalender.h"
#include "orm/persistence/database.h"
 //#include "orm/mappingproperty.h"

 SKalendermapper* SKalendermapper::instance=0;
 
 SKalendermapper* SKalendermapper::getInstance()
 {
 	if(!instance){
 		instance=new SKalendermapper();
 	}
 	return instance;
 }


 SKalendermapper::SKalendermapper()
  {
 	version = "0.2";
	columns = new string[0];
 	columnTypes = new string[0];
 asc_Weeks = new Association<SKalender, WeekMap>("kalender_weeks","kalender_id","klasse_id","WeekMap", &SKalender::addToWeeks, &SKalender::deleteFromWeeks);
mapAssociations["Weeks"] = asc_Weeks;
registerAssociation( asc_Weeks);
asc_Days = new Association<SKalender, DayMap>("kalender_days","kalender_id","days_id","DayMap", &SKalender::addToDays, &SKalender::deleteFromDays);
mapAssociations["Days"] = asc_Days;
registerAssociation( asc_Days);
}


SKalendermapper::~SKalendermapper(){}


 PObject* SKalendermapper::createNewObject()
 {
     return new SKalender();
 }


 SKalender* SKalendermapper::create()
 {
     return  (SKalender*) AbstractMapper::create( SKalendermapper::getInstance() );
 }


 string SKalendermapper::getTableName()
 {
     return string("skalender");
 }
 
 string SKalendermapper::getClassName()
 {
 	return string("SKalender");
 }
 
 string* SKalendermapper::getColumnTypes()
 {
 	return columnTypes;
 }
 
 string* SKalendermapper::getColumns()
 {
 	return columns;
 }
 
 int SKalendermapper::getColumnCount()
 {
     return 0;
 }


 string* SKalendermapper::getValues(PObject *realSubject)
 {
 	string *values = new string[0];  
 	SKalender *o = (SKalender*) realSubject;
return values;
 }


 void SKalendermapper::save(){
qWarning("SKalender: save() not implemented");
}

void SKalendermapper::save(PObject *realSubject)
{
 	SKalender *o = (SKalender*) realSubject;

    Database *db = Database::getInstance();
    db->save(realSubject);
	asc_Weeks -> save(realSubject, o->getWeeks() );

	asc_Days -> save(realSubject, o->getDays() );

}


void SKalendermapper::init(PObject* inito, Variant *res)
 {
 	SKalender *o = (SKalender*) inito;
	inito->init();
}


 list<SKalender *>*SKalendermapper::find() 
 {
 	return (list <SKalender*>*) Database::getInstance()->getAll(this); 
}


list<WeekMap*> * SKalendermapper::findWeeks(int pri_id) 
 { 
 	return asc_Weeks ->  findAssociates( pri_id );
     }


list<WeekMap*> * SKalendermapper::findWeeks(int pri_id,string prop,string value) 
         { 
             return asc_Weeks ->  findAssociates( pri_id,prop,value);
             }


list<DayMap*> * SKalendermapper::findDays(int pri_id) 
 { 
 	return asc_Days ->  findAssociates( pri_id );
     }


list<DayMap*> * SKalendermapper::findDays(int pri_id,string prop,string value) 
         { 
             return asc_Days ->  findAssociates( pri_id,prop,value);
             }


RepositoryEntry* SKalendermapper::getRepositoryEntry()
 	{
 	RepositoryEntry* entry = new RepositoryEntryImpl( "SKalender" ); 
	entry->addProperty( new StringProperty<SKalender>("Name", "string", &SKalender::getName, &SKalender::setName, false) );
	entry->addProperty( new CollectionPropertyImpl<WeekMap,SKalender>( "Weeks" , "WeekMap", &SKalender::getWeeks, &SKalender::addToWeeks, &SKalender::deleteFromWeeks  ) ); 
	entry->addProperty( new CollectionPropertyImpl<DayMap,SKalender>( "Days" , "DayMap", &SKalender::getDays, &SKalender::addToDays, &SKalender::deleteFromDays  ) ); 
	return entry;
 }
