#include "modeplanung.h"
#include "gui/base/guiconfig.h"
#include "gui/base/doublepane.h"
#include "gui/guirepository.h"
#include "services/skalender.h"
#include "datamodel/stundenplaneintrag.h"
#include "gui/forms/pobjecteditor3.h"
#include "orm/repository/repository.h"

#include <QIcon>
#include <QLabel>

ModePlanung* ModePlanung::instance=0;


ModePlanung::ModePlanung() :
    GuiMode("Planung")
{
    QPixmap pm = GuiConfig::getInstance()->getIcon("ModePlanung");
    if(pm.isNull()){
        GuiConfig::getInstance()->selectIcon("ModePlanung");
        pm = GuiConfig::getInstance()->getIcon("ModePlanung");
    }
    setIcon(pm);

    sePropertyList = new list<RepositoryProperty*>();
    RepositoryEntry *re=Repository::getInstance()->getRepositoryEntry("stundenplaneintrag");
    sePropertyList->push_back(re->getProperty("Verlauf"));
    sePropertyList->push_back(re->getProperty("Notizen"));
    sePropertyList->push_back(re->getProperty("Materialien"));

    dp=0;
    spl=0;
    toolBar=0;
}


ModePlanung* ModePlanung::getInstance()
{
    if(instance==0)
    {
        instance=new ModePlanung();
    }
    return instance;
}

void ModePlanung::showForm(QWidget *w)
{
    if(dp){
        dp->showFormAtBottom(w);
    }
}

void ModePlanung::setupMode()
{
    GuiRepository *rep=GuiRepository::getInstance();
    QStackedWidget *sw=rep->getCentralWidget();

    //rep->setActiveMode(this);
    if(spl==0){
        spl = new QSplitter(Qt::Horizontal,sw);

        /*
        dp = new DoublePane();
        dp->showFormAtTop(rep->getFormForObject(SKalender::getInstance(),dp));
        dp->setStretchFactor(1,10);
        spl->addWidget(dp);
        */
        QWidget *w = rep->getFormForObject(SKalender::getInstance(),dp);
        spl->addWidget(w);

        stack = new QStackedWidget(sw);

        dp = new DoublePane();
        stack->addWidget(dp);

        RepositoryProperty *rp=Repository::getInstance()->getRepositoryEntry("stundenplantemplateeintrag")
                                        ->getProperty("Reihen");
        browser = new ReiheBrowser(rp,0,sw);
        stack->addWidget(browser);
        browser->hide();

        spl->addWidget(stack);


        sw->addWidget(spl);
    }
    sw->setCurrentWidget(spl);
    if(!toolBar){
        toolBar = new QToolBar(rep->getMainFrame());
        QPixmap pm = GuiConfig::getInstance()->getIcon("ReihePlaner");
        toolBar->addAction(pm," ",this,SLOT(showReihePlaner()));

        /*
        pm = GuiConfig::getInstance()->getIcon("Lernkarten");
        toolBar->addAction(pm,"",this,SLOT(showLernkarten()));
        */

        rep->getMainFrame()->addToolBar(Qt::RightToolBarArea,toolBar);
    } else {
        toolBar->show();
    }

}

void ModePlanung::activateObject(PObject *o)
{
    if(stundenplaneintrag *se = dynamic_cast<stundenplaneintrag*>(o))
    {
        if(stundenplantemplateeintrag *ste=se->getTemplate()){
            browser->setParentObject(ste);
        }


        if(klasse *kl = se->getKlasse()){
            //QWidget *editor=GuiRepository::getInstance()->getFormForObject(se,dp);
            QWidget *editor=new PObjectEditor3(se,dp,sePropertyList);
            dp->showFormAtTop(editor);

            sitzplan *sp = kl->getSitzplan();
            if(sp){
                SitzplanMapView *spmv = GuiRepository::getInstance()->getFormForSitzplan(sp);
                spmv->setStundenplaneintrag(se);
                dp->showFormAtBottom(spmv);

            }

        }
    }
}

void ModePlanung::showReihePlaner()
{
    if(stack->currentWidget()==browser){
        stack->setCurrentWidget(dp);
    } else {
        stack->setCurrentWidget(browser);
    }

}
void ModePlanung::tearDownMode()
{
    toolBar->hide();
}
