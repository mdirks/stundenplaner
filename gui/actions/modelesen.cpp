#include "modelesen.h"
#include "gui/base/guiconfig.h"
#include "gui/guirepository.h"
#include "gui/forms/pdfviewer.h"
#include "orm/repository/repository.h"
#include "orm/repository/repositoryproperty.h"
#include "gui/actions/guicreateaction.h"
#include "gui/forms/pobjectlistprovider.h"
#include "orm/transactions/transactions.h"
#include "orm/mapping/mappingcontroler.h"
#include "datamodel/lektuere.h"
#include "datamodel/tweetmapper.h"
//#include "modelesenmapper.h"
#include "services/docstore/docstore.h"

#include <QPixmap>
#include <QVBoxLayout>
#include <QList>


//ModeLesen* ModeLesen::instance=0;

ModeLesen::ModeLesen()
    : GuiMode("Lesen")
{
    activeText=0;
    toolBar = 0;
    splitter = 0;

    QPixmap pm = GuiConfig::getInstance()->getIcon("ModeLesen");

    setIcon(pm);
    setToolTip("Lesen");
}



void ModeLesen::doCommonSetup()
{
    qWarning() << "ModeLesen::doCommonSetup()";
    GuiRepository *guirep=GuiRepository::getInstance();
    QStackedWidget *sw=guirep->getCentralWidget();

     if(!splitter){
        RepositoryEntry *re = Repository::getInstance()->getRepositoryEntry("lektuere");
        RepositoryProperty *colProp = re->getProperty("Notizen");
        re = Repository::getInstance()->getRepositoryEntry("lektuerenotiz");
        RepositoryProperty *dispProp = re->getProperty("Body");

        splitter = new QSplitter(Qt::Horizontal,sw);

        viewer = new TextViewer(splitter);
        viewer->setResizePolicy(true);
        viewer->collectionDisplay()->addDropHandler_items(new LektuereDropHandler());

        //tocWidget = new QWidget(sw);
        //tocWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        tocSplitter = new QSplitter(Qt::Vertical,splitter);

        RepositoryProperty *rp=Repository::getInstance()->getRepositoryEntry("lektuere")->getProperty("Toc");
        tocView = new PObjectIconView(rp,0,tocSplitter);
        tocView->setActivationHandler(new BookmarkActivationHandler(viewer));
        rp=Repository::getInstance()->getRepositoryEntry("lektuere")->getProperty("Bookmarks");
        bmView = new PObjectIconView(rp,0,tocSplitter);
        list<RepositoryProperty*> *listDisplayProp = new list<RepositoryProperty*>();
        listDisplayProp->push_back(Repository::getInstance()->getRepositoryEntry("bookmark")->getProperty("Name"));
        listDisplayProp->push_back(Repository::getInstance()->getRepositoryEntry("bookmark")->getProperty("Beschreibung"));
        bmView->setDisplayProperties(listDisplayProp);
        bmView->setActivationHandler(new BookmarkActivationHandler(viewer));


        browser = new TextPropertyBrowser(activeText,colProp,dispProp,sw);

        re = Repository::getInstance()->getRepositoryEntry("lernkartensatz");
        RepositoryProperty *kartenProp = re->getProperty("Lernkarten");
        lkDisplay = new PObjectDisplay(kartenProp,0,sw,0,1,true);
        lkDisplay->setPrototype(new LernkarteDisplayItem());

        re = Repository::getInstance()->getRepositoryEntry("materialsatz");
        RepositoryProperty *materialProp = re->getProperty("Materialien");
        mDisplay = new PObjectDisplay(materialProp,0,sw,0,1,true);
        mDisplay->setPrototype(new MaterialDisplayItem());

        lkViewer = new LernkartensatzViewer(0,0,LernkarteViewer::Stacked);

        tweetEdit = new PObjectIconView(sw);
        tweetEdit->setObjectListProvider(new MapperListProvider(tweetmapper::getInstance()));
        listDisplayProp = new list<RepositoryProperty*>();
        listDisplayProp->push_back(Repository::getInstance()->getRepositoryEntry("tweet")->getProperty("Name"));
        listDisplayProp->push_back(Repository::getInstance()->getRepositoryEntry("tweet")->getProperty("Body"));
        tweetEdit->setDisplayProperties(listDisplayProp);


        scndViewer = new TextViewer(sw);
        scndViewer->setResizePolicy(true);

        QWidget *notew = new QWidget(splitter);
        QVBoxLayout *l= new QVBoxLayout(notew);
        l->setContentsMargins(0,0,0,0);
        l->addWidget(scndViewer);
        l->addWidget(tweetEdit);
        l->addWidget(tocSplitter);
        l->addWidget(browser);
        l->addWidget(lkDisplay);
        l->addWidget(mDisplay);
        l->addWidget(lkViewer);



        splitter->addWidget(viewer);
        splitter->addWidget(notew);
        QList<int> sizes;
        sizes << 600 << 500 << 10;
        splitter->setSizes(sizes);
        //sw->addWidget(splitter);

        scndViewer->hide();
        tweetEdit->hide();
        tocSplitter->hide();
        browser->hide();
        lkDisplay->hide();
        mDisplay->hide();
        lkViewer->hide();


    }
    setModeWidget(splitter);

    QAction *a;
    QPixmap pm = GuiConfig::getInstance()->getIcon("Lektuere");
    a=modeToolBar->addAction(pm,"",this,SLOT(showScndViewer()));
    a->setToolTip("Lektuere");
    pm = GuiConfig::getInstance()->getIcon("Tweets");
    a=modeToolBar->addAction(pm,"",this,SLOT(showTweets()));
    a->setToolTip("Tweets");
    pm = GuiConfig::getInstance()->getIcon("Bookmarks");
    a=modeToolBar->addAction(pm,"",this,SLOT(showBookmarks()));
    a->setToolTip("Bookmarks");
    pm = GuiConfig::getInstance()->getIcon("Notizeditor");
    a=modeToolBar->addAction(pm,"",this,SLOT(showNotizeditor()));
    a->setToolTip("Notizeditor");
    pm = GuiConfig::getInstance()->getIcon("Lernkarten");
    a=modeToolBar->addAction(pm,"",this,SLOT(showLernkarten()));
    a->setToolTip("Lernkarten");
    pm = GuiConfig::getInstance()->getIcon("LernkartenDisplay");
    a=modeToolBar->addAction(pm,"",this,SLOT(showLernkartenDisplay()));
    a->setToolTip("LK-Display");
    pm = GuiConfig::getInstance()->getIcon("MaterialDisplay");
    a=modeToolBar->addAction(pm,"",this,SLOT(showMaterialDisplay()));
    a->setToolTip("M-Display");


}

