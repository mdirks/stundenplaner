#include "testlektuere.h"
#include "datamodel/datamodelrepository.h"
#include "datamodel/lektuere.h"
#include "gui/actions/guicreateaction.h"
#include "orm/transactions/transactions.h"
#include "orm/persistence/database.h"

TestLektuere::TestLektuere(): TestCase()
{
}


void TestLektuere::run()
{
    DataModelRepository::getInstance();
    lektuere *lk = (lektuere*) GuiCreateAction::getInstance()->create("lektuere");
    string fn_vorher=lk->getFileName();

    lektuerenotiz *lkn = (lektuerenotiz*) GuiCreateAction::getInstance()->create("lektuerenotiz");
    lk->addToNotizen(lkn);

    int id_lk = lk->getID();
    int id_lkn = lkn->getID();

    Transactions::getCurrentTransaction()->commit();
    Database::getInstance()->close();

    PObject *o = Database::getInstance()->loadObjectById(id_lk);
    lk = dynamic_cast<lektuere*>(o);
    if(!lk){fail("Klasse nicht gespeichert");return;}

    if(fn_vorher != lk->getFileName()){fail("Filename nicht gespeichert"); return;}

    list<lektuerenotiz*> *ln = lk->getNotizen();
    if(ln->size()==0){fail("Notiz nicht gespeichert"); return;}
    if(ln->front()->getID() != id_lkn){fail("Notiz falsch gespeichert");return;}
    publish("Erfolg");
}
