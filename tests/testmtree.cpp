#include "testmtree.h"
#include "testrunner.h"
#include "datamodel/klasse.h"
#include "datamodel/datamodelrepository.h"
#include "orm/transactions/transactions.h"
#include "orm/persistence/database.h"
#include "orm/mapping/mtree.h"
#include "gui/actions/guicreateaction.h"


TestMTree::TestMTree()
{
}


TestMTree::~TestMTree()
{
}


void TestMTree::run()
{
    DataModelRepository::getInstance();
    MTree *tr = (MTree*) GuiCreateAction::getInstance()->create("MTree");

    int id_kl = tr->getID();

    Transactions::getCurrentTransaction()->commit();

    TestRunner::restartDatabase();

    PObject *o = Database::getInstance()->loadObjectById(id_kl);
    tr = dynamic_cast<MTree*>(o);
    if(!tr){fail("MTree nicht gespeichert");return;}

    publish("Erfolg");
}
