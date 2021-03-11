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



    splitter = new QSplitter(Qt::Horizontal,this);
    viewer = new TextPropertyViewer2(0,dispProp,splitter);
    iconView = new PObjectIconView(colProp,po,splitter);

    connect(iconView,SIGNAL(currentRowChanged(int)),this,SLOT(indexChanged(int)));





    QVBoxLayout *l= new QVBoxLayout(this);
    l->setContentsMargins(0,0,0,0);
    l->addWidget(splitter);

    if(po){
        setParentObject(po);
    }

}

void TextPropertyBrowser::numberChanged(int i)
{
    PObject *o=iconView->getCurrent();
    if(lektuerenotiz* ln=dynamic_cast<lektuerenotiz*>(o))
    {
        Transactions::getCurrentTransaction()->add(ln);
        ln->setSeite(i);
    }

}

void TextPropertyBrowser::nameChanged(QString newName)
{
    PObject *o=iconView->getCurrent();
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
    iconView->setParentObject(po);

}


void TextPropertyBrowser::indexChanged(int i)
{
        PObject *o=iconView->getObject(i);
        viewer->setParentObject(o);
        if(lektuerenotiz *ln = dynamic_cast<lektuerenotiz*>(o))
        {
            int npage=ln->getSeite();
        }

}

void TextPropertyBrowser::gotoPage()
{
      qDebug("WARNING: TextPropertyBrowser::gotoPage() -- do nothing!!");
}

void TextPropertyBrowser::setActiveObject(PObject *o)
{
    qDebug("WARNING: TextPropertyBrowser::setActiveObject - do nothing implementation");
}

