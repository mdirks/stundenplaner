#include "modehome.h"
#include "ui_modehome.h"

#include "gui/guirepository.h"
#include "datamodel/tweetmapper.h"
#include "orm/repository/repository.h"
#include "gui/forms/tweeteditor.h"

ModeHome::ModeHome() :
    GuiMode("Home"),
    ui(new Ui::ModeHome),
    displayWidget(0)
{

}

ModeHome::~ModeHome()
{
    delete ui;
}

void ModeHome::setupMode()
{
    GuiRepository *guirep=GuiRepository::getInstance();
    //guirep->setActiveMode(this);
    QStackedWidget *cw=guirep->getCentralWidget();

    if(!displayWidget){
        displayWidget=new QWidget(cw);
        ui->setupUi(displayWidget);
        cw->addWidget(displayWidget);
        list<PObject*> *listRecent=GuiRepository::getInstance()->getGlobalCollection("Recent");
        ui->list1->setObjectListProvider(new PoLListProvider(listRecent));


        list<RepositoryProperty*> *listDisplayProp = new list<RepositoryProperty*>();
        ui->list2->setObjectListProvider(new MapperListProvider(tweetmapper::getInstance()));
        listDisplayProp->push_back(Repository::getInstance()->getRepositoryEntry("tweet")->getProperty("Name"));
        listDisplayProp->push_back(Repository::getInstance()->getRepositoryEntry("tweet")->getProperty("Body"));
        ui->list2->setDisplayProperties(listDisplayProp);

        /*
        RepositoryProperty *rpBody=Repository::getInstance()->getRepositoryEntry("tweet")->getProperty("Body");
        ui->list2->setObjectListProvider(new MapperListProvider(tweetmapper::getInstance()));
        ui->list2->setDisplayProperty(rpBody);
        */
        //TweetEditor *te = new TweetEditor(m,sw);
        //te->setDisplayProperty(rpBody);
        //ui->
    }


    setModeWidget(displayWidget);
}


void ModeHome::tearDownMode()
{

}
void ModeHome::activateObject(PObject *o)
{
    GuiMode::activateObject(o);
}

void ModeHome::showForm(QWidget *w)
{
    GuiMode::showForm(w);
}

QList<QAction*>* ModeHome::getModeActions()
{
    return GuiMode::getModeActions();
}
