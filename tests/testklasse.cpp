#include "testklasse.h"
#include "datamodel/klasse.h"
#include "datamodel/datamodelrepository.h"
#include "orm/transactions/transactions.h"
#include "orm/persistence/database.h"
#include "gui/actions/guicreateaction.h"


TestKlasse::TestKlasse()
{
}


TestKlasse::~TestKlasse()
{
}

void TestKlasse::run()
{
	DataModelRepository::getInstance();
	klasse *kl = (klasse*) GuiCreateAction::getInstance()->create("klasse");

	int id_kl = kl->getID();	

	Transactions::getCurrentTransaction()->commit();
	Database::getInstance()->close();

	PObject *o = Database::getInstance()->loadObjectById(id_kl);
	kl = dynamic_cast<klasse*>(o);
	if(!kl){fail("Klasse nicht gespeichert");return;}

	publish("Erfolg");
}

