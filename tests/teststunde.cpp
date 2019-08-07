
#include "teststunde.h"
#include "services/actions/createaction.h"
#include "datamodel/stunde.h"
#include "orm/persistence/pobject.h"
#include "datamodel/datamodelrepository.h"
#include "orm/persistence/database.h"
#include "orm/mapping/mappingcontroler.h"
#include "orm/mapping/abstractmapper.h"
#include <QRegExp>
#include <QString>

#include <string>


#define TESTNAME "aSDfde"


using namespace std;

TestStunde::TestStunde() : TestCase()
{
}


TestStunde::~TestStunde()
{
}

void TestStunde::run()
{
	publish("Start");

    QRegExp rx("*/");
    rx.setPatternSyntax(QRegExp::Wildcard);
    if(QString("hallo/du").remove(rx) != QString("du")){fail("RegExp not working");return;}

	string s("hallo/du");
    if( s.erase(0,s.find_last_of("/")+1) != string("du") ){fail(QString("remove not working: %1").arg(s.c_str())); return;}

	stunde *st=testCreateObject();
	if( ! st ) return;

	st->setName(TESTNAME);
	
    thema *th=0;
    AbstractMapper *mapper =MappingControler::getInstance()->getMapperByName("thema");
	list<PObject*> *list_th = mapper->find_gen();
    if(list_th->size()>0){
        th = dynamic_cast<thema*>(list_th->front());
    } else {
        th = (thema*) CreateAction::getInstance()->create("thema");
    }
	if(!th){fail("Konnte kein Thema finden");return;}
 	st->setThema(th);
	
	st->save();

	int id = st->getID();

	Database::getInstance()->close();
	PObject *o=Database::getInstance()->loadObjectById(id);
	if(!o){fail("could not retrieve object from database");return;}
	st = dynamic_cast<stunde*>(o);
	if(!st){fail("retrieved object has wrong type");return;}
	
	if(st->getName() != TESTNAME){fail("name not saved");return;}
	
	th = st->getThema();
	if(!th){fail("Thema nicht gespeichert"); return;}
	

	publish("Erfolg");
}


stunde* TestStunde::testCreateObject()
{
	DataModelRepository::getInstance();

	PObject* o=0;
	stunde *st=0;
	o= CreateAction::getInstance()->create("stunde");
	if( !o ){
		fail("created object null");
		return 0;
	}
	st = dynamic_cast<stunde*>(o);
	if( !st  ){
		fail("created object not of type stunde");
		return 0;
	}
	return st;
}
