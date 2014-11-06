
#include "teststundenplantemplateeintrag.h"

#include "datamodel/datamodelrepository.h"
#include "services/actions/createaction.h"
#include "datamodel/klasse.h"
#include "orm/transactions/transactions.h"
#include "orm/persistence/database.h"
#include "orm/persistence/pobject.h"

TestStundenplanTemplateEintrag::TestStundenplanTemplateEintrag()
{
}


TestStundenplanTemplateEintrag::~TestStundenplanTemplateEintrag()
{
}

void TestStundenplanTemplateEintrag::run()
{
	DataModelRepository::getInstance();
	stundenplantemplateeintrag* te =(stundenplantemplateeintrag*) CreateAction::getInstance()->create("stundenplantemplateeintrag");

	klasse *kl = (klasse*) CreateAction::getInstance()->create("klasse");

	te->setKlasse(kl);

	int id_kl = kl->getID();
	int id_te = te->getID();

	Transactions::getCurrentTransaction()->commit();
	Database::getInstance()->close();

	PObject *o=Database::getInstance()->loadObjectById(id_te);
	te = dynamic_cast<stundenplantemplateeintrag*>(o);
	if(!te){fail("Templateeintrag nicht gespeichert");return;}
	
	kl = te->getKlasse();
	if(!kl){fail("Klasse nicht gespeichert");return;}
	
	publish("Erfolg");
	
}


