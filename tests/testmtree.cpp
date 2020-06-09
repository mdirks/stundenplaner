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

    int id_tr = tr->getID();

    Transactions::getCurrentTransaction()->commit();

    TestRunner::restartDatabase();

    PObject *o = Database::getInstance()->loadObjectById(id_tr);
    tr = dynamic_cast<MTree*>(o);
    if(!tr){fail("MTree nicht gespeichert");return;}

    Transactions::getCurrentTransaction()->add(tr);

    MTree *ptr = (MTree*) GuiCreateAction::getInstance()->create("MTree");
    int id_ptr=ptr->getID();
    tr->setParent(ptr);

    MTree *ctr = (MTree*) GuiCreateAction::getInstance()->create("MTree");
    int id_ctr=ctr->getID();
    tr->addToChildren(ctr);

    stunde *st = (stunde*) GuiCreateAction::getInstance()->create("stunde");
    int id_st=st->getID();
    tr->setContents(st);
    Transactions::getCurrentTransaction()->commit();

    TestRunner::restartDatabase();


    o = Database::getInstance()->loadObjectById(id_tr);
    tr = dynamic_cast<MTree*>(o);
    if(!(tr->getContents() && tr->getContents()->getID() == id_st))
    {
        fail("Contents-Object could not be recovered");
    }
    if(!(tr->getParent() && tr->getParent()->getID() == id_ptr))
    {
        fail("Parent-Object could not be recovered");
    }
    if(!(tr->getChildren()&& tr->getChildren()->size() > 0 && tr->getChildren()->front()->getID()==id_ctr))
    {
        fail("Parent-Object could not be recovered");
    }
    publish("Erfolg");
}