void ModeLesen::setupMode()
{
    doCommonSetup();


    GuiRepository *guirep=GuiRepository::getInstance();
    QStackedWidget *sw=guirep->getCentralWidget();


    //browser->setParentObject(activeText);

    connect(viewer, SIGNAL(textChanged(lektuere*)), this, SLOT(setActiveText(lektuere*)));

    viewer->addSelectionAction(new TakeNoteAction(this));
    viewer->addSelectionAction(new TakeCopyAction(this));
    viewer->addSelectionAction(new AddTocEntryAction(this));
    viewer->addSelectionAction(new AddBookmarkAction(this));
    viewer->addContextMenuAction(PdfView::Zoom);
    viewer->addContextMenuAction(PdfView::Bookmarks);
    viewer->addContextMenuAction(PdfView::MouseToolSelection);
    viewer->addContextMenuAction(PdfView::MouseToolBrowse);
    viewer->addKeyAction(Qt::Key_Plus, PdfView::ZoomIn);
}

void ModeLesen::load()
{
    qDebug() << "ModeLesen::load() -- do noting";

}

void ModeLesen::close()
{
    activeText=0;
    splitter=0;
    GuiMode::close();
}

void ModeLesen::tearDownMode()
{
    toolBar->hide();
}

void ModeLesen::setActivePage(int i)
{
    viewer->setPage(i);
}

void ModeLesen::showBookmarks()
{
    if(tocSplitter->isVisible()){
        tocSplitter->hide();
    } else {
        tocSplitter->show();
    }
}

void ModeLesen::showScndViewer()
{
    if(scndViewer->isVisible()){
        scndViewer->hide();
    } else {
        scndViewer->show();
    }
}

