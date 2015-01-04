#include "modelesen.h"
#include "gui/base/guiconfig.h"
#include "gui/guirepository.h"
#include "gui/forms/pdfviewer.h"
#include "orm/repository/repository.h"
#include "orm/repository/repositoryproperty.h"
#include "gui/actions/guicreateaction.h"
#include "orm/transactions/transactions.h"
#include "modelesenmapper.h"

#include <QPixmap>
#include <QVBoxLayout>


ModeLesen* ModeLesen::instance=0;

ModeLesen::ModeLesen()
    : GuiMode("Lesen")
{
    setMapper(ModeLesenmapper::getInstance());
    list_texte=0;
    activeText=0;
    toolBar = 0;

    QPixmap pm = GuiConfig::getInstance()->getIcon("ModeLesen");
    if(pm.isNull()){
        GuiConfig::getInstance()->selectIcon("ModeLesen");
        pm = GuiConfig::getInstance()->getIcon("ModeLesen");
    }
    setIcon(pm);

    RepositoryEntry *re = Repository::getInstance()->getRepositoryEntry("lektuere");
    RepositoryProperty *colProp = re->getProperty("Notizen");
    re = Repository::getInstance()->getRepositoryEntry("lektuerenotiz");
    RepositoryProperty *dispProp = re->getProperty("Body");

    GuiRepository *guirep=GuiRepository::getInstance();
    QStackedWidget *sw=guirep->getCentralWidget();

    splitter = new QSplitter(Qt::Horizontal,sw);

    browser = new TextPropertyBrowser(activeText,colProp,dispProp,sw);
    //browser->setFitToView(true);
    RepositoryProperty *rp=Repository::getInstance()->getRepositoryEntry("ModeLesen")->getProperty("Texte");
    viewer = new TextViewer(rp,0,sw);
    lkViewer = new LernkartensatzViewer(0,0,LernkarteViewer::Stacked);

    QWidget *notew = new QWidget(splitter);
    QVBoxLayout *l= new QVBoxLayout(notew);
    l->addWidget(browser);
    l->addWidget(lkViewer);

    browser->hide();
    lkViewer->hide();
    /*
    stack=new QStackedWidget(splitter);
    blankWidget = new QWidget(stack);
    stack->addWidget(browser);
    stack->addWidget(lkViewer);
    stack->addWidget(blankWidget);
    stack->setCurrentWidget(blankWidget);
    */
    //AdaptingSplitter *splitter2=new AdaptingSplitter(browser,viewer,splitter);
    splitter->addWidget(viewer);
    //splitter->addWidget(stack);
    splitter->addWidget(notew);


}

ModeLesen* ModeLesen::getInstance()
{
    if(instance==0)
    {
        instance = dynamic_cast<ModeLesen*>(ModeLesenmapper::getInstance()->getSingletonInstance());
        /*
        list<PObject*> *li=ModeLesenmapper::getInstance()->find_gen();
        if(li && li->size()>0){
            instance=dynamic_cast<ModeLesen*>((*(--(li->end()))));
        } else {
            instance=ModeLesenmapper::getInstance()->create();
        }
        */
    }
    return instance;
}

void ModeLesen::setupMode()
{
    GuiRepository *guirep=GuiRepository::getInstance();
    QStackedWidget *sw=guirep->getCentralWidget();

    guirep->setActiveMode(this);

    sw->addWidget(splitter);
    viewer->setParentObject(this);
    viewer->load();
    sw->setCurrentWidget(splitter);

    //guirep->addTool(browser,"Notizen","Notizen");
    if(!toolBar){
        toolBar = new QToolBar(guirep->getMainFrame());
        QPixmap pm = GuiConfig::getInstance()->getIcon("Notizeditor");
        toolBar->addAction(pm,"",this,SLOT(showNotizeditor()));
        pm = GuiConfig::getInstance()->getIcon("Lernkarten");
        toolBar->addAction(pm,"",this,SLOT(showLernkarten()));

        guirep->getMainFrame()->addToolBar(Qt::RightToolBarArea,toolBar);
    } else {
        toolBar->show();
    }
}

void ModeLesen::tearDownMode()
{
    toolBar->hide();
}

void ModeLesen::setActivePage(int i)
{
    viewer->setPage(i);
}

void ModeLesen::showNotizeditor()
{
    if(browser->isVisible()){
        browser->hide();
    } else {
        browser->show();
    }
    /*
    if(stack->currentWidget()!=browser)
    {
        stack->setCurrentWidget(browser);
    } else {
        stack->setCurrentWidget(blankWidget);
    }
    */
}

void ModeLesen::showLernkarten()
{
    if(lkViewer->isVisible()){
        lkViewer->hide();
    } else {
        lkViewer->show();
    }

    /*
    if(stack->currentWidget()!=lkViewer){
        stack->setCurrentWidget(lkViewer);
    } else {
        stack->setCurrentWidget(blankWidget);
    }
    */

}

void ModeLesen::activateObject(PObject *o)
{

}

void ModeLesen::showForm(QWidget *w)
{

}

list<lektuere*>* ModeLesen::getTexte()
{
    if(list_texte==0)
    {
        list_texte=ModeLesenmapper::getInstance()->findTexte(getID());
    }
    return list_texte;
}

void ModeLesen::addToTexte(lektuere *l)
{
    getTexte()->push_back(l);
}

void ModeLesen::deleteFromTexte(lektuere *l)
{
    getTexte()->remove(l);
}

void ModeLesen::setActiveText(lektuere *l)
{
    activeText = l;
    browser->setParentObject(activeText);
    lernkartensatz *lks = l->getLernkartensatz();
    if(lks==0){
        Transaction *t=Transactions::getCurrentTransaction();
        lks=(lernkartensatz*)GuiCreateAction::getInstance()->create("lernkartensatz");
        l->setLernkartensatz(lks);
        t->add(l);
    }
    lkViewer->setLernkartensatz(lks);
}

AdaptingSplitter::AdaptingSplitter(QWidget *w1, QWidget *w2, QWidget *parent)
    : QSplitter(Qt::Vertical,parent), widget1(w1), widget2(w2)
{
    addWidget(w1);
    addWidget(w2);
}

void AdaptingSplitter::resizeEvent(QResizeEvent *e)
{
    QSize totalSize=e->size();
    QSize w2Size = widget2->sizeHint();
    QList<int> sizeList = QList<int>();
    sizeList << totalSize.height()-w2Size.height() << w2Size.height();
    setSizes(sizeList);
}
