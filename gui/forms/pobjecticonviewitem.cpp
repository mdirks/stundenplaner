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

PObjectIconViewItem::PObjectIconViewItem(PObject *o, QListWidget *iv, QPixmap &icon)
 : PObjectIconViewItemBase(o,iv)
{
    this->setText(o->getName().c_str());
    this->setIcon(icon);
}

PObjectIconViewItem::~PObjectIconViewItem()
{
}


PObjectIconViewItemE::PObjectIconViewItemE(PObject *o, RepositoryProperty *rp, QListWidget *iv, QPixmap &icon)
 : PObjectIconViewItemBase(o,iv)
{
    widget = new QWidget(iv);
    QVBoxLayout *l= new QVBoxLayout();
    label1a=new QLabel();
    label1a->setPixmap(icon.scaledToHeight(12));
    label1b=new ActiveLabel(o->getName().c_str(),widget);
    connect(label1b,SIGNAL(clicked()),this,SLOT(editRequested()));
    QHBoxLayout *lh = new QHBoxLayout();
    lh->addWidget(label1a);
    lh->addWidget(label1b);
    lh->setStretch(1,100);
    l->addLayout(lh);
    label2=new TextPropertyViewer(o,rp,widget,6.0,28.0);
    label2->setScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    l->addWidget(label2);
    widget->setLayout(l);

    label2->hide();
    iv->setItemWidget(this,widget);
    setSizeHint(widget->sizeHint());
}

void PObjectIconViewItemE::showFull(bool full)
{
    if(full){
        label2->show();
    }else {
        label2->hide();
    }
    setSizeHint(widget->sizeHint());
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
void PObjectIconViewItemE::setDisplayProperty(RepositoryProperty *p)
{
    label2->setProperty(p);
}

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

void ActiveLabel::mouseDoubleClickEvent( QMouseEvent * e ) {
    if(e->button() == Qt::LeftButton)
        emit clicked();
    QLabel::mouseDoubleClickEvent(e);
}
