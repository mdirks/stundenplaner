#include "modeplanung.h"
#include "gui/base/guiconfig.h"
#include "gui/base/doublepane.h"
#include "gui/guirepository.h"
#include "services/skalender.h"
#include "datamodel/stundenplaneintrag.h"
#include "gui/forms/pobjecteditor3.h"
#include "gui/forms/kalenderview.h"
#include "kalenderviewcontroler.h"
#include "orm/repository/repository.h"
#include "sitzplanmapviewcontroler.h"

#include <QIcon>
#include <QLabel>
#include <QApplication>

ModePlanung* ModePlanung::instance=0;


ModePlanung::ModePlanung() :
    GuiMode("Planung"),
    ui(new Ui::ModePlanung)
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
    //spl=0;
    displayWidget=0;
    toolBar=0;
    spmvd=0;
    kw=0;
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
    if(formArea){
        formArea->showForm(w);
    }
}

void ModePlanung::setupMode()
{
    GuiRepository *rep=GuiRepository::getInstance();
    QStackedWidget *sw=rep->getCentralWidget();

    //rep->setActiveMode(this);
    if(displayWidget==0){
        displayWidget=new QWidget(sw);
        ui->setupUi(displayWidget);
        //spl = new QSplitter(Qt::Horizontal,sw);

        /*
        */
        kw=ui->kw;

        new KalenderViewControler(kw);
        kw->setMap(SKalender::getInstance()->getCurrentWeek());
        kw->setToolTip(QString("Wochenuebersicht"));

        stack=ui->stack;

        dp = new DoublePane();
        dp->setStretchFactor(0,10);
        stack->addWidget(dp);


        RepositoryProperty *rp=Repository::getInstance()->getRepositoryEntry("klasse")
                                        ->getProperty("Reihen");
        browser = new ReiheBrowser(rp,0,sw);
        stack->addWidget(browser);
        browser->hide();

        leistungEditor = new TeilleistungEditorDialog(0);
        stack->addWidget(leistungEditor);
        leistungEditor->hide();

        spmvd = new SitzplanMapViewDialog(0);
        new SitzplanMapViewControler(spmvd->getMapView());

        stack->addWidget(spmvd);
        spmvd->hide();

        formArea = new FormArea();
        stack->addWidget(formArea);
        formArea->hide();

        //spl->addWidget(stack);


        sw->addWidget(displayWidget);
        stack->setCurrentWidget(dp);
    }
    sw->setCurrentWidget(displayWidget);


    if(!toolBar){
        toolBar = new QToolBar(rep->getMainFrame());
        QPixmap pm = GuiConfig::getInstance()->getIcon("ReihePlaner");
        toolBar->addAction(pm," ",this,SLOT(showReihePlaner()));

        pm = GuiConfig::getInstance()->getIcon("TeilleistungEditor");
        toolBar->addAction(pm," ",this,SLOT(showLeistungen()));

        pm = GuiConfig::getInstance()->getIcon("Sitzplan");
        toolBar->addAction(pm," ",this,SLOT(showSitzplan()));

        pm = GuiConfig::getInstance()->getIcon("Forms");
        toolBar->addAction(pm," ",this,SLOT(showFormArea()));
        /*
        pm = GuiConfig::getInstance()->getIcon("Lernkarten");
        toolBar->addAction(pm,"",this,SLOT(showLernkarten()));
        */

        rep->getMainFrame()->addToolBar(Qt::RightToolBarArea,toolBar);
    } else {
        toolBar->show();
    }

    kw->readStundenplan();

    //SpReader *r = new SpReader(kw);
    //r->start();
}

void ModePlanung::activateObject(PObject *o)
{
    if(stundenplaneintrag *se = dynamic_cast<stundenplaneintrag*>(o))
    {
        if(klasse *kl = se->getKlasse()){
            QWidget *editor=new PObjectEditor3(se,dp,sePropertyList);
            dp->showFormAtTop(editor);
            QApplication::processEvents();


            spmvd->setParentObject(se);
            QApplication::processEvents();

            leistungEditor->setParentObject(kl);
            QApplication::processEvents();

            browser->setParentObject(kl);
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

void ModePlanung::showLeistungen()
{
    if(stack->currentWidget()==leistungEditor){
        stack->setCurrentWidget(dp);
    } else {
        stack->setCurrentWidget(leistungEditor);
    }
}

void ModePlanung::showSitzplan()
{
    if(stack->currentWidget()==spmvd){
        stack->setCurrentWidget(dp);
    } else {
        stack->setCurrentWidget(spmvd);
    }
}

void ModePlanung::showFormArea()
{
    if(stack->currentWidget()==formArea){
        stack->setCurrentWidget(dp);
    } else {
        stack->setCurrentWidget(formArea);
    }
}

void ModePlanung::tearDownMode()
{
    toolBar->hide();
}
