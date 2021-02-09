#include "textviewer.h"
#include "gui/actions/modelesen.h"

#include <QVBoxLayout>

TextViewer::TextViewer(QWidget *parent) :
    QWidget(parent)
{
    provider=0;
    doCommonSetup();
}

TextViewer::TextViewer(RepositoryProperty *rp, PObject *parent, QWidget *pw)
    : QWidget(pw)
{
    provider=new RpListProvider(rp,parent);
    doCommonSetup();
}

TextViewer::TextViewer(PObjectListProvider *prov,QWidget *pw)
    : QWidget(pw)
{
    provider = prov;
    doCommonSetup();
}

void TextViewer::doCommonSetup()
{
    colSplitter = new QSplitter(Qt::Horizontal,this);
    viewer = new PdfViewer(colSplitter);
    //toolBar = new QToolBar(this);
    //combo = new PObjectComboBox(provider,this);
    //selectButton = new QToolButton(toolBar);

    viewer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

    //toolBar->addWidget(selectButton);
    //toolBar->addWidget(combo);
    //connect(selectButton,SIGNAL(clicked()),this,SLOT(showSelectionMenu()));

    QVBoxLayout *l=new QVBoxLayout(this);
    l->setContentsMargins(0,0,0,0);
    //l->addWidget(toolBar);

    colDisplay = new CollectionDisplay("lektueresatz","Lektueren",colSplitter);
    //colDisplay->hide();
    connect(colDisplay,SIGNAL(itemChanged()),this,SLOT(loadNewLektuere()));


    colSplitter->addWidget(colDisplay);
    colSplitter->addWidget(viewer);
    QList<int> sizes;
    sizes << 200 << 300 << 10;
    colSplitter->setSizes(sizes);

    l->addWidget(colSplitter);
    //l->addWidget(viewer);

    //connect(combo,SIGNAL(currentIndexChanged(int)),this,SLOT(selectionChanged(int)));
    // load initial entry
}

void TextViewer::setProvider(PObjectListProvider *prov)
{
    combo->setProvider(prov);
    combo->load();
}

void TextViewer::setResizePolicy(bool res)
{
    viewer->setResizePolicy(res);
}

void TextViewer::load(){
    combo->load();
}

void TextViewer::setParentObject(PObject *o)
{
    combo->setParentObject(o);
}

/*
void TextViewer::setTextList(list<lektuere *> *tl)
{
    this->tlist = tl;
    combo->load((list<PObject*>*) tl);
}
*/

void TextViewer::setPage(int i)
{
    viewer->setPage(i);
}

int TextViewer::getPage()
{
    return viewer->pageNumber();
}

/*
void TextViewer::selectionChanged(int i){
    PObject *o=combo->getObject(i);
    if(lektuere *l = dynamic_cast<lektuere*>(o) ){
        viewer->loadNewFile(l->getFileName().c_str());
        activeText=l;
        emit textChanged(l);
        //ModeLesen::getInstance()->setActiveText(l);
    }
}
*/
void TextViewer::showSelectionMenu()
{
    colDisplay->show();
}


void TextViewer::loadNewLektuere()
{
    //colDisplay->hide();
    lektuere *l=dynamic_cast<lektuere*>(colDisplay->getCurrentItem());
    if(l){
        viewer->loadNewFile(l->getFileName().c_str());
        activeText=l;
        emit textChanged(l);
    }
}

void TextViewer::addSelectionAction(PdfViewSelectionAction *a)
{
    viewer->addSelectionAction(a);
}

void TextViewer::addKeyAction(Qt::Key key, PdfView::PdfViewAction a)
{
    viewer->addKeyAction(key, viewer->action(a));
}

void TextViewer::addContextMenuAction(PdfView::PdfViewAction a)
{
    viewer->addContextMenuAction(viewer->action(a));
}

