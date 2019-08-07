#include "testsitzplan.h"
#include "datamodel/sitzplan.h"
#include "datamodel/schueler.h"
#include "datamodel/platz.h"
#include "datamodel/note.h"
#include "orm/transactions/transactions.h"
#include "datamodel/sitzplanmapper.h"
#include "datamodel/schuelermapper.h"
#include "datamodel/notemapper.h"
#include "orm/persistence/database.h"
#include "datamodel/datamodelrepository.h"

TestSitzplan::TestSitzplan()
{
}


TestSitzplan::~TestSitzplan()
{
}

void TestSitzplan::run()
{
	DataModelRepository::getInstance();

	sitzplan *sp = sitzplanmapper::create();	
	platz *p = sp->getPlatz(1,3);
	if(p==0){fail("Could not get platz from sitzplan"); return;}
	
	schueler *sch = schuelermapper::create();
	p->setSchueler(sch);

	string test_bem("Hallo");
	note *n = notemapper::create();
	n->setBemerkung(test_bem);
	p->addToNoten(n);
	qDebug("Note created");
	
	int id_sch = sch->getID();
	int id_p = p->getID();	
	int id_sp = sp->getID();
	int id_n = n->getID();

	Transactions::getCurrentTransaction()->commit();

	Database::getInstance()->close();

	PObject *o=Database::getInstance()->loadObjectById(id_sp);
	sp = dynamic_cast<sitzplan*>(o);
	if(sp == 0){fail("Could not recover sitzplan"); return;}

	p = sp->getPlatz(1,3);
	if(p==0){fail("Could not recover platz"); return;}
	if(p->getID() != id_p){fail("Wrong id in recovered platz");return;}
	list<note*> *list_noten = p->getNoten();
	if(! list_noten ) {fail("Could not recover noten from platz"); return;}
	n = list_noten->front();
	if(n->getID() != id_n){fail("Wrong id in recovered note"); return;}
	if(n->getBemerkung() != "Hallo"){fail("Bemerkung not properly saved"); return;}
	sch = p->getSchueler();
	if(sch==0){fail("Could recover schueler from platz"); return;}

	if(sch->getID() != id_sch){fail("Recovered schueler with wrong id"); return;}

	publish("Erfolg");
}

