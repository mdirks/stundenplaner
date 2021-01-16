#include "textpropertybrowser.h"
#include "gui/actions/guicreateaction.h"
#include "gui/actions/modelesen.h"
#include "orm/transactions/transactions.h"
#include "datamodel/lektuerenotiz.h"

#include <QVBoxLayout>
#define TB_HEIGHT 17

TextPropertyBrowser::TextPropertyBrowser(PObject *po, RepositoryProperty *cP, RepositoryProperty *dispProp, QWidget *parent) :
    QWidget(parent)
{
    this->colProp=cP;
    parentObject=0;

    viewer = new TextPropertyViewer2(0,dispProp,this);
    toolBar = new QToolBar(this);

    combo = new PObjectComboBox(colProp,po,this);
    connect(combo,SIGNAL(currentIndexChanged(int)),this,SLOT(indexChanged(int)));
    connect(combo,SIGNAL(editTextChanged(QString)),this,SLOT(nameChanged(QString)));

    /*
    QString String = "border: 0px solid black;";
    combo->setStyleSheet(String );
    combo->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    combo->setEditable(true);
    combo->setInsertPolicy(QComboBox::InsertAtCurrent);
    */

    spinBox = new QSpinBox(this);
    spinBox->setMaximum(999);
    connect(spinBox,SIGNAL(valueChanged(int)),this,SLOT(numberChanged(int)));
    gotoButton =new QToolButton(this);
    connect(gotoButton,SIGNAL(clicked()),this,SLOT(gotoPage()));
    //toolBar->addAction("New",this,SLOT(newObject()));
    spinBox->setFixedHeight(TB_HEIGHT);
    combo->setFixedHeight(TB_HEIGHT);
    gotoButton->setFixedHeight(TB_HEIGHT);
    toolBar->addWidget(combo);
    toolBar->addWidget(spinBox);
    toolBar->addWidget(gotoButton);




    QVBoxLayout *l= new QVBoxLayout(this);
    l->setContentsMargins(0,0,0,0);
    l->addWidget(toolBar);
    l->addWidget(viewer);

    if(po){
        setParentObject(po);
    }

}

void TextPropertyBrowser::numberChanged(int i)
{
    PObject *o=combo->getObject(combo->currentIndex());
    if(lektuerenotiz* ln=dynamic_cast<lektuerenotiz*>(o))
    {
        Transactions::getCurrentTransaction()->add(ln);
        ln->setSeite(i);
    }
    //if(i!=0) ModeLesen::getInstance()->setActivePage(i);

}

void TextPropertyBrowser::nameChanged(QString newName)
{
    PObject *o=combo->getObject(combo->currentIndex());
    if(lektuerenotiz* ln=dynamic_cast<lektuerenotiz*>(o))
    {
        Transactions::getCurrentTransaction()->add(ln);
        ln->setName(newName.toStdString());
    }
}

PObject* TextPropertyBrowser::newObject()
{

    PObject *o = GuiCreateAction::getInstance()->create(colProp->getType());
    Transactions::getCurrentTransaction()->add(parentObject);
    colProp->add(o,parentObject);
    setParentObject(parentObject);
    return o;
}

void TextPropertyBrowser::setParentObject(PObject *po)
{
    this->parentObject=po;
    combo->setParentObject(po);

    /*
    if(colProp){
        load(colProp->asCollection(parentObject));
    }
    */
}

/*
void TextPropertyBrowser::load(list<PObject*> *ol)
{
    this->olist = ol;

    int ind=combo->currentIndex();
    combo->clear();
    for(list<PObject*>::iterator it=olist->begin(); it!=olist->end(); it++)
    {
        combo->addItem((*it)->getName().c_str());
    }
    //if(ind>-1) combo->setCurrentIndex(ind);
}
*/

void TextPropertyBrowser::indexChanged(int i)
{
        PObject *o = combo->getObject(i);
        viewer->setParentObject(o);
        if(lektuerenotiz *ln = dynamic_cast<lektuerenotiz*>(o))
        {
            int npage=ln->getSeite();
            spinBox->setValue(npage);
            //ModeLesen::getInstance()->setActivePage(npage);
        }

}

void TextPropertyBrowser::gotoPage()
{
        int pn=spinBox->value();
        ModeLesen::getInstance()->setActivePage(pn);
}

void TextPropertyBrowser::setActiveObject(PObject *o)
{
    combo->setActiveObject(o);
}

/*
PObject* TextPropertyBrowser::getObject(int i)
{
    PObject *o=0;
    if(olist && i<olist->size() && i>-1){
        std::list<PObject*>::iterator it = olist->begin();
        std::advance(it,i);
        o=*it;
    }
    return o;
}
*/
