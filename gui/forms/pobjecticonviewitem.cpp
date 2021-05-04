//
// C++ Implementation: pobjecticonviewitem
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "pobjecticonviewitem.h"
#include "textpropertyviewer.h"
#include "textpropertyeditor.h"
#include "stringeditor.h"
#include "gui/base/guiconfig.h"
#include "orm/repository/repository.h"
#include "orm/repository/repositoryproperty.h"
#include "orm/transactions/transactions.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QMouseEvent>

PObjectIconViewItemBase::PObjectIconViewItemBase(PObject *o, QListWidget *iv)
 : QListWidgetItem(iv)
{
    this->object = o;
    this->lv=iv;
    setFlags(flags()|Qt::ItemIsEditable);
}

PObjectIconViewItemBase::~PObjectIconViewItemBase()
{
}

PObjectIconViewItem::PObjectIconViewItem(PObject *o, QListWidget *iv, QPixmap &icon, RepositoryProperty *displayProp)
 : PObjectIconViewItemBase(o,iv)
{
    if(displayProp){
        this->setText(displayProp->asString(o).c_str());
    } else {
        this->setText(o->getName().c_str());
    }
    this->setIcon(icon);
}

PObjectIconViewItem::~PObjectIconViewItem()
{
}


PObjectIconViewItemE::PObjectIconViewItemE(PObject *o, list<RepositoryProperty*> *listRp, QListWidget *iv, QPixmap &icon)
 : PObjectIconViewItemBase(o,iv),editor(0)
{
    widget = new QWidget(iv);
    QVBoxLayout *l= new QVBoxLayout();
    label1a=new QLabel();
    label1a->setPixmap(icon.scaledToHeight(12));
    label1b=new ActiveLabel(o,widget);
    connect(label1b,SIGNAL(clicked()),this,SLOT(editRequested()));
    connect(label1b, SIGNAL(nextPropertyRequested()), this, SLOT(switchVisible()));
    QHBoxLayout *lh = new QHBoxLayout();
    lh->addWidget(label1a);
    lh->addWidget(label1b);
    lh->setStretch(1,100);

    editorStack = new QStackedWidget(widget);
    for(list<RepositoryProperty*>::iterator it = listRp->begin(); it!=listRp->end();it++){
        RepositoryProperty *rp = (*it);
        if(rp->isText()){
            TextPropertyViewer *v = new TextPropertyViewer(o,rp,widget,6.0,28.0,TextPropertyViewer::MdLabel);
            v->setScrollBarPolicy(Qt::ScrollBarAlwaysOff);

            editor=v;
        }
        if(editor){
            int i=editorStack->addWidget(editor);
            PropertyButton *b = new PropertyButton(rp,i,widget);
            connect(b,SIGNAL(resized()),this,SLOT(setNewSize()));
            connect(b,SIGNAL(clicked()), this, SLOT(switchVisible()));
            lh->addWidget(b);

        }
    }

    l->addLayout(lh);
    l->addWidget(editorStack);
    widget->setLayout(l);

    editorStack->hide();
    iv->setItemWidget(this,widget);
    setSizeHint(widget->sizeHint());
}


void PObjectIconViewItemE::grepFocus()
{
    label1b->setFocus();
}

void PObjectIconViewItemE::showFull(bool full)
{
    //switchVisible();
    setSizeHint(widget->sizeHint());
}

void PObjectIconViewItemE::setNewSize()
{
    setSizeHint(widget->sizeHint());
}


void PObjectIconViewItemE::switchVisible()
{
    if(editorStack->isVisible()){
        editorStack->hide();
    } else {
        editorStack->show();
        if(editor){
            editorStack->setCurrentWidget(editor);
            //editor->setFocus();
        }
    }
    setNewSize();
}

PObjectIconViewItemE::~PObjectIconViewItemE()
{
}

/*
void PObjectIconViewItem::setText(QString &text)
{
    qDebug() << "PObjectIconViewItem setText called";
    getObject()->setName(text.toStdString());
    QListWidgetItem::setText(text);
}
*/
/*
void PObjectIconViewItemE::setDisplayProperty(RepositoryProperty *p)
{
    label2->setProperty(p);
}
*/

/*!
    \fn PObjectIconViewItem::getObject()
 */
PObject* PObjectIconViewItemBase::getObject()
{
    return object;
}


void PObjectIconViewItemE::editRequested()
{
    qDebug() << "WARNING: todo : PObjectIconViewItem::editRequested() not implemented";
    lv->editItem(this);
}

ActiveLabel::ActiveLabel(PObject *po,  QWidget *parent)
    : QStackedWidget(parent), editing(false)
{
    nameEditor = 0;
    this->po=po;
    //setFocusPolicy(Qt::ClickFocus);
    setFocusPolicy(Qt::StrongFocus);

    if(po){
        RepositoryEntry *re = Repository::getInstance()->getRepositoryEntry(po->getClassName());
        if(re ){
            RepositoryProperty *rpName = re->getProperty("Name");
            nameEditor = new StringEditor(po,rpName,parent);
            connect(nameEditor,SIGNAL(returnPressed()),this,SLOT(stopEdit()));
            addWidget(nameEditor);

        }
        nameLabel = new QLabel(po->getName().c_str());
        addWidget(nameLabel);
        setCurrentWidget(nameLabel);
    }
}

void ActiveLabel::stopEdit()
{
    if(nameEditor && po){
        nameEditor->stopEdit();
        nameLabel->setText(po->getName().c_str());
        setCurrentWidget(nameLabel);
        editing=false;
    }
}




void ActiveLabel::keyPressEvent(QKeyEvent *e)
{
    qDebug() << "ActiveLabel::keyPressEvent: " << e->key();

    if (e->key() == Qt::Key_F2){
        qDebug() << "ActiveLabel::keyPressEvent : F2 -> applyRequested";

        if(editing){
            stopEdit();
        } else {
            setCurrentWidget(nameEditor);
            nameEditor->setFocus();
            Transactions::getCurrentTransaction()->add(po);
            editing = true;

        }
    } else if(e->key() == Qt::Key_F1){
        emit nextPropertyRequested();
    } else {
        e->ignore();
    }


}

PropertyButton :: PropertyButton(RepositoryProperty *rp, int i, QWidget *parent)
    : QToolButton(parent)
{
    setIcon(GuiConfig::getInstance()->getIcon(rp));
    //connect(this,SIGNAL(clicked()),this,SLOT(switchVisible()));
}




