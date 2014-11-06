#include "textviewer.h"
#include "gui/actions/modelesen.h"

#include <QVBoxLayout>

TextViewer::TextViewer(QWidget *parent) :
    QWidget(parent)
{
    viewer = new PdfViewer(this);
    toolBar = new QToolBar(this);
    combo = new PObjectComboBox(0,this);

    viewer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

    toolBar->addWidget(combo);

    QVBoxLayout *l=new QVBoxLayout(this);
    l->addWidget(toolBar);
    l->addWidget(viewer);

    connect(combo,SIGNAL(currentIndexChanged(int)),this,SLOT(selectionChanged(int)));
}

TextViewer::TextViewer(RepositoryProperty *rp, PObject *parent, QWidget *pw)
    : QWidget(pw)
{
    viewer = new PdfViewer(this);
    toolBar = new QToolBar(this);
    combo = new PObjectComboBox(rp,parent,this);

    viewer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

    toolBar->addWidget(combo);

    QVBoxLayout *l=new QVBoxLayout(this);
    l->addWidget(toolBar);
    l->addWidget(viewer);

    connect(combo,SIGNAL(currentIndexChanged(int)),this,SLOT(selectionChanged(int)));
}

void TextViewer::load(){
    combo->load();
}

void TextViewer::setParentObject(PObject *o)
{
    combo->setParentObject(o);
}

void TextViewer::setTextList(list<lektuere *> *tl)
{
    this->tlist = tl;
    combo->load((list<PObject*>*) tl);
}

void TextViewer::setPage(int i)
{
    viewer->setPage(i);
}

void TextViewer::selectionChanged(int i){
    PObject *o=combo->getObject(i);
    if(lektuere *l = dynamic_cast<lektuere*>(o) ){
        viewer->loadNewFile(l->getFileName().c_str());
        activeText=l;
        emit textChanged(l);
        ModeLesen::getInstance()->setActiveText(l);
    }
}


