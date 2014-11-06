#include "testsstundenplan.h"

#include "services/sstundenplan.h"
#include "datamodel/schultag.h"
#include "datamodel/stundenplaneintrag.h"
#include "datamodel/datamodelrepository.h"
#include "orm/persistence/database.h"
#include "orm/transactions/transactions.h"
#include "services/actions/createaction.h"
#include "datamodel/klasse.h"
#include <list>

using namespace std;

TestSStundenplan::TestSStundenplan()
{
}


TestSStundenplan::~TestSStundenplan()
{
}



void TestSStundenplan::run()
{
	
	DataModelRepository::getInstance();

	
	klasse *kl = (klasse*) CreateAction::getInstance()->create("klasse");
	int kl_id = kl->getID();

	stundenplantemplateeintrag *te = SStundenplan::getInstance()->createTemplateEintrag(QDate::currentDate().dayOfWeek(),5);
	te->setKlasse(kl);
	kl->addToStundenplanTemplates(te);

	stundenplantemplateeintrag *tee = SStundenplan::getInstance()->createTemplateEintrag(QDate::currentDate().dayOfWeek(),5);
	int te_id = te->getID();

	if(te != tee){fail("Could not recover templateeintrag"); return;}
	if(tee->getKlasse() != kl){fail("Recovered templateeintrag with wrong klasse"); return;}
	
	
	stundenplaneintrag *e = SStundenplan::getInstance()->createEintrag(te,QDate::currentDate());
	if( !e ){fail("Could not create eintrag"); return;}
	if(!(e->getDatum() == QDate::currentDate())){ fail("Confusing datehandling!??");return;}
	//e->setKlasse(kl);
	if(e->getKlasse() != kl){fail("different klasse in original entry");return;}
	
	stundenplaneintrag *ee = SStundenplan::getInstance()->createEintrag(te,QDate::currentDate());
	if( e != ee){fail("Could not recover eintrag"); return;}
	if(ee->getKlasse() != kl){fail("different klasse in recovered entry");return;}
	int e_id = e->getID();

	SStundenplan::close();

	tee = SStundenplan::getInstance()-> createTemplateEintrag(QDate::currentDate().dayOfWeek(),5);
	int tee_id = tee->getID();
	if(te_id != tee_id){fail("different template instance after close"); return;}
	if(tee->getKlasse() != kl){fail("different klasse after close in template"); return;}


	ee = SStundenplan::getInstance()->createEintrag(te,QDate::currentDate());
	int ee_id = ee->getID();
	if(e_id != ee_id){fail("different eintrag instance after close"); return;}
	if(ee->getKlasse() != kl){fail("different klasse after close in eintrage"); return;}

	
	list<stundenplaneintrag*> *list_eintraege = SStundenplan::getInstance()->getEintraegeForWeek(kl,QDate::currentDate());
	if(list_eintraege->size() != 1){fail(QString("wrong number of of stundenplaneintraege (%1)").arg(list_eintraege->size())); return;}

	stundenplaneintrag *ein = *(list_eintraege->begin());
	int id_ein = ein->getID();
	QDate dateTime = ein->getDatum();

	Transactions::getCurrentTransaction()->commit();
	Database::getInstance()->close();
	PObject *o = Database::getInstance()->loadObjectById(id_ein);
	stundenplaneintrag *einein = dynamic_cast<stundenplaneintrag*>(o);

	if(!einein){fail(QString("Could not recover stundenplaneintrag")); return;}
	if(einein->getDatum() != dateTime){fail(QString("stundenplaneintrag with wrong QDateTime %1 / %2").arg(einein->getDatum().toString()).arg(dateTime.toString()));return;}

	publish("Erfolg");	
}

