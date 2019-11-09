#include "modelesen.h"
#include "gui/base/guiconfig.h"
#include "gui/guirepository.h"
#include "gui/forms/pdfviewer.h"
#include "orm/repository/repository.h"
#include "orm/repository/repositoryproperty.h"
#include "gui/actions/guicreateaction.h"
#include "gui/forms/pobjectlistprovider.h"
#include "orm/transactions/transactions.h"
#include "datamodel/lektuere.h"
#include "modelesenmapper.h"

#include <QPixmap>
#include <QVBoxLayout>
#include <QList>


ModeLesen* ModeLesen::instance=0;

ModeLesen::ModeLesen()
    : GuiMode("Lesen")
{
    setMapper(ModeLesenmapper::getInstance());
    list_texte=0;
    activeText=0;
    toolBar = 0;
    splitter = 0;

    QPixmap pm = GuiConfig::getInstance()->getIcon("ModeLesen");
    if(pm.isNull()){
        GuiConfig::getInstance()->selectIcon("ModeLesen");
        pm = GuiConfig::getInstance()->getIcon("ModeLesen");
    }
    setIcon(pm);

    //doCommonSetup();



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

void ModeLesen::doCommonSetup()
{
    GuiRepository *guirep=GuiRepository::getInstance();
    QStackedWidget *sw=guirep->getCentralWidget();

     if(!splitter){
        RepositoryEntry *re = Repository::getInstance()->getRepositoryEntry("lektuere");
        RepositoryProperty *colProp = re->getProperty("Notizen");
        re = Repository::getInstance()->getRepositoryEntry("lektuerenotiz");
        RepositoryProperty *dispProp = re->getProperty("Body");

        splitter = new QSplitter(Qt::Horizontal,sw);

        viewer = new TextViewer(splitter);

        browser = new TextPropertyBrowser(activeText,colProp,dispProp,sw);
        lkDisplay = new PObjectDisplay(sw,0,1,0);
        lkDisplay->setPrototype(new LernkarteDisplayItem());
        lkViewer = new LernkartensatzViewer(0,0,LernkarteViewer::Stacked);


        QWidget *notew = new QWidget(splitter);
        QVBoxLayout *l= new QVBoxLayout(notew);
        l->setContentsMargins(0,0,0,0);
        l->addWidget(browser);
        l->addWidget(lkDisplay);
        l->addWidget(lkViewer);



        splitter->addWidget(viewer);
        splitter->addWidget(notew);
        QList<int> sizes;
        sizes << 600 << 500 << 10;
        splitter->setSizes(sizes);
        //sw->addWidget(splitter);

        //browser->hide();
        //lkViewer->hide();

        setModeWidget(splitter);
    }

    //sw->setCurrentWidget(splitter);


        QPixmap pm = GuiConfig::getInstance()->getIcon("Notizeditor");
        modeToolBar->addAction(pm,"",this,SLOT(showNotizeditor()));
        pm = GuiConfig::getInstance()->getIcon("Lernkarten");
        modeToolBar->addAction(pm,"",this,SLOT(showLernkarten()));
        pm = GuiConfig::getInstance()->getIcon("LernkartenDisplay");
        modeToolBar->addAction(pm,"",this,SLOT(showLernkartenDisplay()));




    viewer->setResizePolicy(true);
}

void ModeLesen::setupMode()
{
    doCommonSetup();


    GuiRepository *guirep=GuiRepository::getInstance();
    QStackedWidget *sw=guirep->getCentralWidget();



    PObjectListProvider *prov = new MapperListProvider("lektuere");
    viewer->setProvider(prov);

    browser->setParentObject(activeText);


    viewer->selectionChanged(0);
    //viewer->setResizePolicy(true);
    //guirep->setActiveMode(this);
}

void ModeLesen::load()
{
    PObjectListProvider *prov = new MapperListProvider("lektuere");
    viewer->setProvider(prov);
    //load initial item if present
    viewer->selectionChanged(0);

}

void ModeLesen::close()
{

    /*
    GuiRepository *guirep=GuiRepository::getInstance();
    QStackedWidget *sw=guirep->getCentralWidget();

    if(splitter){
        sw->removeWidget(splitter);
        delete(splitter);
        splitter=0;
    }
    if(toolBar){
        toolBar->deleteLater();
        toolBar=0;
    }
    */

    list_texte=0;
    activeText=0;
    viewer->setProvider(0);
    browser->setParentObject(0);
    //toolBar = 0;
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

void ModeLesen::showLernkartenDisplay()
{
    if(lkDisplay->isVisible()){
        lkDisplay->hide();
    } else {
        lkDisplay->show();
    }
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
    lkDisplay->setObjectList((list<PObject*>*) lks->getLernkarten());
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