void ModeLesen::showTweets()
{
    if(tweetEdit->isVisible()){
        tweetEdit->hide();
    } else {
        tweetEdit->show();
    }
}


void ModeLesen::showNotizeditor()
{
    if(browser->isVisible()){
        browser->hide();
    } else {
        browser->show();
    }
}

void ModeLesen::showLernkarten()
{
    if(lkViewer->isVisible()){
        lkViewer->hide();
    } else {
        lkViewer->show();
    }
}

void ModeLesen::showLernkartenDisplay()
{
    if(lkDisplay->isVisible()){
        lkDisplay->hide();
    } else {
        lkDisplay->show();
    }
}

void ModeLesen::showMaterialDisplay()
{
    if(mDisplay->isVisible()){
        mDisplay->hide();
    } else {
        mDisplay->show();
    }
}


void ModeLesen::activateObject(PObject *o)
{

}

void ModeLesen::showForm(QWidget *w)
{

}

/*
list<lektuere*>* ModeLesen::getTexte()
{
    if(list_texte==0)
    {
        list_texte=ModeLesenmapper::getInstance()->findTexte(getID());
    }
    return list_texte;
}
*/

/*
void ModeLesen::addToTexte(lektuere *l)
{
    getTexte()->push_back(l);
}

void ModeLesen::deleteFromTexte(lektuere *l)
{
    getTexte()->remove(l);
}
*/


lektuere* ModeLesen::getActiveText()
{
    return activeText;
}



void ModeLesen::setActiveText(lektuere *l)
{
    activeText = l;
    bmView->setParentObject(activeText);
    tocView->setParentObject(activeText);
    browser->setParentObject(activeText);
    lernkartensatz *lks = l->getLernkartensatz();
    if(lks==0){
        Transaction *t=Transactions::getCurrentTransaction();
        lks=(lernkartensatz*)GuiCreateAction::getInstance()->create("lernkartensatz");
        l->setLernkartensatz(lks);
        t->add(l);
    }
    lkViewer->setLernkartensatz(lks);

    materialsatz *ms = l->getKopien();
    if(ms==0){
        Transaction *t=Transactions::getCurrentTransaction();
        ms=(materialsatz*)GuiCreateAction::getInstance()->create("materialsatz");
        l->setKopien(ms);
        t->add(l);
    }
    //lkDisplay->setObjectList((list<PObject*>*) lks->getLernkarten());
    lkDisplay->setParentObject(l->getLernkartensatz());
    mDisplay->setParentObject(l->getKopien());
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

void ModeLesen::takeNote(QString note)
{
    lektuerenotiz* ln = dynamic_cast<lektuerenotiz*>(browser->newObject());
    if(ln){
        int i=viewer->getPage();
        ln->setSeite(i);
        QString n(activeText->getName().c_str());
        n.append("-").append(i);
        ln->setName(n.toStdString());
        ln->setBody(note.toStdString());
        browser->setActiveObject(ln);
    } else {
        qDebug() << "ModeLesen::takeNote() : failed to create Lektuerenotiz";
    }
}

void ModeLesen::addBookmark(double pos)
{

}

void ModeLesen::takeCopy(QImage im)
{
        int i=viewer->getPage();
        QString n(activeText->getName().c_str());
        n=n.append("-").append(QString("%1").arg(i)).append(".png");

        QFile file(n);
        if(file.open(QIODevice::WriteOnly)){
            QString fileName = file.fileName();
            if(im.save(fileName)){
                material *m= dynamic_cast<material*>(GuiCreateAction::getInstance()->create("material"));
                if(m){
                    m->setName(n.toStdString());
                    m->setTitle(n.toStdString());
                    m->setFileName(fileName.toStdString());
                    DocStore::getInstance()->addDocument(m);
                    materialsatz *ms = activeText->getKopien();
                    Transaction *t=Transactions::getCurrentTransaction();
                    if(ms==0){
                        ms=(materialsatz*)GuiCreateAction::getInstance()->create("materialsatz");
                        activeText->setKopien(ms);
                        t->add(activeText);
                    }
                    t->add(ms);
                    ms->addToMaterialien(m);
                    mDisplay->setParentObject(activeText->getKopien()); //triggers update

                }

            }
        }
}


TakeNoteAction::TakeNoteAction(ModeLesen *parent)
    : PdfViewSelectionAction(QString("TakeNote"), parent)
{
    connect(this,SIGNAL(triggered()),this,SLOT(createLektuereNotiz()),Qt::UniqueConnection);
    mode=parent;
}

void TakeNoteAction::createLektuereNotiz()
{
    QString t= getDataText();
    mode->takeNote(t);
}

void TakeNoteAction::setDataText(QString t)
{
    if(t.isEmpty()) setEnabled(false);
    PdfViewSelectionAction::setDataText(t);
}

TakeCopyAction::TakeCopyAction(ModeLesen *parent)
    : PdfViewSelectionAction(QString("TakeCopy"), parent)
{
    connect(this,SIGNAL(triggered()),this,SLOT(createLektuereCopy()),Qt::UniqueConnection);
    mode=parent;
}

void TakeCopyAction::createLektuereCopy()
{
    QImage i= getDataImage();
    mode->takeCopy(i);
}

void TakeCopyAction::setDataImage(QImage i)
{
    if(i.isNull()) setEnabled(false);
    PdfViewSelectionAction::setDataImage(i);
}

AddBookmarkAction::AddBookmarkAction(ModeLesen *parent)
    : PdfViewSelectionAction(QString("Bookmark"), parent)
{
    connect(this,SIGNAL(triggered()),this,SLOT(addBookmark()),Qt::UniqueConnection);
    mode=parent;
}


void AddBookmarkAction::addBookmark()
{
    bookmark *bm = (bookmark*) GuiCreateAction::getInstance()->create("bookmark");
    lektuere *l = mode->getActiveText();
    if(l){
        bm->setName(std::to_string(getPosition()));
        bm->setZiel(mode->getActiveText());
        bm->setPosition(getPosition());
        Transactions::getCurrentTransaction()->add(l);
        l->addToBookmarks(bm);
    }
    mode->bmView->reload();

}

AddTocEntryAction::AddTocEntryAction(ModeLesen *parent)
    : PdfViewSelectionAction(QString("Toc Eintrag"), parent)
{
    connect(this,SIGNAL(triggered()),this,SLOT(addTocEntry()),Qt::UniqueConnection);
    mode=parent;
}

void AddTocEntryAction::addTocEntry()
{
    bookmark *bm = (bookmark*) GuiCreateAction::getInstance()->create("bookmark");
    lektuere *l = mode->getActiveText();
    if(l){
        bm->setName(std::to_string(getPosition()));
        bm->setZiel(mode->getActiveText());
        bm->setPosition(getPosition());
        Transactions::getCurrentTransaction()->add(l);
        l->addToToc(bm);
    }
    mode->tocView->reload();
}

bool LektuereDropHandler::canHandle(QDragEnterEvent *e)
{
    if(e->mimeData()->hasFormat("text/uri-list")){
        QUrl qu = e->mimeData()->urls().at(0);
        if(qu.isLocalFile()) return true;
    }
    return false;
}

bool LektuereDropHandler::canHandle(QDragMoveEvent *e)
{
    if(e->mimeData()->hasFormat("text/uri-list")){
        QUrl qu = e->mimeData()->urls().at(0);
        if(qu.isLocalFile()) return true;
    }
    return false;
}

bool LektuereDropHandler::dropEvent(QDropEvent *e)
{
    if(e->mimeData()->hasFormat("text/uri-list")){
        QUrl qu = e->mimeData()->urls().at(0);
        if(qu.isLocalFile()){
            qDebug() << QString("Import: %1").arg(qu.toString());

            QString fileName=qu.path();
            QString pureName=qu.fileName();


            AbstractMapper *mapper = MappingControler::getInstance()->getMapperByName("lektuere");
            lektuere *l=(lektuere*) mapper->create();
            Transactions::getCurrentTransaction()->add(l);
            l->setFileName(fileName.toStdString());
            l->setName(pureName.toStdString());
            DocStore::getInstance()->addDocument(l);
            m_view->addObject(l);

            return true;
        }

    }
    qDebug() << QString("PANIC - not a local file ??");
    return false;
}


